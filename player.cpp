//=============================================================================
//
// �o�g�����̃v���C���[���� [player.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "math.h"
#include "input.h"
#include "camera.h"
#include "debugproc.h"
#include "model.h"
#include "game.h"
#include "player.h"
#include "shadow.h"
#include "light.h"
#include "meshfield.h"
#include "collision.h"
#include "time.h"
#include "sound.h"
#include "bullet.h"
#include "playerArms.h"
#include "particle.h"
#include "meshwall.h"
#include "playerIPData.h"
#include "obstacle.h"
#include "result.h"
#include <algorithm>
#include <iostream>
#include <fstream>

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_MAX			(1)								// �e�N�X�`���̐�
#define VAR_WIDTH			(50.0f)
#define VAR_HEIGHT			(5.0f)
#define	VALUE_MOVE			(2.0f)							// �ړ���
#define	VALUE_MOVE_DASH			(3.0f)							// �_�b�V����������
#define	VALUE_AT_MOVE		(8.0f)							// �ړ���
#define	VALUE_ROTATE		(XM_PI * 0.02f)					// ��]��

#define PLAYER_SHADOW_SIZE	(1.0f)							// �e�̑傫��
#define PLAYER_OFFSET_Y		(38.5f)							// �v���C���[�̑��������킹��
#define PLAYER_OFFSET_Z		(-300.0f)							// �v���C���[�̑��������킹��
#define PLAYER_LIFE			(100)								// �v���C���[�̃��C�t

#define PLAYER_PARTS_MAX	(1)								// �v���C���[�̃p�[�c�̐�
#define PLAYER_AT_FLAME		(30.0f)							// �v���C���[�̍U���t���[��
#define PLAYER_SP_FLAME		(30.0f)							// �v���C���[��SP��������Ԋu
#define PLAYER_INVINC_FLAME	(120.0f)						// �v���C���[���G�t���[��
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static ID3D11Buffer					*g_VertexBuffer = NULL;	// ���_���
static ID3D11ShaderResourceView		*g_Texture[TEXTURE_MAX] = { NULL };	// �e�N�X�`�����
static char* g_TextureName[] = {
	"data/TEXTURE/var.png",
};
static PLAYER_VAR	g_PlayerVar;
static PLAYER		g_Player[MAX_PLAYER];						// �v���C���[
static Playerliner  g_Playerline[MAX_PLAYER_PARTS + 1];					//�v���C���[�̐��`��ԃf�[�^
static PLAYER		g_Parts[MAX_PLAYER_PARTS];					// �v���C���[
static pArm*		g_PlayerArm[3];	//��[�A�[���̎�ސ�
static pArm*		g_Arm[2];		//�A�[���̐�
static BOOL			g_Load = FALSE;
static int			playerNum = 0;
static int			atNum[MAX_PLAYER];
static char name[2][64];
using namespace std;
static ofstream fout;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitPlayer(void)
{
	ID3D11Device *pDevice = GetDevice();
	MakeVertexPlayerVar();
	// �e�N�X�`������
	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		D3DX11CreateShaderResourceViewFromFile(GetDevice(),
			g_TextureName[i],
			NULL,
			NULL,
			&g_Texture[i],
			NULL);
	}

	ZeroMemory(&g_PlayerVar.material, sizeof(g_PlayerVar.material));
	g_PlayerVar.material.Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	g_PlayerVar.pos = { 0.0f, 0.0f, 0.0f };
	g_PlayerVar.rot = { XM_PI * -0.5f, 0.0f, 0.0f };
	g_PlayerVar.scl = { 1.0f, 1.0f, 1.0f };
	g_PlayerVar.pardiff = 0.0f;
	g_PlayerVar.parpolar = 0.02f;
	g_PlayerVar.load = TRUE;

	strcpy(name[0], MODEL_PLAYER);
	strcpy(name[1], MODEL_NEUTROPHILS);

	for (int i = 0; i < MAX_PLAYER; i++)
	{
		g_Player[i].load = FALSE;
		g_Player[i].pos = { 0.0f, PLAYER_OFFSET_Y, 200.0f };
		//g_Player[i].pos = { 0.0f, 0.0f, 200.0f };

		if(GetMode() != MODE_GAME)
		g_Player[i].pos = { 0.0f, PLAYER_OFFSET_Y, 0.0f };
		g_Player[i].rot = { 0.0f, -XM_PI * 0.5f, 0.0f };
		g_Player[i].scl = { 1.0f, 1.0f, 1.0f };
		g_Player[i].moveVec = { 0.0f, 0.0f, 0.0f };

		g_Player[i].size = PLAYER_SIZE;		// �����蔻��̑傫��
		g_Player[i].use = FALSE;
		g_Player[i].life = PLAYER_LIFE;
		g_Player[i].lifeMax = g_Player[i].life;
		g_Player[i].power = 5;
		g_Player[i].diffend = 3;
		g_Player[i].attack = FALSE;
		g_Player[i].rescue = FALSE;
		g_Player[i].rescueUse = FALSE;
		g_Player[i].attackUse = FALSE;
		g_Player[i].partsNum = 9;
		g_Player[i].startNum = 0;
		g_Player[i].spd = 0.0f;
		g_Player[i].armType = 0;
		g_Player[i].motionTime = 0.0f;
		g_Player[i].n_motionTime = 0.0f;
		g_Player[i].cntBullet = 0.0f;
		g_Player[i].rescueBullet[0] = { 0.0f, 0.0f, 0.0f };;
		g_Player[i].rescueBullet[1] = { 0.0f, 0.0f, 0.0f };;

		// �K�w�A�j���[�V�����p�̏���������
		g_Player[i].parent = NULL;			// �{�́i�e�j�Ȃ̂�NULL������
		g_Playerline[i].pos = { 0.0f, 0.0f, 0.0f };
		g_Playerline[i].rot = { 0.0f, 0.0f, 0.0f };
		g_Playerline[i].scl = { 0.0f, 0.0f, 0.0f };
	}
	
	for (int i = 0; i < MAX_PLAYER_PARTS; i++)
	{
		g_Parts[i].load = FALSE;
		g_Parts[i].use = FALSE;
	}
	
	g_Player[0].use = TRUE;
	g_Player[0].load = TRUE;
	g_Player[0].partsNum = 9;
	g_Player[0].lifeMax = 100.0f;
	g_Player[0].life = g_Player[0].lifeMax;
	g_Player[0].inv_time = PLAYER_INVINC_FLAME;
	g_Player[0].invincible = FALSE;
	SetPlayerArm();

	for (int i = 0; i < MAX_PLAYER_PARTS; i++) {
		g_Parts[i].parent = &g_Player[0];
		g_Parts[i].load = TRUE;
		g_Parts[i].pos = { 0.0f, 0.0f, 0.0f };
		g_Parts[i].rot = { 0.0f, 0.0f, 0.0f };
		g_Parts[i].scl = { 1.0f,1.0f, 1.0f };
		g_Parts[i].tbl_adrM = NULL;
		g_Parts[i].move_time = 0.0f;
	}

	//�p�[�c���Ƃ̃��[�V�����f�[�^
	for (int i = 0; i < MAX_PLAYER_PARTS + 1; i++) {
		g_Playerline[i].tbl_adrM = walk_data[i];
		g_Playerline[i].tbl_sizeM = data_size[i];
		g_Playerline[i].move_time = 0.0f;
	}


	g_Parts[P_HEAD].pos = { 5.0f, 5.0f, 0.0f };

	g_Parts[P_L_SHOULDER].pos = { 0.0f, 0.0f, -6.0f };

	g_Parts[P_R_SHOULDER].pos = { 0.0f, 0.0f, 6.0f };
	g_Parts[P_L_ARM].parent = &g_Parts[P_L_SHOULDER];
	g_Parts[P_L_ARM].pos = { 0.0f, -8.0f, -3.0f };

	g_Parts[P_R_ARM].parent = &g_Parts[P_R_SHOULDER];
	g_Parts[P_R_ARM].pos = { 0.0f, -8.0f, 3.0f };

	g_Parts[P_L_THIGH].pos = { 0.5f, -13.0f, -3.5f };

	g_Parts[P_R_THIGH].pos = { 0.5f, -13.0f, 3.5f };

	g_Parts[P_L_FOOT].parent = &g_Parts[P_L_THIGH];
	g_Parts[P_L_FOOT].pos = { 1.5f, -5.0f, 0.0f };

	g_Parts[P_R_FOOT].parent = &g_Parts[P_R_THIGH];
	g_Parts[P_R_FOOT].pos = { 1.5f, -5.0f, 0.0f };

	g_Load = TRUE;
	playerNum = 0;
	pArm::SetArmParent(&g_Player[0]);	//�e���������ň����n��
	Normal::SetArmParent(&g_Player[0]);	//�e���������ň����n��
	g_Arm[0] = pArm::GetArm();
	g_Arm[1] = pArm::GetArm();
	for (int i = 0; i < MAX_PLAYER; i++)
		atNum[i] = 0;
	fout.open("pos_data.txt");

	return S_OK;
}

void InitBootPlayer(void)
{
	LoadModel(MODEL_BODY, &g_Player[0].model);
	GetModelDiffuse(&g_Player[0].model, &g_Player[0].diffuse[0]);
	//���f���ǂݍ��݂ƃy�A�����g�t�����s��
	LoadModel(MODEL_HEAD, &g_Parts[P_HEAD].model);
	GetModelDiffuse(&g_Parts[P_HEAD].model, &g_Parts[P_HEAD].diffuse[0]);
	g_Parts[P_HEAD].pos = { 5.0f, 5.0f, 0.0f };


	LoadModel(MODEL_L_SHOULDER, &g_Parts[P_L_SHOULDER].model);
	GetModelDiffuse(&g_Parts[P_L_SHOULDER].model, &g_Parts[P_L_SHOULDER].diffuse[0]);
	g_Parts[P_L_SHOULDER].pos = { 0.0f, 0.0f, -6.0f };

	LoadModel(MODEL_R_SHOULDER, &g_Parts[P_R_SHOULDER].model);
	GetModelDiffuse(&g_Parts[P_R_SHOULDER].model, &g_Parts[P_R_SHOULDER].diffuse[0]);
	g_Parts[P_R_SHOULDER].pos = { 0.0f, 0.0f, 6.0f };
	LoadModel(MODEL_L_ARM, &g_Parts[P_L_ARM].model);
	GetModelDiffuse(&g_Parts[P_L_ARM].model, &g_Parts[P_L_ARM].diffuse[0]);
	g_Parts[P_L_ARM].parent = &g_Parts[P_L_SHOULDER];
	g_Parts[P_L_ARM].pos = { 0.0f, -8.0f, -3.0f };

	LoadModel(MODEL_R_ARM, &g_Parts[P_R_ARM].model);
	GetModelDiffuse(&g_Parts[P_R_ARM].model, &g_Parts[P_R_ARM].diffuse[0]);
	g_Parts[P_R_ARM].parent = &g_Parts[P_R_SHOULDER];
	g_Parts[P_R_ARM].pos = { 0.0f, -8.0f, 3.0f };

	LoadModel(MODEL_L_THIGH, &g_Parts[P_L_THIGH].model);
	GetModelDiffuse(&g_Parts[P_L_THIGH].model, &g_Parts[P_L_THIGH].diffuse[0]);
	g_Parts[P_L_THIGH].pos = { 0.5f, -13.0f, -3.5f };

	LoadModel(MODEL_R_THIGH, &g_Parts[P_R_THIGH].model);
	GetModelDiffuse(&g_Parts[P_R_THIGH].model, &g_Parts[P_R_THIGH].diffuse[0]);
	g_Parts[P_R_THIGH].pos = { 0.5f, -13.0f, 3.5f };

	LoadModel(MODEL_L_FOOT, &g_Parts[P_L_FOOT].model);
	GetModelDiffuse(&g_Parts[P_L_FOOT].model, &g_Parts[P_L_FOOT].diffuse[0]);
	g_Parts[P_L_FOOT].parent = &g_Parts[P_L_THIGH];
	g_Parts[P_L_FOOT].pos = { 0.0f, -5.0f, 0.0f };

	LoadModel(MODEL_R_FOOT, &g_Parts[P_R_FOOT].model);
	GetModelDiffuse(&g_Parts[P_R_FOOT].model, &g_Parts[P_R_FOOT].diffuse[0]);
	g_Parts[P_R_FOOT].parent = &g_Parts[P_R_THIGH];
	g_Parts[P_R_FOOT].pos = { 0.0f, -5.0f, 0.0f };

}

//=============================================================================
// �I������
//=============================================================================
void UninitPlayer(void)
{
	if (g_Load == FALSE) return;

	name[0][0] = '0';
	name[1][0] = '0';
	// ���_�o�b�t�@�̉��
	if (g_VertexBuffer)
	{
		g_VertexBuffer->Release();
		g_VertexBuffer = NULL;
	}


	for (int i = 0; i < MAX_PLAYER; i++)
	{
		// ���f���̉������
		if (g_Player[i].load)
		{
			UnloadModel(&g_Player[i].model);
			g_Player[i].load = FALSE;
		}
	}
	for (int i = 0; i < MAX_PLAYER_PARTS; i++)
	{
		// ���f���̉������
		if (g_Player[i].load)
		{
			UnloadModel(&g_Parts[i].model);
			g_Parts[i].load = FALSE;
		}
	}
	fout.close();
	g_Load = FALSE;
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePlayer(void)
{
	for (int i = 0; i < MAX_PLAYER; i++)
	{
		if (g_Player[i].use != TRUE)continue;

		ControlPlayer();
		ControlCamera();
		MovePlayer();
		ControlChangeArm();

		XMFLOAT3 pos;
		const float dist = 20.0f;
		pos.x = sinf(g_Player[0].rot.y - XM_PI * 0.25f)*dist;
		pos.z = cosf(g_Player[0].rot.y + XM_PI * 0.25f)*dist;
		g_PlayerArm[0]->pos = { g_Player[0].pos.x + pos.x, g_Player[0].pos.y, g_Player[0].pos.z + pos.z };
		g_PlayerArm[1]->pos = { g_Player[0].pos.x + pos.x, g_Player[0].pos.y, g_Player[0].pos.z + pos.z };

		IPUpdate();

		g_Player[i].spd *= 0.7f;
		g_Player[i].moveVec.x *= 0.8f;
		g_Player[i].moveVec.z *= 0.8f;

		//���X�L���[�o���b�g����
		UpdateRescueMode();
		CheckRescue();


		InvincibleFunc(&g_Player[i]);
		UpdateArm();
	}
#ifdef _DEBUG
	PrintDebugProc("�v���C���[���WX:%f, Z:%f\n", g_Player[0].pos.x, g_Player[0].pos.z);
	PrintDebugProc("\n�v���C���[�A�[��X:%f\n", g_Player[0].rescueBullet[0].x);
	PrintDebugProc("�v���C���[�A�[��Z:%f\n", g_Player[0].rescueBullet[0].z);
#endif
}

void IPUpdate(void)
{
	if (g_Player[0].spd >= VALUE_MOVE * VALUE_MOVE_DASH)
	{
		for (int k = 0; k < MAX_PLAYER_PARTS + 1; k++)
		{
			if (g_Playerline[k].old_data != run_data[k])
				g_Playerline[k].move_time = 0.0f;

			PlayerPartsIP(&g_Playerline[k], run_data[k], run_data_size[k]);
			g_Playerline[k].old_data = run_data[k];
		}
	}
	else if (g_Player[0].spd > 0.1f && g_Player[0].spd < VALUE_MOVE * VALUE_MOVE_DASH)
	{
		for (int k = 0; k < MAX_PLAYER_PARTS + 1; k++)
		{
			if (g_Playerline[k].old_data != walk_data[k])
				g_Playerline[k].move_time = 0.0f;

			PlayerPartsIP(&g_Playerline[k], walk_data[k], data_size[k]);
			g_Playerline[k].old_data = walk_data[k];
		}
	}
	else
	{
		for (int k = 0; k < MAX_PLAYER_PARTS + 1; k++)
		{
			if (g_Playerline[k].old_data != stop_data[k])
				g_Playerline[k].move_time = 0.0f;

			PlayerPartsIP(&g_Playerline[k], stop_data[k], stop_data_size[k]);
			g_Playerline[k].old_data = stop_data[k];
		}
	}
}
void ResultIPUpdate(void)
{
	for (int k = 0; k < MAX_PLAYER_PARTS + 1; k++)
	{
		PlayerPartsIP(&g_Playerline[k], walk_data[k], data_size[k]);
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPlayer(void)
{
	// �J�����O����
	SetCullingMode(CULL_MODE_NONE);

	XMMATRIX mtxScl, mtxRot, mtxTranslate, mtxWorld;

	for (int i = 0; i < MAX_PLAYER; i++)
	{
		if (g_Player[i].use != TRUE)continue;
		// ���[���h�}�g���b�N�X�̏�����
		mtxWorld = XMMatrixIdentity();

		// �X�P�[���𔽉f
		mtxScl = XMMatrixScaling(g_Player[i].scl.x + g_Playerline[i].scl.x, g_Player[i].scl.y + g_Playerline[i].scl.y, g_Player[i].scl.z + g_Playerline[i].scl.z);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxScl);

		// ��]�𔽉f
		mtxRot = XMMatrixRotationRollPitchYaw(g_Player[i].rot.x + g_Playerline[i].rot.x, g_Player[i].rot.y - XM_PI * 0.5f + g_Playerline[i].rot.y, g_Player[i].rot.z + g_Playerline[i].rot.z);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxRot);

		// �ړ��𔽉f
		mtxTranslate = XMMatrixTranslation(g_Player[i].pos.x + g_Playerline[i].pos.x, g_Player[i].pos.y + g_Playerline[i].pos.y, g_Player[i].pos.z + g_Playerline[i].pos.z);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxTranslate);

		// ���[���h�}�g���b�N�X�̐ݒ�
		SetWorldMatrix(&mtxWorld);

		XMStoreFloat4x4(&g_Player[i].mtxWorld, mtxWorld);

		// ���f���`��
		DrawModel(&g_Player[i].model);

		if (g_Player[i].partsNum == 0)continue;

		// �p�[�c�̊K�w�A�j���[�V����
		for (int k = g_Player[i].startNum; k < g_Player[i].startNum + g_Player[i].partsNum; k++)
		{
			int num = k + 1;	//���`�⊮�f�[�^�̓Y�����v�Z
			// ���[���h�}�g���b�N�X�̏�����
			mtxWorld = XMMatrixIdentity();

			// �X�P�[���𔽉f
			mtxScl = XMMatrixScaling(g_Parts[k].scl.x + g_Playerline[num].scl.x, g_Parts[k].scl.y + g_Playerline[num].scl.y, g_Parts[k].scl.z + g_Playerline[num].scl.z);
			mtxWorld = XMMatrixMultiply(mtxWorld, mtxScl);

			// ��]�𔽉f
			mtxRot = XMMatrixRotationRollPitchYaw(g_Parts[k].rot.x + g_Playerline[num].rot.x, g_Parts[k].rot.y + g_Playerline[num].rot.y, g_Parts[k].rot.z + g_Playerline[num].rot.z);
			mtxWorld = XMMatrixMultiply(mtxWorld, mtxRot);

			// �ړ��𔽉f
			mtxTranslate = XMMatrixTranslation(g_Parts[k].pos.x + g_Playerline[num].pos.x, g_Parts[k].pos.y + g_Playerline[num].pos.y, g_Parts[k].pos.z + g_Playerline[num].pos.z);
			mtxWorld = XMMatrixMultiply(mtxWorld, mtxTranslate);

			if (g_Parts[k].parent != NULL)	// �q����������e�ƌ�������
			{
				mtxWorld = XMMatrixMultiply(mtxWorld, XMLoadFloat4x4(&g_Parts[k].parent->mtxWorld));
				// ��
				// g_Player[i].mtxWorld���w���Ă���
			}

			XMStoreFloat4x4(&g_Parts[k].mtxWorld, mtxWorld);

			// �g���Ă���Ȃ珈������B�����܂ŏ������Ă��闝�R�͑��̃p�[�c�����̃p�[�c���Q�Ƃ��Ă���\�������邩��B
			if (g_Parts[k].load == FALSE) continue;

			// ���[���h�}�g���b�N�X�̐ݒ�
			SetWorldMatrix(&mtxWorld);

			// ���f���`��
			DrawModel(&g_Parts[k].model);
		}
		//�A�[�����f���`��
		g_Arm[0]->Draw();

		//�~�o�������m�[�}���A�[���̕`����s��
		if (g_Player[0].rescue)
			Normal::Draw();
	}

	// �J�����O�ݒ��߂�
	SetCullingMode(CULL_MODE_BACK);
}


//�ҋ@Ӱ��ݏ���
void PlayerStandLiner(int i)
{
	if (g_Player[i].tbl_adrM == NULL)return;	// ���`��Ԃ����s����H

//
// ���`��Ԃ̏���
// �ړ�����
	int		index = (int)g_Player[i].move_time;
	float	time = g_Player[i].move_time - index;
	int		size = g_Player[i].tbl_sizeM;

	float dt = 1.0f / g_Player[i].tbl_adrM[index].frame;	// 1�t���[���Ői�߂鎞��
	g_Player[i].move_time += dt;							// �A�j���[�V�����̍��v���Ԃɑ���

	if (index > (size - 2))	// �S�[�����I�[�o�[���Ă�����A�f�[�^���ŏ��ɖ߂��čU�����I��
	{
		g_Player[i].move_time = 0.0f;
		index = 0;
		g_Playerline[i].pos = { 0.0f, 0.0f, 0.0f };
		g_Playerline[i].rot = { 0.0f, 0.0f, 0.0f };
		g_Playerline[i].scl = { 0.0f, 0.0f, 0.0f };
	}

	// ���W�����߂�	X = StartX + (EndX - StartX) * ���̎���
	XMVECTOR p1 = XMLoadFloat3(&g_Player[i].tbl_adrM[index + 1].pos);	// ���̏ꏊ
	XMVECTOR p0 = XMLoadFloat3(&g_Player[i].tbl_adrM[index + 0].pos);	// ���݂̏ꏊ
	XMVECTOR vec = p1 - p0;
	XMStoreFloat3(&g_Playerline[i].pos, p0 + vec * time);

	// ��]�����߂�	R = StartX + (EndX - StartX) * ���̎���
	XMVECTOR r1 = XMLoadFloat3(&g_Player[i].tbl_adrM[index + 1].rot);	// ���̊p�x
	XMVECTOR r0 = XMLoadFloat3(&g_Player[i].tbl_adrM[index + 0].rot);	// ���݂̊p�x
	XMVECTOR rot = r1 - r0;
	XMStoreFloat3(&g_Playerline[i].rot, r0 + rot * time);

	// scale�����߂� S = StartX + (EndX - StartX) * ���̎���
	XMVECTOR s1 = XMLoadFloat3(&g_Player[i].tbl_adrM[index + 1].scl);	// ����Scale
	XMVECTOR s0 = XMLoadFloat3(&g_Player[i].tbl_adrM[index + 0].scl);	// ���݂�Scale
	XMVECTOR scl = s1 - s0;
	XMStoreFloat3(&g_Playerline[i].scl, s0 + scl * time);

	for (int k = g_Player[i].startNum; k < g_Player[i].startNum + g_Player[i].partsNum; k++)
	{
		if (g_Parts[k].tbl_adrM == NULL)continue;;	// ���`��Ԃ����s����H

		int		index = (int)g_Parts[k].move_time;
		float	time = g_Parts[k].move_time - index;
		int		size = g_Parts[k].tbl_sizeM;

		float dt = 1.0f / g_Parts[k].tbl_adrM[index].frame;	// 1�t���[���Ői�߂鎞��
		g_Parts[k].move_time += dt;							// �A�j���[�V�����̍��v���Ԃɑ���

		if (index > (size - 2))	// �S�[�����I�[�o�[���Ă�����A�f�[�^���ŏ��ɖ߂��čU�����I��
		{
			g_Parts[k].move_time = 0.0f;
			index = 0;
		}

		// ���W�����߂�	X = StartX + (EndX - StartX) * ���̎���
		XMVECTOR p1 = XMLoadFloat3(&g_Parts[k].tbl_adrM[index + 1].pos);	// ���̏ꏊ
		XMVECTOR p0 = XMLoadFloat3(&g_Parts[k].tbl_adrM[index + 0].pos);	// ���݂̏ꏊ
		XMVECTOR vec = p1 - p0;
		XMStoreFloat3(&g_Parts[k].pos, p0 + vec * time);

		// ��]�����߂�	R = StartX + (EndX - StartX) * ���̎���
		XMVECTOR r1 = XMLoadFloat3(&g_Parts[k].tbl_adrM[index + 1].rot);	// ���̊p�x
		XMVECTOR r0 = XMLoadFloat3(&g_Parts[k].tbl_adrM[index + 0].rot);	// ���݂̊p�x
		XMVECTOR rot = r1 - r0;
		XMStoreFloat3(&g_Parts[k].rot, r0 + rot * time);

		// scale�����߂� S = StartX + (EndX - StartX) * ���̎���
		XMVECTOR s1 = XMLoadFloat3(&g_Parts[k].tbl_adrM[index + 1].scl);	// ����Scale
		XMVECTOR s0 = XMLoadFloat3(&g_Parts[k].tbl_adrM[index + 0].scl);	// ���݂�Scale
		XMVECTOR scl = s1 - s0;
		XMStoreFloat3(&g_Parts[k].scl, s0 + scl * time);
	}
}

//�v���C���[�̐��`���
void PlayerPartsIP(Playerliner* p, INTERPOLATION_DATA *i, int t_size)
{
	if (p->tbl_adrM == NULL)return;
	//
	// ���`��Ԃ̏���
	// �ړ�����
	int		index = (int)p->move_time;
	float	time = p->move_time - index;
	int		size = t_size;

	float dt = 1.0f / i[index].frame;	// 1�t���[���Ői�߂鎞��
	p->move_time += dt;							// �A�j���[�V�����̍��v���Ԃɑ���

	if (index > (size - 2))	// �S�[�����I�[�o�[���Ă�����A�f�[�^���ŏ��ɖ߂��čU�����I��
	{
		p->move_time = 0.0f;
		index = 0;
	}
	// ���W�����߂�	X = StartX + (EndX - StartX) * ���̎���
	XMVECTOR p1 = XMLoadFloat3(&i[index + 1].pos);	// ���̏ꏊ
	XMVECTOR p0 = XMLoadFloat3(&i[index + 0].pos);	// ���݂̏ꏊ
	XMVECTOR vec = p1 - p0;
	XMStoreFloat3(&p->pos, p0 + vec * time);

	// ��]�����߂�	R = StartX + (EndX - StartX) * ���̎���
	XMVECTOR r1 = XMLoadFloat3(&i[index + 1].rot);	// ���̊p�x
	XMVECTOR r0 = XMLoadFloat3(&i[index + 0].rot);	// ���݂̊p�x
	XMVECTOR rot = r1 - r0;
	XMStoreFloat3(&p->rot, r0 + rot * time);

	// scale�����߂� S = StartX + (EndX - StartX) * ���̎���
	XMVECTOR s1 = XMLoadFloat3(&i[index + 1].scl);	// ����Scale
	XMVECTOR s0 = XMLoadFloat3(&i[index + 0].scl);	// ���݂�Scale
	XMVECTOR scl = s1 - s0;
	XMStoreFloat3(&p->scl, s0 + scl * time);
}


//=============================================================================
// �v���C���[�����擾
//=============================================================================
PLAYER *GetPlayer(void)
{
	return &g_Player[0];
}


void MovePlayer(void)
{
	CAMERA *cam = GetCamera();
	float old_x = g_Player[0].pos.x;
	float old_z = g_Player[0].pos.z;
	// Key���͂���������ړ���������
	if (g_Player[0].spd > 0.1f)
	{
		float angle = atan2f(g_Player[0].moveVec.x, g_Player[0].moveVec.z);

		if (!g_Player[0].attack && !g_Player[0].rescue)
		g_Player[0].rot.y = angle;
	}
	//�ړ��l���x�N�g���ϊ����Ĉړ�������
	XMVECTOR moveVec = XMLoadFloat3(&g_Player[0].moveVec);
	XMVECTOR now = XMLoadFloat3(&g_Player[0].pos);								// ���݂̏ꏊ
	XMStoreFloat3(&g_Player[0].pos, now + XMVector3Normalize(moveVec) * g_Player[0].spd);	//�P�ʃx�N�g�������Ɉړ�
	MeshWallHit(g_Player[0].pos, 15.0f, old_x, old_z);

}
void ControlPlayer(void)
{
	CAMERA *cam = GetCamera();
	float changeRotCamera = 0.025f; //�X�����x
	// �ړ��{�^��
	if (IsButtonPressed(0, BUTTON_LEFT) || GetKeyboardPress(DIK_A))
	{	// ���ֈړ�
		g_Player[0].spd = VALUE_MOVE;
		g_Player[0].moveVec.x -= cosf(cam->rot.y) * changeRotCamera;
		g_Player[0].moveVec.z += sinf(cam->rot.y) * changeRotCamera;
	}
	if (IsButtonPressed(0, BUTTON_RIGHT) || GetKeyboardPress(DIK_D))
	{	// �E�ֈړ�
		g_Player[0].spd = VALUE_MOVE;
		g_Player[0].moveVec.x += cosf(cam->rot.y) * changeRotCamera;
		g_Player[0].moveVec.z -= sinf(cam->rot.y) * changeRotCamera;
	}
	if (IsButtonPressed(0, BUTTON_UP) || GetKeyboardPress(DIK_W))
	{	// ��ֈړ�
		g_Player[0].spd = VALUE_MOVE;
		g_Player[0].moveVec.x += sinf(cam->rot.y) * changeRotCamera;
		g_Player[0].moveVec.z += cosf(cam->rot.y) * changeRotCamera;
	}
	if (IsButtonPressed(0, BUTTON_DOWN) || GetKeyboardPress(DIK_S))
	{	// ���ֈړ�
		g_Player[0].spd = VALUE_MOVE;
		g_Player[0].moveVec.x -= sinf(cam->rot.y) * changeRotCamera;
		g_Player[0].moveVec.z -= cosf(cam->rot.y) * changeRotCamera;
	}

	if (GetKeyboardPress(DIK_B))
		g_Player[0].spd = VALUE_MOVE * VALUE_MOVE_DASH;

	if (GetKeyboardTrigger(DIK_RETURN))
	{
		fout << "���W:(" << g_Player[0].pos.x << "," << g_Player[0].pos.y << "," << g_Player[0].pos.z << ")" << endl;
	}

}

void ControlCamera(void)
{
	CAMERA *g_Cam = GetCamera();
	if (GetKeyboardPress(DIK_Q) || IsButtonPressed(0, BUTTON_R_LEFT))
	{// �����_����u���v
		g_Cam->rot.y -= VALUE_ROTATE_CAMERA;
		if (g_Cam->rot.y < -XM_PI)
		{
			g_Cam->rot.y += XM_PI * 2.0f;
		}

	}
	else if (GetKeyboardPress(DIK_E) || IsButtonPressed(0, BUTTON_R_RIGHT))
	{// �����_����u�E�v
		g_Cam->rot.y += VALUE_ROTATE_CAMERA;
		if (g_Cam->rot.y > XM_PI)
		{
			g_Cam->rot.y -= XM_PI * 2.0f;
		}

	}
	if (GetKeyboardPress(DIK_UP))
	{
		if (g_Cam->rot.x < 0.45f)
		g_Cam->rot.x += XM_PI * 0.004f;
	}
	else if (GetKeyboardPress(DIK_DOWN))
	{
		if (g_Cam->rot.x > 0.0f)
		g_Cam->rot.x -= XM_PI * 0.004f;
	}
}

void ControlChangeArm(void)
{
	if (GetKeyboardTrigger(DIK_F))
	{
		ChangePlayerArm(TRUE);
	}
	else if (GetKeyboardTrigger(DIK_G))
	{
		ChangePlayerArm(FALSE);
	}
}
//�������i�K�ł̃A�[���Z�b�g
void SetPlayerArm(void)
{
	g_PlayerArm[0] = Xgun::GetArm();
	g_PlayerArm[1] = Braster::GetArm();
	g_PlayerArm[2] = Saw::GetArm();
}

//�A�[���̐؂�ւ�
void ChangePlayerArm(BOOL flag)
{
	if (g_Player[0].attack)return;	//�U�����Ȃ�ύX�s��
		//�U���̌㌄���ɍU���{�^���������Ƒ��ڍs
	//else if (GetKeyboardTrigger(DIK_Z) && !g_Player[0].attack && arm[g_Player[0].armType].attack && g_Player[0].attack_num < 2)
	//{
	//	g_Player[0].attack_num++;

	//}

	pArm* arm = pArm::GetArmParts();
	for (int i = 0; i < MAX_ARM_PARTS * 2; i++)
	{
		arm[i].ct_frame = 0.0f;
		arm[i].move_time = 0.0f;
		arm[i].spead = 0.0f;
	}

	if (flag)
	{
		g_Player[0].armType++;
		if (g_Player[0].armType >= ARM_VAR)
			g_Player[0].armType = 0;
	}
	else
	{
		g_Player[0].armType--;
		if (g_Player[0].armType < 0)
			g_Player[0].armType = ARM_VAR - 1;
	}
}

void UpdateArm(void)
{
	//pArm::UpdateArm();
	pArm::UpdateReleaseArm();	//�����[�X���͂��������g��
	pArm* arm = pArm::GetArmParts();
	//�U���J�n
	if (GetKeyboardTrigger(DIK_Z) && !g_Player[0].attack)
	{
		g_Player[0].attack = TRUE;
		for (int i = 0; i < MAX_ARM_PARTS * 2; i++)
		{
			arm[i].ct_frame = 0.0f;
			arm[i].move_time = 0.0f;
			arm[i].spead = 0.0f;
		}
		g_Player[0].attack_num++;
	}
	
	if (GetKeyboardTrigger(DIK_0) && g_Player[0].n_motionTime <= 0.0f)
	{
		g_Player[0].rescue = TRUE;
		g_Player[0].rescueUse = FALSE;
		XMFLOAT3 pos = g_Player[0].pos;
		XMFLOAT3 pos2 = g_Player[0].pos;
		const float dist = 5.0f;
		float high = 0.0f;
		pos.x += sinf(g_Player[0].rot.y + XM_PI * 0.20f) * dist;
		pos.y = high;
		pos.z += cosf(g_Player[0].rot.y + XM_PI * 0.20f) * dist;

		pos2.x += sinf(g_Player[0].rot.y - XM_PI * 0.20f) * dist;
		pos2.y = high;
		pos2.z += cosf(g_Player[0].rot.y - XM_PI * 0.20f) * dist;
		g_Player[0].rescueBullet[0] = pos;
		g_Player[0].rescueBullet[1] = pos2;

	}
	//�A�[���ʂɍU������
	if (g_Player[0].attack)
	{
		switch (g_Player[0].armType)
		{
		case 0:
			Xgun::Action();
			break;
		case 1:
			Braster::Action();
			break;
		case 2:
			Saw::Action();
			break;

		}
	}

	if (g_Player[0].rescue)
	{
		if (g_Player[0].n_motionTime <= 0.0f)
			g_Player[0].n_motionTime = 60.0f;

		Normal::UpdateArm();
		g_Player[0].n_motionTime -= 1.0f;
	}

	////���[�V�������Ԃŏ������I��������
	//if (g_Player[0].motionTime <= 0.0f)
	//	g_Player[0].attack = FALSE;
	//���[�V�������Ԃŏ������I��������
	if (g_Player[0].n_motionTime <= 0.0f) {
		g_Player[0].rescue = FALSE;
		g_Player[0].cntBullet = 0.0f;
	}
}

void InvincibleFunc(PLAYER *p)
{
	if (!p->invincible)return;

	if (p->inv_time == PLAYER_INVINC_FLAME)
	{
		FadeCharacter(&g_Player[0].model, 1);
		for (int i = 0; i < MAX_PLAYER_PARTS; i++) {
			FadeCharacter(&g_Parts[i].model, 1);
		}

	}

	p->inv_time -= 1.0f;

	if (p->inv_time <= 0.0f)
	{
		p->invincible = FALSE;
		p->inv_time = PLAYER_INVINC_FLAME;
		FadeCharacter(&g_Player[0].model, 0);
		for (int i = 0; i < MAX_PLAYER_PARTS; i++) {
			FadeCharacter(&g_Parts[i].model, 0);
		}
	}
}

void UpdateRescueMode(void)
{
	if (g_Player[0].rescue && g_Player[0].n_motionTime > 30.0f && !g_Player[0].rescueUse)
		g_Player[0].cntBullet += VALUE_AT_MOVE;
	else if ((g_Player[0].rescue && g_Player[0].n_motionTime <= 30.0f) || g_Player[0].rescueUse)
		g_Player[0].cntBullet -= VALUE_AT_MOVE;

	for (int k = 0; k < 2; k++)
	{
		g_Player[0].rescueBullet[k].x = g_Player[0].pos.x + sinf(g_Player[0].rot.y) * g_Player[0].cntBullet;
		g_Player[0].rescueBullet[k].z = g_Player[0].pos.z + cosf(g_Player[0].rot.y) * g_Player[0].cntBullet;
	}
	if (g_Player[0].rescueUse)
	{
		g_Player[0].rs->pos = g_Player[0].rescueBullet[0];
	}

	if (g_Player[0].rescueUse && g_Player[0].cntBullet <= 0.0f) {
		g_Player[0].rs->use = FALSE;
		g_Player[0].rs->rescue = TRUE;
		Reward* re = GetReward();
		re->rescue_num++;
	}


	if (g_Player[0].cntBullet <= 0.0f)
		g_Player[0].rescueUse = FALSE;
}

//�~�o�������̃`�F�b�N
void CheckRescue(void)
{
	if (!g_Player[0].rescue || g_Player[0].rescueUse)return;

	RescueLife* rs = RescueLife::GetRescueLife();
	for(int i = 0; i < 2; i++)
	{ 
		for (int k = 0; k < MAX_RESCUE; k++) {
			if (!rs[k].use)continue;

			if (!CollisionBC(rs[k].pos, g_Player[0].rescueBullet[i], 15.0f, 15.0f))
				continue;

			g_Player[0].rescueUse = TRUE;
			g_Player[0].rs = &rs[k];
		}
	}
}

HRESULT MakeVertexPlayerVar(void)
{
	// ���_�o�b�t�@����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	GetDevice()->CreateBuffer(&bd, NULL, &g_VertexBuffer);


	{//���_�o�b�t�@�̒��g�𖄂߂�
		D3D11_MAPPED_SUBRESOURCE msr;
		GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

		VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

		// ���_���W�̐ݒ�
		vertex[0].Position = XMFLOAT3(-VAR_WIDTH / 2, 0.0f, VAR_HEIGHT / 2);
		vertex[1].Position = XMFLOAT3(VAR_WIDTH / 2, 0.0f, VAR_HEIGHT / 2);
		vertex[2].Position = XMFLOAT3(-VAR_WIDTH / 2, 0.0f, -VAR_HEIGHT / 2);
		vertex[3].Position = XMFLOAT3(VAR_WIDTH / 2, 0.0f, -VAR_HEIGHT / 2);

		// �@���̐ݒ�
		vertex[0].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
		vertex[1].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
		vertex[2].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
		vertex[3].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);

		// �g�U���̐ݒ�
		vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`�����W�̐ݒ�
		vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);
		vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);
		vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);
		vertex[3].TexCoord = XMFLOAT2(1.0f, 1.0f);

		GetDeviceContext()->Unmap(g_VertexBuffer, 0);
	}

	return S_OK;
}
