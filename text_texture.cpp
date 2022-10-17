//=============================================================================
//
// �����e�N�X�`�����̕\������ [text_texture.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "renderer.h"
#include "sprite.h"
#include "game.h"
#include "time.h"
#include "player.h"
#include "debugproc.h"
#include "text_texture.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_MAX					(6)				// �e�N�X�`���̐�
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static ID3D11Buffer				*g_VertexBuffer = NULL;		// ���_���
static ID3D11ShaderResourceView	*g_Texture[TEXTURE_MAX] = { NULL };	// �e�N�X�`�����

static char *g_TexturName[TEXTURE_MAX] = {
	"data/TEXTURE/t_gameover.png",
	"data/TEXTURE/t_result.png",
	"data/TEXTURE/t_confirm.png",
	"data/TEXTURE/t_day.png",
	"data/TEXTURE/t_powerup.png",
	"data/TEXTURE/t_start.png",
};
static BOOL						g_Load = FALSE;
static TEXT_TEXTURE				g_Texttex[TEXTURE_MAX];
//=============================================================================
// ����������
//=============================================================================
HRESULT InitTexttex(void)
{
	ID3D11Device *pDevice = GetDevice();

	//�e�N�X�`������
	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		g_Texture[i] = NULL;
		D3DX11CreateShaderResourceViewFromFile(GetDevice(),
			g_TexturName[i],
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

	const float mag = 1.2f;
	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		g_Texttex[i].use = FALSE;
		g_Texttex[i].TexNo = i;						//�e�N�X�`���ԍ�
		g_Texttex[i].w = 0;
		g_Texttex[i].h = 0;
		g_Texttex[i].tw = 1.0f;
		g_Texttex[i].th = 1.0f;
		g_Texttex[i].tx = 0.0f;
		g_Texttex[i].ty = 0.0f;		// ���ƍ����A�e�N�X�`�����W
		g_Texttex[i].pos = {SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.8f, 0.0f};						// �|���S���̈ʒu
		g_Texttex[i].color = { 1.0f, 1.0f, 1.0f, 0.0f };						//�F
		g_Texttex[i].time = 0;					
		g_Texttex[i].timeMax = 210;
		g_Texttex[i].type = 0;

		switch (i)
		{
		case TEXT_GAMEOVER:
			g_Texttex[i].w = 398 * mag;
			g_Texttex[i].h = 99 * mag;
			break;
		case TEXT_WIN_RESULT:
			g_Texttex[i].w = 400 * mag;
			g_Texttex[i].h = 250 * mag;
			break;
		}
	}

	// ������
	g_Load = TRUE;
	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void UninitTexttex(void)
{
	if (g_Load == FALSE) return;

	if (g_VertexBuffer)
	{
		g_VertexBuffer->Release();
		g_VertexBuffer = NULL;
	}

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
void UpdateTexttex(void)
{
	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		if (g_Texttex[i].use != TRUE)continue;

		const float fade = 0.05f;
		if (g_Texttex[i].type == 0)		//�t�F�[�h�C��
		{
			if (g_Texttex[i].color.w < 1.0f)
			{//�\���J�n
				g_Texttex[i].color.w += fade;
			}
		}
		else if (g_Texttex[i].type == 1)	//�t�F�[�h�A�E�g
		{
			if (g_Texttex[i].color.w > 0.0f)
			{//�����J�n
				g_Texttex[i].color.w -= fade;
			}
			else if (g_Texttex[i].color.w <= 0.0f)
			{//�����������߁A�S�ď�����
				g_Texttex[i].use = FALSE;
				g_Texttex[i].color.w = 0.0f;
			}
		}
		else if (g_Texttex[i].type == 2)	//�����\��
		{
			g_Texttex[i].color.w = 1.0f;
		}
	}
}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawTexttex(void)
{
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

	SetAlphaTestEnable(TRUE);
	float px = 0.0f;	// �\���ʒuX
	float py = 0.0f;			// �\���ʒuY
	float pw = 0.0f;				// �\����
	float ph = 0.0f;				// �\������

	float tw = 0.0f;		// �e�N�X�`���̕�
	float th = 0.0f;		// �e�N�X�`���̍���
	float tx = 0.0f;		// �e�N�X�`���̍���X���W
	float ty = 0.0f;		// �e�N�X�`���̍���Y���W

	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		if (g_Texttex[i].use != TRUE)continue;

		// �e�N�X�`���ݒ�
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[g_Texttex[i].TexNo]);

		// �X�R�A�̈ʒu��e�N�X�`���[���W�𔽉f
		px = g_Texttex[i].pos.x;			// �\���ʒuX
		py = g_Texttex[i].pos.y;			// �\���ʒuY
		pw = g_Texttex[i].w;				// �\����
		ph = g_Texttex[i].h;				// �\������

		tw = g_Texttex[i].tw;		// �e�N�X�`���̕�
		th = g_Texttex[i].th;		// �e�N�X�`���̍���
		tx = g_Texttex[i].tx;		// �e�N�X�`���̍���X���W
		ty = g_Texttex[i].ty;		// �e�N�X�`���̍���Y���W

		// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
		SetSpriteColor(g_VertexBuffer, px, py, pw, ph, tx, ty, tw, th,
			g_Texttex[i].color);

		// �|���S���`��
		GetDeviceContext()->Draw(4, 0);
	}
	SetAlphaTestEnable(FALSE);

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawTexttChose(int k)	//�����ɕ`�悵�����������B
{
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

	float px = g_Texttex[k].pos.x;	// �\���ʒuX
	float py = g_Texttex[k].pos.y;			// �\���ʒuY
	float pw = 0.0f;				// �\����
	float ph = 0.0f;				// �\������

	float tw = 0.0f;		// �e�N�X�`���̕�
	float th = 0.0f;		// �e�N�X�`���̍���
	float tx = 0.0f;		// �e�N�X�`���̍���X���W
	float ty = 0.0f;		// �e�N�X�`���̍���Y���W

	if (g_Texttex[k].use != TRUE)return;

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[g_Texttex[k].TexNo]);

	// �X�R�A�̈ʒu��e�N�X�`���[���W�𔽉f
	px = g_Texttex[k].pos.x;			// �\���ʒuX
	py = g_Texttex[k].pos.y;			// �\���ʒuY
	pw = g_Texttex[k].w;				// �\����
	ph = g_Texttex[k].h;				// �\������

	tw = g_Texttex[k].tw;		// �e�N�X�`���̕�
	th = g_Texttex[k].th;		// �e�N�X�`���̍���
	tx = g_Texttex[k].tx;		// �e�N�X�`���̍���X���W
	ty = g_Texttex[k].ty;		// �e�N�X�`���̍���Y���W

	// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
	SetSpriteColor(g_VertexBuffer, px, py, pw, ph, tx, ty, tw, th,
		g_Texttex[k].color);

	// �|���S���`��
	GetDeviceContext()->Draw(4, 0);

}

void SetText(int i, int type, XMFLOAT3 pos)
{
	//for (int k = 0; k < TEXTURE_MAX; k++)
	//{
	//	if (g_Texttex[k].use)
	//	{
	//		g_Texttex[k].use = FALSE;
	//		g_Texttex[k].color.w = 0.0f;
	//		g_Texttex[k].time = 0;
	//		break;
	//	}
	//}

	if (g_Texttex[i].use != TRUE)
	{
		g_Texttex[i].use = TRUE;
		g_Texttex[i].pos = pos;
		g_Texttex[i].color.w = 0.0f;
		g_Texttex[i].time = 0;
		g_Texttex[i].type = type;
	}
}
//�����\���̂�����������g��
void SetTextpos(int i, XMFLOAT3 pos)
{
	g_Texttex[i].pos = pos;
	g_Texttex[i].use = TRUE;
	g_Texttex[i].type = 2;
}