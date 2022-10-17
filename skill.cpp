//=============================================================================
//
//  �X�L������[skill.cpp]
// Author : 
//�D�����݂̂ɍs�����ꏈ�����L��
//=============================================================================
#include "player.h"
#include "skill.h"
#include "cost.h"
#include "game.h"
#include "sound.h"
#include "enemy.h"
#include "collision.h"
#include "base.h"
#include "bullet.h"
#define SKILL_TIME (600)
static int atNum = 0;
//�D�����̃X�L������
void NeutroSkill(PLAYER *player)
{
	IncreaseCost(6);
	player->skillUse = FALSE;
	player->state = Standby;
}

//�}�N���t�@�[�W�̃X�L������
void MacroSkill(PLAYER *player, Playerliner *line, PlayerParts *parts)
{
	float attackCt = (float)(player->power);
	player->power = (int)(attackCt * 1.5f);
	//�U���͈͓��ɓG������ꍇ
	if (player->count > 0)
	{
		MacroInterPoration(player, line, parts);
	}
	else
	{
		MacroStand(player, line, parts);
	}

	//�X�L�����Ԃ𒴉߂����Ȃ�X�L����؂�
	player->skillTime++;
	if (player->skillTime >= player->skillTimeMax)
	{
		player->skillUse = FALSE;
		player->state = Standby;
		player->skillTime = 0;
	}
	player->power = (int)(attackCt);
}

//�w���p�[T�̃X�L������
void helperTSkill(PLAYER *player, Playerliner *line, PlayerParts *parts)
{
	//2�{���ōs��
	for (int i = 0; i < 2; i++) {
		//�U���͈͓��ɖ���������ꍇ
		if (player->count > 0)
		{
			HelperInterPoration(player, line, parts);
		}
		else
		{
			HelperStand(player, line, parts);
		}
	}
	//�X�L�����Ԃ𒴉߂����Ȃ�X�L����؂�
	player->skillTime++;
	if (player->skillTime >= player->skillTimeMax)
	{
		player->skillUse = FALSE;
		player->state = Standby;
		player->skillTime = 0;
	}
}

//�L���[T�̃X�L������
void KillerSkill(PLAYER *player, Playerliner *line, PlayerParts *parts)
{
	float attackCt = (float)(player->power);
	float time = (float)(player->skillPointMax);
	player->power = (int)(attackCt * 1.2f);
	player->skillPointMax = (int)(time * 1.2f);
	player->skillUse = FALSE;
	player->state = Standby;
	player->skillTime = 0;
}

//NK�̃X�L������ ����̒��g�L�����̂ŊJ���Ȃ��̐���
void NKSkill(PLAYER *player, Playerliner *line, PlayerParts *parts)
{
	for (int i = 0; i < 2; i++) {
		//�G�l�~�[�T��
		player->count = 0;
		for (int k = 0; k < MAX_TARGET; k++)
		{
			player->targetable[k] = 99;
		}

		for (int k = 0; k < MAX_ENEMY; k++)
		{
			ENEMY *enemy = GetEnemy();
			if (enemy[k].use != TRUE)continue;
			//�v���C���[�̍U���͈͂�1�̂ł��G������Ȃ�΍U�������ɓ���B�^�[�Q�b�g�����ۑ�
			if (CollisionBC(player->pos, enemy[k].pos, player->size * 0.5f, player->size * 0.5f))
			{
				player->targetable[player->count] = k;
				player->count++;
			}
		}
		//�U���͈͓��ɓG������ꍇ
		if (player->count > 0)
		{
			Base *base = GetBase();
			ENEMY *enemy = GetEnemy();
			float cmp = 0.0f;
			for (int k = 0; k < player->count; k++)
			{
				for (int j = 0; j < base->baseNum; j++)
				{
					XMVECTOR v1 = XMLoadFloat3(&base->pos[j]) - XMLoadFloat3(&enemy[player->targetable[k]].pos);
					XMFLOAT3 countData;
					XMStoreFloat3(&countData, v1);
					float dist = fabsf(countData.x) + fabsf(countData.y) + fabsf(countData.z);
					if (dist < cmp || cmp <= 0.0f)//���߂Ă�����ʂ�ꍇ�͐�Γ���邽�߂ɏ����l���Q��
					{
						cmp = dist;
						player->target = player->targetable[k];	//�G�l�~�[�̔z��ԍ��Ŏ��ʁB�|�C���^�[�œn���������ǁA���݂��̍\���̂Ƀ|�C���^�[�����o�ϐ�������Ɠ{����c
						XMVECTOR v2 = XMLoadFloat3(&enemy[player->targetable[k]].pos) - XMLoadFloat3(&player->pos);
						XMStoreFloat3(&countData, v2);
						float angle = atan2f(countData.x, countData.z);
						if (player->rot.y == 0.0f)player->rot.y = XM_PI * 2.0f;	//�o�O�C���ׁ̈A������t��������
						for (int d = 0; d < player->tbl_sizeA; d++)
						{
							float buffx = player->tbl_adrA[d].pos.x;
							float buffz = player->tbl_adrA[d].pos.z;
							player->tbl_adrA[d].pos.x = buffx * cosf(angle - player->rot.y) + buffz * sinf(angle - player->rot.y);
							player->tbl_adrA[d].pos.z = buffz * cosf(angle - player->rot.y) + buffx * -sinf(angle - player->rot.y);
						}
						player->rot.y = angle;
					}
				}
			}


			NKInterPoration(player, line, parts);
		}
		else
		{
			NKStand(player, line, parts);
		}
	}

	//�X�L�����Ԃ𒴉߂����Ȃ�X�L����؂�
	player->skillTime++;
	if (player->skillTime >= player->skillTimeMax)
	{
		player->skillUse = FALSE;
		player->state = Standby;
		player->skillTime = 0;
	}
}

//�D����̃X�L������
void KouenSkill(PLAYER *player, Playerliner *line, PlayerParts *parts)
{
	if (player->skillTime <= 0) {
		player->attackUse = FALSE;
		player->atFrame = 5;
		atNum = 0;
	}
	//�G�l�~�[�T��
	player->count = 0;
	for (int k = 0; k < MAX_TARGET; k++)
	{
		player->targetable[k] = 99;
	}

	for (int k = 0; k < MAX_ENEMY; k++)
	{
		ENEMY *enemy = GetEnemy();
		if (enemy[k].use != TRUE)continue;
		//�v���C���[�̍U���͈͂�1�̂ł��G������Ȃ�΍U�������ɓ���B�^�[�Q�b�g�����ۑ�
		if (CollisionBC(player->pos, enemy[k].pos, player->size * 0.5f, player->size * 0.5f))
		{
			player->targetable[player->count] = k;
			player->count++;
		}
	}
	//�U���͈͓��ɓG������ꍇ
	if (player->count > 0)
	{
		Base *base = GetBase();
		ENEMY *enemy = GetEnemy();
		float cmp = 0.0f;
		for (int k = 0; k < player->count; k++)
		{
			for (int j = 0; j < base->baseNum; j++)
			{
				XMVECTOR v1 = XMLoadFloat3(&base->pos[j]) - XMLoadFloat3(&enemy[player->targetable[k]].pos);
				XMFLOAT3 countData;
				XMStoreFloat3(&countData, v1);
				float dist = fabsf(countData.x) + fabsf(countData.y) + fabsf(countData.z);
				if (dist < cmp || cmp <= 0.0f)//���߂Ă�����ʂ�ꍇ�͐�Γ���邽�߂ɏ����l���Q��
				{
					cmp = dist;
					player->target = player->targetable[k];	//�G�l�~�[�̔z��ԍ��Ŏ��ʁB�|�C���^�[�œn���������ǁA���݂��̍\���̂Ƀ|�C���^�[�����o�ϐ�������Ɠ{����c
					XMVECTOR v2 = XMLoadFloat3(&enemy[player->targetable[k]].pos) - XMLoadFloat3(&player->pos);
					XMStoreFloat3(&countData, v2);
					float angle = atan2f(countData.x, countData.z);
					if (player->rot.y == 0.0f)player->rot.y = XM_PI * 2.0f;	//�o�O�C���ׁ̈A������t��������
					for (int d = 0; d < player->tbl_sizeA; d++)
					{
						float buffx = player->tbl_adrA[d].pos.x;
						float buffz = player->tbl_adrA[d].pos.z;
						player->tbl_adrA[d].pos.x = buffx * cosf(angle - player->rot.y) + buffz * sinf(angle - player->rot.y);
						player->tbl_adrA[d].pos.z = buffz * cosf(angle - player->rot.y) + buffx * -sinf(angle - player->rot.y);
					}
					player->rot.y = angle;
				}
			}
		}


		KouenInterPoration(player, line, parts);
	}
	else
	{
		KouenStand(player, line, parts);
	}

	//�X�L�����Ԃ𒴉߂����Ȃ�X�L����؂�
	player->skillTime++;
	if (player->skillTime >= player->skillTimeMax)
	{
		player->skillUse = FALSE;
		player->state = Standby;
		player->skillTime = 0;
		player->atFrame = 5;
		atNum = 0;
	}
}

//���������ɐ��`��Ԃƍׂ����U������
void MacroInterPoration(PLAYER *player, Playerliner *line, PlayerParts *parts)
{
	if (player->tbl_adrA == NULL)return;	// ���`��Ԃ����s����H

	//
	// ���`��Ԃ̏���
	// �ړ�����
	int		index = (int)player->move_time;
	float	time = player->move_time - index;
	int		size = player->tbl_sizeA;

	float dt = 1.0f / player->tbl_adrA[index].frame;	// 1�t���[���Ői�߂鎞��
	player->move_time += dt;							// �A�j���[�V�����̍��v���Ԃɑ���

	if (index > (size - 2))	// �S�[�����I�[�o�[���Ă�����A�f�[�^���ŏ��ɖ߂��čU�����I��
	{
		player->move_time = 0.0f;
		index = 0;
		player->atCount = 0;
		player->state = Standby;
		player->attackUse = FALSE;
		line->pos = { 0.0f, 0.0f, 0.0f };
		line->rot = { 0.0f, 0.0f, 0.0f };
		line->scl = { 0.0f, 0.0f, 0.0f };
	}
	// ���W�����߂�	X = StartX + (EndX - StartX) * ���̎���
	XMVECTOR p1 = XMLoadFloat3(&player->tbl_adrA[index + 1].pos);	// ���̏ꏊ
	XMVECTOR p0 = XMLoadFloat3(&player->tbl_adrA[index + 0].pos);	// ���݂̏ꏊ
	XMVECTOR vec = p1 - p0;
	XMStoreFloat3(&line->pos, p0 + vec * time);

	// ��]�����߂�	R = StartX + (EndX - StartX) * ���̎���
	XMVECTOR r1 = XMLoadFloat3(&player->tbl_adrA[index + 1].rot);	// ���̊p�x
	XMVECTOR r0 = XMLoadFloat3(&player->tbl_adrA[index + 0].rot);	// ���݂̊p�x
	XMVECTOR rot = r1 - r0;
	XMStoreFloat3(&line->rot, r0 + rot * time);

	// scale�����߂� S = StartX + (EndX - StartX) * ���̎���
	XMVECTOR s1 = XMLoadFloat3(&player->tbl_adrA[index + 1].scl);	// ����Scale
	XMVECTOR s0 = XMLoadFloat3(&player->tbl_adrA[index + 0].scl);	// ���݂�Scale
	XMVECTOR scl = s1 - s0;
	XMStoreFloat3(&line->scl, s0 + scl * time);

	for (int k = player->startNum; k < player->startNum + player->partsNum; k++)
	{
		if (parts[k].tbl_adrA == NULL)continue;;	// ���`��Ԃ����s����H

		int		index = (int)parts[k].move_time;
		float	time = parts[k].move_time - index;
		int		size = parts[k].tbl_sizeA;

		float dt = 1.0f / parts[k].tbl_adrA[index].frame;	// 1�t���[���Ői�߂鎞��
		parts[k].move_time += dt;							// �A�j���[�V�����̍��v���Ԃɑ���

		if (index > (size - 2))	// �S�[�����I�[�o�[���Ă�����A�f�[�^���ŏ��ɖ߂��čU�����I��
		{
			parts[k].move_time = 0.0f;
			index = 0;
		}

		// ���W�����߂�	X = StartX + (EndX - StartX) * ���̎���
		XMVECTOR p1 = XMLoadFloat3(&parts[k].tbl_adrA[index + 1].pos);	// ���̏ꏊ
		XMVECTOR p0 = XMLoadFloat3(&parts[k].tbl_adrA[index + 0].pos);	// ���݂̏ꏊ
		XMVECTOR vec = p1 - p0;
		XMStoreFloat3(&parts[k].pos, p0 + vec * time);

		// ��]�����߂�	R = StartX + (EndX - StartX) * ���̎���
		XMVECTOR r1 = XMLoadFloat3(&parts[k].tbl_adrA[index + 1].rot);	// ���̊p�x
		XMVECTOR r0 = XMLoadFloat3(&parts[k].tbl_adrA[index + 0].rot);	// ���݂̊p�x
		XMVECTOR rot = r1 - r0;
		XMStoreFloat3(&parts[k].rot, r0 + rot * time);

		// scale�����߂� S = StartX + (EndX - StartX) * ���̎���
		XMVECTOR s1 = XMLoadFloat3(&parts[k].tbl_adrA[index + 1].scl);	// ����Scale
		XMVECTOR s0 = XMLoadFloat3(&parts[k].tbl_adrA[index + 0].scl);	// ���݂�Scale
		XMVECTOR scl = s1 - s0;
		XMStoreFloat3(&parts[k].scl, s0 + scl * time);
	}

	//��������U������
	if (player->attackUse == TRUE)return;	//�Z�b�g���Ă��Ȃ��A�Z�b�g����K�v���Ȃ��U�������邩���H
	player->atFrameCount++;
	ENEMY *enemy = GetEnemy();
	//�U���t���[���ɒB������A�_���[�W�v�Z�֐������Ƀ^�[�Q�b�g�Ƀ_���[�W
	if (player->atFrameCount >= player->atFrame) {
		for (int s = 0; s < player->count; s++) {
			enemy[player->targetable[s]].life -= DamageFunc(player->power, enemy[player->targetable[s]].diffend);
		}
		player->atFrameCount = 0;
		player->attackUse = TRUE;
		PlaySound(player->attackSE);
	}
}

void MacroStand(PLAYER *player, Playerliner *line, PlayerParts *parts)
{
	if (player->tbl_adrM == NULL)return;	// ���`��Ԃ����s����H

//
// ���`��Ԃ̏���
// �ړ�����
	int		index = (int)player->move_time;
	float	time = player->move_time - index;
	int		size = player->tbl_sizeM;

	float dt = 1.0f / player->tbl_adrM[index].frame;	// 1�t���[���Ői�߂鎞��
	player->move_time += dt;							// �A�j���[�V�����̍��v���Ԃɑ���

	if (index > (size - 2))	// �S�[�����I�[�o�[���Ă�����A�f�[�^���ŏ��ɖ߂��čU�����I��
	{
		player->move_time = 0.0f;
		index = 0;
		line->pos = { 0.0f, 0.0f, 0.0f };
		line->rot = { 0.0f, 0.0f, 0.0f };
		line->scl = { 0.0f, 0.0f, 0.0f };
	}

	// ���W�����߂�	X = StartX + (EndX - StartX) * ���̎���
	XMVECTOR p1 = XMLoadFloat3(&player->tbl_adrM[index + 1].pos);	// ���̏ꏊ
	XMVECTOR p0 = XMLoadFloat3(&player->tbl_adrM[index + 0].pos);	// ���݂̏ꏊ
	XMVECTOR vec = p1 - p0;
	XMStoreFloat3(&line->pos, p0 + vec * time);

	// ��]�����߂�	R = StartX + (EndX - StartX) * ���̎���
	XMVECTOR r1 = XMLoadFloat3(&player->tbl_adrM[index + 1].rot);	// ���̊p�x
	XMVECTOR r0 = XMLoadFloat3(&player->tbl_adrM[index + 0].rot);	// ���݂̊p�x
	XMVECTOR rot = r1 - r0;
	XMStoreFloat3(&line->rot, r0 + rot * time);

	// scale�����߂� S = StartX + (EndX - StartX) * ���̎���
	XMVECTOR s1 = XMLoadFloat3(&player->tbl_adrM[index + 1].scl);	// ����Scale
	XMVECTOR s0 = XMLoadFloat3(&player->tbl_adrM[index + 0].scl);	// ���݂�Scale
	XMVECTOR scl = s1 - s0;
	XMStoreFloat3(&line->scl, s0 + scl * time);

	for (int k = player->startNum; k < player->startNum + player->partsNum; k++)
	{
		if (parts[k].tbl_adrM == NULL)continue;;	// ���`��Ԃ����s����H

		int		index = (int)parts[k].move_time;
		float	time = parts[k].move_time - index;
		int		size = parts[k].tbl_sizeM;

		float dt = 1.0f / parts[k].tbl_adrM[index].frame;	// 1�t���[���Ői�߂鎞��
		parts[k].move_time += dt;							// �A�j���[�V�����̍��v���Ԃɑ���

		if (index > (size - 2))	// �S�[�����I�[�o�[���Ă�����A�f�[�^���ŏ��ɖ߂��čU�����I��
		{
			parts[k].move_time = 0.0f;
			index = 0;
		}

		// ���W�����߂�	X = StartX + (EndX - StartX) * ���̎���
		XMVECTOR p1 = XMLoadFloat3(&parts[k].tbl_adrM[index + 1].pos);	// ���̏ꏊ
		XMVECTOR p0 = XMLoadFloat3(&parts[k].tbl_adrM[index + 0].pos);	// ���݂̏ꏊ
		XMVECTOR vec = p1 - p0;
		XMStoreFloat3(&parts[k].pos, p0 + vec * time);

		// ��]�����߂�	R = StartX + (EndX - StartX) * ���̎���
		XMVECTOR r1 = XMLoadFloat3(&parts[k].tbl_adrM[index + 1].rot);	// ���̊p�x
		XMVECTOR r0 = XMLoadFloat3(&parts[k].tbl_adrM[index + 0].rot);	// ���݂̊p�x
		XMVECTOR rot = r1 - r0;
		XMStoreFloat3(&parts[k].rot, r0 + rot * time);

		// scale�����߂� S = StartX + (EndX - StartX) * ���̎���
		XMVECTOR s1 = XMLoadFloat3(&parts[k].tbl_adrM[index + 1].scl);	// ����Scale
		XMVECTOR s0 = XMLoadFloat3(&parts[k].tbl_adrM[index + 0].scl);	// ���݂�Scale
		XMVECTOR scl = s1 - s0;
		XMStoreFloat3(&parts[k].scl, s0 + scl * time);
	}
}

void HelperInterPoration(PLAYER *player, Playerliner *line, PlayerParts *parts)
{
	if (player->tbl_adrA == NULL)return;	// ���`��Ԃ����s����H

	//
	// ���`��Ԃ̏���
	// �ړ�����
	int		index = (int)player->move_time;
	float	time = player->move_time - index;
	int		size = player->tbl_sizeA;

	float dt = 1.0f / player->tbl_adrA[index].frame;	// 1�t���[���Ői�߂鎞��
	player->move_time += dt;							// �A�j���[�V�����̍��v���Ԃɑ���

	if (index > (size - 2))	// �S�[�����I�[�o�[���Ă�����A�f�[�^���ŏ��ɖ߂��čU�����I��
	{
		player->move_time = 0.0f;
		index = 0;
		player->atCount = 0;
		player->state = Standby;
		player->attackUse = FALSE;
		line->pos = { 0.0f, 0.0f, 0.0f };
		line->rot = { 0.0f, 0.0f, 0.0f };
		line->scl = { 0.0f, 0.0f, 0.0f };
	}
	// ���W�����߂�	X = StartX + (EndX - StartX) * ���̎���
	XMVECTOR p1 = XMLoadFloat3(&player->tbl_adrA[index + 1].pos);	// ���̏ꏊ
	XMVECTOR p0 = XMLoadFloat3(&player->tbl_adrA[index + 0].pos);	// ���݂̏ꏊ
	XMVECTOR vec = p1 - p0;
	XMStoreFloat3(&line->pos, p0 + vec * time);

	// ��]�����߂�	R = StartX + (EndX - StartX) * ���̎���
	XMVECTOR r1 = XMLoadFloat3(&player->tbl_adrA[index + 1].rot);	// ���̊p�x
	XMVECTOR r0 = XMLoadFloat3(&player->tbl_adrA[index + 0].rot);	// ���݂̊p�x
	XMVECTOR rot = r1 - r0;
	XMStoreFloat3(&line->rot, r0 + rot * time);

	// scale�����߂� S = StartX + (EndX - StartX) * ���̎���
	XMVECTOR s1 = XMLoadFloat3(&player->tbl_adrA[index + 1].scl);	// ����Scale
	XMVECTOR s0 = XMLoadFloat3(&player->tbl_adrA[index + 0].scl);	// ���݂�Scale
	XMVECTOR scl = s1 - s0;
	XMStoreFloat3(&line->scl, s0 + scl * time);

	for (int k = player->startNum; k < player->startNum + player->partsNum; k++)
	{
		if (parts[k].tbl_adrA == NULL)continue;;	// ���`��Ԃ����s����H

		int		index = (int)parts[k].move_time;
		float	time = parts[k].move_time - index;
		int		size = parts[k].tbl_sizeA;

		float dt = 1.0f / parts[k].tbl_adrA[index].frame;	// 1�t���[���Ői�߂鎞��
		parts[k].move_time += dt;							// �A�j���[�V�����̍��v���Ԃɑ���

		if (index > (size - 2))	// �S�[�����I�[�o�[���Ă�����A�f�[�^���ŏ��ɖ߂��čU�����I��
		{
			parts[k].move_time = 0.0f;
			index = 0;
		}

		// ���W�����߂�	X = StartX + (EndX - StartX) * ���̎���
		XMVECTOR p1 = XMLoadFloat3(&parts[k].tbl_adrA[index + 1].pos);	// ���̏ꏊ
		XMVECTOR p0 = XMLoadFloat3(&parts[k].tbl_adrA[index + 0].pos);	// ���݂̏ꏊ
		XMVECTOR vec = p1 - p0;
		XMStoreFloat3(&parts[k].pos, p0 + vec * time);

		// ��]�����߂�	R = StartX + (EndX - StartX) * ���̎���
		XMVECTOR r1 = XMLoadFloat3(&parts[k].tbl_adrA[index + 1].rot);	// ���̊p�x
		XMVECTOR r0 = XMLoadFloat3(&parts[k].tbl_adrA[index + 0].rot);	// ���݂̊p�x
		XMVECTOR rot = r1 - r0;
		XMStoreFloat3(&parts[k].rot, r0 + rot * time);

		// scale�����߂� S = StartX + (EndX - StartX) * ���̎���
		XMVECTOR s1 = XMLoadFloat3(&parts[k].tbl_adrA[index + 1].scl);	// ����Scale
		XMVECTOR s0 = XMLoadFloat3(&parts[k].tbl_adrA[index + 0].scl);	// ���݂�Scale
		XMVECTOR scl = s1 - s0;
		XMStoreFloat3(&parts[k].scl, s0 + scl * time);
	}

	//��������U������
	if (player->attackUse == TRUE)return;	//�Z�b�g���Ă��Ȃ��A�Z�b�g����K�v���Ȃ��U�������邩���H
	player->atFrameCount++;
	PLAYER *g_Player = GetPlayer();
	//�U���t���[���ɒB������A�_���[�W�v�Z�֐������Ƀ^�[�Q�b�g�Ƀ_���[�W
	if (player->atFrameCount >= player->atFrame) {
		if (player->atFrameCount >= player->atFrame) {
			g_Player[player->target].life += DamageFunc(player->power, 0);
			//�񕜌�͍ő�l�ɍ��킹��
			if (g_Player[player->target].life > g_Player[player->target].lifeMax)
				g_Player[player->target].life = g_Player[player->target].lifeMax;
			player->atFrameCount = 0;
			player->attackUse = TRUE;
			PlaySound(player->attackSE);
		}
	}
}

//�ҋ@Ӱ��ݏ���
void HelperStand(PLAYER *player, Playerliner *line, PlayerParts *parts)
{
	if (player->tbl_adrM == NULL)return;	// ���`��Ԃ����s����H

//
// ���`��Ԃ̏���
// �ړ�����
	int		index = (int)player->move_time;
	float	time = player->move_time - index;
	int		size = player->tbl_sizeM;

	float dt = 1.0f / player->tbl_adrM[index].frame;	// 1�t���[���Ői�߂鎞��
	player->move_time += dt;							// �A�j���[�V�����̍��v���Ԃɑ���

	if (index > (size - 2))	// �S�[�����I�[�o�[���Ă�����A�f�[�^���ŏ��ɖ߂��čU�����I��
	{
		player->move_time = 0.0f;
		index = 0;
		line->pos = { 0.0f, 0.0f, 0.0f };
		line->rot = { 0.0f, 0.0f, 0.0f };
		line->scl = { 0.0f, 0.0f, 0.0f };
	}

	// ���W�����߂�	X = StartX + (EndX - StartX) * ���̎���
	XMVECTOR p1 = XMLoadFloat3(&player->tbl_adrM[index + 1].pos);	// ���̏ꏊ
	XMVECTOR p0 = XMLoadFloat3(&player->tbl_adrM[index + 0].pos);	// ���݂̏ꏊ
	XMVECTOR vec = p1 - p0;
	XMStoreFloat3(&line->pos, p0 + vec * time);

	// ��]�����߂�	R = StartX + (EndX - StartX) * ���̎���
	XMVECTOR r1 = XMLoadFloat3(&player->tbl_adrM[index + 1].rot);	// ���̊p�x
	XMVECTOR r0 = XMLoadFloat3(&player->tbl_adrM[index + 0].rot);	// ���݂̊p�x
	XMVECTOR rot = r1 - r0;
	XMStoreFloat3(&line->rot, r0 + rot * time);

	// scale�����߂� S = StartX + (EndX - StartX) * ���̎���
	XMVECTOR s1 = XMLoadFloat3(&player->tbl_adrM[index + 1].scl);	// ����Scale
	XMVECTOR s0 = XMLoadFloat3(&player->tbl_adrM[index + 0].scl);	// ���݂�Scale
	XMVECTOR scl = s1 - s0;
	XMStoreFloat3(&line->scl, s0 + scl * time);

	for (int k = player->startNum; k < player->startNum + player->partsNum; k++)
	{
		if (parts[k].tbl_adrM == NULL)continue;;	// ���`��Ԃ����s����H

		int		index = (int)parts[k].move_time;
		float	time = parts[k].move_time - index;
		int		size = parts[k].tbl_sizeM;

		float dt = 1.0f / parts[k].tbl_adrM[index].frame;	// 1�t���[���Ői�߂鎞��
		parts[k].move_time += dt;							// �A�j���[�V�����̍��v���Ԃɑ���

		if (index > (size - 2))	// �S�[�����I�[�o�[���Ă�����A�f�[�^���ŏ��ɖ߂��čU�����I��
		{
			parts[k].move_time = 0.0f;
			index = 0;
		}

		// ���W�����߂�	X = StartX + (EndX - StartX) * ���̎���
		XMVECTOR p1 = XMLoadFloat3(&parts[k].tbl_adrM[index + 1].pos);	// ���̏ꏊ
		XMVECTOR p0 = XMLoadFloat3(&parts[k].tbl_adrM[index + 0].pos);	// ���݂̏ꏊ
		XMVECTOR vec = p1 - p0;
		XMStoreFloat3(&parts[k].pos, p0 + vec * time);

		// ��]�����߂�	R = StartX + (EndX - StartX) * ���̎���
		XMVECTOR r1 = XMLoadFloat3(&parts[k].tbl_adrM[index + 1].rot);	// ���̊p�x
		XMVECTOR r0 = XMLoadFloat3(&parts[k].tbl_adrM[index + 0].rot);	// ���݂̊p�x
		XMVECTOR rot = r1 - r0;
		XMStoreFloat3(&parts[k].rot, r0 + rot * time);

		// scale�����߂� S = StartX + (EndX - StartX) * ���̎���
		XMVECTOR s1 = XMLoadFloat3(&parts[k].tbl_adrM[index + 1].scl);	// ����Scale
		XMVECTOR s0 = XMLoadFloat3(&parts[k].tbl_adrM[index + 0].scl);	// ���݂�Scale
		XMVECTOR scl = s1 - s0;
		XMStoreFloat3(&parts[k].scl, s0 + scl * time);
	}
}

void NKInterPoration(PLAYER *player, Playerliner *line, PlayerParts *parts)
{
	if (player->tbl_adrA == NULL)return;	// ���`��Ԃ����s����H

	//
	// ���`��Ԃ̏���
	// �ړ�����
	int		index = (int)player->move_time;
	float	time = player->move_time - index;
	int		size = player->tbl_sizeA;

	float dt = 1.0f / player->tbl_adrA[index].frame;	// 1�t���[���Ői�߂鎞��
	player->move_time += dt;							// �A�j���[�V�����̍��v���Ԃɑ���

	if (index > (size - 2))	// �S�[�����I�[�o�[���Ă�����A�f�[�^���ŏ��ɖ߂��čU�����I��
	{
		player->move_time = 0.0f;
		index = 0;
		player->atCount = 0;
		player->state = Standby;
		player->attackUse = FALSE;
		line->pos = { 0.0f, 0.0f, 0.0f };
		line->rot = { 0.0f, 0.0f, 0.0f };
		line->scl = { 0.0f, 0.0f, 0.0f };
	}
	// ���W�����߂�	X = StartX + (EndX - StartX) * ���̎���
	XMVECTOR p1 = XMLoadFloat3(&player->tbl_adrA[index + 1].pos);	// ���̏ꏊ
	XMVECTOR p0 = XMLoadFloat3(&player->tbl_adrA[index + 0].pos);	// ���݂̏ꏊ
	XMVECTOR vec = p1 - p0;
	XMStoreFloat3(&line->pos, p0 + vec * time);

	// ��]�����߂�	R = StartX + (EndX - StartX) * ���̎���
	XMVECTOR r1 = XMLoadFloat3(&player->tbl_adrA[index + 1].rot);	// ���̊p�x
	XMVECTOR r0 = XMLoadFloat3(&player->tbl_adrA[index + 0].rot);	// ���݂̊p�x
	XMVECTOR rot = r1 - r0;
	XMStoreFloat3(&line->rot, r0 + rot * time);

	// scale�����߂� S = StartX + (EndX - StartX) * ���̎���
	XMVECTOR s1 = XMLoadFloat3(&player->tbl_adrA[index + 1].scl);	// ����Scale
	XMVECTOR s0 = XMLoadFloat3(&player->tbl_adrA[index + 0].scl);	// ���݂�Scale
	XMVECTOR scl = s1 - s0;
	XMStoreFloat3(&line->scl, s0 + scl * time);

	for (int k = player->startNum; k < player->startNum + player->partsNum; k++)
	{
		if (parts[k].tbl_adrA == NULL)continue;;	// ���`��Ԃ����s����H

		int		index = (int)parts[k].move_time;
		float	time = parts[k].move_time - index;
		int		size = parts[k].tbl_sizeA;

		float dt = 1.0f / parts[k].tbl_adrA[index].frame;	// 1�t���[���Ői�߂鎞��
		parts[k].move_time += dt;							// �A�j���[�V�����̍��v���Ԃɑ���

		if (index > (size - 2))	// �S�[�����I�[�o�[���Ă�����A�f�[�^���ŏ��ɖ߂��čU�����I��
		{
			parts[k].move_time = 0.0f;
			index = 0;
		}

		// ���W�����߂�	X = StartX + (EndX - StartX) * ���̎���
		XMVECTOR p1 = XMLoadFloat3(&parts[k].tbl_adrA[index + 1].pos);	// ���̏ꏊ
		XMVECTOR p0 = XMLoadFloat3(&parts[k].tbl_adrA[index + 0].pos);	// ���݂̏ꏊ
		XMVECTOR vec = p1 - p0;
		XMStoreFloat3(&parts[k].pos, p0 + vec * time);

		// ��]�����߂�	R = StartX + (EndX - StartX) * ���̎���
		XMVECTOR r1 = XMLoadFloat3(&parts[k].tbl_adrA[index + 1].rot);	// ���̊p�x
		XMVECTOR r0 = XMLoadFloat3(&parts[k].tbl_adrA[index + 0].rot);	// ���݂̊p�x
		XMVECTOR rot = r1 - r0;
		XMStoreFloat3(&parts[k].rot, r0 + rot * time);

		// scale�����߂� S = StartX + (EndX - StartX) * ���̎���
		XMVECTOR s1 = XMLoadFloat3(&parts[k].tbl_adrA[index + 1].scl);	// ����Scale
		XMVECTOR s0 = XMLoadFloat3(&parts[k].tbl_adrA[index + 0].scl);	// ���݂�Scale
		XMVECTOR scl = s1 - s0;
		XMStoreFloat3(&parts[k].scl, s0 + scl * time);
	}

	//��������U������
	if (player->attackUse == TRUE)return;	//�Z�b�g���Ă��Ȃ��A�Z�b�g����K�v���Ȃ��U�������邩���H
	player->atFrameCount++;
	ENEMY *enemy = GetEnemy();
	//���o�p�̃o���b�g�Z�b�g
	if (player->skillID == NK_skill && player->atFrameCount == player->atFrame - 5) {
		ENEMY *enemy = GetEnemy();
		XMFLOAT3 setpos = { player->pos.x, player->pos.y + 15.0f, player->pos.z };
		SetBullet(setpos, player->rot, 1.0f, &enemy[player->target]);
	}
	//�U���t���[���ɒB������A�_���[�W�v�Z�֐������Ƀ^�[�Q�b�g�Ƀ_���[�W
	if (player->atFrameCount >= player->atFrame) {
		enemy[player->target].life -= DamageFunc(player->power, enemy[player->target].diffend);
		player->atFrameCount = 0;
		player->attackUse = TRUE;
		PlaySound(player->attackSE);
	}
}

void NKStand(PLAYER *player, Playerliner *line, PlayerParts *parts)
{
	if (player->tbl_adrM == NULL)return;	// ���`��Ԃ����s����H

//
// ���`��Ԃ̏���
// �ړ�����
	int		index = (int)player->move_time;
	float	time = player->move_time - index;
	int		size = player->tbl_sizeM;

	float dt = 1.0f / player->tbl_adrM[index].frame;	// 1�t���[���Ői�߂鎞��
	player->move_time += dt;							// �A�j���[�V�����̍��v���Ԃɑ���

	if (index > (size - 2))	// �S�[�����I�[�o�[���Ă�����A�f�[�^���ŏ��ɖ߂��čU�����I��
	{
		player->move_time = 0.0f;
		index = 0;
		line->pos = { 0.0f, 0.0f, 0.0f };
		line->rot = { 0.0f, 0.0f, 0.0f };
		line->scl = { 0.0f, 0.0f, 0.0f };
	}

	// ���W�����߂�	X = StartX + (EndX - StartX) * ���̎���
	XMVECTOR p1 = XMLoadFloat3(&player->tbl_adrM[index + 1].pos);	// ���̏ꏊ
	XMVECTOR p0 = XMLoadFloat3(&player->tbl_adrM[index + 0].pos);	// ���݂̏ꏊ
	XMVECTOR vec = p1 - p0;
	XMStoreFloat3(&line->pos, p0 + vec * time);

	// ��]�����߂�	R = StartX + (EndX - StartX) * ���̎���
	XMVECTOR r1 = XMLoadFloat3(&player->tbl_adrM[index + 1].rot);	// ���̊p�x
	XMVECTOR r0 = XMLoadFloat3(&player->tbl_adrM[index + 0].rot);	// ���݂̊p�x
	XMVECTOR rot = r1 - r0;
	XMStoreFloat3(&line->rot, r0 + rot * time);

	// scale�����߂� S = StartX + (EndX - StartX) * ���̎���
	XMVECTOR s1 = XMLoadFloat3(&player->tbl_adrM[index + 1].scl);	// ����Scale
	XMVECTOR s0 = XMLoadFloat3(&player->tbl_adrM[index + 0].scl);	// ���݂�Scale
	XMVECTOR scl = s1 - s0;
	XMStoreFloat3(&line->scl, s0 + scl * time);

	for (int k = player->startNum; k < player->startNum + player->partsNum; k++)
	{
		if (parts[k].tbl_adrM == NULL)continue;;	// ���`��Ԃ����s����H

		int		index = (int)parts[k].move_time;
		float	time = parts[k].move_time - index;
		int		size = parts[k].tbl_sizeM;

		float dt = 1.0f / parts[k].tbl_adrM[index].frame;	// 1�t���[���Ői�߂鎞��
		parts[k].move_time += dt;							// �A�j���[�V�����̍��v���Ԃɑ���

		if (index > (size - 2))	// �S�[�����I�[�o�[���Ă�����A�f�[�^���ŏ��ɖ߂��čU�����I��
		{
			parts[k].move_time = 0.0f;
			index = 0;
		}

		// ���W�����߂�	X = StartX + (EndX - StartX) * ���̎���
		XMVECTOR p1 = XMLoadFloat3(&parts[k].tbl_adrM[index + 1].pos);	// ���̏ꏊ
		XMVECTOR p0 = XMLoadFloat3(&parts[k].tbl_adrM[index + 0].pos);	// ���݂̏ꏊ
		XMVECTOR vec = p1 - p0;
		XMStoreFloat3(&parts[k].pos, p0 + vec * time);

		// ��]�����߂�	R = StartX + (EndX - StartX) * ���̎���
		XMVECTOR r1 = XMLoadFloat3(&parts[k].tbl_adrM[index + 1].rot);	// ���̊p�x
		XMVECTOR r0 = XMLoadFloat3(&parts[k].tbl_adrM[index + 0].rot);	// ���݂̊p�x
		XMVECTOR rot = r1 - r0;
		XMStoreFloat3(&parts[k].rot, r0 + rot * time);

		// scale�����߂� S = StartX + (EndX - StartX) * ���̎���
		XMVECTOR s1 = XMLoadFloat3(&parts[k].tbl_adrM[index + 1].scl);	// ����Scale
		XMVECTOR s0 = XMLoadFloat3(&parts[k].tbl_adrM[index + 0].scl);	// ���݂�Scale
		XMVECTOR scl = s1 - s0;
		XMStoreFloat3(&parts[k].scl, s0 + scl * time);
	}
}

void KouenInterPoration(PLAYER *player, Playerliner *line, PlayerParts *parts)
{
	if (player->tbl_adrA == NULL)return;	// ���`��Ԃ����s����H

	//
	// ���`��Ԃ̏���
	// �ړ�����
	int		index = (int)player->move_time;
	float	time = player->move_time - index;
	int		size = player->tbl_sizeA;

	float dt = 1.0f / player->tbl_adrA[index].frame;	// 1�t���[���Ői�߂鎞��
	player->move_time += dt;							// �A�j���[�V�����̍��v���Ԃɑ���

	if (index > (size - 2))	// �S�[�����I�[�o�[���Ă�����A�f�[�^���ŏ��ɖ߂��čU�����I��
	{
		player->move_time = 0.0f;
		index = 0;
		player->atCount = 0;
		player->state = Standby;
		player->attackUse = FALSE;
		atNum = 0;
		line->pos = { 0.0f, 0.0f, 0.0f };
		line->rot = { 0.0f, 0.0f, 0.0f };
		line->scl = { 0.0f, 0.0f, 0.0f };
	}
	// ���W�����߂�	X = StartX + (EndX - StartX) * ���̎���
	XMVECTOR p1 = XMLoadFloat3(&player->tbl_adrA[index + 1].pos);	// ���̏ꏊ
	XMVECTOR p0 = XMLoadFloat3(&player->tbl_adrA[index + 0].pos);	// ���݂̏ꏊ
	XMVECTOR vec = p1 - p0;
	XMStoreFloat3(&line->pos, p0 + vec * time);

	// ��]�����߂�	R = StartX + (EndX - StartX) * ���̎���
	XMVECTOR r1 = XMLoadFloat3(&player->tbl_adrA[index + 1].rot);	// ���̊p�x
	XMVECTOR r0 = XMLoadFloat3(&player->tbl_adrA[index + 0].rot);	// ���݂̊p�x
	XMVECTOR rot = r1 - r0;
	XMStoreFloat3(&line->rot, r0 + rot * time);

	// scale�����߂� S = StartX + (EndX - StartX) * ���̎���
	XMVECTOR s1 = XMLoadFloat3(&player->tbl_adrA[index + 1].scl);	// ����Scale
	XMVECTOR s0 = XMLoadFloat3(&player->tbl_adrA[index + 0].scl);	// ���݂�Scale
	XMVECTOR scl = s1 - s0;
	XMStoreFloat3(&line->scl, s0 + scl * time);

	for (int k = player->startNum; k < player->startNum + player->partsNum; k++)
	{
		if (parts[k].tbl_adrA == NULL)continue;;	// ���`��Ԃ����s����H

		int		index = (int)parts[k].move_time;
		float	time = parts[k].move_time - index;
		int		size = parts[k].tbl_sizeA;

		float dt = 1.0f / parts[k].tbl_adrA[index].frame;	// 1�t���[���Ői�߂鎞��
		parts[k].move_time += dt;							// �A�j���[�V�����̍��v���Ԃɑ���

		if (index > (size - 2))	// �S�[�����I�[�o�[���Ă�����A�f�[�^���ŏ��ɖ߂��čU�����I��
		{
			parts[k].move_time = 0.0f;
			index = 0;
		}

		// ���W�����߂�	X = StartX + (EndX - StartX) * ���̎���
		XMVECTOR p1 = XMLoadFloat3(&parts[k].tbl_adrA[index + 1].pos);	// ���̏ꏊ
		XMVECTOR p0 = XMLoadFloat3(&parts[k].tbl_adrA[index + 0].pos);	// ���݂̏ꏊ
		XMVECTOR vec = p1 - p0;
		XMStoreFloat3(&parts[k].pos, p0 + vec * time);

		// ��]�����߂�	R = StartX + (EndX - StartX) * ���̎���
		XMVECTOR r1 = XMLoadFloat3(&parts[k].tbl_adrA[index + 1].rot);	// ���̊p�x
		XMVECTOR r0 = XMLoadFloat3(&parts[k].tbl_adrA[index + 0].rot);	// ���݂̊p�x
		XMVECTOR rot = r1 - r0;
		XMStoreFloat3(&parts[k].rot, r0 + rot * time);

		// scale�����߂� S = StartX + (EndX - StartX) * ���̎���
		XMVECTOR s1 = XMLoadFloat3(&parts[k].tbl_adrA[index + 1].scl);	// ����Scale
		XMVECTOR s0 = XMLoadFloat3(&parts[k].tbl_adrA[index + 0].scl);	// ���݂�Scale
		XMVECTOR scl = s1 - s0;
		XMStoreFloat3(&parts[k].scl, s0 + scl * time);
	}

	//��������U������
	if (player->attackUse &&
		atNum < 12) {
		player->atFrameCount++;
		if (player->atFrameCount >= player->atFrame)
			player->attackUse = FALSE;
	}
	if (player->attackUse == TRUE)return;	//�Z�b�g���Ă��Ȃ��A�Z�b�g����K�v���Ȃ��U�������邩���H
	player->atFrameCount++;
	ENEMY *enemy = GetEnemy();
	if (player->atFrameCount >= player->atFrame - 1) {
		ENEMY *enemy = GetEnemy();
		XMFLOAT3 setpos = { player->pos.x + cosf(player->rot.y) * 20.0f, player->pos.y, player->pos.z + sinf(player->rot.y) *20.0f };
		XMFLOAT3 invpos = { player->pos.x - cosf(player->rot.y) * 20.0f, player->pos.y, player->pos.z - sinf(player->rot.y) *20.0f };
		SetBullet(setpos, player->rot, 0.5f, &enemy[player->target]);
		SetBullet(invpos, player->rot, 0.5f, &enemy[player->target]);
	}
	//�U���t���[���ɒB������A�_���[�W�v�Z�֐������Ƀ^�[�Q�b�g�Ƀ_���[�W
	if (player->atFrameCount >= player->atFrame) {
		enemy[player->target].life -= DamageFunc(player->power, enemy[player->target].diffend);
		player->atFrameCount = 0;
		player->attackUse = TRUE;
		if (atNum == 0)
			PlaySound(player->attackSE + 1);
		atNum++;
	}
}

void KouenStand(PLAYER *player, Playerliner *line, PlayerParts *parts)
{
	if (player->tbl_adrM == NULL)return;	// ���`��Ԃ����s����H

//
// ���`��Ԃ̏���
// �ړ�����
	int		index = (int)player->move_time;
	float	time = player->move_time - index;
	int		size = player->tbl_sizeM;

	float dt = 1.0f / player->tbl_adrM[index].frame;	// 1�t���[���Ői�߂鎞��
	player->move_time += dt;							// �A�j���[�V�����̍��v���Ԃɑ���

	if (index > (size - 2))	// �S�[�����I�[�o�[���Ă�����A�f�[�^���ŏ��ɖ߂��čU�����I��
	{
		player->move_time = 0.0f;
		index = 0;
		line->pos = { 0.0f, 0.0f, 0.0f };
		line->rot = { 0.0f, 0.0f, 0.0f };
		line->scl = { 0.0f, 0.0f, 0.0f };
	}

	// ���W�����߂�	X = StartX + (EndX - StartX) * ���̎���
	XMVECTOR p1 = XMLoadFloat3(&player->tbl_adrM[index + 1].pos);	// ���̏ꏊ
	XMVECTOR p0 = XMLoadFloat3(&player->tbl_adrM[index + 0].pos);	// ���݂̏ꏊ
	XMVECTOR vec = p1 - p0;
	XMStoreFloat3(&line->pos, p0 + vec * time);

	// ��]�����߂�	R = StartX + (EndX - StartX) * ���̎���
	XMVECTOR r1 = XMLoadFloat3(&player->tbl_adrM[index + 1].rot);	// ���̊p�x
	XMVECTOR r0 = XMLoadFloat3(&player->tbl_adrM[index + 0].rot);	// ���݂̊p�x
	XMVECTOR rot = r1 - r0;
	XMStoreFloat3(&line->rot, r0 + rot * time);

	// scale�����߂� S = StartX + (EndX - StartX) * ���̎���
	XMVECTOR s1 = XMLoadFloat3(&player->tbl_adrM[index + 1].scl);	// ����Scale
	XMVECTOR s0 = XMLoadFloat3(&player->tbl_adrM[index + 0].scl);	// ���݂�Scale
	XMVECTOR scl = s1 - s0;
	XMStoreFloat3(&line->scl, s0 + scl * time);

	for (int k = player->startNum; k < player->startNum + player->partsNum; k++)
	{
		if (parts[k].tbl_adrM == NULL)continue;;	// ���`��Ԃ����s����H

		int		index = (int)parts[k].move_time;
		float	time = parts[k].move_time - index;
		int		size = parts[k].tbl_sizeM;

		float dt = 1.0f / parts[k].tbl_adrM[index].frame;	// 1�t���[���Ői�߂鎞��
		parts[k].move_time += dt;							// �A�j���[�V�����̍��v���Ԃɑ���

		if (index > (size - 2))	// �S�[�����I�[�o�[���Ă�����A�f�[�^���ŏ��ɖ߂��čU�����I��
		{
			parts[k].move_time = 0.0f;
			index = 0;
		}

		// ���W�����߂�	X = StartX + (EndX - StartX) * ���̎���
		XMVECTOR p1 = XMLoadFloat3(&parts[k].tbl_adrM[index + 1].pos);	// ���̏ꏊ
		XMVECTOR p0 = XMLoadFloat3(&parts[k].tbl_adrM[index + 0].pos);	// ���݂̏ꏊ
		XMVECTOR vec = p1 - p0;
		XMStoreFloat3(&parts[k].pos, p0 + vec * time);

		// ��]�����߂�	R = StartX + (EndX - StartX) * ���̎���
		XMVECTOR r1 = XMLoadFloat3(&parts[k].tbl_adrM[index + 1].rot);	// ���̊p�x
		XMVECTOR r0 = XMLoadFloat3(&parts[k].tbl_adrM[index + 0].rot);	// ���݂̊p�x
		XMVECTOR rot = r1 - r0;
		XMStoreFloat3(&parts[k].rot, r0 + rot * time);

		// scale�����߂� S = StartX + (EndX - StartX) * ���̎���
		XMVECTOR s1 = XMLoadFloat3(&parts[k].tbl_adrM[index + 1].scl);	// ����Scale
		XMVECTOR s0 = XMLoadFloat3(&parts[k].tbl_adrM[index + 0].scl);	// ���݂�Scale
		XMVECTOR scl = s1 - s0;
		XMStoreFloat3(&parts[k].scl, s0 + scl * time);
	}
}
