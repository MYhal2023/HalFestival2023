#pragma once
#include "main.h"
#include "playerArms.h"

INTERPOLATION_DATA wait_armLeft[] = {
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (-0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70 },
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (-0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70 },

};
INTERPOLATION_DATA wait_armRight[] = {
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (-0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70 },
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (-0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70 },

};


//左腕チェーンソーの根元部分
INTERPOLATION_DATA AttackArmSawLeft001[] = {
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (-0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70 },
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70 },
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (-0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70 },

};
//左腕チェーンソーの先部分
INTERPOLATION_DATA AttackArmSawLeft002[] = {
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70 },
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (-0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70 },
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70 },

};

//右腕チェーンソーの根元部分
INTERPOLATION_DATA AttackArmSawRight001[] = {
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (-0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70 },
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70 },
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (-0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70 },

};
//右腕チェーンソーの先部分
INTERPOLATION_DATA AttackArmSawRight002[] = {
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (-0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70 },
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70 },
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (-0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70 },

};

////////
//Xgun
////////
//左腕Xgunの根元部分
INTERPOLATION_DATA AttackArmXgunLeft001[] = {
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (-0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70 },
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70 },
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (-0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70 },

};
//左腕Xgunの先部分
INTERPOLATION_DATA AttackArmXgunLeft002[] = {
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70 },
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (-0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70 },
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70 },

};

//右腕チェーンソーの根元部分
INTERPOLATION_DATA AttackArmXgunRight001[] = {
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (-0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70 },
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70 },
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (-0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 70 },

};
//右腕チェーンソーの先部分
INTERPOLATION_DATA AttackArmXgunRight002[] = {
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
};