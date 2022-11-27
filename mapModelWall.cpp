#include "mapWallModel.h"
#include "game.h"
#define MAX_WALL_MODEL (4)
static MapWallModel g_MapWallModel[MAX_WALL_MODEL_NUM];
static 	DX11_MODEL			model[MAX_WALL_MODEL];		// ���f��

//������
void MapWallModel::Init(void)
{
	for (int i = 0; i < MAX_WALL_MODEL_NUM; i++)
	{
		g_MapWallModel[i].use = FALSE;
		g_MapWallModel[i].rot = { 0.0f, XM_PI * 0.0f, 0.0f };
		g_MapWallModel[i].scl = { 5.0f, 5.0f, 5.0f };
	}
}

void MapWallModel::InitBoot(void)
{
	LoadModel(MODEL_WALL001, &model[0]);
	LoadModel(MODEL_WALL002, &model[1]);
	LoadModel(MODEL_WALL003, &model[2]);
	LoadModel(MODEL_WALL004, &model[3]);
}

void MapWallModel::Uninit(void)
{
	for (int i = 0; i < MAX_WALL_MODEL; i++)
	{
		// ���f���̉������
		if (g_MapWallModel[i].use)
		{
			UnloadModel(&model[i]);
			g_MapWallModel[i].use = FALSE;
		}
	}

}

//�X�V
void MapWallModel::Update(void)
{
	for (int i = 0; i < MAX_WALL_MODEL_NUM; i++)
	{
		if (!g_MapWallModel[i].use)continue;

	}
}

void MapWallModel::SetMapWallModel(XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 scl, int num)
{
	for (int i = 0; i < MAX_WALL_MODEL_NUM; i++)
	{
		if (g_MapWallModel[i].use)continue;

		g_MapWallModel[i].use = TRUE;
		g_MapWallModel[i].pos = pos;
		g_MapWallModel[i].rot = rot;
		g_MapWallModel[i].scl = scl;
		g_MapWallModel[i].model_num = num;
		break;
	}
}

void MapWallModel::ResultMoveWall(void)
{
	for (int i = 0; i < MAX_WALL_MODEL_NUM; i++)
	{
		if (!g_MapWallModel[i].use)continue;

		g_MapWallModel[i].pos.x += 0.8f;
		if (g_MapWallModel[i].pos.x >= 0.8f * 2500.0f)
			g_MapWallModel[i].pos.x = -220.0f;

	}
}

void MapWallModel::Draw(void)
{
	// �J�����O����
	SetCullingMode(CULL_MODE_NONE);

	XMMATRIX mtxScl, mtxRot, mtxTranslate, mtxWorld;

	for (int i = 0; i < MAX_WALL_MODEL_NUM; i++)
	{
		if (g_MapWallModel[i].use != TRUE)continue;
		// ���[���h�}�g���b�N�X�̏�����
		mtxWorld = XMMatrixIdentity();

		// �X�P�[���𔽉f
		mtxScl = XMMatrixScaling(g_MapWallModel[i].scl.x, g_MapWallModel[i].scl.y, g_MapWallModel[i].scl.z);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxScl);

		// ��]�𔽉f
		mtxRot = XMMatrixRotationRollPitchYaw(g_MapWallModel[i].rot.x, g_MapWallModel[i].rot.y, g_MapWallModel[i].rot.z);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxRot);

		// �ړ��𔽉f
		mtxTranslate = XMMatrixTranslation(g_MapWallModel[i].pos.x, g_MapWallModel[i].pos.y, g_MapWallModel[i].pos.z);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxTranslate);

		// ���[���h�}�g���b�N�X�̐ݒ�
		SetWorldMatrix(&mtxWorld);

		XMStoreFloat4x4(&g_MapWallModel[i].mtxWorld, mtxWorld);

		// ���f���`��
		DrawModel(&model[g_MapWallModel[i].model_num]);

	}

	// �J�����O�ݒ��߂�
	SetCullingMode(CULL_MODE_BACK);

}
