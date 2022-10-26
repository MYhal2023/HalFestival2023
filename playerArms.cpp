#include "playerArms.h"
#define MAX_ARM (2)
#define MAX_ARM_PARTS (10)
static pArm g_PlayerArm[3];
static pArm g_ArmParts[MAX_ARM_PARTS];

void pArm::Draw(void)
{
	// カリング無効
	SetCullingMode(CULL_MODE_NONE);

	XMMATRIX mtxScl, mtxRot, mtxTranslate, mtxWorld;

	for (int i = 0; i < MAX_ARM; i++)
	{
		if (g_PlayerArm[i].use != TRUE)continue;
		// ワールドマトリックスの初期化
		mtxWorld = XMMatrixIdentity();

		// スケールを反映
		mtxScl = XMMatrixScaling(g_PlayerArm[i].scl.x, g_PlayerArm[i].scl.y, g_PlayerArm[i].scl.z);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxScl);

		// 回転を反映
		mtxRot = XMMatrixRotationRollPitchYaw(g_PlayerArm[i].rot.x, g_PlayerArm[i].rot.y, g_PlayerArm[i].rot.z);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxRot);

		// 移動を反映
		mtxTranslate = XMMatrixTranslation(g_PlayerArm[i].pos.x, g_PlayerArm[i].pos.y, g_PlayerArm[i].pos.z);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxTranslate);

		// ワールドマトリックスの設定
		SetWorldMatrix(&mtxWorld);

		XMStoreFloat4x4(&g_PlayerArm[i].mtxWorld, mtxWorld);

		// モデル描画
		DrawModel(&g_PlayerArm[i].model);

		if (g_PlayerArm[i].partsNum == 0)continue;

		// パーツの階層アニメーション
		for (int k = 0; k < g_PlayerArm[i].partsNum; k++)
		{
			// ワールドマトリックスの初期化
			mtxWorld = XMMatrixIdentity();

			// スケールを反映
			mtxScl = XMMatrixScaling(g_ArmParts[k].scl.x, g_ArmParts[k].scl.y, g_ArmParts[k].scl.z);
			mtxWorld = XMMatrixMultiply(mtxWorld, mtxScl);

			// 回転を反映
			mtxRot = XMMatrixRotationRollPitchYaw(g_ArmParts[k].rot.x, g_ArmParts[k].rot.y, g_ArmParts[k].rot.z);
			mtxWorld = XMMatrixMultiply(mtxWorld, mtxRot);

			// 移動を反映
			mtxTranslate = XMMatrixTranslation(g_ArmParts[k].pos.x, g_ArmParts[k].pos.y, g_ArmParts[k].pos.z);
			mtxWorld = XMMatrixMultiply(mtxWorld, mtxTranslate);

			if (g_ArmParts[k].parent != NULL)	// 子供だったら親と結合する
			{
				mtxWorld = XMMatrixMultiply(mtxWorld, XMLoadFloat4x4(&g_ArmParts[k].parent->mtxWorld));
				// ↑
				// g_PlayerArm[i].mtxWorldを指している
			}

			XMStoreFloat4x4(&g_ArmParts[k].mtxWorld, mtxWorld);

			// 使われているなら処理する。ここまで処理している理由は他のパーツがこのパーツを参照している可能性があるから。
			if (g_ArmParts[k].use == FALSE) continue;

			// ワールドマトリックスの設定
			SetWorldMatrix(&mtxWorld);

			// モデル描画
			DrawModel(&g_ArmParts[k].model);
		}
	}

	// カリング設定を戻す
	SetCullingMode(CULL_MODE_BACK);

}

//使うアームの親子情報を一括でセット
void pArm::SetArmParent(PLAYER *p)
{
	for (int i = 0; i < MAX_ARM; i++)
	{
		for (int k = 0; k < g_PlayerArm[i].partsNum; k++)
		{
			if (i == 0) {
				g_PlayerArm[i].parent = nullptr;
				g_PlayerArm[i].player = p;
				continue;
			}	//先頭をプレイヤーの親とし、これに順番に紐づけていく
			g_PlayerArm[i].parent = &g_PlayerArm[i - 1];
		}
	}
}

void pArm::ChangeArm(void)
{
}

