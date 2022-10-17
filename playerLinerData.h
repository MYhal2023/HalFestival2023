//=============================================================================
//
// �o�g�����̐��`�⊮�f�[�^(����) [playerLinerData.h]
// Author : 
//
//=============================================================================
#pragma once
#include "main.h"
////////////////////////////////////////
////�d�l����////
//////�{�̃f�[�^�́A���f�[�^�Ɂh���Z�h���鐔�l������΂悢(0.0���ŉ������Ȃ��f�[�^������B����scl�͒���)
/////�p�[�c�f�[�^�������悤�ɍ���Ă���Ă悢���Ascl�����́h1.0f���f�t�H���g�h�Ȃ��ߒ���
/////�܂��A�t���[�������͕K�����ꂷ�邱�ƁB
////�{�̃��[�V������120�t���[���ŏI���Ƃ���Ȃ�΁A�p�[�c��120�t���[���ŏI��点��K�v������B
////�ŏI�e�[�u���f�[�^�̃t���[���͎Q�Ƃ���邱�Ƃ��Ȃ����߁A���������Z�����ɑ��������킹��B
////�e�[�u���������킹��K�v�͂Ȃ��B�e�[�u�����Ɋւ��Ă̓p�[�c���ƂɈ���Ă����Ȃ��B
////
//////////////////////////
////�D�����U�����[�V�����f�[�^
//////////////////////////
static INTERPOLATION_DATA neutro_Attack[] = {	// pos, rot, scl, frame
	{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),				XMFLOAT3(0.5f, 0.5f, 0.5f), 40 },
	{ XMFLOAT3(-10.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI*0.125f, 0.0f, 0.0f),	XMFLOAT3(0.5f, 0.5f, 0.5f),  5 },
	{ XMFLOAT3(10.0f, 0.0f, 0.0f), XMFLOAT3(-XM_PI * 0.125f, 0.0f, 0.0f),	XMFLOAT3(0.5f, 0.5f, 0.5f), 15 },
	{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),				XMFLOAT3(0.5f, 0.5f, 0.5f),  0 },
};
//////////////////////////
////�D�����ҋ@���[�V�����f�[�^
static INTERPOLATION_DATA neutro_Standby[] = {	// pos, rot, scl, frame
	{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),	XMFLOAT3(0.5f, 0.5f, 0.5f), 15 },
	{ XMFLOAT3(0.0f, 5.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),	XMFLOAT3(0.5f, 0.5f, 0.5f), 15 },
	{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),	XMFLOAT3(0.5f, 0.5f, 0.5f), 15 },
	{ XMFLOAT3(0.0f,-5.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),	XMFLOAT3(0.5f, 0.5f, 0.5f), 15 },
	{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),	XMFLOAT3(0.5f, 0.5f, 0.5f),  0 },
};
////////////////////////////////////
//////////////////////////
////�}�N���t�@�[�W�U�����[�V�����f�[�^
//////////////////////////
static INTERPOLATION_DATA macro_Attack[] = {	// pos, rot, scl, frame
	{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),	XMFLOAT3(0.0f, 0.0f, 0.0f), 15 },
	{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),	XMFLOAT3(0.0f, 0.0f, 0.0f), 5 },
	{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, XM_PI * 0.125f, 0.0f),	XMFLOAT3(0.0f, 0.0f, 0.0f),  25 },
	{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),	XMFLOAT3(0.0f, 0.0f, 0.0f), 5 },
	{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),	XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
	{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),	XMFLOAT3(0.0f, 0.0f, 0.0f), 0},

};
static INTERPOLATION_DATA macro_ArmAt[] = {	// pos, rot, scl, frame
	{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),	XMFLOAT3(1.0f, 1.0f, 1.0f),  20 },
	{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),	XMFLOAT3(1.0f, 1.0f, 1.0f),  5 },
	{ XMFLOAT3(0.0f, 0.0f,-15.0f), XMFLOAT3(XM_PI * 0.125f, 0.0f, 0.0f),	XMFLOAT3(1.0f, 1.0f, 1.0f),  5 },
	{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.125f * 0.125f, 0.0f, 0.0f),	XMFLOAT3(1.0f, 1.0f, 1.0f),  5 },
	{ XMFLOAT3(0.0f, 0.0f,-15.0f), XMFLOAT3(XM_PI * 0.125f, 0.0f, 0.0f),	XMFLOAT3(1.0f, 1.0f, 1.0f),  5 },
	{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),	XMFLOAT3(1.0f, 1.0f, 1.0f),  5 },
	{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),	XMFLOAT3(1.0f, 1.0f, 1.0f),  15 },
	{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),	XMFLOAT3(1.0f, 1.0f, 1.0f),  0 },
};
static INTERPOLATION_DATA macro_LegAt[] = {	// pos, rot, scl, frame
	{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),	XMFLOAT3(1.0f, 1.0f, 1.0f), 40 },
	{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),	XMFLOAT3(1.0f, 1.0f, 1.0f),  5 },
	{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),	XMFLOAT3(1.0f, 1.0f, 1.0f), 15 },
	{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),	XMFLOAT3(1.0f, 1.0f, 1.0f),	 0 },

};
//////////////////////////
////�}�N���t�@�[�W�ҋ@���[�V�����f�[�^
static INTERPOLATION_DATA macro_Standby[] = {	// pos, rot, scl, frame
	{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, -XM_PI * 0.125f, 0.0f),	XMFLOAT3(0.0f, 0.0f, 0.0f), 65 },
	{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, XM_PI * 0.25f, 0.0f),	XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
	{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, -XM_PI * 0.125f, 0.0f),	XMFLOAT3(0.0f, 0.0f, 0.0f),  0 },
};
static INTERPOLATION_DATA macro_ArmSb[] = {	// pos, rot, scl, frame
	{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),	XMFLOAT3(1.0f, 1.0f, 1.0f), 5 },
	{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),	XMFLOAT3(1.0f, 1.0f, 1.0f), 15 },
	{ XMFLOAT3(0.0f, 0.0f, -12.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),	XMFLOAT3(1.0f, 1.0f, 1.0f), 15 },
	{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),	XMFLOAT3(1.0f, 1.0f, 1.0f), 15 },
	{ XMFLOAT3(0.0f, 0.0f, -12.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),	XMFLOAT3(1.0f, 1.0f, 1.0f), 15 },
	{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),	XMFLOAT3(1.0f, 1.0f, 1.0f), 10 },
	{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),	XMFLOAT3(1.0f, 1.0f, 1.0f), 0 },


};
static INTERPOLATION_DATA macro_LegSb[] = {	// pos, rot, scl, frame
	{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),	XMFLOAT3(1.0f, 1.0f, 1.0f), 60 },
	{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),	XMFLOAT3(1.0f, 1.0f, 1.0f), 0 },
};
////////////////////////////////////
//////////////////////////
////�w���p�[T�U�����[�V�����f�[�^
//////////////////////////
static INTERPOLATION_DATA helperT_Attack[] = {	// pos, rot, scl, frame
	{ XMFLOAT3(0.0f, 3.0f, 0.0f), XMFLOAT3(0.0f, XM_PI * 0.5f, 0.0f),	XMFLOAT3(0.0f, 0.0f, 0.0f), 30 },
	{ XMFLOAT3(0.0f, 5.0f, 0.0f), XMFLOAT3(0.0f, XM_PI * 0.5f, 0.0f),	XMFLOAT3(0.0f, 0.0f, 0.0f), 30 },
	{ XMFLOAT3(0.0f, 3.0f, 0.0f), XMFLOAT3(0.0f, XM_PI * 0.5f, 0.0f),	XMFLOAT3(0.0f, 0.0f, 0.0f),  0 },
};
static INTERPOLATION_DATA helperT_TopAt[] = {	// pos, rot, scl, frame
	{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, XM_PI * 0.5f, 0.0f),	XMFLOAT3(1.0f, 1.0f, 1.0f), 50 },
	{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, XM_PI * 0.5f, 0.0f),	XMFLOAT3(1.0f, 1.0f, 1.0f), 5 },
	{ XMFLOAT3(0.0f, -2.0f, 0.0f), XMFLOAT3(0.0f, XM_PI * 0.5f, 0.0f),	XMFLOAT3(1.0f, 1.0f, 1.0f), 5 },
	{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, XM_PI * 0.5f, 0.0f),	XMFLOAT3(1.0f, 1.0f, 1.0f), 0 },
};
//////////////////////////
////�w���p�[T�ҋ@���[�V�����f�[�^
static INTERPOLATION_DATA helperT_Standby[] = {	// pos, rot, scl, frame
	{ XMFLOAT3(0.0f, 3.0f, 0.0f), XMFLOAT3(0.0f, XM_PI * 0.5f, 0.0f),	XMFLOAT3(0.0f, 0.0f, 0.0f), 30 },
	{ XMFLOAT3(0.0f, 5.0f, 0.0f), XMFLOAT3(0.0f, XM_PI * 0.5f, 0.0f),	XMFLOAT3(0.0f, 0.0f, 0.0f), 30 },
	{ XMFLOAT3(0.0f, 3.0f, 0.0f), XMFLOAT3(0.0f, XM_PI * 0.5f, 0.0f),	XMFLOAT3(0.0f, 0.0f, 0.0f),  0 },
};
static INTERPOLATION_DATA helperT_TopSb[] = {	// pos, rot, scl, frame
	{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, XM_PI * 0.5f, 0.0f),	XMFLOAT3(1.0f, 1.0f, 1.0f), 60 },
	{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, XM_PI * 0.5f, 0.0f),	XMFLOAT3(1.0f, 1.0f, 1.0f), 0 },
};
////////////////////////////////////
//////////////////////////
////�L���[T�U�����[�V�����f�[�^
//////////////////////////
static INTERPOLATION_DATA killerT_Attack[] = {	// pos, rot, scl, frame
	{ XMFLOAT3(0.0f, 5.0f, 0.0f), XMFLOAT3(0.0f, XM_PI * 0.75f, 0.0f),	XMFLOAT3(0.0f, 0.0f, 0.0f), 50 },
	{ XMFLOAT3(0.0f, 5.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),	XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
	{ XMFLOAT3(0.0f, 5.0f, 0.0f), XMFLOAT3(0.0f, XM_PI * 0.75f, 0.0f),	XMFLOAT3(0.0f, 0.0f, 0.0f),  0 },

};
static INTERPOLATION_DATA killerT_AxeAt[] = {	// pos, rot, scl, frame
	{ XMFLOAT3(0.0f, 0.0f, 10.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),	XMFLOAT3(1.0f, 1.0f, 1.0f), 50 },
	{ XMFLOAT3(0.0f, 0.0f, 10.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * 0.5f),	XMFLOAT3(1.0f, 1.0f, 1.0f),  5 },
	{ XMFLOAT3(0.0f, 0.0f, 10.0f), XMFLOAT3(0.0f, 0.0f, XM_PI * 0.25f),	XMFLOAT3(1.0f, 1.0f, 1.0f),  5 },
	{ XMFLOAT3(0.0f, 0.0f, 10.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),	XMFLOAT3(1.0f, 1.0f, 1.0f), 0 },

};
//////////////////////////
////�L���[T�ҋ@���[�V�����f�[�^
static INTERPOLATION_DATA killerT_Standby[] = {	// pos, rot, scl, frame

	{ XMFLOAT3(0.0f, 5.0f, 0.0f), XMFLOAT3(0.0f, XM_PI * 0.5f, 0.0f),	XMFLOAT3(0.0f, 0.0f, 0.0f), 50 },
	{ XMFLOAT3(0.0f, 5.0f, 0.0f), XMFLOAT3(0.0f, XM_PI * 0.5f, 0.0f),	XMFLOAT3(0.0f, 0.0f, 0.0f),  5 },
	{ XMFLOAT3(0.0f,10.0f, 0.0f), XMFLOAT3(0.0f, XM_PI * 0.5f, 0.0f),	XMFLOAT3(0.0f, 0.0f, 0.0f),  5 },
	{ XMFLOAT3(0.0f, 5.0f, 0.0f), XMFLOAT3(0.0f, XM_PI * 0.5f, 0.0f),	XMFLOAT3(0.0f, 0.0f, 0.0f),  0 },
};
static INTERPOLATION_DATA killerT_AxeSb[] = {	// pos, rot, scl, frame
	{ XMFLOAT3(0.0f, 0.0f, 10.0f), XMFLOAT3(0.0f, XM_PI * 0.0f, 0.0f),	XMFLOAT3(1.0f, 1.0f, 1.0f), 50 },
	{ XMFLOAT3(0.0f, 0.0f, 10.0f), XMFLOAT3(0.0f, XM_PI * 0.0f, 0.0f),	XMFLOAT3(1.0f, 1.0f, 1.0f), 5 },
	{ XMFLOAT3(0.0f, 5.0f, 10.0f), XMFLOAT3(0.0f, XM_PI * 0.0f, 0.0f),	XMFLOAT3(1.0f, 1.0f, 1.0f), 5 },
	{ XMFLOAT3(0.0f, 0.0f, 10.0f), XMFLOAT3(0.0f, XM_PI * 0.0f, 0.0f),	XMFLOAT3(1.0f, 1.0f, 1.0f),  0 },

};
////////////////////////////////////
//////////////////////////
////NK�זE�U�����[�V�����f�[�^
//////////////////////////
static INTERPOLATION_DATA NK_Attack[] = {	// pos, rot, scl, frame
	{ XMFLOAT3(0.0f, -5.0f, 0.0f), XMFLOAT3(0.0f, XM_PI * -0.5f, 0.0f),	XMFLOAT3(0.0f, 0.0f, 0.0f), 75 },
	{ XMFLOAT3(10.0f,-5.0f, 0.0f), XMFLOAT3(0.0f, XM_PI * -0.5f, 0.0f),	XMFLOAT3(0.0f, 0.0f, 0.0f), 5 },
	{ XMFLOAT3(0.0f, -5.0f, 0.0f), XMFLOAT3(0.0f, XM_PI * -0.5f, 0.0f),	XMFLOAT3(0.0f, 0.0f, 0.0f),  0 },
};
//////////////////////////
////NK�זE�ҋ@���[�V�����f�[�^
static INTERPOLATION_DATA NK_Standby[] = {	// pos, rot, scl, frame
	{ XMFLOAT3(0.0f, -5.0f, 0.0f), XMFLOAT3(0.0f,XM_PI * -0.5f, 0.0f),	XMFLOAT3(0.0f, 0.0f, 0.0f), 600 },
	{ XMFLOAT3(0.0f, -5.0f, 0.0f), XMFLOAT3(0.0f,XM_PI * -2.5f, 0.0f),	XMFLOAT3(0.0f, 0.0f, 0.0f), 0 },
};

////////////////////////////////////
//////////////////////////
////�D����U�����[�V�����f�[�^
//////////////////////////
static INTERPOLATION_DATA Kouen_Attack[] = {	// pos, rot, scl, frame
	{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, XM_PI * -0.5f, 0.0f),	XMFLOAT3(0.0f, 0.0f, 0.0f), 90 },
	{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, XM_PI * -0.5f, 0.0f),	XMFLOAT3(0.0f, 0.0f, 0.0f),  0 },
};
static INTERPOLATION_DATA Kouen_Arm_Attack[] = {	// pos, rot, scl, frame
	{ XMFLOAT3(0.0f, 0.0f, 15.0f), XMFLOAT3(XM_PI * 6.0f, XM_PI * 0.0f, 0.0f),	XMFLOAT3(1.0f, 1.0f, 1.0f), 85 },
	{ XMFLOAT3(0.0f, 0.0f, 15.0f), XMFLOAT3(0.0f, XM_PI * 0.0f, 0.0f),	XMFLOAT3(1.0f, 1.0f, 1.0f), 5 },
	{ XMFLOAT3(0.0f, 0.0f, 15.0f), XMFLOAT3(0.0f, XM_PI * 0.0f, 0.0f),	XMFLOAT3(1.0f, 1.0f, 1.0f),  0 },
};
static INTERPOLATION_DATA Kouen_Arm2_Attack[] = {	// pos, rot, scl, frame
	{ XMFLOAT3(0.0f, 0.0f, -15.0f), XMFLOAT3(XM_PI * 6.0f, XM_PI * 0.0f, 0.0f),	XMFLOAT3(1.0f, 1.0f, 1.0f), 85 },
	{ XMFLOAT3(0.0f, 0.0f, -15.0f), XMFLOAT3(0.0f, XM_PI * 0.0f, 0.0f),	XMFLOAT3(1.0f, 1.0f, 1.0f), 5 },
	{ XMFLOAT3(0.0f, 0.0f, -15.0f), XMFLOAT3(0.0f, XM_PI * 0.0f, 0.0f),	XMFLOAT3(1.0f, 1.0f, 1.0f),  0 },
};
//////////////////////////
////�D����ҋ@���[�V�����f�[�^
static INTERPOLATION_DATA Kouen_Standby[] = {	// pos, rot, scl, frame
	{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f,XM_PI * -0.5f, 0.0f),	XMFLOAT3(0.0f, 0.0f, 0.0f), 60 },
	{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f,XM_PI * -0.5f, 0.0f),	XMFLOAT3(0.0f, 0.0f, 0.0f), 0 },
};
static INTERPOLATION_DATA Kouen_Arm_Standby[] = {	// pos, rot, scl, frame
	{ XMFLOAT3(0.0f, 0.0f, 15.0f), XMFLOAT3(-XM_PI * 2.0f, XM_PI * 0.0f, 0.0f),	XMFLOAT3(1.0f, 1.0f, 1.0f), 120 },
	{ XMFLOAT3(0.0f, 0.0f, 15.0f), XMFLOAT3(0.0f, XM_PI * 0.0f, 0.0f),	XMFLOAT3(1.0f, 1.0f, 1.0f),  0 },
};
static INTERPOLATION_DATA Kouen_Arm2_Standby[] = {	// pos, rot, scl, frame
	{ XMFLOAT3(0.0f, 0.0f, -15.0f), XMFLOAT3(-XM_PI * 2.0f, XM_PI * 0.0f, 0.0f),	XMFLOAT3(1.0f, 1.0f, 1.0f), 120 },
	{ XMFLOAT3(0.0f, 0.0f, -15.0f), XMFLOAT3(0.0f, XM_PI * 0.0f, 0.0f),	XMFLOAT3(1.0f, 1.0f, 1.0f),  0 },
};
