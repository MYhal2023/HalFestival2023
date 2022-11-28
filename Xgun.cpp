#include "playerArms.h"
#include "bullet.h"
#include "camera.h"

#define INTERVAL (10.0f)
static Xgun g_PlayerArm;

void Xgun::InitArm(void)
{
	g_PlayerArm.attack = FALSE;
	g_PlayerArm.atCount = INTERVAL;
}

void Xgun::Action(void)
{
	if (!g_PlayerArm.attack && g_PlayerArm.atCount > 0.0f)
	g_PlayerArm.atCount -= 1.0f;

	if (!g_PlayerArm.attack && g_PlayerArm.atCount <= 0.0f)
	{
		PLAYER *player = GetPlayer();
		CAMERA *cam = GetCamera();
		XMFLOAT3 pos = player[0].pos;
		XMFLOAT3 pos2 = player[0].pos;
		XMFLOAT3 rot = player[0].rot;
		const float dist = 5.0f;
		float high = 0.0f;
		pos.x += sinf(player[0].rot.y + XM_PI * 0.40f) * dist;
		pos.y += high;
		pos.z += cosf(player[0].rot.y + XM_PI * 0.40f) * dist;

		pos2.x += sinf(player[0].rot.y - XM_PI * 0.40f) * dist;
		pos2.y += high;
		pos2.z += cosf(player[0].rot.y - XM_PI * 0.40f) * dist;
		player[0].rot.y = cam->rot.y;
		rot.y = cam->rot.y;
		rot.x = cam->rot.x;
		SetBullet(pos, rot, 10.0f, 50.0f, 60, Bullet_XGun);
		SetBullet(pos2, rot, 10.0f, 50.0f, 60, Bullet_XGun);

		g_PlayerArm.attack = TRUE;
		g_PlayerArm.atCount = INTERVAL;
	}

}
//void Xgun::Draw(void)
//{
//	// カリング無効
//	SetCullingMode(CULL_MODE_NONE);
//
//	XMMATRIX mtxScl, mtxRot, mtxTranslate, mtxWorld;
//	for (int i = 0; i < 2; i++) {
//		if (g_PlayerArm[i].use != TRUE)return;
//		// ワールドマトリックスの初期化
//		mtxWorld = XMMatrixIdentity();
//
//		// スケールを反映
//		mtxScl = XMMatrixScaling(g_PlayerArm[i].scl.x, g_PlayerArm[i].scl.y, g_PlayerArm[i].scl.z);
//		mtxWorld = XMMatrixMultiply(mtxWorld, mtxScl);
//
//		// 回転を反映
//		mtxRot = XMMatrixRotationRollPitchYaw(g_PlayerArm[i].rot.x, g_PlayerArm[i].rot.y, g_PlayerArm[i].rot.z);
//		mtxWorld = XMMatrixMultiply(mtxWorld, mtxRot);
//
//		// 移動を反映
//		mtxTranslate = XMMatrixTranslation(g_PlayerArm[i].pos.x, g_PlayerArm[i].pos.y, g_PlayerArm[i].pos.z);
//		mtxWorld = XMMatrixMultiply(mtxWorld, mtxTranslate);
//
//		mtxWorld = XMMatrixMultiply(mtxWorld, XMLoadFloat4x4(&g_PlayerArm[i].parent->mtxWorld));
//		XMStoreFloat4x4(&g_PlayerArm[i].mtxWorld, mtxWorld);
//
//		// ワールドマトリックスの設定
//		SetWorldMatrix(&mtxWorld);
//
//		// モデル描画
//		DrawModel(&g_PlayerArm[i].model);
//
//		// カリング設定を戻す
//		SetCullingMode(CULL_MODE_BACK);
//	}
//}


pArm* Xgun::GetArm(void)
{
	return &g_PlayerArm;
}