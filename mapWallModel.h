#pragma once
#pragma once
#include "model.h"
#define	MODEL_NEUTROPHILS	"data/MODEL/neutrophils.obj"			// 読み込むモデル名
#define	MODEL_WALL001	"data/MODEL/wall_door_closed.obj"			// 読み込むモデル名
#define	MODEL_WALL002	"data/MODEL/wall_basic.obj"			// 読み込むモデル名
#define	MODEL_WALL003	"data/MODEL/wall_window.obj"			// 読み込むモデル名
#define	MODEL_WALL004	"data/MODEL/wall_door_open.obj"			// 読み込むモデル名

//マップの壁モデルクラス
class MapWallModel
{
private:
	DX11_MODEL			model;		// モデル情報
	XMFLOAT4X4			mtxWorld;	// ワールドマトリックス
	XMFLOAT3			pos;		// ポリゴンの位置
	XMFLOAT3			rot;		// ポリゴンの向き(回転)
	XMFLOAT3			scl;		// ポリゴンの大きさ(スケール)
	BOOL				use;
public:
	static void Draw(void);
	static void Init(void);
	static void InitBoot(void);
	static void Uninit(void);
	static void Update(void);
};