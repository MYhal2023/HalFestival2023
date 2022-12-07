//=============================================================================
//
// ゲーム画面処理 [game.h]
// Author : 
//
//=============================================================================
#pragma once
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	FIELD_X				(80)	// X軸方向のブロック数
#define	FIELD_Z				(40)	// Z軸方向のブロック数
#define	FIELD001_X				(50)	// X軸方向のブロック数
#define	FIELD001_Z				(50)	// Z軸方向のブロック数
#define	BLOCK_SIZE			(50.0f)	// ブロックサイズ
#define	FIELD_X_LIMIT		(FIELD_X * BLOCK_SIZE * 0.5f)	// X軸方向の限界座標
#define	FIELD_Z_LIMIT		(FIELD_Z * BLOCK_SIZE * 0.5f)	// Z軸方向の限界座標
#define	FIELD001_X_LIMIT	(FIELD001_X * BLOCK_SIZE * 0.5f)	// X軸方向の限界座標
#define	FIELD001_Z_LIMIT	(FIELD001_Z * BLOCK_SIZE * 0.5f)	// Z軸方向の限界座標
#define	WAVE_POS_Y			(-20.0f)	// 波が発生している為、壁を少し下げる

#define	WALL_Y				(1)	// メッシュ壁の縦枚数
#define	WALL_XZ				(1)	// メッシュ壁の横枚数
#define	WALL_BLOCK_SIZE_Y	(360)	// ブロックサイズ縦
#define	WALL_BLOCK_SIZE_XZ	(FIELD_X_LIMIT * 2.0f)	// ブロックサイズ横
#define	SCORE_COIN				(100)	// X軸方向のブロック数
#define	SCORE_TIMECENT			(10)	// X軸方向のブロック数
#define	SCORE_BEAT				(50)	// X軸方向のブロック数
#define	ADD_TIME				(5)	// X軸方向のブロック数

enum
{
	TITLE_NON,
	MAIN_GAME,
	RESULT
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitGame(void);
void InitSystem(void);
void InitBoot(void);
void InitMap(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);
void DrawGame0(void);
void DrawGame1(void);
void SetPlayMode(int playMode);
void DrawGameTitle(void);
void DrawGameResult(void);
void DrawGameReserve(void);
int GetPlayMode(void);
void SetSlowMode(BOOL flag);
//void SetPlayStage(int stageNum);
//int GetPlayStage(void);
void SetViewPortType(int viewport);
int GetViewPortTypeGame(void);
float FloatClamp(float x, float a, float b);
float FloatCompare(BOOL flag, float a, float b);
BOOL CheckGameover(void);
int DamageFunc(int attacker, int diffender);
BOOL GetSpeedMode(void);
int GetSetTime(void);