#include "obstacle.h"
#include "player.h"
#include "bullet.h"
#include "collision.h"
static Obstacle g_Obstacle[MAX_OBSTACLE];


//������
void Obstacle::Init(void)
{
	//LoadModel(MODEL_HEAD, &g_Parts[0].model);
	//LoadModel(MODEL_LEG, &g_Parts[1].model);
	for (int i = 0; i < MAX_OBSTACLE; i++)
	{
		g_Obstacle[i].use = FALSE;
		g_Obstacle[i].efSwitch = FALSE;
	}
	XMFLOAT3 s = { 0.0f, 0.0f, 0.0f };
	XMFLOAT3 m = { 1.0f, 1.0f, 1.0f };
	SetObstacle(s, s, m, 100.0f, 50.0f, MODEL_OBSTACLE);
	
}
//�I������
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



		Obstacle::Distract(&g_Obstacle[i]);	//���Ă�̂����`�F�b�N
	}
}

void Obstacle::Effect(Obstacle* p)
{
	//�G�t�F�N�g�X�C�b�`���I���̓z�����G�t�F�N�g������
	if (!p->efSwitch)return;

	//�ȉ��ɃG�t�F�N�g�R�[�h���L�q�B


	if (p->efFinish)
		p->efSwitch = FALSE;
}

void Obstacle::Distract(Obstacle* p)
{
	//�ϋv�x0�ȉ��ŏ���
	if (p->durability > 0)
		return;		
	
	p->use = FALSE;
	p->efSwitch = TRUE;
}

void Obstacle::SetObstacle(XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 scl, float durability, float size, char * model)
{
	for (int i = 0; i < MAX_OBSTACLE; i++) {
		if (g_Obstacle[i].use)continue;

		LoadModel(model, &g_Obstacle[i].model);
		g_Obstacle[i].use = TRUE;
		g_Obstacle[i].pos = pos;
		g_Obstacle[i].rot = rot;
		g_Obstacle[i].scl = scl;
		g_Obstacle[i].size = size;
		g_Obstacle[i].durability = durability;

	}
}

Obstacle * Obstacle::GetObstacle(void)
{
	return &g_Obstacle[0];
}

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
