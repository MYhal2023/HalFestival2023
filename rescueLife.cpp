#include "rescueLife.h"

static RescueLife g_RscLife[MAX_RESCUE];
static 	DX11_MODEL	model[MODEL_VAR];		// モデル情報
static int remain;					//残り救助者数

void RescueLife::InitRescue(void)
{
	for (int i = 0; i < MAX_RESCUE; i++)
	{
		g_RscLife[i].use = FALSE;
		g_RscLife[i].load = FALSE;
		g_RscLife[i].rescue = FALSE;
		g_RscLife[i].pos = {0.0f, 0.0f, 0.0f};
	}
	remain = 0;
}

void RescueLife::InitBootRescue(void)
{
	for (int i = 0; i < MODEL_VAR; i++)
	{
		LoadModel(MODEL_RESCUE001, &model[i]);
	}
}

void RescueLife::UninitRescue(void)
{
	for (int i = 0; i < MODEL_VAR; i++)
	{
		UnloadModel(&model[i]);
	}
}

void RescueLife::DrawRescue(void)
{
	// カリング無効
	SetCullingMode(CULL_MODE_NONE);

	XMMATRIX mtxScl, mtxRot, mtxTranslate, mtxWorld;

	for (int i = 0; i < MAX_RESCUE; i++)
	{
		if (g_RscLife[i].use != TRUE)continue;
		// ワールドマトリックスの初期化
		mtxWorld = XMMatrixIdentity();

		// スケールを反映
		mtxScl = XMMatrixScaling(g_RscLife[i].scl.x, g_RscLife[i].scl.y, g_RscLife[i].scl.z);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxScl);

		// 回転を反映
		mtxRot = XMMatrixRotationRollPitchYaw(g_RscLife[i].rot.x, g_RscLife[i].rot.y, g_RscLife[i].rot.z);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxRot);

		// 移動を反映
		mtxTranslate = XMMatrixTranslation(g_RscLife[i].pos.x, g_RscLife[i].pos.y, g_RscLife[i].pos.z);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxTranslate);

		// ワールドマトリックスの設定
		SetWorldMatrix(&mtxWorld);

		XMStoreFloat4x4(&g_RscLife[i].mtxWorld, mtxWorld);

		// モデル描画
		DrawModel(&model[g_RscLife[i].model_num]);

	}

	// カリング設定を戻す
	SetCullingMode(CULL_MODE_BACK);
}

int GetRemain(void)
{
	return remain;
}

BOOL RescueLife::GetRescue(int i)
{
	return g_RscLife[i].rescue;
}

//救助者セット。先頭配列から使用していく
void RescueLife::SetRemain(XMFLOAT3 pos, XMFLOAT3 rot, int model)
{
	for (int i = 0; i < MAX_RESCUE; i++)
	{
		if (g_RscLife[i].load)continue;	//ロード済みならスルー

		g_RscLife[i].model_num = model;
		g_RscLife[i].use = TRUE;
		g_RscLife[i].rescue = FALSE;
		g_RscLife[i].load = TRUE;
		g_RscLife[i].pos = pos;
		g_RscLife[i].rot = rot;
		g_RscLife[i].scl = {1.0f, 1.0f, 1.0f};
		remain++;
		break;
	}
}

RescueLife * RescueLife::GetRescueLife(void)
{
	return &g_RscLife[0];
}

int RescueLife::GetRescueRemainLife(void)
{
	int ans = 0;
	for (int i = 0; i < MAX_RESCUE; i++)
	{
		if (!g_RscLife[i].rescue && g_RscLife[i].load)
			ans++;
	}
	return ans;
}

