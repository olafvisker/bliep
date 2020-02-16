#include <thread>
#include <iostream>

#include "engine.h"

namespace bliep {
    void Engine::Start() {
        m_window->Init("Engine");
        Logger::Init("bin/dump.log", true, 1000000);
        Time::Restart();
        Init();
    	GetSystemManager().Init();

        Loop();
    }

    void Engine::Loop() {
        float frame_time = 1.0 / TARGET_FPS;
        double previous = Time::GetElapsed();
        double lag = 0.0;
        int frames = 0;
        double frame_counter = 0.0;
        
        while (!m_window->IsClosed()) {
            double current = Time::GetElapsed();
            double elapsed = current - previous;
            Time::SetDelta(elapsed);

            previous = current;
            lag += elapsed;
            frame_counter += elapsed;

            if (frame_counter >= 1.0) {
                LOG_INFO << "fps: " << frames;
                frame_counter = 0;
                frames = 0;
            }

            while (lag >= frame_time) {
                UpdateFrame();
                lag -= frame_time;
            }

            RenderFrame(); 
            frames++;
        }
    }

    void Engine::UpdateFrame() {
        m_input->Update(*m_window);
        GetSystemManager().Update();
        Update();    
    }

    void Engine::RenderFrame() {
        m_window->Clear();
        GetSystemManager().Draw();
        Draw();
        m_window->SwapBuffers();
    }
}