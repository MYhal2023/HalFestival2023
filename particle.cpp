//=============================================================================
//
// パーティクル処理 [particle.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "renderer.h"
#include "input.h"
#include "camera.h"
#include "model.h"
#include "shadow.h"
#include "particle.h"
#include "player.h"
#include "math.h"
#include <iostream>
#include <fstream>

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_MAX			(2)			// テクスチャの数

#define	PARTICLE_SIZE_X		(40.0f)		// 頂点サイズ
#define	PARTICLE_SIZE_Y		(40.0f)		// 頂点サイズ
#define	VALUE_MOVE_PARTICLE	(5.0f)		// 移動速度

#define	MAX_PARTICLE		(512)		// パーティクル最大数
#define	MAX_PARTICLE_POINTER		(10)		// パーティクル最大数

#define	DISP_SHADOW						// 影の表示
//#undef DISP_SHADOW

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{
	XMFLOAT4		col;			//保存用マテリアルカラー
	XMFLOAT3		pos;			// 位置
	XMFLOAT3		rot;			// 回転
	XMFLOAT3		scale;			// スケール
	XMFLOAT3		move;			// 移動量
	MATERIAL		material;		// マテリアル
	float			fSizeX;			// 幅
	float			fSizeY;			// 高さ
	int				nLife;			// 寿命
	int				nDecay;			// 減衰タイミング(nDecay <= nLife)
	int				g_TexNo;
	BOOL			bUse;			// 使用しているかどうか

} PARTICLE;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexParticle(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static ID3D11Buffer					*g_VertexBuffer = NULL;		// 頂点バッファ

static ID3D11ShaderResourceView		*g_Texture[TEXTURE_MAX] = { NULL };	// テクスチャ情報
static int							g_TexNo;					// テクスチャ番号

static PARTICLE					g_aParticle[MAX_PARTICLE];		// パーティクルワーク
static PARTICLE*				g_pParticle[MAX_PARTICLE_POINTER];				//パーティクルワークのポインター
static XMFLOAT3					g_posBase;						// ビルボード発生位置
static float					g_fWidthBase = 5.0f;			// 基準の幅
static float					g_fHeightBase = 10.0f;			// 基準の高さ
static float					g_roty = 0.0f;					// 移動方向
static float					g_spd = 0.0f;					// 移動スピード
using namespace std;
static ofstream fout;
static int rand_angle = 1;
static int rand_length = 1;
static int rand_high = 1;
static int tex_num = 0;
static float scale = 0.0f;
static int for_p_num = 1;
static int p_decay = 40;
static int p_Life = 120;
static BOOL blend_mode = FALSE;
static char *g_TextureName[TEXTURE_MAX] =
{
	"data/TEXTURE/effect000.jpg",
	"data/TEXTURE/var.png",
};

static BOOL						g_Load = FALSE;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitParticle(void)
{
	// 頂点情報の作成
	MakeVertexParticle();

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

	// パーティクルワークの初期化
	for(int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		g_aParticle[nCntParticle].pos = XMFLOAT3(0.0f, 0.0f, 0.0f);
		g_aParticle[nCntParticle].rot = XMFLOAT3(0.0f, 0.0f, 0.0f);
		g_aParticle[nCntParticle].scale = XMFLOAT3(1.0f, 1.0f, 1.0f);
		g_aParticle[nCntParticle].move = XMFLOAT3(1.0f, 1.0f, 1.0f);

		ZeroMemory(&g_aParticle[nCntParticle].material, sizeof(g_aParticle[nCntParticle].material));
		g_aParticle[nCntParticle].material.Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

		g_aParticle[nCntParticle].fSizeX = PARTICLE_SIZE_X;
		g_aParticle[nCntParticle].fSizeY = PARTICLE_SIZE_Y;
		g_aParticle[nCntParticle].nLife = 0;
		g_aParticle[nCntParticle].bUse = FALSE;
	}

	for (int i = 0; i < MAX_PARTICLE_POINTER; i++)
	{
		g_pParticle[i] = nullptr;
	}

	g_posBase = XMFLOAT3(0.0f, 0.0f, 0.0f);
	g_roty = 0.0f;
	g_spd = 0.0f;

	g_Load = TRUE;
	fout.open("particle_data.txt");

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitParticle(void)
{
	if (g_Load == FALSE) return;

	//テクスチャの解放
	for (int nCntTex = 0; nCntTex < TEXTURE_MAX; nCntTex++)
	{
		if (g_Texture[nCntTex] != NULL)
		{
			g_Texture[nCntTex]->Release();
			g_Texture[nCntTex] = NULL;
		}
	}

	// 頂点バッファの解放
	if (g_VertexBuffer != NULL)
	{
		g_VertexBuffer->Release();
		g_VertexBuffer = NULL;
	}

	g_Load = FALSE;
	fout.close();

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateParticle(void)
{
	//PLAYER *pPlayer = GetPlayer();
	//g_posBase = pPlayer->pos;

	{
		for (int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
		{
			if (g_aParticle[nCntParticle].bUse)
			{// 使用中
				g_aParticle[nCntParticle].pos.x += g_aParticle[nCntParticle].move.x;
				g_aParticle[nCntParticle].pos.z += g_aParticle[nCntParticle].move.z;

				g_aParticle[nCntParticle].pos.y += g_aParticle[nCntParticle].move.y;

				g_aParticle[nCntParticle].move.x += (g_aParticle[nCntParticle].move.x) * 0.015f;
				g_aParticle[nCntParticle].move.y += (g_aParticle[nCntParticle].move.y) * 0.015f;
				g_aParticle[nCntParticle].move.z += (g_aParticle[nCntParticle].move.z) * 0.015f;

				g_aParticle[nCntParticle].nLife--;
				if (g_aParticle[nCntParticle].nLife <= 0)
				{
					g_aParticle[nCntParticle].bUse = FALSE;
				}
				else
				{
					//加算合成なので、透明になっていくように見える
					if (g_aParticle[nCntParticle].nLife <= g_aParticle[nCntParticle].nDecay)
					{
						g_aParticle[nCntParticle].material.Diffuse.x = g_aParticle[nCntParticle].col.x - (float)(80 - g_aParticle[nCntParticle].nLife) / 80 * g_aParticle[nCntParticle].col.x;
						g_aParticle[nCntParticle].material.Diffuse.y = g_aParticle[nCntParticle].col.y - (float)(80 - g_aParticle[nCntParticle].nLife) / 80 * g_aParticle[nCntParticle].col.y;
						g_aParticle[nCntParticle].material.Diffuse.z = g_aParticle[nCntParticle].col.z - (float)(80 - g_aParticle[nCntParticle].nLife) / 80 * g_aParticle[nCntParticle].col.z;
					}

					//if(g_aParticle[nCntParticle].nLife <= 20)
					//{
					//	// α値設定
					//	g_aParticle[nCntParticle].material.Diffuse.w -= 0.05f;
					//	if(g_aParticle[nCntParticle].material.Diffuse.w < 0.0f)
					//	{
					//		g_aParticle[nCntParticle].material.Diffuse.w = 0.0f;
					//	}
					//}
				}
			}
		}

		//// パーティクル発生
		//{
		//	XMFLOAT3 pos;
		//	XMFLOAT3 move;
		//	float fAngle, fLength;
		//	int nLife;
		//	float fSize;

		//	pos = g_posBase;

		//	fAngle = (float)(rand() % 628 - 314) / 100.0f;
		//	fLength = rand() % (int)(g_fWidthBase * 200 ) / 100.0f - g_fWidthBase;
		//	move.x = sinf(fAngle) * fLength;
		//	move.y = rand() % 300 / 100.0f + g_fHeightBase;
		//	move.z = cosf(fAngle) * fLength;

		//	nLife = rand() % 100 + 150;  

		//	fSize = (float)(rand() % 30 + 20);

		//	pos.y = fSize / 2;

		//	// ビルボードの設定
		//	SetParticle(pos, move, XMFLOAT4(0.8f, 0.7f, 0.2f, 0.85f), fSize, fSize, nLife);
		//}
		if (GetKeyboardPress(DIK_SPACE))
		{
			for (int i = 0; i < for_p_num; i++) {
				CAMERA *cam = GetCamera();
				XMFLOAT3 move = { 0.0f, 0.0f, 0.0f, };			
				float fAngle = (float)(rand() % rand_angle);	//加算する方向(数式結果の数字が大きいほど、左右にばらつきが出る)
				fAngle = XMConvertToRadians(fAngle);
				float fLength = (float)(rand() % rand_length + 1) * 0.1f;	//xとz方向の加算速度この結果が大きいと素早く動く
				float fHigh = (float)(rand() % rand_high + 1) * 0.1f;	//xとz方向の加算速度この結果が大きいと素早く動く
				move.x += cosf(fAngle) * fLength;
				move.y += sinf(fAngle) * fHigh;			//高さの移動加算量
				//move.z += cosf(fAngle) * fLength;
				
				float angle = atan2f(move.y, move.x);
				XMFLOAT3 scl = { 0.025f + scale, 0.4f, 0.025f +scale};	//拡大率
				XMFLOAT3 rot = { 0.0f, cam->rot.y, 0.0f };	//回転率。いじる必要なし
				int nLife = rand() % p_Life + p_decay;
				rot.z = angle - XM_PI * 0.5f;
				rot.y = cam->rot.y;
				SetParticle(XMFLOAT3(0.0f, 30.0f, 100.0f), move, rot, scl, XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), nLife, p_decay, tex_num);
			}
		}
		if (GetKeyboardPress(DIK_1))
		{
			if(rand_angle < 360)
			rand_angle += 1;
		}
		if (GetKeyboardPress(DIK_2))
		{
			if(rand_angle > 2)
			rand_angle -= 1;
		}
		if (GetKeyboardTrigger(DIK_3))
		{
			rand_length += 1;
		}
		if (GetKeyboardTrigger(DIK_4))
		{
			if (rand_length > 2)
			rand_length -= 1;
		}
		if (GetKeyboardPress(DIK_5))
		{
			rand_high += 1;
		}
		if (GetKeyboardPress(DIK_6))
		{
			if (rand_high > 2)
				rand_high -= 1;
		}
		if (GetKeyboardTrigger(DIK_7))
		{
			scale += 0.05f;
		}
		if (GetKeyboardTrigger(DIK_8))
		{
			if (scale > 0.0f)
				scale -= 0.05f;
		}
		if (GetKeyboardTrigger(DIK_J))
		{
			if (tex_num == 0)
				tex_num = 1;
			else if (tex_num == 1)
				tex_num = 0;
		}
		if (GetKeyboardTrigger(DIK_K))
		{
			if(blend_mode)
			blend_mode = FALSE;
			else blend_mode = TRUE;
		}
		if (GetKeyboardTrigger(DIK_9))
		{
			if (for_p_num < 10)
			for_p_num++;
		}
		if (GetKeyboardTrigger(DIK_0))
		{
			if (for_p_num > 2)
				for_p_num--;
		}
		if (GetKeyboardTrigger(DIK_M))
		{
			if (p_decay > 10)
				p_decay--;
		}
		if (GetKeyboardTrigger(DIK_N))
		{
			if (p_decay < 120)
				p_decay++;
		}
		if (GetKeyboardTrigger(DIK_B))
		{
			if (p_Life > 1)
				p_Life--;
		}
		if (GetKeyboardTrigger(DIK_V))
		{
			if (p_Life < 180)
				p_Life++;
		}
		if (GetKeyboardTrigger(DIK_RETURN))
		{
			fout << "パーティクルステータス" << endl;
			fout << "角度のランダム数値;" << rand_angle << endl;
			fout << "飛距離のランダム数値;" << rand_length << endl;
			fout << "飛ぶ高さのランダム数値:" << rand_high << endl;
			fout << "パーティクルテクスチャ:" << tex_num << endl;
			fout << "ブレンドモード:" << blend_mode << endl;
			fout << "スケール:" << scale << endl;
			fout << "繰り返し数:" << for_p_num << endl;
			fout << "フェードをしないフレーム数:" << p_Life << endl;
			fout << "フェード開始フレーム:" << p_decay << endl;
			fout << endl << endl;
		} 
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawParticle(void)
{
	XMMATRIX mtxScl, mtxRot,mtxTranslate, mtxWorld, mtxView;
	CAMERA *cam = GetCamera();

	// ライティングを無効に
	SetLightEnable(FALSE);

	// 加算合成に設定
	if (blend_mode)
		SetBlendState(BLEND_MODE_ADD);
	else if (!blend_mode)
		SetBlendState(BLEND_MODE_ALPHABLEND);

	// Z比較無し
	SetDepthEnable(FALSE);

	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// プリミティブトポロジ設定
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);


	for(int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		if(g_aParticle[nCntParticle].bUse)
		{
			// テクスチャ設定
			GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[g_aParticle[nCntParticle].g_TexNo]);

			// ワールドマトリックスの初期化
			mtxWorld = XMMatrixIdentity();

			// ビューマトリックスを取得
			mtxView = XMLoadFloat4x4(&cam->mtxView);

			//mtxWorld = XMMatrixInverse(nullptr, mtxView);
			//mtxWorld.r[3].m128_f32[0] = 0.0f;
			//mtxWorld.r[3].m128_f32[1] = 0.0f;
			//mtxWorld.r[3].m128_f32[2] = 0.0f;

						// 処理が速いしお勧め
			//mtxWorld.r[0].m128_f32[0] = mtxView.r[0].m128_f32[0];
			//mtxWorld.r[0].m128_f32[1] = mtxView.r[1].m128_f32[0];
			//mtxWorld.r[0].m128_f32[2] = mtxView.r[2].m128_f32[0];

			//mtxWorld.r[1].m128_f32[0] = mtxView.r[0].m128_f32[1];
			//mtxWorld.r[1].m128_f32[1] = mtxView.r[1].m128_f32[1];
			//mtxWorld.r[1].m128_f32[2] = mtxView.r[2].m128_f32[1];

			//mtxWorld.r[2].m128_f32[0] = mtxView.r[0].m128_f32[2];
			//mtxWorld.r[2].m128_f32[1] = mtxView.r[1].m128_f32[2];
			//mtxWorld.r[2].m128_f32[2] = mtxView.r[2].m128_f32[2];

			// スケールを反映
			mtxScl = XMMatrixScaling(g_aParticle[nCntParticle].scale.x, g_aParticle[nCntParticle].scale.y, g_aParticle[nCntParticle].scale.z);
			mtxWorld = XMMatrixMultiply(mtxWorld, mtxScl);

			// 回転を反映
			mtxRot = XMMatrixRotationRollPitchYaw(g_aParticle[nCntParticle].rot.x, g_aParticle[nCntParticle].rot.y, g_aParticle[nCntParticle].rot.z);
			mtxWorld = XMMatrixMultiply(mtxWorld, mtxRot);


			// 移動を反映
			mtxTranslate = XMMatrixTranslation(g_aParticle[nCntParticle].pos.x, g_aParticle[nCntParticle].pos.y, g_aParticle[nCntParticle].pos.z);
			mtxWorld = XMMatrixMultiply(mtxWorld, mtxTranslate);

			// ワールドマトリックスの設定
			SetWorldMatrix(&mtxWorld);

			// マテリアル設定
			SetMaterial(g_aParticle[nCntParticle].material);

			// ポリゴンの描画
			GetDeviceContext()->Draw(4, 0);
		}
	}

	// ライティングを有効に
	SetLightEnable(TRUE);

	// 通常ブレンドに戻す
	SetBlendState(BLEND_MODE_ALPHABLEND);

	// Z比較有効
	SetDepthEnable(TRUE);

}

//=============================================================================
// 頂点情報の作成
//=============================================================================
HRESULT MakeVertexParticle(void)
{
	// 頂点バッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	GetDevice()->CreateBuffer(&bd, NULL, &g_VertexBuffer);

	{//頂点バッファの中身を埋める
		D3D11_MAPPED_SUBRESOURCE msr;
		GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

		VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

		// 頂点座標の設定
		vertex[0].Position = XMFLOAT3(-PARTICLE_SIZE_X / 2, PARTICLE_SIZE_Y / 2, 0.0f);
		vertex[1].Position = XMFLOAT3(PARTICLE_SIZE_X / 2, PARTICLE_SIZE_Y / 2, 0.0f);
		vertex[2].Position = XMFLOAT3(-PARTICLE_SIZE_X / 2, -PARTICLE_SIZE_Y / 2, 0.0f);
		vertex[3].Position = XMFLOAT3(PARTICLE_SIZE_X / 2, -PARTICLE_SIZE_Y / 2, 0.0f);

		// 法線の設定
		vertex[0].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
		vertex[1].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
		vertex[2].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
		vertex[3].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

		// 反射光の設定
		vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

		// テクスチャ座標の設定
		vertex[0].TexCoord = { 0.0f, 0.0f };
		vertex[1].TexCoord = { 1.0f, 0.0f };
		vertex[2].TexCoord = { 0.0f, 1.0f };
		vertex[3].TexCoord = { 1.0f, 1.0f };

		GetDeviceContext()->Unmap(g_VertexBuffer, 0);
	}

	return S_OK;
}

//=============================================================================
// マテリアルカラーの設定
//=============================================================================
void SetColorParticle(int nIdxParticle, XMFLOAT4 col)
{
	g_aParticle[nIdxParticle].material.Diffuse = col;
}

//=============================================================================
// パーティクルの発生処理
//=============================================================================
int SetParticle(XMFLOAT3 pos, XMFLOAT3 move, XMFLOAT3 rot, XMFLOAT3 scl, XMFLOAT4 col,int nLife, int nDecay, int texNo)
{
	int nIdxParticle = -1;

	for(int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		if(!g_aParticle[nCntParticle].bUse)
		{
			g_aParticle[nCntParticle].pos = pos;
			g_aParticle[nCntParticle].rot   = rot;
			g_aParticle[nCntParticle].scale = { 1.0f, 1.0f, 1.0f };
			g_aParticle[nCntParticle].move = move;
			g_aParticle[nCntParticle].material.Diffuse = col;
			g_aParticle[nCntParticle].col = col;
			g_aParticle[nCntParticle].scale = scl;
			g_aParticle[nCntParticle].nLife = nLife;
			g_aParticle[nCntParticle].nDecay = nDecay;
			g_aParticle[nCntParticle].g_TexNo = texNo;
			g_aParticle[nCntParticle].bUse = TRUE;

			nIdxParticle = nCntParticle;
			break;
		}
	}

	return nIdxParticle;
}