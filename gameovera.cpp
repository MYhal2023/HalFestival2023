//=============================================================================
//
// ゲームオーバー処理 [gameovera.cpp]
// Author : 
//
//=============================================================================
#include "gameover.h"
#include "game.h"
#include "sprite.h"
#include "renderer.h"
#include "input.h"
#include "fade.h"
#include "text_texture.h"
#include "debugproc.h"
#include "easing.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_MAX			(MAX_OVER_TEXTURE)				// テクスチャの数
#define WIN_OVER_TIME			(180)				// 勝ち演出の待ち時間

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static ID3D11Buffer					*g_VertexBuffer = NULL;	// 頂点情報
static char* g_TextureName[] = {
	"data/TEXTURE/fade_red.png",
	"data/TEXTURE/hazard.png",
	"data/TEXTURE/clear.png",
	"data/TEXTURE/number.png",
	"data/TEXTURE/danger.png",
	"data/TEXTURE/var.png",
};

static Over g_Over[MAX_OVER_TEXTURE];
static BOOL g_Load = FALSE; 
static BOOL next_mode = FALSE;
static int g_Overtype = 1;		//この変数は別モードに移行したときも保持したいので初期化処理に入れない
static XMFLOAT2 pos = { 0.0f, 0.0f };
static float hazard_pos_x = 0.0f;
static int cnt_frame = 0;
HRESULT InitOver(void)
{
	ID3D11Device *pDevice = GetDevice();

	// テクスチャ生成
	for (int i = 0; i < MAX_OVER_TEXTURE; i++)
	{
		D3DX11CreateShaderResourceViewFromFile(GetDevice(),
			g_TextureName[i],
			NULL,
			NULL,
			&g_Over[i].g_Texture,
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
		g_Over[i].color = { 1.0f, 1.0f, 1.0f, 0.0f };
		g_Over[i].pos = { SCREEN_CENTER_X, SCREEN_CENTER_Y };
		g_Over[i].size = { SCREEN_WIDTH, SCREEN_HEIGHT };
		g_Over[i].use = TRUE;
		g_Over[i].nIndex_x = 99;
		g_Over[i].nIndex_y = 99;
		g_Over[i].nIndex_alpha_x = 99;
		g_Over[i].nIndex_alpha_y = 99;
		g_Over[i].minus_alpha = 0.0f;
	}
	g_Over[ov_FadeRed].pos = { SCREEN_CENTER_X, SCREEN_CENTER_Y };
	g_Over[ov_FadeRed].size = { SCREEN_WIDTH, SCREEN_HEIGHT };
	g_Over[ov_FadeRed].color = { 1.0f, 1.0f, 1.0f, 0.0f };

	g_Over[ov_Hazard].pos = { SCREEN_CENTER_X * 0.5f, SCREEN_CENTER_Y };
	g_Over[ov_Hazard].size = { 350.0f, 350.0f };
	g_Over[ov_Hazard].color = { 1.0f, 1.0f, 1.0f, 0.0f };
	g_Over[ov_Hazard].minus_alpha = 0.015f;

	g_Over[ov_danger].pos = { SCREEN_CENTER_X * 0.5f, SCREEN_CENTER_Y };
	g_Over[ov_danger].size = { 899.0f * 0.9f, 215.0f *0.9f};
	g_Over[ov_danger].color = { 1.0f, 0.0f, 0.0f, 0.0f };
	g_Over[ov_danger].minus_alpha = 0.015f;

	g_Over[ov_Clear].pos = { SCREEN_CENTER_X, SCREEN_CENTER_Y };
	g_Over[ov_Clear].size = { 883.0f + 883.0f, 231.0f + 231.0f };
	g_Over[ov_Clear].color = { 1.0f, 1.0f, 1.0f, 0.0f };

	g_Load = TRUE;
	next_mode = FALSE;
	pos = { -200.0f, 0.0f };
	hazard_pos_x = 0.0f;
	cnt_frame = 0;
	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void UninitOver(void)
{
	if (g_Load == FALSE) return;

	// 頂点バッファの解放
	if (g_VertexBuffer)
	{
		g_VertexBuffer->Release();
		g_VertexBuffer = NULL;
	}

	// テクスチャの解放
	for (int i = 0; i < MAX_OVER_TEXTURE; i++)
	{
		if (g_Over[i].g_Texture)
		{
			g_Over[i].g_Texture->Release();
			g_Over[i].g_Texture = NULL;
		}
	}

	g_Load = FALSE;
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateOver(void)
{
	if (!CheckGameover())return;

	cnt_frame++;
	//ここからはゲームオーバーとなった時に入る
	switch (g_Overtype)
	{
	case OVER_WIN:
		if (g_Over[ov_Clear].color.w == 0.0f)
		{
			g_Over[ov_Clear].nIndex_x = Easing::SetEase(0.0f, 883.0f, 30.0f);
			g_Over[ov_Clear].nIndex_y = Easing::SetEase(0.0f, 231.0f, 30.0f);
		}

		if (Easing::GetEase(g_Over[ov_Clear].nIndex_x) >= 883.0f * 0.8f && g_Over[ov_Clear].nIndex_alpha_x == 99)
		{
			g_Over[ov_Clear].nIndex_alpha_x = Easing::SetEase(0.0f, 883.0f * 0.5f, 30.0f);
			g_Over[ov_Clear].nIndex_alpha_y = Easing::SetEase(0.0f, 231.0f * 0.5f, 30.0f);
		}

		if (g_Over[ov_Clear].nIndex_alpha_x != 99 && g_Over[ov_Clear].minus_alpha > -1.0f)
		{
			g_Over[ov_Clear].minus_alpha += 0.01f;
		}

		if (g_Over[ov_Clear].color.w < 1.0f)
			g_Over[ov_Clear].color.w += 0.05f;

		g_Over[ov_Clear].size.x = 1766.0f - Easing::GetEase(g_Over[ov_Clear].nIndex_x);
		g_Over[ov_Clear].size.y = 462.0f - Easing::GetEase(g_Over[ov_Clear].nIndex_y);
		break;
	case OVER_LOSE:
		if (g_Over[ov_FadeRed].color.w < 0.5f)
			g_Over[ov_FadeRed].color.w += 0.01f;

		if (g_Over[ov_Hazard].color.w < 0.0f || g_Over[ov_Hazard].color.w > 1.0f)
			g_Over[ov_Hazard].minus_alpha *= -1;
		g_Over[ov_Hazard].color.w += g_Over[ov_Hazard].minus_alpha;

		if (g_Over[ov_danger].color.w < 0.0f || g_Over[ov_danger].color.w > 1.0f)
			g_Over[ov_danger].minus_alpha *= -1;
		g_Over[ov_danger].color.w += g_Over[ov_danger].minus_alpha;

		hazard_pos_x -= 1.5f;
		break;
	}

	if (GetKeyboardTrigger(DIK_RETURN) || hazard_pos_x == -1.5f * 300.0f || cnt_frame == WIN_OVER_TIME)
	{
		next_mode = TRUE;
		SetFade(FADE_BOX_OUT, MODE_RESULT, WhiteBox);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawOver(void)
{
	if (!CheckGameover())return;

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

	switch (g_Overtype)
	{
	case OVER_WIN:
		if (next_mode)break;
		DrawOverTexture(&g_Over[ov_Clear], 0.0f, 1.0f);
		if (Easing::GetEase(g_Over[ov_Clear].nIndex_x) >= 880.0f)
		{
			g_Over[ov_Clear].color.w = 0.5f - g_Over[ov_Clear].minus_alpha;
			g_Over[ov_Clear].size.x = 883.0f + Easing::GetEase(g_Over[ov_Clear].nIndex_alpha_x);
			g_Over[ov_Clear].size.y = 231.0f + Easing::GetEase(g_Over[ov_Clear].nIndex_alpha_y);
			DrawOverTexture(&g_Over[ov_Clear], 0.0f, 1.0f);
			//元に戻す
			g_Over[ov_Clear].color.w = 1.0f;
		}

		break;
	case OVER_LOSE:
		DrawOverTexture(&g_Over[ov_FadeRed],0.0f, 1.0f);

		g_Over[ov_danger].pos = { SCREEN_CENTER_X * 1.0f + hazard_pos_x, SCREEN_CENTER_Y };
		DrawOverTexture(&g_Over[ov_danger], 0.0f, 1.0f);

		g_Over[ov_Hazard].pos = { SCREEN_CENTER_X * 0.40f + hazard_pos_x, SCREEN_CENTER_Y };
		DrawOverTexture(&g_Over[ov_Hazard], 0.0f, 1.0f);

		g_Over[ov_Hazard].pos = { SCREEN_CENTER_X * 1.6f + hazard_pos_x, SCREEN_CENTER_Y };
		DrawOverTexture(&g_Over[ov_Hazard], 0.0f, 1.0f);

		g_Over[ov_danger].pos = { SCREEN_CENTER_X * 2.8f + hazard_pos_x, SCREEN_CENTER_Y };
		DrawOverTexture(&g_Over[ov_danger], 0.0f, 1.0f);

		g_Over[ov_Hazard].pos = { SCREEN_CENTER_X * 2.2f + hazard_pos_x, SCREEN_CENTER_Y };
		DrawOverTexture(&g_Over[ov_Hazard], 0.0f, 1.0f);

		g_Over[ov_Hazard].pos = { SCREEN_CENTER_X * 3.4f + hazard_pos_x, SCREEN_CENTER_Y };
		DrawOverTexture(&g_Over[ov_Hazard], 0.0f, 1.0f);

		break;
	}


	SetDepthEnable(TRUE);

	// ライティングを無効
	SetLightEnable(TRUE);

}

void SetOverType(int type)
{
	g_Overtype = type;
}

int GetOverType(void)
{
	return g_Overtype;
}

//テクスチャ描画
void DrawOverTexture(Over* ov,float sx, float fx)
{
	// テクスチャ設定
	GetDeviceContext()->PSSetShaderResources(0, 1, &ov->g_Texture);

	// １枚のポリゴンの頂点とテクスチャ座標を設定
	SetSpriteColor(g_VertexBuffer, ov->pos.x, ov->pos.y, ov->size.x, ov->size.y, sx, 0.0f, fx, 1.0f,
		ov->color);

	// ポリゴン描画
	GetDeviceContext()->Draw(4, 0);

}

//引数:表示したい数字、表示座標(x,y)、表示サイズ(x方向,y方向)
void DrawOverNumber(int numb, float px, float py, float sx, float sy, XMFLOAT4 color)
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
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Over[ov_numb].g_Texture);

		// １枚のポリゴンの頂点とテクスチャ座標を設定
		SetSpriteColor(g_VertexBuffer, psx, py, sx, sy, tx, 0.0f, 0.1f, 1.0f,
			color);

		// ポリゴン描画
		GetDeviceContext()->Draw(4, 0);
		numb /= 10;
	}
}
