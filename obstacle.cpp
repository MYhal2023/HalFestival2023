#include "obstacle.h"
#include "player.h"
#include "bullet.h"
#include "collision.h"
#include "debugproc.h"
#include "result.h"
#include "meshwall.h"
#include "fire.h"
static Obstacle g_Obstacle[MAX_OBSTACLE];
static 	DX11_MODEL		model[MAX_OBSTACLE_MODEL];		// モデル情報
static XMFLOAT4			tankglass_diffuse[16];

//初期化
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
	//タンクガラスだけ透明度を上げる
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
//終了処理
void Obstacle::Uninit(void)
{
	for (int i = 0; i < MAX_OBSTACLE_MODEL; i++)
	{
		// モデルの解放処理
		UnloadModel(&model[i]);
	}
}

//更新
void Obstacle::Update(void)
{
	for (int i = 0; i < MAX_OBSTACLE; i++)
	{
		if (!g_Obstacle[i].use)continue;

		Obstacle::Distract(&g_Obstacle[i]);	//壊れてるのかをチェック
	}
}

void Obstacle::Effect(Obstacle* p)
{
	//エフェクトスイッチがオンの奴だけエフェクトかける
	if (!p->efSwitch)return;

	//以下にエフェクトコードを記述。


	if (p->efFinish)
		p->efSwitch = FALSE;
}

void Obstacle::Distract(Obstacle* p)
{
	//耐久度0以下で消滅
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
	case om_book:		//本
		if (rot.y == 0.0f || rot.y == 1.0f) {
			set_x = 20.0f;
			set_z = 20.0f;
		}
		else
		{
			set_x = 20.0f;
			set_z = 20.0f;
		}

		ob->mesh_wall[i++] = GetMeshWallNum();

		InitMeshWall(XMFLOAT3(pos.x, pos.y, pos.z - set_x), XMFLOAT3(0.0f, XM_PI*0.0f, 0.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
			1, 1, set_z * 2.0f - 15.0f, set_x * 2.0f - 1.0f, WALL_RAY);
		ob->p_fire[0] = SetFireEffect(XMFLOAT3(pos.x, pos.y + 35.0f, pos.z), XMFLOAT3(0.0f, XM_PI * 0.0f, 0.0f));
		ob->p_fire[1] = SetFireEffect(XMFLOAT3(pos.x, pos.y + 35.0f, pos.z), XMFLOAT3(0.0f, XM_PI * 1.0f, 0.0f));
		ob->p_fire[2] = SetFireEffect(XMFLOAT3(pos.x, pos.y + 35.0f, pos.z), XMFLOAT3(0.0f, XM_PI * 0.5f, 0.0f));
		ob->p_fire[3] = SetFireEffect(XMFLOAT3(pos.x, pos.y + 35.0f, pos.z), XMFLOAT3(0.0f, XM_PI * 1.5f, 0.0f));

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
	case om_bookshelf:	//本だな
		if (rot.y == XM_PI * 0.0f || rot.y == XM_PI * 1.0f) {
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

	case om_Ldesk:		//L字の机
		pos.y -= 20.0f;
		if (rot.y == XM_PI * 0.0f || rot.y == XM_PI * 1.0f) {
			set_x = 100.0f;
			set_z = 37.0f;
		}
		else
		{
			set_x = 37.0f;
			set_z = 100.0f;
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
	case om_tank:		//タンク
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
	case om_box:			//謎のがらくた
		set_x = 55.0f;
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
	case om_duct:		//ダクトの接続部分？
		break;
	case om_monitor:		//モニター
		if (rot.y == 0.0f || rot.y == 1.0f) {
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
	case om_steel:		//鉄鋼
		set_x = 60.0f;
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
	case om_break_wall:	//破壊できる壁
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
	// カリング無効
	SetCullingMode(CULL_MODE_NONE);

	XMMATRIX mtxScl, mtxRot, mtxTranslate, mtxWorld;

	for (int i = 0; i < MAX_OBSTACLE; i++)
	{
		if (g_Obstacle[i].use != TRUE)continue;
		// ワールドマトリックスの初期化
		mtxWorld = XMMatrixIdentity();

		// スケールを反映
		mtxScl = XMMatrixScaling(g_Obstacle[i].scl.x, g_Obstacle[i].scl.y, g_Obstacle[i].scl.z);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxScl);

		// 回転を反映
		mtxRot = XMMatrixRotationRollPitchYaw(g_Obstacle[i].rot.x, g_Obstacle[i].rot.y, g_Obstacle[i].rot.z);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxRot);

		// 移動を反映
		mtxTranslate = XMMatrixTranslation(g_Obstacle[i].pos.x, g_Obstacle[i].pos.y, g_Obstacle[i].pos.z);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxTranslate);

		// ワールドマトリックスの設定
		SetWorldMatrix(&mtxWorld);

		XMStoreFloat4x4(&g_Obstacle[i].mtxWorld, mtxWorld);

		// モデル描画
		DrawModel(&model[g_Obstacle[i].model_num]);

	}

	// カリング設定を戻す
	SetCullingMode(CULL_MODE_BACK);

}
