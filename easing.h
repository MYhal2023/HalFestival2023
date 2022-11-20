#pragma once
#include "main.h"
#define MAX_EASE_DATA (20)
#define EASE_IN_PARA (1.1f)	//加速度
#define EASE_OUT_PARA (0.9f)	//減速度
class Easing
{
public:
	float pos;	//移動距離
	float dt;	//最高速度
	float spead;	//加速度
	float time;	//時間
	float dt_frame;	//加速フレーム数
	float ct_frame;	//カウントフレーム数
	float s_pos;	//始点
	float f_pos;	//終点
	BOOL use;	//使用中か
	float* p_f;		//ここに設定したい変数のアドレスをセット
	static void Init(void);
	static void Update(void);
	static int SetEase(float sx, float fx, float time);
	static float GetEase(int i);
};