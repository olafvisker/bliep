#include <GLM/glm.hpp>
#include <GL/glew.h>

#include "ModelRenderSystem.h"
#include "CameraSystem.h"
#include "LightSystem.h"
#include "ModelRenderer.h"
#include "Entity.h"
#include "Transform.h"
#include "Component.h"
#include "Camera.h"
#include "Light.h"
#include "Math.h"
#include "Logger.h"

ModelRenderSystem::ModelRenderSystem()
{
	RegisterRequired(ComponentType::COM_TRANSFORM);
	RegisterRequired(ComponentType::COM_MODELRENDERER);
}

ModelRenderSystem::~ModelRenderSystem()
{ }

void ModelRenderSystem::InitializeSystem()
{
	m_cameraSystem = (CameraSystem*)GetEngine().GetSystemManager().GetSystem<CameraSystem>();
	m_lightSystem = (LightSystem*)GetEngine().GetSystemManager().GetSystem<LightSystem>();
	if (m_lightSystem == nullptr)
		Logger::Log(LogLevel::LOG_WARNING, "No light system was found.");
}

void ModelRenderSystem::Process(float deltaTime, Entity& entity)
{
	ModelRenderer* modelRenderer = (ModelRenderer*)entity.GetComponent<ModelRenderer>();
	Transform* transform = (Transform*)entity.GetComponent<Transform>();

	if (m_cameraSystem != nullptr)
	{
		for (auto& e : m_cameraSystem->GetEntities())
		{
			Camera* camera = (Camera*)e.second->GetComponent<Camera>();
			Transform* cameraTransform = (Transform*)e.second->GetComponent<Transform>();

			BindCamera(camera);

			for (auto& m : modelRenderer->GetModel().Meshes())
			{//SET MAT PRAMS LIKE SHINE ASWELL
				Material* material = modelRenderer->GetModel().Materials().at(m->MaterialIndex());
				SetCameraUniforms(material, transform, cameraTransform, camera);

				if (m_lightSystem != nullptr && m_lightSystem->GetEntities().size() > 0)
				{
					for (auto& l : m_lightSystem->GetEntities())
					{
						Light* light = (Light*)l.second->GetComponent<Light>();
						Transform* lightTransform = (Transform*)l.second->GetComponent<Transform>();
						SetLightUniforms(light, lightTransform, material);
					}
				}

				DrawMesh(m);
			}
		}
	}
	else
		Logger::Log(LogLevel::LOG_WARNING, "No camera system was found.");	

	if (m_cameraSystem->GetEntities().size() == 0)
		Logger::Log(LogLevel::LOG_WARNING, "No camera was found within the scene.");
}

void ModelRenderSystem::BindCamera(Camera* camera)
{
	if (camera->GetRenderWidth() != 0 && camera->GetRenderHeight() != 0)
		GetEngine().GetDisplay().SetViewport(camera->GetRenderX(), camera->GetRenderY(), 
			camera->GetRenderWidth(), camera->GetRenderHeight());
}

void ModelRenderSystem::SetCameraUniforms(Material* material, Transform* meshTransform, 
	Transform* cameraTransform, Camera* camera)
{
	material->Bind();
	material->SetWorld(Math::WorldModel(meshTransform->Position(), meshTransform->Rotation(), meshTransform->Scale()));
	material->SetProjection(m_cameraSystem->Projection(camera));
	material->SetView(m_cameraSystem->View(cameraTransform));
	material->SetViewPosition(cameraTransform->Position());
	material->SetNormalMatrix(Math::NormalMatrix(meshTransform->Position(), meshTransform->Rotation(), meshTransform->Scale()));
}

void ModelRenderSystem::SetLightUniforms(Light* light, Transform* transform, Material* material)
{
	material->SetLightDirection(light->GetLightTypeName(), transform->Rotation());
	material->SetLightAmbient(light->GetLightTypeName(), light->Ambient());
	material->SetLightDiffuse(light->GetLightTypeName(), light->Diffuse());
	material->SetLightSpecular(light->GetLightTypeName(), light->Specular());
}

void ModelRenderSystem::DrawMesh(Mesh* mesh)
{
	glBindVertexArray(mesh->GetVAO());
	if (mesh->Indices().size() > 0)
		glDrawElements(GL_TRIANGLES, mesh->Indices().size(), GL_UNSIGNED_INT, 0);
	else
		glDrawArrays(GL_TRIANGLES, 0, mesh->Vertices().size());
	glBindVertexArray(0);
}