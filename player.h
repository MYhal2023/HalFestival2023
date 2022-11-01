//=============================================================================
//
// モデル処理 [player.h]
// Author : 
//
//=============================================================================
#pragma once
#define PLAYER_H_
#include "unitdata.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MODEL_PLAYER		"data/MODEL/dendritic_cells.obj"			// 読み込むモデル名
#define	MODEL_NEUTROPHILS	"data/MODEL/neutrophils.obj"			// 読み込むモデル名
#define	MODEL_BODY			"data/MODEL/mune.obj"			// 読み込むモデル名
#define	MODEL_HEAD			"data/MODEL/kao.obj"			// 読み込むモデル名
#define	MODEL_R_SHOULDER	"data/MODEL/migikata.obj"			// 読み込むモデル名
#define	MODEL_R_ARM			"data/MODEL/migiude.obj"			// 読み込むモデル名
#define	MODEL_L_SHOULDER	"data/MODEL/hidarikata.obj"			// 読み込むモデル名
#define	MODEL_L_ARM			"data/MODEL/hidariude.obj"			// 読み込むモデル名
#define	MODEL_R_THIGH		"data/MODEL/migifutomomo.obj"			// 読み込むモデル名
#define	MODEL_R_FOOT		"data/MODEL/migiashi.obj"			// 読み込むモデル名
#define	MODEL_L_THIGH		"data/MODEL/hidarifutomomo.obj"			// 読み込むモデル名
#define	MODEL_L_FOOT		"data/MODEL/hidariashi.obj"			// 読み込むモデル名

#define MAX_PLAYER		(1)					// プレイヤーの数
#define MAX_PLAYER_PARTS (9)

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

enum PLAYER_PARTS
{
	//P_BODY,	//これをプレイヤーモデルとする
	P_HEAD,
	P_L_SHOULDER,
	P_R_SHOULDER,
	P_L_ARM,
	P_R_ARM,
	P_L_THIGH,
	P_R_THIGH,
	P_L_FOOT,
	P_R_FOOT,
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

	float				spd;
	int					armType;	//装備中のアームタイプ
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
void ControlChangeArm(void);
void SetPlayerArm(void);
void ChangePlayerArm(BOOL flag);
void UpdateArm(void);
PLAYER *GetPlayer(void);
void PlayerStandLiner(int i);
void PlayerInterPoration(int i);
HRESULT MakeVertexPlayerVar(void);
