#include "map.h"
#include "meshwall.h"
#include "obstacle.h"
#include "rescueLife.h"
#include "mapWallModel.h"
#include "game.h"

static Map g_Map;
//�����Ƀ}�b�v�̑S�v�f��������(���b�V���t�B�[���h�ȊO)
void Map::InitMap(void)
{
	//�T���v��
		//�ǃ��f��
	MapWallModel::Init();

	//���b�V���E�H�[���̐ݒu
	//InitMeshWall();
	InitMeshWall(XMFLOAT3(FIELD_X_LIMIT, WAVE_POS_Y, 0.0f), XMFLOAT3(0.0f, XM_PI * 0.5f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, FIELD_Z_LIMIT * 2.0f, WALL_BLOCK_SIZE_Y, WALL_RAY);

	InitMeshWall(XMFLOAT3(-FIELD_X_LIMIT, WAVE_POS_Y, 0.0f), XMFLOAT3(0.0f, XM_PI * 0.5f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, FIELD_Z_LIMIT * 2.0f, WALL_BLOCK_SIZE_Y, WALL_RAY);

	InitMeshWall(XMFLOAT3(0.0f, WAVE_POS_Y, FIELD_Z_LIMIT), XMFLOAT3(0.0f, XM_PI * 0.0f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, FIELD_X_LIMIT * 2.0f, WALL_BLOCK_SIZE_Y, WALL_RAY);

	InitMeshWall(XMFLOAT3(0.0f, WAVE_POS_Y, -FIELD_Z_LIMIT), XMFLOAT3(0.0f, XM_PI * 0.0f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, FIELD_X_LIMIT * 2.0f, WALL_BLOCK_SIZE_Y, WALL_RAY);

	//�ݒu��Q��
	//SetObstacle();
	XMFLOAT3 p = { 0.0f, 50.0f, 0.0f };
	XMFLOAT3 r = { 0.0f, 0.0f, 0.0f };
	XMFLOAT3 m = { 1.0f, 1.0f, 1.0f };
	Obstacle::SetObstacle(p, r, m, 100.0f, 50.0f, MODEL_TEST);

	////�ݒu�~����
	////RescueLife()
	//p = { 50.0f, 0.0f, 0.0f };
	//r = { 0.0f, 0.0f, 0.0f };
	//RescueLife::SetRemain(p, r, MODEL_RESCUE001);
	//�ݒu�I�u�W�F�N�g


}
