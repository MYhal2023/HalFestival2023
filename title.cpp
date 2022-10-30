//=============================================================================
//
// タイトル処理 [title.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "sprite.h"
#include "renderer.h"
#include "input.h"
#include "game.h"
#include "title.h"
#include "gameover.h"
#include "debugproc.h"
#include "fade.h"
#include "sound.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_MAX			(TITLE_TEXTURE_MAX)				// テクスチャの数
#define TEXTURE_SPEED		(0.1f)		// テクスチャの移動速度
#define TITLE_BUTTON_NUM	(title_finish - title_start + 1)			//
#define COLOR_SPEED			(0.01f)		// テクスチャの変色速度


//*****************************************************************************
// グローバル変数
//*****************************************************************************
static ID3D11Buffer					*g_VertexBuffer = NULL;	// 頂点情報
static char* g_TextureName[] = {
	"data/TEXTURE/var.png",
	"data/TEXTURE/var.png",
	"data/TEXTURE/var.png",
	"data/TEXTURE/var.png",
	"data/TEXTURE/var.png",
	"data/TEXTURE/var.png",
	"data/TEXTURE/var.png",
};
static Title g_Title[TEXTURE_MAX];
static BOOL g_Load = FALSE;
static float speed[TEXTURE_MAX];
static int cursol;
HRESULT InitTitle(void)
{
	ID3D11Device *pDevice = GetDevice();

	//テクスチャ生成
	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		g_Title[i].g_Texture = NULL;
		D3DX11CreateShaderResourceViewFromFile(GetDevice(),
			g_TextureName[i],
			NULL,
			NULL,
			&g_Title[i].g_Texture,
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
		g_Title[i].textNo = i;
		switch (i)
		{
		case title_bg:
			g_Title[i].color = { 0.0f, 0.0f, 1.0f, 1.0f };
			g_Title[i].pos = { SCREEN_CENTER_X, SCREEN_CENTER_Y };
			g_Title[i].size = { SCREEN_WIDTH, SCREEN_HEIGHT };
			break;
		case title_logo:
			g_Title[i].color = { 1.0f, 1.0f, 1.0f, 1.0f };
			g_Title[i].pos = { SCREEN_CENTER_X, SCREEN_HEIGHT * 0.18f };
			g_Title[i].size = {600 * 1.0f, 200 * 1.0f };
			break;
		case title_start:
			g_Title[i].color = { 1.0f, 1.0f, 1.0f, 1.0f };
			g_Title[i].pos = { SCREEN_CENTER_X, SCREEN_CENTER_Y };
			g_Title[i].size = { 400 * 1.0f, 100 * 1.0f };
			break;
		case title_score:
			g_Title[i].color = { 1.0f, 1.0f, 1.0f, 1.0f };
			g_Title[i].pos = { SCREEN_CENTER_X, g_Title[title_start].pos.y + 100.0f * 1.1f };
			g_Title[i].size = { 400 * 1.0f, 100 * 1.0f };
			break;
		case title_option:
			g_Title[i].color = { 1.0f, 1.0f, 1.0f, 1.0f };
			g_Title[i].pos = { SCREEN_CENTER_X,g_Title[title_score].pos.y + 100.0f * 1.1f };
			g_Title[i].size = { 400 * 1.0f, 100 * 1.0f };
			break;
		case title_finish:
			g_Title[i].color = { 1.0f, 1.0f, 1.0f, 1.0f };
			g_Title[i].pos = { SCREEN_CENTER_X, g_Title[title_option].pos.y + 100.0f * 1.1f };
			g_Title[i].size = { 400 * 1.0f, 100 * 1.0f };
			break;
		case title_cursol:
			g_Title[i].color = { 1.0f, 0.0f, 0.0f, 1.0f };
			g_Title[i].pos = { 0.0f, 0.0f };
			g_Title[i].size = { 400 * 1.0f, 100 * 1.0f };
			break;
		}
	}
	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		switch (i)
		{
		case title_cursol:
			speed[i] = 0.01f;
			break;
		}
	}
	cursol = 0;
		g_Load = TRUE;
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitTitle(void)
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
		if (g_Title[i].g_Texture)
		{
			g_Title[i].g_Texture->Release();
			g_Title[i].g_Texture = NULL;
		}
	}

	g_Load = FALSE;
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateTitle(void)
{

	//カーソルの変色
	if (g_Title[title_cursol].color.w > 1.2f || g_Title[title_cursol].color.w < 0.7f)
		speed[title_cursol] *= -1;

	g_Title[title_cursol].color.w += speed[title_cursol];
	g_Title[title_cursol].color.x += speed[title_cursol];
	g_Title[title_cursol].color.y += speed[title_cursol];
	g_Title[title_cursol].color.z += speed[title_cursol];

	//カーソル変更
	if (GetKeyboardTrigger(DIK_UP) && cursol > 0)
	{
		cursol--;
		//PlaySound(SOUND_LABEL_SE_Select);
	}
	else if (GetKeyboardTrigger(DIK_DOWN) && TITLE_BUTTON_NUM - 1 > cursol)
	{
		cursol++;
		//PlaySound(SOUND_LABEL_SE_Select);
	}
	int num = title_start + cursol;
	g_Title[title_cursol].pos = g_Title[num].pos;
	
	if (GetKeyboardTrigger(DIK_RETURN))
	{
		switch (cursol) {
		case 0://はじめから
			//PlaySound(SOUND_LABEL_SE_Decision);
			SetFade(FADE_BOX_OUT, MODE_GAME, WhiteBox);
			break;
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawTitle(void)
{
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


	DrawTexture(&g_Title[title_bg]);
	DrawTexture(&g_Title[title_logo]);
	DrawTexture(&g_Title[title_start]);
	DrawTexture(&g_Title[title_score]);
	DrawTexture(&g_Title[title_option]);
	DrawTexture(&g_Title[title_finish]);
	DrawTexture(&g_Title[title_cursol]);

}

//0はフェードイン、1はフェードアウト
void FadeTexture(int type, Title *title)
{
	switch (type) {
	case 0: 
		title->color.w += 0.01f;
			break;
	case 1:
		title->color.w -= 0.01f;
		break;
	}
}

//移動速度、座標最大値、座標最小値、ポインター
void MoveTexture(float speed, Title *title)
{
	title->pos.y += speed;
}

//テクスチャ描画
void DrawTexture(Title* title)
{
	// テクスチャ設定
	GetDeviceContext()->PSSetShaderResources(0, 1, &title->g_Texture);

	// １枚のポリゴンの頂点とテクスチャ座標を設定
	SetSpriteColor(g_VertexBuffer, title->pos.x, title->pos.y, title->size.x, title->size.y, 0.0f, 0.0f, 1.0f, 1.0f,
		title->color);

	// ポリゴン描画
	GetDeviceContext()->Draw(4, 0);
}
