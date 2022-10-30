//=============================================================================
//
// 弾発射処理 [bullet.h]
// Author : 
//
//=============================================================================
#pragma once
#include "model.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MAX_BULLET		(128)	// 弾最大数

#define	BULLET_WH		(5.0f)	// 当たり判定の大きさ
#define MODEL_BULLET_SAW	"data/MODEL/neutrophils.obj"			// 読み込むモデル名

enum BULLET_VAR
{
	Bullet_XGun,
	Bullet_Braster,
	Bullet_Saw,
	MAX_BULLET_VAR
};
//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{
	DX11_MODEL			model;		// モデル情報
	XMFLOAT4X4	mtxWorld;		// ワールドマトリックス
	XMFLOAT3	pos;			// 位置
	XMFLOAT3	rot;			// 角度
	XMFLOAT3	scl;			// スケール
	MATERIAL	material;		// マテリアル
	float		spd;			// 移動量
	float		fWidth;			// 幅
	float		fHeight;		// 高さ
	float		size;
	float		attack;			//攻撃力
	int			shadowIdx;		// 影ID
	int			life;
	int			model_num;		//使用するモデル
	BOOL		efSwitch;
	BOOL		use;			// 使用しているかどうか

} BULLET;


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void DrawBulletModel(void);
BULLET *GetBullet(void);
void SetBullet(XMFLOAT3 pos, XMFLOAT3 rot, float spd, float attack, int life, int model_num);
