#include "map.h"
#include "meshwall.h"
#include "obstacle.h"
#include "rescueLife.h"
#include "mapWallModel.h"
#include "game.h"
#include "reserve.h"

static Map g_Map;

//�����Ƀ}�b�v�̑S�v�f��������(���b�V���t�B�[���h�ȊO)
void Map::InitMap(void)
{
	//�T���v��
	//�ǃ��f��

	//���b�V���E�H�[���̐ݒu
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

	// �E���̕���
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

	// �E��̕���
	InitMeshWall(XMFLOAT3(500.0f, WAVE_POS_Y, 625.0f), XMFLOAT3(0.0f, XM_PI * 0.5f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, 375 * 2.0f, WALL_BLOCK_SIZE_Y, WALL_GRAY);

	InitMeshWall(XMFLOAT3(600.0f, WAVE_POS_Y, 250.0f), XMFLOAT3(0.0f, XM_PI * 0.0f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, 100 * 2.0f, WALL_BLOCK_SIZE_Y, WALL_GRAY);

	InitMeshWall(XMFLOAT3(900.0f, WAVE_POS_Y, 250.0f), XMFLOAT3(0.0f, XM_PI * 0.0f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, 100 * 2.0f, WALL_BLOCK_SIZE_Y, WALL_GRAY);

	InitMeshWall(XMFLOAT3(1000.0f, WAVE_POS_Y, 625.0f), XMFLOAT3(0.0f, XM_PI * 0.5f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, 375 * 2.0f, WALL_BLOCK_SIZE_Y, WALL_GRAY);

	InitMeshWall(XMFLOAT3(1200.0f, WAVE_POS_Y, 250.0f), XMFLOAT3(0.0f, XM_PI * 0.0f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, 200 * 2.0f, WALL_BLOCK_SIZE_Y, WALL_GRAY);

	InitMeshWall(XMFLOAT3(1800.0f, WAVE_POS_Y, 250.0f), XMFLOAT3(0.0f, XM_PI * 0.0f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, 200 * 2.0f, WALL_BLOCK_SIZE_Y, WALL_GRAY);

	// ����̕���
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

	InitMeshWall(XMFLOAT3(-1000.0f, WAVE_POS_Y, 625.0f), XMFLOAT3(0.0f, XM_PI * 0.5f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, 375 * 2.0f, WALL_BLOCK_SIZE_Y, WALL_GRAY);

	// �����̕���
	InitMeshWall(XMFLOAT3(0.0f, WAVE_POS_Y, -625.0f), XMFLOAT3(0.0f, XM_PI * 0.5f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, 375 * 2.0f, WALL_BLOCK_SIZE_Y, WALL_GRAY);

	InitMeshWall(XMFLOAT3(-1900.0f, WAVE_POS_Y, -250.0f), XMFLOAT3(0.0f, XM_PI * 0.0f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, 100 * 2.0f, WALL_BLOCK_SIZE_Y, WALL_GRAY);

	InitMeshWall(XMFLOAT3(-1500.0f, WAVE_POS_Y, -250.0f), XMFLOAT3(0.0f, XM_PI * 0.0f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, 100 * 2.0f, WALL_BLOCK_SIZE_Y, WALL_GRAY);

	InitMeshWall(XMFLOAT3(-800.0f, WAVE_POS_Y, -250.0f), XMFLOAT3(0.0f, XM_PI * 0.0f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, 400 * 2.0f, WALL_BLOCK_SIZE_Y, WALL_GRAY);

	InitMeshWall(XMFLOAT3(-100.0f, WAVE_POS_Y, -250.0f), XMFLOAT3(0.0f, XM_PI * 0.0f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, 100 * 2.0f, WALL_BLOCK_SIZE_Y, WALL_GRAY);

	// ���i���E��
	InitMeshWall(XMFLOAT3(100.0f, WAVE_POS_Y, 800.0f), XMFLOAT3(0.0f, XM_PI * 0.0f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, 100 * 2.0f, WALL_BLOCK_SIZE_Y, WALL_GRAY);

	InitMeshWall(XMFLOAT3(400.0f, WAVE_POS_Y, 800.0f), XMFLOAT3(0.0f, XM_PI * 0.0f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, 100 * 2.0f, WALL_BLOCK_SIZE_Y, WALL_GRAY);

	// ���i���E��
	InitMeshWall(XMFLOAT3(100.0f, WAVE_POS_Y, -800.0f), XMFLOAT3(0.0f, XM_PI * 0.0f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, 100 * 2.0f, WALL_BLOCK_SIZE_Y, WALL_GRAY);

	InitMeshWall(XMFLOAT3(400.0f, WAVE_POS_Y, -800.0f), XMFLOAT3(0.0f, XM_PI * 0.0f, 0.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f), WALL_XZ, WALL_Y, 100 * 2.0f, WALL_BLOCK_SIZE_Y, WALL_GRAY);

	//�ݒu��Q��
	//SetObstacle();
	XMFLOAT3 p = { 0.0f, 0.0f, 0.0f };
	XMFLOAT3 r = { 0.0f, 0.0f, 0.0f };
	XMFLOAT3 m = { 1.0f, 1.0f, 1.0f };

	//���f���\���p�̂��
	Obstacle::SetObstacle(XMFLOAT3{ -400.0f, 0.0f, 0.0f }, XMFLOAT3{ 0.0f, 0.0f, 0.0f }, XMFLOAT3{ 1.0f, 1.5f, 1.5f }, 100.0f, 50.0f, om_bookshelf);
	Obstacle::SetObstacle(XMFLOAT3{ -200.0f, 0.0f, 0.0f }, XMFLOAT3{ 0.0f, 0.0f, 0.0f }, XMFLOAT3{ 2.0f, 1.0f, 2.0f }, 100.0f, 50.0f, om_Ldesk);
	Obstacle::SetObstacle(XMFLOAT3{ 0.0f, 0.0f, 0.0f }, XMFLOAT3{ 0.0f, 0.0f, 0.0f }, XMFLOAT3{ 2.0f, 2.0f, 2.0f }, 100.0f, 50.0f, om_tank);
	Obstacle::SetObstacle(XMFLOAT3{ 100.0f, 0.0f, 0.0f }, XMFLOAT3{ 0.0f, 0.0f, 0.0f }, XMFLOAT3{ 4.0f, 4.0f, 4.0f }, 100.0f, 50.0f, om_box);
	//Obstacle::SetObstacle(XMFLOAT3{ 200.0f, 0.0f, 0.0f }, XMFLOAT3{ 0.0f, 0.0f, 0.0f }, XMFLOAT3{ 2.0f, 2.0f, 2.0f }, 100.0f, 50.0f, om_duct);
	Obstacle::SetObstacle(XMFLOAT3{ 350.0f, 20.0f, 0.0f }, XMFLOAT3{ 0.0f, 0.0f, XM_PI * 0.5f }, XMFLOAT3{ 5.0f, 5.0f, 5.0f }, 100.0f, 50.0f, om_monitor);
	//Obstacle::SetObstacle(XMFLOAT3{ 500.0f, 0.0f, 0.0f }, XMFLOAT3{ 0.0f, 0.0f, 0.0f }, XMFLOAT3{ 5.0f, 5.0f, 5.0f }, 100.0f, 50.0f, om_steel);
	Obstacle::SetObstacle(XMFLOAT3{ 700.0f, 0.0f, 0.0f }, XMFLOAT3{ 0.0f, 0.0f, 0.0f }, XMFLOAT3{ 4.0f, 4.0f, 4.0f }, 100.0f, 50.0f, om_break_wall);
	//Obstacle::SetObstacle(XMFLOAT3{ 900.0f, 0.0f, 0.0f }, XMFLOAT3{ 0.0f, 0.0f, 0.0f }, XMFLOAT3{ 1.0f, 1.0f, 1.0f }, 100.0f, 50.0f, om_terminal);

	// ��c��

	// ��ꌤ����
	Obstacle::SetObstacle(XMFLOAT3{ -144.0f, 0.0f, 765.0f }, XMFLOAT3{ 0.0f, 1.57f, 0.0f }, XMFLOAT3{ 5.0f, 1.0f, 5.0f }, 100.0f, 50.0f, om_Ldesk);
	Obstacle::SetObstacle(XMFLOAT3{ -500.0f, 0.0f, 550.0f }, XMFLOAT3{ 0.0f, 1.57f, 0.0f }, XMFLOAT3{ 2.0f, 2.0f, 2.0f }, 100.0f, 50.0f, om_tank);
	Obstacle::SetObstacle(XMFLOAT3{ -500.0f, 0.0f, 550.0f }, XMFLOAT3{ 0.0f, 1.57f, 0.0f }, XMFLOAT3{ 2.0f, 2.0f, 2.0f }, 100.0f, 50.0f, om_tankglass);

	// ����
	Obstacle::SetObstacle(XMFLOAT3{ 550.0f, 0.0f, -765.0f }, XMFLOAT3{ 0.0f, 4.7f, 0.0f }, XMFLOAT3{ 3.0f, 3.0f, 3.0f }, 100.0f, 50.0f, om_bookshelf);
	Obstacle::SetObstacle(XMFLOAT3{ 750.0f, 0.0f, -900.0f }, XMFLOAT3{ 0.0f, 3.1f, 0.0f }, XMFLOAT3{ 3.0f, 3.0f, 3.0f }, 100.0f, 50.0f, om_bookshelf);

	// ���i�u����
	Obstacle::SetObstacle(XMFLOAT3{ 900.0f, 0.0f, 850.0f }, XMFLOAT3{ 0.0f, 0.7f, 0.0f }, XMFLOAT3{ 3.0f, 3.0f, 3.0f }, 100.0f, 50.0f, om_bookshelf);

	//�����_���ݒu
	Reserve *re = GetReserve();
	float rand_base = re->vigilance;		//�x���x����Ƀ����_��������������
	int set_num = (int)(rand_base / 5.0f);	//�ǉ��ݒu��
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
	int s = 0;
	for (int i = 0; i < MAX_OBSTACLE_RAND_POS; i++) {
		if (!g_Map.use[i])
			continue;
		int rand_obstacle = rand() % 2;
		switch (rand_obstacle)
		{
		case 0:
			g_Map.set_pos[i].y += 15.0f;
			Obstacle::SetObstacle(g_Map.set_pos[i], XMFLOAT3{ 0.0f, XM_PI * 0.5f, 0.0f }, XMFLOAT3{ 5.0f, 5.0f, 5.0f }, 100.0f, 50.0f, om_steel);
			break;
		case 1:
			Obstacle::SetObstacle(g_Map.set_pos[i], XMFLOAT3{ 0.0f, 0.0f, 0.0f }, XMFLOAT3{ 3.0f, 3.0f, 3.0f }, 100.0f, 50.0f, om_box);
			break;
		}
	}
	
	//�����_���Ŕj��ł���ǂ�ݒu


	////�ݒu�~����
	////RescueLife()
	p = { 400.0f, 0.0f, 0.0f };
	r = { 0.0f, 0.0f, 0.0f };
	RescueLife::SetRemain(p, r, 0);
	p = { 600.0f, 0.0f, 0.0f };
	RescueLife::SetRemain(p, r, 0);
	//�ݒu�I�u�W�F�N�g

}

void Map::InitBootMap(void)
{
	g_Map.set_pos[0] = XMFLOAT3(-298.003, 0.0, 176.499);
	g_Map.set_pos[1] = XMFLOAT3(-298.002, 0.0, -182.175);
	g_Map.set_pos[2] = XMFLOAT3(-711.908, 0.0, 162.985);
	g_Map.set_pos[3] = XMFLOAT3(-1243.71, 0.0, 183.222);
	g_Map.set_pos[4] = XMFLOAT3(-1678.95, 0.0, 194.4);
	g_Map.set_pos[5] = XMFLOAT3(-1701.7, 0.0, -190.484);
	g_Map.set_pos[6] = XMFLOAT3(-1335.37, 0.0, -204.254);
	g_Map.set_pos[7] = XMFLOAT3(252.105, 0.0, -646.464);
	g_Map.set_pos[8] = XMFLOAT3(738.792, 0.0, -175.682);
	g_Map.set_pos[9] = XMFLOAT3(1240.1, 0.0, -164.904);
	g_Map.set_pos[10] = XMFLOAT3(1739.5, 0.0, -164.86);
	g_Map.set_pos[11] = XMFLOAT3(1552.4, 0.0, 179.575);
	g_Map.set_pos[12] = XMFLOAT3(781.047, 0.0, 199.842);
	g_Map.set_pos[13] = XMFLOAT3(251.184, 0.0, 664.722);
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
