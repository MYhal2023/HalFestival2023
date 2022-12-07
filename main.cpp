//=============================================================================
//
// ���C������ [main.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "renderer.h"
#include "shadow_renderer.h"
#include "input.h"
#include "camera.h"
#include "debugproc.h"
#include "model.h"
#include "shadow.h"
#include "light.h"
#include "collision.h"
#include "time.h"
#include "sound.h"

#include "game.h"
#include "fade.h"
#include "result.h"
#include "title.h"
#include "reserve.h"
#include "player.h"
#include "playerArms.h"
#include "easing.h"
#include "fire.h"
#include "particle.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define CLASS_NAME		"AppClass"			// �E�C���h�E�̃N���X��
#define WINDOW_NAME		"game"		// �E�C���h�E�̃L���v�V������

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);


//*****************************************************************************
// �O���[�o���ϐ�:
//*****************************************************************************
long g_MouseX = 0;
long g_MouseY = 0;


#ifdef _DEBUG
int		g_CountFPS;							// FPS�J�E���^
char	g_DebugStr[2048] = WINDOW_NAME;		// �f�o�b�O�����\���p

#endif

int	g_Mode = MODE_TITLE;					// �N�����̉�ʂ�ݒ�


//=============================================================================
// ���C���֐�
//=============================================================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);	// �����Ă��ǂ����ǁA�x�����o��i���g�p�錾�j
	UNREFERENCED_PARAMETER(lpCmdLine);		// �����Ă��ǂ����ǁA�x�����o��i���g�p�錾�j

	// ���Ԍv���p
	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;
	DWORD dwCurrentTime;
	DWORD dwFrameCount;

	WNDCLASSEX	wcex = {
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		hInstance,
		NULL,
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		NULL
	};
	HWND		hWnd;
	MSG			msg;
	
	// �E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	// �E�B���h�E�̍쐬
	hWnd = CreateWindow(CLASS_NAME,
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,																		// �E�B���h�E�̍����W
		CW_USEDEFAULT,																		// �E�B���h�E�̏���W
		SCREEN_WIDTH + GetSystemMetrics(SM_CXDLGFRAME) * 2,									// �E�B���h�E����
		SCREEN_HEIGHT + GetSystemMetrics(SM_CXDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION),	// �E�B���h�E�c��
		NULL,
		NULL,
		hInstance,
		NULL);

	// ����������(�E�B���h�E���쐬���Ă���s��)
	if(FAILED(Init(hInstance, hWnd, TRUE)))
	{
		return -1;
	}

	// �t���[���J�E���g������
	timeBeginPeriod(1);	// ����\��ݒ�
	dwExecLastTime = dwFPSLastTime = timeGetTime();	// �V�X�e���������~���b�P�ʂŎ擾
	dwCurrentTime = dwFrameCount = 0;

	// �E�C���h�E�̕\��(�����������̌�ɌĂ΂Ȃ��Ƒʖ�)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	
	// ���b�Z�[�W���[�v
	while(1)
	{
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
			{// PostQuitMessage();//���Ă΂ꂽ�烋�[�v�I��
				break;
			}
			else
			{
				// ���b�Z�[�W�̖|��Ƒ��o
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
        }
		else
		{
			dwCurrentTime = timeGetTime();

			if ((dwCurrentTime - dwFPSLastTime) >= 1000)	// 1�b���ƂɎ��s
			{
#ifdef _DEBUG
				g_CountFPS = dwFrameCount;
#endif
				dwFPSLastTime = dwCurrentTime;				// FPS�𑪒肵��������ۑ�
				dwFrameCount = 0;							// �J�E���g���N���A
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))	// 1/60�b���ƂɎ��s
			{
				dwExecLastTime = dwCurrentTime;	// ��������������ۑ�

#ifdef _DEBUG	// �f�o�b�O�ł̎�����FPS��\������
				wsprintf(g_DebugStr, WINDOW_NAME);
				wsprintf(&g_DebugStr[strlen(g_DebugStr)], " FPS:%d", g_CountFPS);
#endif

				Update();			// �X�V����
				Draw();				// �`�揈��

#ifdef _DEBUG	// �f�o�b�O�ł̎������\������
				wsprintf(&g_DebugStr[strlen(g_DebugStr)], " MX:%d MY:%d", GetMousePosX(), GetMousePosY());
				SetWindowText(hWnd, g_DebugStr);
#endif

				dwFrameCount++;
			}
		}
	}

	timeEndPeriod(1);				// ����\��߂�

	// �E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	// �I������
	Uninit();

	return (int)msg.wParam;
}

//=============================================================================
// �v���V�[�W��
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;
		}
		break;

	case WM_MOUSEMOVE:
		g_MouseX = LOWORD(lParam);
		g_MouseY = HIWORD(lParam);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	InitRenderer(hInstance, hWnd, bWindow);

	InitLight();

	InitCamera();

	// ���͏����̏�����
	InitInput(hInstance, hWnd);

	// �T�E���h�̏�����
	InitSound(hWnd);
	SetSourceVolume(SOUND_LABEL_BGM_Title, 0.5f);
	SetSourceVolume(SOUND_LABEL_BGM_Battle, 0.3f);
	SetSourceVolume(SOUND_LABEL_BGM_Result, 0.5f);
	SetSourceVolume(SOUND_LABEL_BGM_Result2, 0.5f);
	SetSourceVolume(SOUND_LABEL_SE_lock, 0.7f);

#ifdef _DEBUG
	SetSourceVolume(SOUND_LABEL_BGM_Title, 0.0f);
	SetSourceVolume(SOUND_LABEL_BGM_Battle, 0.0f);
	SetSourceVolume(SOUND_LABEL_BGM_Result2, 0.0f);
	SetSourceVolume(SOUND_LABEL_BGM_Result, 0.0f);
#endif
	// �e�̏�����
	InitSM();

	// ���C�g��L����
	SetLightEnable(TRUE);

	// �w�ʃ|���S�����J�����O
	SetCullingMode(CULL_MODE_BACK);


	// �t�F�[�h�̏�����
	InitFade();

	Easing::Init();

	// �ŏ��̃��[�h���Z�b�g
	SetMode(g_Mode);	// ������SetMode�̂܂܂ŁI

	InitReward();	//���U���g�f�[�^������
	SetReward();

	//3D���f���ǂݍ���
	InitBoot();
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void Uninit(void)
{
	//���f���Ⓒ�_���̉��
	UninitGame();

	// �I���̃��[�h���Z�b�g
	SetMode(MODE_MAX);
	
	// �T�E���h�I������
	UninitSound();

	// �J�����̏I������
	UninitCamera();

	//���͂̏I������
	UninitInput();

	// �����_���[�̏I������
	UninitRenderer();

	// �e�̏I������
	UninitSM();

	//�t�F�[�h�̏I������
	UninitFade();

	//3D���f���̏I������
	UninitModel();

	pArm::UninitArm();
	Normal::UninitArm();
}

//=============================================================================
// �X�V����
//=============================================================================
void Update(void)
{
	// ���͂̍X�V����
	UpdateInput();

	// ���C�g�̍X�V����
	UpdateLight();

	// �J�����X�V
	UpdateCamera();

	Easing::Update();

	// ���[�h�ɂ���ď����𕪂���
	switch (g_Mode)
	{
	case MODE_TITLE:		// �^�C�g����ʂ̍X�V
		UpdateFire();
		UpdateParticle();
		UpdateTitle();
		break;

	case MODE_RESERVE:
		UpdateFire();
		UpdateParticle();
		UpdateReserve();
		break;
	case MODE_GAME:			// �Q�[����ʂ̍X�V
		UpdateGame();
		break;
	case MODE_RESULT:		// ���U���g��ʂ̍X�V
		UpdateResult();
		break;
	}

	// �t�F�[�h�����̍X�V
	UpdateFade();


}

//=============================================================================
// �`�揈��
//=============================================================================
void Draw(void)
{
	// �o�b�N�o�b�t�@�N���A
	Clear();

	// �J��������
	{	
		SetCamera();				// �J�������_
		UpdateLight();
		SetLightViewProjection();	// ���C�g���_
	}

	// ���[�h�ɂ���ď����𕪂���
	switch (g_Mode)
	{
	case MODE_TITLE:		// �^�C�g����ʂ̕`��
		SetViewPort(TYPE_FULL_SCREEN);

		SetSMRenderer();	//�V���h�E�}�b�v�Z�b�g
		DrawGame1();

		SetViewPortType(TYPE_FULL_SCREEN);
		SetRenderer();		//�ʏ�`��
		DrawGameTitle();

		// ���C�e�B���O��L����
		SetLightEnable(TRUE);

		// Z��r����
		SetDepthEnable(TRUE);
		break;

	case MODE_RESERVE:
		SetViewPort(TYPE_FULL_SCREEN);

		SetSMRenderer();	//�V���h�E�}�b�v�Z�b�g
		DrawGame1();
		SetRenderer();		//�ʏ�`��
		DrawGameReserve();
		break;
	case MODE_GAME:			// �Q�[����ʂ̕`��
		SetViewPortType(TYPE_LIGHT_SCREEN);
		SetSMRenderer();	//�V���h�E�}�b�v�Z�b�g
		DrawGame1();

		SetViewPortType(TYPE_FULL_SCREEN);
		SetRenderer();		//�ʏ�`��
		DrawGame();

		break;

	case MODE_RESULT:		// ���U���g��ʂ̕`��
		SetViewPort(TYPE_FULL_SCREEN);

		SetSMRenderer();	//�V���h�E�}�b�v�Z�b�g
		DrawGame1();

		SetRenderer();		//�ʏ�`��
		DrawGameResult();
		break;

	}

	// �t�F�[�h�`��
	DrawFade();

#ifdef _DEBUG
	// �f�o�b�O�\��
	//DrawDebugProc();
#endif

	// �o�b�N�o�b�t�@�A�t�����g�o�b�t�@����ւ�
	Present();
}


long GetMousePosX(void)
{
	return g_MouseX;
}


long GetMousePosY(void)
{
	return g_MouseY;
}


#ifdef _DEBUG
char* GetDebugStr(void)
{
	return g_DebugStr;
}
#endif



//=============================================================================
// ���[�h�̐ݒ�
//=============================================================================
void SetMode(int mode)
{
	// ���[�h��ς���O�ɑS�������������
	StopSound();

	// �Q�[����ʂ̏I������
	UninitResult();
	UninitReserve();
	UninitTitle();
	Easing::Init();
	g_Mode = mode;	// ���̃��[�h���Z�b�g���Ă���

	switch (g_Mode)
	{
	case MODE_TITLE:
		// �^�C�g����ʂ̏�����
		InitGame();
		InitTitle();
		break;
	case MODE_RESERVE:
		// �琬��ʂ̏�����
		InitReserve();
		InitGame();
		break;

	case MODE_GAME:
		// �Q�[����ʂ̏�����
		InitReward();	//���U���g�f�[�^������
		InitGame();
		PlaySound(SOUND_LABEL_BGM_Battle);
		break;

	case MODE_RESULT:
		// ���U���g��ʂ̏�����
		SetReward();
		InitGame();
		InitResult();
		break;

		// �Q�[���I�����̏���
	case MODE_MAX:
		PostQuitMessage(0);
		break;
	}
}

//=============================================================================
// ���[�h�̎擾
//=============================================================================
int GetMode(void)
{
	return g_Mode;
}

