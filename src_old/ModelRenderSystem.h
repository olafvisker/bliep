#pragma once
#include "System.h"

class Entity;
class CameraSystem;
class Camera;
class Transform;
class Mesh;
class LightSystem;
class Light;

class ModelRenderSystem : public System
{
public:
	ModelRenderSystem();
	~ModelRenderSystem();

	void InitializeSystem();
	void Initialize(Entity& entity) { }
	void Process(float deltaTime, Entity& entity);

private:
	CameraSystem* m_cameraSystem;
	LightSystem* m_lightSystem;

	void BindCamera(Camera* camera);
	void SetCameraUniforms(Material* material, Transform* meshTransform, Transform* cameraTransform, Camera* camera);
	void SetLightUniforms(Light* light, Transform* transform, Material* material);
	void DrawMesh(Mesh* mesh);
};