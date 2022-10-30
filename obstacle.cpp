#include "obstacle.h"
#include "player.h"
#include "bullet.h"
#include "collision.h"
static Obstacle g_Obstacle[MAX_OBSTACLE];


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
	XMFLOAT3 s = { 0.0f, 0.0f, 0.0f };
	XMFLOAT3 m = { 1.0f, 1.0f, 1.0f };
	SetObstacle(s, s, m, 100.0f, 50.0f, MODEL_OBSTACLE);
	
}
//終了処理
void Obstacle::Uninit(void)
{
	for (int i = 0; i < MAX_OBSTACLE; i++)
	{
		// モデルの解放処理
		if (g_Obstacle[i].use)
		{
			UnloadModel(&g_Obstacle[i].model);
			g_Obstacle[i].use = FALSE;
		}
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
	
	p->use = FALSE;
	p->efSwitch = TRUE;
}

void Obstacle::SetObstacle(XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 scl, float durability, float size, char * model)
{
	for (int i = 0; i < MAX_OBSTACLE; i++) {
		if (g_Obstacle[i].use)continue;

		LoadModel(model, &g_Obstacle[i].model);
		g_Obstacle[i].use = TRUE;
		g_Obstacle[i].pos = pos;
		g_Obstacle[i].rot = rot;
		g_Obstacle[i].scl = scl;
		g_Obstacle[i].size = size;
		g_Obstacle[i].durability = durability;

	}
}

Obstacle * Obstacle::GetObstacle(void)
{
	return &g_Obstacle[0];
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
		DrawModel(&g_Obstacle[i].model);

	}

	// カリング設定を戻す
	SetCullingMode(CULL_MODE_BACK);

}
