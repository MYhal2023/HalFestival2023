//=============================================================================
//
// �琬��ʏ��� [reserve.h]
// Author : 
//
//=============================================================================
#pragma once
#define BASE_RESCUE_NUM (2)
class Reserve
{
public:
	float vigilance;	//�x���x
	float old_vigi;		//�O��v���C���̌x���x
	int quota;		//�m���}�~���Ґ�
	int rank;			//���݃����N�B�����100�ŏ������ۂ̏��Ō��݃����N��\������
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


enum Reserve_TEXTURE
{
	rs_vigilance,	//�x���x
	rs_rank,		//�v���C���[�̃����N
	rs_start,		//�X�^�[�g�{�^��
	rs_Button_tx,	//�{�^�����n
	rs_number,		//�����e�N�X�`��
	rs_number_w,
	rs_xpvar_bg,
	rs_xpvar,
	rs_rank_0,
	rs_rank_1,
	rs_rank_2,
	rs_rank_3,
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