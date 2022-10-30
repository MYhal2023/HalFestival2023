//=============================================================================
//
// タイトル処理 [title.h]
// Author : 
//
//=============================================================================
#pragma once
struct Title
{
	XMFLOAT4 color;
	XMFLOAT2 pos;
	XMFLOAT2 size;
	int textNo;
	ID3D11ShaderResourceView		*g_Texture = NULL;	// テクスチャ情報

};


enum TitleTexture
{
	title_bg,
	title_logo,
	title_start,
	title_score,
	title_option,
	title_finish,
	title_cursol,
	TITLE_TEXTURE_MAX,
};

HRESULT InitTitle(void);
void UninitTitle(void);
void UpdateTitle(void);
void DrawTitle(void);
void FadeTexture(int type, Title *title);
void MoveTexture(float speed, Title *title);
void DrawTexture(Title* title);