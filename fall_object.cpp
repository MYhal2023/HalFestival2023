#include "obstacle.h"
#include "player.h"
#include "bullet.h"
#include "collision.h"
static FallObject g_Obstacle[MAX_FALL_OBSTACLE];
static DX11_MODEL g_Model[MAX_FALL_OBSTACLE_NUM];
static float fall_cool_time = 0.0f;

//������
void FallObject::Init(void)
{
	//LoadModel(MODEL_HEAD, &g_Parts[0].model);
	//LoadModel(MODEL_LEG, &g_Parts[1].model);
	for (int i = 0; i < MAX_FALL_OBSTACLE; i++)
	{
		g_Obstacle[i].use = FALSE;
		g_Obstacle[i].load = FALSE;
		g_Obstacle[i].efSwitch = FALSE;
	}
	LoadModel(MODEL_CEILING, &g_Model[0]);
	LoadModel(MODEL_ROCK, &g_Model[1]);
	fall_cool_time = 0.0f;
}
//�I������
void FallObject::Uninit(void)
{
	for (int i = 0; i < MAX_FALL_OBSTACLE; i++)
	{
		// ���f���̉������
		UnloadModel(&g_Model[i]);
	}
}

//�X�V
void FallObject::Update(void)
{
	fall_cool_time -= 1.0f;
	if (fall_cool_time <= 0.0f) {
		PLAYER *player = GetPlayer();
		XMFLOAT3 pos = player[0].pos;
		pos.x += (float)(rand() % 200) - 100.0f;
		pos.y = 300.0f;
		pos.z += (float)(rand() % 200) - 100.0f;
		XMFLOAT3 rot = { (float)(rand() % -157) + 314 / 157.0f ,(float)(rand() % -157) + 314 / 157.0f ,(float)(rand() % -157) + 314 / 157.0f };
		XMFLOAT3 scl = { 1.0f, 1.0f, 1.0f };
		int num = rand() % 2;
		SetObstacle(pos, rot, scl, 100.0f, 50.0f, num);
		fall_cool_time = (float)(rand() % FALL_RAND_TIME) + FALL_COOL_TIME_BASE;
	}

	for (int i = 0; i < MAX_FALL_OBSTACLE; i++)
	{
		if (!g_Obstacle[i].use)continue;

		//��������
		if (g_Obstacle[i].pos.y > 0.0f)
			g_Obstacle[i].pos.y -= FALL_SPEED;

		FallObject::Distract(&g_Obstacle[i]);	//���Ă�̂����`�F�b�N�A�����ŉ�
	}
}

void FallObject::Effect(FallObject* p)
{
	//�G�t�F�N�g�X�C�b�`���I���̓z�����G�t�F�N�g������
	if (!p->efSwitch)return;

	//�ȉ��ɃG�t�F�N�g�R�[�h���L�q�B


	if (p->efFinish)
		p->efSwitch = FALSE;
}

void FallObject::Distract(FallObject* p)
{
	if (p->pos.y <= 0.0f)
	{
		p->use = FALSE;
		return;
	}

	//�ϋv�x0�ȉ��ŏ���
	if (p->durability > 0)
		return;		
	

	p->use = FALSE;
	p->efSwitch = TRUE;
}

void FallObject::SetObstacle(XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 scl, float durability, float size, int model)
{
	for (int i = 0; i < MAX_FALL_OBSTACLE; i++) {
		if (g_Obstacle[i].use)continue;

		g_Obstacle[i].use = TRUE;
		g_Obstacle[i].load = TRUE;
		g_Obstacle[i].pos = pos;
		g_Obstacle[i].rot = rot;
		g_Obstacle[i].scl = scl;
		g_Obstacle[i].size = size;
		g_Obstacle[i].durability = durability;
		g_Obstacle[i].model_num = model;
		break;
	}
}

FallObject * FallObject::GetObstacle(void)
{
	return &g_Obstacle[0];
}

void FallObject::Draw(void)
{
	return;
	// �J�����O����
	SetCullingMode(CULL_MODE_NONE);

	XMMATRIX mtxScl, mtxRot, mtxTranslate, mtxWorld;

	for (int i = 0; i < MAX_FALL_OBSTACLE; i++)
	{
		if (g_Obstacle[i].use != TRUE || g_Obstacle[i].efFinish == TRUE)continue;
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
		DrawModel(&g_Model[g_Obstacle[i].model_num]);

	}

	// �J�����O�ݒ��߂�
	SetCullingMode(CULL_MODE_BACK);

}
