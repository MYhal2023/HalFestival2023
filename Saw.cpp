#include "playerArms.h"
static Saw g_PlayerArm;

void Saw::InitArm(void)
{
	LoadModel(MODEL_SAW, &g_PlayerArm.model);
	g_PlayerArm.use = TRUE;
	g_PlayerArm.parent = pArm::GetArmParts();
	g_PlayerArm.pos = { 0.0f, 0.0f, 0.0f };
	g_PlayerArm.rot = { 0.0f, 0.0f, 0.0f };
	g_PlayerArm.scl = { 1.0f, 1.0f, 1.0f };
}

void Saw::Action(void)
{

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