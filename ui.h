//=============================================================================
//
// UIèàóù [ui.h]
// Author : 
//
//=============================================================================
#pragma once
#include "rescueLife.h"

class UI
{
public:
	XMFLOAT4 color;
	XMFLOAT2 pos;
	XMFLOAT2 size;
	XMFLOAT2 tex;
	BOOL use;
	ID3D11ShaderResourceView	*g_Texture;
};

enum UI_TEXTURE
{
	var_bg,
	hp_box,
	hp_var,
	hp_var_bg,
	rescue_ng,
	rescue_ok,
	check_mark,
	arm_UI_slot,
	number,
	UI_MAX,
};


HRESULT InitUI(void);
void UninitUI(void);
void UpdateUI(void);
void DrawUI(void);
void DrawUIbg(void);
void DrawNumber(int numb, float px, float py, float sx, float sy, XMFLOAT4 color);
void DrawTexture(UI* utp);
void DrawRescueLife(RescueLife* rlp);
void DrawButtonNorD(void);
void DrawButtonStop(void);
void DrawHelpButton(void);
void SetHelpButton(BOOL flag); 
BOOL GetHelpButton(void);
