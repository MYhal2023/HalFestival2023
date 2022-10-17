//=============================================================================
//
// �t�B�[���h���f������ [fieldchip.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "camera.h"
#include "debugproc.h"
#include "model.h"
#include "game.h"
#include "player.h"
#include "shadow.h"
#include "light.h"
#include "meshfield.h"
#include "collision.h"
#include "time.h"
#include "fieldchip.h"
#include "playerSet.h"
#include "sprite.h"
#include "base.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_MAX			(1)				// �e�N�X�`���̐�
#define BG_MAX				(1)				// �p�ӂ���ǂ̐�
#define BG_WIDTH	(960 * 1.0f)
#define BG_HEIGHT	(540 * 0.75f)
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static ID3D11Buffer					*g_VertexBuffer = NULL;	// ���_���
static ID3D11ShaderResourceView		*g_Texture[TEXTURE_MAX] = { NULL };	// �e�N�X�`�����
static char* g_TextureName[] = {
	"data/TEXTURE/title_bg2.png",
};
static MAP_CHIP		g_MapChip[MAX_CHIP_NUM];						// �v���C���[
static MAP_CHIP		g_MapChipObj[MAX_CHIP_NUM];						// �v���C���[
static MAP_CHIP		g_MapSet[MAX_CHIP_HEIGHT][MAX_CHIP_WIDTH + 1];
static MAP_CHIP		g_MapSetObj[MAX_CHIP_HEIGHT][MAX_CHIP_WIDTH + 1];
static FIELD_BG		g_bg[BG_MAX];
static BOOL			g_Load = FALSE;
static int m_width, m_height;
int g_BattleMap[MAX_CHIP_HEIGHT][MAX_CHIP_WIDTH + 1];
int g_BattleMapObj[MAX_CHIP_HEIGHT][MAX_CHIP_WIDTH + 1];
//=============================================================================
// ����������(�}�b�v�`�b�v�Z�b�g�Ɣw�i�̗p�ӁA�}�b�v�Z�b�g�܂�)
//=============================================================================
HRESULT InitMapChip(int map[][MAX_CHIP_WIDTH + 1], int mapObj[][MAX_CHIP_WIDTH + 1], int height, int width)
{
	ID3D11Device *pDevice = GetDevice();
	MakeVertexBG();
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
	for (int i = 0; i < MAX_CHIP_HEIGHT; i++)
	{
		for (int k = 0; k < MAX_CHIP_WIDTH; k++)
		{
			g_BattleMap[i][k] = 99;	//�S�}�b�v�`�b�v�ꏊ�����Z�b�g(99�͔z�u���Ȃ��ԍ�)
			g_BattleMapObj[i][k] = 9;	//�S�}�b�v�`�b�v�ꏊ�����Z�b�g(9�͔z�u���Ȃ��ԍ�)
		}
	}

	m_width = width;
	m_height = height;
	//�w�i�ݒ�
	for (int i = 0; i < BG_MAX; i++)
	{
		ZeroMemory(&g_bg[i].material, sizeof(g_bg[i].material));
		g_bg[i].material.Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		g_bg[i].pos = { m_width * CHIP_SIZE * 0.5f - 25.0f, 0.0f, m_height * CHIP_SIZE -25.0f};
		g_bg[i].rot = { XM_PI * -0.5f, 0.0f, 0.0f };
		g_bg[i].scl = { 1.0f, 1.0f, 1.0f };
		g_bg[i].load = TRUE;
	}
	//�}�b�v�`�b�v���f���p��
	for (int i = 0; i < MAX_CHIP_NUM; i++)
	{
		switch (i)
		{
		case ROW:
			LoadModel(MODEL_FIELD001, &g_MapChip[i].model);
			break;
		case HIGH:
			LoadModel(MODEL_FIELD002, &g_MapChip[i].model);
			break;
		case ROW_BLOOD:
			LoadModel(MODEL_FIELD003, &g_MapChip[i].model);
			break;
		case HIGH_BLOOD:
			LoadModel(MODEL_FIELD004, &g_MapChip[i].model);
			break;
		case MAX_VAL:
			break;
		}
		// ���f���̃f�B�t���[�Y��ۑ����Ă����B�F�ς��Ή��ׁ̈B
		GetModelDiffuse(&g_MapChip[i].model, &g_MapChip[i].diffuse[0]);

		g_MapChip[i].load = TRUE;

		g_MapChip[i].pos = { 0.0f, 0.0f, 0.0f };
		g_MapChip[i].rot = { 0.0f, 0.0f, 0.0f };
		g_MapChip[i].scl = { 1.0f, 1.0f, 1.0f };

		g_MapChip[i].size = CHIP_SIZE;	// �����蔻��̑傫��
	}
	//�}�b�v�`�b�v�I�u�W�F�N�g���f���p��
	for (int i = 0; i < MAX_OBJ_NUM; i++)
	{
		switch (i)
		{
		case Building:
			LoadModel(MODEL_OBJECT001, &g_MapChipObj[i].model);
			g_MapChipObj[i].scl = { 1.0f, 1.0f, 1.0f };
			break;
		case Container:
			LoadModel(MODEL_OBJECT002, &g_MapChipObj[i].model);
			g_MapChipObj[i].scl = { 0.5f, 0.5f, 0.5f };
			break;
		case MAX_VAL:
			break;
		}
		// ���f���̃f�B�t���[�Y��ۑ����Ă����B�F�ς��Ή��ׁ̈B
		GetModelDiffuse(&g_MapChipObj[i].model, &g_MapChipObj[i].diffuse[0]);

		g_MapChipObj[i].load = TRUE;

		g_MapChipObj[i].pos = { 0.0f, 0.0f, 0.0f };
		g_MapChipObj[i].rot = { 0.0f, 0.0f, 0.0f };

		g_MapChipObj[i].size = CHIP_SIZE;	// �����蔻��̑傫��
	}
	//�}�b�v�`�b�v���̃��Z�b�g
	for (int i = 0; i < MAX_CHIP_HEIGHT; i++)
	{
		for (int k = 0; k < MAX_CHIP_WIDTH; k++)
		{
			g_MapSet[i][k].pos = { 0.0f + CHIP_SIZE * k, 0.0f,  0.0f + CHIP_SIZE * i };
			g_MapSet[i][k].rot = { 0.0f, 0.0f, 0.0f };
			g_MapSet[i][k].scl = { 1.7f, 1.0f, 1.7f };
			g_MapSet[i][k].type = LowPlaces;
			g_MapSet[i][k].use = FALSE;
		}
	}
	//�}�b�v�`�b�v�I�u�W�F���̃��Z�b�g
	for (int i = 0; i < MAX_CHIP_HEIGHT; i++)
	{
		for (int k = 0; k < MAX_CHIP_WIDTH; k++)
		{
			g_MapSetObj[i][k].pos = { 0.0f + CHIP_SIZE * k, 0.0f,  0.0f + CHIP_SIZE * i };
			g_MapSetObj[i][k].rot = { 0.0f, 0.0f, 0.0f };
			g_MapSetObj[i][k].scl = { 2.0f, 2.0f, 2.0f };
			g_MapSetObj[i][k].type = LowPlaces;
			g_MapSetObj[i][k].use = FALSE;
		}
	}

	SetBattleMap(map, height, width);	//�����Ń}�b�v���Z�b�g���Ă���
	SetBattleMapObj(mapObj, height, width);	//�����Ń}�b�v���Z�b�g���Ă���

	g_Load = TRUE;
	return S_OK;

}

//=============================================================================
// �I������
//=============================================================================
void UninitMapChip(void)
{
	if (g_Load == FALSE) return;
	// ���_�o�b�t�@�̉��
	if (g_VertexBuffer)
	{
		g_VertexBuffer->Release();
		g_VertexBuffer = NULL;
	}

	for (int i = 0; i < MAX_CHIP_NUM; i++)
	{
		// ���f���̉������
		if (g_MapChip[i].load)
		{
			UnloadModel(&g_MapChip[i].model);
			g_MapChip[i].load = FALSE;
		}
	}
	for (int i = 0; i < MAX_CHIP_NUM; i++)
	{
		// ���f���̉������
		if (g_MapChipObj[i].load)
		{
			UnloadModel(&g_MapChipObj[i].model);
			g_MapChip[i].load = FALSE;
		}
	}
	g_Load = FALSE;
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateMapChip(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawMapChip(void)
{
	XMMATRIX mtxScl, mtxRot, mtxTranslate, mtxWorld;
	//�t�B�[���h�`�b�v�p�V�F�[�_�[�ɐ؂�ւ�
	//�I������Ă���`�b�v�͐F���ς��
	SwapShader(MODE_FIELD_CHIP);
	PlayerSet *ps = GetSetPos();
	Base *bs = GetBase();
	for (int i = 0; i < m_height; i++)
	{
		for (int k = 0; k < m_width; k++)
		{
			if (ps->setPos.x == g_MapSet[i][k].pos.x &&
				ps->setPos.z == g_MapSet[i][k].pos.z &&
				ps->setMode == TRUE)
				SetChip(1);
			else
				SetChip(0);

			for (int s = 0; s < bs->baseNum; s++)
			{
				if (bs->pos->x - 25.0f == g_MapSet[i][k].pos.x &&
					bs->pos->z == g_MapSet[i][k].pos.z) {
					SetChip(2);
					break;
				}
			}
			int m = g_BattleMap[i][k];
			if (m == 99)continue;	//�}�b�v�`�b�v�����B�`��s�v
			// ���[���h�}�g���b�N�X�̏�����
			mtxWorld = XMMatrixIdentity();

			// �X�P�[���𔽉f
			mtxScl = XMMatrixScaling(g_MapSet[i][k].scl.x, g_MapSet[i][k].scl.y, g_MapSet[i][k].scl.z);
			mtxWorld = XMMatrixMultiply(mtxWorld, mtxScl);

			// ��]�𔽉f
			mtxRot = XMMatrixRotationRollPitchYaw(g_MapSet[i][k].rot.x, g_MapSet[i][k].rot.y + XM_PI, g_MapSet[i][k].rot.z);
			mtxWorld = XMMatrixMultiply(mtxWorld, mtxRot);

			// �ړ��𔽉f
			mtxTranslate = XMMatrixTranslation(g_MapSet[i][k].pos.x, g_MapSet[i][k].pos.y, g_MapSet[i][k].pos.z);
			mtxWorld = XMMatrixMultiply(mtxWorld, mtxTranslate);

			// ���[���h�}�g���b�N�X�̐ݒ�
			SetWorldMatrix(&mtxWorld);

			XMStoreFloat4x4(&g_MapSet[i][k].mtxWorld, mtxWorld);

			// ���f���`��
			//�����������O�ɗp�ӂ����}�b�v�`�b�v�i���o�[���Q��
			DrawModel(&g_MapChip[m].model);
		}
	}

	SwapShader(MODE_PLANE);

	DrawMapObject();

	// �J�����O�ݒ��߂�
	SetCullingMode(CULL_MODE_BACK);
}

void DrawBG(void)
{
	// Z��r�Ȃ�
	SetDepthEnable(FALSE);
	// ���C�e�B���O�𖳌�
	SetLightEnable(FALSE);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[0]);

	XMMATRIX mtxScl, mtxRot, mtxTranslate, mtxWorld;
	//�w�i�ݒu
	for (int i = 0; i < BG_MAX; i++)
	{
		// ���[���h�}�g���b�N�X�̏�����
		mtxWorld = XMMatrixIdentity();

		// �X�P�[���𔽉f
		mtxScl = XMMatrixScaling(g_bg[i].scl.x, g_bg[i].scl.y, g_bg[i].scl.z);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxScl);

		// ��]�𔽉f
		mtxRot = XMMatrixRotationRollPitchYaw(g_bg[i].rot.x, g_bg[i].rot.y, g_bg[i].rot.z);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxRot);

		// �ړ��𔽉f
		mtxTranslate = XMMatrixTranslation(g_bg[i].pos.x, g_bg[i].pos.y, g_bg[i].pos.z);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxTranslate);

		// ���[���h�}�g���b�N�X�̐ݒ�
		SetWorldMatrix(&mtxWorld);

		// �}�e���A���̐ݒ�
		SetMaterial(g_bg[i].material);

		// �|���S���̕`��
		GetDeviceContext()->Draw(4, 0);
	}
	// Z��r����
	SetDepthEnable(TRUE);
	// ���C�e�B���O�𖳌�
	SetLightEnable(TRUE);

}

void DrawMapObject(void)
{
	XMMATRIX mtxScl, mtxRot, mtxTranslate, mtxWorld;
	for (int i = 0; i < m_height; i++)
	{
		for (int k = 0; k < m_width; k++)
		{
			int m = g_BattleMapObj[i][k];
			if (m == 9)continue;	//�}�b�v�`�b�v�����B�`��s�v
			switch (m)
			{
			case Building:
				g_MapSetObj[i][k].scl = { 2.0f, 2.0f, 2.0f };
				break;
			case Container:
				g_MapSetObj[i][k].scl = { 1.2f, 0.8f, 0.8f };
				g_MapSetObj[i][k].rot = { 0.0f, XM_PI * 0.5f, 0.0f };
				break;
			}
			// ���[���h�}�g���b�N�X�̏�����
			mtxWorld = XMMatrixIdentity();

			// �X�P�[���𔽉f
			mtxScl = XMMatrixScaling(g_MapSetObj[i][k].scl.x, g_MapSetObj[i][k].scl.y, g_MapSetObj[i][k].scl.z);
			mtxWorld = XMMatrixMultiply(mtxWorld, mtxScl);

			// ��]�𔽉f
			mtxRot = XMMatrixRotationRollPitchYaw(g_MapSetObj[i][k].rot.x, g_MapSetObj[i][k].rot.y + XM_PI, g_MapSetObj[i][k].rot.z);
			mtxWorld = XMMatrixMultiply(mtxWorld, mtxRot);

			// �ړ��𔽉f
			mtxTranslate = XMMatrixTranslation(g_MapSetObj[i][k].pos.x, g_MapSetObj[i][k].pos.y, g_MapSetObj[i][k].pos.z);
			mtxWorld = XMMatrixMultiply(mtxWorld, mtxTranslate);

			// ���[���h�}�g���b�N�X�̐ݒ�
			SetWorldMatrix(&mtxWorld);

			XMStoreFloat4x4(&g_MapSetObj[i][k].mtxWorld, mtxWorld);

			// ���f���`��
			//�����������O�ɗp�ӂ����}�b�v�`�b�v�i���o�[���Q��
			DrawModel(&g_MapChipObj[m].model);
		}
	}

}

HRESULT MakeVertexBG(void)
{
	// ���_�o�b�t�@����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	GetDevice()->CreateBuffer(&bd, NULL, &g_VertexBuffer);


	{//���_�o�b�t�@�̒��g�𖄂߂�
		D3D11_MAPPED_SUBRESOURCE msr;
		GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

		VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

		// ���_���W�̐ݒ�
		vertex[0].Position = XMFLOAT3(-BG_WIDTH / 2, 0.0f, BG_HEIGHT / 2);
		vertex[1].Position = XMFLOAT3(BG_WIDTH / 2, 0.0f, BG_HEIGHT / 2);
		vertex[2].Position = XMFLOAT3(-BG_WIDTH / 2, 0.0f, -BG_HEIGHT / 2);
		vertex[3].Position = XMFLOAT3(BG_WIDTH / 2, 0.0f, -BG_HEIGHT / 2);

		// �@���̐ݒ�
		vertex[0].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
		vertex[1].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
		vertex[2].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
		vertex[3].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);

		// �g�U���̐ݒ�
		vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`�����W�̐ݒ�
		vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);
		vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);
		vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);
		vertex[3].TexCoord = XMFLOAT2(1.0f, 1.0f);

		GetDeviceContext()->Unmap(g_VertexBuffer, 0);
	}

	return S_OK;
}

//�o�g���}�b�v�Z�b�g�B�}�b�v�z��Əc���̒����������ɓn���B���łɃ`�b�v�^�C�v���Z�b�g
void SetBattleMap(int map[][MAX_CHIP_WIDTH + 1], int height, int width)
{
	for (int i = 0; i < height; i++)
	{
		for (int k = 0; k < width; k++)
		{
			g_BattleMap[i][k] = map[i][k];
			switch (g_BattleMap[i][k])
			{
			case ROW:
			case ROW_BLOOD:
				g_MapSet[i][k].type = LowPlaces;
				break;
			case HIGH:
			case HIGH_BLOOD:
				g_MapSet[i][k].type = HighPlaces;
				break;
			}
		}
	}
}
//�o�g���}�b�v�Z�b�g�B�}�b�v�z��Əc���̒����������ɓn���B���łɃ`�b�v�^�C�v���Z�b�g
void SetBattleMapObj(int map[][MAX_CHIP_WIDTH + 1], int height, int width)
{
	for (int i = 0; i < height; i++)
	{
		for (int k = 0; k < width; k++)
		{
			g_BattleMapObj[i][k] = map[i][k];

			switch (g_MapSet[i][k].type)
			{
			case LowPlaces:
				g_MapSetObj[i][k].pos.y = 8.0f;
				break;
			case HighPlaces:
				g_MapSetObj[i][k].pos.y = 20.0f;
				break;
			}
			if(map[i][k] != 9)
			g_MapSet[i][k].type = NoEntry;	//�������炪����Ȃ�i���֎~�ŏ㏑��
		}
	}
}

//=============================================================================
// �v���C���[�����擾
//=============================================================================
MAP_CHIP *GetMapChip(void)
{
	return &g_MapChip[0];
}
//���炩���߁A���W���`�b�v�T�C�Y�ŏ��Z����������n��
//2��x���W�A1��z���W
int GetMapChiptype(int i, int k)
{
	return g_MapSet[i][k].type;
}

void SetMapChipUse(BOOL flag, int i, int k)
{
	g_MapSet[i][k].use = flag;
}

BOOL GetMapChipUse(int i, int k)
{
	return g_MapSet[i][k].use;
}

float GetMapWidth(void)
{
	return m_width * CHIP_SIZE;
}
float GetMapHeight(void)
{
	return m_height * CHIP_SIZE;
}