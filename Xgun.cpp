#include "playerArms.h"
#include "bullet.h"
static Xgun g_PlayerArm[2];

void Xgun::InitArm(void)
{
	for (int i = 0; i < 2; i++) {
		LoadModel(MODEL_XGUN, &g_PlayerArm[i].model);
		g_PlayerArm[i].use = TRUE;
		g_PlayerArm[i].parent = nullptr;
		g_PlayerArm[i].pos = { 0.0f, 0.0f, 0.0f };
		g_PlayerArm[i].rot = { 0.0f, 0.0f, 0.0f };
		g_PlayerArm[i].scl = { 1.0f, 1.0f, 1.0f };
	}
	pArm* p = pArm::GetArmParts();
	Xgun::SetParent(&p[0], &p[MAX_ARM_PARTS * 2 - 1]);	//右腕のセット
}

void Xgun::Action(void)
{
	PLAYER *player = GetPlayer();
	XMFLOAT3 pos = player[0].pos;
	XMFLOAT3 pos2 = player[0].pos;
	const float dist = 10.0f;
	const float high = 10.0f;
	pos.x += sinf(player[0].rot.y + XM_PI * 0.20f) * dist;
	pos.y += high;
	pos.z += cosf(player[0].rot.y + XM_PI * 0.20f) * dist;

	pos2.x += sinf(player[0].rot.y - XM_PI * 0.20f) * dist;
	pos2.y += high;
	pos2.z += cosf(player[0].rot.y - XM_PI * 0.20f) * dist;
	SetBullet(pos, player[0].rot, 10.0f, 50.0f, 60, Bullet_XGun);
	SetBullet(pos2, player[0].rot, 10.0f, 50.0f, 60, Bullet_XGun);
}

void Xgun::Draw(void)
{
	// カリング無効
	SetCullingMode(CULL_MODE_NONE);

	XMMATRIX mtxScl, mtxRot, mtxTranslate, mtxWorld;
	for (int i = 0; i < 2; i++) {
		if (g_PlayerArm[i].use != TRUE)return;
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

		mtxWorld = XMMatrixMultiply(mtxWorld, XMLoadFloat4x4(&g_PlayerArm[i].parent->mtxWorld));
		XMStoreFloat4x4(&g_PlayerArm[i].mtxWorld, mtxWorld);

		// ワールドマトリックスの設定
		SetWorldMatrix(&mtxWorld);

		// モデル描画
		DrawModel(&g_PlayerArm[i].model);

		// カリング設定を戻す
		SetCullingMode(CULL_MODE_BACK);
	}
}


pArm* Xgun::GetArm(void)
{
	return &g_PlayerArm[0];
}

void Xgun::SetParent(pArm * p1, pArm * p2)
{
	g_PlayerArm[0].parent = p1;
	g_PlayerArm[1].parent = p2;
}

