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
			{ XMFLOAT3(0.75, 2.5, -0.7),XMFLOAT3(0, 0, -0.24) , XMFLOAT3(1.0f, 1.0f, 1.0f), 20, EASING },
		{ XMFLOAT3(2.5f, -2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (-0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 30,  EASING   },
		{ XMFLOAT3(2.5f, 4.5f, -4.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f),  20,  EASE_OUT   },
		{ XMFLOAT3(2.5f, -2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (-0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 40,  NON_EASE  },
			{ XMFLOAT3(0.75, 2.5, -0.7),XMFLOAT3(0, 0, -0.24) , XMFLOAT3(1.0f, 1.0f, 1.0f), 20, NON_EASE },

};
//左腕チェーンソーの先部分
static INTERPOLATION_DATA_EASING AttackArmSawLeft002[] = {
			{ XMFLOAT3(1.5, 3.2, -0.5),XMFLOAT3(0, 0, -0.2) , XMFLOAT3(1.0f, 1.0f, 1.0f), 20, EASING },
		{ XMFLOAT3(4.0f,-9.5f, 2.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (-0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 30, EASING  },
		{ XMFLOAT3(2.0f, 2.5f, -4.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 20, EASE_OUT },
		{ XMFLOAT3(4.0f,-9.5f, 2.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (-0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 40, NON_EASE   },
			{ XMFLOAT3(1.5, 3.2, -0.5),XMFLOAT3(0, 0, -0.2) , XMFLOAT3(1.0f, 1.0f, 1.0f), 20, NON_EASE },

};

//右腕チェーンソーの根元部分
static INTERPOLATION_DATA_EASING AttackArmSawRight001[] = {
			{ XMFLOAT3(0.75, 2.5, 0.7),XMFLOAT3(0, 0, -0.23) , XMFLOAT3(1.0f, 1.0f, 1.0f), 10, EASING },
		{ XMFLOAT3(5.4, -2.5, 2.16143),XMFLOAT3(-0.0879646, 0.0722566, -0.725706) , XMFLOAT3(1.0f, 1.0f, 1.0f),  40,  EASE_IN     },
		{ XMFLOAT3(3.75, -0.3, 0.97075),XMFLOAT3(0.125664, -0.00314159, -0.317301) , XMFLOAT3(1.0f, 1.0f, 1.0f), 20, EASE_OUT },
		{ XMFLOAT3(5.4, -2.5, 2.16143),XMFLOAT3(-0.0879646, 0.0722566, -0.725706) , XMFLOAT3(1.0f, 1.0f, 1.0f),  40,  EASING    },
					{ XMFLOAT3(0.75, 2.5, 0.7),XMFLOAT3(0, 0, -0.23) , XMFLOAT3(1.0f, 1.0f, 1.0f), 20, NON_EASE },

};
//右腕チェーンソーの先部分
static INTERPOLATION_DATA_EASING AttackArmSawRight002[] = {
		{ XMFLOAT3(1.5, 3.2, 0.5),XMFLOAT3(0, 0, -0.2) , XMFLOAT3(1.0f, 1.0f, 1.0f), 10, EASING },
		{ XMFLOAT3(5.1, -9.5, 0.386416),XMFLOAT3(0.0188496, -0.0251328, 0) , XMFLOAT3(1.0f, 1.0f, 1.0f), 40,             EASE_IN  },
		{ XMFLOAT3(7.10001, 1.25, 0.666016),XMFLOAT3(-0.248186, -0.0753982, 0.0471239) , XMFLOAT3(1.0f, 1.0f, 1.0f), 20, EASE_OUT },
		{ XMFLOAT3(5.1, -9.5, 0.386416),XMFLOAT3(0.0188496, -0.0251328, 0) , XMFLOAT3(1.0f, 1.0f, 1.0f), 40,             EASING   },
				{ XMFLOAT3(1.5, 3.2, 0.5),XMFLOAT3(0, 0, -0.2) , XMFLOAT3(1.0f, 1.0f, 1.0f), 20, NON_EASE },

};

//モーションその2
//左腕チェーンソーの根元部分
static INTERPOLATION_DATA_EASING AttackArmSawLeft101[] = {
			{ XMFLOAT3(0.75, 2.5, -0.7),XMFLOAT3(0, 0, -0.24) , XMFLOAT3(1.0f, 1.0f, 1.0f), 10, EASING },
		{ XMFLOAT3(2.5f, -2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (-0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 30,  EASING   },
		{ XMFLOAT3(2.5f, 4.5f, -4.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f),  10,  EASE_OUT   },
		{ XMFLOAT3(2.5f, -2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (-0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 40,  EASE_IN  },
		{ XMFLOAT3(0.75, 2.5, -0.7),XMFLOAT3(0, 0, -0.24) , XMFLOAT3(1.0f, 1.0f, 1.0f), 20, NON_EASE },

};
//左腕チェーンソーの先部分
static INTERPOLATION_DATA_EASING AttackArmSawLeft102[] = {
			{ XMFLOAT3(1.5, 3.2, -0.5),XMFLOAT3(0, 0, -0.2) , XMFLOAT3(1.0f, 1.0f, 1.0f), 10, EASING },
		{ XMFLOAT3(4.0f,-9.5f, 2.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (-0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 30, EASING     },
		{ XMFLOAT3(2.0f, 2.5f, -4.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 10, EASE_OUT   },
		{ XMFLOAT3(4.0f,-9.5f, 2.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (-0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 40, EASE_IN   },
					{ XMFLOAT3(1.5, 3.2, -0.5),XMFLOAT3(0, 0, -0.2) , XMFLOAT3(1.0f, 1.0f, 1.0f), 20, EASING },

};

//右腕チェーンソーの根元部分
static INTERPOLATION_DATA_EASING AttackArmSawRight101[] = {
			{ XMFLOAT3(0.75, 2.5, 0.7),XMFLOAT3(0, 0, -0.23) , XMFLOAT3(1.0f, 1.0f, 1.0f), 10, EASING },
	{ XMFLOAT3(2.5f, -2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (-0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 30,  EASING   },
		{ XMFLOAT3(2.5f, 4.5f, 4.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f),  10,  EASE_OUT   },
		{ XMFLOAT3(2.5f, -2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (-0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 40,  EASE_IN  },
					{ XMFLOAT3(0.75, 2.5, 0.7),XMFLOAT3(0, 0, -0.23) , XMFLOAT3(1.0f, 1.0f, 1.0f), 20, NON_EASE },

};
//右腕チェーンソーの先部分
static INTERPOLATION_DATA_EASING AttackArmSawRight102[] = {
		{ XMFLOAT3(1.5, 3.2, 0.5),XMFLOAT3(0, 0, -0.2) , XMFLOAT3(1.0f, 1.0f, 1.0f), 10, EASING },
		{ XMFLOAT3(4.0f,-9.5f, -2.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (-0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 30, EASING     },
		{ XMFLOAT3(2.0f, 2.5f, 4.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (-0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 10, EASE_OUT   },
		{ XMFLOAT3(4.0f,-9.5f, -2.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * (-0.5f / (float)(MAX_ARM_PARTS - 1))), XMFLOAT3(1.0f, 1.0f, 1.0f), 40, EASE_IN   },
				{ XMFLOAT3(1.5, 3.2, 0.5),XMFLOAT3(0, 0, -0.2) , XMFLOAT3(1.0f, 1.0f, 1.0f), 20, NON_EASE },

};

////////
//Xgun
////////
//左腕Xgunの根元部分
static INTERPOLATION_DATA_EASING AttackArmXgunLeft001[] = {
		{ XMFLOAT3(0.75, 2.5, -0.7),XMFLOAT3(0, 0, -0.24) , XMFLOAT3(1.0f, 1.0f, 1.0f), 10, EASE_OUT },
		//{ XMFLOAT3(0.35, 1.35, -0.603185),XMFLOAT3(0, 0, -0.0942478) , XMFLOAT3(1.0f, 1.0f, 1.0f), 50 , EASE_OUT },
		{ XMFLOAT3(0.4, 2.3, -0.603185),XMFLOAT3(0, 0, 0) , XMFLOAT3(1.0f, 1.0f, 1.0f), 3 , EASING },
		{ XMFLOAT3(0.4, 2.3, -0.603185),XMFLOAT3(0, 0, 0) , XMFLOAT3(1.0f, 1.0f, 1.0f), 30 , EASE_IN },
		//{ XMFLOAT3(1.6, 2.5, -0.706857),XMFLOAT3(0, 0.069115, 0) , XMFLOAT3(1.0f, 1.0f, 1.0f), 10, NON_EASE },
		{ XMFLOAT3(0.4, 2, -0.581194),XMFLOAT3(0, 0.0251328, 0.015708) , XMFLOAT3(1.0f, 1.0f, 1.0f), 10, NON_EASE },
		{ XMFLOAT3(0.35, 1.35, -0.603185),XMFLOAT3(0, 0, -0.0942478) , XMFLOAT3(1.0f, 1.0f, 1.0f), 30 , EASE_OUT },
				{ XMFLOAT3(0.75, 2.5, -0.7),XMFLOAT3(0, 0, -0.24) , XMFLOAT3(1.0f, 1.0f, 1.0f), 20, NON_EASE },
};
//左腕Xgunの先部分
static INTERPOLATION_DATA_EASING AttackArmXgunLeft002[] = {
					{ XMFLOAT3(1.5, 3.2, -0.5),XMFLOAT3(0, 0, -0.2) , XMFLOAT3(1.0f, 1.0f, 1.0f), 10, EASE_OUT },
		//{ XMFLOAT3(1.3, 2.55, -0.603185),XMFLOAT3(0, -0.0219911, -0.23562) , XMFLOAT3(1.0f, 1.0f, 1.0f), 50, EASE_OUT },
		{ XMFLOAT3(0.25, 3, -0.603185),XMFLOAT3(0, -0.0345575, -0.207345) , XMFLOAT3(1.0f, 1.0f, 1.0f), 3, EASING },
		{ XMFLOAT3(0.25, 3, -0.603185),XMFLOAT3(0, -0.0345575, -0.207345) , XMFLOAT3(1.0f, 1.0f, 1.0f), 30, EASE_IN },
		//{ XMFLOAT3(1.8, 2.45, -0.618893),XMFLOAT3(0, 0.0753982, -0.241903) , XMFLOAT3(1.0f, 1.0f, 1.0f), 10, NON_EASE },
		{ XMFLOAT3(2, 2.6, -0.57491),XMFLOAT3(0.069115, 0.084823, -0.420973) , XMFLOAT3(1.0f, 1.0f, 1.0f), 10, NON_EASE },
		{ XMFLOAT3(1.3, 2.55, -0.603185),XMFLOAT3(0, -0.0219911, -0.23562) , XMFLOAT3(1.0f, 1.0f, 1.0f), 30, EASE_OUT  },
				{ XMFLOAT3(1.5, 3.2, -0.5),XMFLOAT3(0, 0, -0.2) , XMFLOAT3(1.0f, 1.0f, 1.0f), 20, NON_EASE },
};

//右腕Xgun根元部分
static INTERPOLATION_DATA_EASING AttackArmXgunRight001[] = {
					{ XMFLOAT3(0.75, 2.5, 0.7),XMFLOAT3(0, 0, -0.23) , XMFLOAT3(1.0f, 1.0f, 1.0f), 10, EASE_OUT },
		//{ XMFLOAT3(0.35, 1.35, 0.603185),XMFLOAT3(0, 0, -0.0942478) , XMFLOAT3(1.0f, 1.0f, 1.0f), 50 , EASE_OUT },
		{ XMFLOAT3(0.4, 3, 0.603185),XMFLOAT3(0, 0, 0) , XMFLOAT3(1.0f, 1.0f, 1.0f), 3 , EASING },
		{ XMFLOAT3(0.4, 3, 0.603185),XMFLOAT3(0, 0, 0) , XMFLOAT3(1.0f, 1.0f, 1.0f), 30 , EASE_IN },
		//{ XMFLOAT3(1.6, 2.5, 0.706857),XMFLOAT3(0, -0.069115, 0) , XMFLOAT3(1.0f, 1.0f, 1.0f), 10, NON_EASE },
		{ XMFLOAT3(0.4, 2, 0.581194),XMFLOAT3(0, -0.0251328, 0.015708) , XMFLOAT3(1.0f, 1.0f, 1.0f), 10, NON_EASE },
		{ XMFLOAT3(0.35, 1.35, 0.603185),XMFLOAT3(0, 0, -0.0942478) , XMFLOAT3(1.0f, 1.0f, 1.0f), 30 , EASE_OUT },
				{ XMFLOAT3(0.75, 2.5, 0.7),XMFLOAT3(0, 0, -0.23) , XMFLOAT3(1.0f, 1.0f, 1.0f), 20, NON_EASE },
};
//右腕Xgun先部分
static INTERPOLATION_DATA_EASING AttackArmXgunRight002[] = {
					{ XMFLOAT3(1.5, 3.2, 0.5),XMFLOAT3(0, 0, -0.2) , XMFLOAT3(1.0f, 1.0f, 1.0f), 10, EASE_OUT },
		//{ XMFLOAT3(1.3, 2.55, 0.603185),XMFLOAT3(0, 0.0219911, -0.23562) , XMFLOAT3(1.0f, 1.0f, 1.0f), 50, EASE_OUT },
		{ XMFLOAT3(0.25, 4, 0.603185),XMFLOAT3(0, 0.0345575, -0.207345) , XMFLOAT3(1.0f, 1.0f, 1.0f), 3, EASING },
		{ XMFLOAT3(0.25, 4, 0.603185),XMFLOAT3(0, 0.0345575, -0.207345) , XMFLOAT3(1.0f, 1.0f, 1.0f), 30, EASE_IN },
		//{ XMFLOAT3(1.8, 2.45, 0.618893),XMFLOAT3(0, -0.0753982, -0.241903) , XMFLOAT3(1.0f, 1.0f, 1.0f), 10, NON_EASE },
		{ XMFLOAT3(2, 2.6, 0.57491),XMFLOAT3(0.069115, -0.084823, -0.420973) , XMFLOAT3(1.0f, 1.0f, 1.0f), 10, NON_EASE },
		{ XMFLOAT3(1.3, 2.55, 0.603185),XMFLOAT3(0, 0.0219911, -0.23562) , XMFLOAT3(1.0f, 1.0f, 1.0f), 30, EASE_OUT  },
				{ XMFLOAT3(1.5, 3.2, 0.5),XMFLOAT3(0, 0, -0.2) , XMFLOAT3(1.0f, 1.0f, 1.0f), 20, NON_EASE }
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

//左ノーマルの先部分
static INTERPOLATION_DATA_EASING NormalArmLeft001[] = {
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(1.0f, 1.0f, 1.0f), 30, EASING },
		{ XMFLOAT3(-3.0f, -1.6f, 0.0f),XMFLOAT3(0.0f, 0.0f, -0.0471239f) , XMFLOAT3(1.0f, 1.0f, 1.0f), 30, NON_EASE },
		// 戻りモーション
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(1.0f, 1.0f, 1.0f), 70, EASING },
};
//左ノーマルの先部分
static INTERPOLATION_DATA_EASING NormalArmLeft002[] = {
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(1.0f, 1.0f, 1.0f), 30, EASING },
		{ XMFLOAT3(-1.25f, -52.6494f, 0.0f),XMFLOAT3(0.0f, 0.0f, 0.0659735f) , XMFLOAT3(1.0f, 1.0f, 1.0f), 30, NON_EASE },
		// 戻りモーション
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(1.0f, 1.0f, 1.0f), 70, EASING },

};

//右腕ノーマル部分
static INTERPOLATION_DATA_EASING NormalArmRight001[] = {
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(1.0f, 1.0f, 1.0f), 30, EASING },
		{ XMFLOAT3(-3.0f, -1.6f, 0.0f),XMFLOAT3(0.0f, 0.0f, -0.0471239f) , XMFLOAT3(1.0f, 1.0f, 1.0f), 30, NON_EASE },
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(1.0f, 1.0f, 1.0f), 70, EASING },

};
//右腕ノーマル部分
static INTERPOLATION_DATA_EASING NormalArmRight002[] = {
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(1.0f, 1.0f, 1.0f), 30, EASING },
		{ XMFLOAT3(-1.25f, -52.6494f, 0.0f),XMFLOAT3(0.0f, 0.0f, 0.0659735f) , XMFLOAT3(1.0f, 1.0f, 1.0f), 30, NON_EASE },
		{ XMFLOAT3(0.0f, 2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(1.0f, 1.0f, 1.0f), 70, EASING },

};

static int tblsize[] = { sizeof(wait_armLeft001) / sizeof(INTERPOLATION_DATA_EASING),
							sizeof(wait_armLeft002) / sizeof(INTERPOLATION_DATA_EASING),
							sizeof(wait_armRight001) / sizeof(INTERPOLATION_DATA_EASING),
							sizeof(wait_armRight002) / sizeof(INTERPOLATION_DATA_EASING),
							sizeof(AttackArmSawLeft001) / sizeof(INTERPOLATION_DATA_EASING),
							sizeof(AttackArmSawLeft002) / sizeof(INTERPOLATION_DATA_EASING),
							sizeof(AttackArmSawRight001) / sizeof(INTERPOLATION_DATA_EASING),
							sizeof(AttackArmSawRight002) / sizeof(INTERPOLATION_DATA_EASING),
							sizeof(AttackArmSawLeft101) / sizeof(INTERPOLATION_DATA_EASING),
							sizeof(AttackArmSawLeft102) / sizeof(INTERPOLATION_DATA_EASING),
							sizeof(AttackArmSawRight101) / sizeof(INTERPOLATION_DATA_EASING),
							sizeof(AttackArmSawRight102) / sizeof(INTERPOLATION_DATA_EASING),
							sizeof(AttackArmXgunLeft001) / sizeof(INTERPOLATION_DATA_EASING),
							sizeof(AttackArmXgunLeft002) / sizeof(INTERPOLATION_DATA_EASING),
							sizeof(AttackArmXgunRight001) / sizeof(INTERPOLATION_DATA_EASING),
							sizeof(AttackArmXgunRight002) / sizeof(INTERPOLATION_DATA_EASING),
							sizeof(AttackArmBrasterLeft001) / sizeof(INTERPOLATION_DATA_EASING),
							sizeof(AttackArmBrasterLeft002) / sizeof(INTERPOLATION_DATA_EASING),
							sizeof(AttackArmBrasterRight001) / sizeof(INTERPOLATION_DATA_EASING),
							sizeof(AttackArmBrasterRight002) / sizeof(INTERPOLATION_DATA_EASING),
							sizeof(NormalArmLeft001) / sizeof(INTERPOLATION_DATA_EASING),
							sizeof(NormalArmLeft002) / sizeof(INTERPOLATION_DATA_EASING),
							sizeof(NormalArmRight001) / sizeof(INTERPOLATION_DATA_EASING),
							sizeof(NormalArmRight002) / sizeof(INTERPOLATION_DATA_EASING),
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
	M_AttackArmSawL101,
	M_AttackArmSawL102,
	M_AttackArmSawR101,
	M_AttackArmSawR102,
	M_AttackArmXgunL001,
	M_AttackArmXgunL002,
	M_AttackArmXgunR001,
	M_AttackArmXgunR002,
	M_AttackArmBrasterL001,
	M_AttackArmBrasterL002,
	M_AttackArmBrasterR001,
	M_AttackArmBrasterR002,
	M_NormalArmL001,
	M_NormalArmL002,
	M_NormalArmR001,
	M_NormalArmR002,
};