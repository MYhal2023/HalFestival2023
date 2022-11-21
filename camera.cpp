//=============================================================================
//
// カメラ処理 [camera.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "camera.h"
#include "game.h"
#include "player.h"
#include "time.h"
#include "debugproc.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
//#define	POS_X_CAM		(0.0f)			// カメラの初期位置(X座標)
//#define	POS_Y_CAM		(200.0f)		// カメラの初期位置(Y座標)
//#define	POS_Z_CAM		(-400.0f)		// カメラの初期位置(Z座標)


#define	VIEW_ANGLE		(XMConvertToRadians(45.0f))						// ビュー平面の視野角
#define	VIEW_ASPECT		((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT)	// ビュー平面のアスペクト比	
#define	VIEW_NEAR_Z		(10.0f)											// ビュー平面のNearZ値
#define	VIEW_FAR_Z		(10000.0f)										// ビュー平面のFarZ値


typedef enum
{
	RUN,
	BETWEEN,
	WALK
}CAMERA_PHASE;
//*****************************************************************************
// グローバル変数
//*****************************************************************************
static CAMERA			g_Cam;		// カメラデータ

static int				g_ViewPortType = TYPE_FULL_SCREEN;
//=============================================================================
// 初期化処理
//=============================================================================
void InitCamera(void)
{
	g_Cam.pos = { 0.0f, 80.0f, 350.0f };
	g_Cam.at = { 0.0f, 0.0f, 0.0f };
	g_Cam.atPos = { 0.0f, 0.0f, 0.0f };
	g_Cam.up  = { 0.0f, 1.0f, 0.0f };
	g_Cam.rot = { 0.0f, 0.0f, 0.0f };

	// 視点と注視点の距離を計算
	float vx, vz;
	vx = g_Cam.pos.x - g_Cam.at.x;
	vz = g_Cam.pos.z - g_Cam.at.z;
	g_Cam.len = sqrtf(vx * vx + vz * vz);
	
	g_Cam.tbl_adr = NULL;		// 再生するアニメデータの先頭アドレスをセット
	g_Cam.move_time = 0.0f;	// 線形補間用のタイマーをクリア
	g_Cam.tbl_size = NULL;		// 再生するアニメデータのレコード数をセット

	// ビューポートタイプの初期化
	g_ViewPortType = TYPE_FULL_SCREEN;
}


//=============================================================================
// カメラの終了処理
//=============================================================================
void UninitCamera(void)
{

}


//=============================================================================
// カメラの更新処理
//=============================================================================
void UpdateCamera(void)
{
	XMFLOAT3 pos, pos2;
	PLAYER *player = GetPlayer();
	pos2 = player[0].pos;
	const float dist = -30.0f;
	pos.x = pos2.x + sinf(g_Cam.rot.y)*dist;
	pos.y =pos2.y + 30.0f;
	pos.z = pos2.z + cosf(g_Cam.rot.y)*dist;
	g_Cam.pos = pos;
#ifdef _DEBUG	//デバッグ用のカメラ操作。モード関係なく動かせる
	if (GetKeyboardPress(DIK_Q))
	{
		g_Cam.rot.y -= VALUE_ROTATE_CAMERA;
		if (g_Cam.rot.y < -XM_PI)
		{
			g_Cam.rot.y += XM_PI * 2.0f;
		}
	}
	else if (GetKeyboardPress(DIK_E))
	{
		g_Cam.rot.y += VALUE_ROTATE_CAMERA;
		if (g_Cam.rot.y > XM_PI)
		{
			g_Cam.rot.y -= XM_PI * 2.0f;
		}

	}
	if (GetKeyboardPress(DIK_UP))
	{
		if (g_Cam.rot.x < XM_PI * 0.2f)
			g_Cam.rot.x += XM_PI * 0.004f;
	}
	else if (GetKeyboardPress(DIK_DOWN))
	{
		if (g_Cam.rot.x > 0.0f)
			g_Cam.rot.x -= XM_PI * 0.004f;
	}


#endif

	if (g_Cam.tbl_adr != NULL)
	{
		// 移動処理
		int		index = (int)g_Cam.move_time;
		float	time = g_Cam.move_time - index;
		int		size = g_Cam.tbl_size;

		float dt = 1.0f / g_Cam.tbl_adr[index].frame;	// 1フレームで進める時間
		g_Cam.move_time += dt;							// アニメーションの合計時間に足す

		if (index > (size - 2))	// ゴールをオーバーしていたら、最初へ戻す。線形補間データを消去
		{
			g_Cam.move_time = 0.0f;
			index = 0;
			g_Cam.tbl_adr = NULL;
			return;
		}

		// 座標を求める	X = StartX + (EndX - StartX) * 今の時間
		XMVECTOR p1 = XMLoadFloat3(&g_Cam.tbl_adr[index + 1].pos);	// 次の場所
		XMVECTOR p0 = XMLoadFloat3(&g_Cam.tbl_adr[index + 0].pos);	// 現在の場所
		XMVECTOR vec = p1 - p0;
		XMStoreFloat3(&g_Cam.pos, p0 + vec * time);

		// 回転を求める	R = StartX + (EndX - StartX) * 今の時間
		XMVECTOR r1 = XMLoadFloat3(&g_Cam.tbl_adr[index + 1].rot);	// 次の角度
		XMVECTOR r0 = XMLoadFloat3(&g_Cam.tbl_adr[index + 0].rot);	// 現在の角度
		XMVECTOR rot = r1 - r0;
		XMStoreFloat3(&g_Cam.rot, r0 + rot * time);

		// 注視点の変更量を求める S = StartX + (EndX - StartX) * 今の時間
		XMVECTOR s1 = XMLoadFloat3(&g_Cam.tbl_adr[index + 1].scl);	// 次の注視点
		XMVECTOR s0 = XMLoadFloat3(&g_Cam.tbl_adr[index + 0].scl);	// 現在の注視点
		XMVECTOR scl = s1 - s0;
		XMStoreFloat3(&g_Cam.atPos, s0 + scl * time);

	}
#ifdef _DEBUG

	PrintDebugProc("\nカメラ回転y:%f,x:%f\n", g_Cam.rot.y, g_Cam.rot.x);
#endif

}


//=============================================================================
// カメラの更新
//=============================================================================
void SetCamera(void) 
{
	// ビューマトリックス設定
	XMMATRIX mtxView;
	mtxView = XMMatrixLookAtLH(XMLoadFloat3(&g_Cam.pos), XMLoadFloat3(&g_Cam.at), XMLoadFloat3(&g_Cam.up));
	SetViewMatrix(&mtxView);
	XMStoreFloat4x4(&g_Cam.mtxView, mtxView);

	XMMATRIX mtxInvView;
	mtxInvView = XMMatrixInverse(nullptr, mtxView);
	XMStoreFloat4x4(&g_Cam.mtxInvView, mtxInvView);


	// プロジェクションマトリックス設定
	XMMATRIX mtxProjection;
	mtxProjection = XMMatrixPerspectiveFovLH(VIEW_ANGLE, VIEW_ASPECT, VIEW_NEAR_Z, VIEW_FAR_Z);

	SetProjectionMatrix(&mtxProjection);
	XMStoreFloat4x4(&g_Cam.mtxProjection, mtxProjection);

	SetShaderCamera(g_Cam.pos);
}


//=============================================================================
// カメラの取得
//=============================================================================
CAMERA *GetCamera(void) 
{
	return &g_Cam;
}

//=============================================================================
// ビューポートの設定
//=============================================================================
void SetViewPort(int type)
{
	//ID3D11DeviceContext *g_ImmediateContext = GetDeviceContext();
	//D3D11_VIEWPORT vp;

	//g_ViewPortType = type;

	//// ビューポート設定
	//switch (g_ViewPortType)
	//{
	//case TYPE_FULL_SCREEN:
	//case TYPE_LIGHT_SCREEN:
	//	vp.Width = (FLOAT)SCREEN_WIDTH;
	//	vp.Height = (FLOAT)SCREEN_HEIGHT;
	//	vp.MinDepth = 0.0f;
	//	vp.MaxDepth = 1.0f;
	//	vp.TopLeftX = 0;
	//	vp.TopLeftY = 0;
	//	break;

	//case TYPE_LEFT_HALF_SCREEN:
	//	vp.Width = (FLOAT)SCREEN_WIDTH / 2;
	//	vp.Height = (FLOAT)SCREEN_HEIGHT;
	//	vp.MinDepth = 0.0f;
	//	vp.MaxDepth = 1.0f;
	//	vp.TopLeftX = 0;
	//	vp.TopLeftY = 0;
	//	break;

	//case TYPE_RIGHT_HALF_SCREEN:
	//	vp.Width = (FLOAT)SCREEN_WIDTH / 2;
	//	vp.Height = (FLOAT)SCREEN_HEIGHT;
	//	vp.MinDepth = 0.0f;
	//	vp.MaxDepth = 1.0f;
	//	vp.TopLeftX = (FLOAT)SCREEN_WIDTH / 2;
	//	vp.TopLeftY = 0;
	//	break;

	//case TYPE_UP_HALF_SCREEN:
	//	vp.Width = (FLOAT)SCREEN_WIDTH;
	//	vp.Height = (FLOAT)SCREEN_HEIGHT / 2;
	//	vp.MinDepth = 0.0f;
	//	vp.MaxDepth = 1.0f;
	//	vp.TopLeftX = 0;
	//	vp.TopLeftY = 0;
	//	break;

	//case TYPE_DOWN_HALF_SCREEN:
	//	vp.Width = (FLOAT)SCREEN_WIDTH;
	//	vp.Height = (FLOAT)SCREEN_HEIGHT / 2;
	//	vp.MinDepth = 0.0f;
	//	vp.MaxDepth = 1.0f;
	//	vp.TopLeftX = 0;
	//	vp.TopLeftY = (FLOAT)SCREEN_HEIGHT / 2;
	//	break;

	//}
	//g_ImmediateContext->RSSetViewports(1, &vp);

}


int GetViewPortType(void)
{
	return g_ViewPortType;
}


// カメラの視点と注視点セット
void SetCameraAT(XMFLOAT3 pos)
{
	XMVECTOR v1 = XMLoadFloat3(&pos) - XMLoadFloat3(&g_Cam.at);
	XMVECTOR nor = XMVector3Normalize(v1);
	XMStoreFloat3(&g_Cam.at, XMLoadFloat3(&g_Cam.at) + nor * 1.0f);

	//引数の座標に変更量を加算。
	pos.x += g_Cam.atPos.x;
	pos.y += g_Cam.atPos.y;
	pos.z += g_Cam.atPos.z;
	// カメラの注視点をセット
	pos.y += sinf(g_Cam.rot.x) * g_Cam.len;
	g_Cam.at = { pos.x,pos.y,pos.z };
	float dist = FloatClamp(1.0f - sinf(g_Cam.rot.x), 0.98f, 1.0f);
	// カメラの視点をカメラのY軸回転に対応させている
	g_Cam.pos.x = g_Cam.at.x - sinf(g_Cam.rot.y) * g_Cam.len;
	g_Cam.pos.z = g_Cam.at.z - cosf(g_Cam.rot.y) * g_Cam.len;
	g_Cam.pos.y -= sinf(g_Cam.rot.x)* g_Cam.len * (sinf(g_Cam.rot.x) * 0.75f);
}
