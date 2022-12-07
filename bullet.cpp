//=============================================================================
//
// 弾発射処理 [bullet.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "renderer.h"
#include "shadow.h"
#include "bullet.h"
#include "sound.h"
#include "camera.h"
#include "collision.h"
#include "obstacle.h"
#include "player.h"
#include "particle.h"
#include "meshwall.h"
#include "fire.h"
#include "result.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_MAX			(1)				// テクスチャの数

#define	BULLET_WIDTH		(10.0f)			// 頂点サイズ
#define	BULLET_HEIGHT		(10.0f)			// 頂点サイズ

#define	BULLET_SPEED		(15.0f)			// 弾の移動スピード


//*****************************************************************************
// 構造体定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexBullet(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static DX11_MODEL			model[MAX_BULLET_VAR];		// モデル情報
static ID3D11Buffer					*g_VertexBuffer = NULL;	// 頂点バッファ
static ID3D11ShaderResourceView		*g_Texture[TEXTURE_MAX] = { NULL };	// テクスチャ情報

static BULLET						g_Bullet[MAX_BULLET];	// 弾ワーク
static int							g_TexNo;				// テクスチャ番号

static char *g_TextureName[TEXTURE_MAX] =
{
	"data/TEXTURE/bullet.png",
};

static BOOL							g_Load = FALSE;


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitBullet(void)
{
	MakeVertexBullet();

	// テクスチャ生成
	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		g_Texture[i] = NULL;
		D3DX11CreateShaderResourceViewFromFile(GetDevice(),
			g_TextureName[i],
			NULL,
			NULL,
			&g_Texture[i],
			NULL);
	}

	g_TexNo = 0;

	// 弾ワークの初期化
	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		ZeroMemory(&g_Bullet[nCntBullet].material, sizeof(g_Bullet[nCntBullet].material));
		g_Bullet[nCntBullet].material.Diffuse = { 1.0f, 1.0f, 1.0f, 1.0f };

		g_Bullet[nCntBullet].pos = { 0.0f, 0.0f, 0.0f };
		g_Bullet[nCntBullet].rot = { 0.0f, 0.0f, 0.0f };
		g_Bullet[nCntBullet].scl = { 1.0f, 1.0f, 1.0f };
		g_Bullet[nCntBullet].spd = BULLET_SPEED;
		g_Bullet[nCntBullet].fWidth = BULLET_WIDTH;
		g_Bullet[nCntBullet].fHeight = BULLET_HEIGHT;
		g_Bullet[nCntBullet].use = FALSE;
	}

	g_Load = TRUE;
	return S_OK;
}

//起動時の処理
void InitBulletBoot(void)
{
	LoadModel(MODEL_BULLET_Xgun, &model[Bullet_XGun]);
	LoadModel(MODEL_BULLET_Braster, &model[Bullet_Braster]);
	LoadModel(MODEL_BULLET_SAW, &model[Bullet_Saw]);
}
//=============================================================================
// 終了処理
//=============================================================================
void UninitBullet(void)
{
	if (g_Load == FALSE) return;

	for (int nCntTex = 0; nCntTex < TEXTURE_MAX; nCntTex++)
	{
		if (g_Texture[nCntTex] != NULL)
		{// テクスチャの解放
			g_Texture[nCntTex]->Release();
			g_Texture[nCntTex] = NULL;
		}
	}

	if (g_VertexBuffer != NULL)
	{// 頂点バッファの解放
		g_VertexBuffer->Release();
		g_VertexBuffer = NULL;
	}

	for (int i = 0; i < MAX_BULLET_VAR; i++)
	{
		// モデルの解放処理
		UnloadModel(&model[i]);
	}

	g_Load = FALSE;
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateBullet(void)
{

	for (int i = 0; i < MAX_BULLET; i++)
	{
		if (g_Bullet[i].use != TRUE)	//使われてないバレットは処理をスキップ
			continue;

		// 弾の移動処理
		g_Bullet[i].pos.x += sinf(g_Bullet[i].rot.y) * g_Bullet[i].spd;
		g_Bullet[i].pos.z += cosf(g_Bullet[i].rot.y) * g_Bullet[i].spd;
		g_Bullet[i].pos.y += sinf(g_Bullet[i].rot.x) * g_Bullet[i].spd * 2.0f;
		if (g_Bullet[i].model_num == Bullet_XGun)	//Xガンだけスローに
			g_Bullet[i].spd *= 0.95f;
		g_Bullet[i].life--;

		Obstacle* ob = Obstacle::GetObstacle();
		for (int k = 0; k < MAX_OBSTACLE; k++)
		{
			if (!ob[k].use)continue;

			if (ob[k].model_num != om_break_wall) {
				if (CollisionBC(ob[k].pos, g_Bullet[i].pos, ob[k].size, g_Bullet[i].size))
				{
					g_Bullet[i].life = 0;
					ob[k].durability -= g_Bullet[i].attack;
					g_Bullet[i].efSwitch = TRUE;
					break;
				}
			}
			else
			{
				if(MeshRayWallHitObj(g_Bullet[i].pos, 15.0f, &ob[k]))
				{
					g_Bullet[i].life = 0;
					ob[k].durability -= g_Bullet[i].attack;
					g_Bullet[i].efSwitch = TRUE;
					break;
				}
			}
		}
		//消化できる
		if (g_Bullet[i].model_num == Bullet_Braster) {
			FireEffect* fe = GetFireEffect();
			for (int k = 0; k < MAX_FIRE_EFFECT; k++)
			{
				if (!fe[k].use)continue;
				if (CollisionBC(fe[k].pos, g_Bullet[i].pos, 40.0f, g_Bullet[i].size))
				{
					g_Bullet[i].life = 0;
					fe[k].use = FALSE;
					Reward* re = GetReward();
					re->beatNum++;
					g_Bullet[i].efSwitch = TRUE;
					break;
				}
			}
		}
		//弾を消す処理
		if ((g_Bullet[i].life <= 0) || MeshWallHitObj(g_Bullet[i].pos, 5.0f))
		{
			g_Bullet[i].use = FALSE;
			g_Bullet[i].efSwitch = TRUE;
		}

	}

	for (int i = 0; i < MAX_BULLET; i++)
	{
		if (!g_Bullet[i].efSwitch)continue;


		//エフェクトコード記述
		switch (g_Bullet[i].model_num)
		{
		case Bullet_XGun:
			if (g_Bullet[i].p_time == 5)PlaySound(SOUND_LABEL_SE_xgun_impact);
			XgunParticle(g_Bullet[i].pos);
			break;
		case Bullet_Braster:
			if (g_Bullet[i].p_time == 5)PlaySound(SOUND_LABEL_SE_Braster_hits);
			BrasterParticle(g_Bullet[i].pos);
			break;

		}

		g_Bullet[i].p_time--;

		if (g_Bullet[i].p_time <= 0)
			g_Bullet[i].efSwitch = FALSE;
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawBullet(void)
{
	// ライティングを無効
	SetLightEnable(FALSE);

	// 加算合成に設定
	SetBlendState(BLEND_MODE_ADD);

	XMMATRIX mtxScl, mtxTranslate, mtxWorld, mtxView;
	CAMERA *cam = GetCamera();

	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// プリミティブトポロジ設定
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	for (int i = 0; i < MAX_BULLET; i++)
	{
		if (g_Bullet[i].use)
		{
			// ワールドマトリックスの初期化
			mtxWorld = XMMatrixIdentity();

			// ビューマトリックスを取得
			mtxView = XMLoadFloat4x4(&cam->mtxView);
			int inverse = 3;	//転置する正規行列の行列数
			for (int i = 0; i < inverse; i++)
			{
				for (int k = 0; k < inverse; k++)
				{
					mtxWorld.r[i].m128_f32[k] = mtxView.r[k].m128_f32[i];
				}
			}

			// スケールを反映
			mtxScl = XMMatrixScaling(g_Bullet[i].scl.x, g_Bullet[i].scl.y, g_Bullet[i].scl.z);
			mtxWorld = XMMatrixMultiply(mtxWorld, mtxScl);


			// 移動を反映
			mtxTranslate = XMMatrixTranslation(g_Bullet[i].pos.x, g_Bullet[i].pos.y, g_Bullet[i].pos.z);
			mtxWorld = XMMatrixMultiply(mtxWorld, mtxTranslate);

			// ワールドマトリックスの設定
			SetWorldMatrix(&mtxWorld);

			XMStoreFloat4x4(&g_Bullet[i].mtxWorld, mtxWorld);


			// マテリアル設定
			SetMaterial(g_Bullet[i].material);

			// テクスチャ設定
			GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[g_TexNo]);

			// ポリゴンの描画
			GetDeviceContext()->Draw(4, 0);
		}
	}

	// 通常ブレンドに戻す
	SetBlendState(BLEND_MODE_ALPHABLEND);

	// ライティングを有効に
	SetLightEnable(TRUE);

}

//3Dモデルの弾の描画
void DrawBulletModel(void)
{
	// カリング無効
	SetCullingMode(CULL_MODE_NONE);

	XMMATRIX mtxScl, mtxRot, mtxTranslate, mtxWorld;

	// パーツの階層アニメーション
	for (int k = 0; k < MAX_BULLET; k++)
	{
		if (!g_Bullet[k].use)continue;

		// ワールドマトリックスの初期化
		mtxWorld = XMMatrixIdentity();

		// スケールを反映
		mtxScl = XMMatrixScaling(g_Bullet[k].scl.x, g_Bullet[k].scl.y, g_Bullet[k].scl.z);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxScl);

		// 回転を反映
		mtxRot = XMMatrixRotationRollPitchYaw(g_Bullet[k].rot.x, g_Bullet[k].rot.y, g_Bullet[k].rot.z);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxRot);

		// 移動を反映
		mtxTranslate = XMMatrixTranslation(g_Bullet[k].pos.x, g_Bullet[k].pos.y, g_Bullet[k].pos.z);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxTranslate);


		XMStoreFloat4x4(&g_Bullet[k].mtxWorld, mtxWorld);

		// ワールドマトリックスの設定
		SetWorldMatrix(&mtxWorld);

		if (g_Bullet[k].model_num == 99)continue;

		DrawModel(&model[g_Bullet[k].model_num]);
	}

	// カリング設定を戻す
	SetCullingMode(CULL_MODE_BACK);

}
//=============================================================================
// 頂点情報の作成
//=============================================================================
HRESULT MakeVertexBullet(void)
{
	// 頂点バッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	GetDevice()->CreateBuffer(&bd, NULL, &g_VertexBuffer);

	// 頂点バッファに値をセットする
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

	float fWidth = BULLET_WIDTH;
	float fHeight = BULLET_HEIGHT;

	// 頂点座標の設定
	vertex[0].Position = XMFLOAT3(-fWidth / 2.0f, fHeight, 0.0f);
	vertex[1].Position = XMFLOAT3(fWidth / 2.0f, fHeight, 0.0f);
	vertex[2].Position = XMFLOAT3(-fWidth / 2.0f, 0.0f, 0.0f);
	vertex[3].Position = XMFLOAT3(fWidth / 2.0f, 0.0f, 0.0f);

	// 拡散光の設定
	vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

	// テクスチャ座標の設定
	vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);
	vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);
	vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);
	vertex[3].TexCoord = XMFLOAT2(1.0f, 1.0f);

	GetDeviceContext()->Unmap(g_VertexBuffer, 0);

	return S_OK;
}


//=============================================================================
// 弾の取得
//=============================================================================
BULLET *GetBullet(void)
{
	return &(g_Bullet[0]);
}

void SetBullet(XMFLOAT3 pos, XMFLOAT3 rot, float spd, float attack, int life, int model_num)
{
	for (int i = 0; i < MAX_BULLET; i++)
	{
		if (g_Bullet[i].use || g_Bullet[i].efSwitch)continue;	//未使用配列へアクセス

		g_Bullet[i].use = TRUE;
		g_Bullet[i].efSwitch = FALSE;
		g_Bullet[i].pos = pos;
		g_Bullet[i].rot = rot;
		g_Bullet[i].spd = spd;
		g_Bullet[i].attack = attack;
		g_Bullet[i].life = life;
		g_Bullet[i].model_num = model_num;
		switch (model_num)
		{
		case Bullet_XGun:
			g_Bullet[i].size = 5.0f;
			g_Bullet[i].p_time = 5;
			break;
		case Bullet_Braster:
			g_Bullet[i].size = 5.0f;
			g_Bullet[i].p_time = 5;
			break;
		case Bullet_Saw:
			g_Bullet[i].size = 5.0f;
			break;

		}
		break;
	}
}

void XgunParticle(XMFLOAT3 pos)
{
	for (int i = 0; i < 3; i++) {
		CAMERA *cam = GetCamera();
		XMFLOAT3 move = { 0.0f, 0.0f, 0.0f, };
		float fAngle = (float)(rand() % 360);	//加算する方向(数式結果の数字が大きいほど、左右にばらつきが出る)
		fAngle = XMConvertToRadians(fAngle);
		float fLength = (float)(rand() % 3 + 1) * 0.5f;	//xとz方向の加算速度この結果が大きいと素早く動く
		float fHigh = (float)(rand() % 3 + 1) * 0.5f;	//xとz方向の加算速度この結果が大きいと素早く動く
		move.x += cosf(fAngle) * fLength;
		move.y += sinf(fAngle) * fHigh;			//高さの移動加算量
		float angle = atan2f(move.y, move.x);
		XMFLOAT3 scl = { 0.025f + 0.05f, 0.5f, 0.025f + 0.05f };	//拡大率
		XMFLOAT3 rot = { 0.0f, cam->rot.y, 0.0f };	//回転率。いじる必要なし
		int nLife = rand() % 40 + 57;
		rot.z = angle - XM_PI * 0.0f;
		rot.y = cam->rot.y;
		if ((rot.y > XM_PI * 0.25f && rot.y < XM_PI * 0.75f) || (rot.y < XM_PI * -0.25f && rot.y > XM_PI * -0.75f)) {
			move.z = move.x;
			move.x = 0.0f;
		}
		SetParticle(pos, move, rot, scl, XMFLOAT4(0.4f, 0.4f, 0.9f, 1.0f), nLife, 57, 0, TRUE);
	}

}
void BrasterParticle(XMFLOAT3 pos)
{
	for (int i = 0; i < 3; i++) {
		CAMERA *cam = GetCamera();
		XMFLOAT3 move = { 0.0f, 0.0f, 0.0f, };
		float fAngle = (float)(rand() % 180);	//加算する方向(数式結果の数字が大きいほど、左右にばらつきが出る)
		fAngle = XMConvertToRadians(fAngle);
		float fLength = (float)(rand() % 40 + 1) * 0.1f;	//xとz方向の加算速度この結果が大きいと素早く動く
		float fHigh = (float)(rand() % 20 + 1) * 0.1f;	//xとz方向の加算速度この結果が大きいと素早く動く
		move.x += cosf(fAngle) * fLength;
		move.y += sinf(fAngle) * fHigh;			//高さの移動加算量

		float angle = atan2f(move.y, move.x);
		XMFLOAT3 scl = { 0.025f + 0.25f, 0.4f, 0.025f + 0.25f };	//拡大率
		XMFLOAT3 rot = { 0.0f, cam->rot.y, 0.0f };	//回転率。いじる必要なし
		int nLife = rand() % 30 + 2;
		rot.z = angle - XM_PI * 0.5f;
		rot.y = cam->rot.y;
		if ((rot.y > XM_PI * 0.25f && rot.y < XM_PI * 0.75f) || (rot.y < XM_PI * -0.25f && rot.y > XM_PI * -0.75f)) {
			move.z = move.x;
			move.x = 0.0f;
		}
		SetParticle(pos, move, rot, scl, XMFLOAT4(0.5f, 0.5f, 1.0f, 1.0f), nLife, 2, 0, TRUE);
	}

}
