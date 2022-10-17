//=============================================================================
//
// �R�X�g���� [cost.cpp]
// Author : 
//
//=============================================================================
#include "cost.h"
#include "debugproc.h"
static Cost g_Cost;

//�R�X�g�Ɋւ���ϐ�������
void InitCost(void)
{
	g_Cost.cost = 10;
	g_Cost.time = 0;
	g_Cost.costMaxTime = 120;

}

void SetCost(int i)
{
	g_Cost.cost = i;
#ifdef _DEBUG
	g_Cost.cost = 90;
#endif
}
//�R�X�g����C�ɑ��₵��������
void IncreaseCost(int increase)
{
	g_Cost.cost += increase;
}

int GetCost(void)
{
	return g_Cost.cost;
}

//�R�X�g�����炵�������ɁB��Ƀ��j�b�g��u�������Ɏg������
void DecreaseCost(int decrease)
{
	g_Cost.cost -= decrease;
}

//���Ԍo�߂ŃR�X�g��������悤�ɂ���
void IncTimeCost(void)
{
	g_Cost.time++;
	if (g_Cost.time >= g_Cost.costMaxTime)
	{
		g_Cost.time = 0;
		IncreaseCost(1);
	}
}

Cost *GetCostNum(void)
{
	return &g_Cost;
}