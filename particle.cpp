//=============================================================================
//
// �p�[�e�B�N������ [particle.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "renderer.h"
#include "input.h"
#include "camera.h"
#include "model.h"
#include "shadow.h"
#include "particle.h"
#include "player.h"
#include "math.h"
#include "meshwall.h"
#include <iostream>
#include <fstream>

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_MAX			(2)			// �e�N�X�`���̐�

#define	PARTICLE_SIZE_X		(40.0f)		// ���_�T�C�Y
#define	PARTICLE_SIZE_Y		(40.0f)		// ���_�T�C�Y
#define	VALUE_MOVE_PARTICLE	(5.0f)		// �ړ����x

#define	MAX_PARTICLE		(700)		// �p�[�e�B�N���ő吔
#define	MAX_PARTICLE_POINTER		(10)		// �p�[�e�B�N���ő吔

#define	DISP_SHADOW						// �e�̕\��
//#undef DISP_SHADOW

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	XMFLOAT4		col;			//�ۑ��p�}�e���A���J���[
	XMFLOAT3		pos;			// �ʒu
	XMFLOAT3		rot;			// ��]
	XMFLOAT3		scale;			// �X�P�[��
	XMFLOAT3		move;			// �ړ���
	MATERIAL		material;		// �}�e���A��
	float			fSizeX;			// ��
	float			fSizeY;			// ����
	int				nLife;			// ����
	int				nDecay;			// �����^�C�~���O(nDecay <= nLife)
	int				g_TexNo;
	int			blend;
	BOOL			bUse;			// �g�p���Ă��邩�ǂ���

} PARTICLE;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexParticle(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static ID3D11Buffer					*g_VertexBuffer = NULL;		// ���_�o�b�t�@

static ID3D11ShaderResourceView		*g_Texture[TEXTURE_MAX] = { NULL };	// �e�N�X�`�����
static int							g_TexNo;					// �e�N�X�`���ԍ�

static PARTICLE					g_aParticle[MAX_PARTICLE];		// �p�[�e�B�N�����[�N
static PARTICLE*				g_pParticle[MAX_PARTICLE_POINTER];				//�p�[�e�B�N�����[�N�̃|�C���^�[
static XMFLOAT3					g_posBase;						// �r���{�[�h�����ʒu
static float					g_fWidthBase = 5.0f;			// ��̕�
static float					g_fHeightBase = 10.0f;			// ��̍���
static float					g_roty = 0.0f;					// �ړ�����
static float					g_spd = 0.0f;					// �ړ��X�s�[�h
using namespace std;
static ofstream fout;
static int rand_angle = 1;
static int rand_length = 1;
static int rand_high = 1;
static int tex_num = 0;
static float scale = 0.0f;
static int for_p_num = 1;
static int p_decay = 40;
static int p_Life = 120;
static BOOL blend_mode = FALSE;
static char *g_TextureName[TEXTURE_MAX] =
{
	"data/TEXTURE/effect000.jpg",
	"data/TEXTURE/var.png",
};

static BOOL						g_Load = FALSE;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitParticle(void)
{
	// ���_���̍쐬
	MakeVertexParticle();

	// �e�N�X�`������
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

	g_TexNo = 0;

	// �p�[�e�B�N�����[�N�̏�����
	for(int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		g_aParticle[nCntParticle].pos = XMFLOAT3(0.0f, 0.0f, 0.0f);
		g_aParticle[nCntParticle].rot = XMFLOAT3(0.0f, 0.0f, 0.0f);
		g_aParticle[nCntParticle].scale = XMFLOAT3(1.0f, 1.0f, 1.0f);
		g_aParticle[nCntParticle].move = XMFLOAT3(1.0f, 1.0f, 1.0f);

		ZeroMemory(&g_aParticle[nCntParticle].material, sizeof(g_aParticle[nCntParticle].material));
		g_aParticle[nCntParticle].material.Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

		g_aParticle[nCntParticle].fSizeX = PARTICLE_SIZE_X;
		g_aParticle[nCntParticle].fSizeY = PARTICLE_SIZE_Y;
		g_aParticle[nCntParticle].nLife = 0;
		g_aParticle[nCntParticle].bUse = FALSE;
	}

	for (int i = 0; i < MAX_PARTICLE_POINTER; i++)
	{
		g_pParticle[i] = nullptr;
	}

	g_posBase = XMFLOAT3(0.0f, 0.0f, 0.0f);
	g_roty = 0.0f;
	g_spd = 0.0f;

	g_Load = TRUE;
	fout.open("particle_data.txt");

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitParticle(void)
{
	if (g_Load == FALSE) return;

	//�e�N�X�`���̉��
	for (int nCntTex = 0; nCntTex < TEXTURE_MAX; nCntTex++)
	{
		if (g_Texture[nCntTex] != NULL)
		{
			g_Texture[nCntTex]->Release();
			g_Texture[nCntTex] = NULL;
		}
	}

	// ���_�o�b�t�@�̉��
	if (g_VertexBuffer != NULL)
	{
		g_VertexBuffer->Release();
		g_VertexBuffer = NULL;
	}

	g_Load = FALSE;
	fout.close();

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateParticle(void)
{
	//PLAYER *pPlayer = GetPlayer();
	//g_posBase = pPlayer->pos;

	{
		for (int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
		{
			if (g_aParticle[nCntParticle].bUse)
			{// �g�p��
				g_aParticle[nCntParticle].pos.x += g_aParticle[nCntParticle].move.x;
				g_aParticle[nCntParticle].pos.z += g_aParticle[nCntParticle].move.z;

				g_aParticle[nCntParticle].pos.y += g_aParticle[nCntParticle].move.y;

				g_aParticle[nCntParticle].move.x += (g_aParticle[nCntParticle].move.x) * 0.015f;
				g_aParticle[nCntParticle].move.y += (g_aParticle[nCntParticle].move.y) * 0.015f;
				g_aParticle[nCntParticle].move.z += (g_aParticle[nCntParticle].move.z) * 0.015f;

				if(MeshWallHit(g_aParticle[nCntParticle].pos, 50.0f))
					g_aParticle[nCntParticle].bUse = FALSE;

				g_aParticle[nCntParticle].nLife--;
				if (g_aParticle[nCntParticle].nLife <= 0)
				{
					g_aParticle[nCntParticle].bUse = FALSE;
				}
				else
				{
					//���Z�����Ȃ̂ŁA�����ɂȂ��Ă����悤�Ɍ�����
					if (g_aParticle[nCntParticle].nLife <= g_aParticle[nCntParticle].nDecay)
					{
						g_aParticle[nCntParticle].material.Diffuse.x = g_aParticle[nCntParticle].col.x - (float)(80 - g_aParticle[nCntParticle].nLife) / 80 * g_aParticle[nCntParticle].col.x;
						g_aParticle[nCntParticle].material.Diffuse.y = g_aParticle[nCntParticle].col.y - (float)(80 - g_aParticle[nCntParticle].nLife) / 80 * g_aParticle[nCntParticle].col.y;
						g_aParticle[nCntParticle].material.Diffuse.z = g_aParticle[nCntParticle].col.z - (float)(80 - g_aParticle[nCntParticle].nLife) / 80 * g_aParticle[nCntParticle].col.z;
					}

					if(g_aParticle[nCntParticle].nLife <= 20)
					{
						// ���l�ݒ�
						g_aParticle[nCntParticle].material.Diffuse.w -= 0.05f;
						if(g_aParticle[nCntParticle].material.Diffuse.w < 0.0f)
						{
							g_aParticle[nCntParticle].material.Diffuse.w = 0.0f;
						}
					}
				}
			}
		}

		//// �p�[�e�B�N������
		//{
		//	XMFLOAT3 pos;
		//	XMFLOAT3 move;
		//	float fAngle, fLength;
		//	int nLife;
		//	float fSize;

		//	pos = g_posBase;

		//	fAngle = (float)(rand() % 628 - 314) / 100.0f;
		//	fLength = rand() % (int)(g_fWidthBase * 200 ) / 100.0f - g_fWidthBase;
		//	move.x = sinf(fAngle) * fLength;
		//	move.y = rand() % 300 / 100.0f + g_fHeightBase;
		//	move.z = cosf(fAngle) * fLength;

		//	nLife = rand() % 100 + 150;  

		//	fSize = (float)(rand() % 30 + 20);

		//	pos.y = fSize / 2;

		//	// �r���{�[�h�̐ݒ�
		//	SetParticle(pos, move, XMFLOAT4(0.8f, 0.7f, 0.2f, 0.85f), fSize, fSize, nLife);
		//}
		//if (GetKeyboardPress(DIK_SPACE))
		//{
		//	for (int i = 0; i < for_p_num; i++) {
		//		CAMERA *cam = GetCamera();
		//		XMFLOAT3 move = { 0.0f, 0.0f, 0.0f, };			
		//		float fAngle = (float)(rand() % rand_angle);	//���Z�������(�������ʂ̐������傫���قǁA���E�ɂ΂�����o��)
		//		fAngle = XMConvertToRadians(fAngle);
		//		float fLength = (float)(rand() % rand_length + 1) * 0.1f;	//x��z�����̉��Z���x���̌��ʂ��傫���Ƒf��������
		//		float fHigh = (float)(rand() % rand_high + 1) * 0.1f;	//x��z�����̉��Z���x���̌��ʂ��傫���Ƒf��������
		//		move.x += cosf(fAngle) * fLength;
		//		move.y += sinf(fAngle) * fHigh;			//�����̈ړ����Z��
		//		//move.z += cosf(fAngle) * fLength;
		//		
		//		float angle = atan2f(move.y, move.x);
		//		XMFLOAT3 scl = { 0.025f + scale, 0.4f, 0.025f +scale};	//�g�嗦
		//		XMFLOAT3 rot = { 0.0f, cam->rot.y, 0.0f };	//��]���B������K�v�Ȃ�
		//		int nLife = rand() % p_Life + p_decay;
		//		rot.z = angle - XM_PI * 0.5f;
		//		rot.y = cam->rot.y;
		//		SetParticle(XMFLOAT3(0.0f, 30.0f, 100.0f), move, rot, scl, XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), nLife, p_decay, tex_num);
		//	}
		//}
		//if (GetKeyboardPress(DIK_1))
		//{
		//	if(rand_angle < 360)
		//	rand_angle += 1;
		//}
		//if (GetKeyboardPress(DIK_2))
		//{
		//	if(rand_angle > 2)
		//	rand_angle -= 1;
		//}
		//if (GetKeyboardTrigger(DIK_3))
		//{
		//	rand_length += 1;
		//}
		//if (GetKeyboardTrigger(DIK_4))
		//{
		//	if (rand_length > 2)
		//	rand_length -= 1;
		//}
		//if (GetKeyboardTrigger(DIK_5))
		//{
		//	rand_high += 1;
		//}
		//if (GetKeyboardTrigger(DIK_6))
		//{
		//	if (rand_high > 2)
		//		rand_high -= 1;
		//}
		//if (GetKeyboardTrigger(DIK_7))
		//{
		//	scale += 0.05f;
		//}
		//if (GetKeyboardTrigger(DIK_8))
		//{
		//	if (scale > 0.05f)
		//		scale -= 0.05f;
		//}
		//if (GetKeyboardTrigger(DIK_J))
		//{
		//	if (tex_num == 0)
		//		tex_num = 1;
		//	else if (tex_num == 1)
		//		tex_num = 0;
		//}
		//if (GetKeyboardTrigger(DIK_K))
		//{
		//	if(blend_mode)
		//	blend_mode = FALSE;
		//	else blend_mode = TRUE;
		//}
		//if (GetKeyboardTrigger(DIK_9))
		//{
		//	if (for_p_num < 10)
		//	for_p_num++;
		//}
		//if (GetKeyboardTrigger(DIK_0))
		//{
		//	if (for_p_num > 2)
		//		for_p_num--;
		//}
		//if (GetKeyboardPress(DIK_M))
		//{
		//	if (p_decay > 10)
		//		p_decay--;
		//}
		//if (GetKeyboardPress(DIK_N))
		//{
		//	if (p_decay < 120)
		//		p_decay++;
		//}
		//if (GetKeyboardPress(DIK_B))
		//{
		//	if (p_Life > 1)
		//		p_Life--;
		//}
		//if (GetKeyboardPress(DIK_V))
		//{
		//	if (p_Life < 180)
		//		p_Life++;
		//}
		//if (GetKeyboardTrigger(DIK_RETURN))
		//{
		//	fout << "�p�[�e�B�N���X�e�[�^�X" << endl;
		//	fout << "�p�x�̃����_�����lrand_angle:" << rand_angle << endl;
		//	fout << "�򋗗��̃����_�����lrand_length:" << rand_length << endl;
		//	fout << "��ԍ����̃����_�����lrand_high:" << rand_high << endl;
		//	fout << "�p�[�e�B�N���e�N�X�`��tex_num:" << tex_num << endl;
		//	fout << "�u�����h���[�hblend_mode:" << blend_mode << endl;
		//	fout << "�X�P�[��scale:" << scale << endl;
		//	fout << "�J��Ԃ���for_p_num:" << for_p_num << endl;
		//	fout << "�t�F�[�h�����Ȃ��t���[����p_Life:" << p_Life << endl;
		//	fout << "�t�F�[�h�J�n�t���[��p_decay:" << p_decay << endl;
		//	fout << endl << endl;
		//} 
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawParticle(void)
{
	XMMATRIX mtxScl, mtxRot,mtxTranslate, mtxWorld, mtxView;
	CAMERA *cam = GetCamera();

	// ���C�e�B���O�𖳌���
	SetLightEnable(FALSE);


	// Z��r����
	SetDepthEnable(FALSE);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);


	for(int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		if (g_aParticle[nCntParticle].bUse)
		{
			// ���Z�����ɐݒ�
			switch (g_aParticle[nCntParticle].blend) {
			case 0:
				SetBlendState(BLEND_MODE_ALPHABLEND);
				break;
			case 1:
				SetBlendState(BLEND_MODE_ADD);
				break;
			case 2:
				SetBlendState(BLEND_MODE_SUBTRACT);
				break;
			}
			// �e�N�X�`���ݒ�
			GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[g_aParticle[nCntParticle].g_TexNo]);

			// ���[���h�}�g���b�N�X�̏�����
			mtxWorld = XMMatrixIdentity();

			// �r���[�}�g���b�N�X���擾
			mtxView = XMLoadFloat4x4(&cam->mtxView);

			//mtxWorld = XMMatrixInverse(nullptr, mtxView);
			//mtxWorld.r[3].m128_f32[0] = 0.0f;
			//mtxWorld.r[3].m128_f32[1] = 0.0f;
			//mtxWorld.r[3].m128_f32[2] = 0.0f;

						// ������������������
			//mtxWorld.r[0].m128_f32[0] = mtxView.r[0].m128_f32[0];
			//mtxWorld.r[0].m128_f32[1] = mtxView.r[1].m128_f32[0];
			//mtxWorld.r[0].m128_f32[2] = mtxView.r[2].m128_f32[0];

			//mtxWorld.r[1].m128_f32[0] = mtxView.r[0].m128_f32[1];
			//mtxWorld.r[1].m128_f32[1] = mtxView.r[1].m128_f32[1];
			//mtxWorld.r[1].m128_f32[2] = mtxView.r[2].m128_f32[1];

			//mtxWorld.r[2].m128_f32[0] = mtxView.r[0].m128_f32[2];
			//mtxWorld.r[2].m128_f32[1] = mtxView.r[1].m128_f32[2];
			//mtxWorld.r[2].m128_f32[2] = mtxView.r[2].m128_f32[2];

			// �X�P�[���𔽉f
			mtxScl = XMMatrixScaling(g_aParticle[nCntParticle].scale.x, g_aParticle[nCntParticle].scale.y, g_aParticle[nCntParticle].scale.z);
			mtxWorld = XMMatrixMultiply(mtxWorld, mtxScl);

			// ��]�𔽉f
			mtxRot = XMMatrixRotationRollPitchYaw(g_aParticle[nCntParticle].rot.x, g_aParticle[nCntParticle].rot.y, g_aParticle[nCntParticle].rot.z);
			mtxWorld = XMMatrixMultiply(mtxWorld, mtxRot);


			// �ړ��𔽉f
			mtxTranslate = XMMatrixTranslation(g_aParticle[nCntParticle].pos.x, g_aParticle[nCntParticle].pos.y, g_aParticle[nCntParticle].pos.z);
			mtxWorld = XMMatrixMultiply(mtxWorld, mtxTranslate);

			// ���[���h�}�g���b�N�X�̐ݒ�
			SetWorldMatrix(&mtxWorld);

			// �}�e���A���ݒ�
			SetMaterial(g_aParticle[nCntParticle].material);

			// �|���S���̕`��
			GetDeviceContext()->Draw(4, 0);
		}
	}

	// ���C�e�B���O��L����
	SetLightEnable(TRUE);

	// �ʏ�u�����h�ɖ߂�
	SetBlendState(BLEND_MODE_ALPHABLEND);

	// Z��r�L��
	SetDepthEnable(TRUE);

}

//=============================================================================
// ���_���̍쐬
//=============================================================================
HRESULT MakeVertexParticle(void)
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
		vertex[0].Position = XMFLOAT3(-PARTICLE_SIZE_X / 2, PARTICLE_SIZE_Y / 2, 0.0f);
		vertex[1].Position = XMFLOAT3(PARTICLE_SIZE_X / 2, PARTICLE_SIZE_Y / 2, 0.0f);
		vertex[2].Position = XMFLOAT3(-PARTICLE_SIZE_X / 2, -PARTICLE_SIZE_Y / 2, 0.0f);
		vertex[3].Position = XMFLOAT3(PARTICLE_SIZE_X / 2, -PARTICLE_SIZE_Y / 2, 0.0f);

		// �@���̐ݒ�
		vertex[0].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
		vertex[1].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
		vertex[2].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
		vertex[3].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

		// ���ˌ��̐ݒ�
		vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`�����W�̐ݒ�
		vertex[0].TexCoord = { 0.0f, 0.0f };
		vertex[1].TexCoord = { 1.0f, 0.0f };
		vertex[2].TexCoord = { 0.0f, 1.0f };
		vertex[3].TexCoord = { 1.0f, 1.0f };

		GetDeviceContext()->Unmap(g_VertexBuffer, 0);
	}

	return S_OK;
}

//=============================================================================
// �}�e���A���J���[�̐ݒ�
//=============================================================================
void SetColorParticle(int nIdxParticle, XMFLOAT4 col)
{
	g_aParticle[nIdxParticle].material.Diffuse = col;
}

//=============================================================================
// �p�[�e�B�N���̔�������
//=============================================================================
int SetParticle(XMFLOAT3 pos, XMFLOAT3 move, XMFLOAT3 rot, XMFLOAT3 scl, XMFLOAT4 col,int nLife, int nDecay, int texNo, BOOL blend)
{
	int nIdxParticle = -1;
	PLAYER *player = GetPlayer();
	float set_x = fabsf(player[0].pos.x - pos.x);
	float set_z = fabsf(player[0].pos.z - pos.z);
	if (set_x + set_z >= 1000.0f)return nIdxParticle;

	for(int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		if (!g_aParticle[nCntParticle].bUse)
		{
			g_aParticle[nCntParticle].pos = pos;
			g_aParticle[nCntParticle].rot = rot;
			float rand_scale = ((float)((rand() % 25)+8) / 10.0f);
			float rand_scale_y = ((float)((rand() % 25)+8) / 10.0f);
			g_aParticle[nCntParticle].move = move;
			g_aParticle[nCntParticle].material.Diffuse = col;
			g_aParticle[nCntParticle].col = col;
			g_aParticle[nCntParticle].scale = { scl.x * rand_scale, scl.y * rand_scale_y,scl.z * rand_scale };
			g_aParticle[nCntParticle].nLife = nLife;
			g_aParticle[nCntParticle].nDecay = nDecay;
			g_aParticle[nCntParticle].g_TexNo = texNo;
			g_aParticle[nCntParticle].bUse = TRUE;
			g_aParticle[nCntParticle].blend = blend;

			nIdxParticle = nCntParticle;
			break;
		}
	}

	return nIdxParticle;
}