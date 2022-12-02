//=============================================================================
//
// �Q�[���I�[�o�[���� [gameovera.cpp]
// Author : 
//
//=============================================================================
#include "gameover.h"
#include "game.h"
#include "sprite.h"
#include "renderer.h"
#include "input.h"
#include "fade.h"
#include "text_texture.h"
#include "debugproc.h"
#include "easing.h"
#include "sound.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_MAX			(MAX_OVER_TEXTURE)				// �e�N�X�`���̐�
#define WIN_OVER_TIME			(180)				// �������o�̑҂�����

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static ID3D11Buffer					*g_VertexBuffer = NULL;	// ���_���
static char* g_TextureName[] = {
	"data/TEXTURE/fade_red.png",
	"data/TEXTURE/hazard.png",
	"data/TEXTURE/clear.png",
	"data/TEXTURE/number.png",
	"data/TEXTURE/danger.png",
	"data/TEXTURE/var.png",
};

static Over g_Over[MAX_OVER_TEXTURE];
static BOOL g_Load = FALSE; 
static BOOL next_mode = FALSE;
static BOOL sound_once = FALSE;
static int g_Overtype = 1;		//���̕ϐ��͕ʃ��[�h�Ɉڍs�����Ƃ����ێ��������̂ŏ����������ɓ���Ȃ�
static XMFLOAT2 pos = { 0.0f, 0.0f };
static float hazard_pos_x = 0.0f;
static int cnt_frame = 0;
HRESULT InitOver(void)
{
	ID3D11Device *pDevice = GetDevice();

	// �e�N�X�`������
	for (int i = 0; i < MAX_OVER_TEXTURE; i++)
	{
		D3DX11CreateShaderResourceViewFromFile(GetDevice(),
			g_TextureName[i],
			NULL,
			NULL,
			&g_Over[i].g_Texture,
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
		g_Over[i].color = { 1.0f, 1.0f, 1.0f, 0.0f };
		g_Over[i].pos = { SCREEN_CENTER_X, SCREEN_CENTER_Y };
		g_Over[i].size = { SCREEN_WIDTH, SCREEN_HEIGHT };
		g_Over[i].use = TRUE;
		g_Over[i].nIndex_x = 99;
		g_Over[i].nIndex_y = 99;
		g_Over[i].nIndex_alpha_x = 99;
		g_Over[i].nIndex_alpha_y = 99;
		g_Over[i].minus_alpha = 0.0f;
	}
	g_Over[ov_FadeRed].pos = { SCREEN_CENTER_X, SCREEN_CENTER_Y };
	g_Over[ov_FadeRed].size = { SCREEN_WIDTH, SCREEN_HEIGHT };
	g_Over[ov_FadeRed].color = { 1.0f, 1.0f, 1.0f, 0.0f };

	g_Over[ov_Hazard].pos = { SCREEN_CENTER_X * 0.5f, SCREEN_CENTER_Y };
	g_Over[ov_Hazard].size = { 350.0f, 350.0f };
	g_Over[ov_Hazard].color = { 1.0f, 1.0f, 1.0f, 0.0f };
	g_Over[ov_Hazard].minus_alpha = 0.015f;

	g_Over[ov_danger].pos = { SCREEN_CENTER_X * 0.5f, SCREEN_CENTER_Y };
	g_Over[ov_danger].size = { 899.0f * 0.9f, 215.0f *0.9f};
	g_Over[ov_danger].color = { 1.0f, 0.0f, 0.0f, 0.0f };
	g_Over[ov_danger].minus_alpha = 0.015f;

	g_Over[ov_Clear].pos = { SCREEN_CENTER_X, SCREEN_CENTER_Y };
	g_Over[ov_Clear].size = { 883.0f + 883.0f, 231.0f + 231.0f };
	g_Over[ov_Clear].color = { 1.0f, 1.0f, 1.0f, 0.0f };

	g_Load = TRUE;
	next_mode = FALSE;
	sound_once = FALSE;
	pos = { -200.0f, 0.0f };
	hazard_pos_x = 0.0f;
	cnt_frame = 0;
	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void UninitOver(void)
{
	if (g_Load == FALSE) return;

	// ���_�o�b�t�@�̉��
	if (g_VertexBuffer)
	{
		g_VertexBuffer->Release();
		g_VertexBuffer = NULL;
	}

	// �e�N�X�`���̉��
	for (int i = 0; i < MAX_OVER_TEXTURE; i++)
	{
		if (g_Over[i].g_Texture)
		{
			g_Over[i].g_Texture->Release();
			g_Over[i].g_Texture = NULL;
		}
	}

	g_Load = FALSE;
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateOver(void)
{
	if (!CheckGameover())return;
	if (!sound_once)
	{
		switch (g_Overtype)
		{
		case OVER_WIN:
			PlaySound(SOUND_LABEL_SE_clear);
			break;
		case OVER_LOSE:
			PlaySound(SOUND_LABEL_SE_game_over);
			break;
		}
		sound_once = TRUE;
	}
	cnt_frame++;
	//��������̓Q�[���I�[�o�[�ƂȂ������ɓ���
	switch (g_Overtype)
	{
	case OVER_WIN:
		if (g_Over[ov_Clear].color.w == 0.0f)
		{
			g_Over[ov_Clear].nIndex_x = Easing::SetEase(0.0f, 883.0f, 30.0f);
			g_Over[ov_Clear].nIndex_y = Easing::SetEase(0.0f, 231.0f, 30.0f);
		}

		if (Easing::GetEase(g_Over[ov_Clear].nIndex_x) >= 883.0f * 0.8f && g_Over[ov_Clear].nIndex_alpha_x == 99)
		{
			g_Over[ov_Clear].nIndex_alpha_x = Easing::SetEase(0.0f, 883.0f * 0.5f, 30.0f);
			g_Over[ov_Clear].nIndex_alpha_y = Easing::SetEase(0.0f, 231.0f * 0.5f, 30.0f);
		}

		if (g_Over[ov_Clear].nIndex_alpha_x != 99 && g_Over[ov_Clear].minus_alpha > -1.0f)
		{
			g_Over[ov_Clear].minus_alpha += 0.01f;
		}

		if (g_Over[ov_Clear].color.w < 1.0f)
			g_Over[ov_Clear].color.w += 0.05f;

		g_Over[ov_Clear].size.x = 1766.0f - Easing::GetEase(g_Over[ov_Clear].nIndex_x);
		g_Over[ov_Clear].size.y = 462.0f - Easing::GetEase(g_Over[ov_Clear].nIndex_y);
		break;
	case OVER_LOSE:
		if (g_Over[ov_FadeRed].color.w < 0.5f)
			g_Over[ov_FadeRed].color.w += 0.01f;

		if (g_Over[ov_Hazard].color.w < 0.0f || g_Over[ov_Hazard].color.w > 1.0f)
			g_Over[ov_Hazard].minus_alpha *= -1;
		g_Over[ov_Hazard].color.w += g_Over[ov_Hazard].minus_alpha;

		if (g_Over[ov_danger].color.w < 0.0f || g_Over[ov_danger].color.w > 1.0f)
			g_Over[ov_danger].minus_alpha *= -1;
		g_Over[ov_danger].color.w += g_Over[ov_danger].minus_alpha;

		hazard_pos_x -= 1.5f;
		break;
	}

	if (GetKeyboardTrigger(DIK_RETURN) || hazard_pos_x == -1.5f * 300.0f || cnt_frame == WIN_OVER_TIME)
	{
		next_mode = TRUE;
		SetFade(FADE_BOX_OUT, MODE_RESULT, WhiteBox);
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawOver(void)
{
	if (!CheckGameover())return;

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

	switch (g_Overtype)
	{
	case OVER_WIN:
		if (next_mode)break;
		DrawOverTexture(&g_Over[ov_Clear], 0.0f, 1.0f);
		if (Easing::GetEase(g_Over[ov_Clear].nIndex_x) >= 880.0f)
		{
			g_Over[ov_Clear].color.w = 0.5f - g_Over[ov_Clear].minus_alpha;
			g_Over[ov_Clear].size.x = 883.0f + Easing::GetEase(g_Over[ov_Clear].nIndex_alpha_x);
			g_Over[ov_Clear].size.y = 231.0f + Easing::GetEase(g_Over[ov_Clear].nIndex_alpha_y);
			DrawOverTexture(&g_Over[ov_Clear], 0.0f, 1.0f);
			//���ɖ߂�
			g_Over[ov_Clear].color.w = 1.0f;
		}

		break;
	case OVER_LOSE:
		DrawOverTexture(&g_Over[ov_FadeRed],0.0f, 1.0f);

		g_Over[ov_danger].pos = { SCREEN_CENTER_X * 1.0f + hazard_pos_x, SCREEN_CENTER_Y };
		DrawOverTexture(&g_Over[ov_danger], 0.0f, 1.0f);

		g_Over[ov_Hazard].pos = { SCREEN_CENTER_X * 0.40f + hazard_pos_x, SCREEN_CENTER_Y };
		DrawOverTexture(&g_Over[ov_Hazard], 0.0f, 1.0f);

		g_Over[ov_Hazard].pos = { SCREEN_CENTER_X * 1.6f + hazard_pos_x, SCREEN_CENTER_Y };
		DrawOverTexture(&g_Over[ov_Hazard], 0.0f, 1.0f);

		g_Over[ov_danger].pos = { SCREEN_CENTER_X * 2.8f + hazard_pos_x, SCREEN_CENTER_Y };
		DrawOverTexture(&g_Over[ov_danger], 0.0f, 1.0f);

		g_Over[ov_Hazard].pos = { SCREEN_CENTER_X * 2.2f + hazard_pos_x, SCREEN_CENTER_Y };
		DrawOverTexture(&g_Over[ov_Hazard], 0.0f, 1.0f);

		g_Over[ov_Hazard].pos = { SCREEN_CENTER_X * 3.4f + hazard_pos_x, SCREEN_CENTER_Y };
		DrawOverTexture(&g_Over[ov_Hazard], 0.0f, 1.0f);

		break;
	}


	SetDepthEnable(TRUE);

	// ���C�e�B���O�𖳌�
	SetLightEnable(TRUE);

}

void SetOverType(int type)
{
	g_Overtype = type;
}

int GetOverType(void)
{
	return g_Overtype;
}

//�e�N�X�`���`��
void DrawOverTexture(Over* ov,float sx, float fx)
{
	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, &ov->g_Texture);

	// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
	SetSpriteColor(g_VertexBuffer, ov->pos.x, ov->pos.y, ov->size.x, ov->size.y, sx, 0.0f, fx, 1.0f,
		ov->color);

	// �|���S���`��
	GetDeviceContext()->Draw(4, 0);

}

//����:�\�������������A�\�����W(x,y)�A�\���T�C�Y(x����,y����)
void DrawOverNumber(int numb, float px, float py, float sx, float sy, XMFLOAT4 color)
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
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Over[ov_numb].g_Texture);

		// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
		SetSpriteColor(g_VertexBuffer, psx, py, sx, sy, tx, 0.0f, 0.1f, 1.0f,
			color);

		// �|���S���`��
		GetDeviceContext()->Draw(4, 0);
		numb /= 10;
	}
}
