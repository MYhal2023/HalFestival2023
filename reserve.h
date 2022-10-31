//=============================================================================
//
// 育成画面処理 [reserve.h]
// Author : 
//
//=============================================================================
#pragma once

class Reserve
{
public:
	int mode;	//ボタンを押した時の画面変化に使う
};

class Button
{
public:
	XMFLOAT4 color;
	XMFLOAT2 pos;
	XMFLOAT2 size;
	int texNo;
	BOOL use;
	BOOL cursol;	//選択されているか
	ID3D11ShaderResourceView		*g_Texture;
};

enum ButtonType
{
	ReserveHelp,
	GameStart,
};


//ヘルプ画像は連続させる
enum Reserve_TEXTURE
{
	rs_vigilance,	//警戒度
	rs_rank,		//プレイヤーのランク
	rs_start,		//スタートボタン
	rs_Button_tx,	//ボタン下地
	rs_number,		//数字テクスチャ
	RESERVE_TEXTURE_MAX

};
enum Icon_TEXTURE
{
	icCost,
	icLife,
	icAttack,
	icDiffend,
	icBlock,
	icSp,
	icEnergy,
	icOxygen,
	icIron,
};


HRESULT InitReserve(void);
void UninitReserve(void);
void UpdateReserve(void);
void DrawReserve(void);
Reserve *GetReserve(void);
void DrawButton(XMFLOAT4 color, float px, float py, float sx, float sy);
void DrawNumberRe(int numb, float px, float py, float sx, float sy, XMFLOAT4 color);
void DrawTexture(Button* bt);