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
#include "cost.h"
#include "enemy.h"
#include "fieldchip.h"
#include "base.h"
#include "playerSet.h"
#include "team.h"
#include "gameover.h"
#include "ui.h"
#include "enemySet.h"
#include "unitdata.h"
#include "text_texture.h"
#include "reserve.h"
#include "result.h"
#include "enemyLinerData.h"
#include "bullet.h"


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
static int	g_PlayMode = MAIN_GAME;
static int mode = 1;
//�����Ŏg�p����}�b�v�`�b�v�i���o�[��ݒ�B�����z�񂾂��A�ő吔�ő�����B
//�ԈႦ�ď㉺�t�ɂȂ���������c���E�͋t����Ȃ���
int g_DebugMap[][MAX_CHIP_WIDTH + 1]
{
	{1,1,1,1,1,1,1,1},
	{2,2,0,0,0,0,2,2},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{1,1,1,1,1,1,1,1},
	{0,0,0,0,0,0,0,0},
	{3,3,3,3,1,1,1,1},
};

int g_DebugMapObject[][MAX_CHIP_WIDTH + 1]
{
	{9,9,9,9,9,9,9,9},
	{9,9,9,9,9,9,9,1},
	{9,9,9,9,9,9,9,1},
	{9,9,9,9,9,9,9,1},
	{9,9,9,9,9,9,9,9},
	{0,1,9,9,9,9,9,1},
	{9,9,9,9,9,9,0,0},
};
int g_FirstMap[][MAX_CHIP_WIDTH + 1]
{
	{1,1,1,1,1,3,1,1},
	{0,2,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,2},
	{0,0,0,0,0,0,0,0},
	{1,1,3,1,1,1,1,1},

};

int g_FirstMapObject[][MAX_CHIP_WIDTH + 1]
{
	{0,9,9,1,9,9,9,9},
	{9,9,9,9,9,9,9,1},
	{9,9,9,9,9,9,9,9},
	{9,9,9,9,9,9,9,1},
	{9,9,9,9,9,9,9,0},


};
int g_SecondMap[][MAX_CHIP_WIDTH + 1]
{
	{1,1,1,1,1,3,1,1},
	{0,2,0,0,2,0,2,0},
	{0,0,2,0,0,0,0,2},
	{2,0,0,0,2,0,2,0},
	{3,1,3,1,1,3,3,1},
};

int g_SecondMapObject[][MAX_CHIP_WIDTH + 1]
{
	{0,9,9,9,1,9,9,9},
	{9,9,1,9,9,9,9,1},
	{9,9,9,9,9,9,9,9},
	{9,9,9,9,1,9,9,1},
	{9,9,9,9,9,9,1,0},
};
int g_ThirdMap[][MAX_CHIP_WIDTH + 1]
{
	{1,1,1,3,1,1,1,1},
	{0,2,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,2},
	{2,0,0,2,0,0,2,0},
	{0,0,2,0,0,0,0,0},
	{0,0,0,0,2,0,0,0},
	{1,1,3,1,1,1,1,1},
};

int g_ThirdMapObject[][MAX_CHIP_WIDTH + 1]
{
	{0,9,9,9,1,9,1,0},
	{9,9,9,9,9,9,9,9},
	{9,9,9,9,9,9,9,9},
	{9,0,9,9,1,0,9,9},
	{9,9,9,9,9,9,9,9},
	{9,9,0,9,9,9,9,9},
	{0,1,9,9,0,9,0,1},
};
int g_ForthMap[][MAX_CHIP_WIDTH + 1]
{
	{1,1,3,3,1,3,1,3},
	{2,2,0,2,2,2,0,0},
	{0,2,2,0,2,0,0,2},
	{2,0,0,2,0,2,2,2},
	{0,0,2,0,2,0,0,2},
	{2,2,0,0,2,2,2,0},
	{3,1,3,1,3,3,1,1},
};

int g_ForthMapObject[][MAX_CHIP_WIDTH + 1]
{
	{0,1,9,9,1,9,1,0},
	{9,9,9,9,9,9,9,9},
	{9,9,9,9,9,9,9,9},
	{9,0,9,9,1,0,9,9},
	{1,9,9,9,9,9,9,9},
	{9,9,0,9,9,9,9,9},
	{0,1,9,9,0,9,0,1},
};
//=============================================================================
// ����������
//=============================================================================
HRESULT InitGame(void)
{
	g_ViewPortType_Game = TYPE_FULL_SCREEN;
	InitSystem();
	switch (GetDay())
	{
	case 0:	//0�̓f�o�b�O�p�Ŏc���Ă����H
		InitSystem();
		break;
	case 1:
		InitSystem();
		break;
	case 2:
		break;
	}

	return S_OK;
}

void InitSystem(void)
{
	// ���C�g��L����	// �e�̏���������
	InitShadow();

	InitPlayer();

	InitEnemy();

	InitBullet();	
	// �t�B�[���h�̏�����
	InitMeshField(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), FIELD_X, FIELD_Z, BLOCK_SIZE, BLOCK_SIZE, WATER);

	InitCost();

	InitOver();


	InitCharFade();

	InitTexttex();

	InitPlayerSet();

	InitUI();
	InitReward();
	mode = 1;
	g_bPause = TRUE;
	//����������ʂ��Ƃ̐ݒ�Ɉڂ�B�������֐�������day���̐ݒ��S�č쐬�B
	//SetReward(0, 1000);
	//SetReward(1, 50);
	//SetReward(2, 1);
	//InitMapChip(g_DebugMap, g_DebugMapObject, 7, MAX_CHIP_WIDTH);
	//SetGrape(800.0f, 40, 5, 1, FirstmoveTbl, sizeof(FirstmoveTbl) / sizeof(MOVERINE));
	//SetGrape(900.0f, 40, 5, 1, FirstmoveTbl, sizeof(FirstmoveTbl) / sizeof(MOVERINE));
	//SetGrape(1000.0f, 40, 5, 1, FirstmoveTbl, sizeof(FirstmoveTbl) / sizeof(MOVERINE));
	//SetRyoku(100.0f, 40, 5, 1, FirstmoveTbl, sizeof(FirstmoveTbl) / sizeof(MOVERINE));
	//SetStrept(1400.0f, 40, 5, 1, FirstmoveTbl, sizeof(FirstmoveTbl) / sizeof(MOVERINE));
	//SetStrept(9000.0f, 40, 5, 1, FirstmoveTbl, sizeof(FirstmoveTbl) / sizeof(MOVERINE));
	//SetStrept(9000.0f, 40, 5, 1, FirstmoveTbl, sizeof(FirstmoveTbl) / sizeof(MOVERINE));
	//SetStrept(9000.0f, 40, 5, 1, FirstmoveTbl, sizeof(FirstmoveTbl) / sizeof(MOVERINE));
	//XMFLOAT3 pos[1];
	//pos[0] = { 25.0f, 0.0f, 100.0f };
	//InitBase(3, &pos[0], 1);
	//PlaySound(SOUND_LABEL_BGM_Battle1);

	Reserve *re = GetReserve();
	int linesize = 0;
	int linesize2 = 0;
	XMFLOAT3 pos[1];
	switch (re->day)
	{
	case 1:
		SetReward(0, 700);
		SetReward(1, 30);
		SetReward(2, 1);
		InitMapChip(g_FirstMap, g_FirstMapObject, 5, MAX_CHIP_WIDTH);
		linesize = sizeof(FirstmoveTbl) / sizeof(MOVERINE);
		linesize2 = sizeof(FirstmoveTbl2) / sizeof(MOVERINE);
		SetGrape(600.0f, 30, 4, 2, FirstmoveTbl2, linesize2);
		SetGrape(1200.0f, 30, 4, 2, FirstmoveTbl2, linesize2);
		SetGrape(9000.0f, 30, 4, 2, FirstmoveTbl, linesize);
		SetRyoku(9600.0f, 30, 7, 1, FirstmoveTbl2, linesize2);
		SetRyoku(10200.0f, 30, 7, 1, FirstmoveTbl2, linesize2);
		SetRyoku(18000.0f, 30, 7, 1, FirstmoveTbl, linesize);
		SetRyoku(19000.0f, 30, 7, 1, FirstmoveTbl, linesize);
		SetStrept(22000.0f, 90, 5, 1, FirstmoveTbl, linesize);
		SetStrept(23000.0f, 90, 5, 1, FirstmoveTbl, linesize);
		SetRyoku(25000.0f, 30, 7, 1, FirstmoveTbl2, linesize2);
		SetRyoku(26000.0f, 30, 7, 1, FirstmoveTbl2, linesize2);

		SetCost(10);
		pos[0] = { 25.0f, 0.0f, 100.0f };
		InitBase(3, &pos[0], 1);
		PlaySound(SOUND_LABEL_BGM_Battle1);
		break;
	case 2:
		SetReward(0, 1000);
		SetReward(1, 50);
		SetReward(2, 1);
		InitMapChip(g_SecondMap, g_SecondMapObject, 5, MAX_CHIP_WIDTH);
		linesize = sizeof(SecondmoveTbl) / sizeof(MOVERINE);
		linesize2 = sizeof(FirstmoveTbl2) / sizeof(MOVERINE);
		SetGrape(1600.0f, 40, 5, 1, SecondmoveTbl, linesize);
		SetGrape(2000.0f, 40, 5, 1, SecondmoveTbl, linesize);
		SetGrape(6000.0f, 40, 5, 1, SecondmoveTbl, linesize);
		SetRyoku(9000.0f, 40, 5, 1, SecondmoveTbl, linesize);
		SetStrept(9600.0f, 40, 5, 1, SecondmoveTbl, linesize);
		SetStrept(12000.0f, 90, 4, 3, SecondmoveTbl, linesize);
		SetStrept(13000.0f, 90, 4, 3, FirstmoveTbl2, linesize2);
		SetRyoku(21000.0f, 30, 7, 1, FirstmoveTbl2, linesize2);
		SetRyoku(22200.0f, 30, 7, 1, FirstmoveTbl2, linesize2);
		SetRyoku(24200.0f, 30, 7, 1, SecondmoveTbl, linesize);
		SetRyoku(26000.0f, 30, 7, 1, SecondmoveTbl, linesize);
		SetGrape(40000.0f, 40, 5, 1, SecondmoveTbl, linesize);
		SetGrape(42500.0f, 40, 5, 1, SecondmoveTbl, linesize);
		SetGrape(44000.0f, 40, 5, 1, SecondmoveTbl, linesize);
		SetGrape(46000.0f, 40, 5, 1, SecondmoveTbl, linesize);
		SetInflue(70000.0f, 30, 10, 2, ThirdmoveTbl, linesize);
		SetInflue(71000.0f, 30, 10, 2, ThirdmoveTbl, linesize);
		SetInflue(72000.0f, 30, 10, 2, ThirdmoveTbl, linesize);

		SetCost(10);
		pos[0] = { 25.0f, 0.0f, 100.0f };
		InitBase(3, &pos[0], 1);
		PlaySound(SOUND_LABEL_BGM_Battle2);
		break;
	case 3:
		SetReward(0, 1200);
		SetReward(1, 80);
		SetReward(2, 1);
		InitMapChip(g_ThirdMap, g_ThirdMapObject, 7, MAX_CHIP_WIDTH);
		linesize = sizeof(ThirdmoveTbl) / sizeof(MOVERINE);
		SetInflue(900.0f, 40, 5, 1, ThirdmoveTbl, linesize);
		SetInflue(3000.0f, 40, 5, 1, ThirdmoveTbl, linesize);
		SetInflue(3600.0f, 40, 5, 1, ThirdmoveTbl, linesize);
		SetInflue(5800.0f, 40, 5, 1, ThirdmoveTbl, linesize);
		SetInflue(9000.0f, 40, 7, 2, ThirdmoveTbl, linesize);
		SetInflue(9300.0f, 40, 7, 2, ThirdmoveTbl, linesize);
		SetInflue(9600.0f, 40, 7, 2, ThirdmoveTbl, linesize);
		SetInflue(20000.0f, 60, 5, 3, ThirdmoveTbl, linesize);
		SetInflue(22000.0f, 60, 5, 3, ThirdmoveTbl, linesize);
		SetInflue(24000.0f, 40, 7, 2, ThirdmoveTbl, linesize);
		SetInflue(26000.0f, 40, 7, 2, ThirdmoveTbl, linesize);
		SetInflue(28000.0f, 40, 7, 2, ThirdmoveTbl, linesize);
		SetInflue(28000.0f, 40, 7, 2, ThirdmoveTbl, linesize);
		SetInflue(30000.0f, 40, 7, 2, ThirdmoveTbl, linesize);
		SetInflue(30600.0f, 40, 7, 2, ThirdmoveTbl, linesize);
		SetInflue(31200.0f, 40, 7, 2, ThirdmoveTbl, linesize);
		SetInflue(31800.0f, 40, 7, 2, ThirdmoveTbl, linesize);
		SetInflue(32400.0f, 40, 7, 2, ThirdmoveTbl, linesize);
		SetInflue(33000.0f, 40, 7, 2, ThirdmoveTbl, linesize);
		SetCost(10);
		pos[0] = { 25.0f, 0.0f, 100.0f };
		InitBase(3, &pos[0], 1);
		PlaySound(SOUND_LABEL_BGM_Battle1);
		break;
	case 4:
		SetReward(0, 1000);
		SetReward(1, 50);
		SetReward(2, 1);
		InitMapChip(g_ForthMap, g_ForthMapObject, 7, MAX_CHIP_WIDTH);
		linesize = sizeof(ForthmoveTbl) / sizeof(MOVERINE);
		SetGrape(800.0f, 40, 5, 1, ForthmoveTbl, linesize);
		SetGrape(900.0f, 40, 5, 1, ForthmoveTbl, linesize);
		SetGrape(1000.0f, 40, 5, 1, ForthmoveTbl, linesize);
		SetRyoku(100.0f, 40, 5, 1, ForthmoveTbl, linesize);
		SetStrept(1400.0f, 40, 5, 1, ForthmoveTbl, linesize);
		SetStrept(9000.0f, 40, 5, 1, ForthmoveTbl, linesize);
		SetStrept(9000.0f, 40, 5, 1, ForthmoveTbl, linesize);
		SetStrept(9000.0f, 40, 5, 1, ForthmoveTbl, linesize);
		SetCost(10);
		pos[0] = { 25.0f, 0.0f, 100.0f };
		InitBase(3, &pos[0], 1);
		PlaySound(SOUND_LABEL_BGM_Title);
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

	UninitEnemy();

	UninitMapChip();

	UninitUI();

	UninitTexttex();
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateGame(void)
{
	if (GetKeyboardTrigger(DIK_P) && !GetHelpButton())
	{
		if (g_bPause == TRUE)
			g_bPause = FALSE;
		else
			g_bPause = TRUE;
	}

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

	UpdatePlayerSet();

	if (GetHelpButton())return;

	if (g_Slow == TRUE)
	{
		mode = 1;
		s_mode++;
		if (s_mode > 2)
		{
			s_mode = 0;
		}
		else return;	//�X���[���Ȃ�2���1�񂾂�����
	}

	for (int i = 0; i < mode; i++)
	{
		UpdateCamera();

		UpdateMapChip();

		UpdatePlayer();

		UpdateEnemy();

		UpdateBullet();

		UpdateLight();

		IncTimeCost();

		UpdateCharFade();
		// �e�̍X�V����
		UpdateShadow();

		UpdateFog();

		UpdateSound();

		UpdateUI();
	}
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

	DrawBG();	//�w�i���ɕ`��

	DrawMapChip();

	DrawPlayer();

	DrawEnemy();

	DrawBattleSetChar();

	DrawBullet();

	DrawPlayerLife();

	DrawEnemyLife();

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

	DrawMapChip();

	DrawPlayer();

	DrawEnemy();
}


void DrawGame(void)
{
	XMFLOAT3 pos;

	// �v���C���[���_
	//pos = GetPlayer()->pos;
	CAMERA *cam = GetCamera();
	PlayerSet *ps = GetSetPos();
	PLAYER *player = GetPlayer();
	float center_w = CHIP_SIZE * (MAX_CHIP_WIDTH - 1) * 0.5f;
	float center_h = CHIP_SIZE * MAX_CHIP_HEIGHT * 0.5f;
	XMFLOAT3 x = player[ps->setPlayer].pos;

	pos = { center_w, 0.0f, center_h };

	if (!ps->setCheckMode)
		SetCameraAT(pos);
	else
		SetCharaCamera(x);

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
	int life = GetEnemyNum() - GetBanishEnemy();
	if (GetBaseLife() <= 0) { 
		ans = TRUE;
		SetOverType(OVER_LOSE);
	}
	else if (life <= 0) {
		ans = TRUE;
		SetOverType(OVER_WIN);
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