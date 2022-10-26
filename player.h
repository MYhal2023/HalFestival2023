//=============================================================================
//
// ���f������ [player.h]
// Author : 
//
//=============================================================================
#pragma once
#define PLAYER_H_
#include "unitdata.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MODEL_PLAYER		"data/MODEL/dendritic_cells.obj"			// �ǂݍ��ރ��f����
#define	MODEL_NEUTROPHILS	"data/MODEL/neutrophils.obj"			// �ǂݍ��ރ��f����
#define	MODEL_BODY			"data/MODEL/mune_notpaint.obj"			// �ǂݍ��ރ��f����
#define	MODEL_HEAD			"data/MODEL/atama_notpaint.obj"			// �ǂݍ��ރ��f����
#define	MODEL_LEG			"data/MODEL/ashi_notpaint.obj"			// �ǂݍ��ރ��f����

#define MAX_PLAYER		(10)					// �v���C���[�̐�
#define MAX_TARGET		(10)					// �v���C���[�̐�
#define MAX_PLAYER_PARTS (MAX_PLAYER * 2)

#define	PLAYER_SIZE		(70.0f)				// �����蔻��̑傫��
#define	HelperT_SIZE		(300.0f)				// �����蔻��̑傫��
#define	NK_SIZE		(200.0f)				// �����蔻��̑傫��

enum PLAYER_STATE
{
	Standby,	//�ҋ@��
	Deffend,	//�}����
	Skill,		//�X�L���g�p��
};

enum SKILL_TYPE
{
	neutro_skill,	//�D�����̃X�L��
	macro_skill,	//�}�N���t�@�[�W�̃X�L��
	helperT_skill,
	killerT_skill,
	NK_skill,
	kouen_skill,
	skill_max,		//�X�L���ő吔
};
//*****************************************************************************
// �\���̒�`
//*****************************************************************************
class PLAYER:public Unit
{
public:
	XMFLOAT3		moveVec;
	// �K�w�A�j���[�V�����p�̃����o�[�ϐ�
	PLAYER				*parent;	// �������e�Ȃ�NULL�A�������q���Ȃ�e��enemy�A�h���X

	float				spd;

};

//�v���C���[�̐��`��ԃf�[�^��ۑ�
class Playerliner
{
public:
	XMFLOAT3			pos;		// �|���S���̈ʒu
	XMFLOAT3			rot;		// �|���S���̌���(��])
	XMFLOAT3			scl;		// �|���S���̑傫��(�X�P�[��)
};

struct PlayerParts
{
	XMFLOAT3			pos;		// �|���S���̈ʒu
	XMFLOAT3			rot;		// �|���S���̌���(��])
	XMFLOAT3			scl;		// �|���S���̑傫��(�X�P�[��)

	XMFLOAT4X4			mtxWorld;	// ���[���h�}�g���b�N�X

	BOOL				load;
	BOOL				use;
	DX11_MODEL			model;		// ���f�����
	XMFLOAT4			diffuse[MODEL_MAX_MATERIAL];	// ���f���̐F
	// �K�w�A�j���[�V�����p�̃����o�[�ϐ�
	INTERPOLATION_DATA	*tbl_adrA;	// �A�j���f�[�^�̃e�[�u���擪�A�h���X
	int					tbl_sizeA;	// �o�^�����e�[�u���̃��R�[�h����
	INTERPOLATION_DATA	*tbl_adrM;	// �A�j���f�[�^�̃e�[�u���擪�A�h���X
	int					tbl_sizeM;	// �o�^�����e�[�u���̃��R�[�h����
	float				move_time;	// ���s����
	PLAYER				*parent;	// �������e�Ȃ�NULL�A�������q���Ȃ�e��enemy�A�h���X
};

struct PLAYER_VAR
{
	XMFLOAT3			pos;		// �|���S���̈ʒu
	XMFLOAT3			rot;		// �|���S���̌���(��])
	XMFLOAT3			scl;		// �|���S���̑傫��(�X�P�[��)

	XMFLOAT4X4			mtxWorld;	// ���[���h�}�g���b�N�X
	MATERIAL			material;
	float				pardiff;	//�ǂݎ�点��ق��̕ϐ�
	float				parpolar;	//���Z���Ă��ق��̕ϐ�
	BOOL				load;
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void AttackChar(int i);
void DrawPlayer(void);
void MovePlayer(void);
void ControlPlayer(void);
void ControlChangeArm(void);
void SetPlayerArm(void);
void ChangePlayerArm(BOOL flag);
PLAYER *GetPlayer(void);
PlayerParts *GetPlayerParts(void);
void PlayerStandLiner(int i);
void PlayerInterPoration(int i);
int GetPlayerPartsNum(void);
void SetPlayerPartsNum(int s);
HRESULT MakeVertexPlayerVar(void);
