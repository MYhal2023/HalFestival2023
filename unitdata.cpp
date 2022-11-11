//=============================================================================
//
// ���j�b�g���ʏ��� [unitdata.cpp]
// Author : 
//
//=============================================================================

#include "unitdata.h"
#define ALPHA_SPEED (0.02f)
static UnitFade g_UnitFade[MAX_BATTLE_MODEL];
void InitCharFade(void){
	for (int i = 0; i < MAX_BATTLE_MODEL; i++)
	{
		g_UnitFade[i].alpha = 0.0f;
		g_UnitFade[i].use = FALSE;
		g_UnitFade[i].character = NULL;
		g_UnitFade[i].type = 0;
	}
}

void UpdateCharFade(void)
{
	for (int i = 0; i < MAX_BATTLE_MODEL; i++)
	{
		if (!g_UnitFade[i].use)continue;

		if (g_UnitFade[i].type == 0)	//�t�F�[�h�C��
		{
			g_UnitFade[i].alpha += ALPHA_SPEED;
			if (g_UnitFade[i].alpha > 1.0f)
			{
				g_UnitFade[i].use = FALSE;
			}

		}
		else if (g_UnitFade[i].type == 1)	//�t�F�[�h�A�E�g
		{
			g_UnitFade[i].alpha -= ALPHA_SPEED;
			if (g_UnitFade[i].alpha <= 0.5f)
			{
				g_UnitFade[i].use = FALSE;
			}
		}

		//�����ŃL�����N�^�[���f���̃��l��M��
		for (int j = 0; j < g_UnitFade[i].character->SubsetNum; j++)
			SetModelDiffuse(g_UnitFade[i].character, j, XMFLOAT4(1.0f, 1.0f, 1.0f, g_UnitFade[i].alpha));
	}
}
//�Y�����������Ɏ����Ă���Btype = 0�Ńt�F�[�h�C���A1�Ńt�F�[�h�A�E�g
void FadeCharacter(DX11_MODEL *character, int type)
{
	for (int i = 0; i < MAX_BATTLE_MODEL; i++)
	{
		if (g_UnitFade[i].use != FALSE)continue;
		if (type == 0)
		{
			g_UnitFade[i].use = TRUE;
			g_UnitFade[i].character = character;
			g_UnitFade[i].type = type;
			g_UnitFade[i].alpha = 0.5f;
		}
		else if (type == 1)
		{
			g_UnitFade[i].use = TRUE;
			g_UnitFade[i].character = character;
			g_UnitFade[i].type = type;
			g_UnitFade[i].alpha = 1.0f;
		}
		return;
	}
}
