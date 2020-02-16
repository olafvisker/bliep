#pragma once
#include <memory>

#include "window.h"
#include "input.h"
#include "logger.h"
#include "timer.h"

#include "../ecs/entity.h"
#include "../ecs/system.h"

namespace bliep {
    class Engine {
        public: 
            const int TARGET_FPS = 60;

            Engine() : 
            m_window(new Window()), 
            m_input(new Input()),
            m_entitymanager(new EntityManager()),
            m_systemmanager(new SystemManager(this)) { }

            virtual ~Engine() { }

            void Start();

            Window& GetWindow()	const { return *m_window; }
            Input& GetInput()	const { return *m_input; }
            EntityManager& GetEntityManager()	const { return *m_entitymanager; }
            SystemManager& GetSystemManager()	const { return *m_systemmanager; }

            virtual void Init() = 0;
            virtual void Update() = 0;
            virtual void Draw() = 0;

        private:
            std::unique_ptr<Window> m_window;
            std::unique_ptr<Input> m_input;
            std::unique_ptr<EntityManager> m_entitymanager;
            std::unique_ptr<SystemManager> m_systemmanager;

            void Loop();
            void UpdateFrame();
            void RenderFrame();
    };
}