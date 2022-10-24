#pragma once
#include "player.h"
#include "model.h"
//アーム種類列挙
enum ArmVar
{
	Xgun,
	Braster,
	Saw,
};
//プレイヤーアームクラス
class pArm
{
private:
	DX11_MODEL			model;		// モデル情報
	XMFLOAT4X4			mtxWorld;	// ワールドマトリックス
	XMFLOAT3			pos;		// ポリゴンの位置
	XMFLOAT3			rot;		// ポリゴンの向き(回転)
	XMFLOAT3			scl;		// ポリゴンの大きさ(スケール)

	// 階層アニメーション用のメンバー変数
	int					tbl_sizeA;	// 登録したテーブルのレコード総数
	int					tbl_sizeM;	// 登録したテーブルのレコード総数
	float				move_time;	// 実行時間

	int					partsNum;	//アームのパーツ数

	BOOL				use;		//使用されているか
	//攻撃
	BOOL			attack;			//攻撃中か否か

	INTERPOLATION_DATA	*tbl_adrA;	// 攻撃アニメデータのテーブル先頭アドレス
	INTERPOLATION_DATA	*tbl_adrM;	// 移動アニメデータのテーブル先頭アドレス
	PLAYER* player;
	pArm* parent;

public:
	static void Draw(void);
	static void SetArmParent(PLAYER *p);
	pArm* GetArm(void);
};

class Xgun :public pArm
{
public:
	static void InitArm(void);
	static void Action(void);
}; 

class Braster :public pArm
{
public:
	static void InitArm(void);
	static void Action(void);
};

class Saw :public pArm
{
public:
	static void InitArm(void);
	static void Action(void);
};