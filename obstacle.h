#pragma once
#include "model.h"
#define	MODEL_OBSTACLE	"data/MODEL/neutrophils.obj"			// 読み込むモデル名
#define MAX_OBSTACLE (30)
#define FALL_SPEED	(5.0f)
//障害物クラス(基底)
class Obstacle
{
protected:
	DX11_MODEL			model;		// モデル情報
	XMFLOAT4X4			mtxWorld;	// ワールドマトリックス
	XMFLOAT3			rot;		// ポリゴンの向き(回転)
	XMFLOAT3			scl;		// ポリゴンの大きさ(スケール)

	BOOL				efSwitch;	//エフェクトスイッチ
	BOOL				efFinish;	//エフェクト終了スイッチ
public:
	XMFLOAT3			pos;		// ポリゴンの位置
	float				size;		//当たり判定
	float				durability; //耐久度
	BOOL				use;		//使用されているか

	static void Draw(void);
	static void Init(void);
	static void Uninit(void);
	static void Update(void);
	static void Effect(Obstacle* p);
	static void Distract(Obstacle* p);
	static void SetObstacle(XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 scl, float durability, float size, char* model);
	static Obstacle* GetObstacle(void);
};

//落下物クラス
class FallObject:public Obstacle
{
	float speed;	//落下速度
	static void Draw(void);
	static void Init(void);
	static void Uninit(void);
	static void Update(void);
	static void Effect(FallObject* p);
	static void Distract(FallObject* p);
	static void SetObstacle(XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 scl, float durability, float size, char* model);
	static FallObject* GetObstacle(void);
};