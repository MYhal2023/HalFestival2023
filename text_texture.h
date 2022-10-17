//=============================================================================
//
// �����e�N�X�`�����̕\������ [text_texture.h]
// Author : 
//
//=============================================================================
#pragma once

//*****************************************************************************
// �}�N����`
//*****************************************************************************
enum TEXT_TEXTURE_NUM
{
	TEXT_GAMEOVER,
	TEXT_WIN_RESULT,
};

struct TEXT_TEXTURE
{
	XMFLOAT3	pos;						// �|���S���̈ʒu
	XMFLOAT4	color;						//�F
	int			TexNo;						//�e�N�X�`���ԍ�
	int			time;						//�\�����Ԃ̃J�E���g�p�ϐ�
	int			timeMax;					//�\������
	float		w, h, tw, th, tx, ty;		// ���ƍ����A�e�N�X�`�����W
	int			type;
	BOOL		use;
};
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitTexttex(void);
void UninitTexttex(void);
void UpdateTexttex(void);
void DrawTexttex(void);
void DrawTexttChose(int k);
void SetText(int i, int type, XMFLOAT3 pos);
void SetTextpos(int i, XMFLOAT3 pos);