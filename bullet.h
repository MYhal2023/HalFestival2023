//=============================================================================
//
// �e���ˏ��� [bullet.h]
// Author : 
//
//=============================================================================
#pragma once
#include "model.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_BULLET		(128)	// �e�ő吔

#define	BULLET_WH		(5.0f)	// �����蔻��̑傫��
#define MODEL_BULLET_SAW	"data/MODEL/neutrophils.obj"			// �ǂݍ��ރ��f����

enum BULLET_VAR
{
	Bullet_XGun,
	Bullet_Braster,
	Bullet_Saw,
	MAX_BULLET_VAR
};
//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	DX11_MODEL			model;		// ���f�����
	XMFLOAT4X4	mtxWorld;		// ���[���h�}�g���b�N�X
	XMFLOAT3	pos;			// �ʒu
	XMFLOAT3	rot;			// �p�x
	XMFLOAT3	scl;			// �X�P�[��
	MATERIAL	material;		// �}�e���A��
	float		spd;			// �ړ���
	float		fWidth;			// ��
	float		fHeight;		// ����
	float		size;
	float		attack;			//�U����
	int			shadowIdx;		// �eID
	int			life;
	int			model_num;		//�g�p���郂�f��
	int			p_time;
	BOOL		efSwitch;
	BOOL		use;			// �g�p���Ă��邩�ǂ���

} BULLET;


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitBullet(void);
void InitBulletBoot(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void DrawBulletModel(void);
BULLET *GetBullet(void);
void SetBullet(XMFLOAT3 pos, XMFLOAT3 rot, float spd, float attack, int life, int model_num);
void XgunParticle(XMFLOAT3 pos); 
void BrasterParticle(XMFLOAT3 pos);