//=============================================================================
//
// ���U���g���� [result.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "sprite.h"
#include "renderer.h"
#include "input.h"
#include "game.h"
#include "result.h"
#include "gameover.h"
#include "debugproc.h"
#include "fade.h"
#include "reserve.h"
#include "sound.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_MAX			(8)				// �e�N�X�`���̐�
#define CH_TEXTURE_MAX			(3)				// �e�N�X�`���̐�
#define ROW_NUM				(5)				// ���ɕ��ׂ郆�j�b�g��

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static ID3D11Buffer					*g_VertexBuffer = NULL;	// ���_���
static ID3D11ShaderResourceView		*g_Texture[TEXTURE_MAX] = { NULL };	// �e�N�X�`�����
static ID3D11ShaderResourceView		*g_CharTexture[TEXTURE_MAX] = { NULL };	// �e�N�X�`�����
static char* g_TextureName[TEXTURE_MAX] = {
	"data/TEXTURE/win_texture.png",
	"data/TEXTURE/lose_texture.png",
	"data/TEXTURE/number.png",
	"data/TEXTURE/var.png",
	"data/TEXTURE/icon_energy.png",
	"data/TEXTURE/icon_oxygen.png",
	"data/TEXTURE/icon_iron.png",
	"data/TEXTURE/Result.png",

};
static char* g_CharTextureName[CH_TEXTURE_MAX] = {
	"data/TEXTURE/neutro.png",
	"data/TEXTURE/neutro.png",
	"data/TEXTURE/macro.png",
};

static Result g_Result;
static Reward g_Reward;
static BOOL g_Load = FALSE;
static BOOL once = FALSE;
static BOOL bgm = FALSE;
static float alpha[10];
HRESULT InitResult(void)
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
	for (int i = 0; i < CH_TEXTURE_MAX; i++)
	{
		g_CharTexture[i] = NULL;
		D3DX11CreateShaderResourceViewFromFile(GetDevice(),
			g_CharTextureName[i],
			NULL,
			NULL,
			&g_CharTexture[i],
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

	g_Result.color = { 1.0f, 1.0f, 1.0f, 1.0f };
	g_Result.pos = { SCREEN_CENTER_X, SCREEN_CENTER_Y };
	g_Result.size = { SCREEN_WIDTH, SCREEN_HEIGHT };
	g_Result.textNo = 0;
	g_Result.type = GetOverType();
	g_Result.enemyNum = 0;
	g_Result.beatNum = 0;
	for (int i = 0; i < MAX_PLAYER_NUM; i++) {
		g_Result.charId[i] = 0;
		g_Result.damage[i] = 0;
	}
	for (int i = 0; i < 10; i++) { alpha[i] = 0.0f; }
	g_Load = TRUE;
	once = FALSE;
	bgm = FALSE;
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitResult(void)
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

	g_Load = FALSE;
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateResult(void)
{
	switch (g_Result.type)
	{
	case OVER_WIN:
		g_Result.textNo = 0;
		WinResult();
		break;
	case OVER_LOSE:
		g_Result.textNo = 1;
		LoseResult();
		break;
	}

//#ifdef _DEBUG
//	PrintDebugProc("")
//#endif
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawResult(void)
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

	// ���U���g�̔w�i��`��
	{
		// �e�N�X�`���ݒ�
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[g_Result.textNo]);

		// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
		SetSpriteLeftTop(g_VertexBuffer, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f);

		// �|���S���`��
		GetDeviceContext()->Draw(4, 0);
	}

	//// �񍐏���`��
	//{
	//	// �e�N�X�`���ݒ�
	//	GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[Report]);
	//	const float x = 1754 * 0.4f;
	//	const float y = 2480 * 0.4f;
	//	// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
	//	SetSpriteColor(g_VertexBuffer, SCREEN_CENTER_X, SCREEN_CENTER_Y, x, y, 0.0f, 0.0f, 1.0f, 1.0f,
	//		XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));

	//	// �|���S���`��
	//	GetDeviceContext()->Draw(4, 0);
	//}


}

void WinResult(void)
{
	if (!bgm) { 
		PlaySound(SOUND_LABEL_BGM_Win);
		bgm = TRUE;
	}
	if (GetKeyboardTrigger(DIK_RETURN) && !once)
	{
		once = TRUE;
		SetFade(FADE_OUT, MODE_RESERVE, WhiteBox);	//���󃋁[�v����悤��
	}
}

void LoseResult(void)
{
	if (!bgm) {
		PlaySound(SOUND_LABEL_BGM_Lose);
		bgm = TRUE;
	}
	if (GetKeyboardTrigger(DIK_RETURN) && !once)
	{
		once = TRUE;
		SetFade(FADE_OUT, MODE_RESERVE, WhiteBox);	//���󃋁[�v����悤��
	}
}

void InitReward(void)
{
	g_Reward.num = 0;
	for (int i = 0; i < MAX_REWARD; i++) {
		g_Reward.ID[i] = 99;
		g_Reward.value[i] = 0;
	}
}

void DrawReward(XMFLOAT2 pos, float size)
{
	for (int i = 0; i < g_Reward.num; i++) {
		// �e�N�X�`���ݒ�
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[g_Reward.ID[i] + result_energy]);

		// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
		SetSpriteColor(g_VertexBuffer, pos.x, pos.y, size, size, 0.0f, 0.0f, 1.0f, 1.0f,
			XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));

		// �|���S���`��
		GetDeviceContext()->Draw(4, 0);

		DrawResultNumber(g_Reward.value[i], pos.x, pos.y + size, size * 0.25f, size * 0.5f, XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
	}
}
//���ނ��ݒ�B�ő�ݒ萔��5
void SetReward(int id, int value)
{
	g_Reward.ID[g_Reward.num] = id;
	g_Reward.value[g_Reward.num] = value;
	g_Reward.num++;
}


Reward *GetReward(void) { return &g_Reward; };

//��������UI�`��Ɋւ�����
void DrawResultButton(XMFLOAT4 color, float px, float py, float sx, float sy)
{
	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[result_var]);

	// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
	SetSpriteColor(g_VertexBuffer, px, py, sx, sy, 0.0f, 0.0f, 1.0f, 1.0f,
		color);

	// �|���S���`��
	GetDeviceContext()->Draw(4, 0);

}
//����:�\�������������A�\�����W(x,y)�A�\���T�C�Y(x����,y����)
void DrawResultNumber(int numb, float px, float py, float sx, float sy, XMFLOAT4 color)
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
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[result_numb]);

		// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
		SetSpriteColor(g_VertexBuffer, psx, py, sx, sy, tx, 0.0f, 0.1f, 1.0f,
			color);

		// �|���S���`��
		GetDeviceContext()->Draw(4, 0);
		numb /= 10;
	}
}
