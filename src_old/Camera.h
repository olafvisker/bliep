#include "Component.h"

class Camera : public Component
{
	friend class CameraSystem;
public:
	Camera() : Component(ComponentType::COM_CAMERA) { }
	~Camera() { }

	void SetRenderBounderies(int x, int y, unsigned int width, unsigned int height);

	float& FieldOfView()	{ return m_fieldOfView; }
	float& NearPlane()		{ return m_nearPlane; }
	float& FarPlane()		{ return m_farPlane; }

	int GetRenderX()	{ return m_renderX; }
	int GetRenderY()	{ return m_renderY; }
	unsigned int GetRenderWidth()	{ return m_renderWidth; }
	unsigned int GetRenderHeight()	{ return m_renderHeight; }

private:
	float m_fieldOfView = 75.0f;
	float m_nearPlane = 0.1f;
	float m_farPlane = 10000.0f;

	int m_renderX = 0;
	int m_renderY = 0;
	unsigned int m_renderWidth	= 0;
	unsigned int m_renderHeight = 0;
};