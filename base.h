//=============================================================================
//
// ���_���C�t���� [base.cpp]
// Author : 
//
//=============================================================================
#pragma once
#include "debugproc.h"
#include "player.h"
#include "enemy.h"
#define MAX_BASE (2)

struct Base
{
	int life;	//���_���C�t
	int baseNum;
	XMFLOAT3 pos[MAX_BASE];	//���_��������W�B�������邩������Ȃ�����A�����͉ϒ��z��
};

HRESULT InitBase(int life, XMFLOAT3 pos[], int baseNum);
int GetBaseLife(void);
Base *GetBase(void);