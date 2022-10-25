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

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_MAX			(13)				// テクスチャの数
#define CH_TEXTURE_MAX		(7)				// キャラテクスチャの数
#define IC_TEXTURE_MAX		(9)				// アイコンテクスチャの数
#define CHAR_TEXTURE_MAX	(7)				// キャラテクスチャの数
#define SKILL_TEXTURE_MAX	(7)				// キャラスキルテクスチャの数
#define NUMBER_SIZE			(30.0f)			// x方向のサイズ
#define COST_NUMBER_SIZE	(45.0f)			// x方向のサイズ
#define BUTTON_SIZE			(106.0f)		// ボタンの縦幅サイズ。多分これくらい
#define BUTTON_MAX			(4)				// ユーサーが選択できるボタン数
#define ROW_NUM				(5)				// 一列に並べるユニット数
#define HELP_TEX_NUM		(1)				// 一列に並べるユニット数

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static ID3D11Buffer					*g_VertexBuffer = NULL;	// 頂点情報
static ID3D11ShaderResourceView		*g_Texture[TEXTURE_MAX] = { NULL };	// テクスチャ情報
static ID3D11ShaderResourceView		*g_CharTexture[CHAR_TEXTURE_MAX] = { NULL };	// テクスチャ情報
static ID3D11ShaderResourceView		*g_IconTexture[IC_TEXTURE_MAX] = { NULL };	// テクスチャ情報
static ID3D11ShaderResourceView		*g_SkillTexture[SKILL_TEXTURE_MAX] = { NULL };	// テクスチャ情報

static char* g_TextureName[TEXTURE_MAX] = {
	"data/TEXTURE/var.png",
	"data/TEXTURE/button.png",
	"data/TEXTURE/title_bg.png",
	"data/TEXTURE/number.png",
	"data/TEXTURE/costbox.png",
	"data/TEXTURE/arrow_right.png",
	"data/TEXTURE/t_confirm.png",
	"data/TEXTURE/t_day.png",
	"data/TEXTURE/t_powerup.png",
	"data/TEXTURE/t_start.png",
	"data/TEXTURE/t_levelup.png",
	"data/TEXTURE/t_cancel.png",
	"data/TEXTURE/var.png",
};
static char* g_CharTextureName[CH_TEXTURE_MAX] = {
	"data/TEXTURE/neutro.png",
	"data/TEXTURE/neutro.png",
	"data/TEXTURE/macro.png",
	"data/TEXTURE/thelper.png",
	"data/TEXTURE/tkiller.png",
	"data/TEXTURE/NK.png",
	"data/TEXTURE/kouen.png",

};
static char* g_IconTextureName[IC_TEXTURE_MAX] = {
	"data/TEXTURE/icon_cost.png",
	"data/TEXTURE/icon_life.png",
	"data/TEXTURE/icon_attack.png",
	"data/TEXTURE/icon_diffend.png",
	"data/TEXTURE/icon_block.png",
	"data/TEXTURE/icon_sp.png",
	"data/TEXTURE/icon_energy.png",
	"data/TEXTURE/icon_oxygen.png",
	"data/TEXTURE/icon_iron.png",
};
static char* g_SkillTextureName[SKILL_TEXTURE_MAX] = {
	"data/TEXTURE/var.png",
	"data/TEXTURE/var.png",
	"data/TEXTURE/var.png",
	"data/TEXTURE/var.png",
	"data/TEXTURE/var.png",
	"data/TEXTURE/var.png",
	"data/TEXTURE/var.png",

};

static Reserve g_Reserve;
static TEXT_TEXTURE g_text[TEXTURE_MAX];
static Button g_Button[BUTTON_MAX];
static Button g_PwButton[2];	//キャンセルとOKボタン
static int cursol;
static int cursolPw;	//パワーアップ画面に使われるカーソル
static int HelpTexNum = 0;	//ヘルプの画像枚数
static float cursolAlpha;	//カーソル透明度
static float alphaSpeed;	//カーソル透明度加算量
static BOOL g_Load = FALSE;
static BOOL restart = FALSE;
HRESULT InitReserve(void)
{
	//起動時、一度だけ初期化
	if (!restart)
	{
		g_Reserve.day = 1;
		g_Reserve.energy = 0;
		g_Reserve.oxygen = 0;
		g_Reserve.iron = 0;
		g_Reserve.mode = 99;
		g_Reserve.selectPw = 0;
		g_Reserve.pwMode = FALSE;
		restart = TRUE;
#ifdef _DEBUG
		g_Reserve.energy = 9999;
		g_Reserve.oxygen = 999;
		g_Reserve.iron = 9;
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
			&g_Texture[i],
			NULL);
	}
	// テクスチャ生成
	for (int i = 0; i < CHAR_TEXTURE_MAX; i++)
	{
		D3DX11CreateShaderResourceViewFromFile(GetDevice(),
			g_CharTextureName[i],
			NULL,
			NULL,
			&g_CharTexture[i],
			NULL);
	}
	for (int i = 0; i < IC_TEXTURE_MAX; i++)
	{
		D3DX11CreateShaderResourceViewFromFile(GetDevice(),
			g_IconTextureName[i],
			NULL,
			NULL,
			&g_IconTexture[i],
			NULL);
	}
	for (int i = 0; i < SKILL_TEXTURE_MAX; i++)
	{
		D3DX11CreateShaderResourceViewFromFile(GetDevice(),
			g_SkillTextureName[i],
			NULL,
			NULL,
			&g_SkillTexture[i],
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

	for (int i = 0; i < BUTTON_MAX; i++)
	{
		g_Button[i].color = { 1.0f, 1.0f, 1.0f, 1.0f };
		g_Button[i].pos = { 0.0f, 0.0f };
		g_Button[i].size = { 50.0f, 50.0f };
		g_Button[i].use = TRUE;
	}


	float py = BUTTON_SIZE * 0.5f + 16.0f;;
	
	g_Button[ReserveHelp].pos.x = 8.0f + BUTTON_SIZE * 1.5f;

	g_Button[GameStart].pos.y = SCREEN_HEIGHT - 40.0f - BUTTON_SIZE * 0.5f;
	g_Button[GameStart].pos.x = SCREEN_WIDTH - 16.0f - BUTTON_SIZE * 1.5f;

	g_PwButton[CanselButton].pos.y = SCREEN_HEIGHT * 0.6f;
	g_PwButton[CanselButton].pos.x = SCREEN_WIDTH * 0.8f;
	g_PwButton[CanselButton].color = { 0.2f, 0.2f, 0.2f, 1.0f };

	g_PwButton[LevelupButton].pos.y = SCREEN_HEIGHT * 0.75f;
	g_PwButton[LevelupButton].pos.x = SCREEN_WIDTH * 0.8f;
	g_PwButton[LevelupButton].color = { 0.0f, 0.5f, 1.0f, 1.0f };
	cursol = 0;
	cursolPw = 0;
	cursolAlpha = 0.5f;
	alphaSpeed = 0.02f;
	g_Load = TRUE;
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
		if (g_Texture[i])
		{
			g_Texture[i]->Release();
			g_Texture[i] = NULL;
		}
	}
	// テクスチャの解放
	for (int i = 0; i < CH_TEXTURE_MAX; i++)
	{
		if (g_CharTexture[i])
		{
			g_CharTexture[i]->Release();
			g_CharTexture[i] = NULL;
		}
	}
	// テクスチャの解放
	for (int i = 0; i < IC_TEXTURE_MAX; i++)
	{
		if (g_IconTexture[i])
		{
			g_IconTexture[i]->Release();
			g_IconTexture[i] = NULL;
		}
	}

	g_Load = FALSE;
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateReserve(void)
{
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
	

	SetDepthEnable(TRUE);

	// ライティングを無効
	SetLightEnable(TRUE);

}

Reserve *GetReserve(void) { return &g_Reserve; };

void DrawButton(XMFLOAT4 color, float px, float py, float sx, float sy)
{
	// テクスチャ設定
	GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[Button_tx]);

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
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[re_number]);

		// １枚のポリゴンの頂点とテクスチャ座標を設定
		SetSpriteColor(g_VertexBuffer, psx, py, sx, sy, tx, 0.0f, 0.1f, 1.0f,
			color);

		// ポリゴン描画
		GetDeviceContext()->Draw(4, 0);
		numb /= 10;
	}
}

void DrawTextReserve(int k, float px, float py, float sx, float sy, XMFLOAT4 color)	//引数に描画したいやつを入れる。
{
	// テクスチャ設定
	GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[k]);


	// １枚のポリゴンの頂点とテクスチャ座標を設定
	SetSpriteColor(g_VertexBuffer, px, py, sx, sy, 0.0f, 0.0f, 1.0f, 1.0f,color);

	// ポリゴン描画
	GetDeviceContext()->Draw(4, 0);

}

void NormalRserveMode(void)
{
	if (cursol < GameStart && GetKeyboardTrigger(DIK_DOWN)) {
		cursol++;
		PlaySound(SOUND_LABEL_SE_Select);
	}
	if (cursol > 0 && GetKeyboardTrigger(DIK_UP)) {
		cursol--;
		PlaySound(SOUND_LABEL_SE_Select);
	}
	//選択されているボタンを強調表示に
	for (int i = 0; i < BUTTON_MAX; i++)
	{
		if (i == cursol)
			g_Button[i].color = { 1.5f, 1.5f, 1.5f, 1.0f };
		else
			g_Button[i].color = { 0.5f, 0.5f, 0.5f, 1.0f };
	}

	//決定ボタンを押したらそれに応じて画面遷移
	if (GetKeyboardTrigger(DIK_RETURN)) {
		switch (cursol)
		{
		}
	}
}

void NormalRserveModeDraw(void)
{
	//背景描画
// テクスチャ設定
	GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[Reserve_bg]);

	// １枚のポリゴンの頂点とテクスチャ座標を設定
	SetSpriteColor(g_VertexBuffer, SCREEN_CENTER_X, SCREEN_CENTER_Y, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f,
		XMFLOAT4{ 1.0f, 1.0f, 1.0f, 1.0f });

	// ポリゴン描画
	GetDeviceContext()->Draw(4, 0);

	////ボタン描画(上に設置してあるやつから順に描画)
	DrawButton(g_Button[ReserveHelp].color, g_Button[ReserveHelp].pos.x, g_Button[ReserveHelp].pos.y, BUTTON_SIZE * 2.5f, BUTTON_SIZE);
	DrawTextReserve(TEXT_CONFIRM, g_Button[ReserveHelp].pos.x, g_Button[ReserveHelp].pos.y, BUTTON_SIZE * 2.0f, BUTTON_SIZE,
		XMFLOAT4{ 1.0f, 1.0f, 1.0f, 1.0f });

	DrawButton(g_Button[GameStart].color, g_Button[GameStart].pos.x, g_Button[GameStart].pos.y, BUTTON_SIZE * 2.5f, BUTTON_SIZE);
	DrawTextReserve(TEXT_START, g_Button[GameStart].pos.x, g_Button[GameStart].pos.y, BUTTON_SIZE * 2.0f, BUTTON_SIZE,
		XMFLOAT4{ 1.0f, 1.0f, 1.0f, 1.0f });

}