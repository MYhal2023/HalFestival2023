#include "playerArms.h"
#include "IPArmData.h"
#include "debugproc.h"
#include "input.h"
#include <iostream>
#include <fstream>

using namespace std;
#define MAX_ARM (2)
#define MOVE_VALUE	(0.05f)
static pArm g_PlayerArm[2];
static pArm g_ArmParts[MAX_ARM_PARTS * 2];
static pArm g_ArmWeapon[ARM_VAR + 1];
static ofstream fout;
static float etc = 1.0f;
static BOOL flag = TRUE;
static BOOL change = FALSE;
static int ct_interval = 0;
void pArm::InitArm(void)
{
	for (int i = 0; i < MAX_ARM; i++)
	{
		g_PlayerArm[i].use = TRUE;
		g_PlayerArm[i].pos = { 0.0f, 0.0f, 0.0f };
		g_PlayerArm[i].rot = { 0.0f, 0.0f, 0.0f };
		g_PlayerArm[i].scl = { 1.0f, 1.0f, 1.0f };
		g_PlayerArm[i].partsNum = MAX_ARM_PARTS;
	}

	for (int i = 0; i < MAX_ARM_PARTS ; i++)
	{
		g_ArmParts[i].use = TRUE;

		//0はプレイヤーモデルを親としているため、別途設定
		if (i == 0) {
			g_ArmParts[i].pos = { -5.0f, 0.0f, -5.0f };
			g_ArmParts[i].rot = { XM_PI * 0.0f , 0.0f, XM_PI * 0.5f };
			g_ArmParts[i].scl = { 1.0f, 1.0f, 1.0f };
		}
		else {
			g_ArmParts[i].pos = { 0.0f, 0.0f, 0.0f };
			g_ArmParts[i].rot = { 0.0f, 0.0f,0.0f };
			g_ArmParts[i].scl = { 1.0f, 1.0f, 1.0f };
		}
	}

	for (int i = MAX_ARM_PARTS; i < MAX_ARM_PARTS * 2; i++)
	{
		g_ArmParts[i].use = TRUE;

		if (i == MAX_ARM_PARTS) {
			g_ArmParts[i].pos = { -5.0f, 0.0f, 5.0f };
			g_ArmParts[i].rot = { XM_PI * 0.0f, 0.0f, XM_PI * 0.5f };
			g_ArmParts[i].scl = { 1.0f, 1.0f, 1.0f };
		}
		else {
			g_ArmParts[i].pos = { 0.0f, 0.0f, 0.0f };
			g_ArmParts[i].rot = { 0.0f, 0.0f, 0.0f };
			g_ArmParts[i].scl = { 1.0f, 1.0f, 1.0f };
		}

		g_ArmParts[i].tbl_adrXgun = NULL;
		g_ArmParts[i].tbl_adr = nullptr;
		g_ArmParts[i].move_time = 0.0f;
		g_ArmParts[i].spead = 0.0f;
		g_ArmParts[i].ct_frame = 0.0f;
	}

	Xgun::InitArm();
	Braster::InitArm();
	Saw::InitArm();
	ofstream fout;

}

void pArm::UninitArm(void)
{
	for (int i = 0; i < MAX_ARM_PARTS * 2; i++)
	{
		// モデルの解放処理
		UnloadModel(&g_ArmParts[i].model);
	}

	for (int i = 0; i < 4; i++)
	{
		UnloadModel(&g_ArmWeapon[i].model);
	}
	fout.close();
}

void pArm::InitArmBoot(void)
{
	for (int i = 0; i < MAX_ARM_PARTS; i++)
	{
		//添え字によって、腕の先端部分かそうでないかを判断
		if (i == MAX_ARM_PARTS - 1)
			LoadModel(MODEL_ARM_PARTS, &g_ArmParts[i].model);
		else
			LoadModel(MODEL_ARM_PARTS, &g_ArmParts[i].model);
	}
	for (int i = MAX_ARM_PARTS; i < MAX_ARM_PARTS * 2; i++)
	{
		//添え字によって、腕の先端部分かそうでないかを判断
		if (i == MAX_ARM_PARTS * 2 - 1)
			LoadModel(MODEL_ARM_PARTS, &g_ArmParts[i].model);
		else
			LoadModel(MODEL_ARM_PARTS, &g_ArmParts[i].model);
	}
	LoadModel(MODEL_XGUN, &g_ArmWeapon[0].model);
	LoadModel(MODEL_BRASTER, &g_ArmWeapon[1].model);
	LoadModel(MODEL_SAW, &g_ArmWeapon[2].model);
	LoadModel(MODEL_ARM_SAW_BLADE, &g_ArmWeapon[3].model);
	fout.open("m_data.txt");
}

//player.cppのUpdateArm()関数に入れる
void pArm::UpdateArm(void)
{
	XMFLOAT3 pos{ 0.0f, 0.0f, 0.0f };
	XMFLOAT3 rot{0.0f, 0.0f, 0.0f};
	//片腕ずつ処理(根本部分は除外)
	//左腕
	if (GetKeyboardPress(DIK_1))
	{
		pos.x += 0.05f * etc;
	}
	else if (GetKeyboardPress(DIK_2))
	{
		pos.y += 0.05f * etc;
	}
	else if (GetKeyboardPress(DIK_3))
	{
		pos.z += XM_PI * 0.001f * etc;
	}
	if (GetKeyboardPress(DIK_4))
	{
		rot.x += XM_PI * 0.001f * etc;
	}
	else if (GetKeyboardPress(DIK_5))
	{
		rot.y += XM_PI * 0.001f * etc;
	}
	else if (GetKeyboardPress(DIK_6))
	{
		rot.z += XM_PI * 0.001f * etc;
	}
	else if (IsMouseLeftTriggered() || GetKeyboardTrigger(DIK_J))
	{
		etc *= -1;
	}
	else if (GetKeyboardTrigger(DIK_K) || IsMouseRightTriggered())
	{
		if (flag)flag = FALSE;
		else flag = TRUE;
	}
	else if (GetKeyboardTrigger(DIK_M))
	{
		if (change)change = FALSE;
		else change = TRUE;
	}
	else if (GetKeyboardTrigger(DIK_RETURN))
	{
		fout << "{ XMFLOAT3(" <<g_ArmParts[1].pos.x << ", " << g_ArmParts[1].pos.y << ", " << g_ArmParts[1].pos.z << "),";
		fout << "XMFLOAT3(" << g_ArmParts[1].rot.x << ", " << g_ArmParts[1].rot.y << ", " << g_ArmParts[1].rot.z << ") , XMFLOAT3(1.0f, 1.0f, 1.0f), 60, EASING }," << endl << endl;
		fout << "{ XMFLOAT3(" << g_ArmParts[6].pos.x << ", " << g_ArmParts[6].pos.y << ", " << g_ArmParts[6].pos.z << "),";
		fout << "XMFLOAT3(" << g_ArmParts[6].rot.x << ", " << g_ArmParts[6].rot.y << ", " << g_ArmParts[6].rot.z << ") , XMFLOAT3(1.0f, 1.0f, 1.0f), 60, EASING }," << endl << endl;
		fout << "{ XMFLOAT3(" << g_ArmParts[11].pos.x << ", " << g_ArmParts[11].pos.y << ", " << g_ArmParts[11].pos.z <<"),";
		fout << "XMFLOAT3(" << g_ArmParts[11].rot.x << ", " << g_ArmParts[11].rot.y << ", " << g_ArmParts[11].rot.z << ") , XMFLOAT3(1.0f, 1.0f, 1.0f), 60, EASING }," << endl << endl;
		fout << "{ XMFLOAT3(" << g_ArmParts[16].pos.x << ", " << g_ArmParts[16].pos.y << ", " << g_ArmParts[16].pos.z << "),";
		fout << "XMFLOAT3(" << g_ArmParts[16].rot.x << ", " << g_ArmParts[16].rot.y << ", " << g_ArmParts[16].rot.z << ") , XMFLOAT3(1.0f, 1.0f, 1.0f), 60, EASING }," << endl << endl<<endl;
	}


	if (!change) {
		for (int i = 1; i < MAX_ARM_PARTS; i++)
		{
			if (i < MAX_ARM_PARTS / 2) {	//下半分のモーション
				//g_ArmParts[i].tbl_sizeA = tblsize[M_AttackArmSawL001];
				//IPArm(&g_ArmParts[i], AttackArmSawLeft001);
				if (flag)
				{
					g_ArmParts[i].pos.x += pos.x;
					g_ArmParts[i].pos.y += pos.y;
					g_ArmParts[i].pos.z += pos.z;
					g_ArmParts[i].rot.x += rot.x;
					g_ArmParts[i].rot.y += rot.y;
					g_ArmParts[i].rot.z += rot.z;
					if (GetKeyboardTrigger(DIK_B))
					{
						g_ArmParts[i].pos = { 0.0f, 0.0f, 0.0f };
						g_ArmParts[i].rot = { 0.0f, 0.0f, 0.0f };
					}
				}
			}
			else if (i >= MAX_ARM_PARTS / 2)	//上半分のモーション
			{
				//g_ArmParts[i].tbl_sizeA = tblsize[M_AttackArmSawL002];
				//IPArm(&g_ArmParts[i], AttackArmSawLeft002);
				if (!flag)
				{
					g_ArmParts[i].pos.x += pos.x;
					g_ArmParts[i].pos.y += pos.y;
					g_ArmParts[i].pos.z += pos.z;
					g_ArmParts[i].rot.x += rot.x;
					g_ArmParts[i].rot.y += rot.y;
					g_ArmParts[i].rot.z += rot.z;
					if (GetKeyboardTrigger(DIK_B))
					{
						g_ArmParts[i].pos = { 0.0f, 0.0f, 0.0f };
						g_ArmParts[i].rot = { 0.0f, 0.0f, 0.0f };
					}
				}

			}
		}
	}
	else if (change) 
	{
		//右腕
		for (int i = MAX_ARM_PARTS + 1; i < MAX_ARM_PARTS * 2; i++)
		{
			if (i < (MAX_ARM_PARTS + 1) + MAX_ARM_PARTS / 2) {
				//g_ArmParts[i].tbl_sizeA = tblsize[M_AttackArmSawL001];
				//IPArm(&g_ArmParts[i], AttackArmSawLeft001);
				if (flag)
				{
					g_ArmParts[i].pos.x += pos.x;
					g_ArmParts[i].pos.y += pos.y;
					g_ArmParts[i].pos.z += pos.z;
					g_ArmParts[i].rot.x += rot.x;
					g_ArmParts[i].rot.y += rot.y;
					g_ArmParts[i].rot.z += rot.z;
					if (GetKeyboardTrigger(DIK_B))
					{
						g_ArmParts[i].pos = { 0.0f, 0.0f, 0.0f };
						g_ArmParts[i].rot = { 0.0f, 0.0f, 0.0f };
					}

				}
			}
			else if (i >= (MAX_ARM_PARTS + 1) + MAX_ARM_PARTS / 2)
			{
				//g_ArmParts[i].tbl_sizeA = tblsize[M_AttackArmSawL002];
				//IPArm(&g_ArmParts[i], AttackArmSawLeft002);
				if (!flag)
				{
					g_ArmParts[i].pos.x += pos.x;
					g_ArmParts[i].pos.y += pos.y;
					g_ArmParts[i].pos.z += pos.z;
					g_ArmParts[i].rot.x += rot.x;
					g_ArmParts[i].rot.y += rot.y;
					g_ArmParts[i].rot.z += rot.z;
					if (GetKeyboardTrigger(DIK_B))
					{
						g_ArmParts[i].pos = { 0.0f, 0.0f, 0.0f };
						g_ArmParts[i].rot = { 0.0f, 0.0f, 0.0f };
					}
				}
			}
		}
	}
	PrintDebugProc("アーム座標:%f\n", g_ArmParts[MAX_ARM_PARTS - 1]);
}

void pArm::UpdateReleaseArm(void)
{
	PLAYER *player = GetPlayer();
	//0:Xgun,1:Braster,3:Saw
	if (player[0].attack) {
		switch (player[0].armType)
		{
		case 0:
			UpdateXgunArm();
			break;
		case 1:
			UpdateBrasterArm();
			break;
		case 2:
			//UpdateSawArm();
			UpdateSawArmSecond();
			break;
		}
	}
	else
	{
		UpdateWaitArm();
	}
}

void pArm::UpdateXgunArm(void)
{
	for (int i = 1; i < MAX_ARM_PARTS; i++)
	{
		if (i < MAX_ARM_PARTS / 2)
		{	//下半分のモーション
			g_ArmParts[i].tbl_sizeA = tblsize[M_AttackArmXgunL001];
			IPArm(&g_ArmParts[i], AttackArmXgunLeft001);
		}
		else if (i >= MAX_ARM_PARTS / 2)	//上半分のモーション
		{
			g_ArmParts[i].tbl_sizeA = tblsize[M_AttackArmXgunL002];
			IPArm(&g_ArmParts[i], AttackArmXgunLeft002);
		}
	}

	//右腕
	for (int i = MAX_ARM_PARTS + 1; i < MAX_ARM_PARTS * 2; i++)
	{
		if (i < (MAX_ARM_PARTS + 1) + MAX_ARM_PARTS / 2) {
			g_ArmParts[i].tbl_sizeA = tblsize[M_AttackArmXgunR001];
			IPArm(&g_ArmParts[i], AttackArmXgunRight001);
		}
		else if (i >= (MAX_ARM_PARTS + 1) + MAX_ARM_PARTS / 2)
		{
			g_ArmParts[i].tbl_sizeA = tblsize[M_AttackArmXgunR002];
			IPArm(&g_ArmParts[i], AttackArmXgunRight002);

		}
	}

}

void pArm::UpdateBrasterArm(void)
{
	for (int i = 1; i < MAX_ARM_PARTS; i++)
	{
		if (i < MAX_ARM_PARTS / 2)
		{	//下半分のモーション
			g_ArmParts[i].tbl_sizeA = tblsize[M_AttackArmBrasterL001];
			IPArm(&g_ArmParts[i], AttackArmBrasterLeft001);
		}
		else if (i >= MAX_ARM_PARTS / 2)	//上半分のモーション
		{
			g_ArmParts[i].tbl_sizeA = tblsize[M_AttackArmBrasterL002];
			IPArm(&g_ArmParts[i], AttackArmBrasterLeft002);
		}
	}

	//右腕
	for (int i = MAX_ARM_PARTS + 1; i < MAX_ARM_PARTS * 2; i++)
	{
		if (i < (MAX_ARM_PARTS + 1) + MAX_ARM_PARTS / 2) {
			g_ArmParts[i].tbl_sizeA = tblsize[M_AttackArmBrasterR001];
			IPArm(&g_ArmParts[i], AttackArmBrasterRight001);
		}
		else if (i >= (MAX_ARM_PARTS + 1) + MAX_ARM_PARTS / 2)
		{
			g_ArmParts[i].tbl_sizeA = tblsize[M_AttackArmBrasterR002];
			IPArm(&g_ArmParts[i], AttackArmBrasterRight002);

		}
	}

}

void pArm::UpdateSawArm(void)
{
	for (int i = 1; i < MAX_ARM_PARTS; i++)
	{
		if (i < MAX_ARM_PARTS / 2)
		{	//下半分のモーション
			g_ArmParts[i].tbl_sizeA = tblsize[M_AttackArmSawL001];
			IPArm(&g_ArmParts[i], AttackArmSawLeft001);
		}
		else if (i >= MAX_ARM_PARTS / 2)	//上半分のモーション
		{
			g_ArmParts[i].tbl_sizeA = tblsize[M_AttackArmSawL002];
			IPArm(&g_ArmParts[i], AttackArmSawLeft002);
		}
	}

	//右腕
	for (int i = MAX_ARM_PARTS + 1; i < MAX_ARM_PARTS * 2; i++)
	{
		if (i < (MAX_ARM_PARTS + 1) + MAX_ARM_PARTS / 2) {
			g_ArmParts[i].tbl_sizeA = tblsize[M_AttackArmSawR001];
			IPArm(&g_ArmParts[i], AttackArmSawRight001);
		}
		else if (i >= (MAX_ARM_PARTS + 1) + MAX_ARM_PARTS / 2)
		{
			g_ArmParts[i].tbl_sizeA = tblsize[M_AttackArmSawR002];
			IPArm(&g_ArmParts[i], AttackArmSawRight002);

		}
	}
}

void pArm::UpdateSawArmSecond(void)
{
	if (ct_interval < 5)
		ct_interval++;
	if (ct_interval < 5)return;

	for (int i = 1; i < MAX_ARM_PARTS; i++)
	{
		if (i < MAX_ARM_PARTS / 2)
		{	//下半分のモーション
			g_ArmParts[i].tbl_sizeA = tblsize[M_AttackArmSawL101];
			IPArm(&g_ArmParts[i], AttackArmSawLeft101);
		}
		else if (i >= MAX_ARM_PARTS / 2)	//上半分のモーション
		{
			g_ArmParts[i].tbl_sizeA = tblsize[M_AttackArmSawL102];
			IPArm(&g_ArmParts[i], AttackArmSawLeft102);
		}
	}

	//右腕
	for (int i = MAX_ARM_PARTS + 1; i < MAX_ARM_PARTS * 2; i++)
	{
		if (i < (MAX_ARM_PARTS + 1) + MAX_ARM_PARTS / 2) {
			g_ArmParts[i].tbl_sizeA = tblsize[M_AttackArmSawR101];
			IPArm(&g_ArmParts[i], AttackArmSawRight101);
		}
		else if (i >= (MAX_ARM_PARTS + 1) + MAX_ARM_PARTS / 2)
		{
			g_ArmParts[i].tbl_sizeA = tblsize[M_AttackArmSawR102];
			IPArm(&g_ArmParts[i], AttackArmSawRight102);

		}
	}
}

void pArm::UpdateWaitArm(void)
{
	for (int i = 1; i < MAX_ARM_PARTS; i++)
	{
		if (i < MAX_ARM_PARTS / 2)
		{	//下半分のモーション
			g_ArmParts[i].tbl_sizeA = tblsize[M_wait_armL01];
			IPArm(&g_ArmParts[i], wait_armLeft001);
		}
		else if (i >= MAX_ARM_PARTS / 2)	//上半分のモーション
		{
			g_ArmParts[i].tbl_sizeA = tblsize[M_wait_armL02];
			IPArm(&g_ArmParts[i], wait_armLeft002);
		}
	}

	//右腕
	for (int i = MAX_ARM_PARTS + 1; i < MAX_ARM_PARTS * 2; i++)
	{
		if (i < (MAX_ARM_PARTS + 1) + MAX_ARM_PARTS / 2) {
			g_ArmParts[i].tbl_sizeA = tblsize[M_wait_armR01];
			IPArm(&g_ArmParts[i], wait_armRight001);
		}
		else if (i >= (MAX_ARM_PARTS + 1) + MAX_ARM_PARTS / 2)
		{
			g_ArmParts[i].tbl_sizeA = tblsize[M_wait_armR02];
			IPArm(&g_ArmParts[i], wait_armRight002);

		}
	}
}

INTERPOLATION_DATA * pArm::CheckMotionData(PLAYER *p)
{
	return nullptr;
}


void pArm::IPArm(pArm* p, INTERPOLATION_DATA_EASING* i)
{
//
// 線形補間の処理
// 移動処理
	int		index = (int)p->move_time;
	float	time = p->move_time - index;
	int		size = p->tbl_sizeA;
	p->ct_frame += 1.0f;

	if(p->move_time == 0.0f && i[index].ease_mode == EASE_OUT)
		p->spead = (1.0f + 0.5f * 1.0f * 4) / i[index].frame;

	float dt = 0.0f;
	//運動方法によって速度に加速力を与える
	switch (i[index].ease_mode) {
	case EASE_IN:
		dt = 1.0f * 4.0f /(i[index].frame * i[index].frame);
		p->spead += dt;

		break;
	case EASE_OUT:
		dt = (1.0f * 4) / (i[index].frame*i[index].frame);
		p->spead -= dt;


		break;
	case EASING:
		dt = (1.0f * 4) / (i[index].frame * i[index].frame);
		if (i[index].frame * 0.5f >= p->ct_frame)
			p->spead += dt;
		else
			p->spead -= dt;

		break;
	case NON_EASE:
		dt = 1.0f / i[index].frame;
		p->spead = dt;

		break;

		//Ease-out
	}

	p->move_time += p->spead;							// アニメーションの合計時間に足す

	if(i[index].frame <= p->ct_frame)p->move_time = 1.0f * (float)(index + 1);

	//テーブル遷移時に各変数を初期化、初速は次のイージングによって決める
	if (index < (int)(p->move_time))
	{
		p->move_time = 1.0f * (float)(index+1);
		p->ct_frame = 0.0f;
		//減速のみ初速を与えなければいけない
		switch (i[index + 1].ease_mode) {
		case EASE_OUT:
			p->spead = (1.0f + 0.5f * 1.0f * 4) / i[index + 1].frame;
			break;
		case EASE_IN:
		case EASING:
		case NON_EASE:
			p->spead = 0.0f;
			break;
		}
	}

	if (index > (size - 2))	// ゴールをオーバーしていたら、データを最初に戻して終了
	{
		PLAYER *player = GetPlayer();
		player[0].attack = FALSE;
		player[0].attack_num = 0;
		pArm* pab = Braster::GetArm();
		pArm* pax = Xgun::GetArm();
		pArm* pas = Saw::GetArm();
		p->move_time = 0.0f;
		p->spead = 0.0f;
		p->ct_frame = 0.0f;
		pab->attack = FALSE;
		pax->attack = FALSE;
		pas->attack = FALSE;
		pas->ct_frame = 0.0f;
		index = 0;
	}
	// 座標を求める	X = StartX + (EndX - StartX) * 今の時間
	XMVECTOR p1 = XMLoadFloat3(&i[index + 1].pos);	// 次の場所
	XMVECTOR p0 = XMLoadFloat3(&i[index + 0].pos);	// 現在の場所
	XMVECTOR vec = p1 - p0;
	XMStoreFloat3(&p->pos, p0 + vec * time);

	// 回転を求める	R = StartX + (EndX - StartX) * 今の時間
	XMVECTOR r1 = XMLoadFloat3(&i[index + 1].rot);	// 次の角度
	XMVECTOR r0 = XMLoadFloat3(&i[index + 0].rot);	// 現在の角度
	XMVECTOR rot = r1 - r0;
	XMStoreFloat3(&p->rot, r0 + rot * time);

	// scaleを求める S = StartX + (EndX - StartX) * 今の時間
	XMVECTOR s1 = XMLoadFloat3(&i[index + 1].scl);	// 次のScale
	XMVECTOR s0 = XMLoadFloat3(&i[index + 0].scl);	// 現在のScale
	XMVECTOR scl = s1 - s0;
	XMStoreFloat3(&p->scl, s0 + scl * time);

}

void pArm::SetIntervalAt(void)
{
	ct_interval = 0;
}

void pArm::Draw(void)
{
	// カリング無効
	SetCullingMode(CULL_MODE_NONE);

	XMMATRIX mtxScl, mtxRot, mtxTranslate, mtxWorld;

	// パーツの階層アニメーション
	for (int k = 0; k < MAX_ARM_PARTS * 2; k++)
	{
		// ワールドマトリックスの初期化
		mtxWorld = XMMatrixIdentity();

		// スケールを反映
		mtxScl = XMMatrixScaling(g_ArmParts[k].scl.x, g_ArmParts[k].scl.y, g_ArmParts[k].scl.z);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxScl);

		// 回転を反映
		mtxRot = XMMatrixRotationRollPitchYaw(g_ArmParts[k].rot.x, g_ArmParts[k].rot.y, g_ArmParts[k].rot.z);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxRot);

		// 移動を反映
		mtxTranslate = XMMatrixTranslation(g_ArmParts[k].pos.x, g_ArmParts[k].pos.y, g_ArmParts[k].pos.z);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxTranslate);

		//親情報があるなら接続
		if (g_ArmParts[k].player != nullptr && g_ArmParts[k].parent == nullptr)
		{
			mtxWorld = XMMatrixMultiply(mtxWorld, XMLoadFloat4x4(&g_ArmParts[k].player->mtxWorld));
		}
		else if (g_ArmParts[k].parent != nullptr)	// 子供だったら親と結合する
		{
			mtxWorld = XMMatrixMultiply(mtxWorld, XMLoadFloat4x4(&g_ArmParts[k].parent->mtxWorld));
		}

		XMStoreFloat4x4(&g_ArmParts[k].mtxWorld, mtxWorld);

		// 使われているなら処理する。ここまで処理している理由は他のパーツがこのパーツを参照している可能性があるから。
		if (g_ArmParts[k].use == FALSE) continue;

		// ワールドマトリックスの設定
		SetWorldMatrix(&mtxWorld);

		//モデル描画
		//先端部分に来た時のみ、武器別にモデルを描画
		if (k == MAX_ARM_PARTS - 1 || k == MAX_ARM_PARTS * 2 - 1) {
			PLAYER *player = GetPlayer();
			switch (player[0].armType)
			{
			case 0:
				DrawModel(&g_ArmWeapon[0].model);
				break;
			case 1:
				DrawModel(&g_ArmWeapon[1].model);
				break;
			case 2:
				DrawModel(&g_ArmWeapon[2].model);
				DrawModel(&g_ArmWeapon[3].model);
				break;
			}
		}
		else
		{
			DrawModel(&g_ArmParts[k].model);
		}
	}

	// カリング設定を戻す
	SetCullingMode(CULL_MODE_BACK);

}

//使うアームの親子情報を一括でセット
void pArm::SetArmParent(PLAYER *p)
{
	//左腕
	for (int k = 0; k < MAX_ARM_PARTS; k++)
	{
		if (k == 0) {
			g_ArmParts[k].parent = nullptr;
			g_ArmParts[k].player = p;
		}
		else {	//先頭をプレイヤーの親とし、これに順番に紐づけていく
			g_ArmParts[k].player = nullptr;
			g_ArmParts[k].parent = &g_ArmParts[k - 1];
		}
	}
	//右腕
	for (int k = MAX_ARM_PARTS; k < MAX_ARM_PARTS * 2; k++)
	{
		if (k == MAX_ARM_PARTS) {
			g_ArmParts[k].parent = nullptr;
			g_ArmParts[k].player = p;
		}	//先頭をプレイヤーの親とし、これに順番に紐づけていく
		else {
			g_ArmParts[k].player = nullptr;
			g_ArmParts[k].parent = &g_ArmParts[k - 1];
		}
	}
}

pArm* pArm::GetArm(void)
{
	return &g_PlayerArm[0];
}

pArm* pArm::GetArmParts(void)
{
	return &g_ArmParts[0];	
}
