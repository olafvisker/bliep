#pragma once
#include "Component.h"

class CameraController : public Component
{
public:
	CameraController() : Component(ComponentType::COM_CAMERACONTROLLER) { }
	~CameraController() { }

	inline unsigned int& UpKey()		{ return m_upKey; }
	inline unsigned int& DownKey()		{ return m_downKey; }
	inline unsigned int& LeftKey()		{ return m_leftKey; }
	inline unsigned int& RightKey()		{ return m_rightKey; }
	inline unsigned int& ForwardKey()	{ return m_forwardKey; }
	inline unsigned int& BackwardKey()	{ return m_backwardKey; }

	inline float& MovementSpeed() { return m_movementSpeed; }
	inline float& RotationSpeed() { return m_rotationSpeed; }

	inline float& MaxPitch() { return m_maxPitch; }
	inline float& MinPitch() { return m_minPitch; }

private:
	unsigned int m_upKey = SDLK_e;
	unsigned int m_downKey = SDLK_q;
	unsigned int m_leftKey = SDLK_a;
	unsigned int m_rightKey = SDLK_d;
	unsigned int m_forwardKey = SDLK_w;
	unsigned int m_backwardKey = SDLK_s;

	float m_movementSpeed = 0.02f;
	float m_rotationSpeed = 0.3f;

	float m_maxPitch = 89.0f;
	float m_minPitch = -89.0f;
};