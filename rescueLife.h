#pragma once
#define MAX_RESCUE (10)
#define	MODEL_RESCUE001	"data/MODEL/neutrophils.obj"			// 読み込むモデル名
#include "main.h"
#include "model.h"

//人名救助者クラス
class RescueLife
{
private:
	XMFLOAT3			pos;
	XMFLOAT3			rot;
	XMFLOAT3			scl;		// ポリゴンの大きさ(スケール)

	XMFLOAT4X4			mtxWorld;	// ワールドマトリックス

	BOOL				load;
	DX11_MODEL			model;		// モデル情報
	XMFLOAT4			diffuse[MODEL_MAX_MATERIAL];	// モデルの色

	BOOL				use;		//救助者を使っているか否か
	BOOL				rescue;	//救助者を助けたか
public:
	static void InitRescue(void);
	static void UninitRescue(void);
	static void DrawRescue(void);
	static BOOL GetRescue(int i);
	static void SetRemain(XMFLOAT3 pos, XMFLOAT3 rot, char* model);
	static RescueLife* GetRescueLife(void);
};

int GetRemain(void);
