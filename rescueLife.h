#pragma once
#define MAX_RESCUE (10)

class RescueLife
{
private:
	int remain;					//�c��~���Ґ�
	bool use[MAX_RESCUE];		//�~���҂��g���Ă��邩�ۂ�
	bool rescue[MAX_RESCUE];	//�~���҂���������
public:
	static void InitRescue(void);
	static int GetRemain(void);
	static bool GetRescue(int i);
	static void SetRemain(int i);
	static RescueLife* GetRescueLife(void);
};