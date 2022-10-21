//=============================================================================
//
// UI���� [ui.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "sprite.h"
#include "renderer.h"
#include "game.h"
#include "ui.h"
#include "reserve.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_MAX			(19)				// �e�N�X�`���̐�
#define CHAR_TEXTURE_MAX	(7)				// �L�����e�N�X�`���̐�
#define IC_TEXTURE_MAX		(9)				// �A�C�R���e�N�X�`���̐�
#define NUMBER_SIZE			(30.0f)			// x�����̃T�C�Y
#define COST_NUMBER_SIZE	(45.0f)			// x�����̃T�C�Y

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static ID3D11Buffer					*g_VertexBuffer = NULL;	// ���_���
static ID3D11ShaderResourceView		*g_Texture[TEXTURE_MAX] = { NULL };	// �e�N�X�`�����
static ID3D11ShaderResourceView		*g_CharTexture[CHAR_TEXTURE_MAX] = { NULL };	// �e�N�X�`�����
static ID3D11ShaderResourceView		*g_IconTexture[IC_TEXTURE_MAX] = { NULL };	// �e�N�X�`�����

static char* g_TextureName[] = {
	"data/TEXTURE/box.png",
	"data/TEXTURE/var.png",
	"data/TEXTURE/number.png",
	"data/TEXTURE/HP_UI.png",
	"data/TEXTURE/ENEMY_UI.png",
	"data/TEXTURE/button_normal.png",
	"data/TEXTURE/button_double.png",
	"data/TEXTURE/button_stop.png",
	"data/TEXTURE/costbox.png",
	"data/TEXTURE/t_help.png",
	"data/TEXTURE/iconH.png",
	"data/TEXTURE/battle_help.png",
	"data/TEXTURE/button.png",
	"data/TEXTURE/icon101.png",
	"data/TEXTURE/icon102.png",
	"data/TEXTURE/icon103.png",
	"data/TEXTURE/icon104.png",
	"data/TEXTURE/icon105.png",
	"data/TEXTURE/icon106.png",
};
static char* g_CharTextureName[] = {
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

static UI g_UI[TEXTURE_MAX];
static BOOL g_Load = FALSE;
static BOOL g_Help = FALSE;
HRESULT InitUI(void)
{
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
		g_UI[i].color = { 1.0f, 1.0f, 1.0f, 1.0f };
		g_UI[i].pos = { 0.0f, 0.0f };
		g_UI[i].size = { 50.0f, 50.0f };
		g_UI[i].use = TRUE;
	}

	g_UI[var_bg].pos = { SCREEN_CENTER_X, 50.0f };
	g_UI[var_bg].size = { 500.0f, 80.0f };
	g_UI[var_bg].color = { 0.0f, 0.0f, 0.0f, 0.6f };
	g_UI[baseLife].pos = { g_UI[var_bg].pos.x + 80.0f, 50.0f };
	g_UI[baseLife].size = { 642.0f * 0.065f, 990.0f*0.065f };
	g_UI[enemyNum].pos = { g_UI[var_bg].pos.x - 190.0f, 50.0f };
	g_UI[enemyNum].size = { 65.0f, 65.0f };
	const float mnp = 0.15f;
	g_UI[button_n].pos = { 1600.0f, 60.0f };
	g_UI[button_n].size = { 1000.0f * mnp, 600.0f * mnp };
	g_UI[button_d].pos = { 1600.0f, 60.0f };
	g_UI[button_d].size = { 1000.0f * mnp, 600.0f * mnp };
	g_UI[button_s].pos = { 1800.0f, 60.0f };
	g_UI[button_s].size = { 1000.0f * mnp, 600.0f * mnp };
	g_UI[costbox].size = { 160.0f, 160.0f };
	g_UI[costbox].pos = { SCREEN_WIDTH - g_UI[costbox].size.x*0.5f , SCREEN_HEIGHT - g_UI[costbox].size.y * 0.5f };
	g_UI[button_help].size = { 1000.0f * mnp, 600.0f * mnp };
	g_UI[button_help].pos = { 250.0f, SCREEN_HEIGHT - g_UI[button_help].size.y };
	
	g_UI[icon_help].size = { 360.0f * mnp, 360.0f * mnp };
	g_UI[icon_help].pos = { 250.0f - 1000.0f * mnp, SCREEN_HEIGHT - g_UI[button_help].size.y };
	
	g_UI[button_bg].size = { 1200.0f * mnp, 600.0f * mnp };
	g_UI[button_bg].pos = { 250.0f, SCREEN_HEIGHT - g_UI[button_help].size.y };
	
	const float help = 1.0f;
	g_UI[help_texture].size = { 1598 * help, 896 * help };
	g_UI[help_texture].pos = { SCREEN_CENTER_X, SCREEN_CENTER_Y};

	g_Load = TRUE;
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitUI(void)
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
	for (int i = 0; i < CHAR_TEXTURE_MAX; i++)
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
void UpdateUI(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawUI(void)
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


void DrawUIbg(void)
{
	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[var_bg]);

	// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
	SetSpriteColor(g_VertexBuffer, g_UI[var_bg].pos.x, g_UI[var_bg].pos.y, g_UI[var_bg].size.x, g_UI[var_bg].size.y, 0.0f, 0.0f, 1.0f, 1.0f,
		g_UI[var_bg].color);

	// �|���S���`��
	GetDeviceContext()->Draw(4, 0);

}

//����:�\�������������A�\�����W(x,y)�A�\���T�C�Y(x����,y����)
void DrawNumber(int numb, float px, float py, float sx, float sy, XMFLOAT4 color)
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

	for (int i = 0; i < digit; i++)
	{
		px = px - sx * i;
		float x = (float)(numb % 10);		//����\�����鐔��
		float tx = x * 0.1f;			// �e�N�X�`���̍���X���W

		// �e�N�X�`���ݒ�
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[number]);

		// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
		SetSpriteColor(g_VertexBuffer, px, py, sx, sy, tx, 0.0f, 0.1f, 1.0f,
			color);

		// �|���S���`��
		GetDeviceContext()->Draw(4, 0);
		numb /= 10;
	}
}




void DrawButtonNorD(void)
{
	if (GetSpeedMode() == 1)
	{
		// �e�N�X�`���ݒ�
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[button_n]);

		// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
		SetSpriteColor(g_VertexBuffer, g_UI[button_n].pos.x, g_UI[button_n].pos.y, g_UI[button_n].size.x, g_UI[button_n].size.y, 0.0f, 0.0f, 1.0f, 1.0f,
			g_UI[button_n].color);

		// �|���S���`��
		GetDeviceContext()->Draw(4, 0);
	}
	else if (GetSpeedMode() == 2)
	{
		// �e�N�X�`���ݒ�
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[button_d]);

		// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
		SetSpriteColor(g_VertexBuffer, g_UI[button_d].pos.x, g_UI[button_d].pos.y, g_UI[button_d].size.x, g_UI[button_d].size.y, 0.0f, 0.0f, 1.0f, 1.0f,
			g_UI[button_d].color);

		// �|���S���`��
		GetDeviceContext()->Draw(4, 0);
	}
}

void DrawButtonStop(void)
{
	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[button_s]);

	// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
	SetSpriteColor(g_VertexBuffer, g_UI[button_s].pos.x, g_UI[button_s].pos.y, g_UI[button_s].size.x, g_UI[button_s].size.y, 0.0f, 0.0f, 1.0f, 1.0f,
		g_UI[button_s].color);

	// �|���S���`��
	GetDeviceContext()->Draw(4, 0);
}


void DrawHelpButton(void)
{
	//�{�^���A�C�R��
	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[icon_help]);

	// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
	SetSpriteColor(g_VertexBuffer, g_UI[icon_help].pos.x, g_UI[icon_help].pos.y, g_UI[icon_help].size.x, g_UI[icon_help].size.y, 0.0f, 0.0f, 1.0f, 1.0f,
		g_UI[icon_help].color);

	// �|���S���`��
	GetDeviceContext()->Draw(4, 0);

	//�{�^�����E�w�i
	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[var_bg]);

	// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
	SetSpriteColor(g_VertexBuffer, g_UI[button_bg].pos.x, g_UI[button_bg].pos.y, g_UI[button_bg].size.x, g_UI[button_bg].size.y, 0.0f, 0.0f, 1.0f, 1.0f,
		XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));

	// �|���S���`��
	GetDeviceContext()->Draw(4, 0);

	//�w���v�e�L�X�g
	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[button_help]);

	// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
	SetSpriteColor(g_VertexBuffer, g_UI[button_help].pos.x, g_UI[button_help].pos.y, g_UI[button_help].size.x, g_UI[button_help].size.y, 0.0f, 0.0f, 1.0f, 1.0f,
		g_UI[button_help].color);

	// �|���S���`��
	GetDeviceContext()->Draw(4, 0);

	if (g_Help)
	{
		//�w���v�e�L�X�g
		// �e�N�X�`���ݒ�
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[help_texture]);

		// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
		SetSpriteColor(g_VertexBuffer, g_UI[help_texture].pos.x, g_UI[help_texture].pos.y, g_UI[help_texture].size.x, g_UI[help_texture].size.y, 0.0f, 0.0f, 1.0f, 1.0f,
			g_UI[help_texture].color);

		// �|���S���`��
		GetDeviceContext()->Draw(4, 0);
	}
}

void SetHelpButton(BOOL flag) { g_Help = flag; }
BOOL GetHelpButton(void) { return g_Help; }