#include <GL/glew.h>

#include "Display.h"
#include "Logger.h"

void Display::SetTitle(const std::string& title)
{
	m_title = title;
	SDL_SetWindowTitle(m_window, title.c_str());
}

void Display::Initialize()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		Logger::Log(LogLevel::LOG_ERROR, "SDL could not be initialized.\n'%s'", SDL_GetError());

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	m_window = SDL_CreateWindow(m_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_width, m_height, SDL_WINDOW_OPENGL);
	if (m_window == 0)
		Logger::Log(LogLevel::LOG_ERROR, "SDL Window '%s' could not be created.\n'%s'", m_title.c_str(), SDL_GetError());

	m_glContext = SDL_GL_CreateContext(m_window);
	if (m_glContext == 0)
		Logger::Log(LogLevel::LOG_ERROR, "GL Context could not be created.\n'%s'", SDL_GetError());

	if (glewInit() != GLEW_OK)
		Logger::Log(LogLevel::LOG_ERROR, "GLEW could not be initialized.");

	glewExperimental = GL_TRUE;

	SetViewport(0, 0, m_width, m_height);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

void Display::SetViewport(int x, int y, unsigned int width, unsigned int height)
{
	glViewport(x, y, width, height);
}

void Display::Clear()
{
	glClearColor(m_clearRed, m_clearGreen, m_clearBlue, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Display::SetClearColor(float red, float green, float blue)
{
	m_clearRed		= red / 255;
	m_clearGreen	= green / 255;
	m_clearBlue		= blue / 255;
}

void Display::SwapBuffers()
{
	SDL_GL_SwapWindow(m_window);
}

