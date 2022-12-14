//=============================================================================
//
// 入力処理 [input.h]
// Author : 
//
//=============================================================================
#pragma once


//*****************************************************************************
// マクロ定義
//*****************************************************************************

// プログラム分けするときに使う
#define	USE_KEYBOARD										// 宣言するとキーボードで操作可能になる
#define	USE_MOUSE											// 宣言するとマウスで操作可能になる
#define	USE_PAD												// 宣言するとパッドで操作可能になる


/* game pad情報 */
#define BUTTON_UP		0x00000001l	// 方向キー上(.IY<0)
#define BUTTON_DOWN		0x00000002l	// 方向キー下(.IY>0)
#define BUTTON_LEFT		0x00000004l	// 方向キー左(.IX<0)
#define BUTTON_RIGHT	0x00000008l	// 方向キー右(.IX>0)
#define BUTTON_A		0x00000010l	// Ａ□ボタン(.rgbButtons[0]&0x80)
#define BUTTON_B		0x00000020l	// Ｂ×ボタン(.rgbButtons[1]&0x80)
#define BUTTON_C		0x00000040l	// Ｃ〇ボタン(.rgbButtons[2]&0x80)
#define BUTTON_X		0x00000080l	// Ｘ△ボタン(.rgbButtons[3]&0x80)
#define BUTTON_Y		0x00000100l	// Ｙボタン(.rgbButtons[4]&0x80)
#define BUTTON_Z		0x00000200l	// Ｚボタン(.rgbButtons[5]&0x80)
#define BUTTON_L		0x00000400l	// Ｌボタン(.rgbButtons[6]&0x80)
#define BUTTON_R		0x00000800l	// Ｒボタン(.rgbButtons[7]&0x80)
#define BUTTON_START	0x00001000l	// ＳＴＡＲＴボタン(.rgbButtons[8]&0x80)
#define BUTTON_M		0x00002000l	// Ｍボタン(.rgbButtons[9]&0x80)
#define BUTTON_R_RIGHT	0x00004000l	// 右スティック右(.lZ<0)
#define BUTTON_R_LEFT	0x00008000l	// 右スティック左(.lZ<0)
#define RGDW_UP			0x00010000l	// 右スティック上
#define RGDW_DOWN		0x00020000l	// 右スティック下
#define RGDW_LEFT		0x00040000l	// 右スティック右(.lZ<0)
#define RGDW_RIGHT		0x00080000l	// 右スティック左(.lZ<0)

#define GAMEPADMAX		4			// 同時に接続するジョイパッドの最大数をセット

enum ForceState
{
	FORCE_NON,
	FORCE_SLOW,
	FORCE_MIDDLE,
	FORCE_FAST,
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitInput(HINSTANCE hInst, HWND hWnd);
void UninitInput(void);
void UpdateInput(void);

//---------------------------- keyboard
BOOL GetKeyboardPress(int nKey);
BOOL GetKeyboardTrigger(int nKey);
BOOL GetKeyboardRepeat(int nKey);
BOOL GetKeyboardRelease(int nKey);

//---------------------------- mouse
BOOL IsMouseLeftPressed(void);      // 左クリックした状態
BOOL IsMouseLeftTriggered(void);    // 左クリックした瞬間
BOOL IsMouseRightPressed(void);     // 右クリックした状態
BOOL IsMouseRightTriggered(void);   // 右クリックした瞬間
BOOL IsMouseCenterPressed(void);    // 中クリックした状態
BOOL IsMouseCenterTriggered(void);  // 中クリックした瞬間
long GetMouseX(void);               // マウスがX方向に動いた相対値
long GetMouseY(void);               // マウスがY方向に動いた相対値
long GetMouseZ(void);               // マウスホイールが動いた相対値

//---------------------------- game pad
BOOL IsButtonPressed(int padNo,DWORD button);
BOOL IsButtonTriggered(int padNo,DWORD button);
int IsButtonForce(int padNo);
void SetForceState(BOOL flag);
void InitForce(int padNo);
void padFFAxisStart(int padNo);
void padFFAxisStop(int padNo);