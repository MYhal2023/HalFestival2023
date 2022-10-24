//=============================================================================
//
// UIèàóù [ui.h]
// Author : 
//
//=============================================================================
#pragma once

class UI
{
public:
	XMFLOAT4 color;
	XMFLOAT2 pos;
	XMFLOAT2 size;
	BOOL use;
};

enum UI_TEXTURE
{
	var_bg,
	number,
	UI_MAX,
};


HRESULT InitUI(void);
void UninitUI(void);
void UpdateUI(void);
void DrawUI(void);
void DrawUIbg(void);
void DrawNumber(int numb, float px, float py, float sx, float sy, XMFLOAT4 color);
void DrawButtonNorD(void);
void DrawButtonStop(void);
void DrawHelpButton(void);
void SetHelpButton(BOOL flag); 
BOOL GetHelpButton(void);
