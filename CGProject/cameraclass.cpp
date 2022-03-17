////////////////////////////////////////////////////////////////////////////////
// Filename: cameraclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "cameraclass.h"


CameraClass::CameraClass()
{
	m_position.x = 0.0f;
	m_position.y = 0.0f;
	m_position.z = 0.0f;

	m_rotation.x = 0.0f;
	m_rotation.y = 0.0f;
	m_rotation.z = 0.0f;
	
	camTarget = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	camUp = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	camForward = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	camRight = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
}


CameraClass::CameraClass(const CameraClass& other)
{
}


CameraClass::~CameraClass()
{
}


void CameraClass::SetPosition(float x, float y, float z)
{
	m_position.x = x;
	m_position.y = y;
	m_position.z = z;
}


void CameraClass::SetRotation(float x, float y, float z)
{
	m_rotation.x = x;
	m_rotation.y = y;
	m_rotation.z = z;
}


XMFLOAT3 CameraClass::GetPosition()
{
	return m_camPosition;
}


XMFLOAT3 CameraClass::GetRotation()
{
	return m_rotation;
}

// This uses the position and rotation of the camera to build and to update the view matrix.
void CameraClass::Render()
{
	XMVECTOR up, position, lookAt;
	float yaw, pitch, roll;
	XMMATRIX rotationMatrix;

	// Setup the vector that points upwards.
	up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	// Setup the position of the camera in the world.
	position = XMLoadFloat3(&m_position);

	// Setup where the camera is looking by default.
	lookAt = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);

	// Set the yaw (Y axis), pitch (X axis), and roll (Z axis) rotations in radians.
	pitch = m_rotation.x * 0.0174532925f;
	yaw   = m_rotation.y * 0.0174532925f;
	roll  = m_rotation.z * 0.0174532925f;

	// Create the rotation matrix from the yaw, pitch, and roll values.
	rotationMatrix = XMMatrixRotationRollPitchYaw(pitch, yaw, roll);

	// Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
	lookAt = XMVector3TransformCoord(lookAt, rotationMatrix);
	up = XMVector3TransformCoord(up, rotationMatrix);

	// Translate the rotated camera position to the location of the viewer.
	lookAt = position + lookAt;

	// Finally create the view matrix from the three updated vectors.
	m_viewMatrix = XMMatrixLookAtLH(position, lookAt, up);

	return;
}

void CameraClass::Render(float camYaw, float camPitch, float moveLR, float moveBF,
	XMVECTOR DefaultForward, XMVECTOR DefaultRight, XMVECTOR charPosition, float camDist)
{
	XMMATRIX camRotateMatrix;

	camTarget = charPosition;

	XMStoreFloat3(&m_camTarget, camTarget);
	m_camTarget.y = m_camTarget.y + 12.0f;
	camTarget = XMLoadFloat3(&m_camTarget);

	camRotateMatrix = XMMatrixRotationRollPitchYaw(camPitch, camYaw, 0);
	camPosition = XMVector3TransformNormal(DefaultForward, camRotateMatrix);
	camPosition = XMVector3Normalize(camPosition);

	XMStoreFloat3(&m_camPosition, camPosition);
	XMStoreFloat3(&m_camTarget, camTarget);

	m_camPosition.x = (m_camPosition.x * camDist) + m_camTarget.x;
	m_camPosition.y = (m_camPosition.y * camDist) + m_camTarget.y;
	m_camPosition.z = (m_camPosition.z * camDist) + m_camTarget.z;

	camPosition = XMLoadFloat3(&m_camPosition);
	camTarget = XMLoadFloat3(&m_camTarget);

	XMFLOAT3 Tar_Pos(m_camTarget.x - m_camPosition.x, m_camTarget.y - m_camPosition.y, m_camTarget.z - m_camPosition.z);
	XMVECTOR Tar_Pos_Vec = XMLoadFloat3(&Tar_Pos);
	camForward = XMVector3Normalize(Tar_Pos_Vec);

	camForward = XMVector3Normalize(camForward);
	XMStoreFloat3(&m_camForward, camForward);
	camRight = XMVectorSet(-m_camForward.z, 0.0f, m_camForward.x, 0.0f);
	
	XMFLOAT3  Pos_Tar(m_camPosition.x - m_camTarget.x, m_camPosition.y - m_camTarget.y, m_camPosition.z - m_camTarget.z);
	XMVECTOR Pos_Tar_Vec = XMLoadFloat3(&Pos_Tar);
	Pos_Tar_Vec = XMVector3Normalize(Pos_Tar_Vec);

	camUp = XMVector3Normalize(XMVector3Cross(Pos_Tar_Vec, camRight));

	m_viewMatrix = XMMatrixLookAtLH(camPosition, camTarget, camUp);
}


void CameraClass::GetViewMatrix(XMMATRIX& viewMatrix)
{
	viewMatrix = m_viewMatrix;
}