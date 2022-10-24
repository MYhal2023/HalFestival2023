//=============================================================================
//
// UI処理 [ui.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "sprite.h"
#include "renderer.h"
#include "game.h"
#include "ui.h"
#include "reserve.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_MAX			(UI_MAX)				// テクスチャの数
#define NUMBER_SIZE			(30.0f)			// x方向のサイズ
#define COST_NUMBER_SIZE	(45.0f)			// x方向のサイズ

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static ID3D11Buffer					*g_VertexBuffer = NULL;	// 頂点情報
static ID3D11ShaderResourceView		*g_Texture[TEXTURE_MAX] = { NULL };	// テクスチャ情報

static char* g_TextureName[] = {
	"data/TEXTURE/var.png",
};


static UI g_UI[TEXTURE_MAX];
static BOOL g_Load = FALSE;
static BOOL g_Help = FALSE;
HRESULT InitUI(void)
{
	ID3D11Device *pDevice = GetDevice();

	// テクスチャ生成
	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		D3DX11CreateShaderResourceViewFromFile(GetDevice(),
			g_TextureName[i],
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

	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		g_UI[i].color = { 1.0f, 1.0f, 1.0f, 1.0f };
		g_UI[i].pos = { 0.0f, 0.0f };
		g_UI[i].size = { 50.0f, 50.0f };
		g_UI[i].use = TRUE;
	}

	g_Load = TRUE;
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitUI(void)
{
	if (g_Load == FALSE) return;

	// 頂点バッファの解放
	if (g_VertexBuffer)
	{
		g_VertexBuffer->Release();
		g_VertexBuffer = NULL;
	}

	// テクスチャの解放
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
void UpdateUI(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawUI(void)
{
	SetDepthEnable(FALSE);

	// ライティングを無効
	SetLightEnable(FALSE);
	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// マトリクス設定
	SetWorldViewProjection2D();

	// プリミティブトポロジ設定
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// マテリアル設定
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	SetMaterial(material);

	SetDepthEnable(TRUE);

	// ライティングを無効
	SetLightEnable(TRUE);

}


void DrawUIbg(void)
{
	// テクスチャ設定
	GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[var_bg]);

	// １枚のポリゴンの頂点とテクスチャ座標を設定
	SetSpriteColor(g_VertexBuffer, g_UI[var_bg].pos.x, g_UI[var_bg].pos.y, g_UI[var_bg].size.x, g_UI[var_bg].size.y, 0.0f, 0.0f, 1.0f, 1.0f,
		g_UI[var_bg].color);

	// ポリゴン描画
	GetDeviceContext()->Draw(4, 0);

}

//引数:表示したい数字、表示座標(x,y)、表示サイズ(x方向,y方向)
void DrawNumber(int numb, float px, float py, float sx, float sy, XMFLOAT4 color)
{
	int digit = 0;
	int clock = numb;
	if (clock != 0)
	{
		while (clock != 0)
		{
			clock /= 10;
			digit++;
		}
	}
	else
		digit = 1;

	for (int i = 0; i < digit; i++)
	{
		px = px - sx * i;
		float x = (float)(numb % 10);		//今回表示する数字
		float tx = x * 0.1f;			// テクスチャの左上X座標

		// テクスチャ設定
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[number]);

		// １枚のポリゴンの頂点とテクスチャ座標を設定
		SetSpriteColor(g_VertexBuffer, px, py, sx, sy, tx, 0.0f, 0.1f, 1.0f,
			color);

		// ポリゴン描画
		GetDeviceContext()->Draw(4, 0);
		numb /= 10;
	}
}



//void DrawButton(void)
//{
//	// テクスチャ設定
//	GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[button_s]);
//
//	// １枚のポリゴンの頂点とテクスチャ座標を設定
//	SetSpriteColor(g_VertexBuffer, g_UI[button_s].pos.x, g_UI[button_s].pos.y, g_UI[button_s].size.x, g_UI[button_s].size.y, 0.0f, 0.0f, 1.0f, 1.0f,
//		g_UI[button_s].color);
//
//	// ポリゴン描画
//	GetDeviceContext()->Draw(4, 0);
//}


//void DrawHelpButton(void)
//{
//	//ボタンアイコン
//	// テクスチャ設定
//	GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[icon_help]);
//
//	// １枚のポリゴンの頂点とテクスチャ座標を設定
//	SetSpriteColor(g_VertexBuffer, g_UI[icon_help].pos.x, g_UI[icon_help].pos.y, g_UI[icon_help].size.x, g_UI[icon_help].size.y, 0.0f, 0.0f, 1.0f, 1.0f,
//		g_UI[icon_help].color);
//
//	// ポリゴン描画
//	GetDeviceContext()->Draw(4, 0);
//
//	//ボタンヨウ背景
//	// テクスチャ設定
//	GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[var_bg]);
//
//	// １枚のポリゴンの頂点とテクスチャ座標を設定
//	SetSpriteColor(g_VertexBuffer, g_UI[button_bg].pos.x, g_UI[button_bg].pos.y, g_UI[button_bg].size.x, g_UI[button_bg].size.y, 0.0f, 0.0f, 1.0f, 1.0f,
//		XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
//
//	// ポリゴン描画
//	GetDeviceContext()->Draw(4, 0);
//
//	//ヘルプテキスト
//	// テクスチャ設定
//	GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[button_help]);
//
//	// １枚のポリゴンの頂点とテクスチャ座標を設定
//	SetSpriteColor(g_VertexBuffer, g_UI[button_help].pos.x, g_UI[button_help].pos.y, g_UI[button_help].size.x, g_UI[button_help].size.y, 0.0f, 0.0f, 1.0f, 1.0f,
//		g_UI[button_help].color);
//
//	// ポリゴン描画
//	GetDeviceContext()->Draw(4, 0);
//
//	if (g_Help)
//	{
//		//ヘルプテキスト
//		// テクスチャ設定
//		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[help_texture]);
//
//		// １枚のポリゴンの頂点とテクスチャ座標を設定
//		SetSpriteColor(g_VertexBuffer, g_UI[help_texture].pos.x, g_UI[help_texture].pos.y, g_UI[help_texture].size.x, g_UI[help_texture].size.y, 0.0f, 0.0f, 1.0f, 1.0f,
//			g_UI[help_texture].color);
//
//		// ポリゴン描画
//		GetDeviceContext()->Draw(4, 0);
//	}
//}

void SetHelpButton(BOOL flag) { g_Help = flag; }
BOOL GetHelpButton(void) { return g_Help; }