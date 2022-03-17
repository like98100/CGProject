////////////////////////////////////////////////////////////////////////////////
// Filename: systemclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "systemclass.h"


SystemClass::SystemClass()
{
	m_Input = 0;
	m_Graphics = 0;
	m_Fps = 0;
	m_Cpu = 0;
	m_Timer = 0;

	m_directInput = 0;
	m_keyboard = 0;
	m_mouse = 0;

	speed = 2.0f;
	isKnockbacked = false;
	for (int i = 0; i < 5; i++) isClocked[i] = false;
	m_Sound = 0;
	bgmFlag = -1;
}


SystemClass::SystemClass(const SystemClass& other)
{
}


SystemClass::~SystemClass()
{
}


bool SystemClass::Initialize()
{
	int screenWidth, screenHeight;
	bool result;


	// Initialize the width and height of the screen to zero before sending the variables into the function.
	screenWidth = 0;
	screenHeight = 0;

	// Initialize the windows api.
	InitializeWindows(screenWidth, screenHeight);

	// Input 입력
	InitDirectInput();

	// Create the input object.  This object will be used to handle reading the keyboard input from the user.
	m_Input = new InputClass;
	if(!m_Input)
	{
		return false;
	}

	// Initialize the input object.
	m_Input->Initialize();

	// Create the graphics object.  This object will handle rendering all the graphics for this application.
	m_Graphics = new GraphicsClass;
	if(!m_Graphics)
	{
		return false;
	}

	// Initialize the graphics object.
	result = m_Graphics->Initialize(screenWidth, screenHeight, m_hwnd);
	if(!result)
	{
		return false;
	}
	
	// Create the fps object.
	m_Fps = new FpsClass;
	if (!m_Fps)
	{
		return false;
	}

	// Initialize the fps object.
	m_Fps->Initialize();
	// Create the cpu object.
	m_Cpu = new CpuClass;
	if (!m_Cpu)
	{
		return false;
	}

	// Initialize the cpu object.
	m_Cpu->Initialize();
	// Create the timer object.
	m_Timer = new TimerClass;
	if (!m_Timer)
	{
		return false;
	}

	// Initialize the timer object.
	result = m_Timer->Initialize();
	if (!result)
	{
		MessageBox(m_hwnd, L"Could not initialize the Timer object.", L"Error", MB_OK);
		return false;
	}

	// Create the sound object.
	m_Sound = new SoundClass;
	if (!m_Sound)
	{
		return false;
	}

	// Initialize the sound object.
	result = m_Sound->Initialize(m_hwnd);
	if (!result)
	{
		MessageBox(m_hwnd, L"Could not initialize Direct Sound.", L"Error", MB_OK);
		return false;
	}

	result = m_Sound->playBGM();
	if (!result)
	{
		MessageBox(m_hwnd, L"Could not play Direct Sound.", L"Error", MB_OK);
		return false;
	}

	return true;
}


void SystemClass::Shutdown()
{
	// Release the graphics object.
	if(m_Graphics)
	{
		m_Graphics->Shutdown();
		delete m_Graphics;
		m_Graphics = 0;
	}

	// Release the input object.
	if(m_Input)
	{
		delete m_Input;
		m_Input = 0;
	}

	// Release the timer object.
	if (m_Timer)
	{
		delete m_Timer;
m_Timer = 0;
	}

	// Release the cpu object.
	if (m_Cpu)
	{
		m_Cpu->Shutdown();
		delete m_Cpu;
		m_Cpu = 0;
	}

	// Release the fps object.
	if (m_Fps)
	{
		delete m_Fps;
		m_Fps = 0;
	}

	// Release the sound object.
	if (m_Sound)
	{
		m_Sound->Shutdown();
		delete m_Sound;
		m_Sound = 0;
	}


	// Shutdown the window.
	ShutdownWindows();

	return;
}


void SystemClass::Run()
{
	MSG msg;
	bool done, result;


	// Initialize the message structure.
	ZeroMemory(&msg, sizeof(MSG));

	// Loop until there is a quit message from the window or the user.
	done = false;
	while (!done)
	{
		// Handle the windows messages.
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// If windows signals to end the application then exit out.
		if (msg.message == WM_QUIT)
		{
			done = true;
		}
		else
		{
			// Otherwise do the frame processing.
			result = Frame();
			if (!result)
			{
				done = true;
			}
		}

	}

	return;
}


bool SystemClass::Frame()
{
	bool result;
	int mouseX, mouseY;
	m_Timer->Frame();
	m_Fps->Frame();
	m_Cpu->Frame();

	DetectInput();
	GetMouseLocation(mouseX, mouseY);
	// Check if the user pressed escape and wants to exit the application.
	if (m_Input->IsKeyDown(VK_ESCAPE))
	{
		return false;
	}

	if (m_Graphics->sceneFlag[0] == true)
	{
		for (int i = 0; i < 5; i++) m_Sound->stopFile(i+1);
	}
	else if (m_Graphics->sceneFlag[1] == true)
	{

		if (m_Graphics->CollidObjNum == 2)
		{
			m_Sound->playScoreSE();
		}
		//else m_Sound->stopFile(2);

		if (bgmFlag < 0 && m_Graphics->GetScore() < 3)
		{
			m_Sound->playBGM();
			bgmFlag = 0;
		}
		if (m_Graphics->GetScore() >= 3 && m_Graphics->GetScore() < 6 && bgmFlag < 1)
		{
			m_Sound->stopFile(1);
			m_Sound->playBGM2();
			bgmFlag = 1;
		}
		if (m_Graphics->GetScore() >= 6 && m_Graphics->GetScore() < 10 && bgmFlag < 2)
		{
			m_Sound->stopFile(4);
			m_Sound->playBGM3();
			bgmFlag = 2;
		}
		else if(m_Graphics->GetScore() >= 10)
		{
			m_Sound->stopFile(5);

		}

		float angle;
		// 물고기가 벽에 부딪힐 때 넉백
		for (int i = 0; i < 5; i++)
		{
			if (m_Graphics->smallFishCollision[i])
			{
				SmallFishKnockBack(i);
				m_Graphics->smallFishCollision[i] = false;
			}
		}
		// 넉백 이후 방향조정
		for (int i = 0; i < 5; i++)
		{
			smallFishTime2[i] = clock();
			if ((smallFishTime2[i] - smallFishTime1[i]) > 0.35f * CLOCKS_PER_SEC && isClocked[i])
			{
				m_Graphics->smallFishBF[i] = -1.0f;

				//m_Graphics->smallFishBF[i] *= -1.0f;
				angle = rand() & 181;
				m_Graphics->SmallFishRotate(angle, i);
				isClocked[i] = false;
			}
		}
	}
	else if(m_Graphics->sceneFlag[2] == true)
	{
		for(int i = 0; i < 5; i++) m_Sound->stopFile(i+1);
		bgmFlag = -1;
	}
	

	// Do the frame processing for the graphics object.
	result = m_Graphics->Frame(m_Fps->GetFps(), m_Cpu->GetCpuPercentage(), m_Timer->GetTime());
	if (!result)
	{
		return false;
	}


	return true;
}


LRESULT CALLBACK SystemClass::MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
	switch(umsg)
	{
		// Check if a key has been pressed on the keyboard.
		case WM_KEYDOWN:
		{
			// If a key is pressed send it to the input object so it can record that state.
			m_Input->KeyDown((unsigned int)wparam);
			return 0;
		}

		// Check if a key has been released on the keyboard.
		case WM_KEYUP:
		{
			// If a key is released then send it to the input object so it can unset the state for that key.
			m_Input->KeyUp((unsigned int)wparam);
			return 0;
		}

		// Any other messages send to the default message handler as our application won't make use of them.
		default:
		{
			return DefWindowProc(hwnd, umsg, wparam, lparam);
		}
	}
}


void SystemClass::InitializeWindows(int& screenWidth, int& screenHeight)
{
	WNDCLASSEX wc;
	DEVMODE dmScreenSettings;
	int posX, posY;


	// Get an external pointer to this object.	
	ApplicationHandle = this;

	// Get the instance of this application.
	m_hinstance = GetModuleHandle(NULL);

	// Give the application a name.
	m_applicationName = L"Engine";

	// Setup the windows class with default settings.
	wc.style         = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc   = WndProc;
	wc.cbClsExtra    = 0;
	wc.cbWndExtra    = 0;
	wc.hInstance     = m_hinstance;
	wc.hIcon		 = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm       = wc.hIcon;
	wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName  = NULL;
	wc.lpszClassName = m_applicationName;
	wc.cbSize        = sizeof(WNDCLASSEX);
	
	// Register the window class.
	RegisterClassEx(&wc);

	// Determine the resolution of the clients desktop screen.
	screenWidth  = GetSystemMetrics(SM_CXSCREEN);
	screenHeight = GetSystemMetrics(SM_CYSCREEN);

	// Setup the screen settings depending on whether it is running in full screen or in windowed mode.
	if(FULL_SCREEN)
	{
		// If full screen set the screen to maximum size of the users desktop and 32bit.
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize       = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth  = (unsigned long)screenWidth;
		dmScreenSettings.dmPelsHeight = (unsigned long)screenHeight;
		dmScreenSettings.dmBitsPerPel = 32;			
		dmScreenSettings.dmFields     = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// Change the display settings to full screen.
		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

		// Set the position of the window to the top left corner.
		posX = posY = 0;
	}
	else
	{
		// If windowed then set it to 800x600 resolution.
		screenWidth  = 800;
		screenHeight = 600;

		// Place the window in the middle of the screen.
		posX = (GetSystemMetrics(SM_CXSCREEN) - screenWidth)  / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - screenHeight) / 2;
	}

	// Create the window with the screen settings and get the handle to it.
	m_hwnd = CreateWindowEx(WS_EX_APPWINDOW, m_applicationName, m_applicationName, 
						    WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,
						    posX, posY, screenWidth, screenHeight, NULL, NULL, m_hinstance, NULL);

	// Bring the window up on the screen and set it as main focus.
	ShowWindow(m_hwnd, SW_SHOW);
	SetForegroundWindow(m_hwnd);
	SetFocus(m_hwnd);

	// Hide the mouse cursor.
	ShowCursor(false);

	return;
}


void SystemClass::ShutdownWindows()
{
	// Show the mouse cursor.
	ShowCursor(true);

	// Fix the display settings if leaving full screen mode.
	if(FULL_SCREEN)
	{
		ChangeDisplaySettings(NULL, 0);
	}

	// Remove the window.
	DestroyWindow(m_hwnd);
	m_hwnd = NULL;

	// Remove the application instance.
	UnregisterClass(m_applicationName, m_hinstance);
	m_hinstance = NULL;

	// Release the pointer to this class.
	ApplicationHandle = NULL;

	return;
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
{
	switch(umessage)
	{
		// Check if the window is being destroyed.
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}

		// Check if the window is being closed.
		case WM_CLOSE:
		{
			PostQuitMessage(0);		
			return 0;
		}

		// All other messages pass to the message handler in the system class.
		default:
		{
			return ApplicationHandle->MessageHandler(hwnd, umessage, wparam, lparam);
		}
	}
}

bool SystemClass::InitDirectInput()
{
	DirectInput8Create(m_hinstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&DirectInput, NULL);

	DirectInput->CreateDevice(GUID_SysKeyboard, &DIKeyboard, NULL);
	DirectInput->CreateDevice(GUID_SysMouse, &DIMouse, NULL);

	DIKeyboard->SetDataFormat(&c_dfDIKeyboard);
	DIKeyboard->SetCooperativeLevel(m_hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

	DIMouse->SetDataFormat(&c_dfDIMouse);
	DIMouse->SetCooperativeLevel(m_hwnd, DISCL_EXCLUSIVE | DISCL_NOWINKEY | DISCL_FOREGROUND);

	return true;
}

void SystemClass::DetectInput()
{
	DIMOUSESTATE mouseCurrentState;
	BYTE keyboardState[256];

	DIKeyboard->Acquire();
	DIMouse->Acquire();

	DIMouse->GetDeviceState(sizeof(DIMOUSESTATE), &mouseCurrentState);
	DIKeyboard->GetDeviceState(sizeof(keyboardState), (LPVOID)&keyboardState);


	if (m_Graphics->sceneFlag[0] == true)
	{
		if (keyboardState[DIK_RETURN] & 0x80) // 게임 시작
		{
			m_Graphics->sceneFlag[1] = true;
			m_Graphics->sceneFlag[0] = false;
			m_Graphics->sceneFlag[2] = false;
			m_Graphics->restartFlag = false;
	}
	}
	else if (m_Graphics->sceneFlag[1] == true)
	{
		//float speed = 2.0f;
		if (m_Graphics->CollidObjNum == 4 || m_Graphics->CollidObjNum == 1 || m_Graphics->CollidObjNum == 3)
		{
			m_Sound->playBloodSE();
			//if (speed == -2.0f && m_Graphics->CollidObjNum == 3)	//상어와 추가 충돌
			//{
			//	
			//}
			if (speed != -2.0f)
			{
				KnockBack();
				m_Graphics->CollidObjNum = 0;

			}
			else
			{
				speed = 2.0f;

			}
		}

		time2 = clock();
		if ((time2 - time1) > 0.55f * CLOCKS_PER_SEC)
		{
			speed = 2.0f;
			m_Graphics->sharkBF = 1.6f;
		}

		bool isGpressedOnce = false;

		m_Graphics->moveBF -= speed;

		if ((mouseCurrentState.lX != mouseLastState.lX) || (mouseCurrentState.lY != mouseLastState.lY))
		{
			m_Graphics->camYaw += mouseLastState.lX * 0.001f;

			m_Graphics->camPitch -= mouseCurrentState.lY * 0.001f;

			mouseLastState = mouseCurrentState;
		}

		// 이동하지 않을 때 중심을 맞춤
		if (!(keyboardState[DIK_D] & 0x80) && !(keyboardState[DIK_A] & 0x80) && (mouseLastState.lX > -10.0f) && (mouseLastState.lX < 10.0f))
		{
		}

		if (keyboardState[DIK_A] & 0x80) // A : 좌측으로 회전
		{
			m_Graphics->playerYaw -= 0.025f;
		}

		if (keyboardState[DIK_D] & 0x80) // D : 좌측으로 회전
		{
			m_Graphics->playerYaw += 0.025f;
		}

		if (keyboardState[DIK_W] & 0x80) // W : 위로 피치
		{
			m_Graphics->playerPitch += 0.015f;
		}

		if (keyboardState[DIK_S] & 0x80) // S : 아래로 피치
		{
			m_Graphics->playerPitch -= 0.015f;
		}

		if (m_Graphics->sceneFlag[1] == true && (m_Graphics->m_score >= 10 || m_Graphics->m_hp <= 0))	// 게임 종료
		{
			m_Graphics->sceneFlag[2] = true;
			m_Graphics->sceneFlag[1] = false;
			m_Graphics->sceneFlag[0] = false;
		}

	}
	else if (m_Graphics->sceneFlag[2] == true)
	{
		for (int i = 0; i < 4; i++) m_Sound->stopFile(i + 1);
		bgmFlag = -1;

		if (keyboardState[DIK_R] & 0x80) // 게임 재시작
		{
			m_Graphics->sceneFlag[1] = true;
			m_Graphics->sceneFlag[0] = false;
			m_Graphics->sceneFlag[2] = false;
			m_Graphics->restartFlag = false;
		}
		else if (keyboardState[DIK_SPACE] & 0x80) // 타이틀로 돌아가기
		{
			m_Graphics->sceneFlag[0] = true;
			m_Graphics->sceneFlag[1] = false;
			m_Graphics->sceneFlag[2] = false;
			m_Graphics->restartFlag = false;
		}
	}
	
}

bool SystemClass::IsEscapePressed()
{
	// esc 눌렀나?
	if (m_keyboardState[DIK_ESCAPE] & 0x80)
	{
		return true;
	}
	return false;
}

void SystemClass::GetMouseLocation(int& mouseX, int& mouseY)
{
	mouseX = m_mouseX;
	mouseY = m_mouseY;
	return;
}

bool SystemClass::ReadKeyBoard()
{
	HRESULT result;

	// 키보드 장치 불러오기
	result = m_keyboard->GetDeviceState(sizeof(m_keyboardState), (LPVOID)&m_keyboardState);
	if (FAILED(result))
	{
		// 키보드 입력을 받아올 수 없을 때
		if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
		{
			m_keyboard->Acquire();
		}
		else
		{
			return false;
		}
	}

	return true;
}

bool SystemClass::ReadMouse()
{
	HRESULT result;
	DIMOUSESTATE m_mouseCurrentState;

	// 마우스 장치 불러오기
	result = m_mouse->GetDeviceState(sizeof(DIMOUSESTATE), &m_mouseCurrentState);
	if (FAILED(result))
	{
		// 마우스 입력을 받아올 수 없을 때
		if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
		{
			m_mouse->Acquire();
		}
		else
		{
			return false;
		}
	}
	m_mouseLastState = m_mouseCurrentState;
	return true;
}

void SystemClass::ProcessInput()
{
	// 현재 마우스 위치를 기준으로 마우스 위치 업데이트
	m_mouseX += m_mouseLastState.lX;
	m_mouseY += m_mouseLastState.lY;

	if (m_mouseX < 0) m_mouseX = 0;
	if (m_mouseY < 0) m_mouseY = 0;

	if (m_mouseX > m_screenWidth) m_mouseX = m_screenWidth;
	if (m_mouseY > m_screenHeight) m_mouseY = m_screenHeight;
	
	return;
}

void SystemClass::KnockBack()
{
	time1 = clock();
	speed = -2.0f;
	m_Graphics->sharkBF = -4.2f;
}

void SystemClass::SmallFishKnockBack(int index)
{
	smallFishTime1[index] = clock();
	m_Graphics->smallFishBF[index] = 1.0f;
	isClocked[index] = true;
}