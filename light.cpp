//=============================================================================
//
// ライト処理 [light.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "renderer.h"
#include "camera.h"
#include "time.h"
#include "light.h"
#include "debugproc.h"
#include "input.h"
#include "game.h"
#include "player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
#define TIME_SEPARATE	(3)		//時間の区切り
#define LIGHT_TYPE		(3)		//時間の区切り
#define CHANGE_ANGLE		(0.0005f)		//時間の区切り

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static LIGHT	g_Light[LIGHT_MAX];

static FOG		g_Fog;
//=============================================================================
// 初期化処理
//=============================================================================
void InitLight(void)
{

	//ライト初期化
	for (int i = 0; i < LIGHT_MAX; i++)
	{
		g_Light[i].Position = XMFLOAT3(150.0f, 500.0f, 100.0f);
		g_Light[i].Direction = XMFLOAT3(1.0f, 1.0f, 1.0f);
		g_Light[i].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		g_Light[i].Ambient = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
		g_Light[i].Attenuation = 100.0f;	// 減衰距離
		g_Light[i].Type = LIGHT_TYPE_NONE;	// ライトのタイプ
		g_Light[i].Enable = FALSE;			// ON / OFF
		SetLight(i, &g_Light[i]);
	}

	// 光源の設定（世界を照らす光）
	g_Light[0].Position = XMFLOAT3(500.0f, 300.0f, 300.0f);
	g_Light[0].Direction = XMFLOAT3(-0.5f, -1.0f, 0.5f);
	float diffuse = 1.0f;
	g_Light[0].Diffuse = XMFLOAT4(1.0f, 0.8f, 0.8f, 1.0f);
	g_Light[0].Type = LIGHT_TYPE_DIRECTIONAL;					// 並行光源
	g_Light[0].Enable = TRUE;									// このライトをON
	SetLight(0, &g_Light[0]);									// これで設定している


	// フォグの初期化（霧の効果）
	g_Fog.FogStart = GAME_FOG_ST;									// 視点からこの距離離れるとフォグがかかり始める
	g_Fog.FogEnd   = GAME_FOG_ED;									// ここまで離れるとフォグの色で見えなくなる
	g_Fog.FogColor = XMFLOAT4( 1.0f, 0.3f, 0.3f, 1.0f );		// フォグの色
	SetFog(&g_Fog);
	SetFogEnable(TRUE);		// 他の場所もチェックする shadow
}




//=============================================================================
// ライトの設定
// Typeによってセットするメンバー変数が変わってくる
//=============================================================================
void SetLightData(int index, LIGHT *light)
{
	SetLight(index, light);
}


LIGHT *GetLightData(int index)
{
	return(&g_Light[index]);
}


//=============================================================================
// フォグの設定
//=============================================================================
void SetFogData(FOG *fog)
{
	SetFog(fog);
}

//ライトの調整
void UpdateLight(void)
{
#ifdef _DEBUG
	if (GetKeyboardPress(DIK_Z))
	{
		g_Light[0].Position.x += 1.0f;
	}
	else if (GetKeyboardPress(DIK_X))
	{
		g_Light[0].Position.x -= 1.0f;
	}
	else if (GetKeyboardPress(DIK_C))
	{
		g_Light[0].Position.z += 1.0f;
	}
	else if (GetKeyboardPress(DIK_V))
	{
		g_Light[0].Position.z -= 1.0f;
	}
	PLAYER *player = GetPlayer();
	g_Light[0].Position.x = player[0].pos.x + 150.0f;
	g_Light[0].Position.z = player[0].pos.z + 100.0f;
	SetLight(0, &g_Light[0]);									// これで設定している
	PrintDebugProc("ライトX:%f、Z:%f", g_Light[0].Position.x, g_Light[0].Position.z);
#endif
}

void UpdateFog(void)
{
//	BOOL debugSW = FALSE;	//デバッグ判断用変数
//#ifdef _DEBUG //デバッグ時のみキーボード操作でフォグを遠くへ
//	if (GetKeyboardTrigger(DIK_H))
//	{
//		g_Fog.FogStart = (g_Fog.FogStart == GAME_FOG_ST) ? DEBUG_FOG_ST : GAME_FOG_ST;
//		g_Fog.FogEnd = (g_Fog.FogEnd == GAME_FOG_ED) ? DEBUG_FOG_ED : GAME_FOG_ED;
//		SetFog(&g_Fog);	//フォグをセット
//	}
//#endif
//	//debugSW変数で、デバッグ中か否かを判断。判断はフォグの開始位置で行う
//	(g_Fog.FogStart == DEBUG_FOG_ST) ? debugSW = TRUE : debugSW = FALSE;
//
//	//デバッグ中のフォグを使用しているなら、リリース版のフォグをスルー
//	if (debugSW == TRUE)return;
//
//	//ライト状態に適さないフォグの場合、状態に合うように再セット
//	if (CheckLightOn() == TRUE && g_Fog.FogStart != GAME_LFOG_ST)
//	{
//		g_Fog.FogStart = GAME_LFOG_ST;
//		g_Fog.FogEnd = GAME_LFOG_ED;
//		SetFog(&g_Fog);	//フォグをセット
//	}
//	else if (CheckLightOn() != TRUE && g_Fog.FogStart == GAME_LFOG_ST)
//	{
//		g_Fog.FogStart = GAME_FOG_ST;
//		g_Fog.FogEnd = GAME_FOG_ED;
//		SetFog(&g_Fog);	//フォグをセット
//	}
}