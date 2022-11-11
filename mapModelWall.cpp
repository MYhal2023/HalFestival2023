#include "mapWallModel.h"
#include "game.h"
#define MAX_WALL_MODEL (4)
static MapWallModel g_MapWallModel[MAX_WALL_MODEL];


//������
void MapWallModel::Init(void)
{
	g_MapWallModel[0].pos = { 0.0f, 0.0f, -FIELD_Z_LIMIT };
	g_MapWallModel[1].pos = { 0.0f, 0.0f, FIELD_Z_LIMIT };
	g_MapWallModel[2].pos = { FIELD_X_LIMIT, 0.0f, 0.0f };
	g_MapWallModel[3].pos = { -FIELD_X_LIMIT, 0.0f, 0.0f };
	for (int i = 0; i < MAX_WALL_MODEL; i++)
	{
		g_MapWallModel[i].use = TRUE;
		g_MapWallModel[i].rot = { 0.0f, XM_PI * 0.0f, 0.0f };
		g_MapWallModel[i].scl = { 5.0f, 5.0f, 5.0f };
	}
}

void MapWallModel::InitBoot(void)
{
	LoadModel(MODEL_WALL001, &g_MapWallModel[0].model);
	LoadModel(MODEL_WALL002, &g_MapWallModel[1].model);
	LoadModel(MODEL_WALL003, &g_MapWallModel[2].model);
	LoadModel(MODEL_WALL004, &g_MapWallModel[3].model);
}

void MapWallModel::Uninit(void)
{
	for (int i = 0; i < MAX_WALL_MODEL; i++)
	{
		// ���f���̉������
		if (g_MapWallModel[i].use)
		{
			UnloadModel(&g_MapWallModel[i].model);
			g_MapWallModel[i].use = FALSE;
		}
	}

}

//�X�V
void MapWallModel::Update(void)
{
	for (int i = 0; i < MAX_WALL_MODEL; i++)
	{
		if (!g_MapWallModel[i].use)continue;

	}
}

void MapWallModel::Draw(void)
{
	// �J�����O����
	SetCullingMode(CULL_MODE_NONE);

	XMMATRIX mtxScl, mtxRot, mtxTranslate, mtxWorld;

	for (int i = 0; i < MAX_WALL_MODEL; i++)
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
		DrawModel(&g_MapWallModel[i].model);

	}

	// �J�����O�ݒ��߂�
	SetCullingMode(CULL_MODE_BACK);

}
