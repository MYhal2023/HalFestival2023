#include "rescueLife.h"

static RescueLife g_RscLife[MAX_RESCUE];
static int remain;					//�c��~���Ґ�

void RescueLife::InitRescue(void)
{
	for (int i = 0; i < MAX_RESCUE; i++)
	{
		g_RscLife[i].use = FALSE;
		g_RscLife[i].load = FALSE;
		g_RscLife[i].rescue = FALSE;
	}
	remain = 0;
}

void RescueLife::UninitRescue(void)
{
	for (int i = 0; i < MAX_RESCUE; i++)
	{
		if (g_RscLife[i].load)
		{
			UnloadModel(&g_RscLife[i].model);
			g_RscLife[i].load = FALSE;
		}
	}
}

void RescueLife::DrawRescue(void)
{
	// �J�����O����
	SetCullingMode(CULL_MODE_NONE);

	XMMATRIX mtxScl, mtxRot, mtxTranslate, mtxWorld;

	for (int i = 0; i < MAX_RESCUE; i++)
	{
		if (g_RscLife[i].use != TRUE)continue;
		// ���[���h�}�g���b�N�X�̏�����
		mtxWorld = XMMatrixIdentity();

		// �X�P�[���𔽉f
		mtxScl = XMMatrixScaling(g_RscLife[i].scl.x, g_RscLife[i].scl.y, g_RscLife[i].scl.z);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxScl);

		// ��]�𔽉f
		mtxRot = XMMatrixRotationRollPitchYaw(g_RscLife[i].rot.x, g_RscLife[i].rot.y, g_RscLife[i].rot.z);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxRot);

		// �ړ��𔽉f
		mtxTranslate = XMMatrixTranslation(g_RscLife[i].pos.x, g_RscLife[i].pos.y, g_RscLife[i].pos.z);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxTranslate);

		// ���[���h�}�g���b�N�X�̐ݒ�
		SetWorldMatrix(&mtxWorld);

		XMStoreFloat4x4(&g_RscLife[i].mtxWorld, mtxWorld);

		// ���f���`��
		DrawModel(&g_RscLife[i].model);

	}

	// �J�����O�ݒ��߂�
	SetCullingMode(CULL_MODE_BACK);
}

int GetRemain(void)
{
	return remain;
}

BOOL RescueLife::GetRescue(int i)
{
	return g_RscLife[i].rescue;
}

//�~���҃Z�b�g�B�擪�z�񂩂�g�p���Ă���
void RescueLife::SetRemain(XMFLOAT3 pos, XMFLOAT3 rot, char* model)
{
	for (int i = 0; i < MAX_RESCUE; i++)
	{
		if (g_RscLife[i].load)continue;	//���[�h�ς݂Ȃ�X���[

		LoadModel(model, &g_RscLife[i].model);
		g_RscLife[i].use = TRUE;
		g_RscLife[i].rescue = TRUE;
		g_RscLife[i].load = TRUE;
		g_RscLife[i].pos = pos;
		g_RscLife[i].rot = rot;
		remain++;
		break;
	}
}

RescueLife * RescueLife::GetRescueLife(void)
{
	return &g_RscLife[0];
}
