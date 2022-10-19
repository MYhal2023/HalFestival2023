//=============================================================================
//
// ���f������ [player.h]
// Author : 
//
//=============================================================================
#pragma once
#ifndef PLAYER_H_
#define PLAYER_H_
#include "unitdata.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MODEL_PLAYER		"data/MODEL/dendritic_cells.obj"			// �ǂݍ��ރ��f����
#define	MODEL_NEUTROPHILS	"data/MODEL/neutrophils.obj"			// �ǂݍ��ރ��f����
#define	MODEL_MACRO			"data/MODEL/Macrophages.obj"			// �ǂݍ��ރ��f����
#define	MODEL_MACRO_ARM		"data/MODEL/Macrophages_arm.obj"			// �ǂݍ��ރ��f����
#define	MODEL_MACRO_LEG		"data/MODEL/Macrophages_leg.obj"			// �ǂݍ��ރ��f����
#define	MODEL_NK			"data/MODEL/sniper.obj"			// �ǂݍ��ރ��f����
#define	MODEL_HELPT			"data/MODEL/thelper.obj"			// �ǂݍ��ރ��f����
#define	MODEL_HELPTTOP		"data/MODEL/thelpertop.obj"			// �ǂݍ��ރ��f����
#define	MODEL_KILLT			"data/MODEL/tkiller.obj"			// �ǂݍ��ރ��f����
#define	MODEL_KILLAXE		"data/MODEL/axe.obj"			// �ǂݍ��ރ��f����
#define	MODEL_KOUEN			"data/MODEL/kouenn.obj"			// �ǂݍ��ރ��f����
#define	MODEL_KOUEN_ARM001	"data/MODEL/kouenn_arm.obj"			// �ǂݍ��ރ��f����
#define	MODEL_KOUEN_ARM002	"data/MODEL/kouenn_arm2.obj"			// �ǂݍ��ރ��f����

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
	// �K�w�A�j���[�V�����p�̃����o�[�ϐ�
	PLAYER				*parent;	// �������e�Ȃ�NULL�A�������q���Ȃ�e��enemy�A�h���X

	int				blockNum;		//�u���b�N���Ă��鐔
	int				blockMax;		//�u���b�N�\��
	int				target;			//�^�[�Q�b�g������99��
	int				targetable[MAX_TARGET];	//�^�[�Q�b�g�\�ȓG�̔z��Y������ۑ����Ă������́B���̃��X�g�̓�����Atarget�ϐ��Ɉ����n�����
	int				count;					//���݃^�[�Q�b�g�ɂ��Ă��鐔
	int				keyNum;			//�����L�[�̂ǂ��ɑΉ����Ă��邩��ۑ�
	int				cost;			//�ݒu���邽�߂ɕK�v�ȃR�X�g
	int				level;			//���j�b�g���x��
	int				skillID;		//�ǂ�ȃX�L���������Ă���̂�(���O�ɃX�L�����Ƃ�ID�U����s��)
	int				skillPoint;		//�ۗL���Ă���X�L���|�C���g
	int				increaseSP;		//���ő�����sp��
	int				skillPointMax;	//�ۗL�ł���X�L���|�C���g�B�����܂ŗ��܂�΃X�L�����g����
	int				intervalSP;		//sp�𑝂₷�Ԋu��}��ׂ̕ϐ�
	int				skillTime;
	int				skillTimeMax;
	BOOL			skillUse;		//�X�L�����g���Ă��邩�ۂ�
	BOOL			skillAble;		//�X�L�����g���邩�ۂ�
	int				attackSE;		//�U������SE
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

PLAYER *GetPlayer(void);
PlayerParts *GetPlayerParts(void);
void PlayerStandLiner(int i);
void PlayerInterPoration(int i);
int GetPlayerPartsNum(void);
void SetPlayerPartsNum(int s);
HRESULT MakeVertexPlayerVar(void);
#endif