#include "map.h"
#include "meshwall.h"
#include "obstacle.h"
#include "rescueLife.h"
#include "mapWallModel.h"
#include "game.h"
#include "reserve.h"

static Map g_Map;

//ここにマップの全要素を初期化(メッシュフィールド以外)
void Map::InitMap(void)
{
	//サンプル
	//壁モデル
	InitBootMap();
	//メッシュウォールの設置
		//InitMeshWall();
	InitMeshWall(XMFLOAT3(0.0f, 330.0f, 0.0f), XMFLOAT3(XM_PI * 0.5f, XM_PI * 0.0f, XM_PI *0.5f),
		XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), WALL_XZ * 2, WALL_Y * 6, FIELD_Z_LIMIT * 1.0f, WALL_BLOCK_SIZE_Y* 1.1f, WALL_GRAY);
	InitMeshWall(XMFLOAT3(2200.0f, 330.0f, 0.0f), XMFLOAT3(XM_PI * 0.5f, XM_PI * 0.0f, XM_PI *0.5f),
		XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), WALL_XZ * 2, WALL_Y * 6, FIELD_Z_LIMIT * 1.0f, WALL_BLOCK_SIZE_Y* 1.1f, WALL_GRAY);

	InitMeshWall(XMFLOAT3(FIELD_X_LIMIT, WAVE_POS_Y, 0.0f), XMFLOAT3(0.0f, XM_PI * 0.5f, 0.0f),
		XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), WALL_XZ, WALL_Y, FIELD_Z_LIMIT * 2.0f, WALL_BLOCK_SIZE_Y, WALL_GRAY);

	InitMeshWall(XMFLOAT3(-FIELD_X_LIMIT, WAVE_POS_Y, 0.0f), XMFLOAT3(0.0f, XM_PI * 0.5f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, FIELD_Z_LIMIT * 2.0f, WALL_BLOCK_SIZE_Y, WALL_GRAY);

	InitMeshWall(XMFLOAT3(0.0f, WAVE_POS_Y, FIELD_Z_LIMIT), XMFLOAT3(0.0f, XM_PI * 0.0f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, FIELD_X_LIMIT * 2.0f, WALL_BLOCK_SIZE_Y, WALL_GRAY);

	InitMeshWall(XMFLOAT3(0.0f, WAVE_POS_Y, -FIELD_Z_LIMIT), XMFLOAT3(0.0f, XM_PI * 0.0f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, FIELD_X_LIMIT * 2.0f, WALL_BLOCK_SIZE_Y, WALL_GRAY);

	// 右下の部屋
	InitMeshWall(XMFLOAT3(500.0f, WAVE_POS_Y, -625.0f), XMFLOAT3(0.0f, XM_PI * 0.5f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, 375 * 2.0f, WALL_BLOCK_SIZE_Y, WALL_GRAY);

	InitMeshWall(XMFLOAT3(1000.0f, WAVE_POS_Y, -625.0f), XMFLOAT3(0.0f, XM_PI * 0.5f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, 375 * 2.0f, WALL_BLOCK_SIZE_Y, WALL_GRAY);

	InitMeshWall(XMFLOAT3(1500.0f, WAVE_POS_Y, -625.0f), XMFLOAT3(0.0f, XM_PI * 0.5f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, 375 * 2.0f, WALL_BLOCK_SIZE_Y, WALL_GRAY);

	InitMeshWall(XMFLOAT3(600.0f, WAVE_POS_Y, -250.0f), XMFLOAT3(0.0f, XM_PI * 0.0f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, 100 * 2.0f, WALL_BLOCK_SIZE_Y, WALL_GRAY);

	InitMeshWall(XMFLOAT3(900.0f, WAVE_POS_Y, -250.0f), XMFLOAT3(0.0f, XM_PI * 0.0f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, 100 * 2.0f, WALL_BLOCK_SIZE_Y, WALL_GRAY);

	InitMeshWall(XMFLOAT3(1100.0f, WAVE_POS_Y, -250.0f), XMFLOAT3(0.0f, XM_PI * 0.0f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, 100 * 2.0f, WALL_BLOCK_SIZE_Y, WALL_GRAY);

	InitMeshWall(XMFLOAT3(1400.0f, WAVE_POS_Y, -250.0f), XMFLOAT3(0.0f, XM_PI * 0.0f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, 100 * 2.0f, WALL_BLOCK_SIZE_Y, WALL_GRAY);

	InitMeshWall(XMFLOAT3(1600.0f, WAVE_POS_Y, -250.0f), XMFLOAT3(0.0f, XM_PI * 0.0f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, 100 * 2.0f, WALL_BLOCK_SIZE_Y, WALL_GRAY);

	InitMeshWall(XMFLOAT3(1900.0f, WAVE_POS_Y, -250.0f), XMFLOAT3(0.0f, XM_PI * 0.0f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, 100 * 2.0f, WALL_BLOCK_SIZE_Y, WALL_GRAY);

	InitMeshWall(XMFLOAT3(1750.0f, WAVE_POS_Y, -400.0f), XMFLOAT3(0.0f, XM_PI * 0.0f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, 150 * 2.0f, WALL_BLOCK_SIZE_Y, WALL_GRAY);

	InitMeshWall(XMFLOAT3(1750.0f, WAVE_POS_Y, -550.0f), XMFLOAT3(0.0f, XM_PI * 0.5f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, 150 * 2.0f, WALL_BLOCK_SIZE_Y, WALL_GRAY);

	InitMeshWall(XMFLOAT3(1700.0f, WAVE_POS_Y, -700.0f), XMFLOAT3(0.0f, XM_PI * 0.0f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, 50 * 2.0f, WALL_BLOCK_SIZE_Y, WALL_GRAY);

	InitMeshWall(XMFLOAT3(1650.0f, WAVE_POS_Y, -850.0f), XMFLOAT3(0.0f, XM_PI * 0.5f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, 150 * 2.0f, WALL_BLOCK_SIZE_Y, WALL_GRAY);

	InitMeshWall(XMFLOAT3(1500.0f, WAVE_POS_Y, -850.0f), XMFLOAT3(0.0f, XM_PI * 0.0f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, 400 * 2.0f, WALL_BLOCK_SIZE_Y, WALL_GRAY);

	InitMeshWall(XMFLOAT3(1400.0f, WAVE_POS_Y, -650.0f), XMFLOAT3(0.0f, XM_PI * 0.0f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, 100 * 2.0f, WALL_BLOCK_SIZE_Y, WALL_GRAY);

	InitMeshWall(XMFLOAT3(1400.0f, WAVE_POS_Y, -450.0f), XMFLOAT3(0.0f, XM_PI * 0.0f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, 100 * 2.0f, WALL_BLOCK_SIZE_Y, WALL_GRAY);

	// 右上の部屋
	InitMeshWall(XMFLOAT3(500.0f, WAVE_POS_Y, 625.0f), XMFLOAT3(0.0f, XM_PI * 0.5f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, 375 * 2.0f, WALL_BLOCK_SIZE_Y, WALL_GRAY);

	InitMeshWall(XMFLOAT3(600.0f, WAVE_POS_Y, 250.0f), XMFLOAT3(0.0f, XM_PI * 0.0f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, 100 * 2.0f, WALL_BLOCK_SIZE_Y, WALL_GRAY);

	InitMeshWall(XMFLOAT3(900.0f, WAVE_POS_Y, 250.0f), XMFLOAT3(0.0f, XM_PI * 0.0f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, 100 * 2.0f, WALL_BLOCK_SIZE_Y, WALL_GRAY);

	InitMeshWall(XMFLOAT3(1200.0f, WAVE_POS_Y, 250.0f), XMFLOAT3(0.0f, XM_PI * 0.0f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, 200 * 2.0f, WALL_BLOCK_SIZE_Y, WALL_GRAY);

	InitMeshWall(XMFLOAT3(1800.0f, WAVE_POS_Y, 250.0f), XMFLOAT3(0.0f, XM_PI * 0.0f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, 200 * 2.0f, WALL_BLOCK_SIZE_Y, WALL_GRAY);
	// 壊れる壁の所
	InitMeshWall(XMFLOAT3(1000.0f, WAVE_POS_Y, 875.0f), XMFLOAT3(0.0f, XM_PI * 0.5f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, 125 * 2.0f, WALL_BLOCK_SIZE_Y, WALL_GRAY);

	InitMeshWall(XMFLOAT3(1000.0f, WAVE_POS_Y, 375.0f), XMFLOAT3(0.0f, XM_PI * 0.5f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, 125 * 2.0f, WALL_BLOCK_SIZE_Y, WALL_GRAY);


	// 左上の部屋
	InitMeshWall(XMFLOAT3(0.0f, WAVE_POS_Y, 625.0f), XMFLOAT3(0.0f, XM_PI * 0.5f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, 375 * 2.0f, WALL_BLOCK_SIZE_Y, WALL_GRAY);

	InitMeshWall(XMFLOAT3(-1900.0f, WAVE_POS_Y, 250.0f), XMFLOAT3(0.0f, XM_PI * 0.0f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, 100 * 2.0f, WALL_BLOCK_SIZE_Y, WALL_GRAY);

	InitMeshWall(XMFLOAT3(-1500.0f, WAVE_POS_Y, 250.0f), XMFLOAT3(0.0f, XM_PI * 0.0f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, 100 * 2.0f, WALL_BLOCK_SIZE_Y, WALL_GRAY);

	InitMeshWall(XMFLOAT3(-1000.0f, WAVE_POS_Y, 250.0f), XMFLOAT3(0.0f, XM_PI * 0.0f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, 200 * 2.0f, WALL_BLOCK_SIZE_Y, WALL_GRAY);

	InitMeshWall(XMFLOAT3(-500.0f, WAVE_POS_Y, 250.0f), XMFLOAT3(0.0f, XM_PI * 0.0f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, 100 * 2.0f, WALL_BLOCK_SIZE_Y, WALL_GRAY);

	InitMeshWall(XMFLOAT3(-100.0f, WAVE_POS_Y, 250.0f), XMFLOAT3(0.0f, XM_PI * 0.0f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, 100 * 2.0f, WALL_BLOCK_SIZE_Y, WALL_GRAY);
	// 壊れる壁の所
	InitMeshWall(XMFLOAT3(-1000.0f, WAVE_POS_Y, 875.0f), XMFLOAT3(0.0f, XM_PI * 0.5f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, 125 * 2.0f, WALL_BLOCK_SIZE_Y, WALL_GRAY);

	InitMeshWall(XMFLOAT3(-1000.0f, WAVE_POS_Y, 375.0f), XMFLOAT3(0.0f, XM_PI * 0.5f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, 125 * 2.0f, WALL_BLOCK_SIZE_Y, WALL_GRAY);


	// 左下の部屋
	InitMeshWall(XMFLOAT3(0.0f, WAVE_POS_Y, -625.0f), XMFLOAT3(0.0f, XM_PI * 0.5f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, 375 * 2.0f, WALL_BLOCK_SIZE_Y, WALL_GRAY);

	InitMeshWall(XMFLOAT3(-1900.0f, WAVE_POS_Y, -250.0f), XMFLOAT3(0.0f, XM_PI * 0.0f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, 100 * 2.0f, WALL_BLOCK_SIZE_Y, WALL_GRAY);

	InitMeshWall(XMFLOAT3(-100.0f, WAVE_POS_Y, -250.0f), XMFLOAT3(0.0f, XM_PI * 0.0f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, 100 * 2.0f, WALL_BLOCK_SIZE_Y, WALL_GRAY);
	// 壊れる壁の所
	InitMeshWall(XMFLOAT3(-1375.0f, WAVE_POS_Y, -250.0f), XMFLOAT3(0.0f, XM_PI * 0.0f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, 225 * 2.0f, WALL_BLOCK_SIZE_Y, WALL_GRAY);

	InitMeshWall(XMFLOAT3(-625.0f, WAVE_POS_Y, -250.0f), XMFLOAT3(0.0f, XM_PI * 0.0f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, 225 * 2.0f, WALL_BLOCK_SIZE_Y, WALL_GRAY);

	// 備品室・上
	InitMeshWall(XMFLOAT3(100.0f, WAVE_POS_Y, 800.0f), XMFLOAT3(0.0f, XM_PI * 0.0f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, 100 * 2.0f, WALL_BLOCK_SIZE_Y, WALL_GRAY);

	InitMeshWall(XMFLOAT3(400.0f, WAVE_POS_Y, 800.0f), XMFLOAT3(0.0f, XM_PI * 0.0f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, 100 * 2.0f, WALL_BLOCK_SIZE_Y, WALL_GRAY);

	// 備品室・下
	InitMeshWall(XMFLOAT3(100.0f, WAVE_POS_Y, -800.0f), XMFLOAT3(0.0f, XM_PI * 0.0f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, 100 * 2.0f, WALL_BLOCK_SIZE_Y, WALL_GRAY);

	InitMeshWall(XMFLOAT3(400.0f, WAVE_POS_Y, -800.0f), XMFLOAT3(0.0f, XM_PI * 0.0f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, 100 * 2.0f, WALL_BLOCK_SIZE_Y, WALL_GRAY);

	//設置障害物
	//SetObstacle();
	XMFLOAT3 p = { 0.0f, 0.0f, 0.0f };
	XMFLOAT3 r = { 0.0f, 0.0f, 0.0f };
	XMFLOAT3 m = { 1.0f, 1.0f, 1.0f };

	////モデル表示用のやつ
	//Obstacle::SetObstacle(XMFLOAT3{ -400.0f, 0.0f, 0.0f }, XMFLOAT3{ 0.0f, XM_PI * 1.5f, 0.0f }, XMFLOAT3{ 1.8f, 1.5f, 1.5f }, 100.0f, 50.0f, om_bookshelf);
	//Obstacle::SetObstacle(XMFLOAT3{ -600.0f, 0.0f, 0.0f }, XMFLOAT3{ 0.0f, XM_PI * 0.0f, 0.0f }, XMFLOAT3{ 1.5f, 1.5f, 1.5f }, 100.0f, 50.0f, om_book);
	//Obstacle::SetObstacle(XMFLOAT3{ -200.0f, 30.0f, 0.0f }, XMFLOAT3{ 0.0f, XM_PI * 1.5f, 0.0f }, XMFLOAT3{ 3.0f, 2.5f, 5.0f }, 100.0f, 50.0f, om_Ldesk);
	//Obstacle::SetObstacle(XMFLOAT3{ 0.0f, 0.0f, 0.0f }, XMFLOAT3{ 0.0f, XM_PI * 0.0f, 0.0f }, XMFLOAT3{ 2.0f, 2.0f, 2.0f }, 100.0f, 50.0f, om_tank);
	//Obstacle::SetObstacle(XMFLOAT3{ 1300.0f, 0.0f, 0.0f }, XMFLOAT3{ 0.0f, XM_PI * 0.0f, 0.0f }, XMFLOAT3{ 3.0f, 3.0f, 3.0f }, 100.0f, 50.0f, om_box);
	////Obstacle::SetObstacle(XMFLOAT3{ 200.0f, 0.0f, 0.0f }, XMFLOAT3{ 0.0f, 0.0f, 0.0f }, XMFLOAT3{ 2.0f, 2.0f, 2.0f }, 100.0f, 50.0f, om_duct);
	//Obstacle::SetObstacle(XMFLOAT3{ 350.0f, 20.0f, 0.0f }, XMFLOAT3{ 0.0f, XM_PI * 0.0f, XM_PI * 0.5f }, XMFLOAT3{ 5.0f, 5.0f, 5.0f }, 100.0f, 50.0f, om_monitor);
	//Obstacle::SetObstacle(XMFLOAT3{ 1100.0f, 0.0f, 0.0f }, XMFLOAT3{ 0.0f, 0.0f, 0.0f }, XMFLOAT3{ 3.5f, 3.5f, 3.5f }, 100.0f, 50.0f, om_steel);
	//Obstacle::SetObstacle(XMFLOAT3{ 700.0f, 0.0f, 0.0f }, XMFLOAT3{ 0.0f, XM_PI * 0.0f, 0.0f }, XMFLOAT3{ 4.0f, 4.0f, 4.0f }, 100.0f, 50.0f, om_break_wall);
	//Obstacle::SetObstacle(XMFLOAT3{ 900.0f, 0.0f, 0.0f }, XMFLOAT3{ 0.0f, XM_PI * 0.0f, 0.0f }, XMFLOAT3{ 4.0f, 4.0f, 4.0f }, 100.0f, 50.0f, om_test);
	////Obstacle::SetObstacle(XMFLOAT3{ 900.0f, 0.0f, 0.0f }, XMFLOAT3{ 0.0f, 0.0f, 0.0f }, XMFLOAT3{ 1.0f, 1.0f, 1.0f }, 100.0f, 50.0f, om_terminal);

	// 会議室

	// 書庫
	// 書庫
	Obstacle::SetObstacle(XMFLOAT3{ 530.0f, 0.0f, -337.5f }, XMFLOAT3{ 0.0f, XM_PI * 1.5f, 0.0f }, XMFLOAT3{ 1.8f, 1.5f, 1.5f }, 100.0f, 50.0f, om_bookshelf);
	Obstacle::SetObstacle(XMFLOAT3{ 970.0f, 0.0f, -337.5f }, XMFLOAT3{ 0.0f, XM_PI * 0.5f, 0.0f }, XMFLOAT3{ 1.8f, 1.5f, 1.5f }, 100.0f, 50.0f, om_bookshelf);
	Obstacle::SetObstacle(XMFLOAT3{ 530.0f, 0.0f, -525.0f }, XMFLOAT3{ 0.0f, XM_PI * 1.5f, 0.0f }, XMFLOAT3{ 1.8f, 1.5f, 1.5f }, 100.0f, 50.0f, om_bookshelf);
	Obstacle::SetObstacle(XMFLOAT3{ 970.0f, 0.0f, -525.0f }, XMFLOAT3{ 0.0f, XM_PI * 0.5f, 0.0f }, XMFLOAT3{ 1.8f, 1.5f, 1.5f }, 100.0f, 50.0f, om_bookshelf);
	Obstacle::SetObstacle(XMFLOAT3{ 630.0f, 0.0f, -970.0f }, XMFLOAT3{ 0.0f, XM_PI * 1.0f, 0.0f }, XMFLOAT3{ 1.8f, 1.5f, 1.5f }, 100.0f, 50.0f, om_bookshelf);
	Obstacle::SetObstacle(XMFLOAT3{ 870.0f, 0.0f, -970.0f }, XMFLOAT3{ 0.0f, XM_PI * 1.0f, 0.0f }, XMFLOAT3{ 1.8f, 1.5f, 1.5f }, 100.0f, 50.0f, om_bookshelf);

	Obstacle::SetObstacle(XMFLOAT3{ 530.0f, 0.0f, -712.5f }, XMFLOAT3{ 0.0f, XM_PI * 1.5f, 0.0f }, XMFLOAT3{ 1.8f, 1.5f, 1.5f }, 100.0f, 50.0f, om_bookshelf);
	Obstacle::SetObstacle(XMFLOAT3{ 970.0f, 0.0f, -712.5f }, XMFLOAT3{ 0.0f, XM_PI * 0.5f, 0.0f }, XMFLOAT3{ 1.8f, 1.5f, 1.5f }, 100.0f, 50.0f, om_bookshelf);
	Obstacle::SetObstacle(XMFLOAT3{ 530.0f, 0.0f, -900.0f }, XMFLOAT3{ 0.0f, XM_PI * 1.5f, 0.0f }, XMFLOAT3{ 1.8f, 1.5f, 1.5f }, 100.0f, 50.0f, om_bookshelf);
	Obstacle::SetObstacle(XMFLOAT3{ 970.0f, 0.0f, -900.0f }, XMFLOAT3{ 0.0f, XM_PI * 0.5f, 0.0f }, XMFLOAT3{ 1.8f, 1.5f, 1.5f }, 100.0f, 50.0f, om_bookshelf);
	Obstacle::SetObstacle(XMFLOAT3{ 630.0f, 0.0f, -625.0f }, XMFLOAT3{ 0.0f, XM_PI * 1.0f, 0.0f }, XMFLOAT3{ 1.8f, 1.5f, 1.5f }, 100.0f, 50.0f, om_bookshelf);
	Obstacle::SetObstacle(XMFLOAT3{ 870.0f, 0.0f, -625.0f }, XMFLOAT3{ 0.0f, XM_PI * 1.0f, 0.0f }, XMFLOAT3{ 1.8f, 1.5f, 1.5f }, 100.0f, 50.0f, om_bookshelf);

	Obstacle::SetObstacle(XMFLOAT3{ 840.0f, 0.0f, -450.0f }, XMFLOAT3{ 0.0f, XM_PI * 0.0f, 0.0f }, XMFLOAT3{ 1.5f, 1.5f, 1.5f }, 100.0f, 50.0f, om_book);
	Obstacle::SetObstacle(XMFLOAT3{ 630.0f, 0.0f, -800.0f }, XMFLOAT3{ 0.0f, XM_PI * 0.0f, 0.0f }, XMFLOAT3{ 1.5f, 1.5f, 1.5f }, 100.0f, 50.0f, om_book);
	Obstacle::SetObstacle(XMFLOAT3{ 770.0f, 0.0f, -630.0f }, XMFLOAT3{ 0.0f, XM_PI * 0.0f, 0.0f }, XMFLOAT3{ 1.5f, 1.5f, 1.5f }, 100.0f, 50.0f, om_book);

	// 部品置き室
	Obstacle::SetObstacle(XMFLOAT3{ 550.0f, 0.0f, 450.0f }, XMFLOAT3{ 0.0f, XM_PI * 1.5f, 0.0f }, XMFLOAT3{ 1.8f, 1.5f, 1.5f }, 100.0f, 50.0f, om_bookshelf);
	Obstacle::SetObstacle(XMFLOAT3{ 750.0f, 0.0f, 950.0f }, XMFLOAT3{ 0.0f, XM_PI * 0.0f, 0.0f }, XMFLOAT3{ 1.8f, 1.5f, 1.5f }, 100.0f, 50.0f, om_bookshelf);
	Obstacle::SetObstacle(XMFLOAT3{ 950.0f, 30.0f, 500.0f }, XMFLOAT3{ 0.0f, XM_PI * 0.0f, 0.0f }, XMFLOAT3{ 3.0f, 2.5f, 5.0f }, 100.0f, 50.0f, om_Ldesk);
	Obstacle::SetObstacle(XMFLOAT3{ 650.0f, 30.0f, 750.0f }, XMFLOAT3{ 0.0f, XM_PI * 0.0f, 0.0f }, XMFLOAT3{ 3.0f, 2.5f, 5.0f }, 100.0f, 50.0f, om_Ldesk);
	Obstacle::SetObstacle(XMFLOAT3{ 800.0f, 0.0f, 800.0f }, XMFLOAT3{ 0.0f, XM_PI * 0.0f, 0.0f }, XMFLOAT3{ 1.5f, 1.5f, 1.5f }, 100.0f, 50.0f, om_book);

	// 第二研究所
	Obstacle::SetObstacle(XMFLOAT3{ 1250.0f, 0.0f, 750.0f }, XMFLOAT3{ 0.0f, XM_PI * 0.0f, 0.0f }, XMFLOAT3{ 2.0f, 2.0f, 2.0f }, 100.0f, 50.0f, om_tank);
	Obstacle::SetObstacle(XMFLOAT3{ 1250.0f, 0.0f, 750.0f }, XMFLOAT3{ 0.0f, XM_PI * 0.0f, 0.0f }, XMFLOAT3{ 2.0f, 2.0f, 2.0f }, 100.0f, 50.0f, om_tankglass);
	Obstacle::SetObstacle(XMFLOAT3{ 1250.0f, 0.0f, 450.0f }, XMFLOAT3{ 0.0f, XM_PI * 0.0f, 0.0f }, XMFLOAT3{ 2.0f, 2.0f, 2.0f }, 100.0f, 50.0f, om_tank);
	Obstacle::SetObstacle(XMFLOAT3{ 1250.0f, 0.0f, 450.0f }, XMFLOAT3{ 0.0f, XM_PI * 0.0f, 0.0f }, XMFLOAT3{ 2.0f, 2.0f, 2.0f }, 100.0f, 50.0f, om_tankglass);
	Obstacle::SetObstacle(XMFLOAT3{ 1500.0f, 30.0f, 850.0f }, XMFLOAT3{ 0.0f, XM_PI * 0.5f, 0.0f }, XMFLOAT3{ 3.0f, 2.5f, 5.0f }, 100.0f, 50.0f, om_Ldesk);
	Obstacle::SetObstacle(XMFLOAT3{ 1900.0f, 30.0f, 500.0f }, XMFLOAT3{ 0.0f, XM_PI * 0.0f, 0.0f }, XMFLOAT3{ 3.0f, 2.5f, 5.0f }, 100.0f, 50.0f, om_Ldesk);
	Obstacle::SetObstacle(XMFLOAT3{ 1900.0f, 30.0f, 800.0f }, XMFLOAT3{ 0.0f, XM_PI * 0.0f, 0.0f }, XMFLOAT3{ 3.0f, 2.5f, 5.0f }, 100.0f, 50.0f, om_Ldesk);
	Obstacle::SetObstacle(XMFLOAT3{ 1500.0f, 30.0f, 550.0f }, XMFLOAT3{ 0.0f, XM_PI * 0.5f, 0.0f }, XMFLOAT3{ 3.0f, 2.5f, 5.0f }, 100.0f, 50.0f, om_Ldesk);
	Obstacle::SetObstacle(XMFLOAT3{ 1500.0f, 20.0f, 950.0f }, XMFLOAT3{ 0.0f, XM_PI * 1.0f, XM_PI * 0.5f }, XMFLOAT3{ 5.0f, 5.0f, 5.0f }, 100.0f, 50.0f, om_monitor);

	// 第一研究所
	Obstacle::SetObstacle(XMFLOAT3{ -450.0f, 0.0f, 550.0f }, XMFLOAT3{ 0.0f, XM_PI * 0.0f, 0.0f }, XMFLOAT3{ 2.0f, 2.0f, 2.0f }, 100.0f, 50.0f, om_tank);
	Obstacle::SetObstacle(XMFLOAT3{ -450.0f, 0.0f, 550.0f }, XMFLOAT3{ 0.0f, XM_PI * 0.0f, 0.0f }, XMFLOAT3{ 2.0f, 2.0f, 2.0f }, 100.0f, 50.0f, om_tankglass);
	Obstacle::SetObstacle(XMFLOAT3{ -600.0f, 0.0f, 550.0f }, XMFLOAT3{ 0.0f, XM_PI * 1.0f, 0.0f }, XMFLOAT3{ 2.0f, 2.0f, 2.0f }, 100.0f, 50.0f, om_tank);
	Obstacle::SetObstacle(XMFLOAT3{ -600.0f, 0.0f, 550.0f }, XMFLOAT3{ 0.0f, XM_PI * 0.0f, 0.0f }, XMFLOAT3{ 2.0f, 2.0f, 2.0f }, 100.0f, 50.0f, om_tankglass);

	Obstacle::SetObstacle(XMFLOAT3{ -100.0f, 30.0f, 965.0f }, XMFLOAT3{ 0.0f, XM_PI * 0.5f, 0.0f }, XMFLOAT3{ 3.0f, 2.5f, 5.0f }, 100.0f, 50.0f, om_Ldesk);
	Obstacle::SetObstacle(XMFLOAT3{ -250.0f, 30.0f, 965.0f }, XMFLOAT3{ 0.0f, XM_PI * 0.5f, 0.0f }, XMFLOAT3{ 3.0f, 2.5f, 5.0f }, 100.0f, 50.0f, om_Ldesk);
	Obstacle::SetObstacle(XMFLOAT3{ -400.0f, 30.0f, 965.0f }, XMFLOAT3{ 0.0f, XM_PI * 0.5f, 0.0f }, XMFLOAT3{ 3.0f, 2.5f, 5.0f }, 100.0f, 50.0f, om_Ldesk);
	Obstacle::SetObstacle(XMFLOAT3{ -550.0f, 30.0f, 965.0f }, XMFLOAT3{ 0.0f, XM_PI * 0.5f, 0.0f }, XMFLOAT3{ 3.0f, 2.5f, 5.0f }, 100.0f, 50.0f, om_Ldesk);
	Obstacle::SetObstacle(XMFLOAT3{ -100.0f, 30.0f, 910.0f }, XMFLOAT3{ 0.0f, XM_PI * 0.5f, 0.0f }, XMFLOAT3{ 3.0f, 2.5f, 5.0f }, 100.0f, 50.0f, om_Ldesk);
	Obstacle::SetObstacle(XMFLOAT3{ -250.0f, 30.0f, 910.0f }, XMFLOAT3{ 0.0f, XM_PI * 0.5f, 0.0f }, XMFLOAT3{ 3.0f, 2.5f, 5.0f }, 100.0f, 50.0f, om_Ldesk);
	Obstacle::SetObstacle(XMFLOAT3{ -400.0f, 30.0f, 910.0f }, XMFLOAT3{ 0.0f, XM_PI * 0.5f, 0.0f }, XMFLOAT3{ 3.0f, 2.5f, 5.0f }, 100.0f, 50.0f, om_Ldesk);
	Obstacle::SetObstacle(XMFLOAT3{ -550.0f, 30.0f, 910.0f }, XMFLOAT3{ 0.0f, XM_PI * 0.5f, 0.0f }, XMFLOAT3{ 3.0f, 2.5f, 5.0f }, 100.0f, 50.0f, om_Ldesk);

	Obstacle::SetObstacle(XMFLOAT3{ -30.0f, 30.0f, 890.0f }, XMFLOAT3{ 0.0f, XM_PI * 0.0f, 0.0f }, XMFLOAT3{ 3.0f, 2.5f, 5.0f }, 100.0f, 50.0f, om_Ldesk);
	Obstacle::SetObstacle(XMFLOAT3{ -30.0f, 30.0f, 740.0f }, XMFLOAT3{ 0.0f, XM_PI * 0.0f, 0.0f }, XMFLOAT3{ 3.0f, 2.5f, 5.0f }, 100.0f, 50.0f, om_Ldesk);
	Obstacle::SetObstacle(XMFLOAT3{ -30.0f, 30.0f, 590.0f }, XMFLOAT3{ 0.0f, XM_PI * 0.0f, 0.0f }, XMFLOAT3{ 3.0f, 2.5f, 5.0f }, 100.0f, 50.0f, om_Ldesk);
	Obstacle::SetObstacle(XMFLOAT3{ -30.0f, 30.0f, 440.0f }, XMFLOAT3{ 0.0f, XM_PI * 0.0f, 0.0f }, XMFLOAT3{ 3.0f, 2.5f, 5.0f }, 100.0f, 50.0f, om_Ldesk);
	Obstacle::SetObstacle(XMFLOAT3{ -70.0f, 30.0f, 890.0f }, XMFLOAT3{ 0.0f, XM_PI * 0.0f, 0.0f }, XMFLOAT3{ 3.0f, 2.5f, 5.0f }, 100.0f, 50.0f, om_Ldesk);
	Obstacle::SetObstacle(XMFLOAT3{ -70.0f, 30.0f, 740.0f }, XMFLOAT3{ 0.0f, XM_PI * 0.0f, 0.0f }, XMFLOAT3{ 3.0f, 2.5f, 5.0f }, 100.0f, 50.0f, om_Ldesk);
	Obstacle::SetObstacle(XMFLOAT3{ -70.0f, 30.0f, 590.0f }, XMFLOAT3{ 0.0f, XM_PI * 0.0f, 0.0f }, XMFLOAT3{ 3.0f, 2.5f, 5.0f }, 100.0f, 50.0f, om_Ldesk);
	Obstacle::SetObstacle(XMFLOAT3{ -70.0f, 30.0f, 440.0f }, XMFLOAT3{ 0.0f, XM_PI * 0.0f, 0.0f }, XMFLOAT3{ 3.0f, 2.5f, 5.0f }, 100.0f, 50.0f, om_Ldesk);

	Obstacle::SetObstacle(XMFLOAT3{ -750.0f, 0.0f, 985.0f }, XMFLOAT3{ 0.0f, XM_PI * 0.0f, 0.0f }, XMFLOAT3{ 1.8f, 1.5f, 1.5f }, 100.0f, 50.0f, om_bookshelf);
	Obstacle::SetObstacle(XMFLOAT3{ -850.0f, 0.0f, 985.0f }, XMFLOAT3{ 0.0f, XM_PI * 0.0f, 0.0f }, XMFLOAT3{ 1.8f, 1.5f, 1.5f }, 100.0f, 50.0f, om_bookshelf);

	Obstacle::SetObstacle(XMFLOAT3{ -600.0f, 0.0f, 420.0f }, XMFLOAT3{ 0.0f, XM_PI * 0.0f, 0.0f }, XMFLOAT3{ 1.5f, 1.5f, 1.5f }, 100.0f, 50.0f, om_book);
	Obstacle::SetObstacle(XMFLOAT3{ -800.0f, 0.0f, 890.0f }, XMFLOAT3{ 0.0f, XM_PI * 0.0f, 0.0f }, XMFLOAT3{ 1.5f, 1.5f, 1.5f }, 100.0f, 50.0f, om_book);
	Obstacle::SetObstacle(XMFLOAT3{ -890.0f, 0.0f, 600.0f }, XMFLOAT3{ 0.0f, XM_PI * 0.0f, 0.0f }, XMFLOAT3{ 1.5f, 1.5f, 1.5f }, 100.0f, 50.0f, om_book);


	Obstacle::SetObstacle(XMFLOAT3{ -1450.0f, 30.0f, 800.0f }, XMFLOAT3{ 0.0f, XM_PI * 0.5f, 0.0f }, XMFLOAT3{ 3.0f, 2.5f, 5.0f }, 100.0f, 50.0f, om_Ldesk);
	Obstacle::SetObstacle(XMFLOAT3{ -1450.0f, 30.0f, 510.0f }, XMFLOAT3{ 0.0f, XM_PI * 0.5f, 0.0f }, XMFLOAT3{ 3.0f, 2.5f, 5.0f }, 100.0f, 50.0f, om_Ldesk);
	Obstacle::SetObstacle(XMFLOAT3{ -1580.0f, 30.0f, 580.0f }, XMFLOAT3{ 0.0f, XM_PI * 0.0f, 0.0f }, XMFLOAT3{ 3.0f, 2.5f, 5.0f }, 100.0f, 50.0f, om_Ldesk);
	Obstacle::SetObstacle(XMFLOAT3{ -1580.0f, 30.0f, 730.0f }, XMFLOAT3{ 0.0f, XM_PI * 0.0f, 0.0f }, XMFLOAT3{ 3.0f, 2.5f, 5.0f }, 100.0f, 50.0f, om_Ldesk);
	Obstacle::SetObstacle(XMFLOAT3{ -1340.0f, 30.0f, 580.0f }, XMFLOAT3{ 0.0f, XM_PI * 0.0f, 0.0f }, XMFLOAT3{ 3.0f, 2.5f, 5.0f }, 100.0f, 50.0f, om_Ldesk);
	Obstacle::SetObstacle(XMFLOAT3{ -1340.0f, 30.0f, 730.0f }, XMFLOAT3{ 0.0f, XM_PI * 0.0f, 0.0f }, XMFLOAT3{ 3.0f, 2.5f, 5.0f }, 100.0f, 50.0f, om_Ldesk);

	Obstacle::SetObstacle(XMFLOAT3{ -1985.0f, 0.0f, 580.0f }, XMFLOAT3{ 0.0f, XM_PI * 1.5f, 0.0f }, XMFLOAT3{ 1.8f, 1.5f, 1.5f }, 100.0f, 50.0f, om_bookshelf);
	Obstacle::SetObstacle(XMFLOAT3{ -1985.0f, 70.0f, 580.0f }, XMFLOAT3{ 0.0f, XM_PI * 1.5f, 0.0f }, XMFLOAT3{ 1.8f, 1.5f, 1.5f }, 100.0f, 50.0f, om_bookshelf);
	Obstacle::SetObstacle(XMFLOAT3{ -1985.0f, 0.0f, 730.0f }, XMFLOAT3{ 0.0f, XM_PI * 1.5f, 0.0f }, XMFLOAT3{ 1.8f, 1.5f, 1.5f }, 100.0f, 50.0f, om_bookshelf);
	Obstacle::SetObstacle(XMFLOAT3{ -1985.0f, 70.0f, 730.0f }, XMFLOAT3{ 0.0f, XM_PI * 1.5f, 0.0f }, XMFLOAT3{ 1.8f, 1.5f, 1.5f }, 100.0f, 50.0f, om_bookshelf);

	// 第三研究所
//　　　　　　　　　　　　　　　　縦　　　　　　　横
													//縦長大テーブル
	Obstacle::SetObstacle(XMFLOAT3{ -700.0f,  30.0f, -500.0f }, XMFLOAT3{ 0.0f, XM_PI * 0.5f, 0.0f }, XMFLOAT3{ 3.0f, 2.5f, 5.0f }, 100.0f, 50.0f, om_Ldesk);
	Obstacle::SetObstacle(XMFLOAT3{ -800.0f,  30.0f, -500.0f }, XMFLOAT3{ 0.0f, XM_PI * 0.5f, 0.0f }, XMFLOAT3{ 3.0f, 2.5f, 5.0f }, 100.0f, 50.0f, om_Ldesk);
	Obstacle::SetObstacle(XMFLOAT3{ -900.0f,  30.0f, -500.0f }, XMFLOAT3{ 0.0f, XM_PI * 0.5f, 0.0f }, XMFLOAT3{ 3.0f, 2.5f, 5.0f }, 100.0f, 50.0f, om_Ldesk);
	Obstacle::SetObstacle(XMFLOAT3{ -1000.0f, 30.0f, -500.0f }, XMFLOAT3{ 0.0f, XM_PI * 0.5f, 0.0f }, XMFLOAT3{ 3.0f, 2.5f, 5.0f }, 100.0f, 50.0f, om_Ldesk);
	Obstacle::SetObstacle(XMFLOAT3{ -1100.0f, 30.0f, -500.0f }, XMFLOAT3{ 0.0f, XM_PI * 0.5f, 0.0f }, XMFLOAT3{ 3.0f, 2.5f, 5.0f }, 100.0f, 50.0f, om_Ldesk);
	Obstacle::SetObstacle(XMFLOAT3{ -1200.0f, 30.0f, -500.0f }, XMFLOAT3{ 0.0f, XM_PI * 0.5f, 0.0f }, XMFLOAT3{ 3.0f, 2.5f, 5.0f }, 100.0f, 50.0f, om_Ldesk);
	Obstacle::SetObstacle(XMFLOAT3{ -1300.0f, 30.0f, -500.0f }, XMFLOAT3{ 0.0f, XM_PI * 0.5f, 0.0f }, XMFLOAT3{ 3.0f, 2.5f, 5.0f }, 100.0f, 50.0f, om_Ldesk);

	Obstacle::SetObstacle(XMFLOAT3{ -700.0f,  30.0f, -650.0f }, XMFLOAT3{ 0.0f, XM_PI * 0.5f, 0.0f }, XMFLOAT3{ 3.0f, 2.5f, 5.0f }, 100.0f, 50.0f, om_Ldesk);
	Obstacle::SetObstacle(XMFLOAT3{ -800.0f,  30.0f, -650.0f }, XMFLOAT3{ 0.0f, XM_PI * 0.5f, 0.0f }, XMFLOAT3{ 3.0f, 2.5f, 5.0f }, 100.0f, 50.0f, om_Ldesk);
	Obstacle::SetObstacle(XMFLOAT3{ -900.0f,  30.0f, -650.0f }, XMFLOAT3{ 0.0f, XM_PI * 0.5f, 0.0f }, XMFLOAT3{ 3.0f, 2.5f, 5.0f }, 100.0f, 50.0f, om_Ldesk);
	Obstacle::SetObstacle(XMFLOAT3{ -1000.0f, 30.0f, -650.0f }, XMFLOAT3{ 0.0f, XM_PI * 0.5f, 0.0f }, XMFLOAT3{ 3.0f, 2.5f, 5.0f }, 100.0f, 50.0f, om_Ldesk);
	Obstacle::SetObstacle(XMFLOAT3{ -1100.0f, 30.0f, -650.0f }, XMFLOAT3{ 0.0f, XM_PI * 0.5f, 0.0f }, XMFLOAT3{ 3.0f, 2.5f, 5.0f }, 100.0f, 50.0f, om_Ldesk);
	Obstacle::SetObstacle(XMFLOAT3{ -1200.0f, 30.0f, -650.0f }, XMFLOAT3{ 0.0f, XM_PI * 0.5f, 0.0f }, XMFLOAT3{ 3.0f, 2.5f, 5.0f }, 100.0f, 50.0f, om_Ldesk);
	Obstacle::SetObstacle(XMFLOAT3{ -1300.0f, 30.0f, -650.0f }, XMFLOAT3{ 0.0f, XM_PI * 0.5f, 0.0f }, XMFLOAT3{ 3.0f, 2.5f, 5.0f }, 100.0f, 50.0f, om_Ldesk);

	Obstacle::SetObstacle(XMFLOAT3{ -633.5f,  30.0f, -575.0f }, XMFLOAT3{ 0.0f, XM_PI * 0.0f, 0.0f }, XMFLOAT3{ 3.0f, 2.5f, 5.0f }, 100.0f, 50.0f, om_Ldesk);

	Obstacle::SetObstacle(XMFLOAT3{ -1370.0f, 30.0f, -575.0f }, XMFLOAT3{ 0.0f, XM_PI * 0.0f, 0.0f }, XMFLOAT3{ 3.0f, 2.5f, 5.0f }, 100.0f, 50.0f, om_Ldesk);

	// 人体ポット
	Obstacle::SetObstacle(XMFLOAT3{ -1060.0f, 0.0f, -920.0f }, XMFLOAT3{ 0.0f, XM_PI * 1.5f, 0.0f }, XMFLOAT3{ 2.0f, 2.0f, 2.0f }, 100.0f, 50.0f, om_tank);
	Obstacle::SetObstacle(XMFLOAT3{ -860.0f, 0.0f, -920.0f }, XMFLOAT3{ 0.0f, XM_PI * 1.5f, 0.0f }, XMFLOAT3{ 2.0f, 2.0f, 2.0f }, 100.0f, 50.0f, om_tank);
	Obstacle::SetObstacle(XMFLOAT3{ -660.0f, 0.0f, -920.0f }, XMFLOAT3{ 0.0f, XM_PI * 1.5f, 0.0f }, XMFLOAT3{ 2.0f, 2.0f, 2.0f }, 100.0f, 50.0f, om_tank);

	Obstacle::SetObstacle(XMFLOAT3{ -1230.0f, 0.0f, -920.0f }, XMFLOAT3{ 0.0f, XM_PI * 1.5f, 0.0f }, XMFLOAT3{ 2.0f, 2.0f, 2.0f }, 100.0f, 50.0f, om_tank);
	Obstacle::SetObstacle(XMFLOAT3{ -1430.0f, 0.0f, -920.0f }, XMFLOAT3{ 0.0f, XM_PI * 1.5f, 0.0f }, XMFLOAT3{ 2.0f, 2.0f, 2.0f }, 100.0f, 50.0f, om_tank);
	Obstacle::SetObstacle(XMFLOAT3{ -1630.0f, 0.0f, -920.0f }, XMFLOAT3{ 0.0f, XM_PI * 1.5f, 0.0f }, XMFLOAT3{ 2.0f, 2.0f, 2.0f }, 100.0f, 50.0f, om_tank);


	// 障害物
	Obstacle::SetObstacle(XMFLOAT3{ -55.0f, 0.0f,  -750.0f }, XMFLOAT3{ 0.0f, XM_PI * 0.0f, 0.0f }, XMFLOAT3{ 3.0f, 3.0f, 3.0f }, 100.0f, 50.0f, om_box);
	Obstacle::SetObstacle(XMFLOAT3{ -123.0f, 0.0f, -750.0f }, XMFLOAT3{ 0.0f, XM_PI * 0.0f, 0.0f }, XMFLOAT3{ 3.0f, 3.0f, 3.0f }, 100.0f, 50.0f, om_box);
	Obstacle::SetObstacle(XMFLOAT3{ -120.0f, 0.0f, -850.0f }, XMFLOAT3{ 0.0f, XM_PI * 0.0f, 0.0f }, XMFLOAT3{ 3.0f, 3.0f, 3.0f }, 100.0f, 50.0f, om_box);
	Obstacle::SetObstacle(XMFLOAT3{ -123.0f, 0.0f, -950.0f }, XMFLOAT3{ 0.0f, XM_PI * 0.0f, 0.0f }, XMFLOAT3{ 3.0f, 3.0f, 3.0f }, 100.0f, 50.0f, om_box);
	Obstacle::SetObstacle(XMFLOAT3{ -180.0f, 0.0f, -350.0f }, XMFLOAT3{ 0.0f, 0.0f, 0.0f }, XMFLOAT3{ 3.5f, 3.5f, 3.5f }, 100.0f, 50.0f, om_steel);
	Obstacle::SetObstacle(XMFLOAT3{ -210.0f, 0.0f, -550.0f }, XMFLOAT3{ 0.0f, 0.0f, 0.0f }, XMFLOAT3{ 3.5f, 3.5f, 3.5f }, 100.0f, 50.0f, om_steel);
	Obstacle::SetObstacle(XMFLOAT3{ -450.0f, 0.0f, -750.0f }, XMFLOAT3{ 0.0f, 0.0f, 0.0f }, XMFLOAT3{ 3.5f, 3.5f, 3.5f }, 100.0f, 50.0f, om_steel);
	Obstacle::SetObstacle(XMFLOAT3{ -300.0f, 0.0f, -650.0f }, XMFLOAT3{ 0.0f, 0.0f, 0.0f }, XMFLOAT3{ 3.5f, 3.5f, 3.5f }, 100.0f, 50.0f, om_steel);
	Obstacle::SetObstacle(XMFLOAT3{ -530.0f, 0.0f, -820.0f }, XMFLOAT3{ 0.0f, 0.0f, 0.0f }, XMFLOAT3{ 3.5f, 3.5f, 3.5f }, 100.0f, 50.0f, om_steel);
	Obstacle::SetObstacle(XMFLOAT3{ -200.0f, 0.0f, -450.0f }, XMFLOAT3{ 0.0f, 0.0f, 0.0f }, XMFLOAT3{ 3.5f, 3.5f, 3.5f }, 100.0f, 50.0f, om_steel);


	//本棚後ろ
	Obstacle::SetObstacle(XMFLOAT3{ -1925.0f, 0.0f, -700.0f }, XMFLOAT3{ 0.0f, XM_PI * 0.0f, 0.0f }, XMFLOAT3{ 3.0f, 3.0f, 3.0f }, 100.0f, 50.0f, om_box);


	// 本棚
	Obstacle::SetObstacle(XMFLOAT3{ -1850.0f, 0.0f, -290.0f }, XMFLOAT3{ 0.0f, XM_PI * 1.5f, 0.0f }, XMFLOAT3{ 1.8f, 1.5f, 1.5f }, 100.0f, 50.0f, om_bookshelf);
	Obstacle::SetObstacle(XMFLOAT3{ -1850.0f, 0.0f, -368.0f }, XMFLOAT3{ 0.0f, XM_PI * 1.5f, 0.0f }, XMFLOAT3{ 1.8f, 1.5f, 1.5f }, 100.0f, 50.0f, om_bookshelf);
	Obstacle::SetObstacle(XMFLOAT3{ -1850.0f, 0.0f, -446.0f }, XMFLOAT3{ 0.0f, XM_PI * 1.5f, 0.0f }, XMFLOAT3{ 1.8f, 1.5f, 1.5f }, 100.0f, 50.0f, om_bookshelf);
	Obstacle::SetObstacle(XMFLOAT3{ -1850.0f, 0.0f, -524.0f }, XMFLOAT3{ 0.0f, XM_PI * 1.5f, 0.0f }, XMFLOAT3{ 1.8f, 1.5f, 1.5f }, 100.0f, 50.0f, om_bookshelf);
	Obstacle::SetObstacle(XMFLOAT3{ -1850.0f, 0.0f, -602.0f }, XMFLOAT3{ 0.0f, XM_PI * 1.5f, 0.0f }, XMFLOAT3{ 1.8f, 1.5f, 1.5f }, 100.0f, 50.0f, om_bookshelf);
	Obstacle::SetObstacle(XMFLOAT3{ -1850.0f, 0.0f, -680.0f }, XMFLOAT3{ 0.0f, XM_PI * 1.5f, 0.0f }, XMFLOAT3{ 1.8f, 1.5f, 1.5f }, 100.0f, 50.0f, om_bookshelf);
	Obstacle::SetObstacle(XMFLOAT3{ -1850.0f, 0.0f, -758.0f }, XMFLOAT3{ 0.0f, XM_PI * 1.5f, 0.0f }, XMFLOAT3{ 1.8f, 1.5f, 1.5f }, 100.0f, 50.0f, om_bookshelf);

	//ランダム設置
	Reserve *re = GetReserve();
	float rand_base = re->vigilance;		//警戒度を基準にランダム性をもたせる
	int set_num = (int)(rand_base / 10.0f) + 5;	//追加設置数
	//int set_num = 14;
	while (set_num > 0)
	{
		if (set_num > 11)
		{
			for (int i = 0; i < MAX_OBSTACLE_RAND_POS; i++)
			{
				g_Map.use[i] = TRUE;
			}
			break;
		}
		int k = rand() % MAX_OBSTACLE_RAND_POS;

		if (!g_Map.use[k]) {
			g_Map.use[k] = TRUE;
			set_num--;
		}
	}
	for (int i = 0; i < MAX_OBSTACLE_RAND_POS; i++) {
		if (!g_Map.use[i])
			continue;
		int rand_obstacle = rand() % 2;
		switch (rand_obstacle)
		{
		case 0:
			Obstacle::SetObstacle(g_Map.set_pos[i], XMFLOAT3{ 0.0f, XM_PI * 0.0f, 0.0f }, XMFLOAT3{ 3.5f, 3.5f, 3.5f }, 100.0f, 50.0f, om_steel);
			break;
		case 1:
			Obstacle::SetObstacle(g_Map.set_pos[i], XMFLOAT3{ 0.0f, 0.0f, 0.0f }, XMFLOAT3{ 3.0f, 3.0f, 3.0f }, 100.0f, 50.0f, om_box);
			break;
		}
	}
	
	//ランダムで破壊できる壁を設置

	//設置救助者
	//RescueLife()
	set_num = re->quota + 3;	//設置数
	while (set_num > 0)
	{
		if (set_num > MAX_RESCUE_RAND_POS - 2)
		{
			for (int i = 0; i < MAX_RESCUE_RAND_POS; i++)
			{
				g_Map.use_res[i] = TRUE;
			}
			break;
		}
		int k = rand() % MAX_RESCUE_RAND_POS;

		if (!g_Map.use_res[k]) {
			g_Map.use_res[k] = TRUE;
			set_num--;
		}
	}
	for (int i = 0; i < MAX_RESCUE_RAND_POS; i++) {
		if (!g_Map.use_res[i])
			continue;
		int rand_rescue = rand() % 1;
		switch (rand_rescue)
		{
		case 0:
			XMFLOAT3 pos = g_Map.set_res_pos[i];
			RescueLife::SetRemain(pos, XMFLOAT3{ 0.0f, XM_PI * 0.5f, 0.0f }, 0);
			break;
		}
	}
	//設置オブジェクト

}

void Map::InitBootMap(void)
{
	g_Map.set_pos[0] = XMFLOAT3(-298.0f, 0.0f, 176.0f);
	g_Map.set_pos[1] = XMFLOAT3(-298.0f, 0.0f, -182.0f);
	g_Map.set_pos[2] = XMFLOAT3(-711.0f, 0.0f, 162.0f);
	g_Map.set_pos[3] = XMFLOAT3(-1243.0f, 0.0f, 183.0f);
	g_Map.set_pos[4] = XMFLOAT3(-1678.0f, 0.0f, 194.0f);
	g_Map.set_pos[5] = XMFLOAT3(-1701.0f, 0.0f, -190.0f);
	g_Map.set_pos[6] = XMFLOAT3(-1335.0f, 0.0f, -204.0f);
	g_Map.set_pos[7] = XMFLOAT3(252.0f, 0.0f, -646.0f);
	g_Map.set_pos[8] = XMFLOAT3(738.0f, 0.0f, -175.0f);
	g_Map.set_pos[9] = XMFLOAT3(1240.0f, 0.0f, -164.0f);
	g_Map.set_pos[10] = XMFLOAT3(1739.0f, 0.0f, -164.0f);
	g_Map.set_pos[11] = XMFLOAT3(1552.0f, 0.0f, 179.0f);
	g_Map.set_pos[12] = XMFLOAT3(781.0f, 0.0f, 199.0f);
	g_Map.set_pos[13] = XMFLOAT3(251.0f, 0.0f, 664.0f);

	g_Map.set_res_pos[0] = XMFLOAT3(-31.0f, 0.0f, 372.0f);
	g_Map.set_res_pos[1] = XMFLOAT3(-966.0f, 0.0f, 809.0f);
	g_Map.set_res_pos[2] = XMFLOAT3(-1085.0f, 0.0f, 931.0f);
	g_Map.set_res_pos[3] = XMFLOAT3(-1918.0f, 0.0f, 294.0f);
	g_Map.set_res_pos[4] = XMFLOAT3(-1930.0f, 0.0f, 928.0f);
	g_Map.set_res_pos[5] = XMFLOAT3(-1848.f, 0.0f, -226.0f);
	g_Map.set_res_pos[6] = XMFLOAT3(-1970.f, 0.0f, -459.0f);
	g_Map.set_res_pos[7] = XMFLOAT3(-1141.0f, 0.0f, -969.0f);
	g_Map.set_res_pos[8] = XMFLOAT3(-57.0f, 0.0f, -829.0f);
	g_Map.set_res_pos[9] = XMFLOAT3(41.0f, 0.0f, -921.0f);
	g_Map.set_res_pos[10] = XMFLOAT3(750.0f, 0.0f, -900.0f);
	g_Map.set_res_pos[11] = XMFLOAT3(750.0f, 0.0f, -490.0f);
	g_Map.set_res_pos[12] = XMFLOAT3(430.0f, 0.0f, 900.0f);
	g_Map.set_res_pos[13] = XMFLOAT3(530.0f, 0.0f, 900.0f);
	g_Map.set_res_pos[14] = XMFLOAT3(750.0f, 0.0f, 500.0f);
	g_Map.set_res_pos[15] = XMFLOAT3(1900.f, 0.0f, 950.0f);
	g_Map.set_res_pos[16] = XMFLOAT3(1500.f, 0.0f, 700.0f);
	g_Map.set_res_pos[17] = XMFLOAT3(1220.0f, 0.0f, 620.0f);
	g_Map.set_res_pos[18] = XMFLOAT3(1680.0f, 0.0f, 420.0f);
	g_Map.set_res_pos[19] = XMFLOAT3(830.0f, 0.0f, 700.0f);
	g_Map.set_res_pos[20] = XMFLOAT3(550.0f, 0.0f, 940.0f);
	g_Map.set_res_pos[21] = XMFLOAT3(940.0f, 0.0f, 940.0f);
	g_Map.set_res_pos[22] = XMFLOAT3(550.0f, 0.0f, 270.0f);
	g_Map.set_res_pos[23] = XMFLOAT3(1050.0f, 0.0f, 300.0f);
	g_Map.set_res_pos[24] = XMFLOAT3(1250.0f, 0.0f, 815.0f);
	g_Map.set_res_pos[25] = XMFLOAT3(1440.0f, 0.0f, 950.0f);
	g_Map.set_res_pos[26] = XMFLOAT3(1985.0f, 0.0f, 975.0f);
	g_Map.set_res_pos[27] = XMFLOAT3(1900.0f, 0.0f, 690.0f);
	g_Map.set_res_pos[28] = XMFLOAT3(1980.0f, 0.0f, 225.0f);
	g_Map.set_res_pos[29] = XMFLOAT3(950.0f, 0.0f, 375.0f);

	for (int i = 0; i < MAX_OBSTACLE_RAND_POS; i++)
	{
		g_Map.use[i] = FALSE;
	}

	for (int i = 0; i < MAX_RESCUE_RAND_POS; i++)
	{
		g_Map.use_res[i] = FALSE;
	}

}

void Map::InitReserveMap(void)
{
}

void Map::InitResultMap(void)
{
	const float dist = 220.0f;
	float set_pos_x = dist * -1.0f;
	XMFLOAT3 pos, rot, scl;
	pos = { set_pos_x, 0.0f, 100.0f };
	rot = { 0.0f, XM_PI * 0.5f, 0.0f };
	scl = { 4.0f, 4.0f, 4.0f };

	for (int i = 0; i < 6; i++) {
		set_pos_x += dist;
		pos = { set_pos_x, 0.0f, 100.0f };
		MapWallModel::SetMapWallModel(pos, rot, scl, wall_model_basic);
		pos = { set_pos_x, 0.0f, -100.0f };
		MapWallModel::SetMapWallModel(pos, rot, scl, wall_model_basic);

		set_pos_x += dist;
		pos = { set_pos_x, 0.0f, 100.0f };
		MapWallModel::SetMapWallModel(pos, rot, scl, wall_model_window);
		pos = { set_pos_x, 0.0f, -100.0f };
		MapWallModel::SetMapWallModel(pos, rot, scl, wall_model_window);

		set_pos_x += dist;
		pos = { set_pos_x, 0.0f, 100.0f };
		MapWallModel::SetMapWallModel(pos, rot, scl, wall_model_basic);
		pos = { set_pos_x, 0.0f, -100.0f };
		MapWallModel::SetMapWallModel(pos, rot, scl, wall_model_basic);
	}
	InitMeshWall(XMFLOAT3(1000.0f, 150.0f, -100.0f), XMFLOAT3(XM_PI * 0.5f, XM_PI * 0.0f, XM_PI * 0.0f),
		XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), WALL_XZ * 3, WALL_Y, FIELD_Z_LIMIT * 1.0f, FIELD_Z_LIMIT * 1.0f, WALL_GRAY);

}
