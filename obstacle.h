//////
//��Q���N���X
//////

#pragma once
#include "model.h"
#define	MODEL_BOOK			"data/MODEL/book.obj"			// �ǂݍ��ރ��f����
#define	MODEL_BOOKSHELF		"data/MODEL/bookshelf.obj"		// �ǂݍ��ރ��f����
#define	MODEL_LDESK			"data/MODEL/Ldesk.obj"			// �ǂݍ��ރ��f����
#define	MODEL_TANK			"data/MODEL/tank.obj"			// �ǂݍ��ރ��f����
#define	MODEL_TANKGLASS		"data/MODEL/tankglass.obj"			// �ǂݍ��ރ��f����
#define	MODEL_TROLLEY		"data/MODEL/trolley.obj"			// �ǂݍ��ރ��f����
#define	MODEL_BOX		"data/MODEL/rubble.obj"			// �ǂݍ��ރ��f����
#define	MODEL_DCUT		"data/MODEL/duct_line.obj"			// �ǂݍ��ރ��f����
#define	MODEL_GASTANK		"data/MODEL/gastank.obj"			// �ǂݍ��ރ��f����
#define	MODEL_MONITOR		"data/MODEL/monitor.obj"			// �ǂݍ��ރ��f����
#define	MODEL_STEEL		"data/MODEL/steelframe.obj"			// �ǂݍ��ރ��f����
#define	MODEL_BREAK_WALL	"data/MODEL/breakwall.obj"			// �ǂݍ��ރ��f����
#define	MODEL_TERMINAL	"data/MODEL/terminal.obj"			// �ǂݍ��ރ��f����
#define	MODEL_TEST			"data/MODEL/neutrophils.obj"			// �ǂݍ��ރ��f����

#define MAX_OBSTACLE (60)
#define MAX_FALL_OBSTACLE (20)
#define MAX_FALL_OBSTACLE_NUM (2)
#define FALL_SPEED	(3.0f)
#define FALL_COOL_TIME_BASE	(60.0f)
#define FALL_RAND_TIME	(30)
#define FALL_INTERVAL	(600.0f)
#define FALL_TIME (340.0f)
#define	MODEL_CEILING			"data/MODEL/ceiling.obj"			// �ǂݍ��ރ��f����
#define	MODEL_ROCK			"data/MODEL/fallingrock.obj"			// �ǂݍ��ރ��f����

enum ObstacleModel
{
	om_book,		//�{
	om_bookshelf,	//�{����
	om_Ldesk,		//L���̊�
	om_tank,		//�^���N
	om_tankglass,	//�^���N�̃K���X����
	om_trolley,		//���
	om_box,			//��̂��炭��
	om_duct,		//�_�N�g�̐ڑ������H
	om_gastank,		//�K�X�^���N
	om_monitor,		//���j�^�[
	om_steel,		//�S�|
	om_break_wall,	//�j��ł����
	om_terminal,		//�e�X�g�p�̃��f��
	om_test,		//�e�X�g�p�̃��f��
	MAX_OBSTACLE_MODEL
};
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
	XMFLOAT4X4			mtxWorld;	// ���[���h�}�g���b�N�X
	XMFLOAT3			rot;		// �|���S���̌���(��])
	XMFLOAT3			scl;		// �|���S���̑傫��(�X�P�[��)

	BOOL				efSwitch;	//�G�t�F�N�g�X�C�b�`
	BOOL				efFinish;	//�G�t�F�N�g�I���X�C�b�`
public:
	XMFLOAT3			pos;		// �|���S���̈ʒu
	float				size;		//�����蔻��
	float				durability; //�ϋv�x
	int					model_num;	//���f���ԍ�
	int					mesh_wall[4];	//1���f����4�̓����蔻��p���b�V�����g���̂�4��
	BOOL				use;		//�g�p����Ă��邩
	BOOL				load;

	static void Draw(void);
	static void Init(void);
	static void InitBoot(void);
	static void Uninit(void);
	static void Update(void);
	static void Effect(Obstacle* p);
	static void Distract(Obstacle* p);
	static void SetObstacle(XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 scl, float durability, float size, int model);
	static Obstacle* GetObstacle(void);
	static void SetHitMeshWall(XMFLOAT3 pos, XMFLOAT3 rot, int model_num, Obstacle *ob);
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
	static FallObject* GetObstacle(void);
	static void FallObject::SetObstacle(XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 scl, float durability, float size, int model);
	static BOOL GetFallSwitch(void);
};