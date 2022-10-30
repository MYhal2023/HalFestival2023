//=============================================================================
//
// フェード処理 [fade.h]
// Author : 
//
//=============================================================================
#pragma once


//*****************************************************************************
// マクロ定義
//*****************************************************************************

// フェードの状態
typedef enum
{
	FADE_NONE = 0,		// 何もない状態
	FADE_IN,			// フェードイン処理
	FADE_OUT,			// フェードアウト処理
	FADE_BOX_IN,
	FADE_BOX_OUT,
	FADE_MAX
} FADE;

enum FadeTexture
{
	WhiteBox,
};

struct FadeBox
{
	XMFLOAT2 pos;
	float size;
	XMFLOAT4 color;
};
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitFade(void);
void UninitFade(void);
void UpdateFade(void);
void DrawFade(void);

void SetFade(FADE fade, int modeNext, int texNo);
FADE GetFade(void);
int FadeOutBoxFunc(int i, int k);
int FadeInBoxFunc(int i, int k);