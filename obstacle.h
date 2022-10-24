#pragma once
#include "model.h"

//障害物クラス(基底)
class Obstacle
{
private:
	DX11_MODEL			model;		// モデル情報
	XMFLOAT4X4			mtxWorld;	// ワールドマトリックス
	XMFLOAT3			pos;		// ポリゴンの位置
	XMFLOAT3			rot;		// ポリゴンの向き(回転)
	XMFLOAT3			scl;		// ポリゴンの大きさ(スケール)
	float				durability; //耐久度

	BOOL				use;		//使用されているか
	BOOL				efSwitch;	//エフェクトスイッチ
public:
	static void Draw(void);
	static void Init(void);
	static void Uninit(void);
	static void Update(void);
	static void Effect(Obstacle* p);
	static void Distract(Obstacle* p);
};