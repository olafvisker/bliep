#pragma once
#include <SDL2/SDL.h>
#include <string>

#include "../types/color.h"
#include "../types/rectangle.h"

namespace bliep {
	class Window {
		public:
			Window() { };
			~Window() { }

			void Init(const std::string& title = "Window");

			SDL_Window* GetWindowId() 		const { return m_window; }
			std::string GetTitle() 			const { return m_title; }
			unsigned int GetWidth() 		const { return m_width; }
			unsigned int GetHeight() 		const { return m_height; }
			float GetAspectRatio() 			const { return ((float)m_width / (float)m_height); }					
			bool IsClosed() 				const { return m_is_closed; }
			rectangle GetWindowBounds()		const { return rectangle(0, 0, m_width, m_height); }

			void SetViewport(const rectangle viewport);
			void SetViewport(const int x, const int y, const unsigned width, const unsigned height);

			void Close();

			void Clear();
			void SwapBuffers();

			void SetClearColor(const color& clear_color);

		private:
			SDL_Window* m_window;
			SDL_GLContext m_gl_context;

			std::string m_title 	= "Window";
			unsigned int m_width 	= 800;
			unsigned int m_height 	= 600;
			bool m_is_closed 		= false;		
			color m_clear_color 	= color(0.15f, 0.15f, 0.15f);
	};
}