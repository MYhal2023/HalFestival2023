#pragma once
#include "main.h"
#define MAX_OBSTACLE_POS	(30)
#define MAX_OBSTACLE_RAND_POS	(14)
#define MAX_RESCUE_RAND_POS	(30)
class Map
{
private:
	XMFLOAT3 set_pos[MAX_OBSTACLE_RAND_POS];
	BOOL use[MAX_OBSTACLE_RAND_POS];
	XMFLOAT3 set_res_pos[MAX_RESCUE_RAND_POS];
	BOOL use_res[MAX_RESCUE_RAND_POS];
public:
	static void InitMap(void);
	static void InitBootMap(void);
	static void InitMap001(void);
	static void InitBootMap001(void);
	static void InitReserveMap(void);
	static void InitResultMap(void);
};