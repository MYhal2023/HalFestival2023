//=============================================================================
//
// ���U���g���� [result.h]
// Author : 
//
//=============================================================================
#pragma once
#define MAX_REWARD	(5)
#define MAX_PLAYER_NUM	(10)
struct Result
{
	XMFLOAT4 color;
	XMFLOAT2 pos;
	XMFLOAT2 size;
	int textNo;
	int type;
	int enemyNum;	//�G����
	int beatNum;	//���ސ�
	int charId[MAX_PLAYER_NUM];		//�L����ID
	int damage[MAX_PLAYER_NUM];		//�_���[�W��^������
};

struct Reward
{
	int num;				//����ނ̕�V������̂�
	int ID[MAX_REWARD];		//��V�̑f��ID
	int value[MAX_REWARD];	//��V�̑f�ޗ�
};
enum ResultType
{
	Lose,
	Win
};

enum ResultTexture
{
	win,
	lose,
	result_numb,
	result_var,
	result_energy,
	result_oxy,
	result_iron,
	Report,
};

HRESULT InitResult(void);
void UninitResult(void);
void UpdateResult(void);
void DrawResult(void);
void WinResult(void);
void LoseResult(void);
void InitReward(void);
void DrawReward(XMFLOAT2 pos, float size);
void SetReward(int id, int value);
void IncreaseReward(Reward *reward);
Reward *GetReward(void);
void DrawResultButton(XMFLOAT4 color, float px, float py, float sx, float sy);
void DrawResultNumber(int numb, float px, float py, float sx, float sy, XMFLOAT4 color);
void DrawResultChar(void);