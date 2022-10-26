#include "playerArms.h"
#define MAX_ARM (2)
#define MAX_ARM_PARTS (10)
static pArm g_PlayerArm[3];
static pArm g_ArmParts[MAX_ARM_PARTS];

void pArm::Draw(void)
{
	// �J�����O����
	SetCullingMode(CULL_MODE_NONE);

	XMMATRIX mtxScl, mtxRot, mtxTranslate, mtxWorld;

	for (int i = 0; i < MAX_ARM; i++)
	{
		if (g_PlayerArm[i].use != TRUE)continue;
		// ���[���h�}�g���b�N�X�̏�����
		mtxWorld = XMMatrixIdentity();

		// �X�P�[���𔽉f
		mtxScl = XMMatrixScaling(g_PlayerArm[i].scl.x, g_PlayerArm[i].scl.y, g_PlayerArm[i].scl.z);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxScl);

		// ��]�𔽉f
		mtxRot = XMMatrixRotationRollPitchYaw(g_PlayerArm[i].rot.x, g_PlayerArm[i].rot.y, g_PlayerArm[i].rot.z);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxRot);

		// �ړ��𔽉f
		mtxTranslate = XMMatrixTranslation(g_PlayerArm[i].pos.x, g_PlayerArm[i].pos.y, g_PlayerArm[i].pos.z);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxTranslate);

		// ���[���h�}�g���b�N�X�̐ݒ�
		SetWorldMatrix(&mtxWorld);

		XMStoreFloat4x4(&g_PlayerArm[i].mtxWorld, mtxWorld);

		// ���f���`��
		DrawModel(&g_PlayerArm[i].model);

		if (g_PlayerArm[i].partsNum == 0)continue;

		// �p�[�c�̊K�w�A�j���[�V����
		for (int k = 0; k < g_PlayerArm[i].partsNum; k++)
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

			if (g_ArmParts[k].parent != NULL)	// �q����������e�ƌ�������
			{
				mtxWorld = XMMatrixMultiply(mtxWorld, XMLoadFloat4x4(&g_ArmParts[k].parent->mtxWorld));
				// ��
				// g_PlayerArm[i].mtxWorld���w���Ă���
			}

			XMStoreFloat4x4(&g_ArmParts[k].mtxWorld, mtxWorld);

			// �g���Ă���Ȃ珈������B�����܂ŏ������Ă��闝�R�͑��̃p�[�c�����̃p�[�c���Q�Ƃ��Ă���\�������邩��B
			if (g_ArmParts[k].use == FALSE) continue;

			// ���[���h�}�g���b�N�X�̐ݒ�
			SetWorldMatrix(&mtxWorld);

			// ���f���`��
			DrawModel(&g_ArmParts[k].model);
		}
	}

	// �J�����O�ݒ��߂�
	SetCullingMode(CULL_MODE_BACK);

}

//�g���A�[���̐e�q�����ꊇ�ŃZ�b�g
void pArm::SetArmParent(PLAYER *p)
{
	for (int i = 0; i < MAX_ARM; i++)
	{
		for (int k = 0; k < g_PlayerArm[i].partsNum; k++)
		{
			if (i == 0) {
				g_PlayerArm[i].parent = nullptr;
				g_PlayerArm[i].player = p;
				continue;
			}	//�擪���v���C���[�̐e�Ƃ��A����ɏ��ԂɕR�Â��Ă���
			g_PlayerArm[i].parent = &g_PlayerArm[i - 1];
		}
	}
}

void pArm::ChangeArm(void)
{
}

