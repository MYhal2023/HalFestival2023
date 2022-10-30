#pragma once
#include "model.h"
#define	MODEL_OBSTACLE	"data/MODEL/neutrophils.obj"			// �ǂݍ��ރ��f����
#define MAX_OBSTACLE (30)

//��Q���N���X(���)
class Obstacle
{
private:
	DX11_MODEL			model;		// ���f�����
	XMFLOAT4X4			mtxWorld;	// ���[���h�}�g���b�N�X
	XMFLOAT3			rot;		// �|���S���̌���(��])
	XMFLOAT3			scl;		// �|���S���̑傫��(�X�P�[��)

	BOOL				efSwitch;	//�G�t�F�N�g�X�C�b�`
	BOOL				efFinish;	//�G�t�F�N�g�I���X�C�b�`
public:
	XMFLOAT3			pos;		// �|���S���̈ʒu
	float				size;		//�����蔻��
	float				durability; //�ϋv�x
	BOOL				use;		//�g�p����Ă��邩

	static void Draw(void);
	static void Init(void);
	static void Uninit(void);
	static void Update(void);
	static void Effect(Obstacle* p);
	static void Distract(Obstacle* p);
	static void SetObstacle(XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 scl, float durability, float size, char* model);
	static Obstacle* GetObstacle(void);
};