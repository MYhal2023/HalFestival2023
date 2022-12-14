//=============================================================================
//
// カメラ処理 [camera.h]
// Author : 
//
//=============================================================================
#pragma once


//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "renderer.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	GAME_X_CAM			(0.0f)			// カメラの初期位置(X座標)
#define	GAME_Y_CAM			(50.0f)			// カメラの初期位置(Y座標)
#define	GAME_Z_CAM			(0.0f)		// カメラの初期位置(Z座標)
#define	VALUE_MOVE_CAMERA	(2.0f)										// カメラの移動量
#define	VALUE_ROTATE_CAMERA	(XM_PI * 0.01f)								// カメラの回転量




enum {
	TYPE_FULL_SCREEN,
	TYPE_LEFT_HALF_SCREEN,
	TYPE_RIGHT_HALF_SCREEN,
	TYPE_UP_HALF_SCREEN,
	TYPE_DOWN_HALF_SCREEN,
	TYPE_LIGHT_SCREEN,
	TYPE_NONE,

};


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);
void SetCamera(void);

CAMERA *GetCamera(void);

void SetViewPort(int type);
int GetViewPortType(void);

void SetCameraAT(XMFLOAT3 pos);
void SetCharaCamera(XMFLOAT3 pos);
void SetReserveCameraAT(XMFLOAT3 pos, XMFLOAT3 rot);
void SetVibTime(int time);