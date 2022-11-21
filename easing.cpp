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

		//�K��t���[�����܂ł͉��Z�A�K��t���[���ɓ��B��������Z���~�߂�
		if (g_Ease[i].ct_frame < g_Ease[i].time) {
			g_Ease[i].pos += g_Ease[i].spead;

			//�ݒ肵���������t���[���ɍ��킹�đ��x��ω�������
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

//����:�n�_�A�I�_�A�ړ��t���[���� �߂�l:�z��Y����
int Easing::SetEase(float sx, float fx, float time)
{
	int ans = 99;
	for (int i = 0; i < MAX_EASE_DATA; i++)
	{
		if (g_Ease[i].use)continue;

		g_Ease[i].use = TRUE;
		g_Ease[i].s_pos = sx;
		g_Ease[i].f_pos = fx;
		g_Ease[i].pos = sx;		//���W���n�_�ɃZ�b�g
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

