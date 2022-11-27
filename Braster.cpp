#include "playerArms.h"
#include "bullet.h"
#include "camera.h"
static Braster g_PlayerArm;

void Braster::InitArm(void)
{
	g_PlayerArm.attack = FALSE;
}

void Braster::Action(void)
{
	if (!g_PlayerArm.attack)
	{
		PLAYER *player = GetPlayer();
		CAMERA *cam = GetCamera();
		XMFLOAT3 pos = player[0].pos;
		XMFLOAT3 pos2 = player[0].pos;
		XMFLOAT3 rot = player[0].rot;
		const float dist = 5.0f;
		float high = 10.0f;
		pos.x += sinf(player[0].rot.y + XM_PI * 0.20f) * dist;
		pos.y += high;
		pos.z += cosf(player[0].rot.y + XM_PI * 0.20f) * dist;

		pos2.x += sinf(player[0].rot.y - XM_PI * 0.20f) * dist;
		pos2.y += high;
		pos2.z += cosf(player[0].rot.y - XM_PI * 0.20f) * dist;
		player[0].rot.y = cam->rot.y;
		rot.y = cam->rot.y;
		rot.x = cam->rot.x;

		SetBullet(pos, rot, 8.0f, 50.0f, 40, Bullet_Braster);
		SetBullet(pos2, rot, 8.0f, 50.0f, 40, Bullet_Braster);

		g_PlayerArm.attack = TRUE;
	}

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