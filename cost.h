//=============================================================================
//
// �R�X�g���� [cost.h]
// Author : 
//
//=============================================================================
#pragma once
#define MAX_COST (99)
struct Cost
{
	int cost;
	int time;
	int costMaxTime;
};
void InitCost(void);		//�C�j�V�����C�U
void SetCost(int i);
void IncreaseCost(int increase);	//�R�X�g�𑝂₷�֐�
int GetCost(void);					//���݂̃R�X�g�������Ȃ̂�
void DecreaseCost(int decrease);	//�R�X�g�����炷�֐�
void IncTimeCost(void);
Cost* GetCostNum(void);
