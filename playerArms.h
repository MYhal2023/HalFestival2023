#pragma once
#include "player.h"
#include "model.h"
#define	MODEL_XGUN			"data/MODEL/Xgun.obj"			// �ǂݍ��ރ��f����
#define	MODEL_BRASTER			"data/MODEL/shoka.obj"			// �ǂݍ��ރ��f����
#define	MODEL_SAW		"data/MODEL/setsudan.obj"			// �ǂݍ��ރ��f����
////�A�[����ޗ�
//enum ArmVar
//{
//	Xgun,
//	Braster,
//	Saw,
//};
//�v���C���[�A�[���N���X
class pArm
{
protected:
	DX11_MODEL			model;		// ���f�����
	XMFLOAT4X4			mtxWorld;	// ���[���h�}�g���b�N�X
	XMFLOAT3			rot;		// �|���S���̌���(��])
	XMFLOAT3			scl;		// �|���S���̑傫��(�X�P�[��)

	// �K�w�A�j���[�V�����p�̃����o�[�ϐ�
	int					tbl_sizeA;	// �o�^�����e�[�u���̃��R�[�h����
	int					tbl_sizeM;	// �o�^�����e�[�u���̃��R�[�h����
	float				move_time;	// ���s����

	int					partsNum;	//�A�[���̃p�[�c��

	BOOL				use;		//�g�p����Ă��邩
	//�U��
	BOOL			attack;			//�U�������ۂ�

	INTERPOLATION_DATA	*tbl_adrA;	// �U���A�j���f�[�^�̃e�[�u���擪�A�h���X
	INTERPOLATION_DATA	*tbl_adrM;	// �ړ��A�j���f�[�^�̃e�[�u���擪�A�h���X
	PLAYER* player;
	pArm* parent;
	int					slot;

public:
	XMFLOAT3			pos;		// �|���S���̈ʒu
	static void SetArmParent(PLAYER *p);
	static void ChangeArm(void);
	static void Draw(void);
};

class Xgun :public pArm
{
public:
	static void InitArm(void);
	static void Action(void);
	static void Draw(void);
	static pArm* GetArm(void);
}; 

class Braster :public pArm
{
public:
	static void InitArm(void);
	static void Action(void);
	static void Draw(void);
	static pArm* GetArm(void);
};

class Saw :public pArm
{
public:
	static void InitArm(void);
	static void Action(void);
	static void Draw(void);
	static pArm* GetArm(void);
};