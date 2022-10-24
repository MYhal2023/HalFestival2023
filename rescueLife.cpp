#include "rescueLife.h"

static RescueLife g_RscLife;

void RescueLife::InitRescue(void)
{
	for (int i = 0; i < MAX_RESCUE; i++)
	{
		g_RscLife.use[i] = false;
		g_RscLife.rescue[i] = false;
	}
}

int RescueLife::GetRemain(void)
{
	return g_RscLife.remain;
}

bool RescueLife::GetRescue(int i)
{
	return g_RscLife.rescue[i];
}

//�~���҃Z�b�g�B�擪�z�񂩂�g�p���Ă���
void RescueLife::SetRemain(int i)
{
	g_RscLife.remain = i;
	for (int k = 0; k < i; k++)
	{
		g_RscLife.use[k] = true;
		//g_RscLife.rescue[k] = true;
	}
}

RescueLife * RescueLife::GetRescueLife(void)
{
	return &g_RscLife;
}
