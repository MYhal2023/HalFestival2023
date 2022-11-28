//=============================================================================
//
// パーティクル処理 [particle.h]
// Author : 
//
//=============================================================================
#pragma once
enum PARTICLE_TEX
{
	P_T_circle,
	P_T_box,
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitParticle(void);
void UninitParticle(void);
void UpdateParticle(void);
void DrawParticle(void);

int SetParticle(XMFLOAT3 pos, XMFLOAT3 move, XMFLOAT3 rot, XMFLOAT3 scl, XMFLOAT4 col, int nLife, int nDecay, int texNo, BOOL blend); void SetColorParticle(int nIdxParticle, XMFLOAT4 col);

