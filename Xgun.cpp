#include "playerArms.h"
static Xgun g_PlayerArm;

void Xgun::InitArm(void)
{
	LoadModel(MODEL_XGUN, &g_PlayerArm.model);
	g_PlayerArm.use = TRUE;
}

void Xgun::Action(void)
{

}

void Xgun::Draw(void)
{
	// カリング無効
	SetCullingMode(CULL_MODE_NONE);

	XMMATRIX mtxScl, mtxRot, mtxTranslate, mtxWorld;

	if (g_PlayerArm.use != TRUE)return;
	// ワールドマトリックスの初期化
	mtxWorld = XMMatrixIdentity();

	// スケールを反映
	mtxScl = XMMatrixScaling(g_PlayerArm.scl.x, g_PlayerArm.scl.y, g_PlayerArm.scl.z);
	mtxWorld = XMMatrixMultiply(mtxWorld, mtxScl);

	// 回転を反映
	mtxRot = XMMatrixRotationRollPitchYaw(g_PlayerArm.rot.x, g_PlayerArm.rot.y, g_PlayerArm.rot.z);
	mtxWorld = XMMatrixMultiply(mtxWorld, mtxRot);

	// 移動を反映
	mtxTranslate = XMMatrixTranslation(g_PlayerArm.pos.x, g_PlayerArm.pos.y, g_PlayerArm.pos.z);
	mtxWorld = XMMatrixMultiply(mtxWorld, mtxTranslate);

	// ワールドマトリックスの設定
	SetWorldMatrix(&mtxWorld);

	XMStoreFloat4x4(&g_PlayerArm.mtxWorld, mtxWorld);

	// モデル描画
	DrawModel(&g_PlayerArm.model);
}


pArm* Xgun::GetArm(void)
{
	return &g_PlayerArm;
}