//=============================================================================
//
// �Q�[����ʏ��� [game.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "renderer.h"
#include "model.h"
#include "camera.h"
#include "light.h"
#include "input.h"
#include "sound.h"
#include "fade.h"
#include "game.h"
#include "collision.h"
#include "debugproc.h"
#include "file.h"
#include "shadow.h"
#include "meshfield.h"
#include "player.h"
#include "gameover.h"
#include "ui.h"
#include "text_texture.h"
#include "reserve.h"
#include "result.h"
#include "bullet.h"
#include "playerArms.h"
#include "rescueLife.h"
#include "mapWallModel.h"
#include "obstacle.h"
#include "particle.h"
#include "map.h"
#include "meshwall.h"
#include "unitdata.h"
#include "time.h"
#include "title.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************



//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static int	g_ViewPortType_Game = TYPE_FULL_SCREEN;

static BOOL	g_bPause = TRUE;	// �|�[�YON/OFF
static BOOL g_Slow = FALSE;
static int s_mode = FALSE;
static BOOL gameover = FALSE;
static int	g_PlayMode = MAIN_GAME;
static int mode = 1;
static 	XMFLOAT3 cam_pos = { 0.0f, 0.0f, 0.0f };
static 	XMFLOAT3 cam_rot = { 0.0f, 0.0f, 0.0f };

//=============================================================================
// ����������
//=============================================================================
HRESULT InitGame(void)
{
	g_ViewPortType_Game = TYPE_FULL_SCREEN;
	InitSystem();

	return S_OK;
}

void InitSystem(void)
{
	CAMERA* cam = GetCamera();
	cam->rot = { 0.0f, 0.0f, 0.0f };
	// ���C�g��L����	// �e�̏���������
	InitShadow();

	InitPlayer();


	pArm::InitArm();
	Normal::InitArm();

	InitBullet();	

	// �t�B�[���h�̏�����
	InitMeshField(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), FIELD_X, FIELD_Z, BLOCK_SIZE, BLOCK_SIZE, GROUND);


	InitTime();
	InitOver();


	InitCharFade();

	//InitTexttex();

	InitParticle();
	InitUI();
	RescueLife::InitRescue();
	MapWallModel::Init();
	Obstacle::Init();
	FallObject::Init();

	InitMap();
	//InitReward();
	mode = 1;
	g_bPause = TRUE;
	gameover = FALSE;
}

//�N�����ɏd�������͂��ׂčs���Ă���(���f���̃��[�h�Ȃ�)
void InitBoot(void)
{
	pArm::InitArmBoot();
	Normal::InitArmBoot();
	MapWallModel::InitBoot();
	FallObject::InitBoot();
	RescueLife::InitBootRescue();
	Obstacle::InitBoot();
	InitBulletBoot();
	InitBootPlayer();
}

void InitMap(void)
{
	UninitMeshWall();	//���b�V���E�H�[���͂����Œ��ꏉ����

	switch (GetMode())
	{
	case MODE_TITLE:
		Map::InitMap();
		break;
	case MODE_GAME:
		Map::InitMap();
		break;
	case MODE_RESULT:
		break;
	}
}
//=============================================================================
// �I������
//=============================================================================
void UninitGame(void)
{
	// �e�̏I������
	UninitShadow();

	UninitOver();

	UninitBullet();

	UninitUI();

	UninitParticle();

	UninitTexttex();

	Obstacle::Uninit();

	MapWallModel::Uninit();

	FallObject::Uninit();

	RescueLife::UninitRescue();

	UninitMeshWall();

	UninitTime();
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateGame(void)
{
#ifdef _DEBUG
	if (GetKeyboardTrigger(DIK_P) && !GetHelpButton())
	{
		if (g_bPause == TRUE)
			g_bPause = FALSE;
		else
			g_bPause = TRUE;
	}
	if (GetKeyboardTrigger(DIK_G))
	{
		gameover = TRUE;
	}
	if (GetKeyboardTrigger(DIK_H))
	{
		Reward* re = GetReward();
		Reserve* res = GetReserve();
		gameover = TRUE;
		re->rescue_num = res->quota;
	}
#endif
	//�����Ɣ{���̐؂�ւ�
	if (GetKeyboardTrigger(DIK_O))
	{
		mode == 1 ? mode++ : mode--;
	}

	FADE fade = GetFade();
	if (fade != FADE_NONE)return;


	if(g_bPause == FALSE)
		return;

	UpdateOver();

	UpdateTexttex();
	if (CheckGameover())return;

	if (GetHelpButton())return;


		UpdateCamera();

		UpdatePlayer();

		UpdateLight();

		MapWallModel::Update();

		UpdateBullet();

		Obstacle::Update();

		FallObject::Update();

		UpdateTime();

		UpdateParticle();
		UpdateCharFade();
		//// �e�̍X�V����
		//UpdateShadow();

		//UpdateFog();

		//UpdateSound();

		UpdateUI();
}

//=============================================================================
// �`�揈��(�J�����ڐ�)
//=============================================================================
void DrawGame0(void)
{
	//�V�F�[�_�[�Ǘ�
	//�|�X�g�G�t�F�N�g��������ꍇ�͂�������
	int ans = MODE_PLANE;
	SwapShader(ans);

	DrawMeshField();

	MapWallModel::Draw();


	DrawMeshWall();

	Obstacle::Draw();

	FallObject::Draw();

	RescueLife::DrawRescue();

	DrawPlayer();

	//DrawBullet();
	DrawBulletModel();

	DrawParticle();

	// 2D���W�ŕ���`�悷�鏈��
	// Z��r�Ȃ�
	SetDepthEnable(FALSE);

	// ���C�e�B���O�𖳌�
	SetLightEnable(FALSE);

	DrawUI();

	DrawOver();

	//// �X�R�A�̕`�揈��
	//DrawScore();


	//�V�F�[�_�[�Ǘ�
	//�V�F�[�_�[�����ɖ߂��B�|�X�g�G�t�F�N�g�͂����܂�
	ans = MODE_PLANE;
	SwapShader(ans);

	// ���C�e�B���O��L����
	SetLightEnable(TRUE);

	// Z��r����
	SetDepthEnable(TRUE);
}


//=============================================================================
// �`�揈��(���C�g�ڐ��B�����������e�̃I�u�W�F�N�g�������w��)
//=============================================================================
void DrawGame1(void)
{
	DrawMeshField();

	MapWallModel::Draw();

	Obstacle::Draw();

	if(GetMode() == MODE_GAME)
	DrawPlayer();

}


void DrawGame(void)
{
	XMFLOAT3 pos;

	// �v���C���[���_
	CAMERA *cam = GetCamera();
	PLAYER *player = GetPlayer();
	pos = player[0].pos;
	pos.y += 0.0f;
	const float dist = 250.0f;
	pos.x += sinf(cam->rot.y)*dist;
	pos.z += cosf(cam->rot.y)*dist;
	SetCameraAT(pos);
	SetCamera();

	switch(g_ViewPortType_Game)
	{
	case TYPE_FULL_SCREEN:
			DrawGame0();
			break;
	case TYPE_LEFT_HALF_SCREEN:
	case TYPE_RIGHT_HALF_SCREEN:
		SetViewPort(TYPE_LEFT_HALF_SCREEN);
		DrawGame0();

		// �G�l�~�[���_
		break;

	case TYPE_UP_HALF_SCREEN:
	case TYPE_DOWN_HALF_SCREEN:
		SetViewPort(TYPE_UP_HALF_SCREEN);
		DrawGame0();

		break;

	case TYPE_LIGHT_SCREEN:	//���C�g�ڐ��̕`������邽�߂̃r���[�|�[�g�^�C�v
		SetViewPort(TYPE_FULL_SCREEN);
		DrawGame1();
		break;

	}

}


void DrawGameTitle(void)
{
	CAMERA *cam = GetCamera();
#ifdef _DEBUG
	if (GetKeyboardPress(DIK_W))
	{
		cam_pos.x += sinf(cam->rot.y);
		cam_pos.z += cosf(cam->rot.y);
	}
	if (GetKeyboardPress(DIK_S))
	{
		cam_pos.x -= sinf(cam->rot.y);
		cam_pos.z -= cosf(cam->rot.y);
	}
	if (GetKeyboardPress(DIK_A))
	{
		cam_pos.x -= cosf(cam->rot.y);
		cam_pos.z += sinf(cam->rot.y);
	}
	if (GetKeyboardPress(DIK_D))
	{
		cam_pos.x += cosf(cam->rot.y);
		cam_pos.z -= sinf(cam->rot.y);
	}
	if (GetKeyboardPress(DIK_U))
	{
		cam_pos.y += 1.0f;
	}
	if (GetKeyboardPress(DIK_V))
	{
		cam_pos.y -= 1.0f;
	}
	PrintDebugProc("\n�J�������Wx:%f,y:%f,z:%f\n", cam_pos.x, cam_pos.y, cam_pos.z);
#endif
	XMFLOAT3 pos;
	XMFLOAT3 rot;
	// �v���C���[���_
	pos = cam_pos;
	pos.y += 0.0f;
	const float dist = 0.0f;
	pos.x += sinf(cam->rot.y)*dist;
	pos.z += cosf(cam->rot.y)*dist;
	SetCameraAT(pos);
	SetCamera();

	//�V�F�[�_�[�Ǘ�
//�|�X�g�G�t�F�N�g��������ꍇ�͂�������
	int ans = MODE_PLANE;
	SwapShader(ans);

	DrawMeshField();

	MapWallModel::Draw();

	DrawMeshWall();

	Obstacle::Draw();

	RescueLife::DrawRescue();

	DrawParticle();

	// 2D���W�ŕ���`�悷�鏈��
	// Z��r�Ȃ�
	SetDepthEnable(FALSE);

	// ���C�e�B���O�𖳌�
	SetLightEnable(FALSE);

	//�V�F�[�_�[�Ǘ�
	//�V�F�[�_�[�����ɖ߂��B�|�X�g�G�t�F�N�g�͂����܂�
	ans = MODE_PLANE;
	SwapShader(ans);

	DrawTitle();

	// ���C�e�B���O��L����
	SetLightEnable(TRUE);

	// Z��r����
	SetDepthEnable(TRUE);

}

void DrawGameResult(void)
{
	CAMERA *cam = GetCamera();
#ifdef _DEBUG
	if (GetKeyboardPress(DIK_W))
	{
		cam_pos.x += sinf(cam->rot.y);
		cam_pos.z += cosf(cam->rot.y);
	}
	if (GetKeyboardPress(DIK_S))
	{
		cam_pos.x -= sinf(cam->rot.y);
		cam_pos.z -= cosf(cam->rot.y);
	}
	if (GetKeyboardPress(DIK_A))
	{
		cam_pos.x -= cosf(cam->rot.y);
		cam_pos.z += sinf(cam->rot.y);
	}
	if (GetKeyboardPress(DIK_D))
	{
		cam_pos.x += cosf(cam->rot.y);
		cam_pos.z -= sinf(cam->rot.y);
	}
	if (GetKeyboardPress(DIK_U))
	{
		cam_pos.y += 1.0f;
	}
	if (GetKeyboardPress(DIK_V))
	{
		cam_pos.y -= 1.0f;
	}
	PrintDebugProc("\n�J�������Wx:%f,y:%f,z:%f\n", cam_pos.x, cam_pos.y, cam_pos.z);
#endif
	XMFLOAT3 pos;
	// �v���C���[���_
	pos = XMFLOAT3{256.0f,-91.0f,-149.0f};
	cam->rot.y = 2.03f;
	cam->rot.x = 0.38f;
	const float dist = 0.0f;
	pos.x += sinf(cam->rot.y)*dist;
	pos.z += cosf(cam->rot.y)*dist;
	SetCameraAT(pos);
	SetCamera();

	//�V�F�[�_�[�Ǘ�
//�|�X�g�G�t�F�N�g��������ꍇ�͂�������
	int ans = MODE_PLANE;
	SwapShader(ans);

	DrawMeshField();

	MapWallModel::Draw();

	DrawMeshWall();

	Obstacle::Draw();

	RescueLife::DrawRescue();

	DrawPlayer();

	DrawParticle();

	// 2D���W�ŕ���`�悷�鏈��
	// Z��r�Ȃ�
	SetDepthEnable(FALSE);

	// ���C�e�B���O�𖳌�
	SetLightEnable(FALSE);

	//�V�F�[�_�[�Ǘ�
	//�V�F�[�_�[�����ɖ߂��B�|�X�g�G�t�F�N�g�͂����܂�
	ans = MODE_PLANE;
	SwapShader(ans);

	DrawResult();

	// ���C�e�B���O��L����
	SetLightEnable(TRUE);

	// Z��r����
	SetDepthEnable(TRUE);

}

void DrawGameReserve(void)
{
	CAMERA *cam = GetCamera();
	int ans = MODE_PLANE;
	SwapShader(ans);
#ifdef _DEBUG
	if (GetKeyboardPress(DIK_W))
	{
		cam_pos.x += sinf(cam->rot.y);
		cam_pos.z += cosf(cam->rot.y);
	}
	if (GetKeyboardPress(DIK_S))
	{
		cam_pos.x -= sinf(cam->rot.y);
		cam_pos.z -= cosf(cam->rot.y);
	}
	if (GetKeyboardPress(DIK_A))
	{
		cam_pos.x -= cosf(cam->rot.y);
		cam_pos.z += sinf(cam->rot.y);
	}
	if (GetKeyboardPress(DIK_D))
	{
		cam_pos.x += cosf(cam->rot.y);
		cam_pos.z -= sinf(cam->rot.y);
	}
	if (GetKeyboardPress(DIK_U))
	{
		cam_pos.y += 1.0f;
	}
	if (GetKeyboardPress(DIK_V))
	{
		cam_pos.y -= 1.0f;
	}
	PrintDebugProc("\n�J�������Wx:%f,y:%f,z:%f\n", cam_pos.x, cam_pos.y, cam_pos.z);
#endif

	XMFLOAT3 pos = cam_pos;
	cam_rot.y += XM_PI * 0.001f;
	if (cam_rot.y >= XM_PI * 2.0f)
		cam_rot.y = 0.0f;

	// �v���C���[���_
	//pos = XMFLOAT3{ 243.0f,-124.0f,-143.0f };
	//cam->rot.y = 2.03f;
	//cam->rot.x = 0.3f;
	float dist = 0.0f;
	pos.x += sinf(cam_rot.y)*dist;
	pos.z += cosf(cam_rot.y)*dist;
	SetReserveCameraAT(pos, cam_rot);
	SetCamera();

	DrawMeshField();

	MapWallModel::Draw();

	DrawMeshWall();

	Obstacle::Draw();

	// �v���C���[���_
	pos = XMFLOAT3{ 243.0f,-124.0f,-143.0f };
	cam->rot.y = 2.03f;
	cam->rot.x = 0.3f;
	dist = 0.0f;
	pos.x += sinf(cam->rot.y)*dist;
	pos.z += cosf(cam->rot.y)*dist;
	SetCameraAT(pos);
	SetCamera();

	//�V�F�[�_�[�Ǘ�
//�|�X�g�G�t�F�N�g��������ꍇ�͂�������
	ans = MODE_PLANE;
	SwapShader(ans);

	//�V�F�[�_�[�Ǘ�
	//�V�F�[�_�[�����ɖ߂��B�|�X�g�G�t�F�N�g�͂����܂�
	ans = MODE_PLANE;
	SwapShader(ans);

	DrawPlayer();

	// 2D���W�ŕ���`�悷�鏈��
	// Z��r�Ȃ�
	SetDepthEnable(FALSE);

	// ���C�e�B���O�𖳌�
	SetLightEnable(FALSE);

	//�V�F�[�_�[�Ǘ�
	//�V�F�[�_�[�����ɖ߂��B�|�X�g�G�t�F�N�g�͂����܂�
	ans = MODE_PLANE;
	SwapShader(ans);

	DrawReserve();
	// ���C�e�B���O��L����
	SetLightEnable(TRUE);

	// Z��r����
	SetDepthEnable(TRUE);

}

void SetPlayMode(int playMode)
{
	g_PlayMode = playMode;
}

int GetPlayMode(void)
{
	return g_PlayMode;
}

void SetSlowMode(BOOL flag)
{
	g_Slow = flag;
}
//void SetPlayStage(int stageNum)
//{
//	g_PlayStage = stageNum;
//}

//int GetPlayStage(void)
//{
//	return g_PlayStage;
//}

void SetViewPortType(int viewport)
{
	g_ViewPortType_Game = viewport;
}

int GetViewPortTypeGame(void)
{
	return g_ViewPortType_Game;
}

//���l�̃N�����v�B����1:�N�����v���������l�A����2:�ŏ��l�A����3:�ő�l
float FloatClamp(float x, float a, float b)
{
	if (x < a)
	{
		return a;
	}
	else if (x > b)
	{
		return b;
	}
	else
	{
		return x;
	}
}

//float�^�̐��l�̔�r������Bflag��FALSE�Ȃ珬���������ATRUE�Ȃ�傫������Ԃ�
float FloatCompare(BOOL flag, float a, float b)
{
	float ans = 0.0f;//�ꉞ0.0f���Z�b�g���Ă���
	switch (flag)
	{
	case FALSE:
		if (a > b)return b;
		else	  return a;
		break;
	case TRUE:
		if (a > b)return a;
		else	  return b;
		break;
	}

	return ans;
}


BOOL CheckGameover(void)
{
	BOOL ans = FALSE;
	Reward* re = GetReward();
	Reserve* res = GetReserve();

	if (GetTime() <= 0 || RescueLife::GetRescueRemainLife() <= 0 || gameover)
	{
		if (res->quota <= re->rescue_num)
			SetOverType(OVER_WIN);
		else
			SetOverType(OVER_LOSE);

		ans = TRUE;
	}

	return ans;
}

//�_���[�W�v�Z�֐��B�����̂��ꂼ��ɁA�U���҂̍U���͂Ɩh�䑤�̖h��͂������Ă���
int DamageFunc(int attacker, int diffender)
{
	//�ЂƂ܂��P���Ȍv�Z���ōς܂�
	int ans = attacker - diffender;
	//�K��1�ȏ�Ń_���[�W��Ԃ��悤�ɂ���
	if (ans <= 0)
		ans = 1;
	return ans;
}

int GetSpeedMode(void)
{
	return mode;
}