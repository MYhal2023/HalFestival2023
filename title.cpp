//=============================================================================
//
// �^�C�g������ [title.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "sprite.h"
#include "renderer.h"
#include "input.h"
#include "game.h"
#include "title.h"
#include "gameover.h"
#include "debugproc.h"
#include "fade.h"
#include "sound.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_MAX			(TITLE_TEXTURE_MAX)				// �e�N�X�`���̐�
#define TEXTURE_SPEED		(0.1f)		// �e�N�X�`���̈ړ����x
#define TITLE_BUTTON_NUM	(title_finish - title_start + 1)			//
#define COLOR_SPEED			(0.01f)		// �e�N�X�`���̕ϐF���x


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static ID3D11Buffer					*g_VertexBuffer = NULL;	// ���_���
static char* g_TextureName[] = {
		"data/TEXTURE/var.png",
	"data/TEXTURE/title_2.png",
	"data/TEXTURE/t_start.png",
	"data/TEXTURE/t_scorebutton.png",
	"data/TEXTURE/t_optionbutton.png",
	"data/TEXTURE/t_gameendbutton.png",
	"data/TEXTURE/var.png",
};
static Title g_Title[TEXTURE_MAX];
static BOOL g_Load = FALSE;
static BOOL sound_once = FALSE;
static float speed[TEXTURE_MAX];
static int cursol;
HRESULT InitTitle(void)
{
	ID3D11Device *pDevice = GetDevice();

	//�e�N�X�`������
	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		g_Title[i].g_Texture = NULL;
		D3DX11CreateShaderResourceViewFromFile(GetDevice(),
			g_TextureName[i],
			NULL,
			NULL,
			&g_Title[i].g_Texture,
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
		g_Title[i].textNo = i;
		switch (i)
		{
		case title_bg:
			g_Title[i].color = { 0.0f, 0.0f, 1.0f, 1.0f };
			g_Title[i].pos = { SCREEN_CENTER_X, SCREEN_CENTER_Y };
			g_Title[i].size = { SCREEN_WIDTH, SCREEN_HEIGHT };
			break;
		case title_logo:
			g_Title[i].color = { 1.0f, 1.0f, 1.0f, 1.0f };
			g_Title[i].pos = { SCREEN_CENTER_X, SCREEN_HEIGHT * 0.18f };
			g_Title[i].size = {600 * 1.0f, 200 * 1.0f };
			break;
		case title_start:
			g_Title[i].color = { 1.0f, 1.0f, 1.0f, 1.0f };
			g_Title[i].pos = { SCREEN_CENTER_X, SCREEN_CENTER_Y };
			g_Title[i].size = { 400 * 1.0f, 100 * 1.0f };
			break;
		case title_score:
			g_Title[i].color = { 1.0f, 1.0f, 1.0f, 1.0f };
			g_Title[i].pos = { SCREEN_CENTER_X, g_Title[title_start].pos.y + 100.0f * 1.1f };
			g_Title[i].size = { 400 * 1.0f, 100 * 1.0f };
			break;
		case title_option:
			g_Title[i].color = { 1.0f, 1.0f, 1.0f, 1.0f };
			g_Title[i].pos = { SCREEN_CENTER_X,g_Title[title_score].pos.y + 100.0f * 1.1f };
			g_Title[i].size = { 400 * 1.0f, 100 * 1.0f };
			break;
		case title_finish:
			g_Title[i].color = { 1.0f, 1.0f, 1.0f, 1.0f };
			g_Title[i].pos = { SCREEN_CENTER_X, g_Title[title_option].pos.y + 100.0f * 1.1f };
			g_Title[i].size = { 400 * 1.0f, 100 * 1.0f };
			break;
		case title_cursol:
			g_Title[i].color = { 1.0f, 0.0f, 0.0f, 0.5f };
			g_Title[i].pos = { 0.0f, 0.0f };
			g_Title[i].size = { 400 * 1.0f, 100 * 1.0f };
			break;
		}
	}
	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		switch (i)
		{
		case title_cursol:
			speed[i] = 0.01f;
			break;
		}
	}
	cursol = 0;
	g_Load = TRUE;
	sound_once = FALSE;
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitTitle(void)
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
		if (g_Title[i].g_Texture)
		{
			g_Title[i].g_Texture->Release();
			g_Title[i].g_Texture = NULL;
		}
	}

	g_Load = FALSE;
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateTitle(void)
{
	if (!sound_once) {
		PlaySound(SOUND_LABEL_BGM_Title);
		sound_once = TRUE;
	}
	//�J�[�\���̕ϐF
	if (g_Title[title_cursol].color.w > 0.8f || g_Title[title_cursol].color.w < 0.2f)
		speed[title_cursol] *= -1;

	g_Title[title_cursol].color.w += speed[title_cursol];
	g_Title[title_cursol].color.x += speed[title_cursol];
	g_Title[title_cursol].color.y += speed[title_cursol];
	g_Title[title_cursol].color.z += speed[title_cursol];

	//�J�[�\���ύX
	if ((GetKeyboardTrigger(DIK_UP) || IsButtonTriggered(0, BUTTON_UP)) && cursol > 0)
	{
		cursol--;
		PlaySound(SOUND_LABEL_SE_select);
	}
	else if ((GetKeyboardTrigger(DIK_DOWN) || IsButtonTriggered(0, BUTTON_DOWN)) && TITLE_BUTTON_NUM - 1 > cursol)
	{
		cursol++;
		PlaySound(SOUND_LABEL_SE_select);
	}
	int num = title_start + cursol;
	g_Title[title_cursol].pos = g_Title[num].pos;
	
	if (GetKeyboardTrigger(DIK_RETURN) || IsButtonTriggered(0, BUTTON_C))
	{
		switch (cursol) {
		case 0://�͂��߂���
			PlaySound(SOUND_LABEL_SE_decision);
			SetFade(FADE_BOX_OUT, MODE_RESERVE, WhiteBox);
			break;
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawTitle(void)
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


	//DrawTexture(&g_Title[title_bg]);
	DrawTexture(&g_Title[title_logo]);
	DrawTexture(&g_Title[title_start]);
	DrawTexture(&g_Title[title_score]);
	DrawTexture(&g_Title[title_option]);
	DrawTexture(&g_Title[title_finish]);
	DrawTexture(&g_Title[title_cursol]);

}

//0�̓t�F�[�h�C���A1�̓t�F�[�h�A�E�g
void FadeTexture(int type, Title *title)
{
	switch (type) {
	case 0: 
		title->color.w += 0.01f;
			break;
	case 1:
		title->color.w -= 0.01f;
		break;
	}
}

//�ړ����x�A���W�ő�l�A���W�ŏ��l�A�|�C���^�[
void MoveTexture(float speed, Title *title)
{
	title->pos.y += speed;
}

//�e�N�X�`���`��
void DrawTexture(Title* title)
{
	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, &title->g_Texture);

	// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
	SetSpriteColor(g_VertexBuffer, title->pos.x, title->pos.y, title->size.x, title->size.y, 0.0f, 0.0f, 1.0f, 1.0f,
		title->color);

	// �|���S���`��
	GetDeviceContext()->Draw(4, 0);
}
