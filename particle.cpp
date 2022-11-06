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

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_MAX			(2)			// �e�N�X�`���̐�

#define	PARTICLE_SIZE_X		(40.0f)		// ���_�T�C�Y
#define	PARTICLE_SIZE_Y		(40.0f)		// ���_�T�C�Y
#define	VALUE_MOVE_PARTICLE	(5.0f)		// �ړ����x

#define	MAX_PARTICLE		(512)		// �p�[�e�B�N���ő吔
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
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateParticle(void)
{
	//PLAYER *pPlayer = GetPlayer();
	//g_posBase = pPlayer->pos;

	{
		for(int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
		{
			if(g_aParticle[nCntParticle].bUse)
			{// �g�p��
				g_aParticle[nCntParticle].pos.x += g_aParticle[nCntParticle].move.x;
				g_aParticle[nCntParticle].pos.z += g_aParticle[nCntParticle].move.z;

				g_aParticle[nCntParticle].pos.y += g_aParticle[nCntParticle].move.y;

				g_aParticle[nCntParticle].move.x += (g_aParticle[nCntParticle].move.x) * 0.015f;
				g_aParticle[nCntParticle].move.y += (g_aParticle[nCntParticle].move.y) * 0.015f;
				g_aParticle[nCntParticle].move.z += (g_aParticle[nCntParticle].move.z) * 0.015f;

				g_aParticle[nCntParticle].nLife--;
				if(g_aParticle[nCntParticle].nLife <= 0)
				{
					g_aParticle[nCntParticle].bUse = FALSE;
				}
				else
				{
					//���Z�����Ȃ̂ŁA�����ɂȂ��Ă����悤�Ɍ�����
					if(g_aParticle[nCntParticle].nLife <= g_aParticle[nCntParticle].nDecay)
					{
						g_aParticle[nCntParticle].material.Diffuse.x = g_aParticle[nCntParticle].col.x - (float)(80 - g_aParticle[nCntParticle].nLife) / 80 * g_aParticle[nCntParticle].col.x;
						g_aParticle[nCntParticle].material.Diffuse.y = g_aParticle[nCntParticle].col.y - (float)(80 - g_aParticle[nCntParticle].nLife) / 80 * g_aParticle[nCntParticle].col.y;
						g_aParticle[nCntParticle].material.Diffuse.z = g_aParticle[nCntParticle].col.z - (float)(80 - g_aParticle[nCntParticle].nLife) / 80 * g_aParticle[nCntParticle].col.z;
					}

					//if(g_aParticle[nCntParticle].nLife <= 20)
					//{
					//	// ���l�ݒ�
					//	g_aParticle[nCntParticle].material.Diffuse.w -= 0.05f;
					//	if(g_aParticle[nCntParticle].material.Diffuse.w < 0.0f)
					//	{
					//		g_aParticle[nCntParticle].material.Diffuse.w = 0.0f;
					//	}
					//}
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
		XMFLOAT3 move = { 2.0f, 2.0f, 2.0f, };			//�ړ���b�ʁB�������قǓ������������ɂȂ�
		float fAngle = (float)(rand() % 90) / 100.0f;	//���Z�������(�������傫���قǁA���E�ɂ΂�����o��)
		float fLength = (float)(rand() % 10) - 3;	//x��z�����̉��Z���x
		move.x += sinf(fAngle) * fLength;
		move.y += (float)(rand() % 5);			//�����̈ړ����Z��
		move.z += cosf(fAngle) * fLength;

		if (GetKeyboardPress(DIK_SPACE))
		{
			PLAYER *player = GetPlayer();
			XMFLOAT3 pos = { 0.0f, 0.0f, 0.0f };
			float angle = atan2f(move.y, move.x);
			pos.z += 200.0f;
			XMFLOAT3 scl = { 0.05f, 0.4f, 0.05f };	//�g�嗦
			XMFLOAT3 rot = { 0.0f, 0.0f, 0.0f };
			int nLife = rand() % 100 + 50;
			SetParticle(pos, move, rot, scl, XMFLOAT4(1.0f, 0.3f, 0.3f, 1.0f), nLife, 40, P_T_box);
		}
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

	// ���Z�����ɐݒ�
	SetBlendState(BLEND_MODE_ADD);

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
		if(g_aParticle[nCntParticle].bUse)
		{
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
int SetParticle(XMFLOAT3 pos, XMFLOAT3 move, XMFLOAT3 rot, XMFLOAT3 scl, XMFLOAT4 col,int nLife, int nDecay, int texNo)
{
	int nIdxParticle = -1;

	for(int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		if(!g_aParticle[nCntParticle].bUse)
		{
			g_aParticle[nCntParticle].pos = pos;
			g_aParticle[nCntParticle].rot   = rot;
			g_aParticle[nCntParticle].scale = { 1.0f, 1.0f, 1.0f };
			g_aParticle[nCntParticle].move = move;
			g_aParticle[nCntParticle].material.Diffuse = col;
			g_aParticle[nCntParticle].col = col;
			g_aParticle[nCntParticle].scale = scl;
			g_aParticle[nCntParticle].nLife = nLife;
			g_aParticle[nCntParticle].nDecay = nDecay;
			g_aParticle[nCntParticle].g_TexNo = texNo;
			g_aParticle[nCntParticle].bUse = TRUE;

			nIdxParticle = nCntParticle;
			break;
		}
	}

	return nIdxParticle;
}