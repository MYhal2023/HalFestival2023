//=============================================================================
//
// ���G�t�F�N�g���� [fire.h]
// Author : 
//
//=============================================================================
#pragma once
#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TIME_MAX			(3599)		// �������Ԃ̍ő�l59��59�b
#define MAX_FIRE_EFFECT			(150)			// �ő吔
#define GAME_TIME			(120)

class FireEffect
{
public:
	XMFLOAT3		scale;			// �X�P�[��
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
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitFire(void);
void UninitFire(void);
void UpdateFire(void);
void DrawFire(void);
FireEffect* SetFireEffect(XMFLOAT3 pos, XMFLOAT3 rot);
void SetFireParticle(XMFLOAT3 pos, float y_rot);
HRESULT MakeVertexFire(void);