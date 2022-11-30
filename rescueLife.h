#pragma once
#define MAX_RESCUE (30)
#define MODEL_VAR (3)
#define	MODEL_RESCUE001	"data/MODEL/helper1.obj"			// 読み込むモデル名
#include "main.h"
#include "model.h"

//人名救助者クラス
class RescueLife
{
public:
	XMFLOAT3			pos;
	XMFLOAT3			rot;
	XMFLOAT3			scl;		// ポリゴンの大きさ(スケール)

	XMFLOAT4X4			mtxWorld;	// ワールドマトリックス

	BOOL				load;
	XMFLOAT4			diffuse[MODEL_MAX_MATERIAL];	// モデルの色
	int					model_num;
	BOOL				use;		//救助者を使っているか否か
	BOOL				rescue;	//救助者を助けたか
public:
	static void InitRescue(void);
	static void InitBootRescue(void);
	static void UninitRescue(void);
	static void DrawRescue(void);
	static BOOL GetRescue(int i);
	static void SetRemain(XMFLOAT3 pos, XMFLOAT3 rot, int model);
	static RescueLife* GetRescueLife(void);
	static int GetRescueRemainLife(void);
};

int GetRemain(void);
