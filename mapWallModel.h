#pragma once
#pragma once
#include "model.h"
#define	MODEL_NEUTROPHILS	"data/MODEL/neutrophils.obj"			// 読み込むモデル名
#define	MODEL_WALL001	"data/MODEL/kabe1.obj"			// 読み込むモデル名
#define	MODEL_WALL002	"data/MODEL/kabe2.obj"			// 読み込むモデル名
#define	MODEL_WALL003	"data/MODEL/kabedoor.obj"			// 読み込むモデル名
#define	MODEL_WALL004	"data/MODEL/MAP_MODEL/kabedoorclosed.obj"			// 読み込むモデル名

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
	static void Uninit(void);
	static void Update(void);
};