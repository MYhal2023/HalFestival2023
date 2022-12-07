//=============================================================================
//
// Reserve���� [ui.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "sprite.h"
#include "renderer.h"
#include "game.h"
#include "reserve.h"
#include "ui.h"
#include "text_texture.h"
#include "fade.h"
#include "debugproc.h"
#include "sound.h"
#include "input.h"
#include "easing.h"
#include "file.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_MAX			(RESERVE_TEXTURE_MAX)				// �e�N�X�`���̐�
#define NUMBER_SIZE			(30.0f)			// x�����̃T�C�Y
#define COST_NUMBER_SIZE	(45.0f)			// x�����̃T�C�Y
#define BUTTON_SIZE			(106.0f)		// �{�^���̏c���T�C�Y�B�������ꂭ�炢
#define ROW_NUM				(5)				// ���ɕ��ׂ郆�j�b�g��
#define HELP_TEX_NUM		(1)				// ���ɕ��ׂ郆�j�b�g��

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static ID3D11Buffer					*g_VertexBuffer = NULL;	// ���_���

static char* g_TextureName[TEXTURE_MAX] = {
	"data/TEXTURE/keikaiji.png",
	"data/TEXTURE/var.png",
	"data/TEXTURE/t_startbutton.png",
	"data/TEXTURE/var.png",
	"data/TEXTURE/number.png",
	"data/TEXTURE/numbers_w.png",
	"data/TEXTURE/xpbar_mae.png",
	"data/TEXTURE/xpbar_iro.png",
	"data/TEXTURE/rank_0.png",
	"data/TEXTURE/rank_1.png",
	"data/TEXTURE/rank_2.png",
	"data/TEXTURE/rank_3.png",
};

static Reserve g_Reserve;
static TEXT_TEXTURE g_text[TEXTURE_MAX];
static Button g_Button[TEXTURE_MAX];
static int cursol;
static int HelpTexNum = 0;	//�w���v�̉摜����
static float cursolAlpha;	//�J�[�\�������x
static float alphaSpeed;	//�J�[�\�������x���Z��
static BOOL g_Load = FALSE;
static BOOL restart = FALSE;
static BOOL once = FALSE;
HRESULT InitReserve(void)
{
	//�N�����A��x����������
	if (!restart)
	{
		restart = TRUE;
		g_Reserve.vigilance = 0.0f;
		g_Reserve.old_vigi = 0.0f;
		g_Reserve.quota = BASE_RESCUE_NUM;
		g_Reserve.rank = 0;

		LoadData();
	}
	ID3D11Device *pDevice = GetDevice();

	// �e�N�X�`������
	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		D3DX11CreateShaderResourceViewFromFile(GetDevice(),
			g_TextureName[i],
			NULL,
			NULL,
			&g_Button[i].g_Texture,
			NULL);
	}

	// ���_�o�b�t�@����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	GetDevice()->CreateBuffer(&bd, NULL, &g_VertexBuffer);

	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		g_Button[i].color = { 1.0f, 1.0f, 1.0f, 1.0f };
		g_Button[i].pos = { 0.0f, 0.0f };
		g_Button[i].size = { 50.0f, 50.0f };
		g_Button[i].use = TRUE;
	}

	g_Button[rs_vigilance].pos = { SCREEN_WIDTH * 0.70f , SCREEN_HEIGHT * 0.2f };
	g_Button[rs_vigilance].size = { 100.0f * 4.0f , 100.0f * 1.0f };

	g_Button[rs_rank].pos = { SCREEN_WIDTH * 0.75f , SCREEN_HEIGHT * 0.60f };
	g_Button[rs_rank].size = { 100.0f * 3.0f , 100.0f * 1.0f };

	g_Button[rs_start].pos = { SCREEN_WIDTH * 0.80f , SCREEN_HEIGHT * 0.80f };
	g_Button[rs_start].size = { 100.0f * 3.0f , 100.0f * 2.0f };

	//�x���x�Z�o
	int base = (int)((float)(g_Reserve.rank) *0.01f);
	if (g_Reserve.vigilance >= ((float)(base)+ 1.0f) * 30.0f)
		g_Reserve.vigilance = ((float)(base) + 1.0f) * 30.0f;
	else if(g_Reserve.vigilance < ((float)(base)) * 30.0f)
		g_Reserve.vigilance = (float)(base) * 30.0f;

	//�x���x�ɂ�����ƃ����_��������������
	g_Reserve.vigilance += rand() % 6;

	//�m���}�~���Ґ��̎Z�o
	int quota_base = (int)((g_Reserve.vigilance) / 15.0f);
	g_Reserve.quota = BASE_RESCUE_NUM + quota_base;
	cursol = 0;
	cursolAlpha = 0.5f;
	alphaSpeed = 0.02f;
	g_Load = TRUE;
	once = FALSE;
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitReserve(void)
{
	if (g_Load == FALSE) return;

	// ���_�o�b�t�@�̉��
	if (g_VertexBuffer)
	{
		g_VertexBuffer->Release();
		g_VertexBuffer = NULL;
	}

	// �e�N�X�`���̉��
	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		if (g_Button[i].g_Texture)
		{
			g_Button[i].g_Texture->Release();
			g_Button[i].g_Texture = NULL;
		}
	}

	g_Load = FALSE;
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateReserve(void)
{
	if (GetKeyboardTrigger(DIK_RETURN) || IsButtonTriggered(0, BUTTON_C))
	{
		SetFade(FADE_BOX_OUT, MODE_GAME, WhiteBox);
		PlaySound(SOUND_LABEL_SE_decision);
	}
	if (!once)
	{
		g_Button[rs_start].nIndex = Easing::SetEase(SCREEN_HEIGHT * 0.0f, SCREEN_HEIGHT * 0.4f, 100.0f);
		g_Button[rs_rank_0].nIndex = Easing::SetEase(SCREEN_HEIGHT * 0.0f, SCREEN_HEIGHT * 0.9f, 80.0f);
		g_Button[rs_vigilance].nIndex = Easing::SetEase(SCREEN_HEIGHT * 0.0f, SCREEN_HEIGHT * 0.9f, 60.0f);
		g_Button[rs_xpvar_bg].nIndex = Easing::SetEase(SCREEN_HEIGHT * 0.0f, SCREEN_HEIGHT * 0.9f, 80.0f);
		g_Button[rs_xpvar].nIndex = Easing::SetEase(SCREEN_HEIGHT * 0.0f, SCREEN_HEIGHT * 0.9f, 80.0f);
		once = TRUE;
	}
	g_Button[rs_start].set_pos.y = Easing::GetEase(g_Button[rs_start].nIndex);
	g_Button[rs_rank_0].set_pos.x = Easing::GetEase(g_Button[rs_rank_0].nIndex);
	g_Button[rs_vigilance].set_pos.x = Easing::GetEase(g_Button[rs_vigilance].nIndex);
	g_Button[rs_xpvar_bg].set_pos.x = Easing::GetEase(g_Button[rs_xpvar_bg].nIndex);
	g_Button[rs_xpvar].set_pos.x = Easing::GetEase(g_Button[rs_xpvar].nIndex);
}

//=============================================================================
// �`�揈�� �����ɑS�������Ă���̂Œ��_�o�b�t�@�ݒ蓙�͌X�ł���Ȃ�
//=============================================================================
void DrawReserve(void)
{
	SetDepthEnable(FALSE);

	// ���C�e�B���O�𖳌�
	SetLightEnable(FALSE);
	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �}�g���N�X�ݒ�
	SetWorldViewProjection2D();

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �}�e���A���ݒ�
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	SetMaterial(material);
	
	g_Button[rs_start].pos = { SCREEN_WIDTH * 0.8f, SCREEN_HEIGHT * 1.2f - g_Button[rs_start].set_pos.y };
	g_Button[rs_start].size = { 530 * 0.9f, 100 * 1.0f };
	g_Button[rs_start].color = { 1.0f, 1.0f, 1.0f, 1.0f };
	DrawTexture(&g_Button[rs_start]);


	g_Button[rs_vigilance].pos = { SCREEN_WIDTH * 1.2f - g_Button[rs_vigilance].set_pos.x, SCREEN_HEIGHT * 0.25f };
	g_Button[rs_vigilance].size = { 530 * 0.9f, 100 * 1.2f };
	g_Button[rs_vigilance].color = { 1.0f, 1.0f, 1.0f, 1.0f };
	DrawTexture(&g_Button[rs_vigilance]);
	DrawNumberRe((int)(g_Reserve.vigilance), g_Button[rs_vigilance].pos.x + 80.0f, g_Button[rs_vigilance].pos.y, 50.0f, 100.0f, XMFLOAT4(1.0f, 0.4f, 0.4f, 1.0f));

	g_Button[rs_rank].pos = { SCREEN_WIDTH * 1.2f - g_Button[rs_rank].set_pos.x , SCREEN_HEIGHT * 0.55f};
	g_Button[rs_rank].size = { 530 * 0.9f, 100 * 1.0f };
	g_Button[rs_rank].color = { 1.0f, 1.0f, 1.0f, 1.0f };
	DrawTexture(&g_Button[rs_rank]);

	int rank = rs_rank_0 + (g_Reserve.rank /100);
	if (rank > rs_rank_3) {
		rank = rs_rank_3;
	}
	g_Button[rank].pos = { SCREEN_WIDTH * 1.25f - g_Button[rs_rank_0].set_pos.x , SCREEN_HEIGHT * 0.55f };
	g_Button[rank].size = { 1900.0f * 0.75f * 0.5f, 800.0f *0.75f*0.5f };
	g_Button[rank].color = { 1.0f, 1.0f, 1.0f, 1.0f };
	DrawTexture(&g_Button[rank]);

	g_Button[rs_xpvar_bg].pos = { SCREEN_WIDTH * 1.25f - g_Button[rs_rank_0].set_pos.x , SCREEN_HEIGHT * 0.55f };
	g_Button[rs_xpvar_bg].size = { 810.0f * 0.75f, 80.0f *0.75f};
	g_Button[rs_xpvar_bg].color = { 1.0f, 1.0f, 1.0f, 1.0f };
	DrawTexture(&g_Button[rs_xpvar_bg]);

	float par = (float)(g_Reserve.rank % 100) / 100.0f;
	if (g_Reserve.rank > 300)par = 1.0f;
	g_Button[rs_xpvar].size = { 800.0f *0.75f* par , 72.0f *0.75f};
	g_Button[rs_xpvar].pos = { (SCREEN_WIDTH * 1.25f - g_Button[rs_xpvar].set_pos.x) + (800.0f *0.75f * (par - 1.0f)) * 0.5f, SCREEN_HEIGHT * 0.55f };
	g_Button[rs_xpvar].color = { 1.0f, 1.0f, 1.0f, 1.0f };
	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, &g_Button[rs_xpvar].g_Texture);

	// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
	SetSpriteColor(g_VertexBuffer, g_Button[rs_xpvar].pos.x, g_Button[rs_xpvar].pos.y, g_Button[rs_xpvar].size.x, g_Button[rs_xpvar].size.y, 0.0f, 0.0f, 1.0f, 1.0f,
		g_Button[rs_xpvar].color);

	// �|���S���`��
	GetDeviceContext()->Draw(4, 0);

	SetDepthEnable(TRUE);

	// ���C�e�B���O�𖳌�
	SetLightEnable(TRUE);

}

Reserve *GetReserve(void) { return &g_Reserve; };

void DrawButton(XMFLOAT4 color, float px, float py, float sx, float sy)
{
	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, &g_Button[rs_Button_tx].g_Texture);

	// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
	SetSpriteColor(g_VertexBuffer, px, py, sx, sy, 0.0f, 0.0f, 1.0f, 1.0f,
		color);

	// �|���S���`��
	GetDeviceContext()->Draw(4, 0);

}
//����:�\�������������A�\�����W(x,y)�A�\���T�C�Y(x����,y����)
void DrawNumberRe(int numb, float px, float py, float sx, float sy, XMFLOAT4 color)
{
	int digit = 0;
	int clock = numb;
	if (clock != 0)
	{
		while (clock != 0)
		{
			clock /= 10;
			digit++;
		}
	}
	else
		digit = 1;

	float psx = px + sx * digit;
	for (int i = 0; i < digit; i++)
	{
		psx -= sx;
		float x = (float)(numb % 10);		//����\�����鐔��
		float tx = x * 0.1f;			// �e�N�X�`���̍���X���W

		// �e�N�X�`���ݒ�
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Button[rs_number_w].g_Texture);

		// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
		SetSpriteColor(g_VertexBuffer, psx, py, sx, sy, tx, 0.0f, 0.1f, 1.0f,
			color);

		// �|���S���`��
		GetDeviceContext()->Draw(4, 0);
		numb /= 10;
	}
}

void DrawTexture(Button* bt)
{
	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, &bt->g_Texture);

	// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
	SetSpriteColor(g_VertexBuffer, bt->pos.x, bt->pos.y, bt->size.x, bt->size.y, 0.0f, 0.0f, 1.0f, 1.0f,
		bt->color);

	// �|���S���`��
	GetDeviceContext()->Draw(4, 0);
}

void SetRank(int data)
{
	g_Reserve.rank = data;
}

int GetRank(void)
{
	return g_Reserve.rank;
}
