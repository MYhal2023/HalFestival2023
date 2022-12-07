#include "obstacle.h"
#include "player.h"
#include "bullet.h"
#include "collision.h"
#include "result.h"
#include "reserve.h"
#include "camera.h"
#include "sound.h"
static FallObject g_Obstacle[MAX_FALL_OBSTACLE];
static DX11_MODEL g_Model[MAX_FALL_OBSTACLE_NUM];
static float fall_cool_time = 0.0f;
static BOOL  fall_switch = FALSE;
static float fall_interval = FALL_INTERVAL;
static float fall_time = FALL_TIME;
//������
void FallObject::Init(void)
{
	for (int i = 0; i < MAX_FALL_OBSTACLE; i++)
	{
		g_Obstacle[i].use = FALSE;
		g_Obstacle[i].load = FALSE;
		g_Obstacle[i].efSwitch = FALSE;
	}
	fall_cool_time = 0.0f;
	fall_switch = FALSE;
}
//�N�����̏�����
void FallObject::InitBoot(void)
{
	LoadModel(MODEL_CEILING, &g_Model[0]);
	LoadModel(MODEL_ROCK, &g_Model[1]);
}

//�I������
void FallObject::Uninit(void)
{
	for (int i = 0; i < MAX_FALL_OBSTACLE_NUM; i++)
	{
		// ���f���̉������
		UnloadModel(&g_Model[i]);
	}
}

//�X�V
void FallObject::Update(void)
{
	if(!fall_switch)
	fall_interval -= 1.0f;

	if (fall_interval <= 0.0f && !fall_switch)
	{
		fall_switch = TRUE;
		SetVibTime(60);
		PlaySound(SOUND_LABEL_SE_earthquake);
	}

	if (fall_switch) 
	{
		fall_cool_time -= 1.0f;
		fall_time -= 1.0f;
		if (fall_cool_time <= 0.0f) {
			Reserve* re = GetReserve();
			int difficult = re->rank / 150 + 1;
			if (difficult > 4)difficult = 4;
			for (int i = 0; i < difficult; i++) 
			{
				PLAYER *player = GetPlayer();
				XMFLOAT3 pos = player[0].pos;
				pos.x += (float)(rand() % 300) - 150.0f;
				pos.y = (float)(rand() % 200) + 500.0f;
				pos.z += (float)(rand() % 300) - 150.0f;
				XMFLOAT3 rot = { (float)(rand() % -157) + 314 / 157.0f ,(float)(rand() % -157) + 314 / 157.0f ,(float)(rand() % -157) + 314 / 157.0f };
				XMFLOAT3 scl = { 1.0f, 1.0f, 1.0f };
				int num = rand() % 2;
				SetObstacle(pos, rot, scl, 100.0f, 20.0f, num);
			}
			fall_cool_time = (float)(rand() % FALL_RAND_TIME) + FALL_COOL_TIME_BASE;
		}

		if (fall_time <= 0.0f)
		{
			Reserve* re = GetReserve();
			fall_interval = FALL_INTERVAL - (re->rank * 2);
			fall_time = FALL_TIME;
			fall_switch = FALSE;
		}
	}

	for (int i = 0; i < MAX_FALL_OBSTACLE; i++)
	{
		if (!g_Obstacle[i].use)continue;

		PLAYER *player = GetPlayer();

		//��������
		if (g_Obstacle[i].pos.y > 0.0f)
			g_Obstacle[i].pos.y -= FALL_SPEED;

		//�����蔻�菈��
		if (CollisionBC(player[0].pos, g_Obstacle[i].pos, player[0].size, g_Obstacle[i].size) &&
			!player[0].invincible)
		{
			g_Obstacle[i].durability -= 0.0f;
			player[0].life -= 5.0f;
			player[0].invincible = TRUE;
		}

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
		PlaySound(SOUND_LABEL_SE_lock);
		p->efSwitch = TRUE;
		return;
	}

	//�ϋv�x0�ȉ��ŏ���
	if (p->durability > 0)
		return;		
	
	PlaySound(SOUND_LABEL_SE_lock);
	Reward* re = GetReward();
	re->beatNum++;
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

BOOL FallObject::GetFallSwitch(void)
{
	return fall_switch;
}

void FallObject::Draw(void)
{
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
