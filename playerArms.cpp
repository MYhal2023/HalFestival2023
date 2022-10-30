#include "playerArms.h"
#define MAX_ARM (2)
static pArm g_PlayerArm[2];
static pArm g_ArmParts[MAX_ARM_PARTS * 2];
static pArm g_ArmWeapon[ARM_VAR];
void pArm::InitArm(void)
{
	for (int i = 0; i < MAX_ARM; i++)
	{
		g_PlayerArm[i].use = TRUE;
		g_PlayerArm[i].pos = { 0.0f, 0.0f, 0.0f };
		g_PlayerArm[i].rot = { 0.0f, 0.0f, 0.0f };
		g_PlayerArm[i].scl = { 1.0f, 1.0f, 1.0f };
		g_PlayerArm[i].partsNum = MAX_ARM_PARTS;
	}

	for (int i = 0; i < MAX_ARM_PARTS ; i++)
	{
		g_ArmParts[i].use = TRUE;
		//�Y�����ɂ���āA�r�̐�[�����������łȂ����𔻒f
		if (i == MAX_ARM_PARTS - 1) 
			LoadModel(MODEL_NEUTROPHILS, &g_ArmParts[i].model);
		else
			LoadModel(MODEL_NEUTROPHILS, &g_ArmParts[i].model);

		if (i == 0) {
			g_ArmParts[i].pos = { 0.0f, 0.0f, -10.0f };
			g_ArmParts[i].rot = { 0.0f, 0.0f, 0.0f };
			g_ArmParts[i].scl = { 0.75f, 0.75f, 0.75f };
		}
		else {
			g_ArmParts[i].pos = { 0.0f, 2.0f, 0.0f };
			g_ArmParts[i].rot = { 0.0f, 0.0f, 0.0f };
			g_ArmParts[i].scl = { 1.0f, 1.0f, 1.0f };
		}
	}
	for (int i = MAX_ARM_PARTS; i < MAX_ARM_PARTS * 2; i++)
	{
		g_ArmParts[i].use = TRUE;
		//�Y�����ɂ���āA�r�̐�[�����������łȂ����𔻒f
		if (i == MAX_ARM_PARTS * 2 - 1)
			LoadModel(MODEL_NEUTROPHILS, &g_ArmParts[i].model);
		else
			LoadModel(MODEL_NEUTROPHILS, &g_ArmParts[i].model);

		if (i == MAX_ARM_PARTS) {
			g_ArmParts[i].pos = { 0.0f, 0.0f, 10.0f };
			g_ArmParts[i].rot = { 0.0f, 0.0f, 0.0f };
			g_ArmParts[i].scl = { 0.75f, 0.75f, 0.75f };
		}
		else {
			g_ArmParts[i].pos = { 0.0f, 2.0f, 0.0f };
			g_ArmParts[i].rot = { 0.0f, 0.0f, 0.0f };
			g_ArmParts[i].scl = { 1.0f, 1.0f, 1.0f };
		}
	}

	LoadModel(MODEL_XGUN, &g_ArmWeapon[0].model);
	LoadModel(MODEL_BRASTER, &g_ArmWeapon[1].model);
	LoadModel(MODEL_SAW, &g_ArmWeapon[2].model);

	Xgun::InitArm();
	Braster::InitArm();
	Saw::InitArm();
}

void pArm::Draw(void)
{
	// �J�����O����
	SetCullingMode(CULL_MODE_NONE);

	XMMATRIX mtxScl, mtxRot, mtxTranslate, mtxWorld;

	// �p�[�c�̊K�w�A�j���[�V����
	for (int k = 0; k < MAX_ARM_PARTS * 2; k++)
	{
		// ���[���h�}�g���b�N�X�̏�����
		mtxWorld = XMMatrixIdentity();

		// �X�P�[���𔽉f
		mtxScl = XMMatrixScaling(g_ArmParts[k].scl.x, g_ArmParts[k].scl.y, g_ArmParts[k].scl.z);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxScl);

		// ��]�𔽉f
		mtxRot = XMMatrixRotationRollPitchYaw(g_ArmParts[k].rot.x, g_ArmParts[k].rot.y, g_ArmParts[k].rot.z);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxRot);

		// �ړ��𔽉f
		mtxTranslate = XMMatrixTranslation(g_ArmParts[k].pos.x, g_ArmParts[k].pos.y, g_ArmParts[k].pos.z);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxTranslate);

		//�e��񂪂���Ȃ�ڑ�
		if (g_ArmParts[k].player != nullptr && g_ArmParts[k].parent == nullptr)
		{
			mtxWorld = XMMatrixMultiply(mtxWorld, XMLoadFloat4x4(&g_ArmParts[k].player->mtxWorld));
		}
		else if (g_ArmParts[k].parent != nullptr)	// �q����������e�ƌ�������
		{
			mtxWorld = XMMatrixMultiply(mtxWorld, XMLoadFloat4x4(&g_ArmParts[k].parent->mtxWorld));
		}

		XMStoreFloat4x4(&g_ArmParts[k].mtxWorld, mtxWorld);

		// �g���Ă���Ȃ珈������B�����܂ŏ������Ă��闝�R�͑��̃p�[�c�����̃p�[�c���Q�Ƃ��Ă���\�������邩��B
		if (g_ArmParts[k].use == FALSE) continue;

		// ���[���h�}�g���b�N�X�̐ݒ�
		SetWorldMatrix(&mtxWorld);

		//���f���`��
		//��[�����ɗ������̂݁A����ʂɃ��f����`��
		if (k == MAX_ARM_PARTS - 1 || k == MAX_ARM_PARTS * 2 - 1) {
			PLAYER *player = GetPlayer();
			switch (player[0].armType)
			{
			case 0:
				DrawModel(&g_ArmWeapon[0].model);
				break;
			case 1:
				DrawModel(&g_ArmWeapon[1].model);
				break;
			case 2:
				DrawModel(&g_ArmWeapon[2].model);
				break;
			}
		}
		else
		{
			DrawModel(&g_ArmParts[k].model);
		}
	}

	// �J�����O�ݒ��߂�
	SetCullingMode(CULL_MODE_BACK);

}

//�g���A�[���̐e�q�����ꊇ�ŃZ�b�g
void pArm::SetArmParent(PLAYER *p)
{
	//���r
	for (int k = 0; k < MAX_ARM_PARTS; k++)
	{
		if (k == 0) {
			g_ArmParts[k].parent = nullptr;
			g_ArmParts[k].player = p;
		}
		else {	//�擪���v���C���[�̐e�Ƃ��A����ɏ��ԂɕR�Â��Ă���
			g_ArmParts[k].player = nullptr;
			g_ArmParts[k].parent = &g_ArmParts[k - 1];
		}
	}
	//�E�r
	for (int k = MAX_ARM_PARTS; k < MAX_ARM_PARTS * 2; k++)
	{
		if (k == MAX_ARM_PARTS) {
			g_ArmParts[k].parent = nullptr;
			g_ArmParts[k].player = p;
		}	//�擪���v���C���[�̐e�Ƃ��A����ɏ��ԂɕR�Â��Ă���
		else {
			g_ArmParts[k].player = nullptr;
			g_ArmParts[k].parent = &g_ArmParts[k - 1];
		}
	}
}

pArm* pArm::GetArm(void)
{
	return &g_PlayerArm[0];
}

pArm* pArm::GetArmParts(void)
{
	return &g_ArmParts[0];	//��[���̏�񂪗~�����̂ł����Ȃ��Ă���
}
