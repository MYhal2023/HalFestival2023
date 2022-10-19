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
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_MAX			(2)				// �e�N�X�`���̐�

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static ID3D11Buffer					*g_VertexBuffer = NULL;	// ���_���
static ID3D11ShaderResourceView		*g_Texture[TEXTURE_MAX] = { NULL };	// �e�N�X�`�����
static char* g_TextureName[] = {
	"data/TEXTURE/fade_red.png",
	"data/TEXTURE/hazard.png",
};

static Over g_Over[TEXTURE_MAX];
static BOOL g_Load = FALSE; 
static int g_Overtype = 0;		//���̕ϐ��͕ʃ��[�h�Ɉڍs�����Ƃ����ێ��������̂ŏ����������ɓ���Ȃ�
static XMFLOAT2 pos = { 0.0f, 0.0f };
HRESULT InitOver(void)
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
		g_Over[i].color = { 1.0f, 1.0f, 1.0f, 0.0f };
		g_Over[i].pos = { SCREEN_CENTER_X, SCREEN_CENTER_Y };
		g_Over[i].size = { SCREEN_WIDTH, SCREEN_HEIGHT };
		g_Over[i].use = TRUE;
	}
	g_Over[Hazard].pos = { SCREEN_CENTER_X * 0.5f, SCREEN_CENTER_Y };
	g_Over[Hazard].size = { 350.0f, 350.0f };

	g_Load = TRUE;
	pos = { -200.0f, 0.0f };
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
void UpdateOver(void)
{
	if (!CheckGameover())return;
	//��������̓Q�[���I�[�o�[�ƂȂ������ɓ���
	switch (g_Overtype)
	{
	case OVER_WIN:
		if (pos.x <= SCREEN_CENTER_X) {
			pos.x += 20.0f;
			pos.y = SCREEN_CENTER_Y;
		}
		SetTextpos(TEXT_WIN_RESULT, XMFLOAT3(pos.x, pos.y, 0.0f));
		break;
	case OVER_LOSE:
		if (g_Over[FadeRed].color.w < 0.5f)
			g_Over[FadeRed].color.w += 0.025f;
		if (g_Over[Hazard].color.w < 1.0f)
			g_Over[Hazard].color.w += 0.05f;
		SetText(TEXT_GAMEOVER, 0, XMFLOAT3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f));
		break;
	}
	if (GetKeyboardTrigger(DIK_RETURN))
	{
		SetFade(FADE_OUT, MODE_RESULT, battleFade);
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

	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		if (g_Over[i].use != TRUE)continue;
		// �e�N�X�`���ݒ�
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[i]);

		// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
		SetSpriteColor(g_VertexBuffer, g_Over[i].pos.x, g_Over[i].pos.y, g_Over[i].size.x, g_Over[i].size.y, 0.0f, 0.0f, 1.0f, 1.0f,
			g_Over[i].color);

		// �|���S���`��
		GetDeviceContext()->Draw(4, 0);
	}

	switch (g_Overtype)
	{
	case OVER_WIN:
		DrawTexttChose(TEXT_WIN_RESULT);
		break;
	case OVER_LOSE:
		DrawTexttChose(TEXT_GAMEOVER);
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

