//=============================================================================
//
// �t�F�[�h���� [fade.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "renderer.h"
#include "fade.h"
#include "sound.h"
#include "sprite.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_WIDTH				(SCREEN_WIDTH)	// �w�i�T�C�Y
#define TEXTURE_HEIGHT				(SCREEN_HEIGHT)	// 
#define TEXTURE_MAX					(2)				// �e�N�X�`���̐�
#define FADE_BOX_MAX				(145)				// �e�N�X�`���̐�
#define FADE_BOX_SIZE				(120.0f)				// �e�N�X�`���̐�
#define FADE_BOX_WIDTH_NUM			(SCREEN_WIDTH / 120.0f)				// �e�N�X�`���̐�
#define FADE_BOX_HEIGHT_NUM			(SCREEN_HEIGHT / 120.0f)				// �e�N�X�`���̐�

#define	FADE_RATE					(0.02f)			// �t�F�[�h�W��
#define	BOX_FADE_RATE					(0.2f)			// �t�F�[�h�W��
#define FADE_FRAME					(1.0f / BOX_FADE_RATE)	//�t�F�[�h���[�g�Ɋ�Â��A�t�F�[�h�t���[����
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static ID3D11Buffer				*g_VertexBuffer = NULL;		// ���_���
static ID3D11ShaderResourceView	*g_Texture[TEXTURE_MAX] = { NULL };	// �e�N�X�`�����

static char *g_TexturName[TEXTURE_MAX] = {
	"data/TEXTURE/var.png",
	"data/TEXTURE/fade_black.png",
};


static BOOL						g_Use;						// TRUE:�g���Ă���  FALSE:���g�p
static float					g_w, g_h;					// ���ƍ���
static XMFLOAT3					g_Pos;						// �|���S���̍��W
static int						g_TexNo;					// �e�N�X�`���ԍ�

FADE							g_Fade = FADE_IN;			// �t�F�[�h�̏��
int								g_ModeNext;					// ���̃��[�h
XMFLOAT4						g_Color;					// �t�F�[�h�̃J���[�i���l�j
static FadeBox					g_FadeBox[64][64];
static BOOL						g_Load = FALSE;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitFade(void)
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


	// ������
	g_Use   = TRUE;
	g_w     = TEXTURE_WIDTH;
	g_h     = TEXTURE_HEIGHT;
	g_Pos   = { SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f };
	g_TexNo = 1;

	g_Fade  = FADE_IN;
	g_Color = { 1.0f, 1.0f, 1.0f, 1.0f };

	const float boxsize = 120.0f;
	int width = (int)(FADE_BOX_WIDTH_NUM);
	int height = (int)(FADE_BOX_HEIGHT_NUM);
	for (int i = 0; i < width; i++)
	{
		for (int k = 0; k < height; k++)
		{
			g_FadeBox[i][k].pos = { (i * boxsize) + (boxsize * 0.5f),  (k * boxsize) + (boxsize * 0.5f) };
			g_FadeBox[i][k].size = 0.0f;
			g_FadeBox[i][k].color = { 0.0f, 1.0f, 1.0f, 0.0f };
		}
	}

	g_Load = TRUE;
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitFade(void)
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
void UpdateFade(void)
{

	if (g_Fade != FADE_NONE)
	{// �t�F�[�h������
		if (g_Fade == FADE_OUT)
		{// �t�F�[�h�A�E�g����
			g_Color.w += FADE_RATE;		// ���l�����Z���ĉ�ʂ������Ă���
			if (g_Color.w >= 1.0f)
			{
				// ���Ă���Ȃ�S���~�߂�
				StopSound();

				// �t�F�[�h�C�������ɐ؂�ւ�
				g_Color.w = 1.0f;
				SetFade(FADE_IN, g_ModeNext, g_TexNo);

				// ���[�h��ݒ�
				SetMode(g_ModeNext);
			}

		}
		else if (g_Fade == FADE_IN)
		{// �t�F�[�h�C������
			g_Color.w -= FADE_RATE;		// ���l�����Z���ĉ�ʂ𕂂��オ�点��
			if (g_Color.w <= 0.0f)
			{
				// �t�F�[�h�����I��
				g_Color.w = 0.0f;
				SetFade(FADE_NONE, g_ModeNext, g_TexNo);
			}

		}
		else if (g_Fade == FADE_BOX_OUT)
		{
			int k = (int)(FADE_BOX_HEIGHT_NUM)-1;
			int i = (int)(FADE_BOX_WIDTH_NUM)-1;
			if (g_FadeBox[i][k].color.w >= 1.0f)
			{
				// ���Ă���Ȃ�S���~�߂�
				StopSound();

				// �t�F�[�h�C�������ɐ؂�ւ�
				SetFade(FADE_BOX_IN, g_ModeNext, g_TexNo);

				// ���[�h��ݒ�
				SetMode(g_ModeNext);

			}
			else 
			{
				for (int i = 0; i < FADE_BOX_WIDTH_NUM; i++)
				{
					//�t�F�[�h�A�E�g	
					if (i == 0 && g_FadeBox[i][k].color.w < 1.0f)
						FadeOutBoxFunc(i, k);
					else if (i >= 1 && g_FadeBox[i - 1][k / 4].color.w > 0.0f)
						FadeOutBoxFunc(i, k);
				}
			}
		}
		else if (g_Fade == FADE_BOX_IN)
		{
			int k = (int)(FADE_BOX_HEIGHT_NUM)-1;
			int i = (int)(FADE_BOX_WIDTH_NUM)-1;
			for (int i = 0; i < FADE_BOX_WIDTH_NUM; i++)
			{
				//�t�F�[�h�C��
				if (i == 0 && g_FadeBox[i][k].color.w > 0.0f)
					FadeInBoxFunc(i, k);
				else if (i >= 1 && g_FadeBox[i - 1][k / 4].color.w <= 0.5f)
					FadeInBoxFunc(i, k);
			}

			//�t�F�[�h�I������
			if (g_FadeBox[i][k].color.w <= 0.0f)
			{
				//�{�b�N�X�t�F�[�h�̏�����
				const float boxsize = 120.0f;
				int width = (int)(FADE_BOX_WIDTH_NUM);
				int height = (int)(FADE_BOX_HEIGHT_NUM);
				for (int s = 0; s < width; s++)
				{
					for (int t = 0; t < height; t++)
					{
						g_FadeBox[s][t].size = 0.0f;
						g_FadeBox[s][t].color = { 0.0f, 1.0f, 1.0f, 0.0f };
					}
				}

				SetFade(FADE_NONE, g_ModeNext, g_TexNo);
			}
		}
	}

#ifdef _DEBUG	// �f�o�b�O����\������
	// PrintDebugProc("\n");

#endif

}

//�t�F�[�h�A�E�g�g�����W�V�����̍ċA�Ăяo��
int FadeOutBoxFunc(int i, int k)
{
	if (k < 0)return 0;

	if (k > 0 && g_FadeBox[i][k - 1].color.w >= 0.2f && g_FadeBox[i][k].color.w < 1.0f) {
		g_FadeBox[i][k].color.w += BOX_FADE_RATE;
		g_FadeBox[i][k].size += FADE_BOX_SIZE / FADE_FRAME;
	}
	else if (k == 0 && g_FadeBox[i][k].color.w < 1.0f) {
		g_FadeBox[i][k].color.w += BOX_FADE_RATE;
		g_FadeBox[i][k].size += FADE_BOX_SIZE / FADE_FRAME;
	}

	k--;
	return FadeOutBoxFunc(i, k);
}

//�t�F�[�h�C���g�����W�V�����̍ċA�Ăяo��
int FadeInBoxFunc(int i, int k)
{
	if (k < 0)return 0;

	if (k > 0 && g_FadeBox[i][k - 1].color.w <= 0.8f && g_FadeBox[i][k].color.w > 0.0f) {
		g_FadeBox[i][k].color.w -= BOX_FADE_RATE;
		g_FadeBox[i][k].size -= FADE_BOX_SIZE / FADE_FRAME;
	}
	else if (k == 0 && g_FadeBox[i][k].color.w > 0.0f) {
		g_FadeBox[i][k].color.w -= BOX_FADE_RATE;
		g_FadeBox[i][k].size -= FADE_BOX_SIZE / FADE_FRAME;
	}

	k--;
	return FadeInBoxFunc(i, k);
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawFade(void)
{
	if (g_Fade == FADE_NONE) return;	// �t�F�[�h���Ȃ��̂Ȃ�`�悵�Ȃ�

	// ���Z�����ɐݒ�
	//SetBlendState(BLEND_MODE_ADD);
	SetDepthEnable(FALSE);

	// ���C�e�B���O�𖳌�
	SetLightEnable(FALSE);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �}�e���A���ݒ�
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	SetMaterial(material);


	//�w�i��`��
	if(g_Fade == FADE_IN || FADE_OUT)
	{
		// �e�N�X�`���ݒ�
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[g_TexNo]);

		// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
		//SetVertex(0.0f, 0.0f, SCREEN_WIDTH, TEXTURE_WIDTH, 0.0f, 0.0f, 1.0f, 1.0f);
		SetSpriteColor(g_VertexBuffer, SCREEN_WIDTH/2, SCREEN_HEIGHT /2, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f,
			g_Color);

		// �|���S���`��
		GetDeviceContext()->Draw(4, 0);
	}

	if (g_Fade == FADE_BOX_OUT || FADE_BOX_IN)
	{
		int width = (int)(FADE_BOX_WIDTH_NUM);
		int height = (int)(FADE_BOX_HEIGHT_NUM);
		for (int i = 0; i < width; i++)
		{
			for (int k = 0; k < height; k++)
			{
				if (g_FadeBox[i][k].color.w <= 0.0f)continue;	//�����Ȃ�̓X���[
				// �e�N�X�`���ݒ�
				GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[g_TexNo]);

				// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
				//SetVertex(0.0f, 0.0f, SCREEN_WIDTH, TEXTURE_WIDTH, 0.0f, 0.0f, 1.0f, 1.0f);
				SetSpriteColor(g_VertexBuffer, g_FadeBox[i][k].pos.x, g_FadeBox[i][k].pos.y, g_FadeBox[i][k].size, g_FadeBox[i][k].size, 0.0f, 0.0f, 1.0f, 1.0f,
					g_FadeBox[i][k].color);

				// �|���S���`��
				GetDeviceContext()->Draw(4, 0);
			}
		}

	}
	SetDepthEnable(TRUE);

	SetLightEnable(TRUE);


}


//=============================================================================
// �t�F�[�h�̏�Ԑݒ�
//=============================================================================
void SetFade(FADE fade, int modeNext, int texNo)
{
	g_Fade = fade;
	g_ModeNext = modeNext;
	g_TexNo = texNo;
}

//=============================================================================
// �t�F�[�h�̏�Ԏ擾
//=============================================================================
FADE GetFade(void)
{
	return g_Fade;
}



