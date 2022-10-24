#pragma once
#define MAX_RESCUE (10)

class RescueLife
{
private:
	int remain;					//残り救助者数
	bool use[MAX_RESCUE];		//救助者を使っているか否か
	bool rescue[MAX_RESCUE];	//救助者を助けたか
public:
	static void InitRescue(void);
	static int GetRemain(void);
	static bool GetRescue(int i);
	static void SetRemain(int i);
	static RescueLife* GetRescueLife(void);
};