//=============================================================================
//
// �o�g�����̃G�l�~�[���� [enemy.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "camera.h"
#include "debugproc.h"
#include "model.h"
#include "game.h"
#include "enemy.h"
#include "shadow.h"
#include "light.h"
#include "meshfield.h"
#include "collision.h"
#include "time.h"
#include "enemyLinerData.h"
#include "unitdata.h"
#include "base.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_MAX			(1)								// �e�N�X�`���̐�
#define VAR_WIDTH			(50.0f)
#define VAR_HEIGHT			(5.0f)
#define	VALUE_MOVE			(2.0f)							// �ړ���
#define	VALUE_AT_MOVE		(4.0f)							// �ړ���
#define	VALUE_ROTATE		(XM_PI * 0.02f)					// ��]��
#define ENEMY_VAR			(4)
#define ENEMY_PARTS_VAR		(ENEMY_VAR * 3)
#define ENEMY_SHADOW_SIZE	(1.0f)							// �e�̑傫��
#define ENEMY_OFFSET_Y		(0.0f)							// �v���C���[�̑��������킹��
#define ENEMY_OFFSET_Z		(-300.0f)							// �v���C���[�̑��������킹��
#define ENEMY_LIFE			(100)								// �v���C���[�̃��C�t

#define ENEMY_PARTS_MAX	(1)								// �v���C���[�̃p�[�c�̐�
#define ENEMY_AT_FLAME		(30.0f)							// �v���C���[�̍U���t���[��
#define ENEMY_INVINC_FLAME	(120.0f)						// �v���C���[���G�t���[��
#define MAX_ENEMY_PARTS (MAX_ENEMY * 3)
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
static PLAYER_VAR	g_EnemyVar;
static ENEMY		g_Enemy[MAX_ENEMY];						// �G�l�~�[
static Enemyliner   g_Enemyline[MAX_ENEMY];
static EnemyParts	g_Parts[MAX_ENEMY_PARTS];					// �G�l�~�[�̃p�[�c�B�]�T�������ăG�l�~�[�~2�{�̐��p��
static Unit			g_EnemyModel[ENEMY_VAR];
static Unit			g_EnemyPartsModel[ENEMY_PARTS_VAR];
static BOOL			g_Load = FALSE;
static int			atCount;
static int			enemyNum = 0;		//���̂̃G�l�~�[�����邩
static int			banishEnemy = 0;		//���̂̃G�l�~�[�����񂾂̂�
static int			partsNum = 0;		//���v�ł����̃p�[�c���g���̂�



//=============================================================================
// ����������
//=============================================================================
HRESULT InitEnemy(void)
{
	ID3D11Device *pDevice = GetDevice();
	MakeVertexEnemyVar();
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

	ZeroMemory(&g_EnemyVar.material, sizeof(g_EnemyVar.material));
	g_EnemyVar.material.Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	g_EnemyVar.pos = { 0.0f, 0.0f, 0.0f };
	g_EnemyVar.rot = { XM_PI * -0.5f, 0.0f, 0.0f };
	g_EnemyVar.scl = { 1.0f, 1.0f, 1.0f };
	g_EnemyVar.load = TRUE;
	int num = 0;
	int p_num = 0;
	{//�u�h�E���ۃ��f���ǂݍ���
		LoadModel(MODEL_GRAPE, &g_EnemyModel[num].model);
		// ���f���̃f�B�t���[�Y��ۑ����Ă����B�F�ς��Ή��ׁ̈B
		GetModelDiffuse(&g_EnemyModel[num].model, &g_Enemy[num].diffuse[0]);
		num++;

		LoadModel(MODEL_GRAPE_PARTS001, &g_EnemyPartsModel[p_num].model);
		// ���f���̃f�B�t���[�Y��ۑ����Ă����B�F�ς��Ή��ׁ̈B
		GetModelDiffuse(&g_EnemyPartsModel[p_num].model, &g_Parts[p_num].diffuse[0]);
		p_num++;
		LoadModel(MODEL_GRAPE_PARTS002, &g_EnemyPartsModel[p_num].model);
		// ���f���̃f�B�t���[�Y��ۑ����Ă����B�F�ς��Ή��ׁ̈B
		GetModelDiffuse(&g_EnemyPartsModel[p_num].model, &g_Parts[p_num].diffuse[0]);
		p_num++;
		LoadModel(MODEL_GRAPE_PARTS003, &g_EnemyPartsModel[p_num].model);
		// ���f���̃f�B�t���[�Y��ۑ����Ă����B�F�ς��Ή��ׁ̈B
		GetModelDiffuse(&g_EnemyPartsModel[p_num].model, &g_Parts[p_num].diffuse[0]);
		p_num++;
	}
	{//A�Q���n�A�ۃ��f���ǂݍ���
		LoadModel(MODEL_STREPT, &g_EnemyModel[num].model);
		// ���f���̃f�B�t���[�Y��ۑ����Ă����B�F�ς��Ή��ׁ̈B
		GetModelDiffuse(&g_Enemy[num].model, &g_EnemyModel[num].diffuse[0]);
		num++;

		LoadModel(MODEL_STREPT_HEAD, &g_EnemyPartsModel[p_num].model);
		// ���f���̃f�B�t���[�Y��ۑ����Ă����B�F�ς��Ή��ׁ̈B
		GetModelDiffuse(&g_EnemyPartsModel[p_num].model, &g_EnemyPartsModel[p_num].diffuse[0]);
		p_num++;
		LoadModel(MODEL_STREPT_NECK, &g_EnemyPartsModel[p_num].model);
		// ���f���̃f�B�t���[�Y��ۑ����Ă����B�F�ς��Ή��ׁ̈B
		GetModelDiffuse(&g_EnemyPartsModel[p_num].model, &g_EnemyPartsModel[p_num].diffuse[0]);
		p_num++;
		LoadModel(MODEL_STREPT_TAIL, &g_EnemyPartsModel[p_num].model);
		// ���f���̃f�B�t���[�Y��ۑ����Ă����B�F�ς��Ή��ׁ̈B
		GetModelDiffuse(&g_EnemyPartsModel[p_num].model, &g_EnemyPartsModel[p_num].diffuse[0]);
		p_num++;
	}
	{//�Δ^�ۃ��f���ǂݍ���
		LoadModel(MODEL_RYOKU, &g_EnemyModel[num].model);
		// ���f���̃f�B�t���[�Y��ۑ����Ă����B�F�ς��Ή��ׁ̈B
		GetModelDiffuse(&g_Enemy[num].model, &g_EnemyModel[num].diffuse[0]);
		num++;

		LoadModel(MODEL_RYOKU_LEFT, &g_EnemyPartsModel[p_num].model);
		// ���f���̃f�B�t���[�Y��ۑ����Ă����B�F�ς��Ή��ׁ̈B
		GetModelDiffuse(&g_EnemyPartsModel[p_num].model, &g_EnemyPartsModel[p_num].diffuse[0]);
		p_num++;
		LoadModel(MODEL_RYOKU_RIGHT, &g_EnemyPartsModel[p_num].model);
		// ���f���̃f�B�t���[�Y��ۑ����Ă����B�F�ς��Ή��ׁ̈B
		GetModelDiffuse(&g_EnemyPartsModel[p_num].model, &g_EnemyPartsModel[p_num].diffuse[0]);
		p_num++;
	}
	{//�u�h�E���ۃ��f���ǂݍ���
		LoadModel(MODEL_INFLUE, &g_EnemyModel[num].model);
		// ���f���̃f�B�t���[�Y��ۑ����Ă����B�F�ς��Ή��ׁ̈B
		GetModelDiffuse(&g_EnemyModel[num].model, &g_Enemy[num].diffuse[0]);
		num++;

		LoadModel(MODEL_INFLUE, &g_EnemyPartsModel[p_num].model);
		// ���f���̃f�B�t���[�Y��ۑ����Ă����B�F�ς��Ή��ׁ̈B
		GetModelDiffuse(&g_EnemyPartsModel[p_num].model, &g_Parts[p_num].diffuse[0]);
		p_num++;
		LoadModel(MODEL_INFLUE, &g_EnemyPartsModel[p_num].model);
		// ���f���̃f�B�t���[�Y��ۑ����Ă����B�F�ς��Ή��ׁ̈B
		GetModelDiffuse(&g_EnemyPartsModel[p_num].model, &g_Parts[p_num].diffuse[0]);
		p_num++;
	}



	for (int i = 0; i < MAX_ENEMY; i++)
	{
		g_Enemy[i].load = FALSE;

		g_Enemy[i].pos = { -100.0f, ENEMY_OFFSET_Y, 0.0f };
		g_Enemy[i].rot = { 0.0f, 0.0f, 0.0f };
		g_Enemy[i].scl = { 0.8f, 1.0f, 1.0f };

		g_Enemy[i].size = ENEMY_SIZE;	// �����蔻��̑傫��
		g_Enemy[i].state = Move;
		g_Enemy[i].life = ENEMY_LIFE;
		g_Enemy[i].lifeMax = g_Enemy[i].life;
		g_Enemy[i].use = FALSE;
		g_Enemy[i].attack = FALSE;
		g_Enemy[i].attackUse = FALSE;
		g_Enemy[i].start = 0;
		g_Enemy[i].tbl_adrA = NULL;	// �A�j���f�[�^�̃e�[�u���擪�A�h���X
		g_Enemy[i].tbl_adrM = NULL;	// �A�j���f�[�^�̃e�[�u���擪�A�h���X
		g_Enemy[i].tbl_sizeA = 0;	// �o�^�����e�[�u���̃��R�[�h����
		g_Enemy[i].tbl_sizeM = 0;	// �o�^�����e�[�u���̃��R�[�h����
		g_Enemy[i].move_time = 0;	// ���s����
		g_Enemy[i].partsNum = 0;
		g_Enemy[i].startNum = 0;
		// �K�w�A�j���[�V�����p�̏���������
		g_Enemy[i].parent = NULL;			// �{�́i�e�j�Ȃ̂�NULL������
	}
	for (int i = 0; i < MAX_ENEMY_PARTS; i++)
	{
		g_Parts[i].pos = { 0.0f, 0.0f, 0.0f };		// �|���S���̈ʒu
		g_Parts[i].rot = { 0.0f, 0.0f, 0.0f };		// �|���S���̌���(��])
		g_Parts[i].scl = {1.0f, 1.0f, 1.0f};		// �|���S���̑傫��(�X�P�[��)

		g_Parts[i].load = FALSE;
		// �K�w�A�j���[�V�����p�̃����o�[�ϐ�
		g_Parts[i].tbl_adrA = NULL;	// �A�j���f�[�^�̃e�[�u���擪�A�h���X
		g_Parts[i].tbl_adrM = NULL;	// �A�j���f�[�^�̃e�[�u���擪�A�h���X
		g_Parts[i].tbl_sizeA = 0;	// �o�^�����e�[�u���̃��R�[�h����
		g_Parts[i].tbl_sizeM = 0;	// �o�^�����e�[�u���̃��R�[�h����
		g_Parts[i].move_time = 0;	// ���s����
		g_Parts[i].parent = NULL;	// �������e�Ȃ�NULL�A�������q���Ȃ�e��enemy�A�h���X
	}

	for (int i = 0; i < MAX_ENEMY; i++)
	{
		g_Enemyline[i].pos = { 0.0f, 0.0f, 0.0f };
		g_Enemyline[i].rot = { 0.0f, 0.0f, 0.0f };
		g_Enemyline[i].scl = { 0.0f, 0.0f, 0.0f };
	}
	enemyNum = 0;
	banishEnemy = 0;
	partsNum = 0;
	g_Load = TRUE;
	atCount = 0;
	return S_OK;

}

//=============================================================================
// �I������
//=============================================================================
void UninitEnemy(void)
{
	if (g_Load == FALSE) return;
	// ���_�o�b�t�@�̉��
	if (g_VertexBuffer)
	{
		g_VertexBuffer->Release();
		g_VertexBuffer = NULL;
	}

	for (int i = 0; i < MAX_ENEMY; i++)
	{
		// ���f���̉������
		if (g_Enemy[i].load)
		{
			UnloadModel(&g_Enemy[i].model);
			g_Enemy[i].load = FALSE;
		}
	}
	for (int i = 0; i < MAX_ENEMY_PARTS; i++)
	{
		// ���f���̉������
		if (g_Parts[i].load)
		{
			UnloadModel(&g_Parts[i].model);
			g_Parts[i].load = FALSE;
		}
	}
	for (int i = 0; i < ENEMY_VAR; i++)
	{
		UnloadModel(&g_EnemyModel[i].model);
		g_EnemyModel[i].load = FALSE;
	}
	for (int i = 0; i < ENEMY_PARTS_VAR; i++)
	{
			UnloadModel(&g_EnemyPartsModel[i].model);
			g_EnemyPartsModel[i].load = FALSE;
	}
	g_Load = FALSE;
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEnemy(void)
{
	for (int i = 0; i < enemyNum; i++)
	{
		//���[���x�[�X�œG���U�����A�X�e�[�g�x�[�X�őJ�ڂ��s���B���`��Ԃňړ�

		SetEnemyTime(i);	//�G�l�~�[�̏o���`�F�b�N

		//�|���ꂽ�G�l�~�[�̍X�V
		if (g_Enemy[i].life <= 0 && g_Enemy[i].use) {
			g_Enemy[i].use = FALSE;
			banishEnemy++;
			continue;
		}

		if (g_Enemy[i].use != TRUE)continue;	//����ł邩�o�����ĂȂ��z�̓X���[

		int oldState = g_Enemy[i].state;
		//�G�l�~�[�̃X�e�[�g����
		g_Enemy[i].state = StateCheck(i);
		if (oldState != g_Enemy[i].state)
		{
			g_Enemy[i].move_time = 0;	// ���s����
			g_Enemy[i].atCount = 0;
			g_Enemy[i].attackUse = FALSE;
			g_Enemyline[i].pos = { 0.0f, 0.0f, 0.0f };
			g_Enemyline[i].rot = { 0.0f, 0.0f, 0.0f };
			g_Enemyline[i].scl = { 0.0f, 0.0f, 0.0f };
			for (int k = g_Enemy[i].startNum; k < g_Enemy[i].startNum + g_Enemy[i].partsNum; k++)
				g_Parts[k].move_time = 0.0f;
		}

		CheckTarget(i);
		switch (g_Enemy[i].state)
		{
		case Move:
			EnemyMove(i);
			EnemyMoveLiner(i);
			break;

		case Attack:
			EnemyInterPoration(i);
			break;
		}

		BaseDamage(i);
	}
#ifdef _DEBUG
	PrintDebugProc("�G�l�~�[�̗�:%d\n", g_Enemy[0].life);
	PrintDebugProc("�G�l�~�[�̗�:%d\n", g_Enemy[1].life);
	PrintDebugProc("�G�l�~�[�̗�:%d\n", g_Enemy[2].life);
	PrintDebugProc("�G�l�~�[�̗�:%d\n", g_Enemy[3].life);
	PrintDebugProc("�G�l�~�[�̗�:%d\n", g_Enemy[0].blocked);
	PrintDebugProc("�G�l�~�[�̗�:%d\n", g_Enemy[1].blocked);
	PrintDebugProc("�G�l�~�[�̗�:%d\n", g_Enemy[2].blocked);
	PrintDebugProc("�G�l�~�[�̗�:%d\n", g_Enemy[3].blocked);
#endif

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawEnemy(void)
{
	// �J�����O����
	SetCullingMode(CULL_MODE_NONE);

	XMMATRIX mtxScl, mtxRot, mtxTranslate, mtxWorld;

	for (int i = 0; i < enemyNum; i++)
	{
		if (g_Enemy[i].use != TRUE)continue;

		// ���[���h�}�g���b�N�X�̏�����
		mtxWorld = XMMatrixIdentity();

		// �X�P�[���𔽉f
		mtxScl = XMMatrixScaling(g_Enemy[i].scl.x + g_Enemyline[i].scl.x, g_Enemy[i].scl.y + g_Enemyline[i].scl.y, g_Enemy[i].scl.z + g_Enemyline[i].scl.z);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxScl);

		// ��]�𔽉f
		mtxRot = XMMatrixRotationRollPitchYaw(g_Enemy[i].rot.x + g_Enemyline[i].rot.x, g_Enemy[i].rot.y + g_Enemyline[i].rot.y, g_Enemy[i].rot.z + g_Enemyline[i].rot.z);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxRot);

		// �ړ��𔽉f
		mtxTranslate = XMMatrixTranslation(g_Enemy[i].pos.x + g_Enemyline[i].pos.x, g_Enemy[i].pos.y + 20.0f + g_Enemyline[i].pos.y, g_Enemy[i].pos.z + g_Enemyline[i].pos.z);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxTranslate);

		// ���[���h�}�g���b�N�X�̐ݒ�
		SetWorldMatrix(&mtxWorld);

		XMStoreFloat4x4(&g_Enemy[i].mtxWorld, mtxWorld);

		// ���f���`��
		switch (g_Enemy[i].charID) {
		case Grape:
			DrawModel(&g_EnemyModel[Grape].model);
			break;
		case Strept:
			DrawModel(&g_EnemyModel[Strept].model);
			break;
		case Ryoku:
			DrawModel(&g_EnemyModel[Ryoku].model);
			break;
		case Infule:
			DrawModel(&g_EnemyModel[Infule].model);
			break;
		}
		if (g_Enemy[i].partsNum == 0)continue;

		int h = 0;
		// �p�[�c�̊K�w�A�j���[�V����
		for (int k = g_Enemy[i].startNum; k < g_Enemy[i].startNum + g_Enemy[i].partsNum; k++)
		{
			// ���[���h�}�g���b�N�X�̏�����
			mtxWorld = XMMatrixIdentity();

			// �X�P�[���𔽉f
			mtxScl = XMMatrixScaling(g_Parts[k].scl.x, g_Parts[k].scl.y, g_Parts[k].scl.z);
			mtxWorld = XMMatrixMultiply(mtxWorld, mtxScl);

			// ��]�𔽉f
			mtxRot = XMMatrixRotationRollPitchYaw(g_Parts[k].rot.x, g_Parts[k].rot.y, g_Parts[k].rot.z);
			mtxWorld = XMMatrixMultiply(mtxWorld, mtxRot);

			// �ړ��𔽉f
			mtxTranslate = XMMatrixTranslation(g_Parts[k].pos.x, g_Parts[k].pos.y, g_Parts[k].pos.z);
			mtxWorld = XMMatrixMultiply(mtxWorld, mtxTranslate);

			if (g_Parts[k].parent != NULL)	// �q����������e�ƌ�������
			{
				mtxWorld = XMMatrixMultiply(mtxWorld, XMLoadFloat4x4(&g_Parts[k].parent->mtxWorld));
				// ��
				// g_Enemy[k].mtxWorld���w���Ă���
			}

			XMStoreFloat4x4(&g_Parts[k].mtxWorld, mtxWorld);

			// �g���Ă���Ȃ珈������B�����܂ŏ������Ă��闝�R�͑��̃p�[�c�����̃p�[�c���Q�Ƃ��Ă���\�������邩��B
			if (g_Parts[k].load == FALSE) continue;

			// ���[���h�}�g���b�N�X�̐ݒ�
			SetWorldMatrix(&mtxWorld);

			// ���f���`��
			switch (g_Enemy[i].charID) {
			case Grape:
				DrawModel(&g_EnemyPartsModel[Grape + h].model);
				break;
			case Strept:
				DrawModel(&g_EnemyPartsModel[3 + h].model);
				break;
			case Ryoku:
				DrawModel(&g_EnemyPartsModel[6 + h].model);
				break;
			case Infule:
				DrawModel(&g_EnemyPartsModel[8 + h].model);
				break;
			}
			h++;
		}

	}


	// �J�����O�ݒ��߂�
	SetCullingMode(CULL_MODE_BACK);
}


//=============================================================================
// �v���C���[�����擾
//=============================================================================
ENEMY *GetEnemy(void)
{
	return &g_Enemy[0];
}
//=============================================================================
// �v���C���[�����擾
//=============================================================================
EnemyParts *GetEnemyParts(void)
{
	return &g_Parts[0];
}
Unit *GetEnemyModel(void)
{
	return &g_EnemyModel[0];
}
Unit *GetPartsModel(void)
{
	return &g_EnemyPartsModel[0];
}

//�Y�����������Ɏ����Ă���
void SetEnemyTime(int i)
{
	for (int k = 0; k < enemyNum; k++)
	{
		if (g_Enemy[i].start <= 0.0f)continue;	//���ɏo���ς݂̃G�l�~�[�͂����Œe��

		g_Enemy[i].start -= 1.0f;
		if (g_Enemy[i].start <= 180.0f && g_Enemy[i].start > 0.0f && !g_Enemy[i].use)//�G�l�~�[���o��������
		{
			g_Enemy[i].use = TRUE;
			int tbl = g_Enemy[i].nowTbl;
			XMVECTOR v1 = XMLoadFloat3(&moveTbl[tbl + 1].start) - XMLoadFloat3(&moveTbl[tbl].start);
			XMVECTOR nor = XMVector3Normalize(v1);
			XMFLOAT3 angle;
			XMStoreFloat3(&angle, nor);
			float yangle = atan2f(angle.x, angle.z);
			for (int d = 0; d < g_Enemy[i].tbl_sizeM; d++)
			{
				float buffx = g_Enemy[i].tbl_adrM[d].pos.x;
				float buffz = g_Enemy[i].tbl_adrM[d].pos.z;
				g_Enemy[i].tbl_adrM[d].pos.x = buffx * cosf(yangle - g_Enemy[i].rot.y) + buffz * sinf(yangle - g_Enemy[i].rot.y);
				g_Enemy[i].tbl_adrM[d].pos.z = buffz * cosf(yangle - g_Enemy[i].rot.y) + buffx * -sinf(yangle - g_Enemy[i].rot.y);
			}
			g_Enemy[i].rot.y = yangle;
			g_Enemy[i].spd *= -1.0f;
		}
		else if (g_Enemy[i].start <= 0.0f)
		{
			g_Enemy[i].spd *= -1.0f;
		}
	}
}


void EnemyMoveLiner(int i)
{
	if (g_Enemy[i].tbl_adrA == NULL)return;	// ���`��Ԃ����s����H

//
// ���`��Ԃ̏���
// �ړ�����
	int		index = (int)g_Enemy[i].move_time;
	float	time = g_Enemy[i].move_time - index;
	int		size = g_Enemy[i].tbl_sizeM;

	float dt = 1.0f / g_Enemy[i].tbl_adrM[index].frame;	// 1�t���[���Ői�߂鎞��
	g_Enemy[i].move_time += dt;							// �A�j���[�V�����̍��v���Ԃɑ���

	if (index > (size - 2))	// �S�[�����I�[�o�[���Ă�����A�f�[�^���ŏ��ɖ߂��čU�����I��
	{
		g_Enemy[i].move_time = 0.0f;
		index = 0;
		g_Enemyline[i].pos = { 0.0f, 0.0f, 0.0f };
		g_Enemyline[i].rot = { 0.0f, 0.0f, 0.0f };
		g_Enemyline[i].scl = { 0.0f, 0.0f, 0.0f };
	}

	// ���W�����߂�	X = StartX + (EndX - StartX) * ���̎���
	XMVECTOR p1 = XMLoadFloat3(&g_Enemy[i].tbl_adrM[index + 1].pos);	// ���̏ꏊ
	XMVECTOR p0 = XMLoadFloat3(&g_Enemy[i].tbl_adrM[index + 0].pos);	// ���݂̏ꏊ
	XMVECTOR vec = p1 - p0;
	XMStoreFloat3(&g_Enemyline[i].pos, p0 + vec * time);

	// ��]�����߂�	R = StartX + (EndX - StartX) * ���̎���
	XMVECTOR r1 = XMLoadFloat3(&g_Enemy[i].tbl_adrM[index + 1].rot);	// ���̊p�x
	XMVECTOR r0 = XMLoadFloat3(&g_Enemy[i].tbl_adrM[index + 0].rot);	// ���݂̊p�x
	XMVECTOR rot = r1 - r0;
	XMStoreFloat3(&g_Enemyline[i].rot, r0 + rot * time);

	// scale�����߂� S = StartX + (EndX - StartX) * ���̎���
	XMVECTOR s1 = XMLoadFloat3(&g_Enemy[i].tbl_adrM[index + 1].scl);	// ����Scale
	XMVECTOR s0 = XMLoadFloat3(&g_Enemy[i].tbl_adrM[index + 0].scl);	// ���݂�Scale
	XMVECTOR scl = s1 - s0;
	XMStoreFloat3(&g_Enemyline[i].scl, s0 + scl * time);

	for (int k = g_Enemy[i].startNum; k < g_Enemy[i].startNum + g_Enemy[i].partsNum; k++)
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

//��ɃG�l�~�[�̍U�����̐��`��ԁB�_���[�W�����������ōs��
void EnemyInterPoration(int i)
{
	if (g_Enemy[i].tbl_adrA == NULL)return;	// ���`��Ԃ����s����H

	//
	// ���`��Ԃ̏���
	// �ړ�����
	int		index = (int)g_Enemy[i].move_time;
	float	time = g_Enemy[i].move_time - index;
	int		size = g_Enemy[i].tbl_sizeA;

	float dt = 1.0f / g_Enemy[i].tbl_adrA[index].frame;	// 1�t���[���Ői�߂鎞��
	g_Enemy[i].move_time += dt;							// �A�j���[�V�����̍��v���Ԃɑ���

	if (index > (size - 2))	// �S�[�����I�[�o�[���Ă�����A�f�[�^���ŏ��ɖ߂��čU�����I��
	{
		g_Enemy[i].move_time = 0.0f;
		index = 0;
		g_Enemy[i].atCount = 0;
		g_Enemy[i].state = Move;
		g_Enemy[i].attackUse = FALSE;
		g_Enemyline[i].pos = { 0.0f, 0.0f, 0.0f };
		g_Enemyline[i].rot = { 0.0f, 0.0f, 0.0f };
		g_Enemyline[i].scl = { 0.0f, 0.0f, 0.0f };
	}

	// ���W�����߂�	X = StartX + (EndX - StartX) * ���̎���
	XMVECTOR p1 = XMLoadFloat3(&g_Enemy[i].tbl_adrA[index + 1].pos);	// ���̏ꏊ
	XMVECTOR p0 = XMLoadFloat3(&g_Enemy[i].tbl_adrA[index + 0].pos);	// ���݂̏ꏊ
	XMVECTOR vec = p1 - p0;
	XMStoreFloat3(&g_Enemyline[i].pos, p0 + vec * time);

	// ��]�����߂�	R = StartX + (EndX - StartX) * ���̎���
	XMVECTOR r1 = XMLoadFloat3(&g_Enemy[i].tbl_adrA[index + 1].rot);	// ���̊p�x
	XMVECTOR r0 = XMLoadFloat3(&g_Enemy[i].tbl_adrA[index + 0].rot);	// ���݂̊p�x
	XMVECTOR rot = r1 - r0;
	XMStoreFloat3(&g_Enemyline[i].rot, r0 + rot * time);

	// scale�����߂� S = StartX + (EndX - StartX) * ���̎���
	XMVECTOR s1 = XMLoadFloat3(&g_Enemy[i].tbl_adrA[index + 1].scl);	// ����Scale
	XMVECTOR s0 = XMLoadFloat3(&g_Enemy[i].tbl_adrA[index + 0].scl);	// ���݂�Scale
	XMVECTOR scl = s1 - s0;
	XMStoreFloat3(&g_Enemyline[i].scl, s0 + scl * time);

	for (int k = g_Enemy[i].startNum; k < g_Enemy[i].startNum + g_Enemy[i].partsNum; k++)
	{
		if (g_Parts[k].tbl_adrA == NULL)continue;;	// ���`��Ԃ����s����H

		int		index = (int)g_Parts[k].move_time;
		float	time = g_Parts[k].move_time - index;
		int		size = g_Parts[k].tbl_sizeA;

		float dt = 1.0f / g_Parts[k].tbl_adrA[index].frame;	// 1�t���[���Ői�߂鎞��
		g_Parts[k].move_time += dt;							// �A�j���[�V�����̍��v���Ԃɑ���

		if (index > (size - 2))	// �S�[�����I�[�o�[���Ă�����A�f�[�^���ŏ��ɖ߂��čU�����I��
		{
			g_Parts[k].move_time = 0.0f;
			index = 0;
		}

		// ���W�����߂�	X = StartX + (EndX - StartX) * ���̎���
		XMVECTOR p1 = XMLoadFloat3(&g_Parts[k].tbl_adrA[index + 1].pos);	// ���̏ꏊ
		XMVECTOR p0 = XMLoadFloat3(&g_Parts[k].tbl_adrA[index + 0].pos);	// ���݂̏ꏊ
		XMVECTOR vec = p1 - p0;
		XMStoreFloat3(&g_Parts[k].pos, p0 + vec * time);

		// ��]�����߂�	R = StartX + (EndX - StartX) * ���̎���
		XMVECTOR r1 = XMLoadFloat3(&g_Parts[k].tbl_adrA[index + 1].rot);	// ���̊p�x
		XMVECTOR r0 = XMLoadFloat3(&g_Parts[k].tbl_adrA[index + 0].rot);	// ���݂̊p�x
		XMVECTOR rot = r1 - r0;
		XMStoreFloat3(&g_Parts[k].rot, r0 + rot * time);

		// scale�����߂� S = StartX + (EndX - StartX) * ���̎���
		XMVECTOR s1 = XMLoadFloat3(&g_Parts[k].tbl_adrA[index + 1].scl);	// ����Scale
		XMVECTOR s0 = XMLoadFloat3(&g_Parts[k].tbl_adrA[index + 0].scl);	// ���݂�Scale
		XMVECTOR scl = s1 - s0;
		XMStoreFloat3(&g_Parts[k].scl, s0 + scl * time);
	}


	//��������U������
	if (g_Enemy[i].target == NULL || g_Enemy[i].attackUse == TRUE)return;	//�Z�b�g���Ă��Ȃ��A�Z�b�g����K�v���Ȃ��U�������邩���H
	g_Enemy[i].atFrameCount++;
	//�U���t���[���ɒB������A�_���[�W�v�Z�֐������Ƀ^�[�Q�b�g�Ƀ_���[�W
	if (g_Enemy[i].atFrameCount >= g_Enemy[i].atFrame) {
		g_Enemy[i].target->life -= DamageFunc(g_Enemy[i].power, g_Enemy[i].target->diffend);
		g_Enemy[i].atFrameCount = 0;
		g_Enemy[i].attackUse = TRUE;
	}
}

void EnemyMove(int i)
{
	//�ߐڃL�����ł��u���b�N���Ȃ�ړ����Ȃ�
	if (g_Enemy[i].type == Proximity && g_Enemy[i].blocked)
		return;
	//���x���}�C�i�X�Ȃ�ړ����Ȃ�
	if (g_Enemy[i].spd < 0.0f)return;

	int tbl = g_Enemy[i].nowTbl;
	//�G�l�~�[�̈ړ����x�����ɍ��W�X�V
	XMVECTOR v1 = XMLoadFloat3(&g_Enemy[i].moveData[tbl + 1].start) - XMLoadFloat3(&g_Enemy[i].moveData[tbl].start);
	XMVECTOR nor = XMVector3Normalize(v1);
	XMStoreFloat3(&g_Enemy[i].pos, XMLoadFloat3(&g_Enemy[i].pos) + nor * g_Enemy[i].spd);
	XMFLOAT3 angle;
	XMStoreFloat3(&angle, nor);
	float yangle = atan2f(angle.x, angle.z);
	for (int d = 0; d < g_Enemy[i].tbl_sizeM; d++)
	{
		float buffx = g_Enemy[i].tbl_adrM[d].pos.x;
		float buffz = g_Enemy[i].tbl_adrM[d].pos.z;
		g_Enemy[i].tbl_adrM[d].pos.x = buffx * cosf(yangle - g_Enemy[i].rot.y) + buffz * sinf(yangle - g_Enemy[i].rot.y);
		g_Enemy[i].tbl_adrM[d].pos.z = buffz * cosf(yangle - g_Enemy[i].rot.y) + buffx * -sinf(yangle - g_Enemy[i].rot.y);
	}
	g_Enemy[i].rot.y = yangle;


	//�f�[�^�̈ړ��ʂƌ��݂̈ړ��ʂ�float�l�ɕϊ����Ĕ�r
	XMFLOAT3 countData;
	XMStoreFloat3(&countData, v1);
	XMFLOAT3 countMove;
	XMStoreFloat3(&countMove, nor * g_Enemy[i].spd);
	float moveMax = fabsf(countData.x) + fabsf(countData.y) + fabsf(countData.z);
	g_Enemy[i].moveCount = fabsf(countMove.x) + fabsf(countMove.y) + fabsf(countMove.z) + g_Enemy[i].moveCount;
	//�ړ��ʂ𒴂��Ă����玟�̃f�[�^�e�[�u����
	if (g_Enemy[i].moveCount >= moveMax)
	{
		g_Enemy[i].nowTbl++;
		g_Enemy[i].moveCount = 0.0f;
	}

	if (g_Enemy[i].nowTbl >= g_Enemy[i].moveTblSize - 1)
		g_Enemy[i].use = FALSE;
}


//����A���̃X�e�[�g�J�ڕ��@�͉������L�����B�ߋ����L�����͉~�߂����Ꮼ��������
int StateCheck(int i)
{
	//�U�����Ȃ�X�e�[�g�͂����ł͕ύX���Ȃ�
	if (g_Enemy[i].state == Attack)return Attack;

	int ans = Move;			//�f�t�H���g�͈ړ�
	BOOL check = FALSE;
	PLAYER *player = GetPlayer();
	for (int k = 0; k < MAX_PLAYER; k++)
	{
		//1�l�ł��������Ă��郆�j�b�g����������U�����[�h��
		if (player[k].use != TRUE)continue;
		if (CollisionBC(g_Enemy[i].pos, player[k].pos, g_Enemy[i].size, 1.0f)) { 
			check = TRUE;
			break;
		}
	}
	if (check == FALSE)return ans;

	g_Enemy[i].atCount++;
	if (g_Enemy[i].atCount >= g_Enemy[i].atInterval)
	{
		ans = Attack;
		g_Enemy[i].atCount = 0;
	}
	return ans;
}

//�G�L�����̍U���^�[�Q�b�g����B��ԋ߂��G�������čU������
void CheckTarget(int i)
{
	//�U�����ł͂Ȃ��A���̓u���b�N����Ă���Ȃ炱���Ń^�[�Q�b�g����͂��Ȃ�
	if (g_Enemy[i].state != Attack || g_Enemy[i].blocked != FALSE)return;

	PLAYER *player = GetPlayer();
	float cmp = 0.0f;;
	for (int k = 0; k < MAX_PLAYER; k++)
	{
		if (player[k].use != TRUE)continue;
		XMVECTOR v1 = XMLoadFloat3(&g_Enemy[i].pos) - XMLoadFloat3(&player[k].pos);
		XMFLOAT3 countData;
		XMStoreFloat3(&countData, v1);
		float dist = fabsf(countData.x) + fabsf(countData.y) + fabsf(countData.z);
		if (dist < cmp || cmp <= 0.0f)
		{
			cmp = dist;
			g_Enemy[i].target = &player[k];
		}
	}
	XMVECTOR v2 = XMLoadFloat3(&g_Enemy[i].target->pos) - XMLoadFloat3(&g_Enemy[i].pos);
	XMFLOAT3 countData;
	XMStoreFloat3(&countData, v2);
	float angle = atan2f(countData.x, countData.z);
	for (int d = 0; d < g_Enemy[i].tbl_sizeA; d++)
	{
		float buffx = g_Enemy[i].tbl_adrA[d].pos.x;
		float buffz = g_Enemy[i].tbl_adrA[d].pos.z;
		g_Enemy[i].tbl_adrA[d].pos.x = buffx * cosf(angle - g_Enemy[i].rot.y) + buffz * sinf(angle - g_Enemy[i].rot.y);
		g_Enemy[i].tbl_adrA[d].pos.z = buffz * cosf(angle - g_Enemy[i].rot.y) + buffx * -sinf(angle - g_Enemy[i].rot.y);
	}
	g_Enemy[i].rot.y = angle;

}

void BaseDamage(int i)
{
	Base *base = GetBase();
	for (int k = 0; k < base->baseNum; k++)
	{
		if (g_Enemy[i].use != TRUE)continue;
		if (!CollisionBC(g_Enemy[i].pos, base->pos[k], 10.0f, 10.0f))continue;

		base->life--;
		banishEnemy++;
		g_Enemy[i].use = FALSE;
	}

}

int GetEnemyNum(void)
{
	return enemyNum;
}

int GetBanishEnemy(void)
{
	return banishEnemy;
}

int GetEnemyPartsNum(void)
{
	return partsNum;
}
void SetEnemyNum(void)
{
	enemyNum++;
}

void SetEnemyPartsNum(void)
{
	partsNum++;
}
//�v���C���[�L�����̗̑̓o�[�̕\������
void DrawEnemyLife(void)
{
	// Z��r�Ȃ�
	SetDepthEnable(FALSE);
	// ���C�e�B���O�𖳌�
	SetLightEnable(FALSE);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[0]);

	XMMATRIX mtxScl, mtxRot, mtxTranslate, mtxWorld;
	//hp�o�[��ݒu
	for (int i = 0; i < MAX_ENEMY; i++)
	{
		if (g_Enemy[i].use != TRUE || g_Enemy[i].lifeMax == g_Enemy[i].life)continue;	//�g���ĂȂ����̗͂������ĂȂ��Ȃ�X���[

		for (int k = 0; k < 2; k++)//�ŏ��ɍő�l�̗͂��A���Ɍ��̗͂�\��
		{
			g_EnemyVar.pos = { g_Enemy[i].pos.x, g_Enemy[i].pos.y + 15.0f, g_Enemy[i].pos.z - 15.0f };
			if (k == 0)
			{
				g_EnemyVar.scl = { 1.0f, 1.0f, 1.0f };
				g_EnemyVar.material.Diffuse = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.7f);
			}
			else
			{
				float par = (float)(g_Enemy[i].life) / (float)(g_Enemy[i].lifeMax);
				g_EnemyVar.scl = { par, 1.0f, 1.0f };
				g_EnemyVar.pos.x -= (VAR_WIDTH * (1.0f - par)) * 0.5f;
				g_EnemyVar.material.Diffuse = XMFLOAT4(0.8f, 0.0f, 0.0f, 1.0f);
			}
			// ���[���h�}�g���b�N�X�̏�����
			mtxWorld = XMMatrixIdentity();

			// �X�P�[���𔽉f
			mtxScl = XMMatrixScaling(g_EnemyVar.scl.x, g_EnemyVar.scl.y, g_EnemyVar.scl.z);
			mtxWorld = XMMatrixMultiply(mtxWorld, mtxScl);

			// ��]�𔽉f
			mtxRot = XMMatrixRotationRollPitchYaw(g_EnemyVar.rot.x, g_EnemyVar.rot.y, g_EnemyVar.rot.z);
			mtxWorld = XMMatrixMultiply(mtxWorld, mtxRot);

			// �ړ��𔽉f
			mtxTranslate = XMMatrixTranslation(g_EnemyVar.pos.x, g_EnemyVar.pos.y, g_EnemyVar.pos.z);
			mtxWorld = XMMatrixMultiply(mtxWorld, mtxTranslate);

			// ���[���h�}�g���b�N�X�̐ݒ�
			SetWorldMatrix(&mtxWorld);

			// �}�e���A���̐ݒ�
			SetMaterial(g_EnemyVar.material);

			// �|���S���̕`��
			GetDeviceContext()->Draw(4, 0);
		}
	}
	// Z��r����
	SetDepthEnable(TRUE);
	// ���C�e�B���O��L����
	SetLightEnable(TRUE);

}

HRESULT MakeVertexEnemyVar(void)
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
