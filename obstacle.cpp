#include "obstacle.h"
#include "player.h"
#include "bullet.h"
#include "collision.h"
#include "debugproc.h"
#include "result.h"
#include "meshwall.h"
#include "fire.h"
static Obstacle g_Obstacle[MAX_OBSTACLE];
static 	DX11_MODEL		model[MAX_OBSTACLE_MODEL];		// ���f�����
static XMFLOAT4			tankglass_diffuse[16];

//������
void Obstacle::Init(void)
{
	//LoadModel(MODEL_HEAD, &g_Parts[0].model);
	//LoadModel(MODEL_LEG, &g_Parts[1].model);
	for (int i = 0; i < MAX_OBSTACLE; i++)
	{
		g_Obstacle[i].use = FALSE;
		g_Obstacle[i].efSwitch = FALSE;
	}

}
void Obstacle::InitBoot(void)
{
	LoadModel(MODEL_BOOK, &model[om_book]);
	LoadModel(MODEL_BOOKSHELF, &model[om_bookshelf]);
	LoadModel(MODEL_LDESK, &model[om_Ldesk]);
	LoadModel(MODEL_TANK, &model[om_tank]);
	LoadModel(MODEL_TANKGLASS, &model[om_tankglass]);
	//�^���N�K���X���������x���グ��
	GetModelDiffuse(&model[om_tankglass], &tankglass_diffuse[0]);
	for (int j = 0; j < model[om_tankglass].SubsetNum; j++)
		SetModelDiffuse(&model[om_tankglass], j, XMFLOAT4(1.0f, 1.0f, 1.0f, 0.2f));

	LoadModel(MODEL_TROLLEY, &model[om_trolley]);
	LoadModel(MODEL_BOX, &model[om_box]);
	LoadModel(MODEL_DCUT, &model[om_duct]);
	LoadModel(MODEL_GASTANK, &model[om_gastank]);
	LoadModel(MODEL_MONITOR, &model[om_monitor]);
	LoadModel(MODEL_STEEL, &model[om_steel]);
	LoadModel(MODEL_TEST, &model[om_test]);
	LoadModel(MODEL_BREAK_WALL, &model[om_break_wall]);
	//LoadModel(MODEL_TERMINAL, &model[om_terminal]);
}
//�I������
void Obstacle::Uninit(void)
{
	for (int i = 0; i < MAX_OBSTACLE_MODEL; i++)
	{
		// ���f���̉������
		UnloadModel(&model[i]);
	}
}

//�X�V
void Obstacle::Update(void)
{
	for (int i = 0; i < MAX_OBSTACLE; i++)
	{
		if (!g_Obstacle[i].use)continue;

#ifdef _DEBUG
		PrintDebugProc("\n�ϋv�x:%f", g_Obstacle[i].durability);
#endif
		Obstacle::Distract(&g_Obstacle[i]);	//���Ă�̂����`�F�b�N
	}
}

void Obstacle::Effect(Obstacle* p)
{
	//�G�t�F�N�g�X�C�b�`���I���̓z�����G�t�F�N�g������
	if (!p->efSwitch)return;

	//�ȉ��ɃG�t�F�N�g�R�[�h���L�q�B


	if (p->efFinish)
		p->efSwitch = FALSE;
}

void Obstacle::Distract(Obstacle* p)
{
	//�ϋv�x0�ȉ��ŏ���
	if (p->durability > 0)
		return;

	Reward* re = GetReward();
	re->beatNum++;
	p->use = FALSE;
	p->efSwitch = TRUE;
	for (int i = 0; i < 4; i++)
		DeleteMeshWall(p->mesh_wall[i]);
	for (int i = 0; i < 4; i++) {
		if (p->p_fire[i] != nullptr)
			p->p_fire[i]->use = FALSE;
	}
}

void Obstacle::SetObstacle(XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 scl, float durability, float size, int model)
{
	for (int i = 0; i < MAX_OBSTACLE; i++) {
		if (g_Obstacle[i].use)continue;

		g_Obstacle[i].model_num = model;
		g_Obstacle[i].use = TRUE;
		g_Obstacle[i].pos = pos;
		g_Obstacle[i].rot = rot;
		g_Obstacle[i].scl = scl;
		g_Obstacle[i].size = size;
		g_Obstacle[i].durability = durability;
		Obstacle::SetHitMeshWall(pos, rot, model, &g_Obstacle[i]);
		break;
	}
}

Obstacle * Obstacle::GetObstacle(void)
{
	return &g_Obstacle[0];
}

void Obstacle::SetHitMeshWall(XMFLOAT3 pos, XMFLOAT3 rot, int model_num, Obstacle *ob)
{
	int x = -1;
	int z = -1;
	float set_x = 2.0f;
	float set_z = 2.0f;
	int i = 0;
	switch (model_num)
	{
	case om_book:		//�{
		break;
	case om_bookshelf:	//�{����
		if (rot.y == 0.0f) {
			set_x = 15.0f;
			set_z = 40.0f;
		}
		else
		{
			set_x = 40.0f;
			set_z = 15.0f;
		}

		ob->mesh_wall[i++] = GetMeshWallNum();

		InitMeshWall(XMFLOAT3(pos.x, pos.y, pos.z - set_x), XMFLOAT3(0.0f, XM_PI*0.0f, 0.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
			1, 1, set_z * 2.0f - 15.0f, set_x * 2.0f - 1.0f, WALL_RAY);
		ob->p_fire[0] = SetFireEffect(XMFLOAT3(pos.x, pos.y + 40.0f, pos.z - set_x), XMFLOAT3(0.0f, XM_PI * 0.0f, 0.0f));

		ob->mesh_wall[i++] = GetMeshWallNum();
		InitMeshWall(XMFLOAT3(pos.x - set_z, pos.y, pos.z), XMFLOAT3(0.0f, XM_PI*0.5f, 0.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
			1, 1, set_x * 2.0f - 15.0f, set_x * 2.0f - 1.0f, WALL_RAY);
		ob->p_fire[1] = SetFireEffect(XMFLOAT3(pos.x - set_z, pos.y + 40.0f, pos.z), XMFLOAT3(0.0f, XM_PI * 0.5f, 0.0f));

		ob->mesh_wall[i++] = GetMeshWallNum();
		InitMeshWall(XMFLOAT3(pos.x, pos.y, pos.z + set_x), XMFLOAT3(0.0f, XM_PI*0.0f, 0.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
			1, 1, set_z * 2.0f - 15.0f, set_x * 2.0f - 1.0f, WALL_RAY);
		ob->p_fire[2] = SetFireEffect(XMFLOAT3(pos.x, pos.y + 40.0f, pos.z + set_x), XMFLOAT3(0.0f, XM_PI * 1.0f, 0.0f));

		ob->mesh_wall[i++] = GetMeshWallNum();
		InitMeshWall(XMFLOAT3(pos.x + set_z, pos.y, pos.z), XMFLOAT3(0.0f, XM_PI*0.5f, 0.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
			1, 1, set_x * 2.0f - 15.0f, set_x * 2.0f - 1.0f, WALL_RAY);
		ob->p_fire[3] = SetFireEffect(XMFLOAT3(pos.x + set_z, pos.y + 40.0f, pos.z), XMFLOAT3(0.0f, XM_PI * 1.5f, 0.0f));
		break;

	case om_Ldesk:		//L���̊�
		set_x = 80.0f;
		ob->mesh_wall[i++] = GetMeshWallNum();
		InitMeshWall(XMFLOAT3(pos.x, pos.y, pos.z - set_x), XMFLOAT3(0.0f, XM_PI*0.0f, 0.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
			1, 1, set_x * 2.0f - 15.0f, set_x * 2.0f - 1.0f, WALL_RAY);
		ob->mesh_wall[i++] = GetMeshWallNum();
		InitMeshWall(XMFLOAT3(pos.x - set_x, pos.y, pos.z), XMFLOAT3(0.0f, XM_PI*0.5f, 0.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
			1, 1, set_x * 2.0f - 15.0f, set_x * 2.0f - 1.0f, WALL_RAY);
		ob->mesh_wall[i++] = GetMeshWallNum();
		InitMeshWall(XMFLOAT3(pos.x, pos.y, pos.z + set_x), XMFLOAT3(0.0f, XM_PI*0.0f, 0.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
			1, 1, set_x * 2.0f - 15.0f, set_x * 2.0f - 1.0f, WALL_RAY);
		ob->mesh_wall[i++] = GetMeshWallNum();
		InitMeshWall(XMFLOAT3(pos.x + set_x, pos.y, pos.z), XMFLOAT3(0.0f, XM_PI*0.5f, 0.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
			1, 1, set_x * 2.0f - 15.0f, set_x * 2.0f - 1.0f, WALL_RAY);

		break;
	case om_tank:		//�^���N
		set_x = 50.0f;
		ob->mesh_wall[i++] = GetMeshWallNum();
		InitMeshWall(XMFLOAT3(pos.x, pos.y, pos.z - set_x), XMFLOAT3(0.0f, XM_PI*0.0f, 0.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
			1, 1, set_x * 2.0f - 15.0f, set_x * 2.0f - 1.0f, WALL_RAY);
		ob->mesh_wall[i++] = GetMeshWallNum();
		InitMeshWall(XMFLOAT3(pos.x - set_x, pos.y, pos.z), XMFLOAT3(0.0f, XM_PI*0.5f, 0.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
			1, 1, set_x * 2.0f - 15.0f, set_x * 2.0f - 1.0f, WALL_RAY);
		ob->mesh_wall[i++] = GetMeshWallNum();
		InitMeshWall(XMFLOAT3(pos.x, pos.y, pos.z + set_x), XMFLOAT3(0.0f, XM_PI*0.0f, 0.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
			1, 1, set_x * 2.0f - 15.0f, set_x * 2.0f - 1.0f, WALL_RAY);
		ob->mesh_wall[i++] = GetMeshWallNum();
		InitMeshWall(XMFLOAT3(pos.x + set_x, pos.y, pos.z), XMFLOAT3(0.0f, XM_PI*0.5f, 0.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
			1, 1, set_x * 2.0f - 15.0f, set_x * 2.0f - 1.0f, WALL_RAY);

		break;
	case om_box:			//��̂��炭��
		set_x = 45.0f;
		ob->mesh_wall[i++] = GetMeshWallNum();
		InitMeshWall(XMFLOAT3(pos.x, pos.y, pos.z - set_x), XMFLOAT3(0.0f, XM_PI*0.0f, 0.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
			1, 1, set_x * 2.0f - 15.0f, set_x * 2.0f - 1.0f, WALL_RAY);
		ob->mesh_wall[i++] = GetMeshWallNum();
		InitMeshWall(XMFLOAT3(pos.x - set_x, pos.y, pos.z), XMFLOAT3(0.0f, XM_PI*0.5f, 0.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
			1, 1, set_x * 2.0f - 15.0f, set_x * 2.0f - 1.0f, WALL_RAY);
		ob->mesh_wall[i++] = GetMeshWallNum();
		InitMeshWall(XMFLOAT3(pos.x, pos.y, pos.z + set_x), XMFLOAT3(0.0f, XM_PI*0.0f, 0.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
			1, 1, set_x * 2.0f - 15.0f, set_x * 2.0f - 1.0f, WALL_RAY);
		ob->mesh_wall[i++] = GetMeshWallNum();
		InitMeshWall(XMFLOAT3(pos.x + set_x, pos.y, pos.z), XMFLOAT3(0.0f, XM_PI*0.5f, 0.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
			1, 1, set_x * 2.0f - 15.0f, set_x * 2.0f - 1.0f, WALL_RAY);
		break;
	case om_duct:		//�_�N�g�̐ڑ������H
		break;
	case om_monitor:		//���j�^�[
		if (rot.y == 0.0f) {
			set_x = 15.0f;
			set_z = 40.0f;
		}
		else
		{
			set_x = 40.0f;
			set_z = 15.0f;
		}
		ob->mesh_wall[i++] = GetMeshWallNum();
		InitMeshWall(XMFLOAT3(pos.x, pos.y, pos.z - set_x), XMFLOAT3(0.0f, XM_PI*0.0f, 0.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
			1, 1, set_z * 2.0f - 15.0f, set_x * 2.0f - 1.0f, WALL_RAY);
		ob->mesh_wall[i++] = GetMeshWallNum();
		InitMeshWall(XMFLOAT3(pos.x - set_z, pos.y, pos.z), XMFLOAT3(0.0f, XM_PI*0.5f, 0.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
			1, 1, set_x * 2.0f - 15.0f, set_x * 2.0f - 1.0f, WALL_RAY);
		ob->mesh_wall[i++] = GetMeshWallNum();
		InitMeshWall(XMFLOAT3(pos.x, pos.y, pos.z + set_x), XMFLOAT3(0.0f, XM_PI*0.0f, 0.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
			1, 1, set_z * 2.0f - 15.0f, set_x * 2.0f - 1.0f, WALL_RAY);
		ob->mesh_wall[i++] = GetMeshWallNum();
		InitMeshWall(XMFLOAT3(pos.x + set_z, pos.y, pos.z), XMFLOAT3(0.0f, XM_PI*0.5f, 0.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
			1, 1, set_x * 2.0f - 15.0f, set_x * 2.0f - 1.0f, WALL_RAY);
		break; 
	case om_steel:		//�S�|
		break; 
	case om_break_wall:	//�j��ł����
		if (rot.y == 0.0f) {
			set_x = 120.0f;
			set_z = 10.0f;
		}
		else
		{
			set_x = 10.0f;
			set_z = 120.0f;
		}
		ob->mesh_wall[i++] = GetMeshWallNum();
		InitMeshWall(XMFLOAT3(pos.x, pos.y, pos.z - set_x), XMFLOAT3(0.0f, XM_PI*0.0f, 0.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
			1, 1, set_z * 2.0f - 15.0f, set_x * 2.0f - 1.0f, WALL_RAY);
		ob->mesh_wall[i++] = GetMeshWallNum();
		InitMeshWall(XMFLOAT3(pos.x - set_z, pos.y, pos.z), XMFLOAT3(0.0f, XM_PI*0.5f, 0.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
			1, 1, set_x * 2.0f - 15.0f, set_x * 2.0f - 1.0f, WALL_RAY);
		ob->mesh_wall[i++] = GetMeshWallNum();
		InitMeshWall(XMFLOAT3(pos.x, pos.y, pos.z + set_x), XMFLOAT3(0.0f, XM_PI*0.0f, 0.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
			1, 1, set_z * 2.0f - 15.0f, set_x * 2.0f - 1.0f, WALL_RAY);
		ob->mesh_wall[i++] = GetMeshWallNum();
		InitMeshWall(XMFLOAT3(pos.x + set_z, pos.y, pos.z), XMFLOAT3(0.0f, XM_PI*0.5f, 0.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
			1, 1, set_x * 2.0f - 15.0f, set_x * 2.0f - 1.0f, WALL_RAY);
		break;
	}

}

void Obstacle::Draw(void)
{
	// �J�����O����
	SetCullingMode(CULL_MODE_NONE);

	XMMATRIX mtxScl, mtxRot, mtxTranslate, mtxWorld;

	for (int i = 0; i < MAX_OBSTACLE; i++)
	{
		if (g_Obstacle[i].use != TRUE)continue;
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
		DrawModel(&model[g_Obstacle[i].model_num]);

	}

	// �J�����O�ݒ��߂�
	SetCullingMode(CULL_MODE_BACK);

}
