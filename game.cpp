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
#include "unitdata.h"
#include "text_texture.h"
#include "reserve.h"
#include "result.h"
#include "bullet.h"
#include "playerArms.h"
#include "rescueLife.h"
#include "mapWallModel.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************



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
static int	g_PlayMode = MAIN_GAME;
static int mode = 1;
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
	// ライトを有効化	// 影の初期化処理
	InitShadow();

	InitPlayer();

	//InitBullet();	
	// フィールドの初期化
	InitMeshField(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), FIELD_X, FIELD_Z, BLOCK_SIZE, BLOCK_SIZE, GROUND);

	MapWallModel::Init();

	//InitOver();


	//InitCharFade();

	//InitTexttex();


	InitUI();
	RescueLife::InitRescue();
	RescueLife::SetRemain(4);
	//InitReward();
	mode = 1;
	g_bPause = TRUE;

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

	UninitTexttex();

	MapWallModel::Uninit();

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateGame(void)
{
	if (GetKeyboardTrigger(DIK_P) && !GetHelpButton())
	{
		if (g_bPause == TRUE)
			g_bPause = FALSE;
		else
			g_bPause = TRUE;
	}

	//等速と倍速の切り替え
	if (GetKeyboardTrigger(DIK_O))
	{
		mode == 1 ? mode++ : mode--;
	}

	FADE fade = GetFade();
	if (fade != FADE_NONE)return;


	if(g_bPause == FALSE)
		return;

	UpdateOver();

	UpdateTexttex();
	if (CheckGameover())return;

	if (GetHelpButton())return;


		UpdateCamera();

		UpdatePlayer();

		UpdateLight();

		MapWallModel::Update();

		//UpdateBullet();

		//UpdateCharFade();
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

	DrawPlayer();

	//DrawBullet();


	// 2D座標で物を描画する処理
	// Z比較なし
	SetDepthEnable(FALSE);

	// ライティングを無効
	SetLightEnable(FALSE);

	DrawUI();

	//DrawOver();

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

	DrawPlayer();

}


void DrawGame(void)
{
	XMFLOAT3 pos;

	// プレイヤー視点
	CAMERA *cam = GetCamera();
	PLAYER *player = GetPlayer();
	pos = player[0].pos;
	pos.y -= 10.0f;
	const float dist = 200.0f;
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