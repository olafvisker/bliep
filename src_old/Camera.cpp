#include "Camera.h"

void Camera::SetRenderBounderies(int x, int y, unsigned int width, unsigned int height)
{
	m_renderX = x;
	m_renderY = y;
	m_renderWidth = width;
	m_renderHeight = height;
}