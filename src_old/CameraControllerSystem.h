#pragma once
#include "System.h"

class CameraControllerSystem : public System
{
public:
	CameraControllerSystem();
	~CameraControllerSystem();

	void InitializeSystem();
	void Initialize(Entity& entity) { }
	void Process(float deltaTime, Entity& entity);

private:
	InputManager* input;
};