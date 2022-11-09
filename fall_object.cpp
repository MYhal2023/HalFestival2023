#include "obstacle.h"
#include "player.h"
#include "bullet.h"
#include "collision.h"
static FallObject g_Obstacle[MAX_FALL_OBSTACLE];
static float fall_cool_time = 0.0f;

//初期化
void FallObject::Init(void)
{
	//LoadModel(MODEL_HEAD, &g_Parts[0].model);
	//LoadModel(MODEL_LEG, &g_Parts[1].model);
	for (int i = 0; i < MAX_FALL_OBSTACLE; i++)
	{
		g_Obstacle[i].use = FALSE;
		g_Obstacle[i].efSwitch = FALSE;
	}
	fall_cool_time = 0.0f;
}
//終了処理
void FallObject::Uninit(void)
{
	for (int i = 0; i < MAX_FALL_OBSTACLE; i++)
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
void FallObject::Update(void)
{
	fall_cool_time -= 1.0f;
	if (fall_cool_time <= 0.0f) {
		PLAYER *player = GetPlayer();
		XMFLOAT3 pos = player[0].pos;
		pos.x += (float)(rand() % -100) + 200.0f;
		pos.y = 300.0f;
		pos.z += (float)(rand() % -100) + 200.0f;
		XMFLOAT3 rot = { (float)(rand() % -157) + 314 / 157.0f ,(float)(rand() % -157) + 314 / 157.0f ,(float)(rand() % -157) + 314 / 157.0f };
		XMFLOAT3 scl = { 1.0f, 1.0f, 1.0f };

		SetObstacle(pos, rot, scl, 100.0f, 50.0f, MODEL_ROCK);
		fall_cool_time = (float)(rand() % 120) + 60.0f;
	}

	for (int i = 0; i < MAX_FALL_OBSTACLE; i++)
	{
		if (!g_Obstacle[i].use)continue;

		//落下処理
		if (g_Obstacle[i].pos.y > 0.0f)
			g_Obstacle[i].pos.y -= FALL_SPEED;

		Obstacle::Distract(&g_Obstacle[i]);	//壊れてるのかをチェック
	}
}

void FallObject::Effect(FallObject* p)
{
	//エフェクトスイッチがオンの奴だけエフェクトかける
	if (!p->efSwitch)return;

	//以下にエフェクトコードを記述。


	if (p->efFinish)
		p->efSwitch = FALSE;
}

void FallObject::Distract(FallObject* p)
{
	//耐久度0以下で消滅
	if (p->durability > 0)
		return;		
	
	p->use = FALSE;
	p->efSwitch = TRUE;
}

void FallObject::SetObstacle(XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 scl, float durability, float size, char * model)
{
	for (int i = 0; i < MAX_FALL_OBSTACLE; i++) {
		if (g_Obstacle[i].use)continue;

		LoadModel(model, &g_Obstacle[i].model);
		g_Obstacle[i].use = TRUE;
		g_Obstacle[i].pos = pos;
		g_Obstacle[i].rot = rot;
		g_Obstacle[i].scl = scl;
		g_Obstacle[i].size = size;
		g_Obstacle[i].durability = durability;
		break;
	}
}

FallObject * FallObject::GetObstacle(void)
{
	return &g_Obstacle[0];
}

void FallObject::Draw(void)
{
	// カリング無効
	SetCullingMode(CULL_MODE_NONE);

	XMMATRIX mtxScl, mtxRot, mtxTranslate, mtxWorld;

	for (int i = 0; i < MAX_FALL_OBSTACLE; i++)
	{
		if (g_Obstacle[i].use != TRUE || g_Obstacle[i].efFinish == TRUE)continue;
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
