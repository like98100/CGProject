////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "graphicsclass.h"


GraphicsClass::GraphicsClass()
{
	restartFlag = true;
	m_D3D = 0;
	m_Camera = 0;
	m_Ground = 0;
	m_Stone = 0;
	m_PlayableFish = 0;
	m_SmallFish = 0;
	m_Shark = 0;
	m_BillboardModel = 0;
	m_SeaBox = 0;

	m_LightShader = 0;
	m_Light = 0;

	m_TextureShader = 0;
	m_Bitmap = 0;
	m_BitmapSuccess = 0;
	m_BitmapFail = 0;

	m_Text = 0;
	m_ParticleShader = 0;
	for(int i = 0; i < 3; i++) m_ParticleSystem[i] = 0;

	for (int i = 0; i < 2; i++) ParticleTime[i] = 0;

	m_FogShader = 0;

	desiredCharDir = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	playerPosition = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	sharkPosition = XMVectorSet(100.0f, 550.0f, 350.0f, 0.0f);

	for (int i = 0; i < 10; i++)
	{
		seaWeedPosition[i] = XMVectorSet(0.0f + i * 10.0f, 0.0f, 20.0f + i, 0.0f);
	}

	seaWeedPosition[0] = XMVectorSet(-450.0f, 0.0f, 900.0f, 0.0f);
	seaWeedPosition[1] = XMVectorSet(400.0f, 0.0f, 800.0f, 0.0f);
	seaWeedPosition[2] = XMVectorSet(-345.0f, 0.0f, -500.0f, 0.0f);
	seaWeedPosition[3] = XMVectorSet(345.0f, 0.0f, -500.0f, 0.0f);
	seaWeedPosition[4] = XMVectorSet(-1100.0f, 0.0f, 815.0f, 0.0f);
	seaWeedPosition[5] = XMVectorSet(-400.0f, 0.0f, -800.0f, 0.0f);
	seaWeedPosition[6] = XMVectorSet(400.0f, 0.0f, 900.0f, 0.0f);
	seaWeedPosition[7] = XMVectorSet(1100.0f, 0.0f, -810.0f, 0.0f);
	seaWeedPosition[8] = XMVectorSet(475.0f, 0.0f, -725.0f, 0.0f);
	seaWeedPosition[9] = XMVectorSet(-850.0f, 0.0f, -300.0f, 0.0f);

	smallFishPosition[0] = XMVectorSet(-500.0f, 150.0f, -200.0f, 0.0f);
	smallFishPosition[1] = XMVectorSet(-100.0f, 200.0f, -500.0f, 0.0f);
	smallFishPosition[2] = XMVectorSet(200.0f, 300.0f, 300.0f, 0.0f);
	smallFishPosition[3] = XMVectorSet(-200.0f, 100.0f, -250.0f, 0.0f);
	smallFishPosition[4] = XMVectorSet(400.0f, 250.0f, 450.0f, 0.0f);

	smallFishYaw[0] = -90.0f;
	smallFishYaw[1] = 45.0f;
	smallFishYaw[2] = -45.0f;
	smallFishYaw[3] = 0.0f;
	smallFishYaw[4] = 180.0f;

	crossForward = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	crossRight = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	crossUp = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	DefaultForward = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	DefaultRight = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);

	CamDefaultForward = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	CamDefaultRight = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);

	playerTarget = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	
	playerUp = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	playerForward = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	playerRight = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);

	sharkTarget = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);

	sharkUp = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	sharkForward = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	sharkRight = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);

	smallFishTarget = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);

	smallFishUp = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	smallFishForward = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	smallFishRight = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);

	RotateYaw = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	RotatePitch = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	RotateRoll = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);

	XMStoreFloat3(&m_playerPosition, playerPosition);
	XMStoreFloat3(&m_sharkPosition, sharkPosition);

	CollidObjNum = 0;
	m_time = 0.0f;
	frameTime = 0.0f;
	m_score = 0;
	m_hp = 20;
	m_screenWidth = 0;
	m_screenHeight = 0;
	m_playerPos = 0;
	playerX = 0;
	playerY = 0;
	playerZ = 0;

	fogColor = 0.0f;
	fogStart = 0.0f;
	fogEnd = 0.0f;

	m_SharkRadian = 0;

	sharkX = 0;
	sharkY = 0;
	sharkZ = 0;

	for (int i = 0; i < 5; i++)
	{
		smallFishDestroyed[i] = false;
		smallFishX[i] = 0;
		smallFishY[i] = 0;
		smallFishZ[i] = 0;
		smallFishBF[i] = -1.0f;
		smallFishCollision[i] = false;
		smallFishRespawn[i] = 0.0f;
	}
	for (int i = 1; i < 3; i++) sceneFlag[i] = false;
	sceneFlag[0] = true;
}


GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}


GraphicsClass::~GraphicsClass()
{
}


bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;

	XMMATRIX baseViewMatrix;

	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;

	// Create the Direct3D object.
	m_D3D = new D3DClass;
	if(!m_D3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}

	// Create the camera object.
	m_Camera = new CameraClass;
	if(!m_Camera)
	{
		return false;
	}

	// Set the initial position of the camera.
	m_Camera->SetPosition(0.0f, 10.0f, -75.0f);	
		
	// Create the ground model object.
	m_Ground = new ModelClass;
	if (!m_Ground) return false;

	// Create the Stone model object.
	m_Stone = new ModelClass;
	if (!m_Stone) return false;

	// Create the PlayableFish model object.
	m_PlayableFish = new ModelClass;
	if (!m_PlayableFish) return false;

	// Create the SmallFish model object.
	m_SmallFish = new ModelClass;
	if (!m_SmallFish) return false;

	// Create the Shark model object.
	m_Shark = new ModelClass;
	if (!m_Shark) return false;

	// Create the SeaBox model object.
	m_SeaBox = new SkymapClass;
	if (!m_SeaBox) return false;

	m_BillboardModel = new ModelClass;
	if (!m_BillboardModel) return false;

	// Initialize the model object.
	result = m_Ground->Initialize(m_D3D->GetDevice(), (char*)"./data/Terrain.obj", L"./data/sand.dds");
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	result = m_Stone->Initialize(m_D3D->GetDevice(), (char*)"./data/stonetoTriangle.obj", L"./data/Stone.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	result = m_PlayableFish->Initialize(m_D3D->GetDevice(), (char*)"./data/fishtoTriangle.obj", L"./data/fish_texture.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	result = m_SmallFish->Initialize(m_D3D->GetDevice(), (char*)"./data/smallfishtoTriangle.obj", L"./data/smallfish.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	result = m_Shark->Initialize(m_D3D->GetDevice(), (char*)"./data/GreatWhite.obj", L"./data/GreatWhiteDiffuse.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	result = m_BillboardModel->Initialize(m_D3D->GetDevice(), (char*)"./data/SeaWeed.obj", L"./data/SeaWeed.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the billboard model object.", L"Error", MB_OK);
		return false;
	}

	result = m_SeaBox->Initialize(m_D3D->GetDevice(), (WCHAR*)L"./data/seabox.dds", 10, 10);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// Create the light shader object.
	m_LightShader = new LightShaderClass;
	if (!m_LightShader)
	{
		return false;
	}

	// Initialize the light shader object.
	result = m_LightShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the light shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the light object.
	m_Light = new LightClass;
	if (!m_Light)
	{
		return false;
	}
	
	// Initialize the light object.
	m_Light->SetAmbientColor(0.3f, 0.45f, 0.65f, 1.0f);
 	m_Light->SetDiffuseColor(0.03f, 0.2f, 0.8f, 1.0f);
	m_Light->SetDirection(0.0f, -1.0f, 0.0f);
	m_Light->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetSpecularPower(256.0f);

	m_SharkRadian = new RadianType;

	// Create the texture shader object.
	m_TextureShader = new TextureShaderClass;
	if (!m_TextureShader)
	{
		return false;
	}

	// Initialize the texture shader object.
	result = m_TextureShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the texture shader object.", L"Error", MB_OK);
		return false;
	}


	// Create the bitmap object.
	m_Bitmap = new BitmapClass;
	if (!m_Bitmap)
	{
		return false;
	}

	// Initialize the bitmap object.
	result = m_Bitmap->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight, L"./data/Title.dds", screenWidth, screenHeight);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the bitmap object.", L"Error", MB_OK);
		return false;
	}

	// Create the bitmap object.
	m_BitmapSuccess = new BitmapClass;
	if (!m_Bitmap)
	{
		return false;
	}

	// Initialize the bitmap object.
	result = m_BitmapSuccess->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight, L"./data/Success.dds", screenWidth, screenHeight);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the bitmap object.", L"Error", MB_OK);
		return false;
	}

	// Create the bitmap object.
	m_BitmapFail = new BitmapClass;
	if (!m_Bitmap)
	{
		return false;
	}

	// Initialize the bitmap object.
	result = m_BitmapFail->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight, L"./data/Fail.dds", screenWidth, screenHeight);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the bitmap object.", L"Error", MB_OK);
		return false;
	}

	// Initialize a base view matrix with the camera for 2D user interface rendering.
//	m_Camera->SetPosition(0.0f, 0.0f, -1.0f);
	m_Camera->Render(playerYaw, playerPitch, moveLR, moveBF, CamDefaultForward, CamDefaultRight, playerPosition, charCamDist);
	m_Camera->GetViewMatrix(baseViewMatrix);

	// Create the text object.
	m_Text = new TextClass;
	if (!m_Text)
	{
		return false;
	}

	// Initialize the text object.
	result = m_Text->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), hwnd, screenWidth, screenHeight, baseViewMatrix);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the text object.", L"Error", MB_OK);
		return false;
	}

	// 파티클 셰이더 개체를 만듭니다.
	m_ParticleShader = new ParticleShaderClass;
	if (!m_ParticleShader)
	{
		return false;
	}

	// 파티클 셰이더 개체를 초기화합니다.
	if (!m_ParticleShader->Initialize(m_D3D->GetDevice(), hwnd))
	{
		MessageBox(hwnd, L"Could not initialize the particle shader object.", L"Error", MB_OK);
		return false;
	}

	// 파티클 시스템 객체를 만듭니다.
	for (int i = 0; i < 3; i++)
	{
		m_ParticleSystem[i] = new ParticleSystemClass;
		if (!m_ParticleSystem[i])
		{
			return false;
		}

	}

	// 파티클 시스템 객체를 초기화합니다.
	// bubble
	if (!m_ParticleSystem[0]->Initialize(m_D3D->GetDevice(), L"./data/bubble.dds", 0))
	{
		return false;
	}

	// light
	if (!m_ParticleSystem[1]->Initialize(m_D3D->GetDevice(), L"./data/light.dds", 1))
	{
		return false;
	}

	// blood
	if (!m_ParticleSystem[2]->Initialize(m_D3D->GetDevice(), L"./data/blood.dds", 2))
	{
		return false;
	}

	// Create the fog shader object
	m_FogShader = new FogShaderClass;
	if(!m_FogShader) return false;

	// Initialize the fog shader object.
	result = m_FogShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"안개 셰이더 오브젝트를 초기화할 수 없습니다.", L"Error", MB_OK);
		return false;
	}

	return true;
}


void GraphicsClass::Shutdown()
{
	// Release the model object.
	if (m_PlayableFish)
	{
		m_PlayableFish->Shutdown();
		delete m_PlayableFish;
		m_PlayableFish = 0;
	}

	if (m_Stone)
	{
		m_Stone->Shutdown();
		delete m_Stone;
		m_Stone = 0;
	}

	if (m_SmallFish)
	{
		m_SmallFish->Shutdown();
		delete m_SmallFish;
		m_SmallFish = 0;
	}

	if (m_Ground)
	{
		m_Ground->Shutdown();
		delete m_Ground;
		m_Ground = 0;
	}

	if (m_Shark)
	{
		m_Shark->Shutdown();
		delete m_Shark;
		m_Shark = 0;
	}

	if (m_BillboardModel)
	{
		m_BillboardModel->Shutdown();
		delete m_BillboardModel;
		m_BillboardModel = 0;
	}

	if (m_SeaBox)
	{
		m_SeaBox->Shutdown();
		delete m_SeaBox;
		m_SeaBox = 0;
	}

	// Release the camera object.
	if(m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	// Release the D3D object.
	if(m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}

	// Release the light object.
	if (m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}

	// Release the light shader object.
	if (m_LightShader)
	{
		m_LightShader->Shutdown();
		delete m_LightShader;
		m_LightShader = 0;
	}
	
	// Release the bitmap object.
	if (m_Bitmap)
	{
		m_Bitmap->Shutdown();
		delete m_Bitmap;
		m_Bitmap = 0;
	}

	// Release the bitmap object.
	if (m_BitmapSuccess)
	{
		m_BitmapSuccess->Shutdown();
		delete m_BitmapSuccess;
		m_BitmapSuccess = 0;
	}

	// Release the bitmap object.
	if (m_BitmapFail)
	{
		m_BitmapFail->Shutdown();
		delete m_BitmapFail;
		m_BitmapFail = 0;
	}

	// Release the texture shader object.
	if (m_TextureShader)
	{
		m_TextureShader->Shutdown();
		delete m_TextureShader;
		m_TextureShader = 0;
	}

	// 파티클 시스템 객체를 해제합니다.
	for (int i = 0; i < 3; i++)
	{
		if (m_ParticleSystem[i])
		{
			m_ParticleSystem[i]->Shutdown();
			delete m_ParticleSystem[i];
			m_ParticleSystem[i] = 0;
		}
	}

	// particle shader 객체를 해제한다.
	if (m_ParticleShader)
	{
		m_ParticleShader->Shutdown();
		delete m_ParticleShader;
		m_ParticleShader = 0;
	}

	// fog shdaer 객체를 해제한다
	if (m_FogShader)
	{
		m_FogShader->Shutdown();
		delete m_FogShader;
		m_FogShader = 0;
	}

	return;
}

bool GraphicsClass::Frame()
{
	bool result;

	static float rotation = 0.0f;

	// Update the rotation variable each frame.
	rotation += XM_PI * 0.005f;
	if (rotation > 360.0f)
	{
		rotation -= 360.0f;
	}

	// Render the graphics scene.
	result = RenderIngameScene(rotation);
	if(!result)
	{
		return false;
	}

	return true;
}

bool GraphicsClass::Frame(int fps, int cpu, float frameTime)
{
	bool result;
	static float rotation = 0.0f;
	this->frameTime = frameTime;
	//m_time += 0.25f / frameTime;
	if (fps <= 0)
	{
		m_time = 0;
	}
	else
	{
		m_time += 1.0f / fps;
	}

	// Update the rotation variable each frame.
	rotation += (float)XM_PI * 0.005f;
	if (rotation > 360.0f)
	{
		rotation -= 360.0f;
	}

	// Set the frames per second.
	result = m_Text->SetFps(fps, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	// Set the cpu usage.
	result = m_Text->SetCpu(cpu, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	result = m_Text->SetObject(objNum, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	result = m_Text->SetPolygon(m_indexCount, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	result = m_Text->SetTime(m_time, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	result = m_Text->SetScore(m_score, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	result = m_Text->SetHP(m_hp, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	result = m_Text->SetScreenWidth(m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	result = m_Text->SetScreenHeight(m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	result = m_Text->SetPlayerPosX(playerX, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	result = m_Text->SetPlayerPosY(playerY, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	result = m_Text->SetPlayerPosZ(playerZ, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	// 파티클 시스템에 대한 프레임 처리를 실행합니다.
	for (int i = 0; i < 3; i++)
	{
		m_ParticleSystem[i]->Frame(playerY, frameTime, m_D3D->GetDeviceContext());
	}


	if (!restartFlag)
	{
		RestartScene();
		restartFlag = true;
	}

	// Render the graphics scene.
	if (sceneFlag[0] == true)
	{
		result = RenderTitleScene();
		if (!result)
		{
			return false;
		}
	}
	else if (sceneFlag[1] == true)
	{
		result = RenderIngameScene(rotation);
		if (!result)
		{
			return false;
		}
	}
	else if (sceneFlag[2] == true)
	{
		result = RenderResultScene();
		if (!result)
		{
			return false;
		}
	}

	// Set the position of the camera.
//	m_Camera->SetPosition(0.0f, 0.0f, -10.0f);

	return true;
}

bool GraphicsClass::Frame(int mouseX, int mouseY)
{
	bool result;
	static float rotation = 0.0f;

	// Update the rotation variable each frame.
	rotation += (float)XM_PI * 0.005f;
	if (rotation > 360.0f)
	{
		rotation -= 360.0f;
	}

	// Set the location of the mouse.
	result = m_Text->SetMousePosition(mouseX, mouseY, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	// Render the graphics scene.
	result = RenderIngameScene(rotation);
	if (!result)
	{
		return false;
	}

	return true;
}

bool GraphicsClass::RenderTitleScene()
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix, orthoMatrix;
	bool result;


	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.0f, 1.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);
	m_D3D->GetOrthoMatrix(orthoMatrix);

	// Turn off the Z buffer to begin all 2D rendering.
	m_D3D->TurnZBufferOff();

	// Put the bitmap vertex and index buffers on the graphics pipeline to prepare them for drawing.
	result = m_Bitmap->Render(m_D3D->GetDeviceContext(), 0, -10.0f);
	if (!result)
	{
		return false;
	}

	// Render the bitmap with the texture shader.
	result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_Bitmap->GetIndexCount(), worldMatrix, viewMatrix, orthoMatrix, m_Bitmap->GetTexture());
	if (!result)
	{
		return false;
	}

	// Turn the Z buffer back on now that all 2D rendering has completed.
	m_D3D->TurnZBufferOn();

	// Present the rendered scene to the screen.
	m_D3D->EndScene();

	return true;
}

bool GraphicsClass::RenderResultScene()
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix, orthoMatrix;
	bool result;
	// Clear the buffers to begin the scene.
	if(m_score >= 10) m_D3D->BeginScene(0.0f, 0.0f, 1.0f, 1.0f);
	else if(m_hp <= 0) m_D3D->BeginScene(1.0f, 0.0f, 0.0f, 1.0f);

	//// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);
	m_D3D->GetOrthoMatrix(orthoMatrix);

	if (m_score >= 10)
	{
		// Put the bitmap vertex and index buffers on the graphics pipeline to prepare them for drawing.
		result = m_BitmapSuccess->Render(m_D3D->GetDeviceContext(), 0, -10.0f);
		if (!result)
		{
			return false;
		}

		// Render the bitmap with the texture shader.
		result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_Bitmap->GetIndexCount(), worldMatrix, viewMatrix, orthoMatrix, m_BitmapSuccess->GetTexture());
		if (!result)
		{
			return false;
		}
	}
	else if (m_hp <= 0)
	{
		// Put the bitmap vertex and index buffers on the graphics pipeline to prepare them for drawing.
		result = m_BitmapFail->Render(m_D3D->GetDeviceContext(), 0, -10.0f);
		if (!result)
		{
			return false;
		}

		// Render the bitmap with the texture shader.
		result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_Bitmap->GetIndexCount(), worldMatrix, viewMatrix, orthoMatrix, m_BitmapFail->GetTexture());
		if (!result)
		{
			return false;
		}
	}

	// Present the rendered scene to the screen.
	m_D3D->EndScene();


	return true;
}

bool GraphicsClass::RenderIngameScene(float rotation)
{
	m_indexCount = m_Stone->getPolygon() * num_stone
		+ m_SmallFish->getPolygon() * (objNum - (4 + num_stone))
		+ m_PlayableFish->getPolygon() + m_Shark->getPolygon() + m_Ground->getPolygon() + m_BillboardModel->getPolygon() * 10;

	fogColor = 0.1f;
	fogStart = 50.0f;
	fogEnd = 0.0f;

	XMMATRIX worldMatrix_Player;

	XMMATRIX worldMatrix_Ground;
	XMMATRIX transMatrix_Ground;
	XMMATRIX scaleMatrix_Ground;
	XMMATRIX rotateMatrix_Ground;

	XMMATRIX worldMatrix_Stone[4];
	XMMATRIX transMatrix_Stone[4];
	XMMATRIX scaleMatrix_Stone[4];
	XMMATRIX rotateMatrix_Stone[4];

	XMMATRIX worldMatrix_SmallFish[5];

	XMMATRIX worldMatrix_Shark;

	XMMATRIX worldMatrix_SeaBox;
	XMMATRIX transMatrix_SeaBox;
	XMMATRIX scaleMatrix_SeaBox;

	XMMATRIX worldMatrix_SeaWeed[10];

	XMMATRIX TextRotate;
	XMMATRIX TextScale;
	TextRotate = XMMatrixScaling(1.5f, 1.2f, 1.0f);

	XMMATRIX worldMatrix, viewMatrix, projectionMatrix, orthoMatrix;

	XMMATRIX worldMatrix_Particle[3];
	XMMATRIX scaleMatrix_Particle[3];
	XMMATRIX rotateMatrix_Particle[3];
	XMMATRIX transMatrix_Particle[3];
	bool result;

	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0, 0, fogColor, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render(camYaw, camPitch, moveLR, moveBF, CamDefaultForward, CamDefaultRight, playerPosition, charCamDist);
	
	
	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetWorldMatrix(worldMatrix_Player);
	m_D3D->GetWorldMatrix(worldMatrix_Ground);
	m_D3D->GetWorldMatrix(worldMatrix_Shark);
	m_D3D->GetWorldMatrix(worldMatrix_SeaBox);
	for(int i = 0; i < 10; i++)m_D3D->GetWorldMatrix(worldMatrix_SeaWeed[i]);
	for(int i = 0; i < 3; i++)m_D3D->GetWorldMatrix(worldMatrix_Particle[i]);

	for (int i = 0; i < num_stone; i++)		m_D3D->GetWorldMatrix(worldMatrix_Stone[i]);
	for (int i = 0; i < num_smallFish; i++)		m_D3D->GetWorldMatrix(worldMatrix_SmallFish[i]);

	m_D3D->GetProjectionMatrix(projectionMatrix);

	m_D3D->GetOrthoMatrix(orthoMatrix);

	XMFLOAT3 Camera_Pos = m_Camera->GetPosition();
	XMVECTOR Camera_Pos_Vec = XMLoadFloat3(&Camera_Pos);
	XMFLOAT3 Camera_Rotate = m_Camera->GetRotation();
	XMVECTOR Camera_Rotate_Vec = XMLoadFloat3(&Camera_Rotate);

	// 플레이어 이동
	camRotateInfoYaw = playerYaw;
	camRotateInfoPitch = playerPitch;
	

	scaleMatrix_Player = XMMatrixScaling(7.5f + ((m_score + 0.5f) * 0.8f), 7.5f + ((m_score + 0.5f) * 0.8f), 7.5f + ((m_score + 0.5f) * 0.8f));
	rotateMatrix_Player = MoveChar(playerYaw, playerPitch, playerRoll, moveLR, moveBF, DefaultForward, DefaultRight, worldMatrix_Player);
	

	m_PlayableFish->SetCollider(scaleMatrix_Player, transMatrix_Player, rotateMatrix_Player);

	//고정 버전 콜라이더

	


	//seabox
	scaleMatrix_SeaBox = XMMatrixScaling(1024.0f, 1024.0f, 1024.0f);
	transMatrix_SeaBox = XMMatrixTranslation(XMVectorGetX(playerPosition), XMVectorGetY(playerPosition), XMVectorGetZ(playerPosition));

	worldMatrix_SeaBox = scaleMatrix_SeaBox * transMatrix_SeaBox;	//srt

	//seaweed
	XMFLOAT3 seaWeedPos;
	double seaWeedAngle;
	float seaWeedRotation;
	for (int i = 0; i < 10; i++)
	{
		scaleMatrix_SeaWeed[i] = XMMatrixScaling(50.0f, 200.0f, 50.0f);

		XMStoreFloat3(&seaWeedPos, seaWeedPosition[i]);
		transMatrix_SeaWeed[i] = XMMatrixTranslation(seaWeedPos.x, seaWeedPos.y, seaWeedPos.z);
		//double seaWeedAngle = atan2(seaWeedPos.x - Camera_Pos.x, seaWeedPos.z - Camera_Pos.z) * (180.0 / XM_PI);
		seaWeedAngle = atan2(seaWeedPos.z - Camera_Pos.z, seaWeedPos.x - Camera_Pos.x) * (180.0 / XM_PI) * -1;
		//if (seaWeedAngle > 0) seaWeedAngle *= -1;
		//printf("seaWeedAngle : %.1lf\n", seaWeedAngle);
		seaWeedRotation = (float)seaWeedAngle * 0.0174532925f;
		rotateMatrix_SeaWeed[i] = XMMatrixRotationY(seaWeedRotation);
	}
	

	// ground
	scaleMatrix_Ground = XMMatrixScaling(45.0f, 25.0f, 45.0f);
	transMatrix_Ground = XMMatrixTranslation(0.0f, -100.0f, 0.0f);
	rotateMatrix_Ground = XMMatrixRotationY(0);

	// shark
	scaleMatrix_Shark = XMMatrixScaling(10.0f, 10.0f, 10.0f);
	XMFLOAT3 sharkPos;
	XMStoreFloat3(&sharkPos, sharkPosition);
	transMatrix_Shark = XMMatrixTranslation(sharkPos.x, sharkPos.y, sharkPos.z);

	CrossLookAt(sharkPosition, playerPosition);
	rotateMatrix_Shark = MoveShark(m_SharkRadian->rightRadian, m_SharkRadian->upRadian, 0, moveLR, sharkBF, DefaultForward, DefaultRight, worldMatrix_Shark);

	// particle
	for (int i = 0; i < 3; i++)
	{
		//rotateMatrix_Particle[i] = XMMatrixRotationY(camYaw);
		//rotateMatrix_Particle[i] = XMMatrixRotationX(camPitch);
		//rotateMatrix_Particle[i] = rotateMatrix_Player;
		//rotateMatrix_Particle[i] = XMMatrixRotationY(XMConvertToRadians(180));
		transMatrix_Particle[i] = transMatrix_Player;
		transMatrix_Particle[i] *= XMMatrixTranslation(3.0f, 3.0f, 3.0f);	//상단 위치에서 좌표만큼 추가 이동
		scaleMatrix_Particle[i] = XMMatrixScaling(10.0f, 10.0f, 10.0f);
		rotateMatrix_Particle[i] = XMMatrixRotationRollPitchYaw(camPitch, camYaw, playerRoll);
		worldMatrix_Particle[i] = scaleMatrix_Particle[i] * rotateMatrix_Particle[i] * transMatrix_Particle[i];
	}

	// stone
	{
		scaleMatrix_Stone[0] = XMMatrixScaling(50.0f, 75.0f, 50.0f);
		rotateMatrix_Stone[0] = XMMatrixRotationY(0);
		transMatrix_Stone[0] = XMMatrixTranslation(-740.0f, -50.0f, -840.0f);

		scaleMatrix_Stone[1] = XMMatrixScaling(75.0f, 90.0f, 75.0f);
		rotateMatrix_Stone[1] = XMMatrixRotationY(90);
		transMatrix_Stone[1] = XMMatrixTranslation(305.0f, -25.0f, -490.0f);

		scaleMatrix_Stone[2] = XMMatrixScaling(75.0f, 75.0f, 75.0f);
		rotateMatrix_Stone[2] = XMMatrixRotationY(45);
		transMatrix_Stone[2] = XMMatrixTranslation(-560.0f, 0.0f, 230.0f);

		scaleMatrix_Stone[3] = XMMatrixScaling(90.0f, 90.0f, 90.0f);
		rotateMatrix_Stone[3] = XMMatrixRotationY(180);
		transMatrix_Stone[3] = XMMatrixTranslation(580.0f, -12.5f, 500.0f);

		num_stone = 4;
	}

	//smallfish
	XMFLOAT3 smallFishPos[5];
	for(int i = 0; i < 5; i++) XMStoreFloat3(&smallFishPos[i], smallFishPosition[i]);

	{
		scaleMatrix_SmallFish[0] = XMMatrixScaling(7.5f, 5.0f, 7.5f);
		scaleMatrix_SmallFish[1] = XMMatrixScaling(7.5f, 5.0f, 7.5f);
		scaleMatrix_SmallFish[2] = XMMatrixScaling(7.5f, 5.0f, 7.5f);
		scaleMatrix_SmallFish[3] = XMMatrixScaling(7.5f, 5.0f, 7.5f);
		scaleMatrix_SmallFish[4] = XMMatrixScaling(7.5f, 5.0f, 7.5f);


		for (int i = 0; i < 5; i++)
		{
			if (smallFishPos[i].x > 1350 || smallFishPos[i].x < -1350 ||
				smallFishPos[i].z > 1350 || smallFishPos[i].z < -1350 ||
				smallFishPos[i].y > 1350 || smallFishPos[i].y < 0)
			{
				smallFishCollision[i] = true;
			}
		}

		for (int i = 0; i < 5; i++)
		{
			rotateMatrix_SmallFish[i] = MoveSmallFish(smallFishYaw[i], 0, 0, 0, smallFishBF[i], DefaultForward, DefaultRight, worldMatrix_SmallFish[i], i);
			transMatrix_SmallFish[i] = XMMatrixTranslation(smallFishPos[i].x, smallFishPos[i].y, smallFishPos[i].z);
		}
		num_smallFish = 5;
	}

	objNum = 0;
	//render + collider

	//seabox
	m_D3D->TurnOffCulling();
	m_D3D->TurnDSLessEqualOn();

	m_SeaBox->Render(m_D3D->GetDeviceContext(), worldMatrix_SeaBox, viewMatrix, projectionMatrix);

	// 안개 셰이더 렌더
	//result = m_FogShader->Render(m_D3D->GetDeviceContext(), m_SeaBox->GetIndexCount(), worldMatrix_SeaBox, viewMatrix, projectionMatrix, m_SeaBox->GetTexture(), fogStart, fogEnd);
	//if (!result) return false;
	objNum += 1;
	m_D3D->TurnDSLessEqualOff();
	m_D3D->TurnOnCulling();

	CollidObjNum = 0;
	for (int i = 0; i < num_stone; i++)
	{
		worldMatrix_Stone[i] = scaleMatrix_Stone[i] * rotateMatrix_Stone[i] * transMatrix_Stone[i];
		m_Stone->SetCollider(scaleMatrix_Stone[i], transMatrix_Stone[i], rotateMatrix_Stone[i]);

		isCollide = m_PlayableFish->checkCollider(m_Stone->GetMaxX(), m_Stone->GetMinX(), 
			m_Stone->GetMaxY(), m_Stone->GetMinY(), 
			m_Stone->GetMaxZ(), m_Stone->GetMinZ());

		if (isCollide)
		{
			printf("돌과 충돌\n");
			CollidObjNum = 1;
		}
	}
	objNum += num_stone;
	for (int i = 0; i < num_smallFish; i++)
	{
		worldMatrix_SmallFish[i] = scaleMatrix_SmallFish[i] * rotateMatrix_SmallFish[i] * transMatrix_SmallFish[i];
		m_SmallFish->SetCollider(scaleMatrix_SmallFish[i], transMatrix_SmallFish[i], rotateMatrix_SmallFish[i]);
		isCollide = m_PlayableFish->checkCollider(m_SmallFish->GetMaxX(), m_SmallFish->GetMinX(),
			m_SmallFish->GetMaxY(), m_SmallFish->GetMinY(),
			m_SmallFish->GetMaxZ(), m_SmallFish->GetMinZ());

		if (isCollide && !smallFishDestroyed[i])
		{
			printf("작은 물고기와 충돌\n");
			CollidObjNum = 2;
			m_score += 4;
			smallFishDestroyed[i] = true;
			ParticleTime[0] = m_time;
			smallFishRespawn[i] = m_time;
		}
	}

	for (int i = 0; i < num_smallFish; i++)
	{
		if (smallFishDestroyed[i] && smallFishRespawn[i] != 0.0f && smallFishRespawn[i] + 5.0f <= m_time)
		{
			smallFishDestroyed[i] = false;
			smallFishRespawn[i] = 0.0f;
		}
	}
	
	for (int i = 0; i < num_smallFish; i++)
	{
		if(!smallFishDestroyed[i]) objNum += 1;
	}

	worldMatrix_Shark = scaleMatrix_Shark * rotateMatrix_Shark * transMatrix_Shark;
	m_Shark->SetCollider(scaleMatrix_Shark, transMatrix_Shark, rotateMatrix_Shark);

	isCollide = m_PlayableFish->checkCollider(m_Shark->GetMaxX(), m_Shark->GetMinX(),
		m_Shark->GetMaxY(), m_Shark->GetMinY(),
		m_Shark->GetMaxZ(), m_Shark->GetMinZ());

	if (isCollide && CollidObjNum == 0 && moveBF != 2.0f)
	{
		printf("상어와 충돌\n");
		CollidObjNum = 3;
		m_hp -= 6;
		ParticleTime[1] = m_time;
	}
	objNum += 1;

	worldMatrix_Ground = scaleMatrix_Ground * rotateMatrix_Ground * transMatrix_Ground;
	m_Ground->SetCollider(scaleMatrix_Ground, transMatrix_Ground, rotateMatrix_Ground);

	isCollide = m_PlayableFish->checkCollider(m_Ground->GetMaxX(), m_Ground->GetMinX(),
		m_Ground->GetMaxY(), m_Ground->GetMinY(),
		m_Ground->GetMaxZ(), m_Ground->GetMinZ());

	if (isCollide)
	{
		printf("지형과 충돌\n");
		CollidObjNum = 4;
	}
	objNum += 1;

	for (int i = 0; i < 10; i++)
	{
		worldMatrix_SeaWeed[i] = scaleMatrix_SeaWeed[i] * rotateMatrix_SeaWeed[i] * transMatrix_SeaWeed[i];
		m_BillboardModel->SetCollider(scaleMatrix_SeaWeed[i], transMatrix_SeaWeed[i], rotateMatrix_SeaWeed[i]);
		objNum += 1;
	}



	// Rotate the world matrix by the rotation value so that the triangle will spin.
	//worldMatrix = XMMatrixRotationY(rotation);
	TextRotate = worldMatrix;

	//TextRotate = XMMatrixRotationY(3.1f);	//3.1f
	//printf("%.1lf\n", rotation);
	TextRotate = XMMatrixRotationY(XMConvertToRadians(180));
	worldMatrix = TextRotate;

	moveLR = 0.0f;
	moveBF = 0.0f;
	//sharkBF = 0.0f;

	//ground
	m_Ground->Render(m_D3D->GetDeviceContext());

	// 안개 셰이더 렌더
	//result = m_FogShader->Render(m_D3D->GetDeviceContext(), m_Ground->GetIndexCount(), worldMatrix_Ground, viewMatrix, projectionMatrix, m_Ground->GetTexture(), fogStart, fogEnd);
	//if (!result) return false;

	// Render the model using the light shader.
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Ground->GetIndexCount(),
		worldMatrix_Ground, viewMatrix, projectionMatrix,
		m_Ground->GetTexture(),
		m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower(), rotateMatrix_Ground);

	//shark
	m_Shark->Render(m_D3D->GetDeviceContext());

	// 안개 셰이더 렌더
	//result = m_FogShader->Render(m_D3D->GetDeviceContext(), m_Shark->GetIndexCount(), worldMatrix_Shark, viewMatrix, projectionMatrix, m_Shark->GetTexture(), fogStart, fogEnd);
	//if (!result) return false;

	// Render the model using the light shader.
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Shark->GetIndexCount(),
		worldMatrix_Shark, viewMatrix, projectionMatrix,
		m_Shark->GetTexture(),
		m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower(), rotateMatrix_Shark);

	//stone
	for (int i = 0; i < num_stone; i++)
	{
		m_Stone->Render(m_D3D->GetDeviceContext());

		// 안개 셰이더 렌더
		//result = m_FogShader->Render(m_D3D->GetDeviceContext(), m_Stone->GetIndexCount(), worldMatrix_Stone[i], viewMatrix, projectionMatrix, m_Stone->GetTexture(), fogStart, fogEnd);
		//if (!result) return false;

		// Render the model using the light shader.
		result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Shark->GetIndexCount(),
			worldMatrix_Stone[i], viewMatrix, projectionMatrix,
			m_Stone->GetTexture(),
			m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
			m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower(), rotateMatrix_Stone[i]);
	}

	//smallfish
	for (int i = 0; i < num_smallFish; i++)
	{
		if (!smallFishDestroyed[i])
		{
			m_SmallFish->Render(m_D3D->GetDeviceContext());

			// 안개 셰이더 렌더
			//result = m_FogShader->Render(m_D3D->GetDeviceContext(), m_SmallFish->GetIndexCount(), worldMatrix_SmallFish[i], viewMatrix, projectionMatrix, m_SmallFish->GetTexture(), fogStart, fogEnd);
			//if (!result) return false;

			// Render the model using the light shader.
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_SmallFish->GetIndexCount(),
				worldMatrix_SmallFish[i], viewMatrix, projectionMatrix,
				m_SmallFish->GetTexture(),
				m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
				m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower(), rotateMatrix_SmallFish[i]);
		}
	}

	// Turn on the alpha blending before rendering the text.
	m_D3D->TurnOnAlphaBlending();
	m_D3D->TurnOffCulling();
	for (int i = 0; i < 10; i++)
	{
		// 모델의 정점 및 인덱스 버퍼를 파이프라인에 넣어 그릴 준비를 합니다. 
		m_BillboardModel->Render(m_D3D->GetDeviceContext());

		// 안개 셰이더 렌더
		//result = m_FogShader->Render(m_D3D->GetDeviceContext(), m_BillboardModel->GetIndexCount(), worldMatrix_SeaWeed[i], viewMatrix, projectionMatrix, m_BillboardModel->GetTexture(), fogStart, fogEnd);
		//if (!result) return false;

		// 텍스쳐 셰이더를 이용하여 모델을 그립니다. 
		result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_BillboardModel->GetIndexCount(), worldMatrix_SeaWeed[i], viewMatrix, projectionMatrix,
			m_BillboardModel->GetTexture());
		if (!result)
		{
			return false;
		}
	}

	m_D3D->TurnOnCulling();
	m_D3D->TurnOffAlphaBlending();
	// Turn off the Z buffer to begin all 2D rendering.
	m_D3D->TurnZBufferOff();

	// Turn on the alpha blending before rendering the text.
	m_D3D->TurnOnAlphaBlending();

	// Render the text strings.
	result = m_Text->Render(m_D3D->GetDeviceContext(), worldMatrix, orthoMatrix);
	if (!result)
	{
		return false;
	}

	m_D3D->TurnOffCulling();

	if (m_ParticleSystem[0]->OnParticle == false)
	{
		m_ParticleSystem[0]->TurnOnParticle(0);
		m_ParticleSystem[0]->OnParticle = true;
	}
	// 파티클 시스템 버텍스와 인덱스 버퍼를 그래픽 파이프 라인에 배치하여 그리기를 준비합니다.
	m_ParticleSystem[0]->Render(m_D3D->GetDeviceContext());

	// 텍스처 셰이더를 사용하여 모델을 렌더링합니다.
		if (!m_ParticleShader->Render(m_D3D->GetDeviceContext(), m_ParticleSystem[0]->GetIndexCount(), worldMatrix_Particle[0], viewMatrix, projectionMatrix,
			m_ParticleSystem[0]->GetTexture()))
		{
			return false;
		}

	for (int i = 0; i < 2; i++)
	{
		if (ParticleTime[i] != 0.0f && ParticleTime[i] + 1.0f >= m_time)
		{
			if (m_ParticleSystem[i + 1]->OnParticle == false)
			{
				m_ParticleSystem[i + 1]->TurnOnParticle(i + 1);
				m_ParticleSystem[i + 1]->OnParticle = true;
			}
			// 파티클 시스템 버텍스와 인덱스 버퍼를 그래픽 파이프 라인에 배치하여 그리기를 준비합니다.
			m_ParticleSystem[i + 1]->Render(m_D3D->GetDeviceContext());

			// 텍스처 셰이더를 사용하여 모델을 렌더링합니다.
			if (!m_ParticleShader->Render(m_D3D->GetDeviceContext(), m_ParticleSystem[i + 1]->GetIndexCount(), worldMatrix_Particle[i + 1], viewMatrix, projectionMatrix,
				m_ParticleSystem[i + 1]->GetTexture()))
			{
				return false;
			}
		}
		else if (ParticleTime[i] != 0.0f)
		{
			if (m_ParticleSystem[i + 1]->OnParticle)
			{
				m_ParticleSystem[i + 1]->TurnOffParticle(i + 1);
				m_ParticleSystem[i + 1]->OnParticle = false;
			}
			ParticleTime[i] = 0.0f;
		}
		else
		{
			if (m_ParticleSystem[i + 1]->OnParticle)
			{
				m_ParticleSystem[i + 1]->TurnOffParticle(i + 1);
				m_ParticleSystem[i + 1]->OnParticle = false;
			}
		}
	}

	m_D3D->TurnOnCulling();

	// Turn off alpha blending after rendering the text.
	m_D3D->TurnOffAlphaBlending();

	// Turn the Z buffer back on now that all 2D rendering has completed.
	m_D3D->TurnZBufferOn();

	
	m_D3D->TurnOffCulling();
	//player
	m_PlayableFish->Render(m_D3D->GetDeviceContext());

	// 안개 셰이더 렌더
	//result = m_FogShader->Render(m_D3D->GetDeviceContext(), m_PlayableFish->GetIndexCount(), worldMatrix_Player, viewMatrix, projectionMatrix, m_PlayableFish->GetTexture(), fogStart, fogEnd);
	//if (!result) return false;

	// Render the model using the light shader.
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_PlayableFish->GetIndexCount(),
		worldMatrix_Player, viewMatrix, projectionMatrix,
		m_PlayableFish->GetTexture(),
		m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower(), rotateMatrix_Player);
	objNum += 1;

	m_D3D->TurnOnCulling();

	// Present the rendered scene to the screen.
	m_D3D->EndScene();
	
	return true;
}

XMMATRIX GraphicsClass::MoveChar(float playerYaw, float playerPitch, float playerRoll, float moveLR, float moveBF, 
								XMVECTOR DefaultForward, XMVECTOR DefaultRight, XMMATRIX& worldMatrix)
{
	XMMATRIX rotateMatrix_Player;

	rotateMatrix_Player = XMMatrixRotationRollPitchYaw(playerPitch, playerYaw, playerRoll);

	playerTarget = XMVector3TransformNormal(DefaultForward, rotateMatrix_Player);

	playerRight = XMVector3TransformCoord(DefaultRight, rotateMatrix_Player);
	playerForward = XMVector3TransformCoord(DefaultForward, rotateMatrix_Player);
	playerUp = XMVector3Cross(playerForward, playerRight);

	playerPosition += moveLR * playerRight;
	playerPosition += moveBF * playerForward;

	playerTarget = playerPosition + playerTarget;

	transMatrix_Player = XMMatrixTranslation(XMVectorGetX(playerPosition), XMVectorGetY(playerPosition), XMVectorGetZ(playerPosition));
	
	XMFLOAT3 playerPos;
	XMStoreFloat3(&playerPos, playerPosition);
	float x = playerPos.x;
	float y = playerPos.y;
	float z = playerPos.z;
	playerX = (int)x;
	playerY = (int)y;
	playerZ = (int)z;
	//printf("%d, %d, %d\n", playerX, playerY, playerZ);
	worldMatrix = scaleMatrix_Player * rotateMatrix_Player * transMatrix_Player;

	//m_PlayableFish->SetCollider(scaleMatrix_Player, transMatrix_Player, rotateMatrix_Player);

	return rotateMatrix_Player;
}

XMMATRIX GraphicsClass::MoveShark(float sharkYaw, float sharkPitch, float sharkRoll, float moveLR, float moveBF,
	XMVECTOR DefaultForward, XMVECTOR DefaultRight, XMMATRIX& worldMatrix)
{
	XMMATRIX rotateMatrix_Shark;

	rotateMatrix_Shark = XMMatrixRotationRollPitchYaw(sharkPitch, sharkYaw, sharkRoll);

	sharkTarget = XMVector3TransformNormal(DefaultForward, rotateMatrix_Shark);

	sharkRight = XMVector3TransformCoord(DefaultRight, rotateMatrix_Shark);
	sharkForward = XMVector3TransformCoord(DefaultForward, rotateMatrix_Shark);
	sharkUp = XMVector3Cross(sharkForward, sharkRight);

	sharkPosition += moveLR * sharkRight;
	sharkPosition += moveBF * sharkForward;

	sharkTarget = sharkPosition + sharkTarget;

	transMatrix_Shark = XMMatrixTranslation(XMVectorGetX(sharkPosition), XMVectorGetY(sharkPosition), XMVectorGetZ(sharkPosition));

	XMFLOAT3 sharkPos;
	XMStoreFloat3(&sharkPos, sharkPosition);
	float x = sharkPos.x;
	float y = sharkPos.y;
	float z = sharkPos.z;
	sharkX = (int)x;
	sharkY = (int)y;
	sharkZ = (int)z;
	//printf("%d, %d, %d\n", playerX, playerY, playerZ);
	//worldMatrix = scaleMatrix_Player * rotateMatrix_Player * transMatrix_Player;

	//m_PlayableFish->SetCollider(scaleMatrix_Player, transMatrix_Player, rotateMatrix_Player);

	return rotateMatrix_Shark;
}

XMMATRIX GraphicsClass::MoveSmallFish(float smallFishYaw, float smallFishPitch, float smallFishRoll, float moveLR, float moveBF,
	XMVECTOR DefaultForward, XMVECTOR DefaultRight, XMMATRIX& worldMatrix, int index)
{
	XMMATRIX rotateMatrix_SmallFish;

	rotateMatrix_SmallFish = XMMatrixRotationRollPitchYaw(smallFishPitch, smallFishYaw, smallFishRoll);

	smallFishTarget = XMVector3TransformNormal(DefaultForward, rotateMatrix_SmallFish);

	smallFishRight = XMVector3TransformCoord(DefaultRight, rotateMatrix_SmallFish);
	smallFishForward = XMVector3TransformCoord(DefaultForward, rotateMatrix_SmallFish);
	smallFishUp = XMVector3Cross(smallFishForward, smallFishRight);

	smallFishPosition[index] += moveLR * smallFishRight;
	smallFishPosition[index] += moveBF * smallFishForward;

	smallFishTarget = smallFishPosition[index] + smallFishTarget;

	transMatrix_SmallFish[index] = XMMatrixTranslation(XMVectorGetX(smallFishPosition[index]), XMVectorGetY(smallFishPosition[index]), XMVectorGetZ(smallFishPosition[index]));

	XMFLOAT3 smallFishPos;
	XMStoreFloat3(&smallFishPos, smallFishPosition[index]);
	float x = smallFishPos.x;
	float y = smallFishPos.y;
	float z = smallFishPos.z;
	smallFishX[index] = (int)x;
	smallFishY[index] = (int)y;
	smallFishZ[index] = (int)z;

	return rotateMatrix_SmallFish;
}

void GraphicsClass::CrossLookAt(XMVECTOR sharkPos, XMVECTOR playerPos)
{
	XMVECTOR Cross_Dir;
	XMVECTOR Cross_Up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	XMVECTOR Cross_Right = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	XMVECTOR Cross_Front = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);

	//crossForward = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	//crossRight = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	//crossUp = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	Cross_Dir = playerPos - sharkPos;
	crossForward = XMVector3Normalize(crossForward);
	crossRight = XMVector3Normalize(crossRight);
	crossUp = XMVector3Normalize(crossUp);
	Cross_Dir = XMVector3Normalize(Cross_Dir);

	XMVECTOR dot[2];
	XMVECTOR radian[2];
	float radian_Float[2];

	dot[0] = XMVector3Dot(crossForward, Cross_Dir);			dot[1] = XMVector3Dot(crossUp, Cross_Dir);
	radian[0] = XMVectorACos(dot[0]);						radian[1] = XMVectorATan(dot[1]);
	radian_Float[0] = XMVectorGetX(radian[0]);				radian_Float[1] = XMVectorGetX(radian[1]);

	crossForward = XMVector3Cross(Cross_Right, Cross_Up);		crossUp = XMVector3Cross(Cross_Front, Cross_Right);

	if (XMVectorGetX(XMVector3Dot(crossRight, Cross_Dir)) < 0) radian_Float[0] *= -1;

	radian_Float[1] *= -1;

	//if (XMVectorGetX(XMVector3Dot(crossForward, Cross_Dir)) < 0) radian_Float[1] *= -1;
	
	m_SharkRadian->rightRadian = radian_Float[0];
	m_SharkRadian->upRadian = radian_Float[1];
}

void GraphicsClass::SmallFishRotate(float angle, int index)
{
	if (smallFishYaw[index] > 0) angle *= -1;
	smallFishYaw[index] = XMConvertToRadians(angle);
}

int GraphicsClass::GetScore()
{
	return m_score;
}

void GraphicsClass::RestartScene()
{
	desiredCharDir = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	playerPosition = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	sharkPosition = XMVectorSet(100.0f, 550.0f, 350.0f, 0.0f);

	smallFishPosition[0] = XMVectorSet(-500.0f, 150.0f, -200.0f, 0.0f);
	smallFishPosition[1] = XMVectorSet(-100.0f, 200.0f, -500.0f, 0.0f);
	smallFishPosition[2] = XMVectorSet(200.0f, 300.0f, 300.0f, 0.0f);
	smallFishPosition[3] = XMVectorSet(-200.0f, 100.0f, -250.0f, 0.0f);
	smallFishPosition[4] = XMVectorSet(400.0f, 250.0f, 450.0f, 0.0f);

	smallFishYaw[0] = -90.0f;
	smallFishYaw[1] = 45.0f;
	smallFishYaw[2] = -45.0f;
	smallFishYaw[3] = 0.0f;
	smallFishYaw[4] = 180.0f;

	crossForward = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	crossRight = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	crossUp = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	DefaultForward = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	DefaultRight = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);

	CamDefaultForward = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	CamDefaultRight = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);

	playerTarget = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);

	playerUp = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	playerForward = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	playerRight = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);

	sharkTarget = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);

	sharkUp = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	sharkForward = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	sharkRight = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);

	smallFishTarget = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);

	smallFishUp = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	smallFishForward = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	smallFishRight = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);

	RotateYaw = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	RotatePitch = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	RotateRoll = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);

	XMStoreFloat3(&m_playerPosition, playerPosition);
	XMStoreFloat3(&m_sharkPosition, sharkPosition);

	CollidObjNum = 0;
	m_time = 0.0f;
	frameTime = 0.0f;
	m_score = 0;
	m_hp = 20;
	m_playerPos = 0;
	playerX = 0;
	playerY = 0;
	playerZ = 0;

	fogColor = 0.0f;
	fogStart = 0.0f;
	fogEnd = 0.0f;

	sharkX = 0;
	sharkY = 0;
	sharkZ = 0;

	ParticleTime[0] = 0;
	ParticleTime[1] = 0;

	for (int i = 0; i < 5; i++)
	{
		smallFishDestroyed[i] = false;
		smallFishX[i] = 0;
		smallFishY[i] = 0;
		smallFishZ[i] = 0;
		smallFishBF[i] = -1.0f;
		smallFishCollision[i] = false;
		smallFishRespawn[i] = 0.0f;
	}
}