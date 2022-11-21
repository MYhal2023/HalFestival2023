//=============================================================================
//
// �琬��ʏ��� [reserve.h]
// Author : 
//
//=============================================================================
#pragma once

class Reserve
{
public:
	int mode;	//�{�^�������������̉�ʕω��Ɏg��
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
	BOOL cursol;	//�I������Ă��邩
	ID3D11ShaderResourceView		*g_Texture;
};

enum ButtonType
{
	ReserveHelp,
	GameStart,
};


//�w���v�摜�͘A��������
enum Reserve_TEXTURE
{
	rs_vigilance,	//�x���x
	rs_rank,		//�v���C���[�̃����N
	rs_start,		//�X�^�[�g�{�^��
	rs_Button_tx,	//�{�^�����n
	rs_number,		//�����e�N�X�`��
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