#include "input.h"

namespace bliep {
	void Input::Update(Window& window) {
		SDL_Event evnt;
		m_prev_key_map = m_keymap;

		m_mouse_delta_x = 0;
		m_mouse_delta_y = 0;

		while (SDL_PollEvent(&evnt)) {		
			switch (evnt.type) {	
				case SDL_QUIT:
					window.Close();
					break;
				case SDL_KEYDOWN:
					m_keymap[evnt.key.keysym.sym] = KeyState::DOWN;
					break;
				case SDL_KEYUP:
					m_keymap[evnt.key.keysym.sym] = KeyState::UP;
					break;
				case SDL_MOUSEMOTION:
					m_mouse_x = evnt.motion.x;
					m_mouse_y = evnt.motion.y;
					m_mouse_delta_x = evnt.motion.xrel;
					m_mouse_delta_y = evnt.motion.yrel;
					break;				
			}
		}
	}
}