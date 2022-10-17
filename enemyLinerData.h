//=============================================================================
//
// �o�g�����̐��`�⊮�f�[�^(�G) [enemyLinerData.h]
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
////���F�u�h�E���ۃ��[�V�����f�[�^
//////////////////////////
////
// �{�̍U�����[�V����
////
static INTERPOLATION_DATA grape_Attack[] = {	// pos, rot, scl, frame
	{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),		XMFLOAT3(0.0f, 0.0f, 0.0f), 70 },
	{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),		XMFLOAT3(1.0f, 1.0f, 1.0f), 5 },
	{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),		XMFLOAT3(0.0f, 0.0f, 0.0f), 15 },
	{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),		XMFLOAT3(0.0f, 0.0f, 0.0f),  0 },
};
// �p�[�c1�̍U�����[�V����
static INTERPOLATION_DATA grape_Parts001Attack[] = {	// pos, rot, scl, frame
	{ XMFLOAT3(0.0f, 0.0f,  0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),		XMFLOAT3(1.0f, 1.0f, 1.0f), 35 },
	{ XMFLOAT3(13.5f,-3.0f,  5.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),		XMFLOAT3(0.25f, 0.25f, 0.25f), 40 },
	{ XMFLOAT3(13.5f,-3.0f,  5.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),		XMFLOAT3(0.25f, 0.25f, 0.25f), 5 },
	{ XMFLOAT3(13.5f,-3.0f, 25.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),		XMFLOAT3(1.5f, 1.5f, 1.5f), 5 },
	{ XMFLOAT3(13.5f,-3.0f,  5.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),		XMFLOAT3(1.0f, 1.0f, 1.0f), 5 },
	{ XMFLOAT3(0.0f, 0.0f,  0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),		XMFLOAT3(1.0f, 1.0f, 1.0f),  0 },
};
//�p�[�c2
static INTERPOLATION_DATA grape_Parts002Attack[] = {	// pos, rot, scl, frame
	{ XMFLOAT3(0.0f, 0.0f,  0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),		XMFLOAT3(1.0f, 1.0f, 1.0f), 35 },
	{ XMFLOAT3(3.5f,-5.0f,  0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),		XMFLOAT3(0.25f, 0.25f, 0.25f), 40 },
	{ XMFLOAT3(3.5f,-5.0f,  0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),		XMFLOAT3(0.25f, 0.25f, 0.25f), 5 },
	{ XMFLOAT3(3.5f,-5.0f, 20.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),		XMFLOAT3(1.5f, 1.5f, 1.5f), 5 },
	{ XMFLOAT3(3.5f,-5.0f,  0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),		XMFLOAT3(1.0f, 1.0f, 1.0f), 5 },
	{ XMFLOAT3(0.0f, 0.0f,  0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),		XMFLOAT3(1.0f, 1.0f, 1.0f),  0 },

};
//�p�[�c3
static INTERPOLATION_DATA grape_Parts003Attack[] = {	// pos, rot, scl, frame
	{ XMFLOAT3(0.0f, 0.0f,  0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),		XMFLOAT3(1.0f, 1.0f, 1.0f), 35 },
	{ XMFLOAT3(-3.5f,-5.0f,  0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),		XMFLOAT3(0.25f, 0.25f, 0.25f), 40 },
	{ XMFLOAT3(-3.5f,-5.0f,  0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),		XMFLOAT3(0.25f, 0.25f, 0.25f), 5 },
	{ XMFLOAT3(-3.5f,-5.0f, 20.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),		XMFLOAT3(1.5f, 1.5f, 1.5f), 5 },
	{ XMFLOAT3(-3.5f,-5.0f,  0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),		XMFLOAT3(1.0f, 1.0f, 1.0f), 5 },
	{ XMFLOAT3(0.0f, 0.0f,  0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),		XMFLOAT3(1.0f, 1.0f, 1.0f),  0 },
};
////
// �{�̈ړ������[�V����
////
static INTERPOLATION_DATA grape_Move[] = {	// pos, rot, scl, frame
	{ XMFLOAT3(0.0f,  0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),		XMFLOAT3(0.0f, 0.0f, 0.0f), 30 },
	{ XMFLOAT3(0.0f, 20.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),		XMFLOAT3(0.0f, 0.0f, 0.0f), 30 },
	{ XMFLOAT3(0.0f,  0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),		XMFLOAT3(0.0f, 0.0f, 0.0f),  0 },
};
// �p�[�c1
static INTERPOLATION_DATA grape_Parts001Move[] = {	// pos, rot, scl, frame
	{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),			XMFLOAT3(1.0f, 1.0f, 1.0f), 60 },
	{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, -2.0f*XM_PI, 0.0f),	XMFLOAT3(1.0f, 1.0f, 1.0f),  0 },

};
// �p�[�c2
static INTERPOLATION_DATA grape_Parts002Move[] = {	// pos, rot, scl, frame
	{ XMFLOAT3(0.0f,   0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),			XMFLOAT3(1.0f, 1.0f, 1.0f), 30 },
	{ XMFLOAT3(0.0f, -20.0f, 0.0f), XMFLOAT3(0.0f, XM_PI, 0.0f),		XMFLOAT3(1.0f, 1.0f, 1.0f), 30 },
	{ XMFLOAT3(0.0f,   0.0f, 0.0f), XMFLOAT3(0.0f, 2.0f*XM_PI, 0.0f),	XMFLOAT3(1.0f, 1.0f, 1.0f),  0 },

};
// �p�[�c3
static INTERPOLATION_DATA grape_Parts003Move[] = {	// pos, rot, scl, frame
	{ XMFLOAT3(0.0f,   0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),			XMFLOAT3(1.0f, 1.0f, 1.0f), 30 },
	{ XMFLOAT3(0.0f, -20.0f, 0.0f), XMFLOAT3(0.0f, XM_PI, 0.0f),		XMFLOAT3(1.0f, 1.0f, 1.0f), 30 },
	{ XMFLOAT3(0.0f,   0.0f, 0.0f), XMFLOAT3(0.0f, 2.0f*XM_PI, 0.0f),	XMFLOAT3(1.0f, 1.0f, 1.0f),  0 },

};
////////////////////////////////////

//////////////////////////
////A�Q���n�A�ۃ��[�V�����f�[�^
//////////////////////////
////
// �{�̍U�����[�V����
////
static INTERPOLATION_DATA strept_Attack[] = {	// pos, rot, scl, frame
	{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),      XMFLOAT3(0.0f, 0.0f, 0.0f), 10, },
	{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI*0.25f, 0.0f, 0.0f),	   XMFLOAT3(0.0f, 0.0f, 0.0f), 50 },
	{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),      XMFLOAT3(0.0f, 0.0f, 0.0f), 60 },

};
// �p�[�c1�̍U�����[�V����
static INTERPOLATION_DATA strept_headAt[] = {	// pos, rot, scl, frame
	{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),      XMFLOAT3(1.0f, 1.0f, 1.0f), 10, },
	{ XMFLOAT3(0.0f, -30.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),	   XMFLOAT3(1.375f, 1.375f, 1.375f), 50 },
	{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),      XMFLOAT3(1.0f, 1.0f, 1.0f), 60 },

};
//�p�[�c2
static INTERPOLATION_DATA strept_neckAt[] = {	// pos, rot, scl, frame
	{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),      XMFLOAT3(1.0f, 1.0f, 1.0f), 10, },
	{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),	   XMFLOAT3(1.0f, 1.0f, 1.0f), 50 },
	{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),      XMFLOAT3(1.0f, 1.0f, 1.0f), 60 },

};
//�p�[�c3
static INTERPOLATION_DATA strept_tailAt[] = {	// pos, rot, scl, frame
	{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),      XMFLOAT3(1.0f, 1.0f, 1.0f), 10, },
	{ XMFLOAT3(0.0f, 27.0f, -19.0f), XMFLOAT3(-XM_PI * 0.375f, 0.0f, 0.0f),	   XMFLOAT3(1.0f, 1.0f, 1.0f), 50 },
	{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),      XMFLOAT3(1.0f, 1.0f, 1.0f), 60 },

};
////
// �{�̈ړ������[�V����
////
static INTERPOLATION_DATA strept_Move[] = {	// pos, rot, scl, frame
	{ XMFLOAT3(0.0f, 0.0f, -5.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),      XMFLOAT3(0.0f, 0.0f, 0.0f), 30, },
	{ XMFLOAT3(0.0f, 0.0f, 5.0f), XMFLOAT3(XM_PI*0.125f, 0.0f, 0.0f),	   XMFLOAT3(0.0f, 0.0f, 0.0f), 30 },
	{ XMFLOAT3(0.0f, 0.0f, -5.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),      XMFLOAT3(0.0f, 0.0f, 0.0f), 0 },

};
// �p�[�c1
static INTERPOLATION_DATA strept_headMv[] = {	// pos, rot, scl, frame
	{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),      XMFLOAT3(1.0f, 1.0f, 1.0f), 30, },
	{ XMFLOAT3(0.0f, 30.0f, -40.0f), XMFLOAT3(XM_PI*0.125f, 0.0f, 0.0f),	   XMFLOAT3(1.0f, 1.0f, 1.0f), 30 },
	{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),      XMFLOAT3(1.0f, 1.0f, 1.0f), 0 },

};
// �p�[�c2
static INTERPOLATION_DATA strept_neckMv[] = {	// pos, rot, scl, frame
	{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),      XMFLOAT3(1.0f, 1.0f, 1.0f), 30, },
	{ XMFLOAT3(0.0f, 40.0f,40.0f), XMFLOAT3(-XM_PI * 0.25f,0.0f ,0.0f),	   XMFLOAT3(1.0f, 1.0f, 1.0f), 30 },
	{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),      XMFLOAT3(1.0f, 1.0f, 1.0f), 0 },

};
// �p�[�c3
static INTERPOLATION_DATA strept_tailMv[] = {	// pos, rot, scl, frame
	{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),      XMFLOAT3(1.0f, 1.0f, 1.0f), 30, },
	{ XMFLOAT3(0.0f, 25.0f, -15.0f), XMFLOAT3(-XM_PI * 0.25f, 0.0f, 0.0f),	XMFLOAT3(1.0f, 1.0f, 1.0f), 30 },
	{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),      XMFLOAT3(1.0f, 1.0f, 1.0f), 0 },

};

//////////////////////////
////�Δ^�ۃ��[�V�����f�[�^
//////////////////////////
////
// �{�̍U�����[�V����
////
static INTERPOLATION_DATA ryoku_Attack[] = {	// pos, rot, scl, frame
	{ XMFLOAT3(0.0f, -5.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),      XMFLOAT3(0.0f, 0.0f, 0.0f), 5, },
	{ XMFLOAT3(0.0f, 10.0f, 0.0f), XMFLOAT3(-XM_PI * 0.25f, 0.0f, 0.0f),	   XMFLOAT3(0.0f, 0.0f, 0.0f), 5 },
	{ XMFLOAT3(0.0f, 10.0f, 0.0f), XMFLOAT3(-XM_PI * 0.25f, 0.0f, -XM_PI * 0.25f),	   XMFLOAT3(0.0f, 0.0f, 0.0f), 5 },
	{ XMFLOAT3(0.0f, 10.0f, 0.0f), XMFLOAT3(-XM_PI * 0.25f, 0.0f,  XM_PI * 0.25f),	   XMFLOAT3(0.0f, 0.0f, 0.0f), 5 },
	{ XMFLOAT3(0.0f, 10.0f, 0.0f), XMFLOAT3(-XM_PI * 0.25f, 0.0f, -XM_PI * 0.25f),	   XMFLOAT3(0.0f, 0.0f, 0.0f), 5 },
	{ XMFLOAT3(0.0f, 10.0f, 0.0f), XMFLOAT3(-XM_PI * 0.25f, 0.0f,  XM_PI * 0.25f),	   XMFLOAT3(0.0f, 0.0f, 0.0f), 5 },
		{ XMFLOAT3(0.0f, -5.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),      XMFLOAT3(0.0f, 0.0f, 0.0f), 5, },
	{ XMFLOAT3(0.0f, -5.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),      XMFLOAT3(0.0f, 0.0f, 0.0f), 25, },
	{ XMFLOAT3(0.0f, -5.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),      XMFLOAT3(0.0f, 0.0f, 0.0f), 0 },

};
// �p�[�c1�̍U�����[�V����
static INTERPOLATION_DATA ryoku_leftAt[] = {	// pos, rot, scl, frame
	{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),      XMFLOAT3(1.0f, 1.0f, 1.0f), 10, },
	{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),	   XMFLOAT3(1.0f, 1.0f, 1.0f), 50 },
	{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),      XMFLOAT3(1.0f, 1.0f, 1.0f), 0 },

};
//�p�[�c2
static INTERPOLATION_DATA ryoku_rightAt[] = {	// pos, rot, scl, frame
	{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),      XMFLOAT3(1.0f, 1.0f, 1.0f), 10, },
	{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),	   XMFLOAT3(1.0f, 1.0f, 1.0f), 50 },
	{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),      XMFLOAT3(1.0f, 1.0f, 1.0f), 0 },

};
////
// �ړ����[�V����
////
static INTERPOLATION_DATA ryoku_Move[] = {	// pos, rot, scl, frame
	{ XMFLOAT3(0.0f, -5.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),      XMFLOAT3(0.0f, 0.0f, 0.0f), 10, },
	{ XMFLOAT3(0.0f, -5.0f, 0.0f), XMFLOAT3(XM_PI*0.0f, 0.0f, 0.0f),	   XMFLOAT3(0.0f, 0.0f, 0.0f), 50 },
	{ XMFLOAT3(0.0f, -5.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),      XMFLOAT3(0.0f, 0.0f, 0.0f), 60 },

};
// �p�[�c1�̍U�����[�V����
static INTERPOLATION_DATA ryoku_leftMv[] = {	// pos, rot, scl, frame
	{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(-XM_PI * 0.25f, 0.0f, 0.0f),      XMFLOAT3(1.0f, 1.0f, 1.0f), 10, },
	{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(-XM_PI * 0.5f, 0.0f, 0.0f),	   XMFLOAT3(1.0f, 1.0f, 1.0f), 50 },
	{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(-XM_PI * 0.25f, 0.0f, 0.0f),      XMFLOAT3(1.0f, 1.0f, 1.0f), 0 },

};
//�p�[�c2
static INTERPOLATION_DATA ryoku_rightMv[] = {	// pos, rot, scl, frame
	{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(-XM_PI * 0.25f, 0.0f, 0.0f),      XMFLOAT3(1.0f, 1.0f, 1.0f), 10, },
	{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(-XM_PI * 0.5f, 0.0f, 0.0f),	   XMFLOAT3(1.0f, 1.0f, 1.0f), 50 },
	{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(-XM_PI * 0.25f, 0.0f, 0.0f),      XMFLOAT3(1.0f, 1.0f, 1.0f), 0 },

};

//////////////////////////
////�C���t���G���U���[�V�����f�[�^
//////////////////////////
////
// �{�̍U�����[�V����
////
static INTERPOLATION_DATA infule_Attack[] = {	// pos, rot, scl, frame
	{ XMFLOAT3(7.0f, -4.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),		XMFLOAT3(-0.4f, -0.5f, -0.5f), 45 },
	{ XMFLOAT3(7.0f, -4.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),		XMFLOAT3(-0.25f, -0.375f, -0.375f),  10 },
	{ XMFLOAT3(7.0f, -4.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),		XMFLOAT3(-0.4f, -0.5f, -0.5f), 5 },
	{ XMFLOAT3(7.0f, -4.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),		XMFLOAT3(-0.4f, -0.5f, -0.5f), 0 },
};
// �p�[�c1�̍U�����[�V����
static INTERPOLATION_DATA infule_Parts001Attack[] = {	// pos, rot, scl, frame
	{ XMFLOAT3(43.0f,-25.0f, -25.0f),  XMFLOAT3(0.0f, 0.0f, 0.0f),		XMFLOAT3(1.0f, 1.0f, 1.0f), 8 },
	{ XMFLOAT3(43.0f,-25.0f, -25.0f),  XMFLOAT3(0.0f, 0.0f, 0.0f),		XMFLOAT3(1.0f, 1.0f, 1.0f), 2 },
	{ XMFLOAT3(43.0f, 25.0f,  25.0f),  XMFLOAT3(0.0f, 2.0f*XM_PI, 0.0f),		XMFLOAT3(1.0f, 1.0f, 1.0f), 8 },
	{ XMFLOAT3(43.0f, 25.0f,  25.0f),  XMFLOAT3(0.0f, 0.0f, 0.0f),		XMFLOAT3(1.0f, 1.0f, 1.0f), 2 },
	{ XMFLOAT3(43.0f, 15.0f, -15.0f),  XMFLOAT3(0.0f, 2.0f*XM_PI, 0.0f),		XMFLOAT3(1.5f, 1.5f, 1.5f), 8 },
	{ XMFLOAT3(43.0f, 15.0f, -15.0f),  XMFLOAT3(0.0f, 0.0f, 0.0f),		XMFLOAT3(1.5f, 1.5f, 1.5f), 10 },
	{ XMFLOAT3(43.0f, 15.0f, -25.0f),  XMFLOAT3(0.0f, 0.0f, 0.0f),		XMFLOAT3(1.5f, 1.5f, 1.5f), 2 },
	{ XMFLOAT3(-7.0f, 15.0f,  15.0f),  XMFLOAT3(0.0f, 0.0f, 0.0f),		XMFLOAT3(1.5f, 1.5f, 1.5f), 5 },
	{ XMFLOAT3(43.0f,-15.0f, -25.0f),  XMFLOAT3(0.0f, 0.0f, 0.0f),		XMFLOAT3(1.0f, 1.0f, 1.0f), 15 },
	{ XMFLOAT3(43.0f,-15.0f, -25.0f),  XMFLOAT3(0.0f, 0.0f, 0.0f),		XMFLOAT3(1.0f, 1.0f, 1.0f), 0 },
};
//�p�[�c2
static INTERPOLATION_DATA infule_Parts002Attack[] = {	// pos, rot, scl, frame
	{ XMFLOAT3(-57.0f, 25.0f,  25.0f),  XMFLOAT3(0.0f, 0.0f, 0.0f),		XMFLOAT3(1.0f, 1.0f, 1.0f), 8 },
	{ XMFLOAT3(-57.0f, 25.0f,  25.0f),  XMFLOAT3(0.0f, 0.0f, 0.0f),		XMFLOAT3(1.0f, 1.0f, 1.0f), 2 },
	{ XMFLOAT3(-57.0f,-25.0f, -25.0f),  XMFLOAT3(0.0f, 2.0f*XM_PI, 0.0f),		XMFLOAT3(1.0f, 1.0f, 1.0f), 8 },
	{ XMFLOAT3(-57.0f,-25.0f, -25.0f),  XMFLOAT3(0.0f, 0.0f, 0.0f),		XMFLOAT3(1.0f, 1.0f, 1.0f), 2 },
	{ XMFLOAT3(-57.0f, 15.0f, -15.0f),  XMFLOAT3(0.0f, 2.0f*XM_PI, 0.0f),		XMFLOAT3(1.5f, 1.5f, 1.5f), 8 },
	{ XMFLOAT3(-57.0f, 15.0f, -15.0f),  XMFLOAT3(0.0f, 0.0f, 0.0f),		XMFLOAT3(1.5f, 1.5f, 1.5f), 10 },
	{ XMFLOAT3(-57.0f, 15.0f, -25.0f),  XMFLOAT3(0.0f, 0.0f, 0.0f),		XMFLOAT3(1.5f, 1.5f, 1.5f), 2 },
	{ XMFLOAT3(-7.0f, 15.0f,  15.0f),  XMFLOAT3(0.0f, 0.0f, 0.0f),		XMFLOAT3(1.5f, 1.5f, 1.5f), 5 },
	{ XMFLOAT3(-57.0f, 15.0f, -25.0f),  XMFLOAT3(0.0f, 0.0f, 0.0f),		XMFLOAT3(1.0f, 1.0f, 1.0f), 15 },
	{ XMFLOAT3(-57.0f, 15.0f, -25.0f),  XMFLOAT3(0.0f, 0.0f, 0.0f),		XMFLOAT3(1.0f, 1.0f, 1.0f), 0 },
};
////
// �{�̈ړ������[�V����
////
static INTERPOLATION_DATA infule_Move[] = {	// pos, rot, scl, frame
	{ XMFLOAT3(-7.0f,   0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),		XMFLOAT3(-0.4f, -0.5f, -0.5f), 30 },
	{ XMFLOAT3(-7.0f,   0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),		XMFLOAT3(-0.25f, -0.375f, -0.375f), 30 },
	{ XMFLOAT3(-7.0f,   0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),		XMFLOAT3(-0.4f, -0.5f, -0.5f), 0 },
};
// �p�[�c1
static INTERPOLATION_DATA infule_Parts001Move[] = {	// pos, rot, scl, frame
	{ XMFLOAT3(43.0f, -0.0f, -25.0f),  XMFLOAT3(0.0f, 0.0f, 0.0f),		XMFLOAT3(1.0f, 1.0f, 1.0f), 15 },
	{ XMFLOAT3(43.0f,  25.0f, -25.0f),  XMFLOAT3(0.0f, 0.5f*XM_PI, 0.0f),	XMFLOAT3(1.0f, 1.0f, 1.0f),  15 },
	{ XMFLOAT3(43.0f,  0.0f, -25.0f),  XMFLOAT3(0.0f, 1.0f*XM_PI, 0.0f),	XMFLOAT3(1.0f, 1.0f, 1.0f), 15 },
	{ XMFLOAT3(43.0f, -25.0f, -25.0f),  XMFLOAT3(0.0f, 1.5f*XM_PI, 0.0f),	XMFLOAT3(1.0f, 1.0f, 1.0f),  15 },
	{ XMFLOAT3(43.0f, -0.0f, -25.0f),  XMFLOAT3(0.0f, 2.0f*XM_PI, 0.0f),	XMFLOAT3(1.0f, 1.0f, 1.0f), 0 },

};
// �p�[�c2
static INTERPOLATION_DATA infule_Parts002Move[] = {	// pos, rot, scl, frame
	{ XMFLOAT3(-57.0f, -0.0f,-30.0f), XMFLOAT3(0.0f, 0.0f, 0.0f),		XMFLOAT3(1.0f, 1.0f, 1.0f), 15 },
	{ XMFLOAT3(-57.0f, -25.0f,-30.0f), XMFLOAT3(0.0f, 0.5f*XM_PI, 0.0f),XMFLOAT3(1.0f, 1.0f, 1.0f), 15 },
	{ XMFLOAT3(-57.0f,  0.0f,-30.0f), XMFLOAT3(0.0f, 1.0f*XM_PI, 0.0f),XMFLOAT3(1.0f, 1.0f, 1.0f), 15 },
	{ XMFLOAT3(-57.0f,  25.0f,-30.0f), XMFLOAT3(0.0f, 1.5f*XM_PI, 0.0f),XMFLOAT3(1.0f, 1.0f, 1.0f), 15 },
	{ XMFLOAT3(-57.0f, -0.0f,-30.0f), XMFLOAT3(0.0f, 2.0f*XM_PI, 0.0f),XMFLOAT3(1.0f, 1.0f, 1.0f),  0 },

};

////////////////////////////////////

static MOVERINE		moveTbl[] = { XMFLOAT3(300.0f, 0.0f, 100.0f), XMFLOAT3(0.0f, 0.0f, 100.0f) };
static MOVERINE		FirstmoveTbl[] = {
	XMFLOAT3(350.0f, 0.0f, 100.0f), XMFLOAT3(300.0f, 0.0f, 100.0f), XMFLOAT3(300.0f, 0.0f, 150.0f),
	XMFLOAT3(200.0f, 0.0f, 150.0f), XMFLOAT3(200.0f, 0.0f, 100.0f), XMFLOAT3(150.0f, 0.0f, 100.0f),
	XMFLOAT3(150.0f, 0.0f, 50.0f),XMFLOAT3(50.0f, 0.0f, 50.0f), XMFLOAT3(50.0f, 0.0f, 100.0f),
	XMFLOAT3(0.0f, 0.0f, 100.0f)
};
static MOVERINE		FirstmoveTbl2[] = {
	XMFLOAT3(350.0f, 0.0f, 100.0f), XMFLOAT3(0.0f, 0.0f, 100.0f),
};

static MOVERINE		SecondmoveTbl[] = {
	XMFLOAT3(350.0f, 0.0f, 100.0f), XMFLOAT3(300.0f, 0.0f, 100.0f), XMFLOAT3(300.0f, 0.0f, 50.0f),
	XMFLOAT3(200.0f, 0.0f, 50.0f), XMFLOAT3(200.0f, 0.0f, 100.0f), XMFLOAT3(150.0f, 0.0f, 100.0f),
	XMFLOAT3(150.0f, 0.0f, 150.0f),XMFLOAT3(50.0f, 0.0f, 150.0f), XMFLOAT3(50.0f, 0.0f, 100.0f),
	XMFLOAT3(0.0f, 0.0f, 100.0f)
};
static MOVERINE		ThirdmoveTbl[] = {
	XMFLOAT3(350.0f, 0.0f, 100.0f), XMFLOAT3(200.0f, 0.0f, 100.0f), XMFLOAT3(200.0f, 0.0f, 50.0f),
	XMFLOAT3(150.0f, 0.0f, 50.0f), XMFLOAT3(150.0f, 0.0f, 150.0f), XMFLOAT3(100.0f, 0.0f, 150.0f),
	XMFLOAT3(100.0f, 0.0f, 50.0f), XMFLOAT3(50.0f, 0.0f, 50.0f), XMFLOAT3(50.0f, 0.0f, 100.0f),
	XMFLOAT3(0.0f, 0.0f, 100.0f),
};
static MOVERINE		ForthmoveTbl[] = {
	XMFLOAT3(350.0f, 0.0f, 100.0f), XMFLOAT3(300.0f, 0.0f, 100.0f), XMFLOAT3(300.0f, 0.0f, 250.0f),
	XMFLOAT3(150.0f, 0.0f, 250.0f), XMFLOAT3(150.0f, 0.0f, 200.0f), XMFLOAT3(100.0f, 0.0f, 200.0f),
	XMFLOAT3(100.0f, 0.0f, 50.0f), XMFLOAT3(50.0f, 0.0f, 50.0f), XMFLOAT3(50.0f, 0.0f, 100.0f),
	XMFLOAT3(0.0f, 0.0f, 100.0f),
};

#pragma once
