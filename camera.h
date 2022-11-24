//=============================================================================
//
// �J�������� [camera.h]
// Author : 
//
//=============================================================================
#pragma once


//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "renderer.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	GAME_X_CAM			(0.0f)			// �J�����̏����ʒu(X���W)
#define	GAME_Y_CAM			(50.0f)			// �J�����̏����ʒu(Y���W)
#define	GAME_Z_CAM			(0.0f)		// �J�����̏����ʒu(Z���W)
#define	VALUE_MOVE_CAMERA	(2.0f)										// �J�����̈ړ���
#define	VALUE_ROTATE_CAMERA	(XM_PI * 0.01f)								// �J�����̉�]��




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
// �v���g�^�C�v�錾
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