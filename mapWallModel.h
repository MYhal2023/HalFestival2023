#pragma once
#pragma once
#include "model.h"
#define	MODEL_NEUTROPHILS	"data/MODEL/neutrophils.obj"			// �ǂݍ��ރ��f����
#define	MODEL_WALL001	"data/MODEL/kabe1.obj"			// �ǂݍ��ރ��f����
#define	MODEL_WALL002	"data/MODEL/kabe2.obj"			// �ǂݍ��ރ��f����
#define	MODEL_WALL003	"data/MODEL/kabedoor.obj"			// �ǂݍ��ރ��f����

//�}�b�v�̕ǃ��f���N���X
class MapWallModel
{
private:
	DX11_MODEL			model;		// ���f�����
	XMFLOAT4X4			mtxWorld;	// ���[���h�}�g���b�N�X
	XMFLOAT3			pos;		// �|���S���̈ʒu
	XMFLOAT3			rot;		// �|���S���̌���(��])
	XMFLOAT3			scl;		// �|���S���̑傫��(�X�P�[��)
	BOOL				use;
public:
	static void Draw(void);
	static void Init(void);
	static void Uninit(void);
	static void Update(void);
};