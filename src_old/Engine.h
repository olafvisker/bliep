#pragma once
#include <GL/glew.h>
#include <memory>

#include "Display.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "SystemManager.h"
#include "EntityManager.h"

class Engine
{
public:
	Engine();
	virtual ~Engine();

	Display& GetDisplay()					const { return *m_display; }
	InputManager& GetInputManager()			const { return *m_inputManager; }
	ResourceManager& GetResourceManager()	const { return *m_resourceManager; }
	SystemManager& GetSystemManager()		const { return *m_systemManager; }
	EntityManager& GetEntityManager()		const { return *m_entityManager; }

	void Start();

	virtual void Initialize() = 0;
	virtual void Update(float deltaTime) = 0;

private:
	std::unique_ptr<Display> m_display;
	std::unique_ptr<InputManager> m_inputManager;
	std::unique_ptr<ResourceManager> m_resourceManager;
	std::unique_ptr<SystemManager> m_systemManager;
	std::unique_ptr<EntityManager> m_entityManager;

	GLfloat deltaTime;
	GLfloat lastFrame;

	void Loop();
};
