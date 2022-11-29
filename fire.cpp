//=============================================================================
//
// ���G�t�F�N�g���� [fire.cpp]
// Author : 
//
//=============================================================================
#include "fire.h"
#include "fade.h"
#include "renderer.h"
#include "sprite.h"
#include "model.h"
#include "particle.h"
#include "camera.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_WIDTH				(64)	// �L�����T�C�Y
#define TEXTURE_HEIGHT				(128)	// 
#define TEXTURE_MAX					(2)		// �e�N�X�`���̐�
#define TEX_WIDTH					(4)
#define TEX_HEIGHT					(4)
#define FRAME_RATE					(3)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static ID3D11Buffer				*g_VertexBuffer[TEX_WIDTH * TEX_HEIGHT] = {NULL};		// ���_���
static ID3D11ShaderResourceView	*g_Texture[TEXTURE_MAX] = { NULL };	// �e�N�X�`�����

static char *g_TexturName[TEXTURE_MAX] = {
	"data/TEXTURE/fire_1.png",
	"data/TEXTURE/fire_2.jpg",
};


static BOOL						g_Use;						// TRUE:�g���Ă���  FALSE:���g�p
static float					g_w, g_h;					// ���ƍ���
static XMFLOAT3					g_Pos;						// �|���S���̍��W
static FireEffect				g_Fire[MAX_FIRE_EFFECT];
static BOOL						g_Load = FALSE;


//=============================================================================
// ����������
//=============================================================================
HRESULT InitFire(void)
{
	// ���_���̍쐬
	MakeVertexFire();

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


	for (int i = 0; i < MAX_FIRE_EFFECT; i++)
	{
		g_Fire[i].use = FALSE;
	}
	g_Load = TRUE;
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitFire(void)
{
	if (g_Load == FALSE) return;

	for (int i = 0; i < TEX_WIDTH * TEX_HEIGHT; i++)
	{
		if (g_VertexBuffer[i])
		{
			g_VertexBuffer[i]->Release();
			g_VertexBuffer[i] = NULL;
		}
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
void UpdateFire(void)
{
	for (int i = 0; i < MAX_FIRE_EFFECT; i++)
	{
		if (!g_Fire[i].use)continue;
		
		g_Fire[i].interval++;
		if (g_Fire[i].interval < FRAME_RATE)continue;
		switch (g_Fire[i].g_TexNo)
		{
		case 0:
			g_Fire[i].u++;
			if (g_Fire[i].u >= 4)
			{
				g_Fire[i].u = 0;
				g_Fire[i].v ++;
				if (g_Fire[i].v >= 3)
					g_Fire[i].v = 0;
			}
			break;
		}
		g_Fire[i].interval = 0;
		SetFireParticle(g_Fire[i].pos, g_Fire[i].rot.y);
	}
#ifdef _DEBUG	// �f�o�b�O����\������

#endif

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawFire(void)
{

	// ���C�e�B���O�𖳌���
	SetLightEnable(FALSE);

	// Z��r����
	SetDepthEnable(FALSE);

	XMMATRIX mtxScl, mtxRot, mtxTranslate, mtxWorld;

	



	for (int i = 0; i < MAX_FIRE_EFFECT; i++)
	{
		if (!g_Fire[i].use)continue;

		int num = (int)(g_Fire[i].u) + (int)(g_Fire[i].v) * TEX_WIDTH;

		// ���_�o�b�t�@�ݒ�
		UINT stride = sizeof(VERTEX_3D);
		UINT offset = 0;
		GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer[num], &stride, &offset);


		// �v���~�e�B�u�g�|���W�ݒ�
		GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

		// �e�N�X�`���ݒ�
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[g_Fire[i].g_TexNo]);

		// ���[���h�}�g���b�N�X�̏�����
		mtxWorld = XMMatrixIdentity();


		// �X�P�[���𔽉f
		mtxScl = XMMatrixScaling(g_Fire[i].scale.x, g_Fire[i].scale.y, g_Fire[i].scale.z);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxScl);

		// ��]�𔽉f
		mtxRot = XMMatrixRotationRollPitchYaw(g_Fire[i].rot.x, g_Fire[i].rot.y, g_Fire[i].rot.z);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxRot);


		// �ړ��𔽉f
		mtxTranslate = XMMatrixTranslation(g_Fire[i].pos.x, g_Fire[i].pos.y, g_Fire[i].pos.z);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxTranslate);

		// ���[���h�}�g���b�N�X�̐ݒ�
		SetWorldMatrix(&mtxWorld);

		// �|���S���̕`��
		GetDeviceContext()->Draw(4, 0);
	}

	// Z��r����
	SetDepthEnable(TRUE);
	SetLightEnable(TRUE);

}

FireEffect* SetFireEffect(XMFLOAT3 pos, XMFLOAT3 rot)
{
	FireEffect* ans = nullptr;
	for (int i = 0; i < MAX_FIRE_EFFECT; i++)
	{
		if (g_Fire[i].use)continue;

		g_Fire[i].use = TRUE;
		g_Fire[i].pos = pos;
		g_Fire[i].rot = rot;
		g_Fire[i].scale = { 2.0f, 2.0f, 2.0f };
		g_Fire[i].g_TexNo = rand() % 1;
		g_Fire[i].size = { 30.0f, 30.0f };
		return &g_Fire[i];
	}

	return ans;
}

void SetFireParticle(XMFLOAT3 pos, float y_rot)
{
	CAMERA *cam = GetCamera();
	float p_rot_y = XMConvertToDegrees(y_rot);
	float cam_rot_y = XMConvertToDegrees(cam->rot.y);
	float fab = fabsf(fabsf(p_rot_y) - fabsf(cam_rot_y));
	if (fab < 75)return;
	for (int i = 0; i < 3; i++) {
		XMFLOAT3 move = { 0.0f, 0.0f, 0.0f, };
		float fAngle = (float)(rand() % 30) + 40;	//���Z�������(�������ʂ̐������傫���قǁA���E�ɂ΂�����o��)
		fAngle = XMConvertToRadians(fAngle);
		float fLength = (float)(rand() % 2 + 1) * 0.2f;	//x��z�����̉��Z���x���̌��ʂ��傫���Ƒf��������
		float fHigh = (float)(rand() % 4 + 1) * 0.2f;	//x��z�����̉��Z���x���̌��ʂ��傫���Ƒf��������
		move.x += cosf(fAngle) * fLength;
		move.y += sinf(fAngle) * fHigh;			//�����̈ړ����Z��
		float angle = atan2f(move.y, move.x);
		XMFLOAT3 scl = { 0.15f, 0.15f, 0.15f };	//�g�嗦
		XMFLOAT3 rot = { 0.0f, cam->rot.y, 0.0f };	//��]���B������K�v�Ȃ�
		int nLife = rand() % 20 + 43;
		rot.z = angle - XM_PI * 0.0f;
		rot.y = cam->rot.y;
		if ((rot.y > XM_PI * 0.25f && rot.y < XM_PI * 0.75f) || (rot.y < XM_PI * -0.25f && rot.y > XM_PI * -0.75f)) {
			move.z = move.x;
			move.x = 0.0f;
		}
		pos.y -= 10.0f;
		SetParticle(pos, move, rot, scl, XMFLOAT4(0.3f, 0.3f, 0.3f, 0.3f), nLife, 43, 1, 0);
	}

}


HRESULT MakeVertexFire(void)
{
	float tx = 1.0f / TEX_WIDTH;
	float ty = 1.0f / TEX_HEIGHT;
	int s = 0;
	for (int i = 0; i < TEX_HEIGHT; i++) {
		for (int k = 0; k < TEX_WIDTH; k++) {
			// ���_�o�b�t�@����
			D3D11_BUFFER_DESC bd;
			ZeroMemory(&bd, sizeof(bd));
			bd.Usage = D3D11_USAGE_DYNAMIC;
			bd.ByteWidth = sizeof(VERTEX_3D) * 4;
			bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

			GetDevice()->CreateBuffer(&bd, NULL, &g_VertexBuffer[s]);

			{//���_�o�b�t�@�̒��g�𖄂߂�
				D3D11_MAPPED_SUBRESOURCE msr;
				GetDeviceContext()->Map(g_VertexBuffer[s], 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

				VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

				// ���_���W�̐ݒ�
				vertex[0].Position = XMFLOAT3(-40.0f / 2, 40.0f / 2, 0.0f);
				vertex[1].Position = XMFLOAT3(40.0f / 2, 40.0f / 2, 0.0f);
				vertex[2].Position = XMFLOAT3(-40.0f / 2, -40.0f / 2, 0.0f);
				vertex[3].Position = XMFLOAT3(40.0f / 2, -40.0f / 2, 0.0f);

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
				vertex[0].TexCoord = { tx * k, ty * i };
				vertex[1].TexCoord = { tx * (k+1), ty * i };
				vertex[2].TexCoord = { tx * k, ty * (i + 1) };
				vertex[3].TexCoord = { tx * (k + 1), ty * (i + 1) };

				GetDeviceContext()->Unmap(g_VertexBuffer[s], 0);
				s++;
			}
		}
	}
	return S_OK;
}
