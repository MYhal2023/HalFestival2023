//=============================================================================
//
// 炎エフェクト処理 [fire.h]
// Author : 
//
//=============================================================================
#pragma once
#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TIME_MAX			(3599)		// 制限時間の最大値59分59秒
#define MAX_FIRE_EFFECT			(400)			// 最大数
#define GAME_TIME			(120)

class FireEffect
{
public:
	XMFLOAT3		scale;			// スケール
	XMFLOAT3 pos;
	XMFLOAT3 rot;
	XMFLOAT2 size;
	int u;
	int v;
	int g_TexNo;
	int interval;
	BOOL use;
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitFire(void);
void UninitFire(void);
void UpdateFire(void);
void DrawFire(void);
FireEffect* SetFireEffect(XMFLOAT3 pos, XMFLOAT3 rot);
void SetFireParticle(XMFLOAT3 pos, float y_rot);
HRESULT MakeVertexFire(void);
FireEffect* GetFireEffect(void);