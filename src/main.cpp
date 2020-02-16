#include <memory>
#include <vector>
#include <string>
#include <fstream>
#include <random>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "main.h"
#include "core/logger.h"
#include "core/timer.h"

#include "graphics/mesh.h"
#include "graphics/material.h"
#include "graphics/model.h"
#include "graphics/render_system.h"

#include "components/mesh_renderer.h"
#include "components/transform.h"
#include "components/camera.h"

#include "resource/asset.h"
#include "resource/asset_loader.h"
#include "resource/asset_manager.h"

#include "ecs/entity.h"
#include "ecs/system.h"

#include "debug_components.h"
#include "debug_systems.h"


using namespace bliep;


std::vector<glm::vec3> GetCubeVertices() {
	std::vector<glm::vec3> vertices;
	//BOTTOM
	vertices.push_back(glm::vec3(0.5f, -0.5f, -0.5f));
	vertices.push_back(glm::vec3(0.5f, -0.5f, 0.5f));
	vertices.push_back(glm::vec3(-0.5f, -0.5f, 0.5f));
	vertices.push_back(glm::vec3(0.5f, -0.5f, -0.5f));
	vertices.push_back(glm::vec3(-0.5f, -0.5f, 0.5f));
	vertices.push_back(glm::vec3(-0.5f, -0.5f, -0.5f));

	//TOP
	vertices.push_back(glm::vec3(0.5f, 0.5f, -0.5f));
	vertices.push_back(glm::vec3(-0.5f, 0.5f, -0.5f));
	vertices.push_back(glm::vec3(-0.5f, 0.5f, 0.5f));
	vertices.push_back(glm::vec3(0.5f, 0.5f, -0.5f));
	vertices.push_back(glm::vec3(-0.5f, 0.5f, 0.5f));
	vertices.push_back(glm::vec3(0.5f, 0.5f, 0.5f));

	//RIGHT
	vertices.push_back(glm::vec3(0.5f, -0.5f, -0.5f));
	vertices.push_back(glm::vec3(0.5f, 0.5f, -0.5f));
	vertices.push_back(glm::vec3(0.5f, 0.5f, 0.5f));
	vertices.push_back(glm::vec3(0.5f, -0.5f, -0.5f));
	vertices.push_back(glm::vec3(0.5f, 0.5f, 0.5f));
	vertices.push_back(glm::vec3(0.5f, -0.5f, 0.5f));

	//FRONT
	vertices.push_back(glm::vec3(0.5f, -0.5f, 0.5f));
	vertices.push_back(glm::vec3(0.5f, 0.5f, 0.5f));
	vertices.push_back(glm::vec3(-0.5f, 0.5f, 0.5f));
	vertices.push_back(glm::vec3(0.5f, -0.5f, 0.5f));
	vertices.push_back(glm::vec3(-0.5f, 0.5f, 0.5f));
	vertices.push_back(glm::vec3(-0.5f, -0.5f, 0.5f));

	//LEFT
	vertices.push_back(glm::vec3(-0.5f, -0.5f, 0.5f));
	vertices.push_back(glm::vec3(-0.5f, 0.5f, 0.5f));
	vertices.push_back(glm::vec3(-0.5f, 0.5f, -0.5f));
	vertices.push_back(glm::vec3(-0.5f, -0.5f, 0.5f));
	vertices.push_back(glm::vec3(-0.5f, 0.5f, -0.5f));
	vertices.push_back(glm::vec3(-0.5f, -0.5f, -0.5f));

	//BACK
	vertices.push_back(glm::vec3(0.5f, 0.5f, -0.5f));
	vertices.push_back(glm::vec3(0.5f, -0.5f, -0.5f));
	vertices.push_back(glm::vec3(-0.5f, -0.5f, -0.5f));
	vertices.push_back(glm::vec3(0.5f, 0.5f, -0.5f));
	vertices.push_back(glm::vec3(-0.5f, -0.5f, -0.5f));
	vertices.push_back(glm::vec3(-0.5f, 0.5f, -0.5f));
	return vertices;
}
std::vector<glm::vec2> GetCubeUvs() {
	std::vector<glm::vec2> uvs;
	//BOTTOM
	uvs.push_back(glm::vec2(0.0f, 1.0f));
	uvs.push_back(glm::vec2(1.0f, 1.0f));
	uvs.push_back(glm::vec2(1.0f, 0.0f));
	uvs.push_back(glm::vec2(1.0f, 0.0f));
	uvs.push_back(glm::vec2(0.0f, 0.0f));
	uvs.push_back(glm::vec2(0.0f, 1.0f));

	//TOP
	uvs.push_back(glm::vec2(0.0f, 1.0f));
	uvs.push_back(glm::vec2(1.0f, 1.0f));
	uvs.push_back(glm::vec2(1.0f, 0.0f));
	uvs.push_back(glm::vec2(1.0f, 0.0f));
	uvs.push_back(glm::vec2(0.0f, 0.0f));
	uvs.push_back(glm::vec2(0.0f, 1.0f));

	//RIGHT
	uvs.push_back(glm::vec2(1.0f, 0.0f));
	uvs.push_back(glm::vec2(1.0f, 1.0f));
	uvs.push_back(glm::vec2(0.0f, 1.0f));
	uvs.push_back(glm::vec2(0.0f, 1.0f));
	uvs.push_back(glm::vec2(0.0f, 0.0f));
	uvs.push_back(glm::vec2(1.0f, 0.0f));

	//FRONT
	uvs.push_back(glm::vec2(0.0f, 0.0f));
	uvs.push_back(glm::vec2(1.0f, 0.0f));
	uvs.push_back(glm::vec2(1.0f, 1.0f));
	uvs.push_back(glm::vec2(1.0f, 1.0f));
	uvs.push_back(glm::vec2(0.0f, 1.0f));
	uvs.push_back(glm::vec2(0.0f, 0.0f));

	//LEFT
	uvs.push_back(glm::vec2(1.0f, 0.0f));
	uvs.push_back(glm::vec2(1.0f, 1.0f));
	uvs.push_back(glm::vec2(0.0f, 1.0f));
	uvs.push_back(glm::vec2(0.0f, 1.0f));
	uvs.push_back(glm::vec2(0.0f, 0.0f));
	uvs.push_back(glm::vec2(1.0f, 0.0f));

	//BACK
	uvs.push_back(glm::vec2(0.0f, 0.0f));
	uvs.push_back(glm::vec2(1.0f, 0.0f));
	uvs.push_back(glm::vec2(1.0f, 1.0f));
	uvs.push_back(glm::vec2(1.0f, 1.0f));
	uvs.push_back(glm::vec2(0.0f, 1.0f));
	uvs.push_back(glm::vec2(0.0f, 0.0f));
	return uvs;
}
std::vector<glm::vec3> GetCubeNormals() {
	std::vector<glm::vec3> normals;
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

	normals.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	normals.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	normals.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	normals.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	normals.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	normals.push_back(glm::vec3(1.0f, 0.0f, 0.0f));

	normals.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	normals.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	normals.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	normals.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	normals.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	normals.push_back(glm::vec3(0.0f, 0.0f, 1.0f));

	normals.push_back(glm::vec3(-1.0f, 0.0f, 0.0f));
	normals.push_back(glm::vec3(-1.0f, 0.0f, 0.0f));
	normals.push_back(glm::vec3(-1.0f, 0.0f, 0.0f));
	normals.push_back(glm::vec3(-1.0f, 0.0f, 0.0f));
	normals.push_back(glm::vec3(-1.0f, 0.0f, 0.0f));
	normals.push_back(glm::vec3(-1.0f, 0.0f, 0.0f));

	normals.push_back(glm::vec3(0.0f, 0.0f, -1.0f));
	normals.push_back(glm::vec3(0.0f, 0.0f, -1.0f));
	normals.push_back(glm::vec3(0.0f, 0.0f, -1.0f));
	normals.push_back(glm::vec3(0.0f, 0.0f, -1.0f));
	normals.push_back(glm::vec3(0.0f, 0.0f, -1.0f));
	normals.push_back(glm::vec3(0.0f, 0.0f, -1.0f));
	return normals;
}

std::unique_ptr<AssetManager> asset_manager(new AssetManager());
std::unique_ptr<Mesh> mesh(new Mesh());
std::unique_ptr<Mesh> mesh2(new Mesh());
std::unique_ptr<Material> material(new Material());
std::unique_ptr<Material> material2(new Material());

Entity l;

void Main::Init() {
	//RESOURCE
    Shader* flat_shader = asset_manager->Load<Shader>("flat_shader", "E:/Projects/C++/Bliep Engine/assets/shaders/flat");	
    Shader* shader = asset_manager->Load<Shader>("default_shader", "E:/Projects/C++/Bliep Engine/assets/shaders/default");	
    Texture* texture = asset_manager->Load<Texture>("test_texture", "E:/Projects/C++/Bliep Engine/assets/textures/test_texture");
    Texture* texture2 = asset_manager->Load<Texture>("test_texture2", "E:/Projects/C++/Bliep Engine/assets/textures/test_texture2");
    Model* model = asset_manager->Load<Model>("bunny", "E:/Projects/C++/Bliep Engine/assets/models/nanosuit");

    //MATERIAL
    material->SetShader(shader);
    material->SetDiffuse(texture);
    material->SetSpecular(texture2);
    material->SetShininess(16.0f);

	material->GetShader().SetInt("n_dir_lights", 1);
	material->GetShader().SetInt("n_point_lights", 3);

	material->GetShader().SetVec3("dirlight[0].direction", glm::vec3(-1,-1,0));
	material->GetShader().SetVec3("dirlight[0].ambient",  glm::vec3(0.1f, 0.1f, 0.1f));
	material->GetShader().SetVec3("dirlight[0].diffuse",  glm::vec3(0.5f, 0.5f, 0.5f)); 
	material->GetShader().SetVec3("dirlight[0].specular", glm::vec3(1.0f, 1.0f, 1.0f)); 

	material->GetShader().SetVec3("pointlight[0].position", glm::vec3(0,0,0));
	material->GetShader().SetVec3("pointlight[0].ambient",  glm::vec3(0.2f, 0.2f, 0.2f));
	material->GetShader().SetVec3("pointlight[0].diffuse",  glm::vec3(0.5f, 0.5f, 0.5f)); 
	material->GetShader().SetVec3("pointlight[0].specular", glm::vec3(1.0f, 1.0f, 1.0f)); 
	material->GetShader().SetFloat("pointlight[0].constant", 1.0f); 
	material->GetShader().SetFloat("pointlight[0].linear", 0.09f); 
	material->GetShader().SetFloat("pointlight[0].quadratic", 0.032f); 

	material->GetShader().SetVec3("pointlight[1].position", glm::vec3(0,20,0));
	material->GetShader().SetVec3("pointlight[1].ambient",  glm::vec3(0.6f, 0.2f, 0.2f));
	material->GetShader().SetVec3("pointlight[1].diffuse",  glm::vec3(0.5f, 0.7f, 0.2f)); 
	material->GetShader().SetVec3("pointlight[1].specular", glm::vec3(1.0f, 1.0f, 1.0f)); 
	material->GetShader().SetFloat("pointlight[1].constant", 1.0f); 
	material->GetShader().SetFloat("pointlight[1].linear", 0.09f); 
	material->GetShader().SetFloat("pointlight[1].quadratic", 0.032f); 

	material->GetShader().SetVec3("pointlight[2].position", glm::vec3(10,0,0));
	material->GetShader().SetVec3("pointlight[2].ambient",  glm::vec3(0.2f, 0.8f, 0.8f));
	material->GetShader().SetVec3("pointlight[2].diffuse",  glm::vec3(0.5f, 0.9f, 0.9f)); 
	material->GetShader().SetVec3("pointlight[2].specular", glm::vec3(1.0f, 1.0f, 1.0f)); 
	material->GetShader().SetFloat("pointlight[2].constant", 1.0f); 
	material->GetShader().SetFloat("pointlight[2].linear", 0.2f); 
	material->GetShader().SetFloat("pointlight[2].quadratic", 0.032f); 

	material2->SetShader(flat_shader);
	material2->GetShader().SetVec3("object_color", glm::vec3(1, 1, 1));

	//MESH
	mesh->SetVertices(GetCubeVertices());
	mesh->SetNormals(GetCubeNormals());
	mesh->SetUVs(GetCubeUvs());
	mesh->SetMaterial(material.get());
	mesh->Build();

	mesh2->SetVertices(GetCubeVertices());
	mesh2->SetMaterial(material2.get());
	mesh2->Build();

	//ENTITY
	Entity c = GetEntityManager().Create();
	c.AddComponent<Camera>(GetWindow().GetWindowBounds())
	 .AddComponent<CameraController>()
	 .AddComponent<Transform>()
	 .Bind();

	l = GetEntityManager().Create();
	l.AddComponent<MeshRenderer>(mesh2.get())
	 .AddComponent<Transform>(glm::vec3(0.0f), glm::vec3(0.25f))
	 .Bind();
	
	GetEntityManager().Create()
    .AddComponent<MeshRenderer>(mesh2.get())
    .AddComponent<Transform>(glm::vec3(0.0f, 20.0f, 0.0f), glm::vec3(0.25f))
    .Bind();

	GetEntityManager().Create()
    .AddComponent<MeshRenderer>(mesh2.get())
    .AddComponent<Transform>(glm::vec3(10.0f, 0.0f, 0.0f), glm::vec3(0.25f))
    .Bind();

	// std::random_device rd;
  //   std::mt19937 e2(rd());
  //   std::uniform_real_distribution<> dist(-25, 25);
  //   std::uniform_real_distribution<> sc(0.5, 4);

	for (int i = 0; i < model->Meshes().size(); i++) {
		model->Meshes()[i]->SetMaterial(material.get());
		Entity e1 = GetEntityManager().Create();
		e1.AddComponent<MeshRenderer>(model->Meshes()[i].get())
		    .AddComponent<Transform>()
			.Bind();
	}

	// for (int i = 0; i < 250; i++) {
	// 	Entity e1 = GetEntityManager().Create();
	// 	e1.AddComponent<MeshRenderer>(mesh.get())
	// 	  .AddComponent<Transform>(glm::vec3(dist(e2), dist(e2), -15 + dist(e2)), glm::vec3(sc(e2), sc(e2), sc(e2)))
	// 	  .Bind();
	// }

	//SYSTEM
	GetSystemManager().Register<RenderSystem>();
	GetSystemManager().Register<CameraControllerSystem>();
}

void Main::Update() {
	if (GetInput().IsKeyDown(SDLK_ESCAPE)) 
		GetWindow().Close();

	l.GetComponent<Transform>()->position = glm::vec3(2.0f * sin(Time::GetElapsed()), 0.0, 2.0f * cos(Time::GetElapsed()));
	material->GetShader().Bind();
	material->GetShader().SetVec3("pointlight[0].position", l.GetComponent<Transform>()->position);
}

void Main::Draw() { }