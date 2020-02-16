#include <glm/gtc/matrix_transform.hpp>

#include "CameraSystem.h"
#include "Camera.h"
#include "Transform.h"
#include "Component.h"
#include "Entity.h"
#include "Math.h"

CameraSystem::CameraSystem()
{
	RegisterRequired(ComponentType::COM_TRANSFORM);
	RegisterRequired(ComponentType::COM_CAMERA);
}

CameraSystem::~CameraSystem()
{ }

void CameraSystem::Process(float deltaTime, Entity& entity)
{
	Camera* camera = (Camera*)entity.GetComponent<Camera>();
	Transform* transform = (Transform*)entity.GetComponent<Transform>();
}

float CameraSystem::CameraAspectRatio(Camera* camera) 
{ 
	if (camera->GetRenderWidth() != 0 && camera->GetRenderHeight() != 0)
		return (float)camera->GetRenderWidth() / (float)camera->GetRenderHeight();
	return GetEngine().GetDisplay().GetWindowAspectRatio();
}

glm::mat4 CameraSystem::Projection(Camera* camera)
{
	return glm::perspective(glm::radians(camera->FieldOfView()), CameraAspectRatio(camera),
		camera->NearPlane(), camera->FarPlane());
}

glm::mat4 CameraSystem::View(Transform* transform)
{
	return glm::lookAt(transform->Position(), transform->Position() + Math::Forward(transform->Rotation()), Math::Up());
}