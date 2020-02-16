#pragma once
#include <vector>
#include <unordered_map>
#include <typeindex>
#include <memory>

#include "entity.h"

namespace bliep {

    class Engine;
    class System;
    class Component;
    class SystemManager;

    class System {

        friend class SystemManager;

        public:
            System() { }
            virtual ~System() { }
            
            template<typename T> void Require() { Require<T>(0); };
            template<typename T> void Require(int set);

            unsigned GetFlag(int set);
            std::vector<Entity>& GetEntities();
            std::vector<Entity>& GetEntities(int set);
            std::unordered_map<int, unsigned>& GetSets();
            Engine& GetEngine() const;
            
            virtual void Init() { }
            virtual void Update() { }
            virtual void Draw() { }

        private:
            std::unordered_map<int, std::vector<Entity>> m_entities;
            std::unordered_map<int, unsigned> m_flags;
            SystemManager* m_manager;

            void Require(std::type_index t, int set);
            void AddEntity(Entity e, int set);
            void RemoveEntity(Entity e, int set);
    };

    class SystemManager {
        public:
            SystemManager(Engine* engine) : m_engine(engine) { }    
            ~SystemManager();

            template<typename T> SystemManager& Register();
            template<typename T> bool HasSystem();
            Engine& GetEngine() const;

            void Init();
            void Update();
            void Draw();

        private:
            std::unordered_map<std::type_index, std::unique_ptr<System>> m_systems;

            Engine* m_engine;

            void AddToSystems(Entity e);      
            void RemoveFromSystems(Entity e);
    };

    template<typename T> void System::Require(int set) { Require(typeid(T), set); }

    template<typename T> SystemManager& SystemManager::Register()   { 
        if (HasSystem<T>()) { return *this; } 
        m_systems[typeid(T)] = std::unique_ptr<T>(new T); 
        m_systems[typeid(T)]->m_manager = this;
        return *this; 
    }
    template<typename T> bool SystemManager::HasSystem()            {  return m_systems.count(typeid(T)); }
};