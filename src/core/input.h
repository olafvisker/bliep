#pragma once
#include <SDL2/SDL.h>
#include <map>

#include "window.h"

namespace bliep {
	enum KeyState {
		UP,
		DOWN,
	};

	class Input {
		public:
			Input() { }
			~Input() { }

			bool IsKeyDown(unsigned int key)                { return m_keymap[key] == KeyState::DOWN; }
			bool IsKeyPressed(unsigned int key)             { return m_keymap[key] == KeyState::DOWN && m_prev_key_map[key] == KeyState::UP; }
			bool IsKeyUp(unsigned int key)                  { return m_keymap[key] == KeyState::UP; }
			bool IsKeyReleased(unsigned int key)            { return m_keymap[key] == KeyState::UP && m_prev_key_map[key] == KeyState::DOWN; }

			KeyState GetKeyState(unsigned int key)          { return m_keymap[key]; }
			KeyState GetPreviousKeyState(unsigned int key)  { return m_prev_key_map[key]; }

			int GetDeltaX()         { return m_mouse_x; }
			int GetDeltaY()         { return m_mouse_y; }
			int GetMouseDeltaX()    { return m_mouse_delta_x; }
			int GetMouseDeltaY()    { return m_mouse_delta_y; }

			void ShowCursor(bool show) { SDL_ShowCursor(show); }	
			void LockCursor(bool lock) { SDL_SetRelativeMouseMode((SDL_bool)lock); }

			void Update(Window& window);

		private:
			std::map<unsigned int, KeyState> m_keymap;
			std::map<unsigned int, KeyState> m_prev_key_map;

			int m_mouse_x = 0;
			int m_mouse_y = 0;
			int m_mouse_delta_x = 0;
			int m_mouse_delta_y = 0;
	}; 
}