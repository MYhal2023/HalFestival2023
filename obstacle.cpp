#include "obstacle.h"
#include "player.h"
#include "bullet.h"
#include "collision.h"
#include "debugproc.h"
#include "result.h"
static Obstacle g_Obstacle[MAX_OBSTACLE];
static 	DX11_MODEL		model[MAX_OBSTACLE_MODEL];		// ���f�����
static XMFLOAT4			tankglass_diffuse[16];

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

}
void Obstacle::InitBoot(void)
{
	LoadModel(MODEL_BOOK, &model[om_book]);
	LoadModel(MODEL_BOOKSHELF, &model[om_bookshelf]);
	LoadModel(MODEL_LDESK, &model[om_Ldesk]);
	LoadModel(MODEL_TANK, &model[om_tank]);
	LoadModel(MODEL_TANKGLASS, &model[om_tankglass]);
	//�^���N�K���X���������x���グ��
	GetModelDiffuse(&model[om_tankglass], &tankglass_diffuse[0]);
	for (int j = 0; j < model[om_tankglass].SubsetNum; j++)
		SetModelDiffuse(&model[om_tankglass], j, XMFLOAT4(1.0f, 1.0f, 1.0f, 0.2f));

	LoadModel(MODEL_TROLLEY, &model[om_trolley]);
	LoadModel(MODEL_BOX, &model[om_box]);
	LoadModel(MODEL_DCUT, &model[om_duct]);
	LoadModel(MODEL_GASTANK, &model[om_monitor]);
	LoadModel(MODEL_MONITOR, &model[om_steel]);
	LoadModel(MODEL_STEEL, &model[om_test]);
}
//�I������
void Obstacle::Uninit(void)
{
	for (int i = 0; i < MAX_OBSTACLE_MODEL; i++)
	{
		// ���f���̉������
		UnloadModel(&model[i]);
	}
}

//�X�V
void Obstacle::Update(void)
{
	for (int i = 0; i < MAX_OBSTACLE; i++)
	{
		if (!g_Obstacle[i].use)continue;

#ifdef _DEBUG
		PrintDebugProc("\n�ϋv�x:%f", g_Obstacle[i].durability);
#endif
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

	Reward* re = GetReward();
	re->beatNum++;
	p->use = FALSE;
	p->efSwitch = TRUE;
}

void Obstacle::SetObstacle(XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 scl, float durability, float size, int model)
{
	for (int i = 0; i < MAX_OBSTACLE; i++) {
		if (g_Obstacle[i].use)continue;

		g_Obstacle[i].model_num = model;
		g_Obstacle[i].use = TRUE;
		g_Obstacle[i].pos = pos;
		g_Obstacle[i].rot = rot;
		g_Obstacle[i].scl = scl;
		g_Obstacle[i].size = size;
		g_Obstacle[i].durability = durability;
		break;
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
		DrawModel(&model[g_Obstacle[i].model_num]);

	}

	// �J�����O�ݒ��߂�
	SetCullingMode(CULL_MODE_BACK);

}
