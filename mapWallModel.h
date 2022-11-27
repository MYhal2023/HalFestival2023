#pragma once
#pragma once
#include "model.h"
#define	MODEL_NEUTROPHILS	"data/MODEL/neutrophils.obj"			// 読み込むモデル名
#define	MODEL_WALL001	"data/MODEL/doorerror.obj"			// 読み込むモデル名
#define	MODEL_WALL002	"data/MODEL/wall_basic.obj"			// 読み込むモデル名
#define	MODEL_WALL003	"data/MODEL/wall_window.obj"			// 読み込むモデル名
#define	MODEL_WALL004	"data/MODEL/dooropen.obj"			// 読み込むモデル名
#define MAX_WALL_MODEL_NUM (40)

enum
{
	wall_model_error,
	wall_model_basic,
	wall_model_window,
	wall_model_open,
};
//マップの壁モデルクラス
class MapWallModel
{
private:
	XMFLOAT4X4			mtxWorld;	// ワールドマトリックス
	XMFLOAT3			pos;		// ポリゴンの位置
	XMFLOAT3			rot;		// ポリゴンの向き(回転)
	XMFLOAT3			scl;		// ポリゴンの大きさ(スケール)
	int					model_num;
	BOOL				use;
public:
	static void Draw(void);
	static void Init(void);
	static void InitBoot(void);
	static void Uninit(void);
	static void Update(void);
	static void SetMapWallModel(XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 scl, int num);
	static void ResultMoveWall(void);
};