#include "playerArms.h"
#include "bullet.h"
#include "camera.h"
#include "particle.h"
#include "sound.h"
#include "game.h"

#define INTERVAL (10.0f)
#define EFFECT_FRME (5)
#define POS_ROT_VAL (90)
static Xgun g_PlayerArm;

void Xgun::InitArm(void)
{
	g_PlayerArm.attack = FALSE;
	g_PlayerArm.atCount = INTERVAL;
	g_PlayerArm.ef_frame = EFFECT_FRME;
}

void Xgun::Action(void)
{
	if (!g_PlayerArm.attack && g_PlayerArm.atCount > 0.0f)
	g_PlayerArm.atCount -= 1.0f;

	if (!g_PlayerArm.attack && g_PlayerArm.atCount <= 0.0f)
	{
		PLAYER *player = GetPlayer();
		CAMERA *cam = GetCamera();
		XMFLOAT3 pos = player[0].pos;
		XMFLOAT3 pos2 = player[0].pos;
		XMFLOAT3 rot = player[0].rot;
		const float dist = 10.0f;
		float high = 0.0f;
		float rot_y = XMConvertToDegrees(player[0].rot.y);
		pos.x += sinf(XMConvertToRadians(rot_y + POS_ROT_VAL)) * dist;
		pos.y += high;
		pos.z += cosf(XMConvertToRadians(rot_y + POS_ROT_VAL)) * dist;

		pos2.x += sinf(XMConvertToRadians(rot_y - POS_ROT_VAL)) * dist;
		pos2.y += high;
		pos2.z += cosf(XMConvertToRadians(rot_y - POS_ROT_VAL)) * dist;

		if(!GetUpdateCam())
		player[0].rot.y = cam->rot.y;
		rot.y = player[0].rot.y;
		rot.x = player[0].rot.x;
		SetBullet(pos, rot, 10.0f, 30.0f, 70, Bullet_XGun);
		SetBullet(pos2, rot, 10.0f, 30.0f, 70, Bullet_XGun);
		PlaySound(SOUND_LABEL_SE_xgun_hit);
		g_PlayerArm.attack = TRUE;
		g_PlayerArm.atCount = INTERVAL;
		g_PlayerArm.ef_frame = EFFECT_FRME;
	}

	//�G�t�F�N�g�R�[�h
	if (g_PlayerArm.attack && g_PlayerArm.ef_frame > 0)
	{
		PLAYER *player = GetPlayer();
		CAMERA *cam = GetCamera();
		XMFLOAT3 pos = player[0].pos;
		XMFLOAT3 pos2 = player[0].pos;
		XMFLOAT3 rot = player[0].rot;
		const float dist = 8.0f;
		float high = 22.0f;
		float rot_y = XMConvertToDegrees(player[0].rot.y);
		pos.x += sinf(XMConvertToRadians(rot_y + POS_ROT_VAL)) * dist;
		pos.y += high;
		pos.z += cosf(XMConvertToRadians(rot_y + POS_ROT_VAL)) * dist;

		pos2.x += sinf(XMConvertToRadians(rot_y - POS_ROT_VAL)) * dist;
		pos2.y += high;
		pos2.z += cosf(XMConvertToRadians(rot_y - POS_ROT_VAL)) * dist;
		g_PlayerArm.ef_frame--;
		for (int i = 0; i < 1; i++) {
			CAMERA *cam = GetCamera();
			XMFLOAT3 move = { 0.0f, 0.0f, 0.0f, };
			float fAngle = (float)(rand() % 163) + 30;	//���Z�������(�������ʂ̐������傫���قǁA���E�ɂ΂�����o��)
			fAngle = XMConvertToRadians(fAngle);
			float fLength = (float)(rand() % 10 + 1) * 0.1f;	//x��z�����̉��Z���x���̌��ʂ��傫���Ƒf��������
			float fHigh = (float)(rand() % 26 + 1) * 0.1f;	//x��z�����̉��Z���x���̌��ʂ��傫���Ƒf��������
			move.x += cosf(fAngle) * fLength;
			move.y += sinf(fAngle) * fHigh;			//�����̈ړ����Z��

			float angle = atan2f(move.y, move.x);
			XMFLOAT3 scl = { 0.02f, 0.2f, 0.02f };	//�g�嗦
			XMFLOAT3 rot = { 0.0f, cam->rot.y, 0.0f };	//��]���B������K�v�Ȃ�
			int nLife = rand() % 41 + 118;
			rot.z = angle - XM_PI * 0.5f;
			rot.y = cam->rot.y;
			if ((rot.y > XM_PI * 0.25f && rot.y < XM_PI * 0.75f) || (rot.y < XM_PI * -0.25f && rot.y > XM_PI * -0.75f)) {
				move.z = move.x;
				move.x = 0.0f;
			}
			SetParticle(pos, move, rot, scl, XMFLOAT4(0.5f, 0.5f, 1.0f, 1.0f), nLife, 118, 0, TRUE);
			SetParticle(pos2, move, rot, scl, XMFLOAT4(0.5f, 0.5f, 1.0f, 1.0f), nLife, 118, 0, TRUE);
		}

	}

}
//void Xgun::Draw(void)
//{
//	// �J�����O����
//	SetCullingMode(CULL_MODE_NONE);
//
//	XMMATRIX mtxScl, mtxRot, mtxTranslate, mtxWorld;
//	for (int i = 0; i < 2; i++) {
//		if (g_PlayerArm[i].use != TRUE)return;
//		// ���[���h�}�g���b�N�X�̏�����
//		mtxWorld = XMMatrixIdentity();
//
//		// �X�P�[���𔽉f
//		mtxScl = XMMatrixScaling(g_PlayerArm[i].scl.x, g_PlayerArm[i].scl.y, g_PlayerArm[i].scl.z);
//		mtxWorld = XMMatrixMultiply(mtxWorld, mtxScl);
//
//		// ��]�𔽉f
//		mtxRot = XMMatrixRotationRollPitchYaw(g_PlayerArm[i].rot.x, g_PlayerArm[i].rot.y, g_PlayerArm[i].rot.z);
//		mtxWorld = XMMatrixMultiply(mtxWorld, mtxRot);
//
//		// �ړ��𔽉f
//		mtxTranslate = XMMatrixTranslation(g_PlayerArm[i].pos.x, g_PlayerArm[i].pos.y, g_PlayerArm[i].pos.z);
//		mtxWorld = XMMatrixMultiply(mtxWorld, mtxTranslate);
//
//		mtxWorld = XMMatrixMultiply(mtxWorld, XMLoadFloat4x4(&g_PlayerArm[i].parent->mtxWorld));
//		XMStoreFloat4x4(&g_PlayerArm[i].mtxWorld, mtxWorld);
//
//		// ���[���h�}�g���b�N�X�̐ݒ�
//		SetWorldMatrix(&mtxWorld);
//
//		// ���f���`��
//		DrawModel(&g_PlayerArm[i].model);
//
//		// �J�����O�ݒ��߂�
//		SetCullingMode(CULL_MODE_BACK);
//	}
//}


pArm* Xgun::GetArm(void)
{
	return &g_PlayerArm;
}