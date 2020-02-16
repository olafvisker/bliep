#include <GL/glew.h>

#include "window.h"
#include "logger.h"

namespace bliep {
	void Window::Init(const std::string& title) {
		LOG_ERROR_IF(SDL_Init(SDL_INIT_EVERYTHING) >= 0) << "SDL could not be initialized.\n Error: " << SDL_GetError();
		
		SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_width, m_height, SDL_WINDOW_OPENGL);
		LOG_ERROR_IF(m_window != 0) << "SDL Window '" << title.c_str() << "' could not be created.\n Error: " << SDL_GetError();

		SDL_GL_SetSwapInterval(0); //disable vsync
		//SDL_SetWindowFullscreen(m_window, SDL_WINDOW_FULLSCREEN);

		m_gl_context = SDL_GL_CreateContext(m_window);
		LOG_ERROR_IF(m_gl_context != 0) << "GL Context could not be created.\n Error: " << SDL_GetError();
		LOG_ERROR_IF(glewInit() == GLEW_OK) << "GLEW could not be initialized.";

		glewExperimental = GL_TRUE;

		SetViewport(0, 0, m_width, m_height);

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
	}

	void Window::SetViewport(const rectangle viewport) {
		SetViewport(viewport.x, viewport.y, viewport.width, viewport.height);
	}

	void Window::SetViewport(const int x, const int y, const unsigned width, const unsigned height) {
		glViewport(x, y, width, height);
	}

	void Window::Clear() {
		glClearColor(m_clear_color.r, m_clear_color.g, m_clear_color.b, m_clear_color.a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Window::Close() { m_is_closed = true; }
	void Window::SetClearColor(const color& clear_color) { m_clear_color = clear_color; }
	void Window::SwapBuffers() { SDL_GL_SwapWindow(m_window); }
}

