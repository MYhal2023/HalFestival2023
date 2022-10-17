
#include "enemy.h"
#include "enemyLinerData.h"


//���F�u�h�E���ۗp�̃Z�b�g�֐�
//����1:���t���[���̎��ɏo���̂��A�̗́A�U���́A�h���
void SetGrape(float time, int life, int power, int deffend, MOVERINE *move, int size)
{
	ENEMY *g_Enemy = GetEnemy();
	EnemyParts *g_Parts = GetEnemyParts();
	g_Enemy[GetEnemyNum()].load = TRUE;
	g_Enemy[GetEnemyNum()].charID = Grape;

	g_Enemy[GetEnemyNum()].rot = { 0.0f, 0.0f, 0.0f };
	g_Enemy[GetEnemyNum()].scl = { 0.8f, 1.0f, 1.0f };

	g_Enemy[GetEnemyNum()].size = 60.0f;	// �����蔻��̑傫��
	g_Enemy[GetEnemyNum()].life = life;
	g_Enemy[GetEnemyNum()].lifeMax = g_Enemy[GetEnemyNum()].life;
	g_Enemy[GetEnemyNum()].spd = 0.5f;
	g_Enemy[GetEnemyNum()].use = FALSE;
	g_Enemy[GetEnemyNum()].attack = FALSE;
	g_Enemy[GetEnemyNum()].attackUse = FALSE;
	g_Enemy[GetEnemyNum()].atInterval = 180;
	g_Enemy[GetEnemyNum()].atFrame = 20;
	g_Enemy[GetEnemyNum()].atFrameCount = 0;
	g_Enemy[GetEnemyNum()].power = power;
	g_Enemy[GetEnemyNum()].diffend = deffend;
	g_Enemy[GetEnemyNum()].target = NULL;
	g_Enemy[GetEnemyNum()].atCount = g_Enemy[GetEnemyNum()].atInterval;	//�ŏ��̓m�[�^�C���ōU�����[�V������
	g_Enemy[GetEnemyNum()].type = Proximity;;
	g_Enemy[GetEnemyNum()].start = time;
	g_Enemy[GetEnemyNum()].moveData = move;
	g_Enemy[GetEnemyNum()].moveCount = 0.0f;
	g_Enemy[GetEnemyNum()].moveTblSize = size;
	g_Enemy[GetEnemyNum()].pos = { move[0].start.x, 0.0f, move[0].start.z };
	g_Enemy[GetEnemyNum()].nowTbl = 0;
	g_Enemy[GetEnemyNum()].tbl_adrA = grape_Attack;	// �A�j���f�[�^�̃e�[�u���擪�A�h���X
	g_Enemy[GetEnemyNum()].tbl_adrM = grape_Move;	// �A�j���f�[�^�̃e�[�u���擪�A�h���X
	g_Enemy[GetEnemyNum()].tbl_sizeA = sizeof(grape_Attack) / sizeof(INTERPOLATION_DATA);	// �o�^�����e�[�u���̃��R�[�h����
	g_Enemy[GetEnemyNum()].tbl_sizeM = sizeof(grape_Move) / sizeof(INTERPOLATION_DATA);	// �o�^�����e�[�u���̃��R�[�h����
	g_Enemy[GetEnemyNum()].move_time = 0.0f;	// ���s����
	g_Enemy[GetEnemyNum()].partsNum = 3;
	g_Enemy[GetEnemyNum()].startNum = GetEnemyPartsNum();
	// �K�w�A�j���[�V�����p�̏���������
	g_Enemy[GetEnemyNum()].parent = NULL;			// �{�́i�e�j�Ȃ̂�NULL������
	{	
		g_Parts[GetEnemyPartsNum()].load = TRUE;

		g_Parts[GetEnemyPartsNum()].pos = { 0.0f, 0.0f, 0.0f };		// �|���S���̈ʒu
		g_Parts[GetEnemyPartsNum()].rot = { 0.0f, 0.0f, 0.0f };		// �|���S���̌���(��])
		g_Parts[GetEnemyPartsNum()].scl = { 1.0f, 1.0f, 1.0f };		// �|���S���̑傫��(�X�P�[��)

		// �K�w�A�j���[�V�����p�̃����o�[�ϐ�
		g_Parts[GetEnemyPartsNum()].tbl_adrA = grape_Parts001Attack;	// �A�j���f�[�^�̃e�[�u���擪�A�h���X
		g_Parts[GetEnemyPartsNum()].tbl_adrM = grape_Parts001Move;	// �A�j���f�[�^�̃e�[�u���擪�A�h���X
		g_Parts[GetEnemyPartsNum()].tbl_sizeA = sizeof(grape_Parts001Attack) / sizeof(INTERPOLATION_DATA);	// �o�^�����e�[�u���̃��R�[�h����
		g_Parts[GetEnemyPartsNum()].tbl_sizeM = sizeof(grape_Parts001Move) / sizeof(INTERPOLATION_DATA);	// �o�^�����e�[�u���̃��R�[�h����
		g_Parts[GetEnemyPartsNum()].move_time = 0;	// ���s����
		g_Parts[GetEnemyPartsNum()].parent = &g_Enemy[GetEnemyNum()];	// �������e�Ȃ�NULL�A�������q���Ȃ�e��enemy�A�h���X
		SetEnemyPartsNum();
	}

	{
		g_Parts[GetEnemyPartsNum()].load = TRUE;

		g_Parts[GetEnemyPartsNum()].pos = { 0.0f, 0.0f, 0.0f };		// �|���S���̈ʒu
		g_Parts[GetEnemyPartsNum()].rot = { 0.0f, 0.0f, 0.0f };		// �|���S���̌���(��])
		g_Parts[GetEnemyPartsNum()].scl = { 1.0f, 1.0f, 1.0f };		// �|���S���̑傫��(�X�P�[��)
		// �K�w�A�j���[�V�����p�̃����o�[�ϐ�
		g_Parts[GetEnemyPartsNum()].tbl_adrA = grape_Parts002Attack;	// �A�j���f�[�^�̃e�[�u���擪�A�h���X
		g_Parts[GetEnemyPartsNum()].tbl_adrM = grape_Parts002Move;	// �A�j���f�[�^�̃e�[�u���擪�A�h���X
		g_Parts[GetEnemyPartsNum()].tbl_sizeA = sizeof(grape_Parts002Attack) / sizeof(INTERPOLATION_DATA);	// �o�^�����e�[�u���̃��R�[�h����
		g_Parts[GetEnemyPartsNum()].tbl_sizeM = sizeof(grape_Parts002Move) / sizeof(INTERPOLATION_DATA);	// �o�^�����e�[�u���̃��R�[�h����
		g_Parts[GetEnemyPartsNum()].move_time = 0;	// ���s����
		g_Parts[GetEnemyPartsNum()].parent = &g_Enemy[GetEnemyNum()];	// �������e�Ȃ�NULL�A�������q���Ȃ�e��enemy�A�h���X
		SetEnemyPartsNum();
	}
	{
		g_Parts[GetEnemyPartsNum()].load = TRUE;

		g_Parts[GetEnemyPartsNum()].pos = { 0.0f, 0.0f, 0.0f };		// �|���S���̈ʒu
		g_Parts[GetEnemyPartsNum()].rot = { 0.0f, 0.0f, 0.0f };		// �|���S���̌���(��])
		g_Parts[GetEnemyPartsNum()].scl = { 1.0f, 1.0f, 1.0f };		// �|���S���̑傫��(�X�P�[��)

			// �K�w�A�j���[�V�����p�̃����o�[�ϐ�
		g_Parts[GetEnemyPartsNum()].tbl_adrA = grape_Parts003Attack;	// �A�j���f�[�^�̃e�[�u���擪�A�h���X
		g_Parts[GetEnemyPartsNum()].tbl_adrM = grape_Parts003Move;	// �A�j���f�[�^�̃e�[�u���擪�A�h���X
		g_Parts[GetEnemyPartsNum()].tbl_sizeA = sizeof(grape_Parts003Attack) / sizeof(INTERPOLATION_DATA);	// �o�^�����e�[�u���̃��R�[�h����
		g_Parts[GetEnemyPartsNum()].tbl_sizeM = sizeof(grape_Parts003Move) / sizeof(INTERPOLATION_DATA);	// �o�^�����e�[�u���̃��R�[�h����
		g_Parts[GetEnemyPartsNum()].move_time = 0;	// ���s����
		g_Parts[GetEnemyPartsNum()].parent = &g_Enemy[GetEnemyNum()];	// �������e�Ȃ�NULL�A�������q���Ȃ�e��enemy�A�h���X
		SetEnemyPartsNum();
	}
	SetEnemyNum();
}

//A�Q���n�A��
//����1:���t���[���̎��ɏo���̂��A�̗́A�U���́A�h���
void SetStrept(float time, int life, int power, int deffend, MOVERINE *move, int size)
{
	ENEMY *g_Enemy = GetEnemy();
	EnemyParts *g_Parts = GetEnemyParts();
	g_Enemy[GetEnemyNum()].load = TRUE;
	g_Enemy[GetEnemyNum()].charID = Strept;

	g_Enemy[GetEnemyNum()].rot = { 0.0f, 0.0f, 0.0f };
	g_Enemy[GetEnemyNum()].scl = { 0.25f, 0.25f, 0.25f };

	g_Enemy[GetEnemyNum()].size = 30.0f;	// �����蔻��̑傫��
	g_Enemy[GetEnemyNum()].life = life;
	g_Enemy[GetEnemyNum()].lifeMax = g_Enemy[GetEnemyNum()].life;
	g_Enemy[GetEnemyNum()].spd = 0.5f;
	g_Enemy[GetEnemyNum()].use = FALSE;
	g_Enemy[GetEnemyNum()].attack = FALSE;
	g_Enemy[GetEnemyNum()].attackUse = FALSE;
	g_Enemy[GetEnemyNum()].atInterval = 180;
	g_Enemy[GetEnemyNum()].atFrame = 20;
	g_Enemy[GetEnemyNum()].atFrameCount = 0;
	g_Enemy[GetEnemyNum()].power = power;
	g_Enemy[GetEnemyNum()].diffend = deffend;
	g_Enemy[GetEnemyNum()].target = NULL;
	g_Enemy[GetEnemyNum()].atCount = g_Enemy[GetEnemyNum()].atInterval;	//�ŏ��̓m�[�^�C���ōU�����[�V������
	g_Enemy[GetEnemyNum()].type = Proximity;;
	g_Enemy[GetEnemyNum()].start = time;
	g_Enemy[GetEnemyNum()].moveData = move;
	g_Enemy[GetEnemyNum()].moveCount = 0.0f;
	g_Enemy[GetEnemyNum()].moveTblSize = size;
	g_Enemy[GetEnemyNum()].pos = { move[0].start.x, 0.0f, move[0].start.z };
	g_Enemy[GetEnemyNum()].nowTbl = 0;
	g_Enemy[GetEnemyNum()].tbl_adrA = strept_Attack;	// �A�j���f�[�^�̃e�[�u���擪�A�h���X
	g_Enemy[GetEnemyNum()].tbl_adrM = strept_Move;	// �A�j���f�[�^�̃e�[�u���擪�A�h���X
	g_Enemy[GetEnemyNum()].tbl_sizeA = sizeof(strept_Attack) / sizeof(INTERPOLATION_DATA);	// �o�^�����e�[�u���̃��R�[�h����
	g_Enemy[GetEnemyNum()].tbl_sizeM = sizeof(strept_Move) / sizeof(INTERPOLATION_DATA);	// �o�^�����e�[�u���̃��R�[�h����
	g_Enemy[GetEnemyNum()].move_time = 0.0f;	// ���s����
	g_Enemy[GetEnemyNum()].partsNum = 3;
	g_Enemy[GetEnemyNum()].startNum = GetEnemyPartsNum();
	// �K�w�A�j���[�V�����p�̏���������
	g_Enemy[GetEnemyNum()].parent = NULL;			// �{�́i�e�j�Ȃ̂�NULL������
	{
		g_Parts[GetEnemyPartsNum()].load = TRUE;

		g_Parts[GetEnemyPartsNum()].pos = { 0.0f, 0.0f, 0.0f };		// �|���S���̈ʒu
		g_Parts[GetEnemyPartsNum()].rot = { 0.0f, 0.0f, 0.0f };		// �|���S���̌���(��])
		g_Parts[GetEnemyPartsNum()].scl = { 1.0f, 1.0f, 1.0f };		// �|���S���̑傫��(�X�P�[��)

		// �K�w�A�j���[�V�����p�̃����o�[�ϐ�
		g_Parts[GetEnemyPartsNum()].tbl_adrA = strept_headAt;	// �A�j���f�[�^�̃e�[�u���擪�A�h���X
		g_Parts[GetEnemyPartsNum()].tbl_adrM = strept_headMv;	// �A�j���f�[�^�̃e�[�u���擪�A�h���X
		g_Parts[GetEnemyPartsNum()].tbl_sizeA = sizeof(strept_headAt) / sizeof(INTERPOLATION_DATA);	// �o�^�����e�[�u���̃��R�[�h����
		g_Parts[GetEnemyPartsNum()].tbl_sizeM = sizeof(strept_headMv) / sizeof(INTERPOLATION_DATA);	// �o�^�����e�[�u���̃��R�[�h����
		g_Parts[GetEnemyPartsNum()].move_time = 0;	// ���s����
		g_Parts[GetEnemyPartsNum()].parent = &g_Enemy[GetEnemyNum()];	// �������e�Ȃ�NULL�A�������q���Ȃ�e��enemy�A�h���X
		SetEnemyPartsNum();
	}

	{
		g_Parts[GetEnemyPartsNum()].load = TRUE;

		g_Parts[GetEnemyPartsNum()].pos = { 0.0f, 0.0f, 0.0f };		// �|���S���̈ʒu
		g_Parts[GetEnemyPartsNum()].rot = { 0.0f, 0.0f, 0.0f };		// �|���S���̌���(��])
		g_Parts[GetEnemyPartsNum()].scl = { 1.0f, 1.0f, 1.0f };		// �|���S���̑傫��(�X�P�[��)
		// �K�w�A�j���[�V�����p�̃����o�[�ϐ�
		g_Parts[GetEnemyPartsNum()].tbl_adrA = strept_neckAt;	// �A�j���f�[�^�̃e�[�u���擪�A�h���X
		g_Parts[GetEnemyPartsNum()].tbl_adrM = strept_neckMv;	// �A�j���f�[�^�̃e�[�u���擪�A�h���X
		g_Parts[GetEnemyPartsNum()].tbl_sizeA = sizeof(strept_neckAt) / sizeof(INTERPOLATION_DATA);	// �o�^�����e�[�u���̃��R�[�h����
		g_Parts[GetEnemyPartsNum()].tbl_sizeM = sizeof(strept_neckMv) / sizeof(INTERPOLATION_DATA);	// �o�^�����e�[�u���̃��R�[�h����
		g_Parts[GetEnemyPartsNum()].move_time = 0;	// ���s����
		g_Parts[GetEnemyPartsNum()].parent = &g_Enemy[GetEnemyNum()];	// �������e�Ȃ�NULL�A�������q���Ȃ�e��enemy�A�h���X
		SetEnemyPartsNum();
	}
	{
		g_Parts[GetEnemyPartsNum()].load = TRUE;

		g_Parts[GetEnemyPartsNum()].pos = { 0.0f, 0.0f, 0.0f };		// �|���S���̈ʒu
		g_Parts[GetEnemyPartsNum()].rot = { 0.0f, 0.0f, 0.0f };		// �|���S���̌���(��])
		g_Parts[GetEnemyPartsNum()].scl = { 1.0f, 1.0f, 1.0f };		// �|���S���̑傫��(�X�P�[��)

			// �K�w�A�j���[�V�����p�̃����o�[�ϐ�
		g_Parts[GetEnemyPartsNum()].tbl_adrA = strept_tailAt;	// �A�j���f�[�^�̃e�[�u���擪�A�h���X
		g_Parts[GetEnemyPartsNum()].tbl_adrM = strept_tailMv;	// �A�j���f�[�^�̃e�[�u���擪�A�h���X
		g_Parts[GetEnemyPartsNum()].tbl_sizeA = sizeof(strept_tailAt) / sizeof(INTERPOLATION_DATA);	// �o�^�����e�[�u���̃��R�[�h����
		g_Parts[GetEnemyPartsNum()].tbl_sizeM = sizeof(strept_tailMv) / sizeof(INTERPOLATION_DATA);	// �o�^�����e�[�u���̃��R�[�h����
		g_Parts[GetEnemyPartsNum()].move_time = 0;	// ���s����
		g_Parts[GetEnemyPartsNum()].parent = &g_Enemy[GetEnemyNum()];	// �������e�Ȃ�NULL�A�������q���Ȃ�e��enemy�A�h���X
		SetEnemyPartsNum();
	}
	SetEnemyNum();
}

//�Δ^��
//����1:���t���[���̎��ɏo���̂��A�̗́A�U���́A�h���
void SetRyoku(float time, int life, int power, int deffend, MOVERINE *move, int size)
{
	ENEMY *g_Enemy = GetEnemy();
	EnemyParts *g_Parts = GetEnemyParts();
	g_Enemy[GetEnemyNum()].load = TRUE;
	g_Enemy[GetEnemyNum()].charID = Ryoku;

	g_Enemy[GetEnemyNum()].rot = { 0.0f, 0.0f, 0.0f };
	g_Enemy[GetEnemyNum()].scl = { 2.0f, 2.0f, 2.0f };

	g_Enemy[GetEnemyNum()].size = 30.0f;	// �����蔻��̑傫��
	g_Enemy[GetEnemyNum()].life = life;
	g_Enemy[GetEnemyNum()].lifeMax = g_Enemy[GetEnemyNum()].life;
	g_Enemy[GetEnemyNum()].spd = 0.5f;
	g_Enemy[GetEnemyNum()].use = FALSE;
	g_Enemy[GetEnemyNum()].attack = FALSE;
	g_Enemy[GetEnemyNum()].attackUse = FALSE;
	g_Enemy[GetEnemyNum()].atInterval = 180;
	g_Enemy[GetEnemyNum()].atFrame = 20;
	g_Enemy[GetEnemyNum()].atFrameCount = 0;
	g_Enemy[GetEnemyNum()].power = power;
	g_Enemy[GetEnemyNum()].diffend = deffend;
	g_Enemy[GetEnemyNum()].target = NULL;
	g_Enemy[GetEnemyNum()].atCount = g_Enemy[GetEnemyNum()].atInterval;	//�ŏ��̓m�[�^�C���ōU�����[�V������
	g_Enemy[GetEnemyNum()].type = Proximity;
	g_Enemy[GetEnemyNum()].start = time;
	g_Enemy[GetEnemyNum()].moveData = move;
	g_Enemy[GetEnemyNum()].moveCount = 0.0f;
	g_Enemy[GetEnemyNum()].moveTblSize = size;
	g_Enemy[GetEnemyNum()].pos = { move[0].start.x, 0.0f, move[0].start.z };
	g_Enemy[GetEnemyNum()].nowTbl = 0;
	g_Enemy[GetEnemyNum()].tbl_adrA = ryoku_Attack;	// �A�j���f�[�^�̃e�[�u���擪�A�h���X
	g_Enemy[GetEnemyNum()].tbl_adrM = ryoku_Move;	// �A�j���f�[�^�̃e�[�u���擪�A�h���X
	g_Enemy[GetEnemyNum()].tbl_sizeA = sizeof(ryoku_Attack) / sizeof(INTERPOLATION_DATA);	// �o�^�����e�[�u���̃��R�[�h����
	g_Enemy[GetEnemyNum()].tbl_sizeM = sizeof(ryoku_Move) / sizeof(INTERPOLATION_DATA);	// �o�^�����e�[�u���̃��R�[�h����
	g_Enemy[GetEnemyNum()].move_time = 0.0f;	// ���s����
	g_Enemy[GetEnemyNum()].partsNum = 2;
	g_Enemy[GetEnemyNum()].startNum = GetEnemyPartsNum();
	// �K�w�A�j���[�V�����p�̏���������
	g_Enemy[GetEnemyNum()].parent = NULL;			// �{�́i�e�j�Ȃ̂�NULL������
	{
		g_Parts[GetEnemyPartsNum()].load = TRUE;

		g_Parts[GetEnemyPartsNum()].pos = { 0.0f, 0.0f, 0.0f };		// �|���S���̈ʒu
		g_Parts[GetEnemyPartsNum()].rot = { 0.0f, 0.0f, 0.0f };		// �|���S���̌���(��])
		g_Parts[GetEnemyPartsNum()].scl = { 1.0f, 1.0f, 1.0f };		// �|���S���̑傫��(�X�P�[��)

		// �K�w�A�j���[�V�����p�̃����o�[�ϐ�
		g_Parts[GetEnemyPartsNum()].tbl_adrA = ryoku_leftAt;	// �A�j���f�[�^�̃e�[�u���擪�A�h���X
		g_Parts[GetEnemyPartsNum()].tbl_adrM = ryoku_leftMv;	// �A�j���f�[�^�̃e�[�u���擪�A�h���X
		g_Parts[GetEnemyPartsNum()].tbl_sizeA = sizeof(ryoku_leftAt) / sizeof(INTERPOLATION_DATA);	// �o�^�����e�[�u���̃��R�[�h����
		g_Parts[GetEnemyPartsNum()].tbl_sizeM = sizeof(ryoku_leftMv) / sizeof(INTERPOLATION_DATA);	// �o�^�����e�[�u���̃��R�[�h����
		g_Parts[GetEnemyPartsNum()].move_time = 0;	// ���s����
		g_Parts[GetEnemyPartsNum()].parent = &g_Enemy[GetEnemyNum()];	// �������e�Ȃ�NULL�A�������q���Ȃ�e��enemy�A�h���X
		SetEnemyPartsNum();
	}

	{
		g_Parts[GetEnemyPartsNum()].load = TRUE;

		g_Parts[GetEnemyPartsNum()].pos = { 0.0f, 0.0f, 0.0f };		// �|���S���̈ʒu
		g_Parts[GetEnemyPartsNum()].rot = { 0.0f, 0.0f, 0.0f };		// �|���S���̌���(��])
		g_Parts[GetEnemyPartsNum()].scl = { 1.0f, 1.0f, 1.0f };		// �|���S���̑傫��(�X�P�[��)
		// �K�w�A�j���[�V�����p�̃����o�[�ϐ�
		g_Parts[GetEnemyPartsNum()].tbl_adrA = ryoku_rightAt;	// �A�j���f�[�^�̃e�[�u���擪�A�h���X
		g_Parts[GetEnemyPartsNum()].tbl_adrM = ryoku_rightMv;	// �A�j���f�[�^�̃e�[�u���擪�A�h���X
		g_Parts[GetEnemyPartsNum()].tbl_sizeA = sizeof(ryoku_rightAt) / sizeof(INTERPOLATION_DATA);	// �o�^�����e�[�u���̃��R�[�h����
		g_Parts[GetEnemyPartsNum()].tbl_sizeM = sizeof(ryoku_rightMv) / sizeof(INTERPOLATION_DATA);	// �o�^�����e�[�u���̃��R�[�h����
		g_Parts[GetEnemyPartsNum()].move_time = 0;	// ���s����
		g_Parts[GetEnemyPartsNum()].parent = &g_Enemy[GetEnemyNum()];	// �������e�Ȃ�NULL�A�������q���Ȃ�e��enemy�A�h���X
		SetEnemyPartsNum();
	}
	SetEnemyNum();
}

void SetInflue(float time, int life, int power, int deffend, MOVERINE *move, int size)
{
	ENEMY *g_Enemy = GetEnemy();
	EnemyParts *g_Parts = GetEnemyParts();
	g_Enemy[GetEnemyNum()].load = TRUE;
	g_Enemy[GetEnemyNum()].charID = Infule;

	g_Enemy[GetEnemyNum()].rot = { 0.0f, 0.0f, 0.0f };
	g_Enemy[GetEnemyNum()].scl = { 0.8f, 1.0f, 1.0f };

	g_Enemy[GetEnemyNum()].size = 60.0f;	// �����蔻��̑傫��
	g_Enemy[GetEnemyNum()].life = life;
	g_Enemy[GetEnemyNum()].lifeMax = g_Enemy[GetEnemyNum()].life;
	g_Enemy[GetEnemyNum()].spd = 0.5f;
	g_Enemy[GetEnemyNum()].use = FALSE;
	g_Enemy[GetEnemyNum()].attack = FALSE;
	g_Enemy[GetEnemyNum()].attackUse = FALSE;
	g_Enemy[GetEnemyNum()].atInterval = 180;
	g_Enemy[GetEnemyNum()].atFrame = 20;
	g_Enemy[GetEnemyNum()].atFrameCount = 0;
	g_Enemy[GetEnemyNum()].power = power;
	g_Enemy[GetEnemyNum()].diffend = deffend;
	g_Enemy[GetEnemyNum()].target = NULL;
	g_Enemy[GetEnemyNum()].atCount = g_Enemy[GetEnemyNum()].atInterval;	//�ŏ��̓m�[�^�C���ōU�����[�V������
	g_Enemy[GetEnemyNum()].type = Proximity;;
	g_Enemy[GetEnemyNum()].start = time;
	g_Enemy[GetEnemyNum()].moveData = move;
	g_Enemy[GetEnemyNum()].moveCount = 0.0f;
	g_Enemy[GetEnemyNum()].moveTblSize = size;
	g_Enemy[GetEnemyNum()].pos = { move[0].start.x, 0.0f, move[0].start.z };
	g_Enemy[GetEnemyNum()].nowTbl = 0;
	g_Enemy[GetEnemyNum()].tbl_adrA = infule_Attack;	// �A�j���f�[�^�̃e�[�u���擪�A�h���X
	g_Enemy[GetEnemyNum()].tbl_adrM = infule_Move;	// �A�j���f�[�^�̃e�[�u���擪�A�h���X
	g_Enemy[GetEnemyNum()].tbl_sizeA = sizeof(infule_Attack) / sizeof(INTERPOLATION_DATA);	// �o�^�����e�[�u���̃��R�[�h����
	g_Enemy[GetEnemyNum()].tbl_sizeM = sizeof(infule_Move) / sizeof(INTERPOLATION_DATA);	// �o�^�����e�[�u���̃��R�[�h����
	g_Enemy[GetEnemyNum()].move_time = 0.0f;	// ���s����
	g_Enemy[GetEnemyNum()].partsNum = 2;
	g_Enemy[GetEnemyNum()].startNum = GetEnemyPartsNum();
	// �K�w�A�j���[�V�����p�̏���������
	g_Enemy[GetEnemyNum()].parent = NULL;			// �{�́i�e�j�Ȃ̂�NULL������
	{
		g_Parts[GetEnemyPartsNum()].load = TRUE;

		g_Parts[GetEnemyPartsNum()].pos = { 0.0f, 0.0f, 0.0f };		// �|���S���̈ʒu
		g_Parts[GetEnemyPartsNum()].rot = { 0.0f, 0.0f, 0.0f };		// �|���S���̌���(��])
		g_Parts[GetEnemyPartsNum()].scl = { 1.0f, 1.0f, 1.0f };		// �|���S���̑傫��(�X�P�[��)

		// �K�w�A�j���[�V�����p�̃����o�[�ϐ�
		g_Parts[GetEnemyPartsNum()].tbl_adrA = infule_Parts001Attack;	// �A�j���f�[�^�̃e�[�u���擪�A�h���X
		g_Parts[GetEnemyPartsNum()].tbl_adrM = infule_Parts001Move;	// �A�j���f�[�^�̃e�[�u���擪�A�h���X
		g_Parts[GetEnemyPartsNum()].tbl_sizeA = sizeof(infule_Parts001Attack) / sizeof(INTERPOLATION_DATA);	// �o�^�����e�[�u���̃��R�[�h����
		g_Parts[GetEnemyPartsNum()].tbl_sizeM = sizeof(infule_Parts001Move) / sizeof(INTERPOLATION_DATA);	// �o�^�����e�[�u���̃��R�[�h����
		g_Parts[GetEnemyPartsNum()].move_time = 0;	// ���s����
		g_Parts[GetEnemyPartsNum()].parent = &g_Enemy[GetEnemyNum()];	// �������e�Ȃ�NULL�A�������q���Ȃ�e��enemy�A�h���X
		SetEnemyPartsNum();
	}

	{
		g_Parts[GetEnemyPartsNum()].load = TRUE;

		g_Parts[GetEnemyPartsNum()].pos = { 0.0f, 0.0f, 0.0f };		// �|���S���̈ʒu
		g_Parts[GetEnemyPartsNum()].rot = { 0.0f, 0.0f, 0.0f };		// �|���S���̌���(��])
		g_Parts[GetEnemyPartsNum()].scl = { 1.0f, 1.0f, 1.0f };		// �|���S���̑傫��(�X�P�[��)
		// �K�w�A�j���[�V�����p�̃����o�[�ϐ�
		g_Parts[GetEnemyPartsNum()].tbl_adrA = infule_Parts002Attack;	// �A�j���f�[�^�̃e�[�u���擪�A�h���X
		g_Parts[GetEnemyPartsNum()].tbl_adrM = infule_Parts002Move;	// �A�j���f�[�^�̃e�[�u���擪�A�h���X
		g_Parts[GetEnemyPartsNum()].tbl_sizeA = sizeof(infule_Parts002Attack) / sizeof(INTERPOLATION_DATA);	// �o�^�����e�[�u���̃��R�[�h����
		g_Parts[GetEnemyPartsNum()].tbl_sizeM = sizeof(infule_Parts002Move) / sizeof(INTERPOLATION_DATA);	// �o�^�����e�[�u���̃��R�[�h����
		g_Parts[GetEnemyPartsNum()].move_time = 0;	// ���s����
		g_Parts[GetEnemyPartsNum()].parent = &g_Enemy[GetEnemyNum()];	// �������e�Ȃ�NULL�A�������q���Ȃ�e��enemy�A�h���X
		SetEnemyPartsNum();
	}
	SetEnemyNum();
}
