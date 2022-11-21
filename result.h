//=============================================================================
//
// リザルト処理 [result.h]
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
	int beatNum;	//障害物の破壊数
	int rescue_num;	//救助した数
	int time;		//経過した時間
	int score;		//合計スコア
	int rank_up;	//上昇するランク経験量

	int ef_beatNum;	//障害物の破壊数上昇数
	int ef_rescue_num;	//救助した数上昇数
	int ef_time;		//経過した時間上昇数
	int ef_score;		//合計スコア上昇数
	float ef_rank_up;	//上昇するランク経験量上昇数

	int max_beatNum;	//障害物の破壊数最大値
	int max_rescue_num;	//救助した数最大値
	int max_time;		//経過した時間最大値
	int max_score;		//合計スコア最大値
	int max_rank_up;	//上昇するランク経験量最大値

	int rank;			//現在のランク
	int rank_gauge;			//現在のゲージ量
	int rank_gauge_max;		//ランクアップに必要なゲージ量

	float dt;
	float set_y;
	int nEaseIndex;
};

enum ResultTexture
{
	result_numb,
	result_numb_cent,
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