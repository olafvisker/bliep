#pragma once
#include <chrono>

namespace bliep {
    namespace Time {
        double GetElapsed();
        float GetDelta();
        
        void Restart();
        void Sleep(int milliseconds);

        void SetDelta(float delta);

        namespace { 
            #pragma GCC diagnostic ignored "-Wunused-variable" 
            std::chrono::high_resolution_clock::time_point m_start_time;
            float m_delta;
        }
    };
}