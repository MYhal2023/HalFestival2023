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
#define TEXTURE_MAX			(6)				// �e�N�X�`���̐�
#define TEXTURE_SPEED		(0.1f)		// �e�N�X�`���̈ړ����x
#define TITLE_BUTTON_NUM	(2)			//
#define COLOR_SPEED			(0.01f)		// �e�N�X�`���̕ϐF���x


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static ID3D11Buffer					*g_VertexBuffer = NULL;	// ���_���
static ID3D11ShaderResourceView		*g_Texture[TEXTURE_MAX] = { NULL };	// �e�N�X�`�����
static char* g_TextureName[] = {
	"data/TEXTURE/title_bg.png",
	"data/TEXTURE/title_allies.png",
	"data/TEXTURE/title_enemy.png",
	"data/TEXTURE/newgame.png",
	"data/TEXTURE/loadgame.png",
	"data/TEXTURE/title_logo.png",
};
static Title g_Title[TEXTURE_MAX];
static BOOL g_Load = FALSE;
static float speed[TEXTURE_MAX];
static int cursol;
HRESULT InitTitle(void)
{
	ID3D11Device *pDevice = GetDevice();

	//�e�N�X�`������
	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		g_Texture[i] = NULL;
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
		g_Title[i].textNo = i;
		switch (i)
		{
		case title_bg:
			g_Title[i].color = { 1.0f, 1.0f, 1.0f, 1.0f };
			g_Title[i].pos = { SCREEN_CENTER_X, SCREEN_CENTER_Y };
			g_Title[i].size = { SCREEN_WIDTH, SCREEN_HEIGHT };
			break;
		case title_allies:
			g_Title[i].color = { 1.0f, 1.0f, 1.0f, 0.0f };
			g_Title[i].pos = { SCREEN_CENTER_X, SCREEN_CENTER_Y };
			g_Title[i].size = { SCREEN_WIDTH, SCREEN_HEIGHT *1.1f};
			break;
		case title_enemy:
			g_Title[i].color = { 1.0f, 1.0f, 1.0f, 0.0f };
			g_Title[i].pos = { SCREEN_CENTER_X, SCREEN_CENTER_Y };
			g_Title[i].size = { SCREEN_WIDTH, SCREEN_HEIGHT };
			break;
		case newgame:
			g_Title[i].color = { 1.0f, 1.0f, 1.0f, 0.8f };
			g_Title[i].pos = { SCREEN_CENTER_X, SCREEN_CENTER_Y *1.2f };
			g_Title[i].size = { 390, 90 };
			break;
		case loadgame:
			g_Title[i].color = { 1.0f, 1.0f, 1.0f, 0.8f };
			g_Title[i].pos = { SCREEN_CENTER_X, SCREEN_CENTER_Y *1.2f };
			g_Title[i].size = { 390, 90 };
			break;
		case title_logo:
			g_Title[i].color = { 1.0f, 1.0f, 1.0f, 0.0f };
			g_Title[i].pos = { SCREEN_CENTER_X, SCREEN_HEIGHT * 0.18f };
			g_Title[i].size = { 400*1.75f, 200*1.75f };
			break;
		}
	}
	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		switch (i)
		{
		case title_enemy:
			speed[i] = TEXTURE_SPEED;
			break;
		case title_allies:
			speed[i] = TEXTURE_SPEED * 4.0f;
			break;
		case newgame:
			speed[i] = COLOR_SPEED;
			break;
		case loadgame:
			speed[i] = COLOR_SPEED;
			break;
		case title_logo:
			speed[i] = 0.1f;
			break;
		}
	}
	cursol = 0;
		g_Load = TRUE;
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
void UpdateTitle(void)
{
	//�����t�F�[�h�C���œo�ꂳ����
	if (g_Title[title_allies].color.w < 1.0f) {
		if (g_Title[title_bg].color.w < 1.0f)
			FadeTexture(0, &g_Title[title_bg]);

		if (g_Title[title_bg].color.w > 0.5f && g_Title[title_enemy].color.w < 1.0f)
		{
			FadeTexture(0, &g_Title[title_enemy]);
		}

		if (g_Title[title_enemy].color.w > 0.5f && g_Title[title_allies].color.w < 1.0f)
		{
			FadeTexture(0, &g_Title[title_allies]);
		}

		if (g_Title[title_logo].color.w < 1.0f) {
			FadeTexture(0, &g_Title[title_logo]);
		}
	}
	//�t�F�[�h�C��������e���œ���������
	if (g_Title[title_enemy].color.w > 0.5f) {
		if (g_Title[title_enemy].pos.y > SCREEN_CENTER_Y * 1.025f || g_Title[title_enemy].pos.y < SCREEN_CENTER_Y * 0.975f)
			speed[title_enemy] *= -1;
		MoveTexture(speed[title_enemy], &g_Title[title_enemy]);
	}

	if (g_Title[title_allies].color.w > 0.5f) {

		if (g_Title[title_allies].pos.y > SCREEN_CENTER_Y * 1.025f || g_Title[title_allies].pos.y < SCREEN_CENTER_Y * 1.0f)
			speed[title_allies] *= -1;
		MoveTexture(speed[title_allies], &g_Title[title_allies]);
	}

	//�J�[�\���̕ϐF
	int num = newgame + cursol;
	if (g_Title[num].color.w > 1.2f || g_Title[num].color.w < 0.7f)
		speed[num] *= -1;
	g_Title[num].color.w += speed[num];
	g_Title[num].color.x += speed[num];
	g_Title[num].color.y += speed[num];
	g_Title[num].color.z += speed[num];

	//�J�[�\���ύX
	if (GetKeyboardTrigger(DIK_LEFT) && cursol > 0)
	{
		cursol--;
		PlaySound(SOUND_LABEL_SE_Select);
	}
	else if (GetKeyboardTrigger(DIK_RIGHT) && cursol < TITLE_BUTTON_NUM - 1)
	{
		cursol++;
		PlaySound(SOUND_LABEL_SE_Select);
	}
	if (GetKeyboardTrigger(DIK_Z) || GetKeyboardTrigger(DIK_RETURN))
	{
		switch (cursol) {
		case 0://�͂��߂���
			PlaySound(SOUND_LABEL_SE_Decision);
			SetFade(FADE_OUT, MODE_RESERVE, BlackFade);
			break;
		case 1://�Â�����
			PlaySound(SOUND_LABEL_SE_Decision);
			SetFade(FADE_OUT, MODE_RESERVE, BlackFade);
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

	// �w�i��`��
		// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[g_Title[title_bg].textNo]);

	// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
	SetSpriteLeftTop(g_VertexBuffer, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f);

	// �|���S���`��
	GetDeviceContext()->Draw(4, 0);


	// �G�l�~�[�Q��`��
	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[g_Title[title_enemy].textNo]);

	// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
	SetSpriteColor(g_VertexBuffer, g_Title[title_enemy].pos.x, g_Title[title_enemy].pos.y, g_Title[title_enemy].size.x, g_Title[title_enemy].size.y, 0.0f, 0.0f, 1.0f, 1.0f,
		g_Title[title_enemy].color);

	// �|���S���`��
	GetDeviceContext()->Draw(4, 0);


	// �v���C���[�Q��`��
	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[g_Title[title_allies].textNo]);

	// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
	SetSpriteColor(g_VertexBuffer, g_Title[title_allies].pos.x, g_Title[title_allies].pos.y, g_Title[title_allies].size.x, g_Title[title_allies].size.y, 0.0f, 0.0f, 1.0f, 1.0f,
		g_Title[title_allies].color);

	// �|���S���`��
	GetDeviceContext()->Draw(4, 0);

	// �^�C�g�����S��`��
	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[g_Title[title_logo].textNo]);

	// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
	SetSpriteColor(g_VertexBuffer, g_Title[title_logo].pos.x, g_Title[title_logo].pos.y, g_Title[title_logo].size.x, g_Title[title_logo].size.y, 0.0f, 0.0f, 1.0f, 1.0f,
		g_Title[title_logo].color);

	// �|���S���`��
	GetDeviceContext()->Draw(4, 0);

	// �J�[�\���`��
	// �e�N�X�`���ݒ�
	int num = newgame + cursol;
	GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[g_Title[num].textNo]);

	// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
	SetSpriteColor(g_VertexBuffer, g_Title[num].pos.x, g_Title[num].pos.y, g_Title[num].size.x, g_Title[num].size.y, 0.0f, 0.0f, 1.0f, 1.0f,
		g_Title[num].color);

	// �|���S���`��
	GetDeviceContext()->Draw(4, 0);

	if (cursol > 0) {
		int num = newgame + cursol - 1;
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[g_Title[num].textNo]);

		// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
		SetSpriteColor(g_VertexBuffer, g_Title[num].pos.x - 390.0f, g_Title[num].pos.y + 45.0f, g_Title[num].size.x * 0.5f, g_Title[num].size.y * 0.5f, 0.0f, 0.0f, 1.0f, 1.0f,
			g_Title[num].color);

		// �|���S���`��
		GetDeviceContext()->Draw(4, 0);
	}
	if (cursol < TITLE_BUTTON_NUM - 1) {
		int num = newgame + cursol + 1;
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[g_Title[num].textNo]);

		// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
		SetSpriteColor(g_VertexBuffer, g_Title[num].pos.x + 390.0f, g_Title[num].pos.y + 45.0f, g_Title[num].size.x * 0.5f, g_Title[num].size.y * 0.5f, 0.0f, 0.0f, 1.0f, 1.0f,
			g_Title[num].color);

		// �|���S���`��
		GetDeviceContext()->Draw(4, 0);
	}
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