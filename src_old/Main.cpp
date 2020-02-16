#include <GLM/glm.hpp>
#include <vector>

#include "Main.h"
#include "Transform.h"
#include "Material.h"
#include "Mesh.h"
#include "Model.h"
#include "ModelRenderer.h"
#include "ModelRenderSystem.h"
#include "Camera.h"
#include "CameraSystem.h"
#include "CameraController.h"
#include "CameraControllerSystem.h"
#include "Entity.h"
#include "Light.h"
#include "LightSystem.h"

std::vector<glm::vec3> GetCubeVertices()
{
	std::vector<glm::vec3> vertices;
	//BACK
	vertices.push_back(glm::vec3(0.5f, -0.5f, -0.5f));
	vertices.push_back(glm::vec3(-0.5f, -0.5f, -0.5f));
	vertices.push_back(glm::vec3(-0.5f, 0.5f, -0.5f));
	vertices.push_back(glm::vec3(-0.5f, 0.5f, -0.5f));
	vertices.push_back(glm::vec3(0.5f, 0.5f, -0.5f));
	vertices.push_back(glm::vec3(0.5f, -0.5f, -0.5f));

	//FRONT
	vertices.push_back(glm::vec3(-0.5f, -0.5f, 0.5f));
	vertices.push_back(glm::vec3(0.5f, -0.5f, 0.5f));
	vertices.push_back(glm::vec3(0.5f, 0.5f, 0.5f));
	vertices.push_back(glm::vec3(0.5f, 0.5f, 0.5f));
	vertices.push_back(glm::vec3(-0.5f, 0.5f, 0.5f));
	vertices.push_back(glm::vec3(-0.5f, -0.5f, 0.5f));

	//LEFT
	vertices.push_back(glm::vec3(-0.5f, 0.5f, 0.5f));
	vertices.push_back(glm::vec3(-0.5f, 0.5f, -0.5f));
	vertices.push_back(glm::vec3(-0.5f, -0.5f, -0.5f));
	vertices.push_back(glm::vec3(-0.5f, -0.5f, -0.5f));
	vertices.push_back(glm::vec3(-0.5f, -0.5f, 0.5f));
	vertices.push_back(glm::vec3(-0.5f, 0.5f, 0.5f));

	//RIGHT
	vertices.push_back(glm::vec3(0.5f, -0.5f, -0.5f));
	vertices.push_back(glm::vec3(0.5f, 0.5f, -0.5f));
	vertices.push_back(glm::vec3(0.5f, 0.5f, 0.5f));
	vertices.push_back(glm::vec3(0.5f, 0.5f, 0.5f));
	vertices.push_back(glm::vec3(0.5f, -0.5f, 0.5f));
	vertices.push_back(glm::vec3(0.5f, -0.5f, -0.5f));

	////BOTTOM
	vertices.push_back(glm::vec3(-0.5f, -0.5f, -0.5f));
	vertices.push_back(glm::vec3(0.5f, -0.5f, -0.5f));
	vertices.push_back(glm::vec3(0.5f, -0.5f, 0.5f));
	vertices.push_back(glm::vec3(0.5f, -0.5f, 0.5f));
	vertices.push_back(glm::vec3(-0.5f, -0.5f, 0.5f));
	vertices.push_back(glm::vec3(-0.5f, -0.5f, -0.5f));

	//TOP
	vertices.push_back(glm::vec3(-0.5f, 0.5f, -0.5f));
	vertices.push_back(glm::vec3(-0.5f, 0.5f, 0.5f));
	vertices.push_back(glm::vec3(0.5f, 0.5f, 0.5f));
	vertices.push_back(glm::vec3(0.5f, 0.5f, 0.5f));
	vertices.push_back(glm::vec3(0.5f, 0.5f, -0.5f));
	vertices.push_back(glm::vec3(-0.5f, 0.5f, -0.5f));
	return vertices;
}
std::vector<glm::vec2> GetCubeUvs()
{
	std::vector<glm::vec2> uvs;
	uvs.push_back(glm::vec2(0.0f, 0.0f));
	uvs.push_back(glm::vec2(1.0f, 0.0f));
	uvs.push_back(glm::vec2(1.0f, 1.0f));
	uvs.push_back(glm::vec2(1.0f, 1.0f));
	uvs.push_back(glm::vec2(0.0f, 1.0f));
	uvs.push_back(glm::vec2(0.0f, 0.0f));

	uvs.push_back(glm::vec2(0.0f, 0.0f));
	uvs.push_back(glm::vec2(1.0f, 0.0f));
	uvs.push_back(glm::vec2(1.0f, 1.0f));
	uvs.push_back(glm::vec2(1.0f, 1.0f));
	uvs.push_back(glm::vec2(0.0f, 1.0f));
	uvs.push_back(glm::vec2(0.0f, 0.0f));

	uvs.push_back(glm::vec2(1.0f, 0.0f));
	uvs.push_back(glm::vec2(1.0f, 1.0f));
	uvs.push_back(glm::vec2(0.0f, 1.0f));
	uvs.push_back(glm::vec2(0.0f, 1.0f));
	uvs.push_back(glm::vec2(0.0f, 0.0f));
	uvs.push_back(glm::vec2(1.0f, 0.0f));

	uvs.push_back(glm::vec2(1.0f, 0.0f));
	uvs.push_back(glm::vec2(1.0f, 1.0f));
	uvs.push_back(glm::vec2(0.0f, 1.0f));
	uvs.push_back(glm::vec2(0.0f, 1.0f));
	uvs.push_back(glm::vec2(0.0f, 0.0f));
	uvs.push_back(glm::vec2(1.0f, 0.0f));

	uvs.push_back(glm::vec2(0.0f, 1.0f));
	uvs.push_back(glm::vec2(1.0f, 1.0f));
	uvs.push_back(glm::vec2(1.0f, 0.0f));
	uvs.push_back(glm::vec2(1.0f, 0.0f));
	uvs.push_back(glm::vec2(0.0f, 0.0f));
	uvs.push_back(glm::vec2(0.0f, 1.0f));

	uvs.push_back(glm::vec2(0.0f, 1.0f));
	uvs.push_back(glm::vec2(1.0f, 1.0f));
	uvs.push_back(glm::vec2(1.0f, 0.0f));
	uvs.push_back(glm::vec2(1.0f, 0.0f));
	uvs.push_back(glm::vec2(0.0f, 0.0f));
	uvs.push_back(glm::vec2(0.0f, 1.0f));
	return uvs;
}
std::vector<glm::vec3> GetCubeNormals()
{
	std::vector<glm::vec3> normals;
	normals.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	normals.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	normals.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	normals.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	normals.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	normals.push_back(glm::vec3(0.0f, 0.0f, 1.0f));

	normals.push_back(glm::vec3(0.0f, 0.0f, -1.0f));
	normals.push_back(glm::vec3(0.0f, 0.0f, -1.0f));
	normals.push_back(glm::vec3(0.0f, 0.0f, -1.0f));
	normals.push_back(glm::vec3(0.0f, 0.0f, -1.0f));
	normals.push_back(glm::vec3(0.0f, 0.0f, -1.0f));
	normals.push_back(glm::vec3(0.0f, 0.0f, -1.0f));

	normals.push_back(glm::vec3(-1.0f, 0.0f, 0.0f));
	normals.push_back(glm::vec3(-1.0f, 0.0f, 0.0f));
	normals.push_back(glm::vec3(-1.0f, 0.0f, 0.0f));
	normals.push_back(glm::vec3(-1.0f, 0.0f, 0.0f));
	normals.push_back(glm::vec3(-1.0f, 0.0f, 0.0f));
	normals.push_back(glm::vec3(-1.0f, 0.0f, 0.0f));

	normals.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	normals.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	normals.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	normals.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	normals.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	normals.push_back(glm::vec3(1.0f, 0.0f, 0.0f));

	normals.push_back(glm::vec3(0.0f, -1.0f, 0.0f));
	normals.push_back(glm::vec3(0.0f, -1.0f, 0.0f));
	normals.push_back(glm::vec3(0.0f, -1.0f, 0.0f));
	normals.push_back(glm::vec3(0.0f, -1.0f, 0.0f));
	normals.push_back(glm::vec3(0.0f, -1.0f, 0.0f));
	normals.push_back(glm::vec3(0.0f, -1.0f, 0.0f));

	normals.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	normals.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	normals.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	normals.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	normals.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	normals.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	return normals;
}

void Main::Initialize()
{
	Transform* boxTransform = new Transform();
	boxTransform->Position() = glm::vec3(1, 0, -3);
	ModelRenderer* boxRenderer = new ModelRenderer();
	Model* boxModel = &GetResourceManager().CreateAsset<Model>();
	Material* boxMaterial = &GetResourceManager().CreateAsset<Material>();
	Mesh* boxMesh = new Mesh();
	boxMesh->SetName("Box");
	boxMesh->Vertices() = GetCubeVertices();
	boxMesh->Normals() = GetCubeNormals();
	boxMesh->UVs() = GetCubeUvs();
	boxMesh->Build();
	boxModel->AddMesh(boxMesh);
	Texture* boxTexture = &GetResourceManager().CreateAsset<Texture>("Assets/Textures/Brick.jpg");
	boxTexture->SetType(TextureType::TEX_DIFFUSE);
	boxMaterial->AddTexture(boxTexture);
	boxRenderer->SetModel(boxModel);
	boxMaterial->SetShader(&GetResourceManager().CreateAsset<Shader>("Assets/Shaders/Textured"));
	boxModel->AddMaterial(boxMaterial);

	GetSystemManager()
		.AddSystem(new ModelRenderSystem())
		.AddSystem(new CameraSystem())
		.AddSystem(new LightSystem())
		.AddSystem(new CameraControllerSystem());

	GetEntityManager()
		.CreateEntity()
		.AddComponent(boxTransform)
		.AddComponent(boxRenderer)
		.Refresh();

	GetEntityManager()
		.CreateEntity()
		.AddComponent(new Transform())
		.AddComponent(new Camera())
		.AddComponent(new CameraController())
		.Refresh();

	Transform* lightTransform = new Transform();
	lightTransform->Rotation() = glm::vec3(glm::radians(45.0f), 0, 0);

	GetEntityManager()
		.CreateEntity()
		.AddComponent(lightTransform)
		.AddComponent(new Light())
		.Refresh();
}

void Main::Update(float deltaTime)
{
	if (GetInputManager().IsKeyDown(SDLK_ESCAPE))
		GetDisplay().Close();
}
