#pragma once
#include "model.h"
#define	MODEL_BOOK			"data/MODEL/book.obj"			// �ǂݍ��ރ��f����
#define	MODEL_BOOKSHELF		"data/MODEL/bookshelf.obj"		// �ǂݍ��ރ��f����
#define	MODEL_LDESK			"data/MODEL/Ldesk.obj"			// �ǂݍ��ރ��f����
#define	MODEL_TANK			"data/MODEL/tank.obj"			// �ǂݍ��ރ��f����
#define	MODEL_TANKGLASS		"data/MODEL/tankglass.obj"			// �ǂݍ��ރ��f����
#define	MODEL_TROLLEY		"data/MODEL/trolley.obj"			// �ǂݍ��ރ��f����
#define	MODEL_TEST			"data/MODEL/neutrophils.obj"			// �ǂݍ��ރ��f����
#define MAX_OBSTACLE (30)
#define MAX_FALL_OBSTACLE (5)
#define MAX_FALL_OBSTACLE_NUM (3)
#define FALL_SPEED	(3.0f)
#define FALL_COOL_TIME_BASE	(120.0f)
#define FALL_RAND_TIME	(60)
#define	MODEL_CEILING			"data/MODEL/ceiling.obj"			// �ǂݍ��ރ��f����
#define	MODEL_ROCK			"data/MODEL/fallingrock.obj"			// �ǂݍ��ރ��f����

//���������f��
enum Fall_Object_Num
{
	fCeiling,
	fRock,
};
//��Q���N���X(�ݒu)
class Obstacle
{
protected:
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
	BOOL				load;

	static void Draw(void);
	static void Init(void);
	static void Uninit(void);
	static void Update(void);
	static void Effect(Obstacle* p);
	static void Distract(Obstacle* p);
	static void SetObstacle(XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 scl, float durability, float size, char* model);
	static Obstacle* GetObstacle(void);
};

//�������N���X
class FallObject:public Obstacle
{
	float speed;	//�������x
	int	  model_num;	//���f���ԍ�
public:
	static void Draw(void);
	static void Init(void);
	static void InitBoot(void);
	static void Uninit(void);
	static void Update(void);
	static void Effect(FallObject* p);
	static void Distract(FallObject* p);
	static void SetObstacle(XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 scl, float durability, float size, int model);
	static FallObject* GetObstacle(void);
};