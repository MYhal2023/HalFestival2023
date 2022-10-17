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
	BOOL use;		//���̉摜��\�����邩
};

enum OVER_TEXT
{
	FadeRed,
	Hazard,
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