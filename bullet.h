//=============================================================================
//
// �e���ˏ��� [bullet.h]
// Author : 
//
//=============================================================================
#pragma once
#include "enemy.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_BULLET		(128)	// �e�ő吔

#define	BULLET_WH		(5.0f)	// �����蔻��̑傫��

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	XMFLOAT4X4	mtxWorld;		// ���[���h�}�g���b�N�X
	XMFLOAT3	pos;			// �ʒu
	XMFLOAT3	rot;			// �p�x
	XMFLOAT3	scl;			// �X�P�[��
	MATERIAL	material;		// �}�e���A��
	float		spd;			// �ړ���
	float		fWidth;			// ��
	float		fHeight;		// ����
	int			shadowIdx;		// �eID
	int			life;
	BOOL		use;			// �g�p���Ă��邩�ǂ���
	ENEMY		*enemy;			//�U���Ώ�

} BULLET;


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);

int SetBullet(XMFLOAT3 pos, XMFLOAT3 rot, float scl, ENEMY *enemy);

BULLET *GetBullet(void);

