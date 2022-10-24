#pragma once
#define MAX_RESCUE (10)

class RescueLife
{
private:
	int remain;					//c‚è‹~•Ò”
	bool use[MAX_RESCUE];		//‹~•Ò‚ğg‚Á‚Ä‚¢‚é‚©”Û‚©
	bool rescue[MAX_RESCUE];	//‹~•Ò‚ğ•‚¯‚½‚©
public:
	static void InitRescue(void);
	static int GetRemain(void);
	static bool GetRescue(int i);
	static void SetRemain(int i);
	static RescueLife* GetRescueLife(void);
};