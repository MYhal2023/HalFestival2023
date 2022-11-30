//=============================================================================
//
// 育成画面処理 [reserve.h]
// Author : 
//
//=============================================================================
#pragma once
#define BASE_RESCUE_NUM (2)
class Reserve
{
public:
	float vigilance;	//警戒度
	float old_vigi;		//前回プレイ時の警戒度
	int quota;		//ノルマ救助者数
	int rank;			//現在ランク。これを100で除した際の商で現在ランクを表示する
};

class Button
{
public:
	XMFLOAT4 color;
	XMFLOAT2 pos;
	XMFLOAT2 size;
	XMFLOAT2 set_pos;
	int	nIndex;
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
	rs_number_w,
	RESERVE_TEXTURE_MAX

};


HRESULT InitReserve(void);
void UninitReserve(void);
void UpdateReserve(void);
void DrawReserve(void);
Reserve *GetReserve(void);
void DrawButton(XMFLOAT4 color, float px, float py, float sx, float sy);
void DrawNumberRe(int numb, float px, float py, float sx, float sy, XMFLOAT4 color);
void DrawTexture(Button* bt);