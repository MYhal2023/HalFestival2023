#pragma once
#include "main.h"
#include "playerArms.h"

static INTERPOLATION_DATA_EASING wait_armLeft[] = {
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (-0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70, NON_EASE },
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (-0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70, NON_EASE  },

};
static INTERPOLATION_DATA_EASING wait_armRight[] = {
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (-0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70, NON_EASE  },
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (-0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70, NON_EASE  },

};


//���r�`�F�[���\�[�̍�������
static INTERPOLATION_DATA_EASING AttackArmSawLeft001[] = {
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (-0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70, NON_EASE  },
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70, NON_EASE  },
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (-0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70, NON_EASE  },

};
//���r�`�F�[���\�[�̐敔��
static INTERPOLATION_DATA_EASING AttackArmSawLeft002[] = {
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70, NON_EASE  },
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (-0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70, NON_EASE  },
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70, NON_EASE  },

};

//�E�r�`�F�[���\�[�̍�������
static INTERPOLATION_DATA_EASING AttackArmSawRight001[] = {
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (-0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70, NON_EASE  },
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70, NON_EASE  },
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (-0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70, NON_EASE  },

};
//�E�r�`�F�[���\�[�̐敔��
static INTERPOLATION_DATA_EASING AttackArmSawRight002[] = {
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (-0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70, NON_EASE  },
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70 , NON_EASE },
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (-0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70 , NON_EASE },

};

////////
//Xgun
////////
//���rXgun�̍�������
static INTERPOLATION_DATA_EASING AttackArmXgunLeft001[] = {
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (0.0f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 40 , EASE_IN },
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (0.4f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 40 , EASE_OUT },
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (-0.8f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 40 , EASING },
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (0.0f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 60, EASING  },

};
//���rXgun�̐敔��
static INTERPOLATION_DATA_EASING AttackArmXgunLeft002[] = {
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 60, EASING  },
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (-0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 60 , EASING },
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70, EASING  },

};

//�E�r�`�F�[���\�[�̍�������
static INTERPOLATION_DATA_EASING AttackArmXgunRight001[] = {
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (-0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70 , EASING },
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70, EASING  },
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (-0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70 , EASING },

};
//�E�r�`�F�[���\�[�̐敔��
static INTERPOLATION_DATA_EASING AttackArmXgunRight002[] = {
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (-0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70, EASING  },
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70, EASING  },
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (-0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70 , EASING },

};

////////
//Braster
////////
//���rBraster�̍�������
static INTERPOLATION_DATA_EASING AttackArmBrasterLeft001[] = {
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (-0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70 , NON_EASE },
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70, NON_EASE  },
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (-0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70 , NON_EASE },

};
//���rBraster�̐敔��
static INTERPOLATION_DATA_EASING AttackArmBrasterLeft002[] = {
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70 , NON_EASE },
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (-0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70 , NON_EASE },
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70 , NON_EASE },

};

//�E�rBraster�̍�������
static INTERPOLATION_DATA_EASING AttackArmBrasterRight001[] = {
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (-0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70 , NON_EASE },
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70, NON_EASE  },
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (-0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70 , NON_EASE },

};
//�E�rBraster�̐敔��
static INTERPOLATION_DATA_EASING AttackArmBrasterRight002[] = {
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (-0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70, NON_EASE  },
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70, NON_EASE  },
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (-0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70 , NON_EASE },

};

//�E�r�m�[�}������
static INTERPOLATION_DATA_EASING NormalArmRight001[] = {
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (-0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70, NON_EASE  },
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70 , NON_EASE },
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (-0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70 , NON_EASE },

};
//���m�[�}���̐敔��
static INTERPOLATION_DATA_EASING NormalArmLeft001[] = {
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (-0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70 , NON_EASE },
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70, NON_EASE  },
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (-0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70, NON_EASE  },

};

static int tblsize[] = { sizeof(wait_armLeft) / sizeof(INTERPOLATION_DATA_EASING),
							sizeof(wait_armRight) / sizeof(INTERPOLATION_DATA_EASING),
							sizeof(AttackArmSawLeft001) / sizeof(INTERPOLATION_DATA_EASING),
							sizeof(AttackArmSawLeft002) / sizeof(INTERPOLATION_DATA_EASING),
							sizeof(AttackArmSawRight001) / sizeof(INTERPOLATION_DATA_EASING),
							sizeof(AttackArmSawRight002) / sizeof(INTERPOLATION_DATA_EASING),
							sizeof(AttackArmXgunLeft001) / sizeof(INTERPOLATION_DATA_EASING),
							sizeof(AttackArmXgunLeft002) / sizeof(INTERPOLATION_DATA_EASING),
							sizeof(AttackArmXgunRight001) / sizeof(INTERPOLATION_DATA_EASING),
							sizeof(AttackArmXgunRight002) / sizeof(INTERPOLATION_DATA_EASING),
							sizeof(AttackArmBrasterLeft001) / sizeof(INTERPOLATION_DATA_EASING),
							sizeof(AttackArmBrasterLeft002) / sizeof(INTERPOLATION_DATA_EASING),
							sizeof(AttackArmBrasterRight001) / sizeof(INTERPOLATION_DATA_EASING),
							sizeof(AttackArmBrasterRight002) / sizeof(INTERPOLATION_DATA_EASING),
							sizeof(NormalArmRight001) / sizeof(INTERPOLATION_DATA_EASING),
							sizeof(NormalArmLeft001) / sizeof(INTERPOLATION_DATA_EASING),
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
	M_AttackArmBrasterL001,
	M_AttackArmBrasterL002,
	M_AttackArmBrasterR001,
	M_AttackArmBrasterR002,
	M_NormalArmR001,
	M_NormalArmL001,
};