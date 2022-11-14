//=============================================================================
//
// ���f������ [player.h]
// Author : 
//
//=============================================================================
#pragma once
#define PLAYER_H_
#include "unitdata.h"
#include "rescueLife.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MODEL_PLAYER		"data/MODEL/dendritic_cells.obj"			// �ǂݍ��ރ��f����
#define	MODEL_NEUTROPHILS	"data/MODEL/neutrophils.obj"			// �ǂݍ��ރ��f����
#define	MODEL_BODY			"data/MODEL/chest.obj"			// �ǂݍ��ރ��f����
#define	MODEL_HEAD			"data/MODEL/head.obj"			// �ǂݍ��ރ��f����
#define	MODEL_R_SHOULDER	"data/MODEL/rightshoulder.obj"			// �ǂݍ��ރ��f����
#define	MODEL_R_ARM			"data/MODEL/rightarm.obj"			// �ǂݍ��ރ��f����
#define	MODEL_L_SHOULDER	"data/MODEL/leftshoulder.obj"			// �ǂݍ��ރ��f����
#define	MODEL_L_ARM			"data/MODEL/leftarm.obj"			// �ǂݍ��ރ��f����
#define	MODEL_R_THIGH		"data/MODEL/rightthigh.obj"			// �ǂݍ��ރ��f����
#define	MODEL_R_FOOT		"data/MODEL/rightleg.obj"			// �ǂݍ��ރ��f����
#define	MODEL_L_THIGH		"data/MODEL/leftthigh.obj"			// �ǂݍ��ރ��f����
#define	MODEL_L_FOOT		"data/MODEL/leftleg.obj"			// �ǂݍ��ރ��f����

#define MAX_PLAYER		(1)					// �v���C���[�̐�
#define MAX_PLAYER_PARTS (9)

#define	PLAYER_SIZE		(30.0f)				// �����蔻��̑傫��
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

enum PLAYER_PARTS
{
	//P_BODY,	//������v���C���[���f���Ƃ���
	P_HEAD,
	P_L_SHOULDER,
	P_R_SHOULDER,
	P_L_ARM,
	P_R_ARM,
	P_L_THIGH,
	P_R_THIGH,
	P_L_FOOT,
	P_R_FOOT,
};
//*****************************************************************************
// �\���̒�`
//*****************************************************************************
class PLAYER:public Unit
{
public:
	XMFLOAT3		moveVec;
	XMFLOAT3		rescueBullet[2];	//���r������
	// �K�w�A�j���[�V�����p�̃����o�[�ϐ�
	PLAYER				*parent;	// �������e�Ȃ�NULL�A�������q���Ȃ�e��enemy�A�h���X

	float				spd;
	int					armType;	//�������̃A�[���^�C�v
	float				motionTime;
	float				n_motionTime;
	float				inv_time;
	float				cntBullet;
	RescueLife*			rs;
	BOOL				attack;
	BOOL				invincible;
	BOOL				rescue;
	BOOL				rescueUse;
};

//�v���C���[�y�уp�[�c�̐��`��ԃf�[�^��ۑ�
class Playerliner
{
public:
	XMFLOAT3			pos;		// �|���S���̈ʒu
	XMFLOAT3			rot;		// �|���S���̌���(��])
	XMFLOAT3			scl;		// �|���S���̑傫��(�X�P�[��)
	float				move_time;
	INTERPOLATION_DATA	*tbl_adrA;	// �A�j���f�[�^�̃e�[�u���擪�A�h���X
	int					tbl_sizeA;	// �o�^�����e�[�u���̃��R�[�h����
	//���s���̃��[�V�����f�[�^
	INTERPOLATION_DATA	*tbl_adrM;	// �A�j���f�[�^�̃e�[�u���擪�A�h���X
	int					tbl_sizeM;	// �o�^�����e�[�u���̃��R�[�h����
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
void InitBootPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
void MovePlayer(void);
void ControlPlayer(void);
void ControlChangeArm(void);
void SetPlayerArm(void);
void ChangePlayerArm(BOOL flag);
void UpdateArm(void);
PLAYER *GetPlayer(void);
void PlayerStandLiner(int i);
void PlayerPartsIP(Playerliner* p);
void InvincibleFunc(PLAYER *p);
void UpdateRescueMode(void);
void CheckRescue(void);
HRESULT MakeVertexPlayerVar(void);
