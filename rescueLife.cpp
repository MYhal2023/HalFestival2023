#include "rescueLife.h"

static RescueLife g_RscLife[MAX_RESCUE];
static int remain;					//残り救助者数

void RescueLife::InitRescue(void)
{
	for (int i = 0; i < MAX_RESCUE; i++)
	{
		g_RscLife[i].use = FALSE;
		g_RscLife[i].load = FALSE;
		g_RscLife[i].rescue = FALSE;
	}
	remain = 0;
}

void RescueLife::UninitRescue(void)
{
	for (int i = 0; i < MAX_RESCUE; i++)
	{
		if (g_RscLife[i].load)
		{
			UnloadModel(&g_RscLife[i].model);
			g_RscLife[i].load = FALSE;
		}
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
		DrawModel(&g_RscLife[i].model);

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
void RescueLife::SetRemain(XMFLOAT3 pos, XMFLOAT3 rot, char* model)
{
	for (int i = 0; i < MAX_RESCUE; i++)
	{
		if (g_RscLife[i].load)continue;	//ロード済みならスルー

		LoadModel(model, &g_RscLife[i].model);
		g_RscLife[i].use = TRUE;
		g_RscLife[i].rescue = TRUE;
		g_RscLife[i].load = TRUE;
		g_RscLife[i].pos = pos;
		g_RscLife[i].rot = rot;
		remain++;
		break;
	}
}

RescueLife * RescueLife::GetRescueLife(void)
{
	return &g_RscLife[0];
}
