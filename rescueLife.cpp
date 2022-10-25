#include "rescueLife.h"

static RescueLife g_RscLife[MAX_RESCUE];
static int remain;					//�c��~���Ґ�

void RescueLife::InitRescue(void)
{
	for (int i = 0; i < MAX_RESCUE; i++)
	{
		g_RscLife[i].use = FALSE;
		g_RscLife[i].rescue = FALSE;
	}
	remain = 0;
}

int GetRemain(void)
{
	return remain;
}

BOOL RescueLife::GetRescue(int i)
{
	return g_RscLife[i].rescue;
}

//�~���҃Z�b�g�B�擪�z�񂩂�g�p���Ă���
void RescueLife::SetRemain(int i)
{
	remain = i;
	for (int k = 0; k < i; k++)
	{
		g_RscLife[k].use = TRUE;
		g_RscLife[k].rescue = TRUE;
	}
}

RescueLife * RescueLife::GetRescueLife(void)
{
	return &g_RscLife[0];
}
