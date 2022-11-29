//=============================================================================
//
// リザルト処理 [result.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "sprite.h"
#include "renderer.h"
#include "input.h"
#include "game.h"
#include "result.h"
#include "gameover.h"
#include "debugproc.h"
#include "fade.h"
#include "reserve.h"
#include "sound.h"
#include "time.h"
#include "easing.h"
#include "rescueLife.h"
#include "player.h"
#include "meshfield.h"
#include "mapWallModel.h"
#include "meshwall.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_MAX			(MAX_RESULT_TEX)				// テクスチャの数
#define CH_TEXTURE_MAX			(3)				// テクスチャの数
#define ROW_NUM				(5)				// 一列に並べるユニット数

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static ID3D11Buffer					*g_VertexBuffer = NULL;	// 頂点情報
static char* g_TextureName[MAX_RESULT_TEX] = {
	"data/TEXTURE/number.png",
	"data/TEXTURE/timer_cent.png",
	"data/TEXTURE/distract_num.png",
	"data/TEXTURE/rescue_num.png",
	"data/TEXTURE/time_num.png",
	"data/TEXTURE/final_score.png",
	"data/TEXTURE/xpbar_haikei.png",
	"data/TEXTURE/xpbar_mae.png",
	"data/TEXTURE/xpbar_iro.png",
	"data/TEXTURE/rank_0.png",
	"data/TEXTURE/rank_1.png",
	"data/TEXTURE/rank_2.png",
	"data/TEXTURE/rank_3.png",
	"data/TEXTURE/var.png",
};

static Result g_Result[MAX_RESULT_TEX];
static Reward g_Reward;
static BOOL g_Load = FALSE;
static BOOL once = FALSE;	//一回だけ行う処理で使用
static BOOL ef_once = FALSE;	//一回だけ行う処理で使用
static int sequence = 0;	//リザルトのシーケンス状態
static int skip = 0;
static float alpha[10];
HRESULT InitResult(void)
{
	ID3D11Device *pDevice = GetDevice();

	//テクスチャ生成
	for (int i = 0; i < MAX_RESULT_TEX; i++)
	{
		g_Result[i].g_Texture = NULL;
		D3DX11CreateShaderResourceViewFromFile(GetDevice(),
			g_TextureName[i],
			NULL,
			NULL,
			&g_Result[i].g_Texture,
			NULL);
	}


	// 頂点バッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	GetDevice()->CreateBuffer(&bd, NULL, &g_VertexBuffer);
	for (int i = 0; i < MAX_RESULT_TEX; i++)
	{
		g_Result[i].color = { 1.0f, 1.0f, 1.0f, 1.0f };
		g_Result[i].pos = { SCREEN_CENTER_X, SCREEN_CENTER_Y };
		g_Result[i].size = { SCREEN_WIDTH, SCREEN_HEIGHT };
	}
	for (int i = 0; i < 10; i++) { alpha[i] = 0.0f; }
	sequence = 0;
	g_Load = TRUE;
	once = FALSE;
	ef_once = FALSE;
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitResult(void)
{
	if (g_Load == FALSE) return;

	// 頂点バッファの解放
	if (g_VertexBuffer)
	{
		g_VertexBuffer->Release();
		g_VertexBuffer = NULL;
	}

	// テクスチャの解放
	for (int i = 0; i < MAX_RESULT_TEX; i++)
	{
		if (g_Result[i].g_Texture)
		{
			g_Result[i].g_Texture->Release();
			g_Result[i].g_Texture = NULL;
		}
	}

	g_Load = FALSE;
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateResult(void)
{
	ResultIPUpdate();
	ResultFieldUpdate();
	MapWallModel::ResultMoveWall();
	ResultMoveMeshWall();
	skip++;
	if (skip < 10)return;

	switch (sequence)
	{
	case 0:
		FirstSeq();
		break;
	case 1:
		SecondSeq();
		break;
	case 2:
		ThirdSeq();
		break;
	case 3:
		ForthSeq();
		break;
	case 4:
		FifthSeq();
		break;
	}
	WinResult();

//#ifdef _DEBUG
//	PrintDebugProc("")
//#endif
}

void FirstSeq(void)
{
	if (g_Reward.time < g_Reward.max_time)
		g_Reward.time += g_Reward.ef_time;
	else
		g_Reward.time = g_Reward.max_time;
	if (g_Reward.time == g_Reward.max_time) {
		sequence++;
		skip = 0;
	}
}

void SecondSeq(void)
{
	if (g_Reward.beatNum < g_Reward.max_beatNum)
		g_Reward.beatNum += g_Reward.ef_beatNum;
	else
		g_Reward.beatNum = g_Reward.max_beatNum;

	if (g_Reward.beatNum == g_Reward.max_beatNum) {
		sequence++;
		skip = 0;
	}
}

void ThirdSeq(void)
{
	if (g_Reward.rescue_num < g_Reward.max_rescue_num)
		g_Reward.rescue_num += g_Reward.ef_rescue_num;
	else
		g_Reward.rescue_num = g_Reward.max_rescue_num;
	if (g_Reward.rescue_num == g_Reward.max_rescue_num) {
		sequence++;
		skip = 0;
	}
}
void ForthSeq(void)
{
	if (g_Reward.score < g_Reward.max_score)
		g_Reward.score += g_Reward.ef_score;
	else
		g_Reward.score = g_Reward.max_score;
	if (g_Reward.score == g_Reward.max_score && GetKeyboardTrigger(DIK_RETURN)) { 
		sequence++; 
		g_Reward.nEaseIndex = Easing::SetEase(-500.0f, SCREEN_CENTER_Y, 30.0f);
		skip = -30;
	}

}

void FifthSeq(void)
{
	if (g_Reward.rank_up > 0) {
		g_Reward.ef_rank_up *= 1.01f;
		//増加量が規定をオーバーしていたら調整
		if ((int)(g_Reward.ef_rank_up) > g_Reward.rank_up)
		{
			g_Reward.ef_rank_up = (float)(g_Reward.rank_up);
		}

		g_Reward.rank_gauge += (int)(g_Reward.ef_rank_up);
		g_Reward.rank_up -= (int)(g_Reward.ef_rank_up);

		if (g_Reward.rank_gauge >= g_Reward.rank_gauge_max) {
			g_Reward.rank++;
			g_Reward.rank_gauge -= g_Reward.rank_gauge_max;
		}
	}
	if (g_Reward.rank_up <= 0 && !ef_once) {
		skip = -40;
		ef_once = TRUE;
		return;
	}
	if (g_Reward.rank_up <= 0) { 
		sequence++; 
		g_Reward.nEaseIndex = Easing::SetEase(SCREEN_CENTER_Y, SCREEN_HEIGHT + 500.0f, 60.0f);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawResult(void)
{
	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// マトリクス設定
	SetWorldViewProjection2D();

	// プリミティブトポロジ設定
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// マテリアル設定
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	SetMaterial(material);

	float pos_y = SCREEN_HEIGHT * 0.10f;
	// リザルトの経過時間を描画
	g_Result[result_time].pos = { SCREEN_WIDTH *0.65f , pos_y };
	g_Result[result_time].size = { 530.0f * 0.80f, 100.0f *0.75f };
	g_Result[result_time].color = { 1.0f, 1.0f, 1.0f, 1.0f };
	DrawResultTexture(&g_Result[result_time]);
	pos_y += 80.0f + 8.0f;
	DrawResultTime(SCREEN_WIDTH *0.65f, pos_y, 40.0f, 80.0f, XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));

	// リザルトの救助者数を描画
	pos_y += 80.0f + 32.0f;
	g_Result[result_distract].pos = { SCREEN_WIDTH *0.65f , pos_y };
	g_Result[result_distract].size = { 530.0f *0.80f, 100.0f *0.75f };
	g_Result[result_distract].color = { 1.0f, 1.0f, 1.0f, 1.0f };
	DrawResultTexture(&g_Result[result_distract]);
	pos_y += 80.0f + 8.0f;
	DrawResultNumber(g_Reward.beatNum, SCREEN_WIDTH *0.58f, pos_y, 40.0f, 80.0f, XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));

	// リザルトの破壊数を描画
	pos_y += 80.0f + 32.0f;
	g_Result[result_rescue].pos = { SCREEN_WIDTH *0.65f , pos_y };
	g_Result[result_rescue].size = { 530.0f * 0.80f, 100.0f *0.75f };
	g_Result[result_rescue].color = { 1.0f, 1.0f, 1.0f, 1.0f };
	DrawResultTexture(&g_Result[result_rescue]);
	pos_y += 80.0f + 8.0f;
	DrawResultNumber(g_Reward.rescue_num, SCREEN_WIDTH *0.58f, pos_y, 40.0f, 80.0f, XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));

	// リザルトのスコアを描画
	pos_y += 160.0f + 40.0f;
	g_Result[result_score].pos = { SCREEN_WIDTH *0.65f , pos_y };
	g_Result[result_score].size = { 530.0f * 1.0f, 100.0f *1.0f};
	g_Result[result_score].color = { 1.0f, 1.0f, 1.0f, 1.0f };
	DrawResultTexture(&g_Result[result_score]);
	pos_y += 160.0f + 8.0f;
	DrawResultNumber(g_Reward.score, SCREEN_WIDTH *0.60f, pos_y, 80.0f, 160.0f, XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));

	if (sequence >= 4)
	{
		if (sequence >= 5)
		{
			//g_Reward.set_y += 100.0f * g_Reward.dt;
			g_Reward.set_y = Easing::GetEase(g_Reward.nEaseIndex);
		}
		else if (sequence == 4)
		{
			g_Reward.set_y = Easing::GetEase(g_Reward.nEaseIndex);
		}

		if (sequence < 5) {
			g_Result[result_var].pos = { SCREEN_CENTER_X  , SCREEN_CENTER_Y };
			g_Result[result_var].size = { SCREEN_WIDTH, SCREEN_HEIGHT };
			g_Result[result_var].color = { 0.0f, 0.0f, 0.0f, 0.5f };
			DrawResultTexture(&g_Result[result_var]);
		}
		Reserve* re = GetReserve();

		int rank = result_rank_0 + g_Reward.rank;
		if (rank > result_rank_3) {
			rank = result_rank_3;
			g_Reward.rank_gauge = g_Reward.rank_gauge_max;
		}
		g_Result[rank].pos = { SCREEN_CENTER_X , g_Reward.set_y };
		g_Result[rank].size = { 1900.0f * 0.75f, 800.0f *0.75f };
		g_Result[rank].color = { 1.0f, 1.0f, 1.0f, 1.0f };
		DrawResultTexture(&g_Result[rank]);

		g_Result[result_var_bg].pos = { SCREEN_CENTER_X , g_Reward.set_y + 50.0f };
		g_Result[result_var_bg].size = { 1800.0f * 0.5f, 1000.0f *0.25f };
		g_Result[result_var_bg].color = { 1.0f, 1.0f, 1.0f, 1.0f };
		DrawResultTexture(&g_Result[result_var_bg]);


		g_Result[result_xpvar_bg].pos = { SCREEN_CENTER_X , g_Reward.set_y + 50.0f };
		g_Result[result_xpvar_bg].size = { 810.0f, 80.0f };
		g_Result[result_xpvar_bg].color = { 1.0f, 1.0f, 1.0f, 1.0f };
		DrawResultTexture(&g_Result[result_xpvar_bg]);


		float par = (float)(g_Reward.rank_gauge) / (float)(g_Reward.rank_gauge_max);
		g_Result[result_xpvar].size = { 800.0f * par , 72.0f };
		g_Result[result_xpvar].pos = { SCREEN_CENTER_X + (800.0f * (par - 1.0f)) * 0.5f, g_Reward.set_y + 50.0f };
		g_Result[result_xpvar].color = { 1.0f, 1.0f, 1.0f, 1.0f };
		DrawResultGauge(&g_Result[result_xpvar], par);

	}
}

void WinResult(void)
{
	if (!once) {
		//PlaySound(SOUND_LABEL_BGM_Win);
		
		once = TRUE;
	}
	//if (GetKeyboardTrigger(DIK_RETURN))
	//{
	//	sequence++;
	//}

	if(sequence >= MAX_RESULT_SEQUENCE && GetKeyboardTrigger(DIK_RETURN))
	SetFade(FADE_OUT, MODE_RESERVE, WhiteBox);	//現状ループするように

}


void InitReward(void)
{
	g_Reward.beatNum = 0;
	g_Reward.rescue_num = 0;
	g_Reward.time = 60;
	g_Reward.score = 0;
	g_Reward.rank_up = 0;

	g_Reward.ef_beatNum = 0;
	g_Reward.ef_rescue_num = 0;
	g_Reward.ef_time = 0;
	g_Reward.ef_score = 0;
	g_Reward.ef_rank_up = 1.0f;

	g_Reward.rank = 0;
	g_Reward.rank_gauge = 0;
	g_Reward.rank_gauge_max = 100;

	g_Reward.set_y -= SCREEN_CENTER_Y;
	g_Reward.dt = 0.9f;
}


//モード変更時に引き継ぐデータがある場合、ここで行う
void SetReward(void)
{
	Reserve* re = GetReserve();
	//次回警戒度の算出を行う
	re->old_vigi = re->vigilance;
	int rand_base_num = 0;
	if (RescueLife::GetRescueRemainLife() <= 0)
		rand_base_num = 5;

	if (GetOverType() == OVER_WIN)
		re->vigilance += (float)(rand() % 5 + rand_base_num);
	else
		re->vigilance -= (float)(rand() % 5 + 5);

	if (re->vigilance < 0)
		re->vigilance = 0;

	int base = (int)((re->vigilance) /30.0f);
	re->quota = BASE_RESCUE_NUM + base;

	//ここでデータ引継ぎを行う
	g_Reward.time = GAME_TIME - GetTime();



	g_Reward.ef_beatNum = g_Reward.beatNum / 30;
	if (g_Reward.ef_beatNum < 1)
		g_Reward.ef_beatNum = 1;

	g_Reward.ef_rescue_num = g_Reward.rescue_num / 30;
	if (g_Reward.ef_rescue_num < 1)
		g_Reward.ef_rescue_num = 1;

	g_Reward.ef_time = g_Reward.time / 30;
	if (g_Reward.ef_time < 1)
		g_Reward.ef_time = 1;

	g_Reward.score = (int)((float)(g_Reward.beatNum * 100 + g_Reward.rescue_num * 200 + GetTime() * 150) * (re->vigilance + 1.0f));
	g_Reward.ef_score = g_Reward.score / 100;
	if (g_Reward.ef_score < 1)
		g_Reward.ef_score = 1;


	//ランクボーナスの計算
	if (re->quota <= g_Reward.rescue_num)
	{
		g_Reward.rank_bonus_time = 0;
		if (g_Reward.time <= 30 && RescueLife::GetRescueRemainLife() <= 0)
			g_Reward.rank_bonus_time += g_Reward.time / 2;
		if (g_Reward.time <= 60 && RescueLife::GetRescueRemainLife() <= 0)
			g_Reward.rank_bonus_time += g_Reward.time / 2;
		if (g_Reward.time <= 90 && RescueLife::GetRescueRemainLife() <= 0)
			g_Reward.rank_bonus_time += g_Reward.time / 2;

		g_Reward.rank_bonus_beat = g_Reward.beatNum / 10 * 5;
		g_Reward.rank_bonus_rescue = g_Reward.rescue_num * 2;
		g_Reward.rank_bonus_score += g_Reward.score / 3000 * 2;
	}
	else {
		g_Reward.rank_bonus_time = 0;
		g_Reward.rank_bonus_beat = 0;
		g_Reward.rank_bonus_rescue = -10;
		g_Reward.rank_bonus_score = 0;
	}
	//データの移し替え
	g_Reward.max_beatNum = g_Reward.beatNum;
	g_Reward.max_rescue_num = g_Reward.rescue_num;
	g_Reward.max_time = g_Reward.time;
	g_Reward.max_score = g_Reward.score;

	//表示用数値をリセット
	g_Reward.beatNum = 0;
	g_Reward.rescue_num = 0;
	g_Reward.time = 0;
	g_Reward.score = 0;
	//ランクアップ経験値の計算をここでする
	int num = 150;
	g_Reward.rank_up = g_Reward.rank_bonus_time + g_Reward.rank_bonus_beat + g_Reward.rank_bonus_rescue + g_Reward.rank_bonus_score + 20;
	g_Reward.base_rank = re->rank;
	g_Reward.increase_rank = 0;
	re->rank += g_Reward.rank_up;
}


Reward *GetReward(void) { return &g_Reward; };

//引数:表示したい数字、表示座標(x,y)、表示サイズ(x方向,y方向)
void DrawResultNumber(int numb, float px, float py, float sx, float sy, XMFLOAT4 color)
{
	int digit = 0;
	int clock = numb;
	if (clock != 0)
	{
		while (clock != 0)
		{
			clock /= 10;
			digit++;
		}
	}
	else
		digit = 1;

	float psx = px + sx * digit;
	for (int i = 0; i < digit; i++)
	{
		psx -= sx;
		float x = (float)(numb % 10);		//今回表示する数字
		float tx = x * 0.1f;			// テクスチャの左上X座標

		// テクスチャ設定
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Result[result_numb].g_Texture);

		// １枚のポリゴンの頂点とテクスチャ座標を設定
		SetSpriteColor(g_VertexBuffer, psx, py, sx, sy, tx, 0.0f, 0.1f, 1.0f,
			color);

		// ポリゴン描画
		GetDeviceContext()->Draw(4, 0);
		numb /= 10;
	}
}

//テクスチャ描画
void DrawResultTexture(Result* result)
{
	// テクスチャ設定
	GetDeviceContext()->PSSetShaderResources(0, 1, &result->g_Texture);

	// １枚のポリゴンの頂点とテクスチャ座標を設定
	SetSpriteColor(g_VertexBuffer, result->pos.x, result->pos.y, result->size.x, result->size.y, 0.0f, 0.0f, 1.0f, 1.0f,
		result->color);

	// ポリゴン描画
	GetDeviceContext()->Draw(4, 0);

//テクスチャ描画
}
void DrawResultGauge(Result* result, float tx)
{
	// テクスチャ設定
	GetDeviceContext()->PSSetShaderResources(0, 1, &result->g_Texture);

	// １枚のポリゴンの頂点とテクスチャ座標を設定
	SetSpriteColor(g_VertexBuffer, result->pos.x, result->pos.y, result->size.x, result->size.y, 0.0f, 0.0f, 1.0f, 1.0f,
		result->color);

	// ポリゴン描画
	GetDeviceContext()->Draw(4, 0);
}

void DrawResultTime(float px, float py, float sx, float sy, XMFLOAT4 color)
{
	int number = g_Reward.time;
	for (int i = 0; i < TIME_DIGIT; i++)
	{
		if (i != 1 && i != 2)	//十進数の処理
		{
			// テクスチャ設定
			GetDeviceContext()->PSSetShaderResources(0, 1, &g_Result[result_numb].g_Texture);
			// 今回表示する桁の数字
			float x = (float)(number % 10);

			// 制限時間の位置やテクスチャー座標を反映
			float p_x = px - sx * i;	// 制限時間の表示位置X
			float p_y = py;			// 制限時間の表示位置Y
			float p_w = sx;				// 制限時間の表示幅
			float p_h = sy;				// 制限時間の表示高さ

			float tw = 1.0f / 10;		// テクスチャの幅
			float th = 1.0f / 1;		// テクスチャの高さ
			float tx = x * tw;			// テクスチャの左上X座標
			float ty = 0.0f;			// テクスチャの左上Y座標

			// １枚のポリゴンの頂点とテクスチャ座標を設定
			SetSpriteColor(g_VertexBuffer, p_x, p_y, p_w, p_h, tx, ty, tw, th,
				color);

			// ポリゴン描画
			GetDeviceContext()->Draw(4, 0);

			// 次の桁へ
			number /= 10;

		}
		else if (i == 1)	//時間の二桁目のみ6進数なため、処理を分ける
		{
			// テクスチャ設定
			GetDeviceContext()->PSSetShaderResources(0, 1, &g_Result[result_numb].g_Texture);
			// 今回表示する桁の数字
			float x = (float)(number % 6);

			// 制限時間の位置やテクスチャー座標を反映
			float p_x = px - sx * i;	// 制限時間の表示位置X
			float p_y = py;			// 制限時間の表示位置Y
			float p_w = sx;				// 制限時間の表示幅
			float p_h = sy;				// 制限時間の表示高さ

			float tw = 1.0f / 10;		// テクスチャの幅
			float th = 1.0f / 1;		// テクスチャの高さ
			float tx = x * tw;			// テクスチャの左上X座標
			float ty = 0.0f;			// テクスチャの左上Y座標

			// １枚のポリゴンの頂点とテクスチャ座標を設定
			SetSpriteColor(g_VertexBuffer, p_x, p_y, p_w, p_h, tx, ty, tw, th,
				color);

			// ポリゴン描画
			GetDeviceContext()->Draw(4, 0);

			// 次の桁へ
			number /= 6;


		}
		else if (i == 2)
		{
			// テクスチャ設定
			GetDeviceContext()->PSSetShaderResources(0, 1, &g_Result[result_numb_cent].g_Texture);

			// 制限時間の位置やテクスチャー座標を反映
			float p_x = px - sx * i;	// 制限時間の表示位置X
			float p_y = py;			// 制限時間の表示位置Y
			float p_w = sx;				// 制限時間の表示幅
			float p_h = sy;				// 制限時間の表示高さ

			float tw = 1.0f;		// テクスチャの幅
			float th = 1.0f;		// テクスチャの高さ
			float tx = 0.0f;			// テクスチャの左上X座標
			float ty = 0.0f;			// テクスチャの左上Y座標

			// １枚のポリゴンの頂点とテクスチャ座標を設定
			SetSpriteColor(g_VertexBuffer, p_x, p_y, p_w, p_h, tx, ty, tw, th,
				XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));

			// ポリゴン描画
			GetDeviceContext()->Draw(4, 0);

		}
	}
}