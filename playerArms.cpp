#include "playerArms.h"
#include "IPArmData.h"
#include "debugproc.h"
#define MAX_ARM (2)
static pArm g_PlayerArm[2];
static pArm g_ArmParts[MAX_ARM_PARTS * 2];
static pArm g_ArmWeapon[ARM_VAR + 1];
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
			LoadModel(MODEL_ARM_PARTS, &g_ArmParts[i].model);
		else
			LoadModel(MODEL_ARM_PARTS, &g_ArmParts[i].model);

		//0�̓v���C���[���f����e�Ƃ��Ă��邽�߁A�ʓr�ݒ�
		if (i == 0) {
			g_ArmParts[i].pos = { -5.0f, 0.0f, -5.0f };
			g_ArmParts[i].rot = { XM_PI * 0.0f , 0.0f, XM_PI * 0.5f };
			g_ArmParts[i].scl = { 1.0f, 1.0f, 1.0f };
		}
		else {
			g_ArmParts[i].pos = { 0.0f, 0.0f, 0.0f };
			g_ArmParts[i].rot = { 0.0f, 0.0f,0.0f };
			g_ArmParts[i].scl = { 1.0f, 1.0f, 1.0f };
		}
	}

	for (int i = MAX_ARM_PARTS; i < MAX_ARM_PARTS * 2; i++)
	{
		g_ArmParts[i].use = TRUE;
		//�Y�����ɂ���āA�r�̐�[�����������łȂ����𔻒f
		if (i == MAX_ARM_PARTS * 2 - 1)
			LoadModel(MODEL_ARM_PARTS, &g_ArmParts[i].model);
		else
			LoadModel(MODEL_ARM_PARTS, &g_ArmParts[i].model);

		if (i == MAX_ARM_PARTS) {
			g_ArmParts[i].pos = { -5.0f, 0.0f, 5.0f };
			g_ArmParts[i].rot = { XM_PI * 0.0f, 0.0f, XM_PI * 0.5f };
			g_ArmParts[i].scl = { 1.0f, 1.0f, 1.0f };
		}
		else {
			g_ArmParts[i].pos = { 0.0f, 0.0f, 0.0f };
			g_ArmParts[i].rot = { 0.0f, 0.0f, 0.0f };
			g_ArmParts[i].scl = { 1.0f, 1.0f, 1.0f };
		}

		g_ArmParts[i].tbl_adrXgun = NULL;
		g_ArmParts[i].tbl_adr = wait_armLeft;
		g_ArmParts[i].move_time = 0.0f;
	}

	LoadModel(MODEL_XGUN, &g_ArmWeapon[0].model);
	LoadModel(MODEL_BRASTER, &g_ArmWeapon[1].model);
	LoadModel(MODEL_SAW, &g_ArmWeapon[2].model);
	LoadModel(MODEL_ARM_SAW_BLADE, &g_ArmWeapon[3].model);

	Xgun::InitArm();
	Braster::InitArm();
	Saw::InitArm();
}

//player.cpp��UpdateArm()�֐��ɓ����
void pArm::UpdateArm(void)
{
	//�Иr������(���{�����͏��O)
	//���r
	for (int i = 1; i < MAX_ARM_PARTS; i++)
	{
		if (i < MAX_ARM_PARTS / 2) {	//�������̃��[�V����
			g_ArmParts[i].tbl_sizeA = tblsize[M_AttackArmSawL001];
			IPArm(&g_ArmParts[i], AttackArmSawLeft001);
		}
		else if (i >= MAX_ARM_PARTS / 2)	//�㔼���̃��[�V����
		{
			g_ArmParts[i].tbl_sizeA = tblsize[M_AttackArmSawL002];
			IPArm(&g_ArmParts[i], AttackArmSawLeft002);
		}
	}

	//�E�r
	for (int i = MAX_ARM_PARTS + 1; i < MAX_ARM_PARTS * 2; i++)
	{
		if (i < MAX_ARM_PARTS / 2) {
			g_ArmParts[i].tbl_sizeA = tblsize[M_AttackArmSawL001];
			IPArm(&g_ArmParts[i], AttackArmSawLeft001);
		}
		else if (i >= MAX_ARM_PARTS / 2)
		{
			g_ArmParts[i].tbl_sizeA = tblsize[M_AttackArmSawL002];
			IPArm(&g_ArmParts[i], AttackArmSawLeft002);
		}
	}
	PrintDebugProc("�A�[�����W:%f\n", g_ArmParts[MAX_ARM_PARTS - 1]);
}

INTERPOLATION_DATA * pArm::CheckMotionData(PLAYER *p)
{
	return nullptr;
}


void pArm::IPArm(pArm* p, INTERPOLATION_DATA* i)
{
//
// ���`��Ԃ̏���
// �ړ�����
	int		index = (int)p->move_time;
	float	time = p->move_time - index;
	int		size = p->tbl_sizeA;

	float dt = 1.0f / i->frame;	// 1�t���[���Ői�߂鎞��
	p->move_time += dt;							// �A�j���[�V�����̍��v���Ԃɑ���

	if (index > (size - 2))	// �S�[�����I�[�o�[���Ă�����A�f�[�^���ŏ��ɖ߂��čU�����I��
	{
		p->move_time = 0.0f;
		index = 0;
	}
	// ���W�����߂�	X = StartX + (EndX - StartX) * ���̎���
	XMVECTOR p1 = XMLoadFloat3(&i[index + 1].pos);	// ���̏ꏊ
	XMVECTOR p0 = XMLoadFloat3(&i[index + 0].pos);	// ���݂̏ꏊ
	XMVECTOR vec = p1 - p0;
	XMStoreFloat3(&p->pos, p0 + vec * time);

	// ��]�����߂�	R = StartX + (EndX - StartX) * ���̎���
	XMVECTOR r1 = XMLoadFloat3(&i[index + 1].rot);	// ���̊p�x
	XMVECTOR r0 = XMLoadFloat3(&i[index + 0].rot);	// ���݂̊p�x
	XMVECTOR rot = r1 - r0;
	XMStoreFloat3(&p->rot, r0 + rot * time);

	// scale�����߂� S = StartX + (EndX - StartX) * ���̎���
	XMVECTOR s1 = XMLoadFloat3(&i[index + 1].scl);	// ����Scale
	XMVECTOR s0 = XMLoadFloat3(&i[index + 0].scl);	// ���݂�Scale
	XMVECTOR scl = s1 - s0;
	XMStoreFloat3(&p->scl, s0 + scl * time);

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
				DrawModel(&g_ArmWeapon[3].model);
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
