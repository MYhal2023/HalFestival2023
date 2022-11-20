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
#include "time.h"
#include "easing.h"
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
static char* g_TextureName[MAX_RESULT_TEX] = {
	"data/TEXTURE/number.png",
	"data/TEXTURE/timer_cent.png",
	"data/TEXTURE/var.png",
};

static Result g_Result[MAX_RESULT_TEX];
static Reward g_Reward;
static BOOL g_Load = FALSE;
static BOOL once = FALSE;	//��񂾂��s�������Ŏg�p
static BOOL ef_once = FALSE;	//��񂾂��s�������Ŏg�p
static int sequence = 0;	//���U���g�̃V�[�P���X���
static int skip = 0;
static float alpha[10];
HRESULT InitResult(void)
{
	ID3D11Device *pDevice = GetDevice();

	//�e�N�X�`������
	for (int i = 0; i < MAX_RESULT_TEX; i++)
	{
		g_Result[i].g_Texture = NULL;
		D3DX11CreateShaderResourceViewFromFile(GetDevice(),
			g_TextureName[i],
			NULL,
			NULL,
			&g_Result[i].g_Texture,
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
	for (int i = 0; i < MAX_RESULT_TEX; i++)
	{
		g_Result[i].color = { 1.0f, 1.0f, 1.0f, 1.0f };
		g_Result[i].pos = { SCREEN_CENTER_X, SCREEN_CENTER_Y };
		g_Result[i].size = { SCREEN_WIDTH, SCREEN_HEIGHT };
	}
	for (int i = 0; i < 10; i++) { alpha[i] = 0.0f; }
	sequence = 0;
	g_Load = TRUE;
	once = FALSE;
	ef_once = FALSE;
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
	for (int i = 0; i < MAX_RESULT_TEX; i++)
	{
		if (g_Result[i].g_Texture)
		{
			g_Result[i].g_Texture->Release();
			g_Result[i].g_Texture = NULL;
		}
	}

	g_Load = FALSE;
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateResult(void)
{
	skip++;
	if (skip < 10)return;

	switch (sequence)
	{
	case 0:
		FirstSeq();
		break;
	case 1:
		SecondSeq();
		break;
	case 2:
		ThirdSeq();
		break;
	case 3:
		ForthSeq();
		break;
	case 4:
		FifthSeq();
		break;
	}
	WinResult();

//#ifdef _DEBUG
//	PrintDebugProc("")
//#endif
}

void FirstSeq(void)
{
	if (g_Reward.time < g_Reward.max_time)
		g_Reward.time += g_Reward.ef_time;
	else
		g_Reward.time = g_Reward.max_time;
	if (g_Reward.time == g_Reward.max_time) {
		sequence++;
		skip = 0;
	}
}

void SecondSeq(void)
{
	if (g_Reward.beatNum < g_Reward.max_beatNum)
		g_Reward.beatNum += g_Reward.ef_beatNum;
	else
		g_Reward.beatNum = g_Reward.max_beatNum;

	if (g_Reward.beatNum == g_Reward.max_beatNum) {
		sequence++;
		skip = 0;
	}
}

void ThirdSeq(void)
{
	if (g_Reward.rescue_num < g_Reward.max_rescue_num)
		g_Reward.rescue_num += g_Reward.ef_rescue_num;
	else
		g_Reward.rescue_num = g_Reward.max_rescue_num;
	if (g_Reward.rescue_num == g_Reward.max_rescue_num) {
		sequence++;
		skip = 0;
	}
}
void ForthSeq(void)
{
	if (g_Reward.score < g_Reward.max_score)
		g_Reward.score += g_Reward.ef_score;
	else
		g_Reward.score = g_Reward.max_score;
	if (g_Reward.score == g_Reward.max_score && GetKeyboardTrigger(DIK_RETURN)) { 
		sequence++; 
		g_Reward.nEaseIndex = Easing::SetEase(-100.0f, SCREEN_CENTER_Y, 30.0f);
		skip = 0;
	}

}

void FifthSeq(void)
{
	if (g_Reward.rank_up > 0) {
		g_Reward.ef_rank_up *= 1.01f;
		//�����ʂ��K����I�[�o�[���Ă����璲��
		if ((int)(g_Reward.ef_rank_up) > g_Reward.rank_up)
		{
			g_Reward.ef_rank_up = (float)(g_Reward.rank_up);
		}

		g_Reward.rank_gauge += (int)(g_Reward.ef_rank_up);
		g_Reward.rank_up -= (int)(g_Reward.ef_rank_up);

		if (g_Reward.rank_gauge >= g_Reward.rank_gauge_max) {
			g_Reward.rank++;
			g_Reward.rank_gauge -= g_Reward.rank_gauge_max;
		}
	}
	if (g_Reward.rank_up <= 0 && !ef_once) {
		skip = -40;
		ef_once = TRUE;
		return;
	}
	if (g_Reward.rank_up <= 0) { 
		sequence++; 
		g_Reward.nEaseIndex = Easing::SetEase(SCREEN_CENTER_Y, SCREEN_HEIGHT + 100.0f, 60.0f);
	}
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

	float pos_y = SCREEN_HEIGHT * 0.10f;
	// ���U���g�̌o�ߎ��Ԃ�`��
	g_Result[result_var].pos = { SCREEN_WIDTH *0.6f , pos_y };
	g_Result[result_var].size = { 240.0f, 80.0f };
	g_Result[result_var].color = { 1.0f, 1.0f, 1.0f, 1.0f };
	DrawResultTexture(&g_Result[result_var]);
	pos_y += 80.0f + 8.0f;
	DrawResultTime(SCREEN_WIDTH *0.65f, pos_y, 40.0f, 80.0f, XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));

	// ���U���g�̋~���Ґ���`��
	pos_y += 80.0f + 32.0f;
	g_Result[result_var].pos = { SCREEN_WIDTH *0.6f , pos_y };
	g_Result[result_var].size = { 240.0f, 80.0f };
	g_Result[result_var].color = { 1.0f, 1.0f, 1.0f, 1.0f };
	DrawResultTexture(&g_Result[result_var]);
	pos_y += 80.0f + 8.0f;
	DrawResultNumber(g_Reward.beatNum, SCREEN_WIDTH *0.55f, pos_y, 40.0f, 80.0f, XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));

	// ���U���g�̔j�󐔂�`��
	pos_y += 80.0f + 32.0f;
	g_Result[result_var].pos = { SCREEN_WIDTH *0.6f , pos_y };
	g_Result[result_var].size = { 240.0f, 80.0f };
	g_Result[result_var].color = { 1.0f, 1.0f, 1.0f, 1.0f };
	DrawResultTexture(&g_Result[result_var]);
	pos_y += 80.0f + 8.0f;
	DrawResultNumber(g_Reward.rescue_num, SCREEN_WIDTH *0.55f, pos_y, 40.0f, 80.0f, XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));

	// ���U���g�̃X�R�A��`��
	pos_y += 160.0f + 40.0f;
	g_Result[result_var].pos = { SCREEN_WIDTH *0.6f , pos_y };
	g_Result[result_var].size = { 240.0f, 80.0f };
	g_Result[result_var].color = { 1.0f, 1.0f, 1.0f, 1.0f };
	DrawResultTexture(&g_Result[result_var]);
	pos_y += 160.0f + 8.0f;
	DrawResultNumber(g_Reward.score, SCREEN_WIDTH *0.60f, pos_y, 80.0f, 160.0f, XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));

	if (sequence >= 4)
	{
		if (sequence >= 5)
		{
			//g_Reward.set_y += 100.0f * g_Reward.dt;
			g_Reward.set_y = Easing::GetEase(g_Reward.nEaseIndex);
		}
		else if (sequence == 4)
		{
			g_Reward.set_y = Easing::GetEase(g_Reward.nEaseIndex);
		}

		if (sequence < 5) {
			g_Result[result_var].pos = { SCREEN_CENTER_X  , SCREEN_CENTER_Y };
			g_Result[result_var].size = { SCREEN_WIDTH, SCREEN_HEIGHT };
			g_Result[result_var].color = { 0.0f, 0.0f, 0.0f, 0.5f };
			DrawResultTexture(&g_Result[result_var]);
		}

		g_Result[result_var].pos = { SCREEN_CENTER_X , g_Reward.set_y };
		g_Result[result_var].size = { 800.0f, 80.0f };
		g_Result[result_var].color = { 0.5f, 0.5f, 0.5f, 1.0f };
		DrawResultGauge(&g_Result[result_var], 1.0f);


		float par = (float)(g_Reward.rank_gauge) / (float)(g_Reward.rank_gauge_max);
		g_Result[result_var].size = { 800.0f * par , 80.0f };
		g_Result[result_var].pos = { SCREEN_CENTER_X + (800.0f * (par - 1.0f)) * 0.5f, g_Reward.set_y };
		g_Result[result_var].color = { 1.0f, 1.0f, 1.0f, 1.0f };
		DrawResultGauge(&g_Result[result_var], par);

	}
}

void WinResult(void)
{
	if (!once) {
		//PlaySound(SOUND_LABEL_BGM_Win);
		
		once = TRUE;
	}
	//if (GetKeyboardTrigger(DIK_RETURN))
	//{
	//	sequence++;
	//}

	if(sequence >= MAX_RESULT_SEQUENCE && GetKeyboardTrigger(DIK_RETURN))
	SetFade(FADE_OUT, MODE_TITLE, WhiteBox);	//���󃋁[�v����悤��

}


void InitReward(void)
{
	g_Reward.beatNum = 20;
	g_Reward.rescue_num = 10;
	g_Reward.time = 60;
	g_Reward.score = 6000;
	g_Reward.rank_up = 0;

	g_Reward.ef_beatNum = 0;
	g_Reward.ef_rescue_num = 0;
	g_Reward.ef_time = 0;
	g_Reward.ef_score = 0;
	g_Reward.ef_rank_up = 1.0f;

	g_Reward.rank = 0;
	g_Reward.rank_gauge = 0;
	g_Reward.rank_gauge_max = 100;

	g_Reward.set_y -= SCREEN_CENTER_Y;
	g_Reward.dt = 0.9f;
}


//���[�h�ύX���Ɉ����p���f�[�^������ꍇ�A�����ōs��
void SetReward(void)
{
	//g_Reward.time = GAME_TIME - GetTime();
	g_Reward.time = 60;
	g_Reward.ef_beatNum = g_Reward.beatNum / 30;
	if (g_Reward.ef_beatNum < 1)
		g_Reward.ef_beatNum = 1;

	g_Reward.ef_rescue_num = g_Reward.rescue_num / 30;
	if (g_Reward.ef_rescue_num < 1)
		g_Reward.ef_rescue_num = 1;

	g_Reward.ef_time = g_Reward.time / 30;
	if (g_Reward.ef_time < 1)
		g_Reward.ef_time = 1;

	g_Reward.ef_score = g_Reward.score / 100;
	if (g_Reward.ef_score < 1)
		g_Reward.ef_score = 1;

	//�f�[�^�̈ڂ��ւ�
	g_Reward.max_beatNum = g_Reward.beatNum;
	g_Reward.max_rescue_num = g_Reward.rescue_num;
	g_Reward.max_time = g_Reward.time;
	g_Reward.max_score = g_Reward.score;

	//�\���p���l�����Z�b�g
	g_Reward.beatNum = 0;
	g_Reward.rescue_num = 0;
	g_Reward.time = 0;
	g_Reward.score = 0;
	//�����N�A�b�v�o���l�̌v�Z�������ł���
	int num = 150;
	g_Reward.rank_up = num;
}


Reward *GetReward(void) { return &g_Reward; };

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
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Result[result_numb].g_Texture);

		// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
		SetSpriteColor(g_VertexBuffer, psx, py, sx, sy, tx, 0.0f, 0.1f, 1.0f,
			color);

		// �|���S���`��
		GetDeviceContext()->Draw(4, 0);
		numb /= 10;
	}
}

//�e�N�X�`���`��
void DrawResultTexture(Result* result)
{
	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, &result->g_Texture);

	// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
	SetSpriteColor(g_VertexBuffer, result->pos.x, result->pos.y, result->size.x, result->size.y, 0.0f, 0.0f, 1.0f, 1.0f,
		result->color);

	// �|���S���`��
	GetDeviceContext()->Draw(4, 0);
}

//�e�N�X�`���`��
void DrawResultGauge(Result* result, float tx)
{
	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, &result->g_Texture);

	// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
	SetSpriteColor(g_VertexBuffer, result->pos.x, result->pos.y, result->size.x, result->size.y, 0.0f, 0.0f, 0.0f, 1.0f,
		result->color);

	// �|���S���`��
	GetDeviceContext()->Draw(4, 0);
}

void DrawResultTime(float px, float py, float sx, float sy, XMFLOAT4 color)
{
	int number = g_Reward.time;
	for (int i = 0; i < TIME_DIGIT; i++)
	{
		if (i != 1 && i != 2)	//�\�i���̏���
		{
			// �e�N�X�`���ݒ�
			GetDeviceContext()->PSSetShaderResources(0, 1, &g_Result[result_numb].g_Texture);
			// ����\�����錅�̐���
			float x = (float)(number % 10);

			// �������Ԃ̈ʒu��e�N�X�`���[���W�𔽉f
			float p_x = px - sx * i;	// �������Ԃ̕\���ʒuX
			float p_y = py;			// �������Ԃ̕\���ʒuY
			float p_w = sx;				// �������Ԃ̕\����
			float p_h = sy;				// �������Ԃ̕\������

			float tw = 1.0f / 10;		// �e�N�X�`���̕�
			float th = 1.0f / 1;		// �e�N�X�`���̍���
			float tx = x * tw;			// �e�N�X�`���̍���X���W
			float ty = 0.0f;			// �e�N�X�`���̍���Y���W

			// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
			SetSpriteColor(g_VertexBuffer, p_x, p_y, p_w, p_h, tx, ty, tw, th,
				color);

			// �|���S���`��
			GetDeviceContext()->Draw(4, 0);

			// ���̌���
			number /= 10;

		}
		else if (i == 1)	//���Ԃ̓񌅖ڂ̂�6�i���Ȃ��߁A�����𕪂���
		{
			// �e�N�X�`���ݒ�
			GetDeviceContext()->PSSetShaderResources(0, 1, &g_Result[result_numb].g_Texture);
			// ����\�����錅�̐���
			float x = (float)(number % 6);

			// �������Ԃ̈ʒu��e�N�X�`���[���W�𔽉f
			float p_x = px - sx * i;	// �������Ԃ̕\���ʒuX
			float p_y = py;			// �������Ԃ̕\���ʒuY
			float p_w = sx;				// �������Ԃ̕\����
			float p_h = sy;				// �������Ԃ̕\������

			float tw = 1.0f / 10;		// �e�N�X�`���̕�
			float th = 1.0f / 1;		// �e�N�X�`���̍���
			float tx = x * tw;			// �e�N�X�`���̍���X���W
			float ty = 0.0f;			// �e�N�X�`���̍���Y���W

			// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
			SetSpriteColor(g_VertexBuffer, p_x, p_y, p_w, p_h, tx, ty, tw, th,
				color);

			// �|���S���`��
			GetDeviceContext()->Draw(4, 0);

			// ���̌���
			number /= 6;


		}
		else if (i == 2)
		{
			// �e�N�X�`���ݒ�
			GetDeviceContext()->PSSetShaderResources(0, 1, &g_Result[result_numb_cent].g_Texture);

			// �������Ԃ̈ʒu��e�N�X�`���[���W�𔽉f
			float p_x = px - sx * i;	// �������Ԃ̕\���ʒuX
			float p_y = py;			// �������Ԃ̕\���ʒuY
			float p_w = sx;				// �������Ԃ̕\����
			float p_h = sy;				// �������Ԃ̕\������

			float tw = 1.0f;		// �e�N�X�`���̕�
			float th = 1.0f;		// �e�N�X�`���̍���
			float tx = 0.0f;			// �e�N�X�`���̍���X���W
			float ty = 0.0f;			// �e�N�X�`���̍���Y���W

			// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
			SetSpriteColor(g_VertexBuffer, p_x, p_y, p_w, p_h, tx, ty, tw, th,
				XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));

			// �|���S���`��
			GetDeviceContext()->Draw(4, 0);

		}
	}
}