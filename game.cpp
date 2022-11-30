//=============================================================================
//
// ゲーム画面処理 [game.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "renderer.h"
#include "model.h"
#include "camera.h"
#include "light.h"
#include "input.h"
#include "sound.h"
#include "fade.h"
#include "game.h"
#include "collision.h"
#include "debugproc.h"
#include "file.h"
#include "shadow.h"
#include "meshfield.h"
#include "player.h"
#include "gameover.h"
#include "ui.h"
#include "text_texture.h"
#include "reserve.h"
#include "result.h"
#include "bullet.h"
#include "playerArms.h"
#include "rescueLife.h"
#include "mapWallModel.h"
#include "obstacle.h"
#include "particle.h"
#include "map.h"
#include "meshwall.h"
#include "unitdata.h"
#include "time.h"
#include "title.h"
#include "fire.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define LEAD_TIME (180)		//ゲーム開始前の秒数 * 60


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************



//*****************************************************************************
// グローバル変数
//*****************************************************************************
static int	g_ViewPortType_Game = TYPE_FULL_SCREEN;

static BOOL	g_bPause = TRUE;	// ポーズON/OFF
static BOOL g_Slow = FALSE;
static int s_mode = FALSE;
static BOOL gameover = FALSE;
static int	g_PlayMode = MAIN_GAME;
static int mode = 1;
static 	XMFLOAT3 cam_pos = { 0.0f, 0.0f, 0.0f };
static 	XMFLOAT3 cam_rot = { 0.0f, 0.0f, 0.0f };
static int set_time = LEAD_TIME + 10;
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitGame(void)
{
	g_ViewPortType_Game = TYPE_FULL_SCREEN;
	InitSystem();

	return S_OK;
}

void InitSystem(void)
{
	CAMERA* cam = GetCamera();
	cam->rot = { 0.0f, 0.0f, 0.0f };
	// ライトを有効化	// 影の初期化処理
	InitShadow();

	InitPlayer();


	pArm::InitArm();
	Normal::InitArm();

	InitBullet();	

	// フィールドの初期化
	InitMeshField(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), FIELD_X, FIELD_Z, BLOCK_SIZE, BLOCK_SIZE, GROUND);


	InitTime();
	InitOver();


	InitCharFade();

	//InitTexttex();

	InitParticle();
	InitUI();
	InitFire();
	RescueLife::InitRescue();
	MapWallModel::Init();
	Obstacle::Init();
	FallObject::Init();

	InitMap();
	//InitReward();
	mode = 1;
	set_time = LEAD_TIME + 30;
#ifdef _DEBUG
	set_time = 0;
#endif
	g_bPause = TRUE;
	gameover = FALSE;
}

//起動時に重い処理はすべて行っておく(モデルのロードなど)
void InitBoot(void)
{
	pArm::InitArmBoot();
	Normal::InitArmBoot();
	MapWallModel::InitBoot();
	FallObject::InitBoot();
	RescueLife::InitBootRescue();
	Obstacle::InitBoot();
	InitBulletBoot();
	InitBootPlayer();
	Map::InitBootMap();
}

void InitMap(void)
{
	UninitMeshWall();	//メッシュウォールはここで逐一初期化

	switch (GetMode())
	{
	case MODE_TITLE:
		Map::InitMap();
		break;
	case MODE_RESERVE:
		Map::InitMap();
		break;
	case MODE_GAME:
		Map::InitMap();
		break;
	case MODE_RESULT:
		Map::InitResultMap();
		break;
	}
}
//=============================================================================
// 終了処理
//=============================================================================
void UninitGame(void)
{
	// 影の終了処理
	UninitShadow();

	UninitOver();

	UninitBullet();

	UninitUI();

	UninitFire();

	UninitParticle();

	UninitTexttex();

	Obstacle::Uninit();

	MapWallModel::Uninit();

	FallObject::Uninit();

	RescueLife::UninitRescue();

	UninitMeshWall();

	UninitTime();
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateGame(void)
{
#ifdef _DEBUG
	if (GetKeyboardTrigger(DIK_P) && !GetHelpButton())
	{
		if (g_bPause == TRUE)
			g_bPause = FALSE;
		else
			g_bPause = TRUE;
	}
	if (GetKeyboardTrigger(DIK_G))
	{
		gameover = TRUE;
	}
	if (GetKeyboardTrigger(DIK_H))
	{
		Reward* re = GetReward();
		Reserve* res = GetReserve();
		gameover = TRUE;
		re->rescue_num = res->quota;
	}
#endif
	//等速と倍速の切り替え
	if (GetKeyboardTrigger(DIK_O))
	{
		mode == 1 ? mode++ : mode--;
	}

	FADE fade = GetFade();
	if (fade != FADE_NONE)return;


	if(g_bPause == FALSE)
		return;

	if(set_time > 0)set_time--;
	if (set_time > 0)return;

	UpdateOver();

	UpdateTexttex();
	if (CheckGameover())return;

	if (GetHelpButton())return;


		UpdateCamera();

		UpdatePlayer();

		UpdateLight();

		UpdateMeshWall();

		MapWallModel::Update();

		UpdateBullet();

		Obstacle::Update();

		FallObject::Update();

		UpdateTime();

		UpdateFire();

		UpdateParticle();
		UpdateCharFade();
		//// 影の更新処理
		//UpdateShadow();

		//UpdateFog();

		//UpdateSound();

		UpdateUI();
}

//=============================================================================
// 描画処理(カメラ目線)
//=============================================================================
void DrawGame0(void)
{
	//シェーダー管理
	//ポストエフェクトをかける場合はここから
	int ans = MODE_PLANE;
	SwapShader(ans);

	DrawMeshField();

	MapWallModel::Draw();


	DrawMeshWall();

	Obstacle::Draw();

	FallObject::Draw();

	RescueLife::DrawRescue();

	DrawFire();

	DrawPlayer();

	//DrawBullet();
	DrawBulletModel();

	DrawParticle();

	// 2D座標で物を描画する処理
	// Z比較なし
	SetDepthEnable(FALSE);

	// ライティングを無効
	SetLightEnable(FALSE);

	DrawTime();

	DrawUI();

	DrawOver();

	//// スコアの描画処理
	//DrawScore();


	//シェーダー管理
	//シェーダーを元に戻す。ポストエフェクトはここまで
	ans = MODE_PLANE;
	SwapShader(ans);

	// ライティングを有効に
	SetLightEnable(TRUE);

	// Z比較あり
	SetDepthEnable(TRUE);
}


//=============================================================================
// 描画処理(ライト目線。生成したい影のオブジェクトだけを指定)
//=============================================================================
void DrawGame1(void)
{
	DrawMeshField();

	MapWallModel::Draw();

	Obstacle::Draw();

	if(GetMode() == MODE_GAME)
	DrawPlayer();

}


void DrawGame(void)
{
	XMFLOAT3 pos;

	// プレイヤー視点
	CAMERA *cam = GetCamera();
	PLAYER *player = GetPlayer();
	pos = player[0].pos;
	pos.y += 0.0f;
	const float dist = 250.0f;
	pos.x += sinf(cam->rot.y)*dist;
	pos.z += cosf(cam->rot.y)*dist;
	SetCameraAT(pos);
	SetCamera();

	switch(g_ViewPortType_Game)
	{
	case TYPE_FULL_SCREEN:
			DrawGame0();
			break;
	case TYPE_LEFT_HALF_SCREEN:
	case TYPE_RIGHT_HALF_SCREEN:
		SetViewPort(TYPE_LEFT_HALF_SCREEN);
		DrawGame0();

		// エネミー視点
		break;

	case TYPE_UP_HALF_SCREEN:
	case TYPE_DOWN_HALF_SCREEN:
		SetViewPort(TYPE_UP_HALF_SCREEN);
		DrawGame0();

		break;

	case TYPE_LIGHT_SCREEN:	//ライト目線の描画をするためのビューポートタイプ
		SetViewPort(TYPE_FULL_SCREEN);
		DrawGame1();
		break;

	}

}


void DrawGameTitle(void)
{
	CAMERA *cam = GetCamera();
#ifdef _DEBUG
	if (GetKeyboardPress(DIK_W))
	{
		cam_pos.x += sinf(cam->rot.y);
		cam_pos.z += cosf(cam->rot.y);
	}
	if (GetKeyboardPress(DIK_S))
	{
		cam_pos.x -= sinf(cam->rot.y);
		cam_pos.z -= cosf(cam->rot.y);
	}
	if (GetKeyboardPress(DIK_A))
	{
		cam_pos.x -= cosf(cam->rot.y);
		cam_pos.z += sinf(cam->rot.y);
	}
	if (GetKeyboardPress(DIK_D))
	{
		cam_pos.x += cosf(cam->rot.y);
		cam_pos.z -= sinf(cam->rot.y);
	}
	if (GetKeyboardPress(DIK_U))
	{
		cam_pos.y += 1.0f;
	}
	if (GetKeyboardPress(DIK_V))
	{
		cam_pos.y -= 1.0f;
	}
	PrintDebugProc("\nカメラ座標x:%f,y:%f,z:%f\n", cam_pos.x, cam_pos.y, cam_pos.z);
#endif
	XMFLOAT3 pos;
	XMFLOAT3 rot;
	// プレイヤー視点
	pos = cam_pos;
	pos.y += 0.0f;
	const float dist = 0.0f;
	pos.x += sinf(cam->rot.y)*dist;
	pos.z += cosf(cam->rot.y)*dist;
	SetCameraAT(pos);
	SetCamera();

	//シェーダー管理
//ポストエフェクトをかける場合はここから
	int ans = MODE_PLANE;
	SwapShader(ans);

	DrawMeshField();

	MapWallModel::Draw();

	DrawMeshWall();

	Obstacle::Draw();

	RescueLife::DrawRescue();

	DrawFire();

	DrawParticle();

	// 2D座標で物を描画する処理
	// Z比較なし
	SetDepthEnable(FALSE);

	// ライティングを無効
	SetLightEnable(FALSE);

	//シェーダー管理
	//シェーダーを元に戻す。ポストエフェクトはここまで
	ans = MODE_PLANE;
	SwapShader(ans);

	DrawTitle();

	// ライティングを有効に
	SetLightEnable(TRUE);

	// Z比較あり
	SetDepthEnable(TRUE);

}

void DrawGameResult(void)
{
	CAMERA *cam = GetCamera();
#ifdef _DEBUG
	if (GetKeyboardPress(DIK_W))
	{
		cam_pos.x += sinf(cam->rot.y);
		cam_pos.z += cosf(cam->rot.y);
	}
	if (GetKeyboardPress(DIK_S))
	{
		cam_pos.x -= sinf(cam->rot.y);
		cam_pos.z -= cosf(cam->rot.y);
	}
	if (GetKeyboardPress(DIK_A))
	{
		cam_pos.x -= cosf(cam->rot.y);
		cam_pos.z += sinf(cam->rot.y);
	}
	if (GetKeyboardPress(DIK_D))
	{
		cam_pos.x += cosf(cam->rot.y);
		cam_pos.z -= sinf(cam->rot.y);
	}
	if (GetKeyboardPress(DIK_U))
	{
		cam_pos.y += 1.0f;
	}
	if (GetKeyboardPress(DIK_V))
	{
		cam_pos.y -= 1.0f;
	}
	PrintDebugProc("\nカメラ座標x:%f,y:%f,z:%f\n", cam_pos.x, cam_pos.y, cam_pos.z);
#endif
	XMFLOAT3 pos = cam_pos;
	 //プレイヤー視点
	pos = XMFLOAT3{256.0f,-91.0f,-149.0f};
	cam->rot.y = 2.03f;
	cam->rot.x = 0.38f;
	const float dist = 0.0f;
	pos.x += sinf(cam->rot.y)*dist;
	pos.z += cosf(cam->rot.y)*dist;
	SetCameraAT(pos);
	SetCamera();

	//シェーダー管理
//ポストエフェクトをかける場合はここから
	int ans = MODE_PLANE;
	SwapShader(ans);

	DrawMeshField();

	MapWallModel::Draw();

	DrawMeshWall();

	Obstacle::Draw();

	RescueLife::DrawRescue();

	DrawFire();

	DrawPlayer();

	DrawParticle();

	// 2D座標で物を描画する処理
	// Z比較なし
	SetDepthEnable(FALSE);

	// ライティングを無効
	SetLightEnable(FALSE);

	//シェーダー管理
	//シェーダーを元に戻す。ポストエフェクトはここまで
	ans = MODE_PLANE;
	SwapShader(ans);

	DrawResult();

	// ライティングを有効に
	SetLightEnable(TRUE);

	// Z比較あり
	SetDepthEnable(TRUE);

}

void DrawGameReserve(void)
{
	CAMERA *cam = GetCamera();
	int ans = MODE_PLANE;
	SwapShader(ans);
#ifdef _DEBUG
	if (GetKeyboardPress(DIK_W))
	{
		cam_pos.x += sinf(cam->rot.y);
		cam_pos.z += cosf(cam->rot.y);
	}
	if (GetKeyboardPress(DIK_S))
	{
		cam_pos.x -= sinf(cam->rot.y);
		cam_pos.z -= cosf(cam->rot.y);
	}
	if (GetKeyboardPress(DIK_A))
	{
		cam_pos.x -= cosf(cam->rot.y);
		cam_pos.z += sinf(cam->rot.y);
	}
	if (GetKeyboardPress(DIK_D))
	{
		cam_pos.x += cosf(cam->rot.y);
		cam_pos.z -= sinf(cam->rot.y);
	}
	if (GetKeyboardPress(DIK_U))
	{
		cam_pos.y += 1.0f;
	}
	if (GetKeyboardPress(DIK_V))
	{
		cam_pos.y -= 1.0f;
	}
	PrintDebugProc("\nカメラ座標x:%f,y:%f,z:%f\n", cam_pos.x, cam_pos.y, cam_pos.z);
#endif

	XMFLOAT3 pos = cam_pos;
	cam_rot.y += XM_PI * 0.001f;
	if (cam_rot.y >= XM_PI * 2.0f)
		cam_rot.y = 0.0f;

	// プレイヤー視点
	//pos = XMFLOAT3{ 243.0f,-124.0f,-143.0f };
	//cam->rot.y = 2.03f;
	//cam->rot.x = 0.3f;
	float dist = 0.0f;
	pos.x += sinf(cam_rot.y)*dist;
	pos.z += cosf(cam_rot.y)*dist;
	SetReserveCameraAT(pos, cam_rot);
	SetCamera();

	DrawMeshField();

	MapWallModel::Draw();

	DrawMeshWall();

	Obstacle::Draw();

	DrawFire();

	// プレイヤー視点
	pos = XMFLOAT3{ 243.0f,-124.0f,-143.0f };
	cam->rot.y = 2.03f;
	cam->rot.x = 0.3f;
	dist = 0.0f;
	pos.x += sinf(cam->rot.y)*dist;
	pos.z += cosf(cam->rot.y)*dist;
	SetCameraAT(pos);
	SetCamera();

	//シェーダー管理
//ポストエフェクトをかける場合はここから
	ans = MODE_PLANE;
	SwapShader(ans);

	//シェーダー管理
	//シェーダーを元に戻す。ポストエフェクトはここまで
	ans = MODE_PLANE;
	SwapShader(ans);

	DrawPlayer();

	// 2D座標で物を描画する処理
	// Z比較なし
	SetDepthEnable(FALSE);

	// ライティングを無効
	SetLightEnable(FALSE);

	//シェーダー管理
	//シェーダーを元に戻す。ポストエフェクトはここまで
	ans = MODE_PLANE;
	SwapShader(ans);

	DrawReserve();
	// ライティングを有効に
	SetLightEnable(TRUE);

	// Z比較あり
	SetDepthEnable(TRUE);

}

void SetPlayMode(int playMode)
{
	g_PlayMode = playMode;
}

int GetPlayMode(void)
{
	return g_PlayMode;
}

void SetSlowMode(BOOL flag)
{
	g_Slow = flag;
}
//void SetPlayStage(int stageNum)
//{
//	g_PlayStage = stageNum;
//}

//int GetPlayStage(void)
//{
//	return g_PlayStage;
//}

void SetViewPortType(int viewport)
{
	g_ViewPortType_Game = viewport;
}

int GetViewPortTypeGame(void)
{
	return g_ViewPortType_Game;
}

//数値のクランプ。引数1:クランプしたい数値、引数2:最小値、引数3:最大値
float FloatClamp(float x, float a, float b)
{
	if (x < a)
	{
		return a;
	}
	else if (x > b)
	{
		return b;
	}
	else
	{
		return x;
	}
}

//float型の数値の比較をする。flagがFALSEなら小さい方を、TRUEなら大きい方を返す
float FloatCompare(BOOL flag, float a, float b)
{
	float ans = 0.0f;//一応0.0fをセットしておく
	switch (flag)
	{
	case FALSE:
		if (a > b)return b;
		else	  return a;
		break;
	case TRUE:
		if (a > b)return a;
		else	  return b;
		break;
	}

	return ans;
}


BOOL CheckGameover(void)
{
	BOOL ans = FALSE;
	Reward* re = GetReward();
	Reserve* res = GetReserve();

	if (GetTime() <= 0 || RescueLife::GetRescueRemainLife() <= 0 || gameover)
	{
		if (res->quota <= re->rescue_num)
			SetOverType(OVER_WIN);
		else
			SetOverType(OVER_LOSE);

		ans = TRUE;
	}

	return ans;
}

//ダメージ計算関数。引数のそれぞれに、攻撃者の攻撃力と防御側の防御力を持ってくる
int DamageFunc(int attacker, int diffender)
{
	//ひとまず単純な計算式で済ます
	int ans = attacker - diffender;
	//必ず1以上でダメージを返すようにする
	if (ans <= 0)
		ans = 1;
	return ans;
}

int GetSpeedMode(void)
{
	return mode;
}

int GetSetTime(void)
{
	return set_time;
}
