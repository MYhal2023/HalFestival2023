#pragma once
#include "player.h"
#include "model.h"
#define	MODEL_XGUN			"data/MODEL/Xgun.obj"			// 読み込むモデル名
#define	MODEL_BRASTER			"data/MODEL/shoka.obj"			// 読み込むモデル名
#define	MODEL_SAW		"data/MODEL/setsudan.obj"			// 読み込むモデル名
#define	MODEL_ARM_HAND		"data/MODEL/arm_hand.obj"			// 読み込むモデル名
#define	MODEL_ARM_PARTS		"data/MODEL/ARMpart0.obj"			// 読み込むモデル名
#define	MODEL_ARM_SAW_BLADE		"data/MODEL/saw.obj"			// 読み込むモデル名
#define ARM_VAR			(3)	//アームの種類
#define MAX_ARM_PARTS (10)
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
	INTERPOLATION_DATA*					old_tbl;	//現在の使用テーブル

	int					partsNum;	//アームのパーツ数

	BOOL				use;		//使用されているか
	//攻撃
	BOOL			attack;			//攻撃中か否か

	INTERPOLATION_DATA	*tbl_adrXgun;	// 攻撃アニメデータのテーブル先頭アドレス
	INTERPOLATION_DATA_EASING	*tbl_adr;	// 移動アニメデータのテーブル先頭アドレス
	PLAYER* player;
	int					slot;

public:
	XMFLOAT4X4			mtxWorld;	// ワールドマトリックス
	XMFLOAT3			pos;		// ポリゴンの位置
	float				move_time;	// 実行時間
	float				spead;
	float				ct_frame;
	float				ef_frame;
	pArm* parent;
	static void SetArmParent(PLAYER *p);
	static void InitArm(void);
	static void UninitArm(void);
	static void InitArmBoot(void);
	static void UpdateArm(void);
	static void UpdateReleaseArm(void);	//リリースで使うやつ
	static void UpdateXgunArm(void);
	static void UpdateBrasterArm(void);
	static void UpdateSawArm(void);
	static void UpdateSawArmSecond(void);
	static void UpdateWaitArm(void);
	static INTERPOLATION_DATA* CheckMotionData(PLAYER *p);
	static void IPArm(pArm* p, INTERPOLATION_DATA_EASING* i);
	static pArm* GetArm(void);
	static pArm* GetArmParts(void);
	static pArm* GetLeftArmParts(void);
	void Draw(void);
};

class Normal :public pArm
{
public:
	static void SetArmParent(PLAYER *p);
	static void InitArm(void);
	static void UninitArm(void);
	static void InitArmBoot(void);
	static void UpdateArm(void);
	static INTERPOLATION_DATA* CheckMotionData(PLAYER *p);
	static void IPArm(Normal* p, INTERPOLATION_DATA_EASING* i);
	static pArm* GetArm(void);
	static pArm* GetArmParts(void);
	static void Draw(void);
};

class Xgun :public pArm
{
public:
	BOOL	attackUse;
	float	atInterval;
	float	atCount;
	static void InitArm(void);
	static void Action(void);
	static void Draw(void);
	static pArm* GetArm(void);
}; 

class Braster :public pArm
{
public:
	BOOL	attackUse;
	float	atInterval;
	float	atCount;
	static void InitArm(void);
	static void Action(void);
	static void Draw(void);
	static pArm* GetArm(void);
};

class Saw :public pArm
{
public:
	float attack;
	float atInterval;
	float atCount;
	float motionTime;
	static void InitArm(void);
	static void Action(void);
	static void SetEffect(XMFLOAT3 pos, float rot, float time);
	static void Effect(void);
	static void Draw(void);
	static pArm* GetArm(void);
};