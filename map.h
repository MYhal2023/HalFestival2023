#pragma once
#include "main.h"
#define MAX_OBSTACLE_POS	(30)
#define MAX_OBSTACLE_RAND_POS	(14)
class Map
{
private:
	XMFLOAT3 set_pos[MAX_OBSTACLE_RAND_POS];
	BOOL use[MAX_OBSTACLE_RAND_POS];
public:
	static void InitMap(void);
	static void InitBootMap(void);
	static void InitReserveMap(void);
	static void InitResultMap(void);
};