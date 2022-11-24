#pragma once
#include "main.h"

//pos,rot,scl,frame
static INTERPOLATION_DATA walk_Body[] = {
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), 45 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), 45 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), 60 },

};
static INTERPOLATION_DATA walk_Head[] = {
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), 45 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.00f), XMFLOAT3(0.0f, 0.0f, 0.0f), 45 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), 60 },

};
static INTERPOLATION_DATA walk_LShoulder[] = {
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.05f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.1f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.1f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.05f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.05f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.1f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.1f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.05f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.05f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.1f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.1f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.05f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.05f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.1f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.1f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), 15 },
};
static INTERPOLATION_DATA walk_RShoulder[] = {
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.05f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.1f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.1f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.05f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.05f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.1f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.1f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.05f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.05f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.1f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.1f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.05f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.05f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.1f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.1f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), 15 },

};
static INTERPOLATION_DATA walk_LArm[] = {
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), 60 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.2f), XMFLOAT3(0.0f, 0.0f, 0.0f), 60 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.1f), XMFLOAT3(0.0f, 0.0f, 0.0f), 60 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.2f), XMFLOAT3(0.0f, 0.0f, 0.0f), 60 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.1f), XMFLOAT3(0.0f, 0.0f, 0.0f), 60 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.2f), XMFLOAT3(0.0f, 0.0f, 0.0f), 60 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.1f), XMFLOAT3(0.0f, 0.0f, 0.0f), 60 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.2f), XMFLOAT3(0.0f, 0.0f, 0.0f), 60 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.1f), XMFLOAT3(0.0f, 0.0f, 0.0f), 60 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.2f), XMFLOAT3(0.0f, 0.0f, 0.0f), 60 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.1f), XMFLOAT3(0.0f, 0.0f, 0.0f), 60 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.2f), XMFLOAT3(0.0f, 0.0f, 0.0f), 60 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.1f), XMFLOAT3(0.0f, 0.0f, 0.0f), 60 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.2f), XMFLOAT3(0.0f, 0.0f, 0.0f), 60 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.1f), XMFLOAT3(0.0f, 0.0f, 0.0f), 60 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.2f), XMFLOAT3(0.0f, 0.0f, 0.0f), 60 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), 60 },

};
static INTERPOLATION_DATA walk_RArm[] = {
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), 60 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.2f), XMFLOAT3(0.0f, 0.0f, 0.0f), 60 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.1f), XMFLOAT3(0.0f, 0.0f, 0.0f), 60 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.2f), XMFLOAT3(0.0f, 0.0f, 0.0f), 60 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.1f), XMFLOAT3(0.0f, 0.0f, 0.0f), 60 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.2f), XMFLOAT3(0.0f, 0.0f, 0.0f), 60 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.1f), XMFLOAT3(0.0f, 0.0f, 0.0f), 60 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.2f), XMFLOAT3(0.0f, 0.0f, 0.0f), 60 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.1f), XMFLOAT3(0.0f, 0.0f, 0.0f), 60 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.2f), XMFLOAT3(0.0f, 0.0f, 0.0f), 60 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.1f), XMFLOAT3(0.0f, 0.0f, 0.0f), 60 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.2f), XMFLOAT3(0.0f, 0.0f, 0.0f), 60 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.1f), XMFLOAT3(0.0f, 0.0f, 0.0f), 60 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.2f), XMFLOAT3(0.0f, 0.0f, 0.0f), 60 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.1f), XMFLOAT3(0.0f, 0.0f, 0.0f), 60 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.2f), XMFLOAT3(0.0f, 0.0f, 0.0f), 60 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), 60 },
};
static INTERPOLATION_DATA walk_LThigh[] = {
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.05f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.075f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.05), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.025), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.05f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.075f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.05f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.025f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.05f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.075f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.05), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.025), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.05f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.075f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.05f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), 15 },

};
static INTERPOLATION_DATA walk_RThigh[] = {
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.05f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.075f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.05), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.025), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.05f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.075f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.05f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.025f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.05f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.075f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.05), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.025), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.05f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.075f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.05f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), 15 },

};
static INTERPOLATION_DATA walk_LFoot[] = {
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.15f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.1f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.05f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.05f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.1f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.15f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.1f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.05f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.15f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.1f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.05f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.05f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.1f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.15f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.1f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.15f), XMFLOAT3(0.0f, 0.0f, 0.0f), 15 },

};

static INTERPOLATION_DATA walk_RFoot[] = {
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.05f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.1f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.15f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.1f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.05f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.05f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.1f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.15f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.05f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.1f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.15f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.1f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.05f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.05f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.1f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), 15 },

};



static INTERPOLATION_DATA run_Body[] = {
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), 30 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.03f), XMFLOAT3(0.0f, 0.0f, 0.0f), 30 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), 30 },

};
static INTERPOLATION_DATA run_Head[] = {
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), 30 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.025f), XMFLOAT3(0.0f, 0.0f, 0.0f), 30 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), 30 },

};
static INTERPOLATION_DATA run_LShoulder[] = {
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.2f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.4f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.2f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.2f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.4f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.2f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.2f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.4f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.2f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.2f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.4f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.2f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.2f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.4f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.2f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.2f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.4f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.2f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },

};
static INTERPOLATION_DATA run_RShoulder[] = {
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.2f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.4f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.2f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.2f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.4f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.2f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.2f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.4f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.2f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.2f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.4f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.2f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.2f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.4f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.2f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.2f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.4f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.2f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },

};
static INTERPOLATION_DATA run_LArm[] = {
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.5f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.4f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.5f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.5f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.4f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.5f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.5f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.4f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.5f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.5f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.4f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.5f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.5f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.4f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.5f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.5f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.4f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.5f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },

};
static INTERPOLATION_DATA run_RArm[] = {
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.5f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.4f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.5f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.5f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.4f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.5f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.5f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.4f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.5f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.5f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.4f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.5f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },

};
static INTERPOLATION_DATA run_LThigh[] = {
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.2f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.3f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.2f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.2f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.3f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.2f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.2f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.3f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.2f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.2f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.3f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.2f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.2f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.3f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.2f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.2f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.3f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.2f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.10f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
};
static INTERPOLATION_DATA run_RThigh[] = {
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.10f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.2f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.3f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.2f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.2f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.3f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.2f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.2f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.3f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.2f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.2f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.3f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.2f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.2f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.3f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.2f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.2f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.3f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.2f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },

};
static INTERPOLATION_DATA run_LFoot[] = {
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.50f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.40f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.30f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.30f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.50f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.40f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.30f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.30f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.50f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.40f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.30f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.30f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.50f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.20f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
};

static INTERPOLATION_DATA run_RFoot[] = {
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.50f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.30f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.40f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.50f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.50f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.30f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.40f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.50f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.50f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.30f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.40f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.50f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * -0.2f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },


};


static INTERPOLATION_DATA stop_Body[] = {
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), 45 },

};
static INTERPOLATION_DATA stop_Head[] = {
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), 45 },

};
static INTERPOLATION_DATA stop_LShoulder[] = {
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
};
static INTERPOLATION_DATA stop_RShoulder[] = {
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
};
static INTERPOLATION_DATA stop_LArm[] = {
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), 60 },

};
static INTERPOLATION_DATA stop_RArm[] = {
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), 60 },
};
static INTERPOLATION_DATA stop_LThigh[] = {
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
};
static INTERPOLATION_DATA stop_RThigh[] = {
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
};
static INTERPOLATION_DATA stop_LFoot[] = {
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
};

static INTERPOLATION_DATA stop_RFoot[] = {
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(XM_PI * 0.0f, XM_PI * 0.0f, XM_PI * 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10 },
};

static INTERPOLATION_DATA* walk_data[] = { walk_Body, walk_Head, walk_LShoulder, walk_RShoulder, walk_LArm, walk_RArm, walk_LThigh, walk_RThigh, walk_LFoot, walk_RFoot };
static int data_size[] = { sizeof(walk_Body) / sizeof(INTERPOLATION_DATA),
							sizeof(walk_Head) / sizeof(INTERPOLATION_DATA),
							sizeof(walk_LShoulder) / sizeof(INTERPOLATION_DATA),
							sizeof(walk_RShoulder) / sizeof(INTERPOLATION_DATA),
							sizeof(walk_LArm) / sizeof(INTERPOLATION_DATA),
							sizeof(walk_RArm) / sizeof(INTERPOLATION_DATA),
							sizeof(walk_LThigh) / sizeof(INTERPOLATION_DATA),
							sizeof(walk_RThigh) / sizeof(INTERPOLATION_DATA),
							sizeof(walk_LFoot) / sizeof(INTERPOLATION_DATA),
							sizeof(walk_RFoot) / sizeof(INTERPOLATION_DATA), };

static INTERPOLATION_DATA* run_data[] = { run_Body, run_Head, run_LShoulder, run_RShoulder, run_LArm, run_RArm, run_LThigh, run_RThigh, run_LFoot, run_RFoot };
static int run_data_size[] = { sizeof(run_Body) / sizeof(INTERPOLATION_DATA),
							sizeof(run_Head) / sizeof(INTERPOLATION_DATA),
							sizeof(run_LShoulder) / sizeof(INTERPOLATION_DATA),
							sizeof(run_RShoulder) / sizeof(INTERPOLATION_DATA),
							sizeof(run_LArm) / sizeof(INTERPOLATION_DATA),
							sizeof(run_RArm) / sizeof(INTERPOLATION_DATA),
							sizeof(run_LThigh) / sizeof(INTERPOLATION_DATA),
							sizeof(run_RThigh) / sizeof(INTERPOLATION_DATA),
							sizeof(run_LFoot) / sizeof(INTERPOLATION_DATA),
							sizeof(run_RFoot) / sizeof(INTERPOLATION_DATA), };

static INTERPOLATION_DATA* stop_data[] = { stop_Body, stop_Head, stop_LShoulder, stop_RShoulder, stop_LArm, stop_RArm, stop_LThigh, stop_RThigh, stop_LFoot, stop_RFoot };
static int stop_data_size[] = { sizeof(stop_Body) / sizeof(INTERPOLATION_DATA),
							sizeof(stop_Head) / sizeof(INTERPOLATION_DATA),
							sizeof(stop_LShoulder) / sizeof(INTERPOLATION_DATA),
							sizeof(stop_RShoulder) / sizeof(INTERPOLATION_DATA),
							sizeof(stop_LArm) / sizeof(INTERPOLATION_DATA),
							sizeof(stop_RArm) / sizeof(INTERPOLATION_DATA),
							sizeof(stop_LThigh) / sizeof(INTERPOLATION_DATA),
							sizeof(stop_RThigh) / sizeof(INTERPOLATION_DATA),
							sizeof(stop_LFoot) / sizeof(INTERPOLATION_DATA),
							sizeof(stop_RFoot) / sizeof(INTERPOLATION_DATA), };