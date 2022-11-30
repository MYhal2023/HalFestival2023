#pragma once
#define MAX_RESCUE (30)
#define MODEL_VAR (3)
#define	MODEL_RESCUE001	"data/MODEL/helper1.obj"			// �ǂݍ��ރ��f����
#define	MODEL_RESCUE002	"data/MODEL/helper2.obj"			// �ǂݍ��ރ��f����
#include "main.h"
#include "model.h"

//�l���~���҃N���X
class RescueLife
{
public:
	XMFLOAT3			pos;
	XMFLOAT3			rot;
	XMFLOAT3			scl;		// �|���S���̑傫��(�X�P�[��)

	XMFLOAT4X4			mtxWorld;	// ���[���h�}�g���b�N�X

	BOOL				load;
	XMFLOAT4			diffuse[MODEL_MAX_MATERIAL];	// ���f���̐F
	int					model_num;
	BOOL				use;		//�~���҂��g���Ă��邩�ۂ�
	BOOL				rescue;	//�~���҂���������
public:
	static void InitRescue(void);
	static void InitBootRescue(void);
	static void UninitRescue(void);
	static void DrawRescue(void);
	static BOOL GetRescue(int i);
	static void SetRemain(XMFLOAT3 pos, XMFLOAT3 rot, int model);
	static RescueLife* GetRescueLife(void);
	static int GetRescueRemainLife(void);
};

int GetRemain(void);
