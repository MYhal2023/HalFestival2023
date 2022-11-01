#pragma once
#define MAX_RESCUE (10)
#define	MODEL_RESCUE001	"data/MODEL/neutrophils.obj"			// �ǂݍ��ރ��f����
#include "main.h"
#include "model.h"

//�l���~���҃N���X
class RescueLife
{
private:
	XMFLOAT3			pos;
	XMFLOAT3			rot;
	XMFLOAT3			scl;		// �|���S���̑傫��(�X�P�[��)

	XMFLOAT4X4			mtxWorld;	// ���[���h�}�g���b�N�X

	BOOL				load;
	DX11_MODEL			model;		// ���f�����
	XMFLOAT4			diffuse[MODEL_MAX_MATERIAL];	// ���f���̐F

	BOOL				use;		//�~���҂��g���Ă��邩�ۂ�
	BOOL				rescue;	//�~���҂���������
public:
	static void InitRescue(void);
	static void UninitRescue(void);
	static void DrawRescue(void);
	static BOOL GetRescue(int i);
	static void SetRemain(XMFLOAT3 pos, XMFLOAT3 rot, char* model);
	static RescueLife* GetRescueLife(void);
};

int GetRemain(void);
