//=============================================================================
//
// �J�������� [camera.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "camera.h"
#include "game.h"
#include "player.h"
#include "time.h"
#include "debugproc.h"
#include "obstacle.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
//#define	POS_X_CAM		(0.0f)			// �J�����̏����ʒu(X���W)
//#define	POS_Y_CAM		(200.0f)		// �J�����̏����ʒu(Y���W)
//#define	POS_Z_CAM		(-400.0f)		// �J�����̏����ʒu(Z���W)


#define	VIEW_ANGLE		(XMConvertToRadians(45.0f))						// �r���[���ʂ̎���p
#define	VIEW_ASPECT		((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT)	// �r���[���ʂ̃A�X�y�N�g��	
#define	VIEW_NEAR_Z		(10.0f)											// �r���[���ʂ�NearZ�l
#define	VIEW_FAR_Z		(10000.0f)										// �r���[���ʂ�FarZ�l
#define INTERVAL		(10)

typedef enum
{
	RUN,
	BETWEEN,
	WALK
}CAMERA_PHASE;
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static CAMERA			g_Cam;		// �J�����f�[�^

static int				vibration_inv = 0;
static int				g_ViewPortType = TYPE_FULL_SCREEN;
//=============================================================================
// ����������
//=============================================================================
void InitCamera(void)
{
	g_Cam.pos = { 0.0f, 80.0f, 350.0f };
	g_Cam.at = { 0.0f, 0.0f, 0.0f };
	g_Cam.atPos = { 0.0f, 0.0f, 0.0f };
	g_Cam.up  = { 0.0f, 1.0f, 0.0f };
	g_Cam.rot = { 0.0f, 0.0f, 0.0f };

	// ���_�ƒ����_�̋������v�Z
	float vx, vz;
	vx = g_Cam.pos.x - g_Cam.at.x;
	vz = g_Cam.pos.z - g_Cam.at.z;
	g_Cam.len = sqrtf(vx * vx + vz * vz);
	
	g_Cam.tbl_adr = NULL;		// �Đ�����A�j���f�[�^�̐擪�A�h���X���Z�b�g
	g_Cam.move_time = 0.0f;	// ���`��ԗp�̃^�C�}�[���N���A
	g_Cam.tbl_size = NULL;		// �Đ�����A�j���f�[�^�̃��R�[�h�����Z�b�g

	// �r���[�|�[�g�^�C�v�̏�����
	g_ViewPortType = TYPE_FULL_SCREEN;
	vibration_inv = 0;
}


//=============================================================================
// �J�����̏I������
//=============================================================================
void UninitCamera(void)
{

}


//=============================================================================
// �J�����̍X�V����
//=============================================================================
void UpdateCamera(void)
{
	XMFLOAT3 pos, pos2;
	PLAYER *player = GetPlayer();
	pos2 = player[0].pos;
	const float dist = -30.0f;
	pos.x = pos2.x + sinf(g_Cam.rot.y)*dist;
	pos.y =pos2.y + 30.0f;
	pos.z = pos2.z + cosf(g_Cam.rot.y)*dist;
	g_Cam.pos = pos;
#ifdef _DEBUG	//�f�o�b�O�p�̃J��������B���[�h�֌W�Ȃ���������
	//if (GetKeyboardPress(DIK_Q))
	//{
	//	g_Cam.rot.y -= VALUE_ROTATE_CAMERA;
	//	if (g_Cam.rot.y < -XM_PI)
	//	{
	//		g_Cam.rot.y += XM_PI * 2.0f;
	//	}
	//}
	//else if (GetKeyboardPress(DIK_E))
	//{
	//	g_Cam.rot.y += VALUE_ROTATE_CAMERA;
	//	if (g_Cam.rot.y > XM_PI)
	//	{
	//		g_Cam.rot.y -= XM_PI * 2.0f;
	//	}

	//}
	//if (GetKeyboardPress(DIK_UP))
	//{
	//	if (g_Cam.rot.x < XM_PI * 0.2f)
	//		g_Cam.rot.x += XM_PI * 0.004f;
	//}
	//else if (GetKeyboardPress(DIK_DOWN))
	//{
	//	if (g_Cam.rot.x > 0.0f)
	//		g_Cam.rot.x -= XM_PI * 0.004f;
	//}


#endif

	if (g_Cam.tbl_adr != NULL)
	{
		// �ړ�����
		int		index = (int)g_Cam.move_time;
		float	time = g_Cam.move_time - index;
		int		size = g_Cam.tbl_size;

		float dt = 1.0f / g_Cam.tbl_adr[index].frame;	// 1�t���[���Ői�߂鎞��
		g_Cam.move_time += dt;							// �A�j���[�V�����̍��v���Ԃɑ���

		if (index > (size - 2))	// �S�[�����I�[�o�[���Ă�����A�ŏ��֖߂��B���`��ԃf�[�^������
		{
			g_Cam.move_time = 0.0f;
			index = 0;
			g_Cam.tbl_adr = NULL;
			return;
		}

		// ���W�����߂�	X = StartX + (EndX - StartX) * ���̎���
		XMVECTOR p1 = XMLoadFloat3(&g_Cam.tbl_adr[index + 1].pos);	// ���̏ꏊ
		XMVECTOR p0 = XMLoadFloat3(&g_Cam.tbl_adr[index + 0].pos);	// ���݂̏ꏊ
		XMVECTOR vec = p1 - p0;
		XMStoreFloat3(&g_Cam.pos, p0 + vec * time);

		// ��]�����߂�	R = StartX + (EndX - StartX) * ���̎���
		XMVECTOR r1 = XMLoadFloat3(&g_Cam.tbl_adr[index + 1].rot);	// ���̊p�x
		XMVECTOR r0 = XMLoadFloat3(&g_Cam.tbl_adr[index + 0].rot);	// ���݂̊p�x
		XMVECTOR rot = r1 - r0;
		XMStoreFloat3(&g_Cam.rot, r0 + rot * time);

		// �����_�̕ύX�ʂ����߂� S = StartX + (EndX - StartX) * ���̎���
		XMVECTOR s1 = XMLoadFloat3(&g_Cam.tbl_adr[index + 1].scl);	// ���̒����_
		XMVECTOR s0 = XMLoadFloat3(&g_Cam.tbl_adr[index + 0].scl);	// ���݂̒����_
		XMVECTOR scl = s1 - s0;
		XMStoreFloat3(&g_Cam.atPos, s0 + scl * time);

	}
#ifdef _DEBUG

	PrintDebugProc("\n�J������]y:%f,x:%f\n", g_Cam.rot.y, g_Cam.rot.x);
#endif

}


//=============================================================================
// �J�����̍X�V
//=============================================================================
void SetCamera(void) 
{
	// �r���[�}�g���b�N�X�ݒ�
	XMMATRIX mtxView;
	mtxView = XMMatrixLookAtLH(XMLoadFloat3(&g_Cam.pos), XMLoadFloat3(&g_Cam.at), XMLoadFloat3(&g_Cam.up));
	SetViewMatrix(&mtxView);
	XMStoreFloat4x4(&g_Cam.mtxView, mtxView);

	XMMATRIX mtxInvView;
	mtxInvView = XMMatrixInverse(nullptr, mtxView);
	XMStoreFloat4x4(&g_Cam.mtxInvView, mtxInvView);


	// �v���W�F�N�V�����}�g���b�N�X�ݒ�
	XMMATRIX mtxProjection;
	mtxProjection = XMMatrixPerspectiveFovLH(VIEW_ANGLE, VIEW_ASPECT, VIEW_NEAR_Z, VIEW_FAR_Z);

	SetProjectionMatrix(&mtxProjection);
	XMStoreFloat4x4(&g_Cam.mtxProjection, mtxProjection);

	SetShaderCamera(g_Cam.pos);
}


//=============================================================================
// �J�����̎擾
//=============================================================================
CAMERA *GetCamera(void) 
{
	return &g_Cam;
}

//=============================================================================
// �r���[�|�[�g�̐ݒ�
//=============================================================================
void SetViewPort(int type)
{
	//ID3D11DeviceContext *g_ImmediateContext = GetDeviceContext();
	//D3D11_VIEWPORT vp;

	//g_ViewPortType = type;

	//// �r���[�|�[�g�ݒ�
	//switch (g_ViewPortType)
	//{
	//case TYPE_FULL_SCREEN:
	//case TYPE_LIGHT_SCREEN:
	//	vp.Width = (FLOAT)SCREEN_WIDTH;
	//	vp.Height = (FLOAT)SCREEN_HEIGHT;
	//	vp.MinDepth = 0.0f;
	//	vp.MaxDepth = 1.0f;
	//	vp.TopLeftX = 0;
	//	vp.TopLeftY = 0;
	//	break;

	//case TYPE_LEFT_HALF_SCREEN:
	//	vp.Width = (FLOAT)SCREEN_WIDTH / 2;
	//	vp.Height = (FLOAT)SCREEN_HEIGHT;
	//	vp.MinDepth = 0.0f;
	//	vp.MaxDepth = 1.0f;
	//	vp.TopLeftX = 0;
	//	vp.TopLeftY = 0;
	//	break;

	//case TYPE_RIGHT_HALF_SCREEN:
	//	vp.Width = (FLOAT)SCREEN_WIDTH / 2;
	//	vp.Height = (FLOAT)SCREEN_HEIGHT;
	//	vp.MinDepth = 0.0f;
	//	vp.MaxDepth = 1.0f;
	//	vp.TopLeftX = (FLOAT)SCREEN_WIDTH / 2;
	//	vp.TopLeftY = 0;
	//	break;

	//case TYPE_UP_HALF_SCREEN:
	//	vp.Width = (FLOAT)SCREEN_WIDTH;
	//	vp.Height = (FLOAT)SCREEN_HEIGHT / 2;
	//	vp.MinDepth = 0.0f;
	//	vp.MaxDepth = 1.0f;
	//	vp.TopLeftX = 0;
	//	vp.TopLeftY = 0;
	//	break;

	//case TYPE_DOWN_HALF_SCREEN:
	//	vp.Width = (FLOAT)SCREEN_WIDTH;
	//	vp.Height = (FLOAT)SCREEN_HEIGHT / 2;
	//	vp.MinDepth = 0.0f;
	//	vp.MaxDepth = 1.0f;
	//	vp.TopLeftX = 0;
	//	vp.TopLeftY = (FLOAT)SCREEN_HEIGHT / 2;
	//	break;

	//}
	//g_ImmediateContext->RSSetViewports(1, &vp);

}


int GetViewPortType(void)
{
	return g_ViewPortType;
}


// �J�����̎��_�ƒ����_�Z�b�g
void SetCameraAT(XMFLOAT3 pos)
{
	float random = 0.0f;
	float random_x = 0.0f;
	float random_z = 0.0f;
	if (FallObject::GetFallSwitch() && vibration_inv > 0)
	{
		vibration_inv--;
		random = (float)(rand() % 10) - 5.0f;
		random_x = (float)(rand() % 10) - 5.0f;
		random_z = (float)(rand() % 10) - 5.0f;
		pos.y += random;
		pos.x += random_x;
		pos.z += random_z;
	}

	XMVECTOR v1 = XMLoadFloat3(&pos) - XMLoadFloat3(&g_Cam.at);
	XMVECTOR nor = XMVector3Normalize(v1);
	XMStoreFloat3(&g_Cam.at, XMLoadFloat3(&g_Cam.at) + nor * 1.0f);


	//�����̍��W�ɕύX�ʂ����Z�B
	pos.x += g_Cam.atPos.x;
	pos.y += g_Cam.atPos.y;
	pos.z += g_Cam.atPos.z;
	// �J�����̒����_���Z�b�g
	pos.y += sinf(g_Cam.rot.x) * g_Cam.len;
	g_Cam.at = { pos.x,pos.y,pos.z };
	float dist = FloatClamp(1.0f - sinf(g_Cam.rot.x), 0.98f, 1.0f);
	// �J�����̎��_���J������Y����]�ɑΉ������Ă���
	g_Cam.pos.x = g_Cam.at.x - sinf(g_Cam.rot.y) * g_Cam.len + random_x;
	g_Cam.pos.z = g_Cam.at.z - cosf(g_Cam.rot.y) * g_Cam.len + random_z;
	g_Cam.pos.y -= sinf(g_Cam.rot.x)* g_Cam.len * (sinf(g_Cam.rot.x) * 0.75f) + random;

}

// �J�����̎��_�ƒ����_�Z�b�g
void SetReserveCameraAT(XMFLOAT3 pos, XMFLOAT3 rot)
{
	XMVECTOR v1 = XMLoadFloat3(&pos) - XMLoadFloat3(&g_Cam.at);
	XMVECTOR nor = XMVector3Normalize(v1);
	XMStoreFloat3(&g_Cam.at, XMLoadFloat3(&g_Cam.at) + nor * 1.0f);

	//�����̍��W�ɕύX�ʂ����Z�B
	pos.x += g_Cam.atPos.x;
	pos.y += g_Cam.atPos.y;
	pos.z += g_Cam.atPos.z;
	// �J�����̒����_���Z�b�g
	pos.y += sinf(g_Cam.rot.x) * g_Cam.len;
	g_Cam.at = { pos.x,pos.y,pos.z };
	float dist = FloatClamp(1.0f - sinf(rot.x), 0.98f, 1.0f);
	// �J�����̎��_���J������Y����]�ɑΉ������Ă���
	g_Cam.pos.x = g_Cam.at.x - sinf(rot.y) * g_Cam.len;
	g_Cam.pos.z = g_Cam.at.z - cosf(rot.y) * g_Cam.len;
	g_Cam.pos.y -= sinf(rot.x)* g_Cam.len * (sinf(rot.x) * 0.75f);
}

void SetVibTime(int time)
{
	vibration_inv = time;
}
