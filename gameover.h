//=============================================================================
//
// ゲームオーバー処理 [gameover.h]
// Author : 
//
//=============================================================================
#pragma once
#include "main.h"

class Over
{
public:
	XMFLOAT4 color;	//引き渡す色情報
	XMFLOAT2 pos;	//表示座標
	XMFLOAT2 size;	//表示座標
	int nIndex_x;
	int nIndex_y;
	int nIndex_alpha_x;
	int nIndex_alpha_y;
	float minus_alpha;		//減算用α値
	BOOL use;		//この画像を表示するか
	ID3D11ShaderResourceView		*g_Texture;
};

enum OVER_TEXT
{
	ov_FadeRed,
	ov_Hazard,
	ov_Clear,
	ov_numb,
	ov_danger,
	ov_var,
	MAX_OVER_TEXTURE
};

enum OVER_TYPE
{
	OVER_WIN,
	OVER_LOSE,
};
HRESULT InitOver(void);
void UninitOver(void);
void UpdateOver(void);
void DrawOver(void);
void SetOverType(int type);	//ゲームオーバータイプのセット
int GetOverType(void);	//ゲームオーバータイプを取得
void DrawOverTexture(Over* ov, float sx, float fx);
void DrawOverNumber(int numb, float px, float py, float sx, float sy, XMFLOAT4 color);