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
	Obstacle::Init();
	FallObject::Init();

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

	// �E���̕���
	InitMeshWall(XMFLOAT3(500.0f, WAVE_POS_Y, -625.0f), XMFLOAT3(0.0f, XM_PI * 0.5f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, 375 * 2.0f, WALL_BLOCK_SIZE_Y, WALL_RAY);

	InitMeshWall(XMFLOAT3(1000.0f, WAVE_POS_Y, -625.0f), XMFLOAT3(0.0f, XM_PI * 0.5f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, 375 * 2.0f, WALL_BLOCK_SIZE_Y, WALL_RAY);

	InitMeshWall(XMFLOAT3(1500.0f, WAVE_POS_Y, -625.0f), XMFLOAT3(0.0f, XM_PI * 0.5f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, 375 * 2.0f, WALL_BLOCK_SIZE_Y, WALL_RAY);

	InitMeshWall(XMFLOAT3(600.0f, WAVE_POS_Y, -250.0f), XMFLOAT3(0.0f, XM_PI * 0.0f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, 100 * 2.0f, WALL_BLOCK_SIZE_Y, WALL_RAY);

	InitMeshWall(XMFLOAT3(900.0f, WAVE_POS_Y, -250.0f), XMFLOAT3(0.0f, XM_PI * 0.0f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, 100 * 2.0f, WALL_BLOCK_SIZE_Y, WALL_RAY);

	InitMeshWall(XMFLOAT3(1100.0f, WAVE_POS_Y, -250.0f), XMFLOAT3(0.0f, XM_PI * 0.0f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, 100 * 2.0f, WALL_BLOCK_SIZE_Y, WALL_RAY);

	InitMeshWall(XMFLOAT3(1400.0f, WAVE_POS_Y, -250.0f), XMFLOAT3(0.0f, XM_PI * 0.0f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, 100 * 2.0f, WALL_BLOCK_SIZE_Y, WALL_RAY);

	InitMeshWall(XMFLOAT3(1600.0f, WAVE_POS_Y, -250.0f), XMFLOAT3(0.0f, XM_PI * 0.0f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, 100 * 2.0f, WALL_BLOCK_SIZE_Y, WALL_RAY);

	InitMeshWall(XMFLOAT3(1900.0f, WAVE_POS_Y, -250.0f), XMFLOAT3(0.0f, XM_PI * 0.0f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, 100 * 2.0f, WALL_BLOCK_SIZE_Y, WALL_RAY);

	InitMeshWall(XMFLOAT3(1750.0f, WAVE_POS_Y, -400.0f), XMFLOAT3(0.0f, XM_PI * 0.0f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, 150 * 2.0f, WALL_BLOCK_SIZE_Y, WALL_RAY);

	InitMeshWall(XMFLOAT3(1750.0f, WAVE_POS_Y, -550.0f), XMFLOAT3(0.0f, XM_PI * 0.5f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, 150 * 2.0f, WALL_BLOCK_SIZE_Y, WALL_RAY);

	InitMeshWall(XMFLOAT3(1700.0f, WAVE_POS_Y, -700.0f), XMFLOAT3(0.0f, XM_PI * 0.0f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, 50 * 2.0f, WALL_BLOCK_SIZE_Y, WALL_RAY);

	InitMeshWall(XMFLOAT3(1650.0f, WAVE_POS_Y, -850.0f), XMFLOAT3(0.0f, XM_PI * 0.5f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, 150 * 2.0f, WALL_BLOCK_SIZE_Y, WALL_RAY);

	InitMeshWall(XMFLOAT3(1500.0f, WAVE_POS_Y, -850.0f), XMFLOAT3(0.0f, XM_PI * 0.0f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, 400 * 2.0f, WALL_BLOCK_SIZE_Y, WALL_RAY);

	InitMeshWall(XMFLOAT3(1400.0f, WAVE_POS_Y, -650.0f), XMFLOAT3(0.0f, XM_PI * 0.0f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, 100 * 2.0f, WALL_BLOCK_SIZE_Y, WALL_RAY);

	InitMeshWall(XMFLOAT3(1400.0f, WAVE_POS_Y, -450.0f), XMFLOAT3(0.0f, XM_PI * 0.0f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, 100 * 2.0f, WALL_BLOCK_SIZE_Y, WALL_RAY);

	// �E��̕���
	InitMeshWall(XMFLOAT3(500.0f, WAVE_POS_Y, 625.0f), XMFLOAT3(0.0f, XM_PI * 0.5f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, 375 * 2.0f, WALL_BLOCK_SIZE_Y, WALL_RAY);

	InitMeshWall(XMFLOAT3(600.0f, WAVE_POS_Y, 250.0f), XMFLOAT3(0.0f, XM_PI * 0.0f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, 100 * 2.0f, WALL_BLOCK_SIZE_Y, WALL_RAY);

	InitMeshWall(XMFLOAT3(900.0f, WAVE_POS_Y, 250.0f), XMFLOAT3(0.0f, XM_PI * 0.0f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, 100 * 2.0f, WALL_BLOCK_SIZE_Y, WALL_RAY);

	InitMeshWall(XMFLOAT3(1000.0f, WAVE_POS_Y, 625.0f), XMFLOAT3(0.0f, XM_PI * 0.5f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, 375 * 2.0f, WALL_BLOCK_SIZE_Y, WALL_RAY);

	InitMeshWall(XMFLOAT3(1200.0f, WAVE_POS_Y, 250.0f), XMFLOAT3(0.0f, XM_PI * 0.0f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, 200 * 2.0f, WALL_BLOCK_SIZE_Y, WALL_RAY);

	InitMeshWall(XMFLOAT3(1800.0f, WAVE_POS_Y, 250.0f), XMFLOAT3(0.0f, XM_PI * 0.0f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, 200 * 2.0f, WALL_BLOCK_SIZE_Y, WALL_RAY);

	// ����̕���
	InitMeshWall(XMFLOAT3(0.0f, WAVE_POS_Y, 625.0f), XMFLOAT3(0.0f, XM_PI * 0.5f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, 375 * 2.0f, WALL_BLOCK_SIZE_Y, WALL_RAY);

	InitMeshWall(XMFLOAT3(-1900.0f, WAVE_POS_Y, 250.0f), XMFLOAT3(0.0f, XM_PI * 0.0f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, 100 * 2.0f, WALL_BLOCK_SIZE_Y, WALL_RAY);

	InitMeshWall(XMFLOAT3(-1500.0f, WAVE_POS_Y, 250.0f), XMFLOAT3(0.0f, XM_PI * 0.0f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, 100 * 2.0f, WALL_BLOCK_SIZE_Y, WALL_RAY);

	InitMeshWall(XMFLOAT3(-1000.0f, WAVE_POS_Y, 250.0f), XMFLOAT3(0.0f, XM_PI * 0.0f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, 200 * 2.0f, WALL_BLOCK_SIZE_Y, WALL_RAY);

	InitMeshWall(XMFLOAT3(-500.0f, WAVE_POS_Y, 250.0f), XMFLOAT3(0.0f, XM_PI * 0.0f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, 100 * 2.0f, WALL_BLOCK_SIZE_Y, WALL_RAY);

	InitMeshWall(XMFLOAT3(-100.0f, WAVE_POS_Y, 250.0f), XMFLOAT3(0.0f, XM_PI * 0.0f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, 100 * 2.0f, WALL_BLOCK_SIZE_Y, WALL_RAY);

	InitMeshWall(XMFLOAT3(-1000.0f, WAVE_POS_Y, 625.0f), XMFLOAT3(0.0f, XM_PI * 0.5f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, 375 * 2.0f, WALL_BLOCK_SIZE_Y, WALL_RAY);

	// �����̕���
	InitMeshWall(XMFLOAT3(0.0f, WAVE_POS_Y, -625.0f), XMFLOAT3(0.0f, XM_PI * 0.5f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, 375 * 2.0f, WALL_BLOCK_SIZE_Y, WALL_RAY);

	InitMeshWall(XMFLOAT3(-1900.0f, WAVE_POS_Y, -250.0f), XMFLOAT3(0.0f, XM_PI * 0.0f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, 100 * 2.0f, WALL_BLOCK_SIZE_Y, WALL_RAY);

	InitMeshWall(XMFLOAT3(-1500.0f, WAVE_POS_Y, -250.0f), XMFLOAT3(0.0f, XM_PI * 0.0f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, 100 * 2.0f, WALL_BLOCK_SIZE_Y, WALL_RAY);

	InitMeshWall(XMFLOAT3(-800.0f, WAVE_POS_Y, -250.0f), XMFLOAT3(0.0f, XM_PI * 0.0f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, 400 * 2.0f, WALL_BLOCK_SIZE_Y, WALL_RAY);

	InitMeshWall(XMFLOAT3(-100.0f, WAVE_POS_Y, -250.0f), XMFLOAT3(0.0f, XM_PI * 0.0f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, 100 * 2.0f, WALL_BLOCK_SIZE_Y, WALL_RAY);

	// ���i���E��
	InitMeshWall(XMFLOAT3(100.0f, WAVE_POS_Y, 800.0f), XMFLOAT3(0.0f, XM_PI * 0.0f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, 100 * 2.0f, WALL_BLOCK_SIZE_Y, WALL_RAY);

	InitMeshWall(XMFLOAT3(400.0f, WAVE_POS_Y, 800.0f), XMFLOAT3(0.0f, XM_PI * 0.0f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, 100 * 2.0f, WALL_BLOCK_SIZE_Y, WALL_RAY);

	// ���i���E��
	InitMeshWall(XMFLOAT3(100.0f, WAVE_POS_Y, -800.0f), XMFLOAT3(0.0f, XM_PI * 0.0f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, 100 * 2.0f, WALL_BLOCK_SIZE_Y, WALL_RAY);

	InitMeshWall(XMFLOAT3(400.0f, WAVE_POS_Y, -800.0f), XMFLOAT3(0.0f, XM_PI * 0.0f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, 100 * 2.0f, WALL_BLOCK_SIZE_Y, WALL_RAY);

	//�ݒu��Q��
	//SetObstacle();
	XMFLOAT3 p = { 0.0f, 0.0f, 0.0f };
	XMFLOAT3 r = { 0.0f, 0.0f, 0.0f };
	XMFLOAT3 m = { 1.0f, 1.0f, 1.0f };

	Obstacle::SetObstacle(XMFLOAT3{ 0.0f, 0.0f, 0.0f }, XMFLOAT3{ 0.0f, 0.0f, 0.0f }, XMFLOAT3{ 1.0f, 1.0f, 1.0f }, 100.0f, 50.0f, MODEL_DCUT);
	Obstacle::SetObstacle(XMFLOAT3{ 100.0f, 0.0f, 0.0f }, XMFLOAT3{ 0.0f, 0.0f, 0.0f }, XMFLOAT3{ 1.0f, 1.0f, 1.0f }, 100.0f, 50.0f, MODEL_BOOKSHELF);
	Obstacle::SetObstacle(XMFLOAT3{ 200.0f, 0.0f, 0.0f }, XMFLOAT3{ 0.0f, 0.0f, 0.0f }, XMFLOAT3{ 1.0f, 1.0f, 1.0f }, 100.0f, 50.0f, MODEL_LDESK);
	Obstacle::SetObstacle(XMFLOAT3{ 350.0f, 0.0f, 0.0f }, XMFLOAT3{ 0.0f, 0.0f, 0.0f }, XMFLOAT3{ 3.0f, 3.0f, 3.0f }, 100.0f, 50.0f, MODEL_GASTANK);
	Obstacle::SetObstacle(XMFLOAT3{ 500.0f, 0.0f, 0.0f }, XMFLOAT3{ 0.0f, 0.0f, 0.0f }, XMFLOAT3{ 4.0f, 4.0f, 4.0f }, 100.0f, 50.0f, MODEL_MONITOR);
	Obstacle::SetObstacle(XMFLOAT3{ 700.0f, 0.0f, 0.0f }, XMFLOAT3{ 0.0f, 0.0f, 0.0f }, XMFLOAT3{ 4.0f, 4.0f, 4.0f }, 100.0f, 50.0f, MODEL_STEEL);

	// ��c��

	// ��ꌤ����
	Obstacle::SetObstacle(XMFLOAT3{ -144.0f, 0.0f, 765.0f }, XMFLOAT3{ 0.0f, 1.57f, 0.0f }, XMFLOAT3{ 5.0f, 1.0f, 5.0f }, 100.0f, 50.0f, MODEL_LDESK);
	Obstacle::SetObstacle(XMFLOAT3{ -500.0f, 0.0f, 550.0f }, XMFLOAT3{ 0.0f, 1.57f, 0.0f }, XMFLOAT3{ 4.0f, 3.0f, 4.0f }, 100.0f, 50.0f, MODEL_TANK);
	Obstacle::SetObstacle(XMFLOAT3{ -500.0f, 0.0f, 550.0f }, XMFLOAT3{ 0.0f, 1.57f, 0.0f }, XMFLOAT3{ 4.0f, 3.0f, 4.0f }, 100.0f, 50.0f, MODEL_TANKGLASS);

	// ����
	Obstacle::SetObstacle(XMFLOAT3{ 550.0f, 0.0f, -765.0f }, XMFLOAT3{ 0.0f, 4.7f, 0.0f }, XMFLOAT3{ 5.0f, 2.0f, 3.0f }, 100.0f, 50.0f, MODEL_BOOKSHELF);
	Obstacle::SetObstacle(XMFLOAT3{ 750.0f, 0.0f, -900.0f }, XMFLOAT3{ 0.0f, 3.1f, 0.0f }, XMFLOAT3{ 5.0f, 2.0f, 3.0f }, 100.0f, 50.0f, MODEL_BOOKSHELF);

	// ���i�u����
	Obstacle::SetObstacle(XMFLOAT3{ 900.0f, 0.0f, 850.0f }, XMFLOAT3{ 0.0f, 0.7f, 0.0f }, XMFLOAT3{ 2.0f, 2.0f, 2.0f }, 100.0f, 50.0f, MODEL_BOOKSHELF);

	//�e�X�g

	////�ݒu�~����
	////RescueLife()
	p = { 400.0f, 0.0f, 0.0f };
	r = { 0.0f, 0.0f, 0.0f };
	RescueLife::SetRemain(p, r, 0);
	p = { 600.0f, 0.0f, 0.0f };
	RescueLife::SetRemain(p, r, 0);
	//�ݒu�I�u�W�F�N�g

}
