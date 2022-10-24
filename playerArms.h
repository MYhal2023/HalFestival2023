#pragma once
#include "player.h"
#include "model.h"
//�A�[����ޗ�
enum ArmVar
{
	Xgun,
	Braster,
	Saw,
};
//�v���C���[�A�[���N���X
class pArm
{
private:
	DX11_MODEL			model;		// ���f�����
	XMFLOAT4X4			mtxWorld;	// ���[���h�}�g���b�N�X
	XMFLOAT3			pos;		// �|���S���̈ʒu
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

public:
	static void Draw(void);
	static void SetArmParent(PLAYER *p);
	pArm* GetArm(void);
};

class Xgun :public pArm
{
public:
	static void InitArm(void);
	static void Action(void);
}; 

class Braster :public pArm
{
public:
	static void InitArm(void);
	static void Action(void);
};

class Saw :public pArm
{
public:
	static void InitArm(void);
	static void Action(void);
};