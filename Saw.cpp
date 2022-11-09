#include "playerArms.h"
#include "collision.h"
#include "obstacle.h"
#include "particle.h"
#include "camera.h"
static Saw g_PlayerArm;
static XMFLOAT3 efPos[3];
static XMFLOAT3 efRot[3];
static BOOL efSwitch[3];
static float efTime[3];
void Saw::InitArm(void)
{
	LoadModel(MODEL_SAW, &g_PlayerArm.model);
	g_PlayerArm.use = TRUE;
	g_PlayerArm.parent = pArm::GetArmParts();
	g_PlayerArm.pos = { 0.0f, 0.0f, 0.0f };
	g_PlayerArm.rot = { 0.0f, 0.0f, 0.0f };
	g_PlayerArm.scl = { 1.0f, 1.0f, 1.0f };
	g_PlayerArm.attack = 10.0f;
	g_PlayerArm.atInterval = 10.0f;
	g_PlayerArm.atCount = 0.0f;
	g_PlayerArm.motionTime = 60.0f;
	for (int i = 0; i < 3; i++)
	{
		efSwitch[i] = FALSE;
	}

}

void Saw::Action(void)
{
	pArm* arm = GetArmParts();
	Obstacle* ob = Obstacle::GetObstacle();
	PLAYER *player = GetPlayer();
	CAMERA *camera = GetCamera();
	g_PlayerArm.atCount += 1.0f;
	if (g_PlayerArm.atCount >= g_PlayerArm.atInterval)
	{
		for (int k = 0; k < MAX_OBSTACLE; k++)
		{
			if (!ob[k].use)continue;

			XMFLOAT3 pos = player[0].pos;
			float dist = 30.0f;
			pos.x += sinf(player[0].rot.y) * dist;
			pos.z += cosf(player[0].rot.y) * dist;
			if (CollisionBC(pos, ob[k].pos, 1.0f, ob[k].size))
			{
				ob[k].durability -= g_PlayerArm.attack;
				g_PlayerArm.atCount = 0.0f;
				SetEffect(pos, camera->rot.y, 10.0f);
			}
		}
	}

	Effect();
}

void Saw::SetEffect(XMFLOAT3 pos, float rot, float time)
{
	for (int i = 0; i < 3; i++)
	{
		if (efSwitch[i])continue;

		efSwitch[i] = TRUE;
		efPos[i] = pos;
		efRot[i] = {0.0f, rot, 0.0f};
		efTime[i] = time;
	}
}

void Saw::Effect(void)
{
	for (int i = 0; i < 3; i++)
	{
		if (!efSwitch[i])continue;

		XMFLOAT3 move = { 2.0f, 2.0f, 2.0f, };			//�ړ���b�ʁB�������قǓ������������ɂȂ�
		float fAngle = (float)(rand() % 90) / 100.0f;	//���Z�������(�������傫���قǁA���E�ɂ΂�����o��)
		float fLength = (float)(rand() % 10) - 3;	//x��z�����̉��Z���x
		move.x += sinf(fAngle) * fLength;
		move.y += (float)(rand() % 5);			//�����̈ړ����Z��
		move.z += cosf(fAngle) * fLength;

		float angle = atan2f(move.y, move.x);
		XMFLOAT3 scl = { 0.025f, 0.4f, 0.025f };	//�g�嗦
		XMFLOAT3 rot = efRot[i];
		int nLife = rand() % 100 + 50;
		rot.z = angle - XM_PI * 0.5f;
		SetParticle(efPos[i], move, rot, scl, XMFLOAT4(1.0f, 0.3f, 0.3f, 1.0f), nLife, 40, P_T_box);
		efTime[i] -= 1.0f;
		if (efTime[i] <= 0.0f)
			efSwitch[i] = FALSE;
	}
}

void Saw::Draw(void)
{
	// �J�����O����
	SetCullingMode(CULL_MODE_NONE);

	XMMATRIX mtxScl, mtxRot, mtxTranslate, mtxWorld;

	if (g_PlayerArm.use != TRUE)return;
	// ���[���h�}�g���b�N�X�̏�����
	mtxWorld = XMMatrixIdentity();

	// �X�P�[���𔽉f
	mtxScl = XMMatrixScaling(g_PlayerArm.scl.x, g_PlayerArm.scl.y, g_PlayerArm.scl.z);
	mtxWorld = XMMatrixMultiply(mtxWorld, mtxScl);

	// ��]�𔽉f
	mtxRot = XMMatrixRotationRollPitchYaw(g_PlayerArm.rot.x, g_PlayerArm.rot.y, g_PlayerArm.rot.z);
	mtxWorld = XMMatrixMultiply(mtxWorld, mtxRot);

	// �ړ��𔽉f
	mtxTranslate = XMMatrixTranslation(g_PlayerArm.pos.x, g_PlayerArm.pos.y, g_PlayerArm.pos.z);
	mtxWorld = XMMatrixMultiply(mtxWorld, mtxTranslate);

	mtxWorld = XMMatrixMultiply(mtxWorld, XMLoadFloat4x4(&g_PlayerArm.parent->mtxWorld));

	XMStoreFloat4x4(&g_PlayerArm.mtxWorld, mtxWorld);

	// ���[���h�}�g���b�N�X�̐ݒ�
	SetWorldMatrix(&mtxWorld);

	// ���f���`��
	DrawModel(&g_PlayerArm.model);
}

pArm* Saw::GetArm(void)
{
	return &g_PlayerArm;
}