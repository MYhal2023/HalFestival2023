#pragma once
#include "main.h"
#include "playerArms.h"

static INTERPOLATION_DATA wait_armLeft[] = {
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (-0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70 },
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (-0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70 },

};
static INTERPOLATION_DATA wait_armRight[] = {
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (-0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70 },
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (-0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70 },

};


//���r�`�F�[���\�[�̍�������
static INTERPOLATION_DATA AttackArmSawLeft001[] = {
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (-0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70 },
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70 },
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (-0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70 },

};
//���r�`�F�[���\�[�̐敔��
static INTERPOLATION_DATA AttackArmSawLeft002[] = {
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70 },
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (-0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70 },
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70 },

};

//�E�r�`�F�[���\�[�̍�������
static INTERPOLATION_DATA AttackArmSawRight001[] = {
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (-0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70 },
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70 },
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (-0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70 },

};
//�E�r�`�F�[���\�[�̐敔��
static INTERPOLATION_DATA AttackArmSawRight002[] = {
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (-0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70 },
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70 },
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (-0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70 },

};

////////
//Xgun
////////
//���rXgun�̍�������
static INTERPOLATION_DATA AttackArmXgunLeft001[] = {
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (-0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70 },
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70 },
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (-0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70 },

};
//���rXgun�̐敔��
static INTERPOLATION_DATA AttackArmXgunLeft002[] = {
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70 },
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (-0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70 },
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70 },

};

//�E�r�`�F�[���\�[�̍�������
static INTERPOLATION_DATA AttackArmXgunRight001[] = {
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (-0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70 },
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70 },
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (-0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70 },

};
//�E�r�`�F�[���\�[�̐敔��
static INTERPOLATION_DATA AttackArmXgunRight002[] = {
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (-0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70 },
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70 },
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (-0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70 },

};

//�E�r�`�F�[���\�[�̍�������
static INTERPOLATION_DATA NormalArmRight001[] = {
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (-0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70 },
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70 },
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (-0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70 },

};
//�E�r�`�F�[���\�[�̐敔��
static INTERPOLATION_DATA NormalArmLeft001[] = {
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (-0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70 },
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70 },
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (-0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70 },

};

static int tblsize[] = { sizeof(wait_armLeft) / sizeof(INTERPOLATION_DATA),
							sizeof(wait_armRight) / sizeof(INTERPOLATION_DATA),
							sizeof(AttackArmSawLeft001) / sizeof(INTERPOLATION_DATA),
							sizeof(AttackArmSawLeft002) / sizeof(INTERPOLATION_DATA),
							sizeof(AttackArmSawRight001) / sizeof(INTERPOLATION_DATA),
							sizeof(AttackArmSawRight002) / sizeof(INTERPOLATION_DATA),
							sizeof(AttackArmXgunLeft001) / sizeof(INTERPOLATION_DATA),
							sizeof(AttackArmXgunLeft002) / sizeof(INTERPOLATION_DATA),
							sizeof(AttackArmXgunRight001) / sizeof(INTERPOLATION_DATA),
							sizeof(AttackArmXgunRight002) / sizeof(INTERPOLATION_DATA),
							sizeof(NormalArmRight001) / sizeof(INTERPOLATION_DATA),
							sizeof(NormalArmLeft001) / sizeof(INTERPOLATION_DATA),
};

enum ArmMotion
{
	M_wait_armL,
	M_wait_armR,
	M_AttackArmSawL001,
	M_AttackArmSawL002,
	M_AttackArmSawR001,
	M_AttackArmSawR002,
	M_AttackArmXgunL001,
	M_AttackArmXgunL002,
	M_AttackArmXgunR001,
	M_AttackArmXgunR002,
	M_NormalArmR001,
	M_NormalArmL001,
};