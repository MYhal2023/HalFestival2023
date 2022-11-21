//=============================================================================
//
// Reserve処理 [ui.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "sprite.h"
#include "renderer.h"
#include "game.h"
#include "reserve.h"
#include "ui.h"
#include "text_texture.h"
#include "fade.h"
#include "debugproc.h"
#include "sound.h"
#include "input.h"
#include "easing.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_MAX			(RESERVE_TEXTURE_MAX)				// テクスチャの数
#define NUMBER_SIZE			(30.0f)			// x方向のサイズ
#define COST_NUMBER_SIZE	(45.0f)			// x方向のサイズ
#define BUTTON_SIZE			(106.0f)		// ボタンの縦幅サイズ。多分これくらい
#define ROW_NUM				(5)				// 一列に並べるユニット数
#define HELP_TEX_NUM		(1)				// 一列に並べるユニット数

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static ID3D11Buffer					*g_VertexBuffer = NULL;	// 頂点情報

static char* g_TextureName[TEXTURE_MAX] = {
	"data/TEXTURE/var.png",
	"data/TEXTURE/var.png",
	"data/TEXTURE/t_startbutton.png",
	"data/TEXTURE/var.png",
	"data/TEXTURE/number.png",
};

static Reserve g_Reserve;
static TEXT_TEXTURE g_text[TEXTURE_MAX];
static Button g_Button[TEXTURE_MAX];
static int cursol;
static int HelpTexNum = 0;	//ヘルプの画像枚数
static float cursolAlpha;	//カーソル透明度
static float alphaSpeed;	//カーソル透明度加算量
static BOOL g_Load = FALSE;
static BOOL restart = FALSE;
static BOOL once = FALSE;
HRESULT InitReserve(void)
{
	//起動時、一度だけ初期化
	if (!restart)
	{
		g_Reserve.mode = 99;
		restart = TRUE;
#ifdef _DEBUG

#endif
	}

	ID3D11Device *pDevice = GetDevice();

	// テクスチャ生成
	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		D3DX11CreateShaderResourceViewFromFile(GetDevice(),
			g_TextureName[i],
			NULL,
			NULL,
			&g_Button[i].g_Texture,
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
		g_Button[i].color = { 1.0f, 1.0f, 1.0f, 1.0f };
		g_Button[i].pos = { 0.0f, 0.0f };
		g_Button[i].size = { 50.0f, 50.0f };
		g_Button[i].use = TRUE;
	}

	g_Button[rs_vigilance].pos = { SCREEN_WIDTH * 0.70f , SCREEN_HEIGHT * 0.2f };
	g_Button[rs_vigilance].size = { 100.0f * 4.0f , 100.0f * 1.0f };

	g_Button[rs_rank].pos = { SCREEN_WIDTH * 0.75f , SCREEN_HEIGHT * 0.60f };
	g_Button[rs_rank].size = { 100.0f * 3.0f , 100.0f * 1.0f };

	g_Button[rs_start].pos = { SCREEN_WIDTH * 0.80f , SCREEN_HEIGHT * 0.80f };
	g_Button[rs_start].size = { 100.0f * 3.0f , 100.0f * 2.0f };


	cursol = 0;
	cursolAlpha = 0.5f;
	alphaSpeed = 0.02f;
	g_Load = TRUE;
	once = FALSE;
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitReserve(void)
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
		if (g_Button[i].g_Texture)
		{
			g_Button[i].g_Texture->Release();
			g_Button[i].g_Texture = NULL;
		}
	}

	g_Load = FALSE;
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateReserve(void)
{
	if (GetKeyboardTrigger(DIK_RETURN))
	{
		//PlaySound(SOUND_LABEL_SE_Decision);
		SetFade(FADE_BOX_OUT, MODE_GAME, WhiteBox);
	}
	if (!once)
	{
		g_Button[rs_start].nIndex = Easing::SetEase(SCREEN_HEIGHT * 0.0f, SCREEN_HEIGHT * 0.4f, 100.0f);
		g_Button[rs_rank].nIndex = Easing::SetEase(SCREEN_HEIGHT * 0.0f, SCREEN_HEIGHT * 0.9f, 80.0f);
		g_Button[rs_vigilance].nIndex = Easing::SetEase(SCREEN_HEIGHT * 0.0f, SCREEN_HEIGHT * 0.9f, 60.0f);
		once = TRUE;
	}
	g_Button[rs_start].set_pos.y = Easing::GetEase(g_Button[rs_start].nIndex);
	g_Button[rs_rank].set_pos.x = Easing::GetEase(g_Button[rs_rank].nIndex);
	g_Button[rs_vigilance].set_pos.x = Easing::GetEase(g_Button[rs_vigilance].nIndex);
}

//=============================================================================
// 描画処理 ここに全部持ってくるので頂点バッファ設定等は個々でいらない
//=============================================================================
void DrawReserve(void)
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
	
	g_Button[rs_start].pos = { SCREEN_WIDTH * 0.8f, SCREEN_HEIGHT * 1.2f - g_Button[rs_start].set_pos.y };
	g_Button[rs_start].size = { 530 * 0.9f, 100 * 1.0f };
	g_Button[rs_start].color = { 1.0f, 1.0f, 1.0f, 1.0f };
	DrawTexture(&g_Button[rs_start]);


	g_Button[rs_vigilance].pos = { SCREEN_WIDTH * 1.2f - g_Button[rs_vigilance].set_pos.x, SCREEN_HEIGHT * 0.25f };
	g_Button[rs_vigilance].size = { 530 * 0.9f, 100 * 1.0f };
	g_Button[rs_vigilance].color = { 1.0f, 1.0f, 1.0f, 1.0f };
	DrawTexture(&g_Button[rs_vigilance]);

	g_Button[rs_rank].pos = { SCREEN_WIDTH * 1.2f - g_Button[rs_rank].set_pos.x , SCREEN_HEIGHT * 0.55f};
	g_Button[rs_rank].size = { 530 * 0.9f, 100 * 1.0f };
	g_Button[rs_rank].color = { 1.0f, 1.0f, 1.0f, 1.0f };
	DrawTexture(&g_Button[rs_rank]);

	SetDepthEnable(TRUE);

	// ライティングを無効
	SetLightEnable(TRUE);

}

Reserve *GetReserve(void) { return &g_Reserve; };

void DrawButton(XMFLOAT4 color, float px, float py, float sx, float sy)
{
	// テクスチャ設定
	GetDeviceContext()->PSSetShaderResources(0, 1, &g_Button[rs_Button_tx].g_Texture);

	// １枚のポリゴンの頂点とテクスチャ座標を設定
	SetSpriteColor(g_VertexBuffer, px, py, sx, sy, 0.0f, 0.0f, 1.0f, 1.0f,
		color);

	// ポリゴン描画
	GetDeviceContext()->Draw(4, 0);

}
//引数:表示したい数字、表示座標(x,y)、表示サイズ(x方向,y方向)
void DrawNumberRe(int numb, float px, float py, float sx, float sy, XMFLOAT4 color)
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

	float psx = px + sx * digit;
	for (int i = 0; i < digit; i++)
	{
		psx -= sx;
		float x = (float)(numb % 10);		//今回表示する数字
		float tx = x * 0.1f;			// テクスチャの左上X座標

		// テクスチャ設定
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Button[rs_number].g_Texture);

		// １枚のポリゴンの頂点とテクスチャ座標を設定
		SetSpriteColor(g_VertexBuffer, psx, py, sx, sy, tx, 0.0f, 0.1f, 1.0f,
			color);

		// ポリゴン描画
		GetDeviceContext()->Draw(4, 0);
		numb /= 10;
	}
}

void DrawTexture(Button* bt)
{
	// テクスチャ設定
	GetDeviceContext()->PSSetShaderResources(0, 1, &bt->g_Texture);

	// １枚のポリゴンの頂点とテクスチャ座標を設定
	SetSpriteColor(g_VertexBuffer, bt->pos.x, bt->pos.y, bt->size.x, bt->size.y, 0.0f, 0.0f, 1.0f, 1.0f,
		bt->color);

	// ポリゴン描画
	GetDeviceContext()->Draw(4, 0);
}