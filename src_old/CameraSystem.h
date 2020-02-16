#pragma once
#include "System.h"

class Entity;
class Camera;
class Transform;

class CameraSystem : public System
{
public:
	CameraSystem();
	~CameraSystem();

	void InitializeSystem() { }
	void Initialize(Entity& entity) { }
	void Process(float deltaTime, Entity& entity);

	float CameraAspectRatio(Camera* camera);
	glm::mat4 CameraSystem::Projection(Camera* camera);
	glm::mat4 CameraSystem::View(Transform* transform);
};

