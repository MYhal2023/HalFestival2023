#include "playerArms.h"
#include "IPArmData.h"
#include "debugproc.h"
#include "input.h"
#include <iostream>
#include <fstream>

using namespace std;
#define MAX_ARM (2)
#define MOVE_VALUE	(0.05f)
static Normal g_PlayerArm[2];
static Normal g_ArmParts[MAX_ARM_PARTS * 2];
static Normal g_ArmWeapon[1];
static float etc = 1.0f;
static BOOL flag = TRUE;
static BOOL change = FALSE;
void Normal::InitArm(void)
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
		g_ArmParts[i].tbl_adr = nullptr;
		g_ArmParts[i].move_time = 0.0f;
	}


}

void Normal::UninitArm(void)
{
	for (int i = 0; i < MAX_ARM_PARTS * 2; i++)
	{
		// ���f���̉������
		UnloadModel(&g_ArmParts[i].model);
	}

	for (int i = 0; i < 3; i++)
	{
		UnloadModel(&g_ArmWeapon[i].model);
	}
}

void Normal::InitArmBoot(void)
{
	for (int i = 0; i < MAX_ARM_PARTS; i++)
	{
		//�Y�����ɂ���āA�r�̐�[�����������łȂ����𔻒f
		if (i == MAX_ARM_PARTS - 1)
			LoadModel(MODEL_ARM_PARTS, &g_ArmParts[i].model);
		else
			LoadModel(MODEL_ARM_PARTS, &g_ArmParts[i].model);
	}
	for (int i = MAX_ARM_PARTS; i < MAX_ARM_PARTS * 2; i++)
	{
		//�Y�����ɂ���āA�r�̐�[�����������łȂ����𔻒f
		if (i == MAX_ARM_PARTS * 2 - 1)
			LoadModel(MODEL_ARM_PARTS, &g_ArmParts[i].model);
		else
			LoadModel(MODEL_ARM_PARTS, &g_ArmParts[i].model);
	}
	LoadModel(MODEL_XGUN, &g_ArmWeapon[0].model);
}

//player.cpp��UpdateArm()�֐��ɓ����
void Normal::UpdateArm(void)
{

	for (int i = 1; i < MAX_ARM_PARTS; i++)
	{
		if (i < MAX_ARM_PARTS / 2) {	//�������̃��[�V����
			g_ArmParts[i].tbl_sizeA = tblsize[M_NormalArmL001];
			IPArm(&g_ArmParts[i], NormalArmLeft001);
		}
		else if (i >= MAX_ARM_PARTS / 2)	//�㔼���̃��[�V����
		{
			g_ArmParts[i].tbl_sizeA = tblsize[M_NormalArmL001];
			IPArm(&g_ArmParts[i], NormalArmLeft001);
		}
	}
	//�E�r
	for (int i = MAX_ARM_PARTS + 1; i < MAX_ARM_PARTS * 2; i++)
	{
		if (i < (MAX_ARM_PARTS + 1) + MAX_ARM_PARTS / 2) {
			g_ArmParts[i].tbl_sizeA = tblsize[M_NormalArmR001];
			IPArm(&g_ArmParts[i], NormalArmRight001);
		}
		else if (i >= (MAX_ARM_PARTS + 1) + MAX_ARM_PARTS / 2)
		{
			g_ArmParts[i].tbl_sizeA = tblsize[M_NormalArmR001];
			IPArm(&g_ArmParts[i], NormalArmRight001);
		}
	}
	PrintDebugProc("�A�[�����W:%f\n", g_ArmParts[MAX_ARM_PARTS - 1]);
}

INTERPOLATION_DATA * Normal::CheckMotionData(PLAYER *p)
{
	return nullptr;
}


void Normal::IPArm(Normal* p, INTERPOLATION_DATA_EASING* i)
{
//
// ���`��Ԃ̏���
// �ړ�����
	int		index = (int)p->move_time;
	float	time = p->move_time - index;
	int		size = p->tbl_sizeA;

	p->ct_frame += 1.0f;

	if (p->move_time == 0.0f && i[index].ease_mode == EASE_OUT)
		p->spead = (1.0f + 0.5f * 1.0f * 2) / i[index].frame;

	float dt = 0.0f;
	//�^�����@�ɂ���đ��x�ɉ����͂�^����
	switch (i[index].ease_mode) {
	case EASE_IN:
		dt = (1.0f * 4) / (i[index].frame*i[index].frame);
		p->spead += dt;

		break;
	case EASE_OUT:
		dt = (1.0f * 2) / (i[index].frame*i[index].frame);
		p->spead -= dt;


		break;
	case EASING:
		dt = (1.0f * 4) / (i[index].frame * i[index].frame);
		if (i[index].frame * 0.5f >= p->ct_frame)
			p->spead += dt;
		else
			p->spead -= dt;

		break;
	case NON_EASE:
		dt = 1.0f / i[index].frame;
		p->spead = dt;

		break;

		//Ease-out
	}

	p->move_time += p->spead;							// �A�j���[�V�����̍��v���Ԃɑ���

	if (i[index].frame <= p->ct_frame)p->move_time = 1.0f * (float)(index + 1);

	//�e�[�u���J�ڎ��Ɋe�ϐ����������A�����͎��̃C�[�W���O�ɂ���Č��߂�
	if (index < (int)(p->move_time))
	{
		p->move_time = 1.0f * (float)(index + 1);
		p->ct_frame = 0.0f;
		//�����̂ݏ�����^���Ȃ���΂����Ȃ�
		switch (i[index + 1].ease_mode) {
		case EASE_OUT:
			p->spead = (1.0f + 0.5f * 1.0f * 2) / i[index + 1].frame;
			break;
		case EASE_IN:
		case EASING:
		case NON_EASE:
			p->spead = 0.0f;
			break;
		}
	}

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

void Normal::Draw(void)
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
		//��[�����ɗ������̂݁A���f����`��
		if (k == MAX_ARM_PARTS - 1 || k == MAX_ARM_PARTS * 2 - 1) {
			DrawModel(&g_ArmParts[k].model);
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
void Normal::SetArmParent(PLAYER *p)
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

pArm* Normal::GetArm(void)
{
	return &g_PlayerArm[0];
}

pArm* Normal::GetArmParts(void)
{
	return &g_ArmParts[0];	//��[���̏�񂪗~�����̂ł����Ȃ��Ă���
}
