#include "playerArms.h"
#include "bullet.h"
#include "camera.h"
#include "particle.h"
#include "sound.h"
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
		const float dist = 7.0f;
		float high = 17.0f;
		pos.x += sinf(player[0].rot.y + XM_PI * 0.30f) * dist;
		pos.y += high;
		pos.z += cosf(player[0].rot.y + XM_PI * 0.30f) * dist;

		pos2.x += sinf(player[0].rot.y - XM_PI * 0.30f) * dist;
		pos2.y += high;
		pos2.z += cosf(player[0].rot.y - XM_PI * 0.30f) * dist;
		player[0].rot.y = cam->rot.y;
		rot.y = cam->rot.y;
		rot.x = cam->rot.x;

		SetBullet(pos, rot, 8.0f, 50.0f, 40, Bullet_Braster);
		SetBullet(pos2, rot, 8.0f, 50.0f, 40, Bullet_Braster);

		pos.y += 8.0f;
		pos2.y += 8.0f;
		for (int i = 0; i < 10; i++) {
			CAMERA *cam = GetCamera();
			XMFLOAT3 move = { 0.0f, 0.0f, 0.0f, };
			float fAngle = (float)(rand() % 90)+30;	//加算する方向(数式結果の数字が大きいほど、左右にばらつきが出る)
			fAngle = XMConvertToRadians(fAngle);
			float fLength = (float)(rand() % 2 + 1) * 0.1f;	//xとz方向の加算速度この結果が大きいと素早く動く
			float fHigh = (float)(rand() % 2 + 1) * 0.1f;	//xとz方向の加算速度この結果が大きいと素早く動く
			move.x += cosf(fAngle) * fLength;
			move.y += sinf(fAngle) * fHigh;			//高さの移動加算量

			float angle = atan2f(move.y, move.x);
			XMFLOAT3 scl = { 0.2f, 0.2f, 0.2f };	//拡大率
			XMFLOAT3 rot = { 0.0f, cam->rot.y, 0.0f };	//回転率。いじる必要なし
			int nLife = rand() % 12 + 76;
			rot.z = angle - XM_PI * 0.5f;
			rot.y = cam->rot.y;
			if ((rot.y > XM_PI * 0.25f && rot.y < XM_PI * 0.75f) || (rot.y < XM_PI * -0.25f && rot.y > XM_PI * -0.75f)) {
				move.z = move.x;
				move.x = 0.0f;
			}
			SetParticle(pos, move, rot, scl, XMFLOAT4(0.5f, 0.5f, 1.0f, 1.0f), nLife, 76, 0, TRUE);
			SetParticle(pos2, move, rot, scl, XMFLOAT4(0.5f, 0.5f, 1.0f, 1.0f), nLife, 76, 0, TRUE);
			PlaySound(SOUND_LABEL_SE_Braster_hit);
		}


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