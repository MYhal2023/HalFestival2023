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
#define TEXTURE_MAX			(UI_MAX)				// �e�N�X�`���̐�
#define NUMBER_SIZE			(30.0f)			// x�����̃T�C�Y
#define COST_NUMBER_SIZE	(45.0f)			// x�����̃T�C�Y

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static ID3D11Buffer					*g_VertexBuffer = NULL;	// ���_���
static ID3D11ShaderResourceView		*g_Texture[TEXTURE_MAX] = { NULL };	// �e�N�X�`�����

static char* g_TextureName[] = {
	"data/TEXTURE/var.png",
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



//void DrawButton(void)
//{
//	// �e�N�X�`���ݒ�
//	GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[button_s]);
//
//	// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
//	SetSpriteColor(g_VertexBuffer, g_UI[button_s].pos.x, g_UI[button_s].pos.y, g_UI[button_s].size.x, g_UI[button_s].size.y, 0.0f, 0.0f, 1.0f, 1.0f,
//		g_UI[button_s].color);
//
//	// �|���S���`��
//	GetDeviceContext()->Draw(4, 0);
//}


//void DrawHelpButton(void)
//{
//	//�{�^���A�C�R��
//	// �e�N�X�`���ݒ�
//	GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[icon_help]);
//
//	// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
//	SetSpriteColor(g_VertexBuffer, g_UI[icon_help].pos.x, g_UI[icon_help].pos.y, g_UI[icon_help].size.x, g_UI[icon_help].size.y, 0.0f, 0.0f, 1.0f, 1.0f,
//		g_UI[icon_help].color);
//
//	// �|���S���`��
//	GetDeviceContext()->Draw(4, 0);
//
//	//�{�^�����E�w�i
//	// �e�N�X�`���ݒ�
//	GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[var_bg]);
//
//	// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
//	SetSpriteColor(g_VertexBuffer, g_UI[button_bg].pos.x, g_UI[button_bg].pos.y, g_UI[button_bg].size.x, g_UI[button_bg].size.y, 0.0f, 0.0f, 1.0f, 1.0f,
//		XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
//
//	// �|���S���`��
//	GetDeviceContext()->Draw(4, 0);
//
//	//�w���v�e�L�X�g
//	// �e�N�X�`���ݒ�
//	GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[button_help]);
//
//	// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
//	SetSpriteColor(g_VertexBuffer, g_UI[button_help].pos.x, g_UI[button_help].pos.y, g_UI[button_help].size.x, g_UI[button_help].size.y, 0.0f, 0.0f, 1.0f, 1.0f,
//		g_UI[button_help].color);
//
//	// �|���S���`��
//	GetDeviceContext()->Draw(4, 0);
//
//	if (g_Help)
//	{
//		//�w���v�e�L�X�g
//		// �e�N�X�`���ݒ�
//		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[help_texture]);
//
//		// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
//		SetSpriteColor(g_VertexBuffer, g_UI[help_texture].pos.x, g_UI[help_texture].pos.y, g_UI[help_texture].size.x, g_UI[help_texture].size.y, 0.0f, 0.0f, 1.0f, 1.0f,
//			g_UI[help_texture].color);
//
//		// �|���S���`��
//		GetDeviceContext()->Draw(4, 0);
//	}
//}

void SetHelpButton(BOOL flag) { g_Help = flag; }
BOOL GetHelpButton(void) { return g_Help; }