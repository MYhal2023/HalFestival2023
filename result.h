//=============================================================================
//
// ���U���g���� [result.h]
// Author : 
//
//=============================================================================
#pragma once
#define MAX_REWARD	(5)
#define MAX_PLAYER_NUM	(10)
#define MAX_RESULT_SEQUENCE (5)
struct Result
{
	ID3D11ShaderResourceView		*g_Texture;
	XMFLOAT4 color;
	XMFLOAT2 pos;
	XMFLOAT2 size;
};

struct Reward
{
	int beatNum;	//��Q���̔j��
	int rescue_num;	//�~��������
	int time;		//�o�߂�������
	int score;		//���v�X�R�A
	int rank_up;	//�㏸���郉���N�o����
	int  base_rank;
	int increase_rank;

	int ef_beatNum;	//��Q���̔j�󐔏㏸��
	int ef_rescue_num;	//�~���������㏸��
	int ef_time;		//�o�߂������ԏ㏸��
	int ef_score;		//���v�X�R�A�㏸��
	float ef_rank_up;	//�㏸���郉���N�o���ʏ㏸��

	int max_beatNum;	//��Q���̔j�󐔍ő�l
	int max_rescue_num;	//�~���������ő�l
	int max_time;		//�o�߂������ԍő�l
	int max_score;		//���v�X�R�A�ő�l
	int max_rank_up;	//�㏸���郉���N�o���ʍő�l

	int rank;			//���݂̃����N
	int rank_gauge;			//���݂̃Q�[�W��
	int rank_gauge_max;		//�����N�A�b�v�ɕK�v�ȃQ�[�W��

	int rank_bonus_beat;
	int rank_bonus_time;
	int rank_bonus_rescue;
	int rank_bonus_score;

	float dt;
	float set_y;
	int nEaseIndex;
};

enum ResultTexture
{
	result_numb,
	result_numb_cent,
	result_distract,
	result_rescue,
	result_time,
	result_score,
	result_var_bg,
	result_xpvar_bg,
	result_xpvar,
	result_rank_0,
	result_rank_1,
	result_rank_2,
	result_rank_3,
	result_var,
	MAX_RESULT_TEX
};

HRESULT InitResult(void);
void UninitResult(void);
void UpdateResult(void);
void FirstSeq(void);
void SecondSeq(void);
void ThirdSeq(void);
void ForthSeq(void);
void FifthSeq(void);
void DrawResult(void);
void WinResult(void);
void InitReward(void);
void SetReward(void);
Reward *GetReward(void);
void DrawResultNumber(int numb, float px, float py, float sx, float sy, XMFLOAT4 color);
void DrawResultTexture(Result* result);
void DrawResultGauge(Result* result, float tx);
void DrawResultTime(float px, float py, float sx, float sy, XMFLOAT4 color);