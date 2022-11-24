//=============================================================================
//
// �Q�[���I�[�o�[���� [gameover.h]
// Author : 
//
//=============================================================================
#pragma once
#include "main.h"

class Over
{
public:
	XMFLOAT4 color;	//�����n���F���
	XMFLOAT2 pos;	//�\�����W
	XMFLOAT2 size;	//�\�����W
	int nIndex_x;
	int nIndex_y;
	int nIndex_alpha_x;
	int nIndex_alpha_y;
	float minus_alpha;		//���Z�p���l
	BOOL use;		//���̉摜��\�����邩
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
void SetOverType(int type);	//�Q�[���I�[�o�[�^�C�v�̃Z�b�g
int GetOverType(void);	//�Q�[���I�[�o�[�^�C�v���擾
void DrawOverTexture(Over* ov, float sx, float fx);
void DrawOverNumber(int numb, float px, float py, float sx, float sy, XMFLOAT4 color);