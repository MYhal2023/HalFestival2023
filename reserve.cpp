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

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_MAX			(13)				// �e�N�X�`���̐�
#define CH_TEXTURE_MAX		(7)				// �L�����e�N�X�`���̐�
#define IC_TEXTURE_MAX		(9)				// �A�C�R���e�N�X�`���̐�
#define CHAR_TEXTURE_MAX	(7)				// �L�����e�N�X�`���̐�
#define SKILL_TEXTURE_MAX	(7)				// �L�����X�L���e�N�X�`���̐�
#define NUMBER_SIZE			(30.0f)			// x�����̃T�C�Y
#define COST_NUMBER_SIZE	(45.0f)			// x�����̃T�C�Y
#define BUTTON_SIZE			(106.0f)		// �{�^���̏c���T�C�Y�B�������ꂭ�炢
#define BUTTON_MAX			(4)				// ���[�T�[���I���ł���{�^����
#define ROW_NUM				(5)				// ���ɕ��ׂ郆�j�b�g��
#define HELP_TEX_NUM		(1)				// ���ɕ��ׂ郆�j�b�g��

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static ID3D11Buffer					*g_VertexBuffer = NULL;	// ���_���
static ID3D11ShaderResourceView		*g_Texture[TEXTURE_MAX] = { NULL };	// �e�N�X�`�����
static ID3D11ShaderResourceView		*g_CharTexture[CHAR_TEXTURE_MAX] = { NULL };	// �e�N�X�`�����
static ID3D11ShaderResourceView		*g_IconTexture[IC_TEXTURE_MAX] = { NULL };	// �e�N�X�`�����
static ID3D11ShaderResourceView		*g_SkillTexture[SKILL_TEXTURE_MAX] = { NULL };	// �e�N�X�`�����

static char* g_TextureName[TEXTURE_MAX] = {
	"data/TEXTURE/var.png",
	"data/TEXTURE/button.png",
	"data/TEXTURE/title_bg.png",
	"data/TEXTURE/number.png",
	"data/TEXTURE/costbox.png",
	"data/TEXTURE/arrow_right.png",
	"data/TEXTURE/t_confirm.png",
	"data/TEXTURE/t_day.png",
	"data/TEXTURE/t_powerup.png",
	"data/TEXTURE/t_start.png",
	"data/TEXTURE/t_levelup.png",
	"data/TEXTURE/t_cancel.png",
	"data/TEXTURE/var.png",
};
static char* g_CharTextureName[CH_TEXTURE_MAX] = {
	"data/TEXTURE/neutro.png",
	"data/TEXTURE/neutro.png",
	"data/TEXTURE/macro.png",
	"data/TEXTURE/thelper.png",
	"data/TEXTURE/tkiller.png",
	"data/TEXTURE/NK.png",
	"data/TEXTURE/kouen.png",

};
static char* g_IconTextureName[IC_TEXTURE_MAX] = {
	"data/TEXTURE/icon_cost.png",
	"data/TEXTURE/icon_life.png",
	"data/TEXTURE/icon_attack.png",
	"data/TEXTURE/icon_diffend.png",
	"data/TEXTURE/icon_block.png",
	"data/TEXTURE/icon_sp.png",
	"data/TEXTURE/icon_energy.png",
	"data/TEXTURE/icon_oxygen.png",
	"data/TEXTURE/icon_iron.png",
};
static char* g_SkillTextureName[SKILL_TEXTURE_MAX] = {
	"data/TEXTURE/var.png",
	"data/TEXTURE/var.png",
	"data/TEXTURE/var.png",
	"data/TEXTURE/var.png",
	"data/TEXTURE/var.png",
	"data/TEXTURE/var.png",
	"data/TEXTURE/var.png",

};

static Reserve g_Reserve;
static TEXT_TEXTURE g_text[TEXTURE_MAX];
static Button g_Button[BUTTON_MAX];
static Button g_PwButton[2];	//�L�����Z����OK�{�^��
static int cursol;
static int cursolPw;	//�p���[�A�b�v��ʂɎg����J�[�\��
static int HelpTexNum = 0;	//�w���v�̉摜����
static float cursolAlpha;	//�J�[�\�������x
static float alphaSpeed;	//�J�[�\�������x���Z��
static BOOL g_Load = FALSE;
static BOOL restart = FALSE;
HRESULT InitReserve(void)
{
	//�N�����A��x����������
	if (!restart)
	{
		g_Reserve.day = 1;
		g_Reserve.energy = 0;
		g_Reserve.oxygen = 0;
		g_Reserve.iron = 0;
		g_Reserve.mode = 99;
		g_Reserve.selectPw = 0;
		g_Reserve.pwMode = FALSE;
		restart = TRUE;
#ifdef _DEBUG
		g_Reserve.energy = 9999;
		g_Reserve.oxygen = 999;
		g_Reserve.iron = 9;
#endif
	}

	ID3D11Device *pDevice = GetDevice();

	// �e�N�X�`������
	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		D3DX11CreateShaderResourceViewFromFile(GetDevice(),
			g_TextureName[i],
			NULL,
			NULL,
			&g_Texture[i],
			NULL);
	}
	// �e�N�X�`������
	for (int i = 0; i < CHAR_TEXTURE_MAX; i++)
	{
		D3DX11CreateShaderResourceViewFromFile(GetDevice(),
			g_CharTextureName[i],
			NULL,
			NULL,
			&g_CharTexture[i],
			NULL);
	}
	for (int i = 0; i < IC_TEXTURE_MAX; i++)
	{
		D3DX11CreateShaderResourceViewFromFile(GetDevice(),
			g_IconTextureName[i],
			NULL,
			NULL,
			&g_IconTexture[i],
			NULL);
	}
	for (int i = 0; i < SKILL_TEXTURE_MAX; i++)
	{
		D3DX11CreateShaderResourceViewFromFile(GetDevice(),
			g_SkillTextureName[i],
			NULL,
			NULL,
			&g_SkillTexture[i],
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

	for (int i = 0; i < BUTTON_MAX; i++)
	{
		g_Button[i].color = { 1.0f, 1.0f, 1.0f, 1.0f };
		g_Button[i].pos = { 0.0f, 0.0f };
		g_Button[i].size = { 50.0f, 50.0f };
		g_Button[i].use = TRUE;
	}


	float py = BUTTON_SIZE * 0.5f + 16.0f;;
	
	g_Button[ReserveHelp].pos.x = 8.0f + BUTTON_SIZE * 1.5f;

	g_Button[GameStart].pos.y = SCREEN_HEIGHT - 40.0f - BUTTON_SIZE * 0.5f;
	g_Button[GameStart].pos.x = SCREEN_WIDTH - 16.0f - BUTTON_SIZE * 1.5f;

	g_PwButton[CanselButton].pos.y = SCREEN_HEIGHT * 0.6f;
	g_PwButton[CanselButton].pos.x = SCREEN_WIDTH * 0.8f;
	g_PwButton[CanselButton].color = { 0.2f, 0.2f, 0.2f, 1.0f };

	g_PwButton[LevelupButton].pos.y = SCREEN_HEIGHT * 0.75f;
	g_PwButton[LevelupButton].pos.x = SCREEN_WIDTH * 0.8f;
	g_PwButton[LevelupButton].color = { 0.0f, 0.5f, 1.0f, 1.0f };
	cursol = 0;
	cursolPw = 0;
	cursolAlpha = 0.5f;
	alphaSpeed = 0.02f;
	g_Load = TRUE;
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
		if (g_Texture[i])
		{
			g_Texture[i]->Release();
			g_Texture[i] = NULL;
		}
	}
	// �e�N�X�`���̉��
	for (int i = 0; i < CH_TEXTURE_MAX; i++)
	{
		if (g_CharTexture[i])
		{
			g_CharTexture[i]->Release();
			g_CharTexture[i] = NULL;
		}
	}
	// �e�N�X�`���̉��
	for (int i = 0; i < IC_TEXTURE_MAX; i++)
	{
		if (g_IconTexture[i])
		{
			g_IconTexture[i]->Release();
			g_IconTexture[i] = NULL;
		}
	}

	g_Load = FALSE;
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateReserve(void)
{
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
	

	SetDepthEnable(TRUE);

	// ���C�e�B���O�𖳌�
	SetLightEnable(TRUE);

}

Reserve *GetReserve(void) { return &g_Reserve; };

void DrawButton(XMFLOAT4 color, float px, float py, float sx, float sy)
{
	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[Button_tx]);

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
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[re_number]);

		// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
		SetSpriteColor(g_VertexBuffer, psx, py, sx, sy, tx, 0.0f, 0.1f, 1.0f,
			color);

		// �|���S���`��
		GetDeviceContext()->Draw(4, 0);
		numb /= 10;
	}
}

void DrawTextReserve(int k, float px, float py, float sx, float sy, XMFLOAT4 color)	//�����ɕ`�悵�����������B
{
	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[k]);


	// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
	SetSpriteColor(g_VertexBuffer, px, py, sx, sy, 0.0f, 0.0f, 1.0f, 1.0f,color);

	// �|���S���`��
	GetDeviceContext()->Draw(4, 0);

}

void NormalRserveMode(void)
{
	if (cursol < GameStart && GetKeyboardTrigger(DIK_DOWN)) {
		cursol++;
		PlaySound(SOUND_LABEL_SE_Select);
	}
	if (cursol > 0 && GetKeyboardTrigger(DIK_UP)) {
		cursol--;
		PlaySound(SOUND_LABEL_SE_Select);
	}
	//�I������Ă���{�^���������\����
	for (int i = 0; i < BUTTON_MAX; i++)
	{
		if (i == cursol)
			g_Button[i].color = { 1.5f, 1.5f, 1.5f, 1.0f };
		else
			g_Button[i].color = { 0.5f, 0.5f, 0.5f, 1.0f };
	}

	//����{�^�����������炻��ɉ����ĉ�ʑJ��
	if (GetKeyboardTrigger(DIK_RETURN)) {
		switch (cursol)
		{
		}
	}
}

void NormalRserveModeDraw(void)
{
	//�w�i�`��
// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[Reserve_bg]);

	// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
	SetSpriteColor(g_VertexBuffer, SCREEN_CENTER_X, SCREEN_CENTER_Y, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f,
		XMFLOAT4{ 1.0f, 1.0f, 1.0f, 1.0f });

	// �|���S���`��
	GetDeviceContext()->Draw(4, 0);

	////�{�^���`��(��ɐݒu���Ă������珇�ɕ`��)
	DrawButton(g_Button[ReserveHelp].color, g_Button[ReserveHelp].pos.x, g_Button[ReserveHelp].pos.y, BUTTON_SIZE * 2.5f, BUTTON_SIZE);
	DrawTextReserve(TEXT_CONFIRM, g_Button[ReserveHelp].pos.x, g_Button[ReserveHelp].pos.y, BUTTON_SIZE * 2.0f, BUTTON_SIZE,
		XMFLOAT4{ 1.0f, 1.0f, 1.0f, 1.0f });

	DrawButton(g_Button[GameStart].color, g_Button[GameStart].pos.x, g_Button[GameStart].pos.y, BUTTON_SIZE * 2.5f, BUTTON_SIZE);
	DrawTextReserve(TEXT_START, g_Button[GameStart].pos.x, g_Button[GameStart].pos.y, BUTTON_SIZE * 2.0f, BUTTON_SIZE,
		XMFLOAT4{ 1.0f, 1.0f, 1.0f, 1.0f });

}