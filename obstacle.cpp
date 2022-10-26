#include "obstacle.h"
#define MAX_OBSTACLE (30)
static Obstacle g_Obstacle[MAX_OBSTACLE];

void Obstacle::Draw(void)
{
	// �J�����O����
	SetCullingMode(CULL_MODE_NONE);

	XMMATRIX mtxScl, mtxRot, mtxTranslate, mtxWorld;

	for (int i = 0; i < MAX_OBSTACLE; i++)
	{
		if (g_Obstacle[i].use != TRUE)continue;
		// ���[���h�}�g���b�N�X�̏�����
		mtxWorld = XMMatrixIdentity();

		// �X�P�[���𔽉f
		mtxScl = XMMatrixScaling(g_Obstacle[i].scl.x, g_Obstacle[i].scl.y, g_Obstacle[i].scl.z);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxScl);

		// ��]�𔽉f
		mtxRot = XMMatrixRotationRollPitchYaw(g_Obstacle[i].rot.x, g_Obstacle[i].rot.y, g_Obstacle[i].rot.z);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxRot);

		// �ړ��𔽉f
		mtxTranslate = XMMatrixTranslation(g_Obstacle[i].pos.x, g_Obstacle[i].pos.y, g_Obstacle[i].pos.z);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxTranslate);

		// ���[���h�}�g���b�N�X�̐ݒ�
		SetWorldMatrix(&mtxWorld);

		XMStoreFloat4x4(&g_Obstacle[i].mtxWorld, mtxWorld);

		// ���f���`��
		DrawModel(&g_Obstacle[i].model);

	}

	// �J�����O�ݒ��߂�
	SetCullingMode(CULL_MODE_BACK);

}

//������
void Obstacle::Init(void)
{
	//LoadModel(MODEL_HEAD, &g_Parts[0].model);
	//LoadModel(MODEL_LEG, &g_Parts[1].model);
	for (int i = 0; i < MAX_OBSTACLE; i++)
	{

	}
}

void Obstacle::Uninit(void)
{
	for (int i = 0; i < MAX_OBSTACLE; i++)
	{
		// ���f���̉������
		if (g_Obstacle[i].use)
		{
			UnloadModel(&g_Obstacle[i].model);
			g_Obstacle[i].use = FALSE;
		}
	}
}

//�X�V
void Obstacle::Update(void)
{
	for (int i = 0; i < MAX_OBSTACLE; i++)
	{
		if (!g_Obstacle[i].use)continue;

		Obstacle::Distract(&g_Obstacle[i]);
	}
}

void Obstacle::Effect(Obstacle* p)
{
	//�G�t�F�N�g�X�C�b�`���I���̓z�����G�t�F�N�g������
	if (!p->efSwitch)return;

	//�ȉ��ɃG�t�F�N�g�R�[�h���L�q�B



}

void Obstacle::Distract(Obstacle* p)
{
	//�ϋv�x0�ȉ��ŏ���
	if (p->durability > 0)
		return;		
	
	p->use = FALSE;
	p->efSwitch = TRUE;
}
