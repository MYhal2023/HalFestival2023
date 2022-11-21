#include "easing.h"

static Easing g_Ease[MAX_EASE_DATA];
void Easing::Init(void)
{
	for (int i = 0; i < MAX_EASE_DATA; i++)
	{
		g_Ease[i].pos = 0.0f;
		g_Ease[i].spead = 0.0f;
		g_Ease[i].dt = 0.0f;
		g_Ease[i].time = 0.0f;
		g_Ease[i].p_f = nullptr;
		g_Ease[i].use = FALSE;
	}
}

void Easing::Update(void)
{
	for (int i = 0; i < MAX_EASE_DATA; i++)
	{
		if (!g_Ease[i].use)continue;

		//規定フレーム数までは加算、規定フレームに到達したら加算を止める
		if (g_Ease[i].ct_frame < g_Ease[i].time) {
			g_Ease[i].pos += g_Ease[i].spead;

			//設定した加減速フレームに合わせて速度を変化させる
			if (g_Ease[i].dt_frame > g_Ease[i].ct_frame)
			{
				g_Ease[i].spead += g_Ease[i].dt;
			}
			else
			{
				g_Ease[i].spead -= g_Ease[i].dt;
			}

		}
		else
		{
			g_Ease[i].pos = g_Ease[i].f_pos;
		}

		g_Ease[i].ct_frame += 1.0f;
	}
}

//引数:始点、終点、移動フレーム数 戻り値:配列添え字
int Easing::SetEase(float sx, float fx, float time)
{
	int ans = 99;
	for (int i = 0; i < MAX_EASE_DATA; i++)
	{
		if (g_Ease[i].use)continue;

		g_Ease[i].use = TRUE;
		g_Ease[i].s_pos = sx;
		g_Ease[i].f_pos = fx;
		g_Ease[i].pos = sx;		//座標を始点にセット
		g_Ease[i].time = time;
		g_Ease[i].spead = 0.0f;
		g_Ease[i].dt = fabsf(fx - sx)*4 / (time * time);
		g_Ease[i].dt_frame = g_Ease[i].time * 0.5f;
		g_Ease[i].ct_frame = 0.0f;
		return i;
	}
	return ans;
}

float Easing::GetEase(int i)
{
	return g_Ease[i].pos;
}

