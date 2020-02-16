#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>

#include "timer.h"

namespace bliep {
    void Time::Restart() {
        m_start_time = std::chrono::high_resolution_clock::now();
    }

    void Time::Sleep(int milliseconds) {
        SDL_Delay(milliseconds);
    }

    double Time::GetElapsed() {
        auto curr_time = std::chrono::high_resolution_clock::now();
        auto time_span = std::chrono::duration_cast<std::chrono::nanoseconds>(curr_time - m_start_time);
        return time_span.count() / 1000000000.0;
    } 

    float Time::GetDelta() {
        return m_delta;
    }

    void Time::SetDelta(float delta) { 
        m_delta = delta; 
    }
}
