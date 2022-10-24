#pragma once
#include "model.h"

//��Q���N���X(���)
class Obstacle
{
private:
	DX11_MODEL			model;		// ���f�����
	XMFLOAT4X4			mtxWorld;	// ���[���h�}�g���b�N�X
	XMFLOAT3			pos;		// �|���S���̈ʒu
	XMFLOAT3			rot;		// �|���S���̌���(��])
	XMFLOAT3			scl;		// �|���S���̑傫��(�X�P�[��)
	float				durability; //�ϋv�x

	BOOL				use;		//�g�p����Ă��邩
	BOOL				efSwitch;	//�G�t�F�N�g�X�C�b�`
public:
	static void Draw(void);
	static void Init(void);
	static void Uninit(void);
	static void Update(void);
	static void Effect(Obstacle* p);
	static void Distract(Obstacle* p);
};