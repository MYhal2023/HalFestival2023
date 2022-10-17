//=============================================================================
//
// Reserve���� [ui.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "sprite.h"
#include "renderer.h"
#include "game.h"
#include "playerSet.h"
#include "reserve.h"
#include "base.h"
#include "cost.h"
#include "ui.h"
#include "text_texture.h"
#include "fade.h"
#include "debugproc.h"
#include "sound.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_MAX			(13)				// �e�N�X�`���̐�
#define CH_TEXTURE_MAX		(7)				// �L�����e�N�X�`���̐�
#define IC_TEXTURE_MAX		(9)				// �A�C�R���e�N�X�`���̐�
#define CHAR_TEXTURE_MAX	(7)				// �L�����e�N�X�`���̐�
#define SKILL_TEXTURE_MAX	(7)				// �L�����X�L���e�N�X�`���̐�
#define NUMBER_SIZE			(30.0f)			// x�����̃T�C�Y
#define COST_NUMBER_SIZE	(45.0f)			// x�����̃T�C�Y
#define BUTTON_SIZE			(106.0f)		// �{�^���̏c���T�C�Y�B�������ꂭ�炢
#define BUTTON_MAX			(4)				// ���[�T�[���I���ł���{�^����
#define ROW_NUM				(5)				// ���ɕ��ׂ郆�j�b�g��
#define HELP_TEX_NUM		(1)				// ���ɕ��ׂ郆�j�b�g��

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static ID3D11Buffer					*g_VertexBuffer = NULL;	// ���_���
static ID3D11ShaderResourceView		*g_Texture[TEXTURE_MAX] = { NULL };	// �e�N�X�`�����
static ID3D11ShaderResourceView		*g_CharTexture[CHAR_TEXTURE_MAX] = { NULL };	// �e�N�X�`�����
static ID3D11ShaderResourceView		*g_IconTexture[IC_TEXTURE_MAX] = { NULL };	// �e�N�X�`�����
static ID3D11ShaderResourceView		*g_SkillTexture[SKILL_TEXTURE_MAX] = { NULL };	// �e�N�X�`�����

static char* g_TextureName[TEXTURE_MAX] = {
	"data/TEXTURE/var.png",
	"data/TEXTURE/button.png",
	"data/TEXTURE/title_bg.png",
	"data/TEXTURE/number.png",
	"data/TEXTURE/costbox.png",
	"data/TEXTURE/arrow_right.png",
	"data/TEXTURE/t_confirm.png",
	"data/TEXTURE/t_day.png",
	"data/TEXTURE/t_powerup.png",
	"data/TEXTURE/t_start.png",
	"data/TEXTURE/t_levelup.png",
	"data/TEXTURE/t_cancel.png",
	"data/TEXTURE/var.png",
};
static char* g_CharTextureName[CH_TEXTURE_MAX] = {
	"data/TEXTURE/neutro.png",
	"data/TEXTURE/neutro.png",
	"data/TEXTURE/macro.png",
	"data/TEXTURE/thelper.png",
	"data/TEXTURE/tkiller.png",
	"data/TEXTURE/NK.png",
	"data/TEXTURE/kouen.png",

};
static char* g_IconTextureName[IC_TEXTURE_MAX] = {
	"data/TEXTURE/icon_cost.png",
	"data/TEXTURE/icon_life.png",
	"data/TEXTURE/icon_attack.png",
	"data/TEXTURE/icon_diffend.png",
	"data/TEXTURE/icon_block.png",
	"data/TEXTURE/icon_sp.png",
	"data/TEXTURE/icon_energy.png",
	"data/TEXTURE/icon_oxygen.png",
	"data/TEXTURE/icon_iron.png",
};
static char* g_SkillTextureName[SKILL_TEXTURE_MAX] = {
	"data/TEXTURE/var.png",
	"data/TEXTURE/var.png",
	"data/TEXTURE/var.png",
	"data/TEXTURE/var.png",
	"data/TEXTURE/var.png",
	"data/TEXTURE/var.png",
	"data/TEXTURE/var.png",

};

static Reserve g_Reserve;
static TEXT_TEXTURE g_text[TEXTURE_MAX];
static Button g_Button[BUTTON_MAX];
static Button g_PwButton[2];	//�L�����Z����OK�{�^��
static int cursol;
static int cursolPw;	//�p���[�A�b�v��ʂɎg����J�[�\��
static int HelpTexNum = 0;	//�w���v�̉摜����
static float cursolAlpha;	//�J�[�\�������x
static float alphaSpeed;	//�J�[�\�������x���Z��
static BOOL g_Load = FALSE;
static BOOL restart = FALSE;
HRESULT InitReserve(void)
{
	//�N�����A��x����������
	if (!restart)
	{
		g_Reserve.day = 1;
		g_Reserve.energy = 0;
		g_Reserve.oxygen = 0;
		g_Reserve.iron = 0;
		g_Reserve.mode = 99;
		g_Reserve.selectPw = 0;
		g_Reserve.pwMode = FALSE;
		restart = TRUE;
#ifdef _DEBUG
		g_Reserve.energy = 9999;
		g_Reserve.oxygen = 999;
		g_Reserve.iron = 9;
#endif
	}

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
	// �e�N�X�`������
	for (int i = 0; i < CHAR_TEXTURE_MAX; i++)
	{
		D3DX11CreateShaderResourceViewFromFile(GetDevice(),
			g_CharTextureName[i],
			NULL,
			NULL,
			&g_CharTexture[i],
			NULL);
	}
	for (int i = 0; i < IC_TEXTURE_MAX; i++)
	{
		D3DX11CreateShaderResourceViewFromFile(GetDevice(),
			g_IconTextureName[i],
			NULL,
			NULL,
			&g_IconTexture[i],
			NULL);
	}
	for (int i = 0; i < SKILL_TEXTURE_MAX; i++)
	{
		D3DX11CreateShaderResourceViewFromFile(GetDevice(),
			g_SkillTextureName[i],
			NULL,
			NULL,
			&g_SkillTexture[i],
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

	for (int i = 0; i < BUTTON_MAX; i++)
	{
		g_Button[i].color = { 1.0f, 1.0f, 1.0f, 1.0f };
		g_Button[i].pos = { 0.0f, 0.0f };
		g_Button[i].size = { 50.0f, 50.0f };
		g_Button[i].use = TRUE;
	}


	float py = BUTTON_SIZE * 0.5f + 16.0f;;
	
	g_Button[UnitPowerUp].pos.y = py + BUTTON_SIZE + 40.0f;
	g_Button[UnitPowerUp].pos.x = 8.0f + BUTTON_SIZE * 1.5f;
	
	g_Button[UnitConfirm].pos.y = g_Button[UnitPowerUp].pos.y + BUTTON_SIZE + 16.0f;
	g_Button[UnitConfirm].pos.x = 8.0f + BUTTON_SIZE * 1.5f;

	g_Button[ReserveHelp].pos.y = g_Button[UnitConfirm].pos.y + BUTTON_SIZE + 16.0f;
	g_Button[ReserveHelp].pos.x = 8.0f + BUTTON_SIZE * 1.5f;

	g_Button[GameStart].pos.y = SCREEN_HEIGHT - 40.0f - BUTTON_SIZE * 0.5f;
	g_Button[GameStart].pos.x = SCREEN_WIDTH - 16.0f - BUTTON_SIZE * 1.5f;

	g_PwButton[CanselButton].pos.y = SCREEN_HEIGHT * 0.6f;
	g_PwButton[CanselButton].pos.x = SCREEN_WIDTH * 0.8f;
	g_PwButton[CanselButton].color = { 0.2f, 0.2f, 0.2f, 1.0f };

	g_PwButton[LevelupButton].pos.y = SCREEN_HEIGHT * 0.75f;
	g_PwButton[LevelupButton].pos.x = SCREEN_WIDTH * 0.8f;
	g_PwButton[LevelupButton].color = { 0.0f, 0.5f, 1.0f, 1.0f };
	cursol = 0;
	cursolPw = 0;
	cursolAlpha = 0.5f;
	alphaSpeed = 0.02f;
	g_Load = TRUE;
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitReserve(void)
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
	// �e�N�X�`���̉��
	for (int i = 0; i < IC_TEXTURE_MAX; i++)
	{
		if (g_IconTexture[i])
		{
			g_IconTexture[i]->Release();
			g_IconTexture[i] = NULL;
		}
	}

	g_Load = FALSE;
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateReserve(void)
{
	switch (g_Reserve.mode)
	{
	case UnitPowerUp:
		UnitPowerUpMode();
		break;
	case UnitConfirm:
		UnitConfirmMode();
		break;
	case ReserveHelp:
		ReserveHelpMode();
		break;
	case 99:
		NormalRserveMode();
		break;
	}
}

//=============================================================================
// �`�揈�� �����ɑS�������Ă���̂Œ��_�o�b�t�@�ݒ蓙�͌X�ł���Ȃ�
//=============================================================================
void DrawReserve(void)
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
	
	NormalRserveModeDraw();	//�S�̋��ʕ�����`��(���ʕ��͂����ɓ����B���C���[�ɋC��t���鎖)

	const XMFLOAT4 color = { 0.0f, 0.0f, 0.0f, 0.75f };
	const XMFLOAT2 pos = { SCREEN_WIDTH * 0.55f, SCREEN_HEIGHT * 0.475f };
	XMFLOAT2 pos2 = { SCREEN_WIDTH * 0.6f, SCREEN_HEIGHT * 0.25f };
	PlayerStatus *member = GetTeam();
	//�K�v�f�ފ֘A�̕ϐ��ݒ�
	const int nowLevel = member[g_Reserve.selectPw].level;
	const float size = 100.0f;
	const float numsize = 60.0f;
	XMFLOAT4 matColor = { 0.0f, 0.0f, 0.0f, 1.0f };
	int number = 0;
	switch (g_Reserve.mode)
	{
	case UnitPowerUp:
		DrawButton(color, SCREEN_WIDTH * 0.55f, SCREEN_HEIGHT * 0.475f, SCREEN_WIDTH * 0.75f, SCREEN_HEIGHT* 0.70f);
		DrawReserveChar();
		if (g_Reserve.pwMode && member[g_Reserve.selectPw].level < MAX_LEVEL) {//�������[�h�ɂȂ�����A��ʂ̏�ɐF�X�`�悷��
			DrawCharStatus(pos, g_Reserve.selectPw);	//�X�e�[�^�X�`��
			for (int k = 0; k < MAX_MATERIAL; k++) {
				if (member[g_Reserve.selectPw].material[k].no == 99 || 
					member[g_Reserve.selectPw].material[k].value[nowLevel - 1] == 0)continue;	//�ݒ肳��ĂȂ��Ȃ�X���[
				pos2.x += (size * 1.5f) * number;	//���W�X�V���ĉ������ɕ`��
				DrawNeedMaterial(pos2, size, member[g_Reserve.selectPw].material[k].no);//��ɉ摜�`�悵�Ă���K�v�f�ސ���`��
				DrawNumberRe(member[g_Reserve.selectPw].material[k].value[nowLevel - 1], pos2.x + size * 0.25f, pos2.y + size*0.75f, numsize * 0.5f, numsize, matColor);
				number++;
			}
			//�{�^���`��
			DrawButton(g_PwButton[CanselButton].color, g_PwButton[CanselButton].pos.x, g_PwButton[CanselButton].pos.y, BUTTON_SIZE * 2.5f, BUTTON_SIZE);
			DrawTextReserve(TEXT_CANCEL, g_PwButton[CanselButton].pos.x, g_PwButton[CanselButton].pos.y, BUTTON_SIZE * 2.0f, BUTTON_SIZE,
				XMFLOAT4{ 1.0f, 1.0f, 1.0f, 1.0f });
			//�{�^���`��
			DrawButton(g_PwButton[LevelupButton].color, g_PwButton[LevelupButton].pos.x, g_PwButton[LevelupButton].pos.y, BUTTON_SIZE * 2.5f, BUTTON_SIZE);
			DrawTextReserve(TEXT_LUP, g_PwButton[LevelupButton].pos.x, g_PwButton[LevelupButton].pos.y, BUTTON_SIZE * 2.0f, BUTTON_SIZE,
				XMFLOAT4{ 1.0f, 1.0f, 1.0f, 1.0f });
			//�J�[�\���ɑΉ����ďォ�瓧���ȃ{�b�N�X��`��
			if ((cursolAlpha > 0.8f && alphaSpeed > 0.0f) || (cursolAlpha < 0.4f && alphaSpeed < 0.0f))alphaSpeed *= -1;
			cursolAlpha += alphaSpeed;
			switch (cursolPw) {
			case 0:
				DrawButton(XMFLOAT4{1.0f, 1.0f, 1.0f, cursolAlpha }, g_PwButton[CanselButton].pos.x, g_PwButton[CanselButton].pos.y, BUTTON_SIZE * 2.5f, BUTTON_SIZE);
				break;
			case 1:
				DrawButton(XMFLOAT4{ 1.0f, 1.0f, 1.0f, cursolAlpha }, g_PwButton[LevelupButton].pos.x, g_PwButton[LevelupButton].pos.y, BUTTON_SIZE * 2.5f, BUTTON_SIZE);
				break;
			}
		}
		else if (g_Reserve.pwMode && member[g_Reserve.selectPw].level >= MAX_LEVEL)
		{
			DrawMaxLevelChar(pos, g_Reserve.selectPw);
			//�{�^���`��
			DrawButton(g_PwButton[CanselButton].color, g_PwButton[CanselButton].pos.x, g_PwButton[CanselButton].pos.y, BUTTON_SIZE * 2.5f, BUTTON_SIZE);
			DrawTextReserve(TEXT_CANCEL, g_PwButton[CanselButton].pos.x, g_PwButton[CanselButton].pos.y, BUTTON_SIZE * 2.0f, BUTTON_SIZE,
				XMFLOAT4{ 1.0f, 1.0f, 1.0f, 1.0f });
			//�J�[�\���ɑΉ����ďォ�瓧���ȃ{�b�N�X��`��
			if ((cursolAlpha > 0.8f && alphaSpeed > 0.0f) || (cursolAlpha < 0.4f && alphaSpeed < 0.0f))alphaSpeed *= -1;
			cursolAlpha += alphaSpeed;
			switch (cursolPw) {
			case 0:
				DrawButton(XMFLOAT4{ 1.0f, 1.0f, 1.0f, cursolAlpha }, g_PwButton[CanselButton].pos.x, g_PwButton[CanselButton].pos.y, BUTTON_SIZE * 2.5f, BUTTON_SIZE);
				break;
			case 1:
				DrawButton(XMFLOAT4{ 1.0f, 1.0f, 1.0f, cursolAlpha }, g_PwButton[LevelupButton].pos.x, g_PwButton[LevelupButton].pos.y, BUTTON_SIZE * 2.5f, BUTTON_SIZE);
				break;
			}
		}
		break;
	case UnitConfirm:
		DrawButton(color, SCREEN_WIDTH * 0.55f, SCREEN_HEIGHT * 0.475f, SCREEN_WIDTH * 0.75f, SCREEN_HEIGHT* 0.70f);
		break;
	case ReserveHelp:
		DrawReserveHelp();
		break;
	case 99:
		break;
	}

	SetDepthEnable(TRUE);

	// ���C�e�B���O�𖳌�
	SetLightEnable(TRUE);

}

Reserve *GetReserve(void) { return &g_Reserve; };

void DrawButton(XMFLOAT4 color, float px, float py, float sx, float sy)
{
	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[Button_tx]);

	// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
	SetSpriteColor(g_VertexBuffer, px, py, sx, sy, 0.0f, 0.0f, 1.0f, 1.0f,
		color);

	// �|���S���`��
	GetDeviceContext()->Draw(4, 0);

}
//����:�\�������������A�\�����W(x,y)�A�\���T�C�Y(x����,y����)
void DrawNumberRe(int numb, float px, float py, float sx, float sy, XMFLOAT4 color)
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
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[re_number]);

		// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
		SetSpriteColor(g_VertexBuffer, psx, py, sx, sy, tx, 0.0f, 0.1f, 1.0f,
			color);

		// �|���S���`��
		GetDeviceContext()->Draw(4, 0);
		numb /= 10;
	}
}

void DrawTextReserve(int k, float px, float py, float sx, float sy, XMFLOAT4 color)	//�����ɕ`�悵�����������B
{
	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[k]);


	// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
	SetSpriteColor(g_VertexBuffer, px, py, sx, sy, 0.0f, 0.0f, 1.0f, 1.0f,color);

	// �|���S���`��
	GetDeviceContext()->Draw(4, 0);

}

void NormalRserveMode(void)
{
	if (cursol < GameStart && GetKeyboardTrigger(DIK_DOWN)) {
		cursol++;
		PlaySound(SOUND_LABEL_SE_Select);
	}
	if (cursol > 0 && GetKeyboardTrigger(DIK_UP)) {
		cursol--;
		PlaySound(SOUND_LABEL_SE_Select);
	}
	//�I������Ă���{�^���������\����
	for (int i = 0; i < BUTTON_MAX; i++)
	{
		if (i == cursol)
			g_Button[i].color = { 1.5f, 1.5f, 1.5f, 1.0f };
		else
			g_Button[i].color = { 0.5f, 0.5f, 0.5f, 1.0f };
	}

	//����{�^�����������炻��ɉ����ĉ�ʑJ��
	if (GetKeyboardTrigger(DIK_RETURN)) {
		PlaySound(SOUND_LABEL_SE_Decision);
		switch (cursol)
		{
		case UnitPowerUp:
			PowerUpButton();
			break;
		case UnitConfirm:
			ConfirmButton();
			break;
		case ReserveHelp:
			ReserveHelpButton();
			break;
		case GameStart:
			GameStartButton();
			break;
		}
	}
}

void NormalRserveModeDraw(void)
{
	//�w�i�`��
// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[Reserve_bg]);

	// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
	SetSpriteColor(g_VertexBuffer, SCREEN_CENTER_X, SCREEN_CENTER_Y, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f,
		XMFLOAT4{ 1.0f, 1.0f, 1.0f, 1.0f });

	// �|���S���`��
	GetDeviceContext()->Draw(4, 0);

	XMFLOAT2 size = { SCREEN_WIDTH, 130.0f };
	//�ۗL�f�ޗʂ̕`��
	DrawButton(XMFLOAT4{ 0.0f, 0.0f, 0.0f, 0.7f }, SCREEN_CENTER_X, size.y * 0.5f, size.x, size.y);
	XMFLOAT2 pos = { SCREEN_WIDTH * 0.45f, size.y * 0.5f };
	//�G�l���M�[��
	DrawNeedMaterial(pos, size.y * 0.8f, energy);
	pos.x += size.y * 0.7f;
	DrawNumberRe(g_Reserve.energy, pos.x, pos.y, size.y * 0.25f, size.y * 0.5f, XMFLOAT4{ 1.0f, 1.0f, 1.0f, 1.0f });
	//�_�f��
	pos.x += size.y * 1.8f;
	DrawNeedMaterial(pos, size.y * 0.8f, oxygen);
	pos.x += size.y * 0.7f;
	DrawNumberRe(g_Reserve.oxygen, pos.x, pos.y, size.y * 0.25f, size.y * 0.5f, XMFLOAT4{ 1.0f, 1.0f, 1.0f, 1.0f });
	//�S��
	pos.x += size.y * 1.8f;
	DrawNeedMaterial(pos, size.y * 0.8f, iron);
	pos.x += size.y * 0.7f;
	DrawNumberRe(g_Reserve.iron, pos.x, pos.y, size.y * 0.25f, size.y * 0.5f, XMFLOAT4{ 1.0f, 1.0f, 1.0f, 1.0f });

	//�����`��
	float px = 16.0f + BUTTON_SIZE * 0.25f;
	float py = BUTTON_SIZE * 0.5f + 16.0f;
	DrawNumberRe(g_Reserve.day, px, py, BUTTON_SIZE * 0.5f, BUTTON_SIZE, XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
	DrawTextReserve(TEXT_DAY, px + BUTTON_SIZE * 1.5f, py, BUTTON_SIZE * 2.0f, BUTTON_SIZE, XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));


	////�{�^���`��(��ɐݒu���Ă������珇�ɕ`��)
	DrawButton(g_Button[UnitPowerUp].color, g_Button[UnitPowerUp].pos.x, g_Button[UnitPowerUp].pos.y, BUTTON_SIZE * 2.5f, BUTTON_SIZE);
	DrawTextReserve(TEXT_POWERUP, g_Button[UnitPowerUp].pos.x, g_Button[UnitPowerUp].pos.y, BUTTON_SIZE * 2.0f, BUTTON_SIZE,
		XMFLOAT4{ 1.0f, 1.0f, 1.0f, 1.0f });

	DrawButton(g_Button[UnitConfirm].color, g_Button[UnitConfirm].pos.x, g_Button[UnitConfirm].pos.y, BUTTON_SIZE * 2.5f, BUTTON_SIZE);
	DrawTextReserve(TEXT_CONFIRM, g_Button[UnitConfirm].pos.x, g_Button[UnitConfirm].pos.y, BUTTON_SIZE * 2.0f, BUTTON_SIZE,
		XMFLOAT4{ 1.0f, 1.0f, 1.0f, 1.0f });
	DrawButton(g_Button[ReserveHelp].color, g_Button[ReserveHelp].pos.x, g_Button[ReserveHelp].pos.y, BUTTON_SIZE * 2.5f, BUTTON_SIZE);
	DrawTextReserve(TEXT_CONFIRM, g_Button[ReserveHelp].pos.x, g_Button[ReserveHelp].pos.y, BUTTON_SIZE * 2.0f, BUTTON_SIZE,
		XMFLOAT4{ 1.0f, 1.0f, 1.0f, 1.0f });

	DrawButton(g_Button[GameStart].color, g_Button[GameStart].pos.x, g_Button[GameStart].pos.y, BUTTON_SIZE * 2.5f, BUTTON_SIZE);
	DrawTextReserve(TEXT_START, g_Button[GameStart].pos.x, g_Button[GameStart].pos.y, BUTTON_SIZE * 2.0f, BUTTON_SIZE,
		XMFLOAT4{ 1.0f, 1.0f, 1.0f, 1.0f });

}

void UnitPowerUpMode(void)
{
	PlayerStatus *member = GetTeam();
	if (member[g_Reserve.selectPw].level >= MAX_LEVEL && g_Reserve.pwMode)
	{
		cursolPw = 0;
		if (GetKeyboardTrigger(DIK_C) || GetKeyboardTrigger(DIK_RETURN))
		{
			g_Reserve.pwMode = FALSE;
			cursolPw = 0;
			PlaySound(SOUND_LABEL_SE_Cancel);
		}
	}
	else {
		//�܂��������[�h�̑����D�悵�ď���
		if (GetKeyboardTrigger(DIK_UP) && g_Reserve.pwMode && cursolPw > 0) {
			cursolPw--;
			PlaySound(SOUND_LABEL_SE_Select);
		}
		else if (GetKeyboardTrigger(DIK_DOWN) && g_Reserve.pwMode && cursolPw <= 0) {
			cursolPw++;
			PlaySound(SOUND_LABEL_SE_Select);
		}
		if ((GetKeyboardTrigger(DIK_RETURN) || GetKeyboardTrigger(DIK_Z)) && !g_Reserve.pwMode)
		{
			g_Reserve.pwMode = TRUE;
			PlaySound(SOUND_LABEL_SE_Decision);
		}
		else if (GetKeyboardTrigger(DIK_C) && !g_Reserve.pwMode)
		{
			g_Reserve.mode = 99;
			PlaySound(SOUND_LABEL_SE_Cancel);
		}
		else if (GetKeyboardTrigger(DIK_C))
		{
			g_Reserve.pwMode = FALSE;
			cursolPw = 0;
			PlaySound(SOUND_LABEL_SE_Cancel);
		}
		else if ((GetKeyboardTrigger(DIK_RETURN) || GetKeyboardTrigger(DIK_Z)) && g_Reserve.pwMode)
		{
			switch (cursolPw) {
			case 0:
				g_Reserve.pwMode = FALSE;
				PlaySound(SOUND_LABEL_SE_Cancel);
				break;
			case 1:
				PlayerStatus *member = GetTeam();
				if (CheckPowerUpMaterial(&member[g_Reserve.selectPw]))	//�Z���N�g���Ă���L�����̓��x���A�b�v�\���H
				{
					ReduceMaterial(&member[g_Reserve.selectPw]);	//�f�ޗʂ����炷
					member[g_Reserve.selectPw].level++;	//���x���A�b�v�I
					PlaySound(SOUND_LABEL_SE_PowerUp);
				}
				break;
			}
		}

		if (g_Reserve.pwMode)return;//�������Ȃ瑼������󂯕t���Ȃ�

		if (GetKeyboardTrigger(DIK_LEFT) && g_Reserve.selectPw > 0)
		{
			g_Reserve.selectPw--;
			PlaySound(SOUND_LABEL_SE_Select);
		}
		else if (GetKeyboardTrigger(DIK_RIGHT) && g_Reserve.selectPw < GetMemberNum() - 1)
		{
			g_Reserve.selectPw++;
			PlaySound(SOUND_LABEL_SE_Select);
		}

		else if (GetKeyboardTrigger(DIK_UP) && g_Reserve.selectPw > 4)
		{
			g_Reserve.selectPw -= ROW_NUM;
			PlaySound(SOUND_LABEL_SE_Select);
		}
		else if (GetKeyboardTrigger(DIK_DOWN) && g_Reserve.selectPw < GetMemberNum() - 1)
		{
			if (g_Reserve.selectPw + ROW_NUM > GetMemberNum() - 1)
				g_Reserve.selectPw = GetMemberNum() - 1;
			else
				g_Reserve.selectPw += ROW_NUM;
			PlaySound(SOUND_LABEL_SE_Select);
		}
	}
}

void UnitConfirmMode(void)
{
	if (GetKeyboardTrigger(DIK_LEFT) && g_Reserve.selectPw > 0)
	{
		g_Reserve.selectPw--;
		PlaySound(SOUND_LABEL_SE_Select);
	}
	else if (GetKeyboardTrigger(DIK_RIGHT) && g_Reserve.selectPw < GetMemberNum() - 1)
	{
		g_Reserve.selectPw++;
		PlaySound(SOUND_LABEL_SE_Select);
	}

	if (GetKeyboardTrigger(DIK_UP) && g_Reserve.selectPw > 4)
	{
		g_Reserve.selectPw -= ROW_NUM;
		PlaySound(SOUND_LABEL_SE_Select);
	}
	else if (GetKeyboardTrigger(DIK_DOWN) && g_Reserve.selectPw < GetMemberNum() - 1)
	{
		if (g_Reserve.selectPw + ROW_NUM > GetMemberNum() - 1)
			g_Reserve.selectPw = GetMemberNum() - 1;
		else
			g_Reserve.selectPw += ROW_NUM;
		PlaySound(SOUND_LABEL_SE_Select);
	}
	if (GetKeyboardTrigger(DIK_RETURN))
	{

	}

	if (GetKeyboardTrigger(DIK_C))
	{
		g_Reserve.mode = 99;
		PlaySound(SOUND_LABEL_SE_Cancel);
	}
}

void PowerUpButton(void)
{
	g_Reserve.mode = UnitPowerUp;
}

void ConfirmButton(void)
{
	g_Reserve.mode = UnitConfirm;
}

void ReserveHelpButton(void)
{
	g_Reserve.mode = ReserveHelp;
}

void GameStartButton(void)
{
	SetFade(FADE_OUT, MODE_GAME, battleFade);
}

int GetDay(void)
{
	return g_Reserve.day;
}

//=============================================================================
// �L�����{�b�N�X�`�揈��
//=============================================================================
void DrawReserveChar(void)
{
	const float boxsize = 180.0f;	//�{�b�N�X�T�C�Y��`
	const float boxbuff = 24.0f;
	float buffx = 0.0f;	//�{�b�N�X�Ԃ̋����������J����
	float buffy = 0.0f;	//�{�b�N�X�Ԃ̋����������J����
	const int rowNum = 5;
	int k = 0;
	for (int i = 0; i < MAX_PLAYER_SET; i++)
	{
		PlayerStatus *member = GetTeam();

		if (member[i].use != TRUE)continue;	//���g�p�Ґ��g�̓X���[

		if (k % rowNum != 0)buffx = boxbuff * (k % rowNum);
		else buffx = 0.0f;

		if (k >= rowNum)buffy = boxbuff;
		//�E���珇�ԂɁA�Ґ��̍Ō������`��
		XMFLOAT2 pos = { (SCREEN_WIDTH * 0.25f) + (k %ROW_NUM) * boxsize + buffx, (SCREEN_HEIGHT *0.2f) + boxsize * (0.5f + (float)(k/ ROW_NUM)) + buffy};
		//�L����ID�𒊏o���ăL�����N�^�[���ŏ��ɕ`��
		int id = member[i].charID;
		// �e�N�X�`���ݒ�
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_CharTexture[id]);
		// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
		SetSpriteColor(g_VertexBuffer, pos.x, pos.y, boxsize, boxsize, 0.0f, 0.0f, 1.0f, 1.0f,
			XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));

		// �|���S���`��
		GetDeviceContext()->Draw(4, 0);


		//�L�����̏�Ƀ{�b�N�X��`��
		// �e�N�X�`���ݒ�
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[re_box]);

		// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
		SetSpriteColor(g_VertexBuffer, pos.x, pos.y, boxsize, boxsize, 0.0f, 0.0f, 1.0f, 1.0f,
			XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));

		// �|���S���`��
		GetDeviceContext()->Draw(4, 0);

		//�J�[�\���������Ă���Ȃ炻����ۂ��{�b�N�X���d�˂ĕ`��
		if (k == g_Reserve.selectPw) {
			// �e�N�X�`���ݒ�
			GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[Button_bg]);

			// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
			SetSpriteColor(g_VertexBuffer, pos.x, pos.y, boxsize, boxsize, 0.0f, 0.0f, 1.0f, 1.0f,
				XMFLOAT4(1.0f, 1.0f, 1.0f, 0.25f));

			// �|���S���`��
			GetDeviceContext()->Draw(4, 0);
		}
		k++;

	}
}

//�����F�\���̒��S�ʒu�ƃL�����X�e�[�^�X�|�C���^�[
void DrawCharStatus(XMFLOAT2 pos,int k)
{
	PlayerStatus *member = GetTeam();
	//���n�̘g��`��
	const float sizeX = SCREEN_WIDTH * 0.75f;
	const float sizeY = SCREEN_HEIGHT * 0.70f;
	XMFLOAT4 color = { 0.4f, 0.4f, 1.0f, 1.0f };
	DrawButton(color, pos.x, pos.y, sizeX, sizeY);

	//�L�����摜�`��
	const float boxsize = 180.0f;	//�{�b�N�X�T�C�Y��`
	const int id = member[k].charID;
	float posX = pos.x - sizeX * 0.36f;
	float posY = pos.y - sizeY * 0.375f;
	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, &g_CharTexture[id]);
	// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
	SetSpriteColor(g_VertexBuffer, posX, posY, boxsize, boxsize, 0.0f, 0.0f, 1.0f, 1.0f,
		XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));

	// �|���S���`��
	GetDeviceContext()->Draw(4, 0);
	posX -= boxsize * 0.35f;
	XMFLOAT2 set = { posX, posY + boxsize * 0.75f };
	DrawCharAllStatus(set, k);

	const float arrow = 160.0f * 0.25f;
	for (int i = 0; i < 6; i++) {
		for (int k = 0; k < 3; k++) {
			// �e�N�X�`���ݒ�
			GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[arRight]);
			// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
			SetSpriteColor(g_VertexBuffer, posX + boxsize * 1.25f + k * arrow * 0.75f, set.y + i * arrow + i * 52.0f, arrow, arrow, 0.0f, 0.0f, 1.0f, 1.0f,
				XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));

			// �|���S���`��
			GetDeviceContext()->Draw(4, 0);
		}
	}
	// �|���S���`��
	GetDeviceContext()->Draw(4, 0);
	posX += sizeX * 0.30f;
	set = { posX , posY + boxsize * 0.75f };
	member[k].level++;
	DrawCharAllStatus(set, k);
	member[k].level--;
}

void DrawCharAllStatus(XMFLOAT2 pos, int k)
{
	PlayerStatus *member = GetTeam();
	//�R�X�g�`��
	float posX = pos.x;
	float posY = pos.y;
	const float iconSize = 75.0f;	//�{�b�N�X�T�C�Y��`
	const float iconBuff = 16.0f;
	float buffX = iconSize + iconBuff;
	int level = member[k].level - 1;
	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, &g_IconTexture[icCost]);
	// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
	SetSpriteColor(g_VertexBuffer, posX, posY, iconSize, iconSize, 0.0f, 0.0f, 1.0f, 1.0f,
		XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));

	float isx = iconSize - 8.0f;
	posX = pos.x + isx;
	posY = pos.y + buffX * 0.0f;
	// �|���S���`��
	GetDeviceContext()->Draw(4, 0);
	DrawNumberRe(member[k].cost[level], posX, posY, iconSize * 0.5f, iconSize, XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));


	//���C�t�`��
	posX = pos.x;
	posY = pos.y + buffX * 1.0f;
	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, &g_IconTexture[icLife]);
	// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
	SetSpriteColor(g_VertexBuffer, posX, posY, iconSize, iconSize, 0.0f, 0.0f, 1.0f, 1.0f,
		XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));

	posX = pos.x + isx;
	posY = pos.y + buffX * 1.0f;
	// �|���S���`��
	GetDeviceContext()->Draw(4, 0);
	DrawNumberRe(member[k].lifeMax[level], posX, posY, iconSize * 0.5f, iconSize, XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));


	//�U���͕`��
	posX = pos.x;
	posY = pos.y + buffX * 2.0f;
	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, &g_IconTexture[icAttack]);
	// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
	SetSpriteColor(g_VertexBuffer, posX, posY, iconSize, iconSize, 0.0f, 0.0f, 1.0f, 1.0f,
		XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));

	posX = pos.x + isx;
	posY = pos.y + buffX * 2.0f;
	// �|���S���`��
	GetDeviceContext()->Draw(4, 0);
	DrawNumberRe(member[k].power[level], posX, posY, iconSize * 0.5f, iconSize, XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));


	//�h��͕`��
	posX = pos.x;
	posY = pos.y + buffX * 3.0f;
	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, &g_IconTexture[icDiffend]);
	// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
	SetSpriteColor(g_VertexBuffer, posX, posY, iconSize, iconSize, 0.0f, 0.0f, 1.0f, 1.0f,
		XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));

	posX = pos.x + isx;
	posY = pos.y + buffX * 3.0f;
	// �|���S���`��
	GetDeviceContext()->Draw(4, 0);
	DrawNumberRe(member[k].diffend[level], posX, posY, iconSize * 0.5f, iconSize, XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));


	//�u���b�N���`��
	posX = pos.x;
	posY = pos.y + buffX * 4.0f;
	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, &g_IconTexture[icBlock]);
	// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
	SetSpriteColor(g_VertexBuffer, posX, posY, iconSize, iconSize, 0.0f, 0.0f, 1.0f, 1.0f,
		XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));

	posX = pos.x + isx;
	posY = pos.y + buffX * 4.0f;
	// �|���S���`��
	GetDeviceContext()->Draw(4, 0);
	DrawNumberRe(member[k].blockMax, posX, posY, iconSize * 0.5f, iconSize, XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));

	//SP�`��
	posX = pos.x;
	posY = pos.y + buffX * 5.0f;
	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, &g_IconTexture[icSp]);
	// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
	SetSpriteColor(g_VertexBuffer, posX, posY, iconSize, iconSize, 0.0f, 0.0f, 1.0f, 1.0f,
		XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));

	posX = pos.x + isx;
	posY = pos.y + buffX * 5.0f;
	// �|���S���`��
	GetDeviceContext()->Draw(4, 0);
	DrawNumberRe(member[k].spMax[level], posX, posY, iconSize * 0.5f, iconSize, XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));

}
//need���ď����Ă��邯�ǁA���ʂɎg���܂킵�\
//�����ɍ��W�ƕ`�悷��f��ID�������Ă���
void DrawNeedMaterial(XMFLOAT2 pos, float size, int no)
{
	XMFLOAT2 texSize = { size, size };
	//�Ƃ肠�������n�`��
	XMFLOAT4 color = { 0.0f, 0.0f, 0.0f, 1.0f };
	DrawButton(color, pos.x, pos.y, texSize.x, texSize.y);

	//�e�N�X�`���摜�̐ݒ�
	int texNo = 0;
	switch (no)
	{
	case energy:
		texNo = icEnergy;
		break;
	case oxygen:
		texNo = icOxygen;
		break;
	case iron:
		texNo = icIron;
		break;
	}
	//�A�C�R���`��
	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, &g_IconTexture[texNo]);
	// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
	SetSpriteColor(g_VertexBuffer, pos.x, pos.y, texSize.x * 0.9f, texSize.y * 0.9f, 0.0f, 0.0f, 1.0f, 1.0f,
		XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));

	// �|���S���`��
	GetDeviceContext()->Draw(4, 0);

}
//�����ɂ͋����Ώۂ̃A�h���X�������Ă���
BOOL CheckPowerUpMaterial(PlayerStatus *member)
{
	int level = member->level;
	for (int i = 0; i < MAX_MATERIAL; i++) {
		//�K�v�ʂ������ʂ������Ă�����FALE��Ԃ�
		switch(member->material[i].no){
		case energy:
			if (member->material[i].value[level - 1] > g_Reserve.energy)return FALSE;
			break;
		case oxygen:
			if (member->material[i].value[level - 1] > g_Reserve.oxygen)return FALSE;
			break;
		case iron:
			if (member->material[i].value[level - 1] > g_Reserve.iron)return FALSE;
			break;
		}
	}

	return TRUE;
}

void ReduceMaterial(PlayerStatus *member)
{
	int level = member->level;
	for (int i = 0; i < MAX_MATERIAL; i++) {
		//�K�v�ʂ������ʂ������Ă�����FALE��Ԃ�
		switch (member->material[i].no) {
		case energy:
			g_Reserve.energy -= member->material[i].value[level - 1];
			break;
		case oxygen:
			g_Reserve.oxygen -= member->material[i].value[level - 1];
			break;
		case iron:
			g_Reserve.iron -= member->material[i].value[level - 1];
			break;
		}
	}
}

void ReserveHelpMode(void)
{
	if (GetKeyboardTrigger(DIK_RIGHT)) {
		HelpTexNum++;
		PlaySound(SOUND_LABEL_SE_Select);
	}
	else if (GetKeyboardTrigger(DIK_LEFT) && HelpTexNum > 0) {
		HelpTexNum--;
		PlaySound(SOUND_LABEL_SE_Select);
	}

	//�w���v�摜���I�[�o�[���Ă����烊�Z�b�g
	if (HelpTexNum >= HELP_TEX_NUM || GetKeyboardTrigger(DIK_C))
	{
		HelpTexNum = 0;
		g_Reserve.mode = 99;
		PlaySound(SOUND_LABEL_SE_Cancel);
	}
}

void DrawReserveHelp(void)
{
	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[Help_ReserveTex + HelpTexNum]);
	const XMFLOAT2 pos = { SCREEN_CENTER_X, SCREEN_CENTER_Y };
	const XMFLOAT2 texSize = { 1600.0f, 900.0f };
	// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
	SetSpriteColor(g_VertexBuffer, pos.x, pos.y, texSize.x, texSize.y, 0.0f, 0.0f, 1.0f, 1.0f,
		XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));

	// �|���S���`��
	GetDeviceContext()->Draw(4, 0);
}

void DrawMaxLevelChar(XMFLOAT2 pos, int k)
{
	PlayerStatus *member = GetTeam();
	//���n�̘g��`��
	const float sizeX = SCREEN_WIDTH * 0.75f;
	const float sizeY = SCREEN_HEIGHT * 0.70f;
	XMFLOAT4 color = { 0.4f, 0.4f, 1.0f, 1.0f };
	DrawButton(color, pos.x, pos.y, sizeX, sizeY);

	//�L�����摜�`��
	const float boxsize = 180.0f;	//�{�b�N�X�T�C�Y��`
	const int id = member[k].charID;
	float posX = pos.x - sizeX * 0.36f;
	float posY = pos.y - sizeY * 0.375f;
	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, &g_CharTexture[id]);
	// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
	SetSpriteColor(g_VertexBuffer, posX, posY, boxsize, boxsize, 0.0f, 0.0f, 1.0f, 1.0f,
		XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));

	// �|���S���`��
	pos.y = 180.0f*0.75f + pos.y - SCREEN_HEIGHT * 0.70f * 0.375f;
	pos.x = pos.x - SCREEN_WIDTH * 0.75f * 0.36f - 180.0f * 0.35f;
	GetDeviceContext()->Draw(4, 0);
	DrawCharAllStatus(pos, k);
}

void DrawCharSkill(XMFLOAT2 pos, int k)
{

}