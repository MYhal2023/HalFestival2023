//=============================================================================
//
// スコア処理 [time.h]
// Author : 
//
//=============================================================================
#pragma once


//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TIME_MAX			(3599)		// 制限時間の最大値59分59秒
#define TIME_DIGIT			(5)			// 桁数
#define GAME_TIME			(120)
enum
{
	NUMBER,
	CENT,
};
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitTime(void);
void UninitTime(void);
void UpdateTime(void);
void DrawTime(void);

void RemoveTime(int remove);
void AddTime(int add);
int GetTime(void);


