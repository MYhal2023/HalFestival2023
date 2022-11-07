#include "playerArms.h"
#include "bullet.h"
static Braster g_PlayerArm;

void Braster::InitArm(void)
{
	g_PlayerArm.attackUse = FALSE;
	g_PlayerArm.atInterval = 15.0f;
	g_PlayerArm.atCount = 0.0f;
}

void Braster::Action(void)
{
	if (!g_PlayerArm.attackUse)
	{
		PLAYER *player = GetPlayer();
		XMFLOAT3 pos = player[0].pos;
		XMFLOAT3 pos2 = player[0].pos;
		const float dist = 5.0f;
		float high = 0.0f;
		pos.x += sinf(player[0].rot.y + XM_PI * 0.20f) * dist;
		pos.y += high;
		pos.z += cosf(player[0].rot.y + XM_PI * 0.20f) * dist;

		pos2.x += sinf(player[0].rot.y - XM_PI * 0.20f) * dist;
		pos2.y += high;
		pos2.z += cosf(player[0].rot.y - XM_PI * 0.20f) * dist;
		SetBullet(pos, player[0].rot, 8.0f, 50.0f, 40, Bullet_Braster);
		SetBullet(pos2, player[0].rot, 8.0f, 50.0f, 40, Bullet_Braster);

		g_PlayerArm.atCount = g_PlayerArm.atInterval;

		g_PlayerArm.attackUse = TRUE;
	}

	if (g_PlayerArm.atCount > 0.0f)
		g_PlayerArm.atCount -= 1.0f;

	if (g_PlayerArm.atCount <= 0.0f)
		g_PlayerArm.attackUse = FALSE;

}

void Braster::Draw(void)
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

pArm* Braster::GetArm(void)
{
	return &g_PlayerArm;
}