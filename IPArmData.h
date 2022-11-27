#pragma once
#include "main.h"
#include "playerArms.h"

static INTERPOLATION_DATA_EASING wait_armLeft001[] = {
		{ XMFLOAT3(0.75, 2.5, -0.7),XMFLOAT3(0, 0, -0.24) , XMFLOAT3(1.0f, 1.0f, 1.0f), 40, EASING },
		{ XMFLOAT3(0.0f, 2.5f, -1.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(1.0f, 1.0f, 1.0f), 70 , EASING },
		{ XMFLOAT3(0.75, 2.5, -0.7),XMFLOAT3(0, 0, -0.24) , XMFLOAT3(1.0f, 1.0f, 1.0f), 40, EASING },
};
static INTERPOLATION_DATA_EASING wait_armLeft002[] = {
		{ XMFLOAT3(1.5, 3.2, -0.5),XMFLOAT3(0, 0, -0.2) , XMFLOAT3(1.0f, 1.0f, 1.0f), 40, EASING },
		{ XMFLOAT3(0.0f, 2.5f, -1.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(1.0f, 1.0f, 1.0f), 70 , EASING },
		{ XMFLOAT3(1.5, 3.2, -0.5),XMFLOAT3(0, 0, -0.2) , XMFLOAT3(1.0f, 1.0f, 1.0f), 40, EASING },
};
static INTERPOLATION_DATA_EASING wait_armRight001[] = {
		{ XMFLOAT3(0.75, 2.5, 0.7),XMFLOAT3(0, 0, -0.23) , XMFLOAT3(1.0f, 1.0f, 1.0f), 40, EASING },
		{ XMFLOAT3(0.0f, 2.5f, 0.5f), XMFLOAT3(0.0f, 0.0f, 0.), XMFLOAT3(1.0f, 1.0f, 1.0f), 70, EASING  },
		{ XMFLOAT3(0.75, 2.5, 0.7),XMFLOAT3(0, 0, -0.23) , XMFLOAT3(1.0f, 1.0f, 1.0f), 40, EASING },
};
static INTERPOLATION_DATA_EASING wait_armRight002[] = {
		{ XMFLOAT3(1.5, 3.2, 0.5),XMFLOAT3(0, 0, -0.2) , XMFLOAT3(1.0f, 1.0f, 1.0f), 40, EASING },
		{ XMFLOAT3(0.0f, 2.5f, 0.5f), XMFLOAT3(0.0f, 0.0f, 0.0), XMFLOAT3(1.0f, 1.0f, 1.0f), 70, EASING  },
		{ XMFLOAT3(1.5, 3.2, 0.5),XMFLOAT3(0, 0, -0.2) , XMFLOAT3(1.0f, 1.0f, 1.0f), 40, EASING },

};


//左腕チェーンソーの根元部分
static INTERPOLATION_DATA_EASING AttackArmSawLeft001[] = {
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (-0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70, NON_EASE  },
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70, NON_EASE  },
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (-0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70, NON_EASE  },

};
//左腕チェーンソーの先部分
static INTERPOLATION_DATA_EASING AttackArmSawLeft002[] = {
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70, NON_EASE  },
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (-0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70, NON_EASE  },
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70, NON_EASE  },

};

//右腕チェーンソーの根元部分
static INTERPOLATION_DATA_EASING AttackArmSawRight001[] = {
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (-0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70, NON_EASE  },
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70, NON_EASE  },
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (-0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70, NON_EASE  },

};
//右腕チェーンソーの先部分
static INTERPOLATION_DATA_EASING AttackArmSawRight002[] = {
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (-0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70, NON_EASE  },
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70 , NON_EASE },
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (-0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70 , NON_EASE },

};

////////
//Xgun
////////
//左腕Xgunの根元部分
static INTERPOLATION_DATA_EASING AttackArmXgunLeft001[] = {
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (0.0f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 40 , EASE_IN },
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (0.4f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 40 , EASE_OUT },
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (-0.8f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 40 , EASING },
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (0.0f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 60, EASING  },

};
//左腕Xgunの先部分
static INTERPOLATION_DATA_EASING AttackArmXgunLeft002[] = {
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 60, EASING  },
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (-0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 60 , EASING },
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70, EASING  },

};

//右腕チェーンソーの根元部分
static INTERPOLATION_DATA_EASING AttackArmXgunRight001[] = {
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (-0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70 , EASING },
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70, EASING  },
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (-0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70 , EASING },

};
//右腕チェーンソーの先部分
static INTERPOLATION_DATA_EASING AttackArmXgunRight002[] = {
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (-0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70, EASING  },
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70, EASING  },
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (-0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70 , EASING },

};

////////
//Braster
////////
//左腕Brasterの根元部分
static INTERPOLATION_DATA_EASING AttackArmBrasterLeft001[] = {
	{ XMFLOAT3(0.75, 2.5, -0.7),XMFLOAT3(0, 0, -0.24) , XMFLOAT3(1.0f, 1.0f, 1.0f), 16, EASE_OUT },
	{ XMFLOAT3(1.55, 2.75, -0.73),XMFLOAT3(0, 0, -0.27) , XMFLOAT3(1.0f, 1.0f, 1.0f), 8, NON_EASE },
	{ XMFLOAT3(1.55, 2.9, -0.73),XMFLOAT3(0, 0, -0.26) , XMFLOAT3(1.0f, 1.0f, 1.0f), 8, NON_EASE },
	{ XMFLOAT3(1.55, 3.0, -0.73),XMFLOAT3(0, 0, -0.25) , XMFLOAT3(1.0f, 1.0f, 1.0f), 10, EASING },
	{ XMFLOAT3(1.55, 2.6, -0.73),XMFLOAT3(0, 0, -0.23) , XMFLOAT3(1.0f, 1.0f, 1.0f), 10, EASING },
	{ XMFLOAT3(0.75, 2.5, -0.7),XMFLOAT3(0, 0, -0.24) , XMFLOAT3(1.0f, 1.0f, 1.0f), 15, NON_EASE },

};
//左腕Brasterの先部分
static INTERPOLATION_DATA_EASING AttackArmBrasterLeft002[] = {
	{ XMFLOAT3(1.5, 3.2, -0.5),XMFLOAT3(0, 0, -0.2) , XMFLOAT3(1.0f, 1.0f, 1.0f), 16, EASE_OUT },
	{ XMFLOAT3(2.7, 2.35, -0.5),XMFLOAT3(0, -0.04, -0.1) , XMFLOAT3(1.0f, 1.0f, 1.0f), 8, NON_EASE },
	{ XMFLOAT3(2.7, 2.7, -0.5),XMFLOAT3(0, -0.04, -0.04) , XMFLOAT3(1.0f, 1.0f, 1.0f), 8, NON_EASE },
	{ XMFLOAT3(2.7, 2.85, -0.5),XMFLOAT3(0, -0.04, -0.03) , XMFLOAT3(1.0f, 1.0f, 1.0f), 10, EASING },
	{ XMFLOAT3(2.35, 2.25, -0.5),XMFLOAT3(0, -0.03, -0.1) , XMFLOAT3(1.0f, 1.0f, 1.0f), 10, EASING },
	{ XMFLOAT3(1.5, 3.2, -0.5),XMFLOAT3(0, 0, -0.2) , XMFLOAT3(1.0f, 1.0f, 1.0f), 15, NON_EASE },

};

//右腕Brasterの根元部分
static INTERPOLATION_DATA_EASING AttackArmBrasterRight001[] = {
{ XMFLOAT3(0.75, 2.5, 0.7),XMFLOAT3(0, 0, -0.24) , XMFLOAT3(1.0f, 1.0f, 1.0f), 16, EASE_OUT },
{ XMFLOAT3(1.55, 2.75, 0.73),XMFLOAT3(0, 0, -0.27) , XMFLOAT3(1.0f, 1.0f, 1.0f), 8, NON_EASE },
{ XMFLOAT3(1.55, 2.9, 0.73),XMFLOAT3(0, 0, -0.26) , XMFLOAT3(1.0f, 1.0f, 1.0f), 8, NON_EASE },
{ XMFLOAT3(1.55, 3, 0.73),XMFLOAT3(0, 0, -0.25) , XMFLOAT3(1.0f, 1.0f, 1.0f), 10, EASING },
{ XMFLOAT3(1.55, 2.6, 0.73),XMFLOAT3(0, 0, -0.23) , XMFLOAT3(1.0f, 1.0f, 1.0f), 10, EASING },
{ XMFLOAT3(0.75, 2.5, 0.7),XMFLOAT3(0, 0, -0.23) , XMFLOAT3(1.0f, 1.0f, 1.0f), 15, NON_EASE },

};
//右腕Brasterの先部分
static INTERPOLATION_DATA_EASING AttackArmBrasterRight002[] = {
	{ XMFLOAT3(1.5, 3.2, 0.5),XMFLOAT3(0, 0, -0.2) , XMFLOAT3(1.0f, 1.0f, 1.0f), 16, EASE_OUT },
	{ XMFLOAT3(2.7, 2.35, 0.5),XMFLOAT3(0, 0.04, -0.1) , XMFLOAT3(1.0f, 1.0f, 1.0f), 8, NON_EASE },
	{ XMFLOAT3(2.7, 2.7, 0.5),XMFLOAT3(0, 0.04, -0.04) , XMFLOAT3(1.0f, 1.0f, 1.0f), 8, NON_EASE },
	{ XMFLOAT3(2.7, 2.85, 0.5),XMFLOAT3(0, 0.04, -0.03) , XMFLOAT3(1.0f, 1.0f, 1.0f), 10, EASING },
	{ XMFLOAT3(2.4, 2.25, 0.5),XMFLOAT3(0, 0.03, -0.1) , XMFLOAT3(1.0f, 1.0f, 1.0f), 10, EASING },
	{ XMFLOAT3(1.5, 3.2, 0.5),XMFLOAT3(0, 0, -0.2) , XMFLOAT3(1.0f, 1.0f, 1.0f), 15, NON_EASE },

};

//右腕ノーマル部分
static INTERPOLATION_DATA_EASING NormalArmRight001[] = {
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (-0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70, NON_EASE  },
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70 , NON_EASE },
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (-0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70 , NON_EASE },

};
//左ノーマルの先部分
static INTERPOLATION_DATA_EASING NormalArmLeft001[] = {
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (-0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70 , NON_EASE },
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70, NON_EASE  },
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (-0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70, NON_EASE  },

};

static int tblsize[] = { sizeof(wait_armLeft001) / sizeof(INTERPOLATION_DATA_EASING),
							sizeof(wait_armLeft002) / sizeof(INTERPOLATION_DATA_EASING),
							sizeof(wait_armRight001) / sizeof(INTERPOLATION_DATA_EASING),
							sizeof(wait_armRight002) / sizeof(INTERPOLATION_DATA_EASING),
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
	M_wait_armL01,
	M_wait_armL02,
	M_wait_armR01,
	M_wait_armR02,
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