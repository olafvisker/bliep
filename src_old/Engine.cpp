#include <SDL/SDL.h>

#include "Engine.h"
#include "Logger.h"

Engine::Engine() :
m_display(new Display()),
m_inputManager(new InputManager(this)),
m_resourceManager(new ResourceManager()),
m_systemManager(new SystemManager(this)),
m_entityManager(new EntityManager(this))
{ }

Engine::~Engine()
{
	Logger::Close();
}

void Engine::Start()
{
	m_display->Initialize();
	Initialize();
	m_systemManager->Initialize();
	Loop();
}

void Engine::Loop()
{
	while (!m_display->IsClosed())
	{
		GLfloat currentFrame = (GLfloat)SDL_GetTicks();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		m_display->Clear();
		m_inputManager->Update();
		Update(deltaTime);
		m_systemManager->Update(deltaTime);
		m_display->SwapBuffers();
	}
}

