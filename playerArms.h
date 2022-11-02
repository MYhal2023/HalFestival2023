#pragma once
#include "player.h"
#include "model.h"
#define	MODEL_XGUN			"data/MODEL/Xgun.obj"			// 読み込むモデル名
#define	MODEL_BRASTER			"data/MODEL/shoka.obj"			// 読み込むモデル名
#define	MODEL_SAW		"data/MODEL/setsudan.obj"			// 読み込むモデル名
#define	MODEL_ARM_HAND		"data/MODEL/arm_hand.obj"			// 読み込むモデル名
#define	MODEL_ARM_PARTS		"data/MODEL/ARMpart0.obj"			// 読み込むモデル名
#define ARM_VAR			(3)	//アームの種類
#define MAX_ARM_PARTS (7)
////アーム種類列挙
//enum ArmVar
//{
//	Xgun,
//	Braster,
//	Saw,
//};
//プレイヤーアームクラス
class pArm
{
protected:
	DX11_MODEL			model;		// モデル情報
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

	INTERPOLATION_DATA	*tbl_adrXgun;	// 攻撃アニメデータのテーブル先頭アドレス
	INTERPOLATION_DATA	*tbl_adr;	// 移動アニメデータのテーブル先頭アドレス
	PLAYER* player;
	int					slot;

public:
	XMFLOAT4X4			mtxWorld;	// ワールドマトリックス
	XMFLOAT3			pos;		// ポリゴンの位置
	pArm* parent;
	static void SetArmParent(PLAYER *p);
	static void InitArm(void);
	static void UpdateArm(void);
	static void IPArm(pArm* p, INTERPOLATION_DATA* i);
	static pArm* GetArm(void);
	static pArm* GetArmParts(void);
	static pArm* GetLeftArmParts(void);
	void Draw(void);
};

class Xgun :public pArm
{
public:
	static void InitArm(void);
	static void Action(void);
	static void Draw(void);
	static pArm* GetArm(void);
	static void SetParent(pArm * p1, pArm * p2);
}; 

class Braster :public pArm
{
public:
	static void InitArm(void);
	static void Action(void);
	static void Draw(void);
	static pArm* GetArm(void);
};

class Saw :public pArm
{
public:
	static void InitArm(void);
	static void Action(void);
	static void Draw(void);
	static pArm* GetArm(void);
};