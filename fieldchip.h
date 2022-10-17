//=============================================================================
//
// ���f������ [fieldchip.h]
// Author : 
//
//=============================================================================
#pragma once
#include "model.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MODEL_FIELD001		"data/MODEL/shortrange2.obj"			// �ǂݍ��ރ��f����
#define	MODEL_FIELD002		"data/MODEL/longrange2.obj"			// �ǂݍ��ރ��f����
#define	MODEL_FIELD003		"data/MODEL/shortrange3.obj"			// �ǂݍ��ރ��f����
#define	MODEL_FIELD004		"data/MODEL/longrange3.obj"			// �ǂݍ��ރ��f����

#define	MODEL_OBJECT001		"data/MODEL/obstacle000.obj"			// �ǂݍ��ރ��f����
#define	MODEL_OBJECT002		"data/MODEL/fence.obj"			// �ǂݍ��ރ��f����
#define MAX_CHIP_NUM		(4)					// �t�B�[���h�`�b�v���
#define MAX_OBJ_NUM			(2)					// �t�B�[���h�`�b�v���
#define MAX_CHIP_WIDTH		(8)					// ���̍ő�Z�b�g��
#define MAX_CHIP_HEIGHT		(7)					// �c�̍ő�Z�b�g��

#define	CHIP_SIZE		(50.0f)					// �`�b�v�T�C�Y�̑傫��

enum CHIP_VAL
{
	ROW,
	HIGH,
	ROW_BLOOD,
	HIGH_BLOOD,
	MAX_VAL
};

enum CHIP_OBJ
{
	Building,
	Container,
};
enum CHIP_TYPE
{
	LowPlaces,
	HighPlaces,
	NoEntry,
};
//*****************************************************************************
// �\���̒�`
//*****************************************************************************
struct MAP_CHIP
{
	XMFLOAT3			pos;		// �|���S���̈ʒu
	XMFLOAT3			rot;		// �|���S���̌���(��])
	XMFLOAT3			scl;		// �|���S���̑傫��(�X�P�[��)

	XMFLOAT4X4			mtxWorld;	// ���[���h�}�g���b�N�X

	BOOL				load;
	DX11_MODEL			model;		// ���f�����
	XMFLOAT4			diffuse[MODEL_MAX_MATERIAL];	// ���f���̐F

	float				size;		// �����蔻��̑傫��
	int					type;		//�}�b�v�`�b�v�^�C�v�̐ݒ�
	BOOL				use;		//�}�b�v�`�b�v�����܂��Ă��邩(FALSE�Ŗ��܂��ĂȂ�)
};

struct FIELD_BG
{
	XMFLOAT3			pos;		// �|���S���̈ʒu
	XMFLOAT3			rot;		// �|���S���̌���(��])
	XMFLOAT3			scl;		// �|���S���̑傫��(�X�P�[��)

	XMFLOAT4X4			mtxWorld;	// ���[���h�}�g���b�N�X
	MATERIAL			material;
	BOOL				load;

};
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitMapChip(int map[][MAX_CHIP_WIDTH + 1], int mapObj[][MAX_CHIP_WIDTH + 1], int height, int width);
void UninitMapChip(void);
void UpdateMapChip(void);
void DrawMapChip(void);
void DrawMapObject(void);
void DrawBG(void);
HRESULT MakeVertexBG(void);
void SetBattleMap(int map[][MAX_CHIP_WIDTH + 1], int height, int width);
void SetBattleMapObj(int map[][MAX_CHIP_WIDTH + 1], int height, int width);
MAP_CHIP *GetMapChip(void);
int GetMapChiptype(int i, int k);
void SetMapChipUse(BOOL flag, int i, int k);
BOOL GetMapChipUse(int i, int k);
float GetMapWidth(void);
float GetMapHeight(void);