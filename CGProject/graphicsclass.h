////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "d3dclass.h"
#include "cameraclass.h"
#include "modelclass.h"
#include "lightshaderclass.h"
#include "lightclass.h"

#include "textureshaderclass.h"
#include "bitmapclass.h"
#include "textclass.h"
#include "ParticleSystemClass.h"
#include "ParticleShaderClass.h"
#include "fogshaderclass.h"
#include "skymapclass.h"
#include "timerclass.h"
#include <cmath>
/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 3000.0f;
const float SCREEN_NEAR = 0.1f;

//class ParticleShaderClass;
//class ParticleSystemClass;
// 
////////////////////////////////////////////////////////////////////////////////
// Class name: GraphicsClass
////////////////////////////////////////////////////////////////////////////////
class GraphicsClass
{
public:

	struct RadianType
	{
		float upRadian, rightRadian;
	};
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Frame();
	bool Frame(int, int, float);
	bool Frame(int, int);
	void SmallFishRotate(float, int);
	int GetScore();
	void RestartScene();

	float moveLR = 0.0f;
	float moveBF = 0.0f;

	float sharkBF = 0.0f;
	float smallFishBF[5];

	float camRotateInfoYaw = 0.0f;
	float camRotateInfoPitch = 0.0f;

	float playerYaw = 0.0f;
	float playerPitch = 0.0f;
	float playerRoll = 0.0f;

	float camYaw = 0.0f;
	float camPitch = 0.0f;

	//bool isSpacePressed = false;
	bool isCollide = false;
	int CollidObjNum;
	bool smallFishDestroyed[5];
	bool smallFishCollision[5];
	float smallFishYaw[5];
	float smallFishRespawn[5];

	float ParticleTime[2];

	XMVECTOR desiredCharDir;
	XMVECTOR playerPosition;
	XMVECTOR sharkPosition;
	XMVECTOR smallFishPosition[5];
	XMVECTOR seaWeedPosition[10];

	XMFLOAT3 m_playerPosition;
	XMFLOAT3 m_sharkPosition;

	XMVECTOR crossForward;
	XMVECTOR crossRight;
	XMVECTOR crossUp;

	float m_time;
	bool sceneFlag[3];		// 0 : title, 1 : ingame, 2 : Result
	int m_score;
	int m_hp;

	bool restartFlag;
private:
	bool RenderIngameScene(float);
	bool RenderTitleScene();
	bool RenderResultScene();
	XMMATRIX MoveChar(float, float, float, float, float, XMVECTOR, XMVECTOR, XMMATRIX&);
	XMMATRIX MoveShark(float, float, float, float, float, XMVECTOR, XMVECTOR, XMMATRIX&);
	XMMATRIX MoveSmallFish(float, float, float, float, float, XMVECTOR, XMVECTOR, XMMATRIX&, int);
	void CrossLookAt(XMVECTOR, XMVECTOR);
private:
	D3DClass* m_D3D;
	CameraClass* m_Camera;
	ModelClass* m_Ground;
	ModelClass* m_Stone;
	ModelClass* m_PlayableFish;
	ModelClass* m_SmallFish;
	ModelClass* m_Shark;
	ModelClass* m_BillboardModel;
	SkymapClass* m_SeaBox;

	LightShaderClass* m_LightShader;
	LightClass* m_Light;

	TextureShaderClass* m_TextureShader;
	BitmapClass* m_Bitmap;
	BitmapClass* m_BitmapSuccess;
	BitmapClass* m_BitmapFail;

	TextClass* m_Text;

	ParticleShaderClass* m_ParticleShader;
	ParticleSystemClass* m_ParticleSystem[3];

	FogShaderClass* m_FogShader;

	int num_stone = 0;
	int num_smallFish = 0;
	float m_indexCount = 0.0f;
	int objNum = 0;
	float frameTime;
	int m_screenWidth;
	int m_screenHeight;
	int m_playerPos;
	int playerX, playerY, playerZ;
	int sharkX, sharkY, sharkZ;
	int seaWeedX, seaWeedY, seaWeedZ;
	int smallFishX[5], smallFishY[5], smallFishZ[5];

	float fogColor;
	float fogStart;
	float fogEnd;
	XMVECTOR DefaultForward;
	XMVECTOR DefaultRight;

	XMVECTOR CamDefaultForward;
	XMVECTOR CamDefaultRight;

	XMVECTOR playerTarget;
	XMVECTOR playerUp;

	XMVECTOR playerForward;
	XMVECTOR playerRight;

	XMVECTOR RotateYaw;
	XMVECTOR RotatePitch;
	XMVECTOR RotateRoll;

	float charCamDist = 50.0f;

	XMMATRIX transMatrix_Player;
	XMMATRIX rotateMatrix_Player;
	XMMATRIX scaleMatrix_Player;

	RadianType* m_SharkRadian;

	XMVECTOR sharkTarget;
	XMVECTOR sharkUp;

	XMVECTOR sharkForward;
	XMVECTOR sharkRight;

	XMMATRIX transMatrix_Shark;
	XMMATRIX rotateMatrix_Shark;
	XMMATRIX scaleMatrix_Shark;

	XMMATRIX transMatrix_SeaWeed[10];
	XMMATRIX rotateMatrix_SeaWeed[10];
	XMMATRIX scaleMatrix_SeaWeed[10];

	XMVECTOR smallFishTarget;
	XMVECTOR smallFishUp;

	XMVECTOR smallFishForward;
	XMVECTOR smallFishRight;

	XMMATRIX transMatrix_SmallFish[5];
	XMMATRIX scaleMatrix_SmallFish[5];
	XMMATRIX rotateMatrix_SmallFish[5];
};
#endif