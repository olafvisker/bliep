#include "InputManager.h"
#include "Engine.h"

InputManager::InputManager(Engine* engine) :
m_engine(engine) 
{ }

void InputManager::Update()
{
	SDL_Event evnt;
	m_prevKeyMap = m_keyMap;

	m_mouseDeltaX = m_mouseX - m_prevMouseX;
	m_mouseDeltaY = m_prevMouseY - m_mouseY;
	m_prevMouseX = m_mouseX;
	m_prevMouseY = m_mouseY;

	while (SDL_PollEvent(&evnt))
	{
		switch (evnt.type)
		{
		case SDL_QUIT:
			m_engine->GetDisplay().Close();
			break;
		case SDL_KEYDOWN:
			m_keyMap[evnt.key.keysym.sym] = KeyState::KEY_DOWN;
			break;
		case SDL_KEYUP:
			m_keyMap[evnt.key.keysym.sym] = KeyState::KEY_UP;
			break;
		case SDL_MOUSEMOTION:
			m_mouseX = evnt.motion.x;
			m_mouseY = evnt.motion.y;

			if (m_firstMouse)
			{
				m_prevMouseX = m_mouseX;
				m_prevMouseY = m_mouseY;
				m_firstMouse = false;
			}
			break;
		}
	}
}