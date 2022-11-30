//=============================================================================
//
// �t�F�[�h���� [fade.h]
// Author : 
//
//=============================================================================
#pragma once


//*****************************************************************************
// �}�N����`
//*****************************************************************************

// �t�F�[�h�̏��
typedef enum
{
	FADE_NONE = 0,		// �����Ȃ����
	FADE_IN,			// �t�F�[�h�C������
	FADE_OUT,			// �t�F�[�h�A�E�g����
	FADE_BOX_IN,
	FADE_BOX_OUT,
	TRANSITION_CLOSE,
	TRANSITION_OPEN,
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
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitFade(void);
void UninitFade(void);
void UpdateFade(void);
void DrawFade(void);

void SetFade(FADE fade, int modeNext, int texNo);
FADE GetFade(void);
int FadeOutBoxFunc(int i, int k);
int FadeInBoxFunc(int i, int k);