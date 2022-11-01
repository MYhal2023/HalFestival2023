#include "map.h"
#include "meshwall.h"
#include "obstacle.h"
#include "rescueLife.h"
#include "mapWallModel.h"
#include "game.h"

static Map g_Map;
//ここにマップの全要素を初期化(メッシュフィールド以外)
void Map::InitMap(void)
{
	//サンプル
		//壁モデル
	MapWallModel::Init();

	//メッシュウォールの設置
	//InitMeshWall();
	InitMeshWall(XMFLOAT3(FIELD_X_LIMIT, WAVE_POS_Y, 0.0f), XMFLOAT3(0.0f, XM_PI * 0.5f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, FIELD_Z_LIMIT * 2.0f, WALL_BLOCK_SIZE_Y, WALL_RAY);

	InitMeshWall(XMFLOAT3(-FIELD_X_LIMIT, WAVE_POS_Y, 0.0f), XMFLOAT3(0.0f, XM_PI * 0.5f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, FIELD_Z_LIMIT * 2.0f, WALL_BLOCK_SIZE_Y, WALL_RAY);

	InitMeshWall(XMFLOAT3(0.0f, WAVE_POS_Y, FIELD_Z_LIMIT), XMFLOAT3(0.0f, XM_PI * 0.0f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, FIELD_X_LIMIT * 2.0f, WALL_BLOCK_SIZE_Y, WALL_RAY);

	InitMeshWall(XMFLOAT3(0.0f, WAVE_POS_Y, -FIELD_Z_LIMIT), XMFLOAT3(0.0f, XM_PI * 0.0f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, FIELD_X_LIMIT * 2.0f, WALL_BLOCK_SIZE_Y, WALL_RAY);

	//設置障害物(ランダム)
	//SetObstacle();


	//設置救助者
	//RescueLife()

	//設置オブジェクト


}
