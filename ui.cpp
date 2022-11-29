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
#include "debugproc.h"
#include "player.h"
#include "time.h"
#include "easing.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_MAX			(UI_MAX)				// �e�N�X�`���̐�
#define NUMBER_SIZE			(30.0f)			// x�����̃T�C�Y
#define COST_NUMBER_SIZE	(45.0f)			// x�����̃T�C�Y
#define RESCUE_SIZE_X		(150.0f * 0.5f)
#define RESCUE_STPOS_X		(240.0f)
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static ID3D11Buffer					*g_VertexBuffer = NULL;	// ���_���

static char* g_TextureName[] = {
	"data/TEXTURE/var.png",
	"data/TEXTURE/HP_box.png",
	"data/TEXTURE/HP_bar.png",
	"data/TEXTURE/HP_bar_bg.png",
	"data/TEXTURE/rescue_ng.png",
	"data/TEXTURE/rescue_ok.png",
	"data/TEXTURE/checkmark.png",
	"data/TEXTURE/arm_UI_tama.png",
	"data/TEXTURE/number.png",
	"data/TEXTURE/icon_xgun.png",
	"data/TEXTURE/icon_braster.png",
	"data/TEXTURE/icon_saw.png",
};


static UI g_UI[TEXTURE_MAX];
static BOOL g_Load = FALSE;
static BOOL g_Help = FALSE;
static int nIndex[3];
static int k = 0;
static XMFLOAT2 ic_pos[3];
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
			&g_UI[i].g_Texture,
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

	const XMFLOAT2 hpPos = { 400.0f, SCREEN_CENTER_Y * 1.575f };
	const float hpSize = 0.4f;
	g_UI[hp_box].pos = hpPos;
	g_UI[hp_box].size = { 1200.0f * hpSize, 400.0f *hpSize };
	g_UI[hp_box].tex = { 1.0f, 1.0f };

	g_UI[hp_var_bg].pos = hpPos;
	g_UI[hp_var_bg].size = { 1200.0f * hpSize, 400.0f *hpSize };
	g_UI[hp_var_bg].tex = { 1.0f, 1.0f };

	g_UI[hp_var].pos = hpPos;
	g_UI[hp_var].size = { 1200.0f * hpSize, 400.0f *hpSize };
	g_UI[hp_var].tex = { 1.0f, 1.0f };

	const XMFLOAT2 rescuePos = { RESCUE_STPOS_X, SCREEN_CENTER_Y * 1.775f };
	const float rescueSize = 0.5f;
	g_UI[rescue_ng].pos = rescuePos;
	g_UI[rescue_ng].size = { RESCUE_SIZE_X, 255.0f *rescueSize };
	g_UI[rescue_ng].tex = { 1.0f, 1.0f };

	g_UI[rescue_ok].pos = rescuePos;
	g_UI[rescue_ok].size = { RESCUE_SIZE_X, 255.0f *rescueSize };
	g_UI[rescue_ok].tex = { 1.0f, 1.0f };

	const XMFLOAT2 checkPos = { RESCUE_STPOS_X, SCREEN_CENTER_Y * 1.775f };
	const float checkSize = 0.75f;
	g_UI[check_mark].pos = checkPos;
	g_UI[check_mark].size = { 140.0f*checkSize, 145.0f *checkSize };
	g_UI[check_mark].tex = { 1.0f, 1.0f };

	const XMFLOAT2 armPos = { 1600.0f, SCREEN_CENTER_Y * 1.6f };
	const float armSize = 1.1f;
	const float armSlotSize = 0.75f;
	const float icon_size = 130.0f;
	g_UI[arm_UI_slot].pos = armPos;
	g_UI[arm_UI_slot].size = { 500.0f*armSlotSize, 500.0f *armSlotSize };
	g_UI[arm_UI_slot].tex = { 1.0f, 1.0f };

	g_UI[ic_xgun].pos = { armPos.x, armPos.y - 73.0f };
	g_UI[ic_xgun].size = { icon_size, icon_size };
	g_UI[ic_xgun].tex = { 1.0f, 1.0f };

	g_UI[ic_braster].pos = { armPos.x - 82.0f, armPos.y + 70.0f };
	g_UI[ic_braster].size = { icon_size, icon_size };
	g_UI[ic_braster].tex = { 1.0f, 1.0f };

	g_UI[ic_saw].pos = { armPos.x + 86.0f, armPos.y + 70.0f };
	g_UI[ic_saw].size = { icon_size, icon_size };
	g_UI[ic_saw].tex = { 1.0f, 1.0f };
	
	ic_pos[0] = g_UI[ic_xgun].pos;
	ic_pos[1] = g_UI[ic_braster].pos;
	ic_pos[2] = g_UI[ic_saw].pos;

	k = 0;
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
		if (g_UI[i].g_Texture)
		{
			g_UI[i].g_Texture->Release();
			g_UI[i].g_Texture = NULL;
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

	PLAYER *player = GetPlayer();
	if (player[0].life > 0.0f) {
		float par = (player[0].life) / (player[0].lifeMax);
		g_UI[hp_var].tex.x = par;
		g_UI[hp_var].size.x = 1160.0f * 0.4f * par;
		g_UI[hp_var].pos.x = 420.0f - ((1160.0f * 0.4f * (1.0f - par)) * (0.5f));
	}
	else
		g_UI[hp_var].tex = { 0.0f, 0.0f };

	DrawTexture(&g_UI[hp_var_bg]);
	DrawTexture(&g_UI[hp_var]);
	DrawTexture(&g_UI[hp_box]);
	DrawTexture(&g_UI[arm_UI_slot]);
	RescueLife* p = RescueLife::GetRescueLife();
	DrawRescueLife(p);

	if (GetSetTime() <= 180 && GetSetTime() > 0) {
		if (GetSetTime() == 180 ||
			GetSetTime() == 120 ||
			GetSetTime() == 60)
		{
			nIndex[k] = Easing::SetEase(0.0f, 150.0f, 10.0f);
			k++;
		}
		float set_size = Easing::GetEase(nIndex[k - 1]);
		int num = (GetSetTime() / 60) + 1;
		DrawNumber(num, SCREEN_CENTER_X, SCREEN_CENTER_Y, set_size, set_size*2.0f, XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
	}
	switch (player[0].armType)
	{
	case 0:
		g_UI[ic_xgun].pos = ic_pos[0];
		g_UI[ic_braster].pos = ic_pos[1];
		g_UI[ic_saw].pos = ic_pos[2];
		break;
	case 1:
		g_UI[ic_xgun].pos = ic_pos[2];
		g_UI[ic_braster].pos = ic_pos[0];
		g_UI[ic_saw].pos = ic_pos[1];
		break;
	case 2:
		g_UI[ic_xgun].pos = ic_pos[1];
		g_UI[ic_braster].pos = ic_pos[2];
		g_UI[ic_saw].pos = ic_pos[0];
		break;
	}

	DrawTexture(&g_UI[ic_xgun]);
	DrawTexture(&g_UI[ic_braster]);
	DrawTexture(&g_UI[ic_saw]);

	SetDepthEnable(TRUE);

	// ���C�e�B���O�𖳌�
	SetLightEnable(TRUE);


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
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_UI[number].g_Texture);

		// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
		SetSpriteColor(g_VertexBuffer, px, py, sx, sy, tx, 0.0f, 0.1f, 1.0f,
			color);

		// �|���S���`��
		GetDeviceContext()->Draw(4, 0);
		numb /= 10;
	}
}



void DrawTexture(UI* utp)
{
	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, &utp->g_Texture);

	// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
	SetSpriteColor(g_VertexBuffer, utp->pos.x, utp->pos.y, utp->size.x, utp->size.y, 0.0f, 0.0f, utp->tex.x, utp->tex.y,
		utp->color);

	// �|���S���`��
	GetDeviceContext()->Draw(4, 0);
}

void DrawRescueLife(RescueLife* rlp)
{
	XMFLOAT2 rescuePos = { RESCUE_STPOS_X, SCREEN_CENTER_Y * 1.75f };

	for (int i = 0; i < GetRemain(); i++)
	{
		rescuePos.x = RESCUE_STPOS_X + (RESCUE_SIZE_X + 16.0f) * i;
		if (rlp->GetRescue(i)) 
		{
			g_UI[rescue_ok].pos.x = rescuePos.x;
			g_UI[check_mark].pos.x = rescuePos.x;
			DrawTexture(&g_UI[rescue_ok]);
			DrawTexture(&g_UI[check_mark]);
		}
		else if(!rlp->GetRescue(i))
		{
			g_UI[rescue_ng].pos.x = rescuePos.x;
			DrawTexture(&g_UI[rescue_ng]);
		}
	}

}
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