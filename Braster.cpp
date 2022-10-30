#include "playerArms.h"
static Braster g_PlayerArm;

void Braster::InitArm(void)
{
	LoadModel(MODEL_BRASTER, &g_PlayerArm.model);
	g_PlayerArm.use = TRUE;
	g_PlayerArm.parent = pArm::GetArmParts();
	g_PlayerArm.pos = { 0.0f, 0.0f, 0.0f };
	g_PlayerArm.rot = { 0.0f, 0.0f, 0.0f };
	g_PlayerArm.scl = { 1.0f, 1.0f, 1.0f };
}

void Braster::Action(void)
{

}

void Braster::Draw(void)
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

	mtxWorld = XMMatrixMultiply(mtxWorld, XMLoadFloat4x4(&g_PlayerArm.parent->mtxWorld));

	XMStoreFloat4x4(&g_PlayerArm.mtxWorld, mtxWorld);

	// ワールドマトリックスの設定
	SetWorldMatrix(&mtxWorld);

	// モデル描画
	DrawModel(&g_PlayerArm.model);
}

pArm* Braster::GetArm(void)
{
	return &g_PlayerArm;
}