//=============================================================================
//
// ライト処理 [light.h]
// Author : 
//
//=============================================================================
#pragma once


//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define GAME_FOG_ST (100.0f)
#define GAME_FOG_ED (1500.0f)
#define GAME_LFOG_ST (100.0f)
#define GAME_LFOG_ED (300.0f)
#define DEBUG_FOG_ST (1000.0f)
#define DEBUG_FOG_ED (1100.0f)

#define LIGHT_LINE_ON (300.0f)
#define LIGHT_LINE_OFF (150.0f)

enum
{
	MORNING,
	EVE,
	NIGHT,
	TYPE_NON
};
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitLight(void);
void UpdateLight(void);

void SetLightData(int index, LIGHT *light);
void SetFogData(FOG *fog);
LIGHT *GetLightData(int index);
void UpdateFog(void);