#include "CameraControllerSystem.h"
#include "CameraController.h"
#include "Component.h"
#include "Transform.h"
#include "Entity.h"
#include "Math.h"

CameraControllerSystem::CameraControllerSystem()
{
	RegisterRequired(ComponentType::COM_TRANSFORM);
	RegisterRequired(ComponentType::COM_CAMERACONTROLLER);
}

CameraControllerSystem::~CameraControllerSystem()
{ }

void CameraControllerSystem::InitializeSystem()
{
	input = &GetEngine().GetInputManager();
}

void CameraControllerSystem::Process(float deltaTime, Entity& entity)
{
	Transform* transform = (Transform*)entity.GetComponent<Transform>();
	CameraController* cameraController = (CameraController*)entity.GetComponent<CameraController>();

	if (input->IsKeyDown(cameraController->ForwardKey()))
		transform->Position() += Math::Forward(transform->Rotation()) * cameraController->MovementSpeed() * deltaTime;
	if (input->IsKeyDown(cameraController->BackwardKey()))
		transform->Position() -= Math::Forward(transform->Rotation()) * cameraController->MovementSpeed() * deltaTime;
	if (input->IsKeyDown(cameraController->RightKey()))
		transform->Position() += Math::Right(transform->Rotation()) * cameraController->MovementSpeed() * deltaTime;
	if (input->IsKeyDown(cameraController->LeftKey()))
		transform->Position() -= Math::Right(transform->Rotation()) * cameraController->MovementSpeed() * deltaTime;
	if (input->IsKeyDown(cameraController->UpKey()))
		transform->Position() += Math::Up(transform->Rotation()) * cameraController->MovementSpeed() * deltaTime;
	if (input->IsKeyDown(cameraController->DownKey()))
		transform->Position() -= Math::Up(transform->Rotation())  * cameraController->MovementSpeed() * deltaTime;

	transform->Rotation().y += input->GetMouseDeltaX() * cameraController->RotationSpeed() * deltaTime;
	transform->Rotation().x += input->GetMouseDeltaY() * cameraController->RotationSpeed() * deltaTime;

	if (transform->Rotation().x > 89)
		transform->Rotation().x = 89;
	if (transform->Rotation().x < -89)
		transform->Rotation().x = -89;
}
