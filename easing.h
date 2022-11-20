#pragma once
#include "main.h"
#define MAX_EASE_DATA (20)
#define EASE_IN_PARA (1.1f)	//�����x
#define EASE_OUT_PARA (0.9f)	//�����x
class Easing
{
public:
	float pos;	//�ړ�����
	float dt;	//�ō����x
	float spead;	//�����x
	float time;	//����
	float dt_frame;	//�����t���[����
	float ct_frame;	//�J�E���g�t���[����
	float s_pos;	//�n�_
	float f_pos;	//�I�_
	BOOL use;	//�g�p����
	float* p_f;		//�����ɐݒ肵�����ϐ��̃A�h���X���Z�b�g
	static void Init(void);
	static void Update(void);
	static int SetEase(float sx, float fx, float time);
	static float GetEase(int i);
};