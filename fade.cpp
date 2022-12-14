//=============================================================================
//
// フェード処理 [fade.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "renderer.h"
#include "fade.h"
#include "sound.h"
#include "sprite.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_WIDTH				(SCREEN_WIDTH)	// 背景サイズ
#define TEXTURE_HEIGHT				(SCREEN_HEIGHT)	// 
#define TEXTURE_MAX					(6)				// テクスチャの数
#define FADE_BOX_MAX				(145)				// テクスチャの数
#define FADE_BOX_SIZE				(120.0f)				// テクスチャの数
#define FADE_BOX_WIDTH_NUM			(SCREEN_WIDTH / 120.0f)				// テクスチャの数
#define FADE_BOX_HEIGHT_NUM			(SCREEN_HEIGHT / 120.0f)				// テクスチャの数

#define	FADE_RATE					(0.02f)			// フェード係数
#define	BOX_FADE_RATE					(0.2f)			// フェード係数
#define FADE_FRAME					(1.0f / BOX_FADE_RATE)	//フェードレートに基づく、フェードフレーム数
#define	BOX_FADE_RED					(0.0f)			// フェード係数
#define	BOX_FADE_BLUE					(1.0f)			// フェード係数
#define	BOX_FADE_GREEN					(1.0f)			// フェード係数

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
static ID3D11Buffer				*g_VertexBuffer = NULL;		// 頂点情報
static ID3D11ShaderResourceView	*g_Texture[TEXTURE_MAX] = { NULL };	// テクスチャ情報

static char *g_TexturName[TEXTURE_MAX] = {
	"data/TEXTURE/var.png",
	"data/TEXTURE/fade_black.png",
	"data/TEXTURE/ts_open.png",
	"data/TEXTURE/ts_close.png",
	"data/TEXTURE/ts_right_door.png",
	"data/TEXTURE/ts_left_door.png",
};


static BOOL						g_Use;						// TRUE:使っている  FALSE:未使用
static float					g_w, g_h;					// 幅と高さ
static XMFLOAT3					g_Pos;						// ポリゴンの座標
static int						g_TexNo;					// テクスチャ番号

FADE							g_Fade = FADE_IN;			// フェードの状態
int								g_ModeNext;					// 次のモード
XMFLOAT4						g_Color;					// フェードのカラー（α値）
static FadeBox					g_FadeBox[64][64];
static BOOL						g_Load = FALSE;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitFade(void)
{
	ID3D11Device *pDevice = GetDevice();

	//テクスチャ生成
	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		g_Texture[i] = NULL;
		D3DX11CreateShaderResourceViewFromFile(GetDevice(),
			g_TexturName[i],
			NULL,
			NULL,
			&g_Texture[i],
			NULL);
	}


	// 頂点バッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	GetDevice()->CreateBuffer(&bd, NULL, &g_VertexBuffer);


	// 初期化
	g_Use   = TRUE;
	g_w     = TEXTURE_WIDTH;
	g_h     = TEXTURE_HEIGHT;
	g_Pos   = { SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f };
	g_TexNo = 1;

	g_Fade  = FADE_IN;
	g_Color = { 1.0f, 1.0f, 1.0f, 1.0f };

	const float boxsize = 120.0f;
	int width = (int)(FADE_BOX_WIDTH_NUM);
	int height = (int)(FADE_BOX_HEIGHT_NUM);
	for (int i = 0; i < width; i++)
	{
		for (int k = 0; k < height; k++)
		{
			g_FadeBox[i][k].pos = { (i * boxsize) + (boxsize * 0.5f),  (k * boxsize) + (boxsize * 0.5f) };
			g_FadeBox[i][k].size = 0.0f;
			g_FadeBox[i][k].color = { 0.0f, 0.0f, 0.0f, 0.0f };
		}
	}

	g_Load = TRUE;
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitFade(void)
{
	if (g_Load == FALSE) return;

	if (g_VertexBuffer)
	{
		g_VertexBuffer->Release();
		g_VertexBuffer = NULL;
	}

	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		if (g_Texture[i])
		{
			g_Texture[i]->Release();
			g_Texture[i] = NULL;
		}
	}

	g_Load = FALSE;
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateFade(void)
{

	if (g_Fade != FADE_NONE)
	{// フェード処理中
		if (g_Fade == FADE_OUT)
		{// フェードアウト処理
			g_Color.w += FADE_RATE;		// α値を加算して画面を消していく
			if (g_Color.w >= 1.0f)
			{
				// 鳴っている曲を全部止める
				StopSound();

				// フェードイン処理に切り替え
				g_Color.w = 1.0f;
				SetFade(FADE_IN, g_ModeNext, g_TexNo);

				// モードを設定
				SetMode(g_ModeNext);
			}

		}
		else if (g_Fade == FADE_IN)
		{// フェードイン処理
			g_Color.w -= FADE_RATE;		// α値を減算して画面を浮き上がらせる
			if (g_Color.w <= 0.0f)
			{
				// フェード処理終了
				g_Color.w = 0.0f;
				SetFade(FADE_NONE, g_ModeNext, g_TexNo);
			}

		}
		else if (g_Fade == FADE_BOX_OUT)
		{
			int k = (int)(FADE_BOX_HEIGHT_NUM)-1;
			int i = (int)(FADE_BOX_WIDTH_NUM)-1;
			if (g_FadeBox[i][k].color.w >= 1.0f)
			{
				// 鳴っている曲を全部止める
				StopSound();

				// フェードイン処理に切り替え
				SetFade(FADE_BOX_IN, g_ModeNext, g_TexNo);

				// モードを設定
				SetMode(g_ModeNext);

			}
			else 
			{
				for (int i = 0; i < FADE_BOX_WIDTH_NUM; i++)
				{
					//フェードアウト	
					if (i == 0 && g_FadeBox[i][k].color.w < 1.0f)
						FadeOutBoxFunc(i, k);
					else if (i >= 1 && g_FadeBox[i - 1][k / 4].color.w > 0.0f)
						FadeOutBoxFunc(i, k);
				}
			}
		}
		else if (g_Fade == FADE_BOX_IN)
		{
			int k = (int)(FADE_BOX_HEIGHT_NUM)-1;
			int i = (int)(FADE_BOX_WIDTH_NUM)-1;
			for (int i = 0; i < FADE_BOX_WIDTH_NUM; i++)
			{
				//フェードイン
				if (i == 0 && g_FadeBox[i][k].color.w > 0.0f)
					FadeInBoxFunc(i, k);
				else if (i >= 1 && g_FadeBox[i - 1][k / 4].color.w <= 0.5f)
					FadeInBoxFunc(i, k);
			}

			//フェード終了処理
			if (g_FadeBox[i][k].color.w <= 0.0f)
			{
				//ボックスフェードの初期化
				const float boxsize = 120.0f;
				int width = (int)(FADE_BOX_WIDTH_NUM);
				int height = (int)(FADE_BOX_HEIGHT_NUM);
				for (int s = 0; s < width; s++)
				{
					for (int t = 0; t < height; t++)
					{
						g_FadeBox[s][t].size = 0.0f;
						g_FadeBox[s][t].color = { 0.0f, 0.0f, 0.0f, 0.0f };
					}
				}

				SetFade(FADE_NONE, g_ModeNext, g_TexNo);
			}
		}
		else if (g_Fade == TRANSITION_CLOSE)
		{
		}
		else if (g_Fade == TRANSITION_OPEN)
		{
		}
	}

#ifdef _DEBUG	// デバッグ情報を表示する
	// PrintDebugProc("\n");

#endif

}

//フェードアウトトランジションの再帰呼び出し
int FadeOutBoxFunc(int i, int k)
{
	if (k < 0)return 0;

	if (k > 0 && g_FadeBox[i][k - 1].color.w >= 0.2f && g_FadeBox[i][k].color.w < 1.0f) {
		g_FadeBox[i][k].color.w += BOX_FADE_RATE;
		g_FadeBox[i][k].size += FADE_BOX_SIZE / FADE_FRAME;
		g_FadeBox[i][k].color.x += BOX_FADE_RED / FADE_FRAME;
		g_FadeBox[i][k].color.y += BOX_FADE_BLUE / FADE_FRAME;
		g_FadeBox[i][k].color.z += BOX_FADE_GREEN / FADE_FRAME;
	}
	else if (k == 0 && g_FadeBox[i][k].color.w < 1.0f) {
		g_FadeBox[i][k].color.w += BOX_FADE_RATE;
		g_FadeBox[i][k].size += FADE_BOX_SIZE / FADE_FRAME;
		g_FadeBox[i][k].color.x += BOX_FADE_RED / FADE_FRAME;
		g_FadeBox[i][k].color.y += BOX_FADE_BLUE / FADE_FRAME;
		g_FadeBox[i][k].color.z += BOX_FADE_GREEN / FADE_FRAME;
	}

	k--;
	return FadeOutBoxFunc(i, k);
}

//フェードイントランジションの再帰呼び出し
int FadeInBoxFunc(int i, int k)
{
	if (k < 0)return 0;

	if (k > 0 && g_FadeBox[i][k - 1].color.w <= 0.8f && g_FadeBox[i][k].color.w > 0.0f) {
		g_FadeBox[i][k].color.w -= BOX_FADE_RATE;
		g_FadeBox[i][k].size -= FADE_BOX_SIZE / FADE_FRAME;
		g_FadeBox[i][k].color.x += BOX_FADE_RED / FADE_FRAME;
		g_FadeBox[i][k].color.y += BOX_FADE_BLUE / FADE_FRAME;
		g_FadeBox[i][k].color.z += BOX_FADE_GREEN / FADE_FRAME;
	}
	else if (k == 0 && g_FadeBox[i][k].color.w > 0.0f) {
		g_FadeBox[i][k].color.w -= BOX_FADE_RATE;
		g_FadeBox[i][k].size -= FADE_BOX_SIZE / FADE_FRAME;
		g_FadeBox[i][k].color.x += BOX_FADE_RED / FADE_FRAME;
		g_FadeBox[i][k].color.y += BOX_FADE_BLUE / FADE_FRAME;
		g_FadeBox[i][k].color.z += BOX_FADE_GREEN / FADE_FRAME;
	}

	k--;
	return FadeInBoxFunc(i, k);
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawFade(void)
{
	if (g_Fade == FADE_NONE) return;	// フェードしないのなら描画しない

	// 加算合成に設定
	//SetBlendState(BLEND_MODE_ADD);
	SetDepthEnable(FALSE);

	// ライティングを無効
	SetLightEnable(FALSE);

	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// プリミティブトポロジ設定
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// マテリアル設定
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	SetMaterial(material);


	//背景を描画
	if(g_Fade == FADE_IN || g_Fade == FADE_OUT)
	{
		// テクスチャ設定
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[g_TexNo]);

		// １枚のポリゴンの頂点とテクスチャ座標を設定
		//SetVertex(0.0f, 0.0f, SCREEN_WIDTH, TEXTURE_WIDTH, 0.0f, 0.0f, 1.0f, 1.0f);
		SetSpriteColor(g_VertexBuffer, SCREEN_WIDTH/2, SCREEN_HEIGHT /2, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f,
			g_Color);

		// ポリゴン描画
		GetDeviceContext()->Draw(4, 0);
	}
	else if (g_Fade == FADE_BOX_OUT || g_Fade == FADE_BOX_IN)
	{
		int width = (int)(FADE_BOX_WIDTH_NUM);
		int height = (int)(FADE_BOX_HEIGHT_NUM);
		for (int i = 0; i < width; i++)
		{
			for (int k = 0; k < height; k++)
			{
				if (g_FadeBox[i][k].color.w <= 0.0f)continue;	//透明なやつはスルー
				// テクスチャ設定
				GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[g_TexNo]);

				// １枚のポリゴンの頂点とテクスチャ座標を設定
				//SetVertex(0.0f, 0.0f, SCREEN_WIDTH, TEXTURE_WIDTH, 0.0f, 0.0f, 1.0f, 1.0f);
				SetSpriteColor(g_VertexBuffer, g_FadeBox[i][k].pos.x, g_FadeBox[i][k].pos.y, g_FadeBox[i][k].size, g_FadeBox[i][k].size, 0.0f, 0.0f, 1.0f, 1.0f,
					g_FadeBox[i][k].color);

				// ポリゴン描画
				GetDeviceContext()->Draw(4, 0);
			}
		}

	}
	SetDepthEnable(TRUE);

	SetLightEnable(TRUE);


}


//=============================================================================
// フェードの状態設定
//=============================================================================
void SetFade(FADE fade, int modeNext, int texNo)
{
	g_Fade = fade;
	g_ModeNext = modeNext;
	g_TexNo = texNo;
}

//=============================================================================
// フェードの状態取得
//=============================================================================
FADE GetFade(void)
{
	return g_Fade;
}



