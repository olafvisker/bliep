#pragma once
#include <SDL/SDL.h>
#include <map>

class Engine;

enum KeyState
{
	KEY_UP,
	KEY_DOWN,
};

class InputManager
{
public:
	InputManager(Engine* engine);
	~InputManager() { }

	bool IsKeyDown(unsigned int key) { return m_keyMap[key] == KeyState::KEY_DOWN; }
	bool IsKeyPressed(unsigned int key) { return m_keyMap[key] == KeyState::KEY_DOWN && m_prevKeyMap[key] == KeyState::KEY_UP; }
	bool IsKeyUp(unsigned int key) { return m_keyMap[key] == KeyState::KEY_UP; }
	bool IsKeyReleased(unsigned int key) { return m_keyMap[key] == KeyState::KEY_UP && m_prevKeyMap[key] == KeyState::KEY_DOWN; }

	KeyState GetKeyState(unsigned int key) { return m_keyMap[key]; }
	KeyState GetPreviousKeyState(unsigned int key) { return m_prevKeyMap[key]; }

	int GetDeltaX() { return m_mouseX; }
	int GetDeltaY() { return m_mouseY; }
	int GetMouseDeltaX() { return m_mouseDeltaX; }
	int GetMouseDeltaY() { return m_mouseDeltaY; }

	inline void ShowCursor(bool showCursor) { SDL_ShowCursor(showCursor); }

	void Update();

private:
	Engine* m_engine;

	std::map<unsigned int, KeyState> m_keyMap;
	std::map<unsigned int, KeyState> m_prevKeyMap;

	int m_mouseX = 0;
	int m_mouseY = 0;
	int m_prevMouseX = 0;
	int m_prevMouseY = 0;
	int m_mouseDeltaX = 0;
	int m_mouseDeltaY = 0;
	bool m_firstMouse = true;
};