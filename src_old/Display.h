#pragma once
#include <SDL/SDL.h>
#include <string>

class Display
{
public:
	Display() { };
	~Display() { }

	void Initialize();

	std::string GetTitle() { return m_title; }
	void SetTitle(const std::string& title);

	SDL_Window* GetWindowID() { return m_window; }

	unsigned int GetWidth() { return m_width; }
	void SetWidth(unsigned int width) { m_width = width; }

	unsigned int GetHeight() { return m_height; }
	void SetHeight(unsigned int height) { m_height = height; }

	void Close() { m_isClosed = true; }
	bool IsClosed() { return m_isClosed; }

	void SetViewport(int x, int y, unsigned int width, unsigned int height);
	float GetWindowAspectRatio() { return ((float)m_width / (float)m_height); }

	void Clear();
	void SwapBuffers();

	void SetClearColor(float red, float green, float blue);

private:
	SDL_Window* m_window;
	SDL_GLContext m_glContext;

	std::string m_title		= "Window";
	unsigned int m_width	= 800;
	unsigned int m_height	= 600;
	bool m_isClosed			= false;
	
	float m_clearRed	= 0.44f;
	float m_clearGreen	= 0.57f;
	float m_clearBlue	= 0.75f;
};

