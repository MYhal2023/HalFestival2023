#include "playerArms.h"
#include "collision.h"
#include "obstacle.h"
#include "particle.h"
#include "camera.h"
#include "debugproc.h"
static Saw g_PlayerArm;
static XMFLOAT3 efPos[3];
static XMFLOAT3 efRot[3];
static BOOL efSwitch[3];
static float efTime[3];
void Saw::InitArm(void)
{
	g_PlayerArm.use = TRUE;
	g_PlayerArm.parent = pArm::GetArmParts();
	g_PlayerArm.pos = { 0.0f, 0.0f, 0.0f };
	g_PlayerArm.rot = { 0.0f, 0.0f, 0.0f };
	g_PlayerArm.scl = { 1.0f, 1.0f, 1.0f };
	g_PlayerArm.attack_damage = 10.0f;
	g_PlayerArm.atInterval = 5.0f;
	g_PlayerArm.atCount = 0.0f;
	g_PlayerArm.motionTime = 0.0f;
	g_PlayerArm.attack = FALSE;
	g_PlayerArm.ct_frame = 0.0f;
	for (int i = 0; i < 3; i++)
	{
		efSwitch[i] = FALSE;
	}

}

void Saw::Action(void)
{
	pArm* arm = GetArmParts();
	Obstacle* ob = Obstacle::GetObstacle();
	PLAYER *player = GetPlayer();
	CAMERA *camera = GetCamera();
	g_PlayerArm.atCount += 1.0f;
	g_PlayerArm.motionTime += 1.0f;
	CAMERA *cam = GetCamera();
	player[0].rot.y = cam->rot.y;
	g_PlayerArm.ct_frame += 1.0f;
	PrintDebugProc("アクションフレーム数:%f", g_PlayerArm.ct_frame);

	if (g_PlayerArm.ct_frame <= 5.0f ||(g_PlayerArm.ct_frame >= 20.0f && g_PlayerArm.ct_frame <= 60.0f) || g_PlayerArm.ct_frame >= 85.0f)return;

	if (g_PlayerArm.atCount >= g_PlayerArm.atInterval)
	{
		for (int k = 0; k < MAX_OBSTACLE; k++)
		{
			if (!ob[k].use)continue;

			XMFLOAT3 pos = player[0].pos;
			float dist = 30.0f;
			pos.x += sinf(player[0].rot.y) * dist;
			pos.z += cosf(player[0].rot.y) * dist;
			if (CollisionBC(pos, ob[k].pos, 15.0f, ob[k].size))
			{
				ob[k].durability -= g_PlayerArm.attack_damage;
				g_PlayerArm.atCount = 0.0f;
				SetEffect(pos, camera->rot.y, 10.0f);
				pArm::SetIntervalAt();
			}
		}
	}
	Effect();
}

void Saw::SetEffect(XMFLOAT3 pos, float rot, float time)
{
	for (int i = 0; i < 3; i++)
	{
		if (efSwitch[i])continue;

		efSwitch[i] = TRUE;
		efPos[i] = pos;
		efRot[i] = {0.0f, rot, 0.0f};
		efTime[i] = time;
	}
}

void Saw::Effect(void)
{
	for (int i = 0; i < 3; i++)
	{
		if (!efSwitch[i])continue;

		XMFLOAT3 move = { 2.0f, 2.0f, 2.0f, };			//移動基礎量。小さいほど動きがゆっくりになる
		float fAngle = (float)(rand() % 90) / 100.0f;	//加算する方向(数字が大きいほど、左右にばらつきが出る)
		float fLength = (float)(rand() % 10) - 3;	//xとz方向の加算速度
		move.x += sinf(fAngle) * fLength;
		move.y += (float)(rand() % 5);			//高さの移動加算量
		move.z += cosf(fAngle) * fLength;

		float angle = atan2f(move.y, move.x);
		XMFLOAT3 scl = { 0.025f, 0.4f, 0.025f };	//拡大率
		XMFLOAT3 rot = efRot[i];
		int nLife = rand() % 100 + 50;
		rot.z = angle - XM_PI * 0.5f;
		SetParticle(efPos[i], move, rot, scl, XMFLOAT4(1.0f, 0.3f, 0.3f, 1.0f), nLife, 40, P_T_box, TRUE);
		efTime[i] -= 1.0f;
		if (efTime[i] <= 0.0f)
			efSwitch[i] = FALSE;
	}
}

void Saw::Draw(void)
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

pArm* Saw::GetArm(void)
{
	return &g_PlayerArm;
}