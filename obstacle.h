//////
//障害物クラス
//////

#pragma once
#include "model.h"
#define	MODEL_BOOK			"data/MODEL/book.obj"			// 読み込むモデル名
#define	MODEL_BOOKSHELF		"data/MODEL/bookshelf.obj"		// 読み込むモデル名
#define	MODEL_LDESK			"data/MODEL/Ldesk.obj"			// 読み込むモデル名
#define	MODEL_TANK			"data/MODEL/tank.obj"			// 読み込むモデル名
#define	MODEL_TANKGLASS		"data/MODEL/tankglass.obj"			// 読み込むモデル名
#define	MODEL_TROLLEY		"data/MODEL/trolley.obj"			// 読み込むモデル名
#define	MODEL_BOX		"data/MODEL/rubble.obj"			// 読み込むモデル名
#define	MODEL_DCUT		"data/MODEL/duct_line.obj"			// 読み込むモデル名
#define	MODEL_GASTANK		"data/MODEL/gastank.obj"			// 読み込むモデル名
#define	MODEL_MONITOR		"data/MODEL/monitor.obj"			// 読み込むモデル名
#define	MODEL_STEEL		"data/MODEL/steelframe.obj"			// 読み込むモデル名
#define	MODEL_TEST			"data/MODEL/neutrophils.obj"			// 読み込むモデル名

#define MAX_OBSTACLE (30)
#define MAX_FALL_OBSTACLE (5)
#define MAX_FALL_OBSTACLE_NUM (3)
#define FALL_SPEED	(3.0f)
#define FALL_COOL_TIME_BASE	(120.0f)
#define FALL_RAND_TIME	(60)
#define	MODEL_CEILING			"data/MODEL/ceiling.obj"			// 読み込むモデル名
#define	MODEL_ROCK			"data/MODEL/fallingrock.obj"			// 読み込むモデル名

enum ObstacleModel
{
	om_book,
	om_bookshelf,
	om_Ldesk,
	om_tank,
	om_tankglass,
	om_trolley,
	om_box,
	om_duct,
	om_gastank,
	om_monitor,
	om_steel,
	om_test,
	MAX_OBSTACLE_MODEL
};
//落下物モデル
enum Fall_Object_Num
{
	fCeiling,
	fRock,
};
//障害物クラス(設置)
class Obstacle
{
protected:
	XMFLOAT4X4			mtxWorld;	// ワールドマトリックス
	XMFLOAT3			rot;		// ポリゴンの向き(回転)
	XMFLOAT3			scl;		// ポリゴンの大きさ(スケール)

	BOOL				efSwitch;	//エフェクトスイッチ
	BOOL				efFinish;	//エフェクト終了スイッチ
public:
	XMFLOAT3			pos;		// ポリゴンの位置
	float				size;		//当たり判定
	float				durability; //耐久度
	int					model_num;	//モデル番号
	BOOL				use;		//使用されているか
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
};

//落下物クラス
class FallObject:public Obstacle
{
	float speed;	//落下速度
	int	  model_num;	//モデル番号
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