//=============================================================================
//
// モデル処理 [player.h]
// Author : 
//
//=============================================================================
#pragma once
#ifndef PLAYER_H_
#define PLAYER_H_
#include "unitdata.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MODEL_PLAYER		"data/MODEL/dendritic_cells.obj"			// 読み込むモデル名
#define	MODEL_NEUTROPHILS	"data/MODEL/neutrophils.obj"			// 読み込むモデル名
#define	MODEL_BODY			"data/MODEL/mune_notpaint.obj"			// 読み込むモデル名
#define	MODEL_HEAD			"data/MODEL/atama_notpaint.obj"			// 読み込むモデル名
#define	MODEL_LEG			"data/MODEL/ashi_notpaint.obj"			// 読み込むモデル名

#define MAX_PLAYER		(10)					// プレイヤーの数
#define MAX_TARGET		(10)					// プレイヤーの数
#define MAX_PLAYER_PARTS (MAX_PLAYER * 2)

#define	PLAYER_SIZE		(70.0f)				// 当たり判定の大きさ
#define	HelperT_SIZE		(300.0f)				// 当たり判定の大きさ
#define	NK_SIZE		(200.0f)				// 当たり判定の大きさ

enum PLAYER_STATE
{
	Standby,	//待機中
	Deffend,	//迎撃中
	Skill,		//スキル使用中
};

enum SKILL_TYPE
{
	neutro_skill,	//好中球のスキル
	macro_skill,	//マクロファージのスキル
	helperT_skill,
	killerT_skill,
	NK_skill,
	kouen_skill,
	skill_max,		//スキル最大数
};
//*****************************************************************************
// 構造体定義
//*****************************************************************************
class PLAYER:public Unit
{
public:
	XMFLOAT3		moveVec;
	// 階層アニメーション用のメンバー変数
	PLAYER				*parent;	// 自分が親ならNULL、自分が子供なら親のenemyアドレス

	int				blockNum;		//ブロックしている数
	int				blockMax;		//ブロック可能数
	int				target;			//ターゲット無しは99で
	int				targetable[MAX_TARGET];	//ターゲット可能な敵の配列添え字を保存しておくもの。このリストの内から、target変数に引き渡される
	int				count;					//現在ターゲットにしている数
	int				keyNum;			//数字キーのどこに対応しているかを保存
	int				cost;			//設置するために必要なコスト
	int				level;			//ユニットレベル
	int				skillID;		//どんなスキルを持っているのか(事前にスキルごとにID振りを行う)
	int				skillPoint;		//保有しているスキルポイント
	int				increaseSP;		//一回で増えるsp量
	int				skillPointMax;	//保有できるスキルポイント。ここまで溜まればスキルが使える
	int				intervalSP;		//spを増やす間隔を図る為の変数
	int				skillTime;
	int				skillTimeMax;
	float				spd;
	BOOL			skillUse;		//スキルを使っているか否か
	BOOL			skillAble;		//スキルを使えるか否か
	int				attackSE;		//攻撃時のSE
};

//プレイヤーの線形補間データを保存
class Playerliner
{
public:
	XMFLOAT3			pos;		// ポリゴンの位置
	XMFLOAT3			rot;		// ポリゴンの向き(回転)
	XMFLOAT3			scl;		// ポリゴンの大きさ(スケール)
};

struct PlayerParts
{
	XMFLOAT3			pos;		// ポリゴンの位置
	XMFLOAT3			rot;		// ポリゴンの向き(回転)
	XMFLOAT3			scl;		// ポリゴンの大きさ(スケール)

	XMFLOAT4X4			mtxWorld;	// ワールドマトリックス

	BOOL				load;
	BOOL				use;
	DX11_MODEL			model;		// モデル情報
	XMFLOAT4			diffuse[MODEL_MAX_MATERIAL];	// モデルの色
	// 階層アニメーション用のメンバー変数
	INTERPOLATION_DATA	*tbl_adrA;	// アニメデータのテーブル先頭アドレス
	int					tbl_sizeA;	// 登録したテーブルのレコード総数
	INTERPOLATION_DATA	*tbl_adrM;	// アニメデータのテーブル先頭アドレス
	int					tbl_sizeM;	// 登録したテーブルのレコード総数
	float				move_time;	// 実行時間
	PLAYER				*parent;	// 自分が親ならNULL、自分が子供なら親のenemyアドレス
};

struct PLAYER_VAR
{
	XMFLOAT3			pos;		// ポリゴンの位置
	XMFLOAT3			rot;		// ポリゴンの向き(回転)
	XMFLOAT3			scl;		// ポリゴンの大きさ(スケール)

	XMFLOAT4X4			mtxWorld;	// ワールドマトリックス
	MATERIAL			material;
	float				pardiff;	//読み取らせるほうの変数
	float				parpolar;	//加算してくほうの変数
	BOOL				load;
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void AttackChar(int i);
void DrawPlayer(void);
void MovePlayer(void);
void ControlPlayer(void);
PLAYER *GetPlayer(void);
PlayerParts *GetPlayerParts(void);
void PlayerStandLiner(int i);
void PlayerInterPoration(int i);
int GetPlayerPartsNum(void);
void SetPlayerPartsNum(int s);
HRESULT MakeVertexPlayerVar(void);
#endif