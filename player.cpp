//=============================================================================
//
// バトル中のプレイヤー処理 [player.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "math.h"
#include "input.h"
#include "camera.h"
#include "debugproc.h"
#include "model.h"
#include "game.h"
#include "player.h"
#include "shadow.h"
#include "light.h"
#include "meshfield.h"
#include "collision.h"
#include "time.h"
#include "sound.h"
#include "bullet.h"
#include "playerArms.h"
#include "particle.h"
#include "meshwall.h"
#include "playerIPData.h"
#include <algorithm>

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_MAX			(1)								// テクスチャの数
#define VAR_WIDTH			(50.0f)
#define VAR_HEIGHT			(5.0f)
#define	VALUE_MOVE			(10.0f)							// 移動量
#define	VALUE_AT_MOVE		(4.0f)							// 移動量
#define	VALUE_ROTATE		(XM_PI * 0.02f)					// 回転量

#define PLAYER_SHADOW_SIZE	(1.0f)							// 影の大きさ
#define PLAYER_OFFSET_Y		(0.0f)							// プレイヤーの足元をあわせる
#define PLAYER_OFFSET_Z		(-300.0f)							// プレイヤーの足元をあわせる
#define PLAYER_LIFE			(100)								// プレイヤーのライフ

#define PLAYER_PARTS_MAX	(1)								// プレイヤーのパーツの数
#define PLAYER_AT_FLAME		(30.0f)							// プレイヤーの攻撃フレーム
#define PLAYER_SP_FLAME		(30.0f)							// プレイヤーのSPが増える間隔
#define PLAYER_INVINC_FLAME	(120.0f)						// プレイヤー無敵フレーム
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
static ID3D11Buffer					*g_VertexBuffer = NULL;	// 頂点情報
static ID3D11ShaderResourceView		*g_Texture[TEXTURE_MAX] = { NULL };	// テクスチャ情報
static char* g_TextureName[] = {
	"data/TEXTURE/var.png",
};
static PLAYER_VAR	g_PlayerVar;
static PLAYER		g_Player[MAX_PLAYER];						// プレイヤー
static Playerliner  g_Playerline[MAX_PLAYER];					//プレイヤーの線形補間データ
static PLAYER		g_Parts[MAX_PLAYER_PARTS];					// プレイヤー
static pArm*		g_PlayerArm[3];	//先端アームの種類数
static pArm*		g_Arm[2];		//アームの数
static BOOL			g_Load = FALSE;
static int			playerNum = 0;
static int			atNum[MAX_PLAYER];
static char name[2][64];

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitPlayer(void)
{
	ID3D11Device *pDevice = GetDevice();
	MakeVertexPlayerVar();
	// テクスチャ生成
	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		D3DX11CreateShaderResourceViewFromFile(GetDevice(),
			g_TextureName[i],
			NULL,
			NULL,
			&g_Texture[i],
			NULL);
	}

	ZeroMemory(&g_PlayerVar.material, sizeof(g_PlayerVar.material));
	g_PlayerVar.material.Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	g_PlayerVar.pos = { 0.0f, 0.0f, 0.0f };
	g_PlayerVar.rot = { XM_PI * -0.5f, 0.0f, 0.0f };
	g_PlayerVar.scl = { 1.0f, 1.0f, 1.0f };
	g_PlayerVar.pardiff = 0.0f;
	g_PlayerVar.parpolar = 0.02f;
	g_PlayerVar.load = TRUE;

	strcpy(name[0], MODEL_PLAYER);
	strcpy(name[1], MODEL_NEUTROPHILS);

	for (int i = 0; i < MAX_PLAYER; i++)
	{
		g_Player[i].load = FALSE;
		g_Player[i].pos = { 0.0f, PLAYER_OFFSET_Y, 0.0f };
		g_Player[i].rot = { 0.0f, -XM_PI * 0.5f, 0.0f };
		g_Player[i].scl = { 1.0f, 1.0f, 1.0f };
		g_Player[i].moveVec = { 0.0f, 0.0f, 0.0f };

		g_Player[i].size = PLAYER_SIZE;		// 当たり判定の大きさ
		g_Player[i].use = FALSE;
		g_Player[i].life = PLAYER_LIFE;
		g_Player[i].lifeMax = g_Player[i].life;
		g_Player[i].power = 5;
		g_Player[i].diffend = 3;
		g_Player[i].attack = FALSE;
		g_Player[i].attackUse = FALSE;
		g_Player[i].partsNum = 9;
		g_Player[i].startNum = 0;
		g_Player[i].spd = 0.0f;
		g_Player[i].armType = 0;

		// 階層アニメーション用の初期化処理
		g_Player[i].parent = NULL;			// 本体（親）なのでNULLを入れる
		g_Playerline[i].pos = { 0.0f, 0.0f, 0.0f };
		g_Playerline[i].rot = { 0.0f, 0.0f, 0.0f };
		g_Playerline[i].scl = { 0.0f, 0.0f, 0.0f };
	}
	
	for (int i = 0; i < MAX_PLAYER_PARTS; i++)
	{
		g_Parts[i].load = FALSE;
		g_Parts[i].use = FALSE;
	}
	
	g_Player[0].use = TRUE;
	g_Player[0].load = TRUE;
	g_Player[0].partsNum = 9;
	LoadModel(MODEL_BODY, &g_Player[0].model);
	SetPlayerArm();

	for (int i = 0; i < MAX_PLAYER_PARTS; i++) {
		g_Parts[i].parent = &g_Player[0];
		g_Parts[i].load = TRUE;
		g_Parts[i].pos = { 0.0f, 0.0f, 0.0f };
		g_Parts[i].rot = { 0.0f, 0.0f, 0.0f };
		g_Parts[i].scl = { 1.0f,1.0f, 1.0f };
		g_Parts[i].tbl_adrM = NULL;
	}
	//モデル読み込みとペアレント付けを行う
	LoadModel(MODEL_HEAD, &g_Parts[P_HEAD].model);
	LoadModel(MODEL_L_SHOULDER, &g_Parts[P_L_SHOULDER].model);
	LoadModel(MODEL_R_SHOULDER, &g_Parts[P_R_SHOULDER].model);

	LoadModel(MODEL_L_ARM, &g_Parts[P_L_ARM].model);
	g_Parts[P_L_ARM].parent = &g_Parts[P_L_SHOULDER];
	g_Parts[P_L_ARM].tbl_adrM = walk_Larm;
	g_Parts[P_L_ARM].tbl_sizeM = sizeof(walk_Larm) / sizeof(INTERPOLATION_DATA);

	LoadModel(MODEL_R_ARM, &g_Parts[P_R_ARM].model);
	g_Parts[P_R_ARM].parent = &g_Parts[P_R_SHOULDER];

	LoadModel(MODEL_L_THIGH, &g_Parts[P_L_THIGH].model);
	LoadModel(MODEL_R_THIGH, &g_Parts[P_R_THIGH].model);

	LoadModel(MODEL_L_FOOT, &g_Parts[P_L_FOOT].model);
	g_Parts[P_L_FOOT].parent = &g_Parts[P_L_THIGH];

	LoadModel(MODEL_R_FOOT, &g_Parts[P_R_FOOT].model);
	g_Parts[P_R_FOOT].parent = &g_Parts[P_R_THIGH];

	g_Load = TRUE;
	playerNum = 0;
	pArm::SetArmParent(&g_Player[0]);	//親情報をここで引き渡す
	g_Arm[0] = pArm::GetArm();
	g_Arm[1] = pArm::GetArm();
	for (int i = 0; i < MAX_PLAYER; i++)
		atNum[i] = 0;
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPlayer(void)
{
	if (g_Load == FALSE) return;

	name[0][0] = '0';
	name[1][0] = '0';
	// 頂点バッファの解放
	if (g_VertexBuffer)
	{
		g_VertexBuffer->Release();
		g_VertexBuffer = NULL;
	}


	for (int i = 0; i < MAX_PLAYER; i++)
	{
		// モデルの解放処理
		if (g_Player[i].load)
		{
			UnloadModel(&g_Player[i].model);
			g_Player[i].load = FALSE;
		}
	}
	for (int i = 0; i < MAX_PLAYER_PARTS; i++)
	{
		// モデルの解放処理
		if (g_Player[i].load)
		{
			UnloadModel(&g_Parts[i].model);
			g_Parts[i].load = FALSE;
		}
	}
	g_Load = FALSE;
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePlayer(void)
{
	for (int i = 0; i < MAX_PLAYER; i++)
	{
		if (g_Player[i].use != TRUE)continue;

			ControlPlayer();
			MovePlayer();
			ControlChangeArm();

			XMFLOAT3 pos;
			const float dist = 20.0f;
			pos.x = sinf(g_Player[0].rot.y - XM_PI * 0.25f)*dist;
			pos.z = cosf(g_Player[0].rot.y + XM_PI * 0.25f)*dist;
			g_PlayerArm[0]->pos = { g_Player[0].pos.x + pos.x, g_Player[0].pos.y, g_Player[0].pos.z + pos.z };
			g_PlayerArm[1]->pos = { g_Player[0].pos.x + pos.x, g_Player[0].pos.y, g_Player[0].pos.z + pos.z };

			g_Player[i].spd *= 0.7f;
			g_Player[i].moveVec.x *= 0.8f;
			g_Player[i].moveVec.z *= 0.8f;

			for (int k = 0; k < MAX_PLAYER_PARTS; k++)
			{
				PlayerPartsIP(&g_Parts[k]);
			}
			UpdateArm();
	}
#ifdef _DEBUG
	PrintDebugProc("プレイヤー座標X:%f, Z:%f\n", g_Player[0].pos.x, g_Player[0].pos.z);
	PrintDebugProc("プレイヤーアーム:%d\n", g_Player[0].armType);

#endif
}


//=============================================================================
// 描画処理
//=============================================================================
void DrawPlayer(void)
{
	// カリング無効
	SetCullingMode(CULL_MODE_NONE);

	XMMATRIX mtxScl, mtxRot, mtxTranslate, mtxWorld;

	for (int i = 0; i < MAX_PLAYER; i++)
	{
		if (g_Player[i].use != TRUE)continue;
		// ワールドマトリックスの初期化
		mtxWorld = XMMatrixIdentity();

		// スケールを反映
		mtxScl = XMMatrixScaling(g_Player[i].scl.x + g_Playerline[i].scl.x, g_Player[i].scl.y + g_Playerline[i].scl.y, g_Player[i].scl.z + g_Playerline[i].scl.z);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxScl);

		// 回転を反映
		mtxRot = XMMatrixRotationRollPitchYaw(g_Player[i].rot.x + g_Playerline[i].rot.x, g_Player[i].rot.y - XM_PI * 0.5f + g_Playerline[i].rot.y, g_Player[i].rot.z + g_Playerline[i].rot.z);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxRot);

		// 移動を反映
		mtxTranslate = XMMatrixTranslation(g_Player[i].pos.x + g_Playerline[i].pos.x, g_Player[i].pos.y + g_Playerline[i].pos.y, g_Player[i].pos.z + g_Playerline[i].pos.z);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxTranslate);

		// ワールドマトリックスの設定
		SetWorldMatrix(&mtxWorld);

		XMStoreFloat4x4(&g_Player[i].mtxWorld, mtxWorld);

		// モデル描画
		DrawModel(&g_Player[i].model);

		if (g_Player[i].partsNum == 0)continue;

		// パーツの階層アニメーション
		for (int k = g_Player[i].startNum; k < g_Player[i].startNum + g_Player[i].partsNum; k++)
		{
			// ワールドマトリックスの初期化
			mtxWorld = XMMatrixIdentity();

			// スケールを反映
			mtxScl = XMMatrixScaling(g_Parts[k].scl.x, g_Parts[k].scl.y, g_Parts[k].scl.z);
			mtxWorld = XMMatrixMultiply(mtxWorld, mtxScl);

			// 回転を反映
			mtxRot = XMMatrixRotationRollPitchYaw(g_Parts[k].rot.x, g_Parts[k].rot.y, g_Parts[k].rot.z);
			mtxWorld = XMMatrixMultiply(mtxWorld, mtxRot);

			// 移動を反映
			mtxTranslate = XMMatrixTranslation(g_Parts[k].pos.x, g_Parts[k].pos.y, g_Parts[k].pos.z);
			mtxWorld = XMMatrixMultiply(mtxWorld, mtxTranslate);

			if (g_Parts[k].parent != NULL)	// 子供だったら親と結合する
			{
				mtxWorld = XMMatrixMultiply(mtxWorld, XMLoadFloat4x4(&g_Parts[k].parent->mtxWorld));
				// ↑
				// g_Player[i].mtxWorldを指している
			}

			XMStoreFloat4x4(&g_Parts[k].mtxWorld, mtxWorld);

			// 使われているなら処理する。ここまで処理している理由は他のパーツがこのパーツを参照している可能性があるから。
			if (g_Parts[k].load == FALSE) continue;

			// ワールドマトリックスの設定
			SetWorldMatrix(&mtxWorld);

			// モデル描画
			DrawModel(&g_Parts[k].model);
		}
		//アームモデル描画
		g_Arm[0]->Draw();		
	}

	// カリング設定を戻す
	SetCullingMode(CULL_MODE_BACK);
}

//待機ﾓｰｼｮﾝ処理
void PlayerStandLiner(int i)
{
	if (g_Player[i].tbl_adrM == NULL)return;	// 線形補間を実行する？

//
// 線形補間の処理
// 移動処理
	int		index = (int)g_Player[i].move_time;
	float	time = g_Player[i].move_time - index;
	int		size = g_Player[i].tbl_sizeM;

	float dt = 1.0f / g_Player[i].tbl_adrM[index].frame;	// 1フレームで進める時間
	g_Player[i].move_time += dt;							// アニメーションの合計時間に足す

	if (index > (size - 2))	// ゴールをオーバーしていたら、データを最初に戻して攻撃を終了
	{
		g_Player[i].move_time = 0.0f;
		index = 0;
		g_Playerline[i].pos = { 0.0f, 0.0f, 0.0f };
		g_Playerline[i].rot = { 0.0f, 0.0f, 0.0f };
		g_Playerline[i].scl = { 0.0f, 0.0f, 0.0f };
	}

	// 座標を求める	X = StartX + (EndX - StartX) * 今の時間
	XMVECTOR p1 = XMLoadFloat3(&g_Player[i].tbl_adrM[index + 1].pos);	// 次の場所
	XMVECTOR p0 = XMLoadFloat3(&g_Player[i].tbl_adrM[index + 0].pos);	// 現在の場所
	XMVECTOR vec = p1 - p0;
	XMStoreFloat3(&g_Playerline[i].pos, p0 + vec * time);

	// 回転を求める	R = StartX + (EndX - StartX) * 今の時間
	XMVECTOR r1 = XMLoadFloat3(&g_Player[i].tbl_adrM[index + 1].rot);	// 次の角度
	XMVECTOR r0 = XMLoadFloat3(&g_Player[i].tbl_adrM[index + 0].rot);	// 現在の角度
	XMVECTOR rot = r1 - r0;
	XMStoreFloat3(&g_Playerline[i].rot, r0 + rot * time);

	// scaleを求める S = StartX + (EndX - StartX) * 今の時間
	XMVECTOR s1 = XMLoadFloat3(&g_Player[i].tbl_adrM[index + 1].scl);	// 次のScale
	XMVECTOR s0 = XMLoadFloat3(&g_Player[i].tbl_adrM[index + 0].scl);	// 現在のScale
	XMVECTOR scl = s1 - s0;
	XMStoreFloat3(&g_Playerline[i].scl, s0 + scl * time);

	for (int k = g_Player[i].startNum; k < g_Player[i].startNum + g_Player[i].partsNum; k++)
	{
		if (g_Parts[k].tbl_adrM == NULL)continue;;	// 線形補間を実行する？

		int		index = (int)g_Parts[k].move_time;
		float	time = g_Parts[k].move_time - index;
		int		size = g_Parts[k].tbl_sizeM;

		float dt = 1.0f / g_Parts[k].tbl_adrM[index].frame;	// 1フレームで進める時間
		g_Parts[k].move_time += dt;							// アニメーションの合計時間に足す

		if (index > (size - 2))	// ゴールをオーバーしていたら、データを最初に戻して攻撃を終了
		{
			g_Parts[k].move_time = 0.0f;
			index = 0;
		}

		// 座標を求める	X = StartX + (EndX - StartX) * 今の時間
		XMVECTOR p1 = XMLoadFloat3(&g_Parts[k].tbl_adrM[index + 1].pos);	// 次の場所
		XMVECTOR p0 = XMLoadFloat3(&g_Parts[k].tbl_adrM[index + 0].pos);	// 現在の場所
		XMVECTOR vec = p1 - p0;
		XMStoreFloat3(&g_Parts[k].pos, p0 + vec * time);

		// 回転を求める	R = StartX + (EndX - StartX) * 今の時間
		XMVECTOR r1 = XMLoadFloat3(&g_Parts[k].tbl_adrM[index + 1].rot);	// 次の角度
		XMVECTOR r0 = XMLoadFloat3(&g_Parts[k].tbl_adrM[index + 0].rot);	// 現在の角度
		XMVECTOR rot = r1 - r0;
		XMStoreFloat3(&g_Parts[k].rot, r0 + rot * time);

		// scaleを求める S = StartX + (EndX - StartX) * 今の時間
		XMVECTOR s1 = XMLoadFloat3(&g_Parts[k].tbl_adrM[index + 1].scl);	// 次のScale
		XMVECTOR s0 = XMLoadFloat3(&g_Parts[k].tbl_adrM[index + 0].scl);	// 現在のScale
		XMVECTOR scl = s1 - s0;
		XMStoreFloat3(&g_Parts[k].scl, s0 + scl * time);
	}
}

//プレイヤーの線形補間
void PlayerPartsIP(PLAYER* p)
{
	if (p->tbl_adrM == NULL)return;
	//
	// 線形補間の処理
	// 移動処理
	int		index = (int)p->move_time;
	float	time = p->move_time - index;
	int		size = p->tbl_sizeM;

	float dt = 1.0f / p->tbl_adrM[index].frame;	// 1フレームで進める時間
	p->move_time += dt;							// アニメーションの合計時間に足す

	if (index > (size - 2))	// ゴールをオーバーしていたら、データを最初に戻して攻撃を終了
	{
		p->move_time = 0.0f;
		index = 0;
	}
	// 座標を求める	X = StartX + (EndX - StartX) * 今の時間
	XMVECTOR p1 = XMLoadFloat3(&p->tbl_adrM[index + 1].pos);	// 次の場所
	XMVECTOR p0 = XMLoadFloat3(&p->tbl_adrM[index + 0].pos);	// 現在の場所
	XMVECTOR vec = p1 - p0;
	XMStoreFloat3(&p->pos, p0 + vec * time);

	// 回転を求める	R = StartX + (EndX - StartX) * 今の時間
	XMVECTOR r1 = XMLoadFloat3(&p->tbl_adrM[index + 1].rot);	// 次の角度
	XMVECTOR r0 = XMLoadFloat3(&p->tbl_adrM[index + 0].rot);	// 現在の角度
	XMVECTOR rot = r1 - r0;
	XMStoreFloat3(&p->rot, r0 + rot * time);

	// scaleを求める S = StartX + (EndX - StartX) * 今の時間
	XMVECTOR s1 = XMLoadFloat3(&p->tbl_adrM[index + 1].scl);	// 次のScale
	XMVECTOR s0 = XMLoadFloat3(&p->tbl_adrM[index + 0].scl);	// 現在のScale
	XMVECTOR scl = s1 - s0;
	XMStoreFloat3(&p->scl, s0 + scl * time);
}


//=============================================================================
// プレイヤー情報を取得
//=============================================================================
PLAYER *GetPlayer(void)
{
	return &g_Player[0];
}


void MovePlayer(void)
{
	CAMERA *cam = GetCamera();
	float old_x = g_Player[0].pos.x;
	float old_z = g_Player[0].pos.z;
	// Key入力があったら移動処理する
	if (g_Player[0].spd > 0.0f)
	{
		float angle = atan2f(g_Player[0].moveVec.x, g_Player[0].moveVec.z);
		g_Player[0].rot.y = angle;
	}
	//移動値をベクトル変換して移動させる
	XMVECTOR moveVec = XMLoadFloat3(&g_Player[0].moveVec);
	XMVECTOR now = XMLoadFloat3(&g_Player[0].pos);								// 現在の場所
	XMStoreFloat3(&g_Player[0].pos, now + XMVector3Normalize(moveVec) * g_Player[0].spd);	//単位ベクトルを元に移動
	MeshWallHit(g_Player[0].pos, 10.0f, old_x, old_z);

}
void ControlPlayer(void)
{
	CAMERA *cam = GetCamera();
	float changeRotCamera = 0.025f; //傾く速度
	// 移動ボタン
	if (IsButtonPressed(0, BUTTON_LEFT) || GetKeyboardPress(DIK_A))
	{	// 左へ移動
		g_Player[0].spd = VALUE_MOVE;
		g_Player[0].moveVec.x -= cosf(cam->rot.y) * changeRotCamera;
		g_Player[0].moveVec.z += sinf(cam->rot.y) * changeRotCamera;
	}
	if (IsButtonPressed(0, BUTTON_RIGHT) || GetKeyboardPress(DIK_D))
	{	// 右へ移動
		g_Player[0].spd = VALUE_MOVE;
		g_Player[0].moveVec.x += cosf(cam->rot.y) * changeRotCamera;
		g_Player[0].moveVec.z -= sinf(cam->rot.y) * changeRotCamera;
	}
	if (IsButtonPressed(0, BUTTON_UP) || GetKeyboardPress(DIK_W))
	{	// 上へ移動
		g_Player[0].spd = VALUE_MOVE;
		g_Player[0].moveVec.x += sinf(cam->rot.y) * changeRotCamera;
		g_Player[0].moveVec.z += cosf(cam->rot.y) * changeRotCamera;
	}
	if (IsButtonPressed(0, BUTTON_DOWN) || GetKeyboardPress(DIK_S))
	{	// 下へ移動
		g_Player[0].spd = VALUE_MOVE;
		g_Player[0].moveVec.x -= sinf(cam->rot.y) * changeRotCamera;
		g_Player[0].moveVec.z -= cosf(cam->rot.y) * changeRotCamera;
	}
}

void ControlChangeArm(void)
{
	if (GetKeyboardTrigger(DIK_F))
	{
		ChangePlayerArm(TRUE);
	}
	else if (GetKeyboardTrigger(DIK_G))
	{
		ChangePlayerArm(FALSE);
	}
}
//初期化段階でのアームセット
void SetPlayerArm(void)
{
	g_PlayerArm[0] = Xgun::GetArm();
	g_PlayerArm[1] = Braster::GetArm();
	g_PlayerArm[2] = Saw::GetArm();
}

//アームの切り替え
void ChangePlayerArm(BOOL flag)
{
	if (flag)
	{
		g_Player[0].armType++;
		if (g_Player[0].armType >= ARM_VAR)
			g_Player[0].armType = 0;
	}
	else
	{
		g_Player[0].armType--;
		if (g_Player[0].armType < 0)
			g_Player[0].armType = ARM_VAR - 1;
	}
}

void UpdateArm(void)
{
	pArm::UpdateArm();
	if (GetKeyboardTrigger(DIK_1))
	{
		switch (g_Player[0].armType)
		{
		case 0:
			Xgun::Action();
			break;
		case 1:
			break;
		case 2:
			break;

		}
	}
}

HRESULT MakeVertexPlayerVar(void)
{
	// 頂点バッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	GetDevice()->CreateBuffer(&bd, NULL, &g_VertexBuffer);


	{//頂点バッファの中身を埋める
		D3D11_MAPPED_SUBRESOURCE msr;
		GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

		VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

		// 頂点座標の設定
		vertex[0].Position = XMFLOAT3(-VAR_WIDTH / 2, 0.0f, VAR_HEIGHT / 2);
		vertex[1].Position = XMFLOAT3(VAR_WIDTH / 2, 0.0f, VAR_HEIGHT / 2);
		vertex[2].Position = XMFLOAT3(-VAR_WIDTH / 2, 0.0f, -VAR_HEIGHT / 2);
		vertex[3].Position = XMFLOAT3(VAR_WIDTH / 2, 0.0f, -VAR_HEIGHT / 2);

		// 法線の設定
		vertex[0].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
		vertex[1].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
		vertex[2].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
		vertex[3].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);

		// 拡散光の設定
		vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

		// テクスチャ座標の設定
		vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);
		vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);
		vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);
		vertex[3].TexCoord = XMFLOAT2(1.0f, 1.0f);

		GetDeviceContext()->Unmap(g_VertexBuffer, 0);
	}

	return S_OK;
}
