#pragma once
#include <vector>
#include <deque>
#include <typeindex>
#include <memory>
#include <cstdint>

namespace bliep {
    class EntityManager; 
    class Component;

    class Entity {

        friend class EntityManager;

        public:
            Entity() { }
            Entity(EntityManager* manager, uint32_t index, uint8_t version) : m_manager(manager), m_uid((version << IndexBits) | index)  { }

            Entity(const Entity&) = default;
            Entity& operator=(const Entity&) = default;
            
            uint32_t GetId()        const;
            uint8_t GetVersion()    const;
            unsigned GetFlag()      const;
            unsigned GetOldFlag()   const;
            
            void Destroy();            
            bool IsValid()  const;
            void Bind();

            template <typename T, typename ... Args> Entity& AddComponent(Args && ... args);
            template<typename T> Entity& RemoveComponent();
            template<typename T> bool HasComponent() const;
            template<typename T> T* GetComponent();

            
            bool operator==(const Entity e)    const{ return GetId() == e.GetId(); }
            bool operator!=(const Entity e)    const{ return GetId() != e.GetId(); }
            bool operator<(const Entity e)     const{ return GetId() < e.GetId(); }

        private:
            EntityManager* m_manager;
            uint32_t m_uid;

            static const uint32_t IndexBits     = 24;
            static const uint32_t IndexMask     = (1 << IndexBits) - 1;
            static const uint32_t VersionBits   = 8;
            static const uint32_t VersionMask   = (1 << VersionBits) - 1;

            EntityManager& GetManager() const;
    };

    class EntityManager {

        friend class SystemManager;

        public:
            EntityManager() { }
            ~EntityManager();

            Entity Create();
            void Destroy(Entity e);
            bool IsValid(Entity e) const;
            Entity Get(uint32_t index);
            unsigned GetFlag(Entity e);
            unsigned GetOldFlag(Entity e);
            void UpdateFlags(Entity e);
            void Bind(Entity e);

            template <typename T, typename ... Args> void AddComponent(Entity e, Args && ... args);           
            template<typename T> void RemoveComponent(Entity e);
            template<typename T> bool HasComponent(Entity e) const;
            template<typename T> T* GetComponent(Entity e);

        private:
            const uint32_t MIN_FREE_IDS = 1024;
            const uint32_t EXTRA_ID_RESERVE = 512;

            std::vector<std::vector<Component*>> m_components;
            
            std::deque<int> m_free_ids;
            std::vector<uint8_t> m_versions;
            std::vector<unsigned> m_bitflags;
            std::vector<unsigned> m_old_bitflags;
            std::vector<Entity> m_bindable_entities;
            std::vector<Entity> m_removable_entities;
            
            void Clear();
            void AddComponent(Entity e, Component* c);
            void RemoveComponent(Entity e, std::type_index t);
            bool HasComponent(Entity e, std::type_index t) const;
            Component* GetComponent(Entity e, std::type_index t);

            void Remove(Entity e);
            const std::vector<Entity>& GetBindableEntities()    const{ return m_bindable_entities; }
            const std::vector<Entity>& GetRemovableEntities()   const{ return m_removable_entities; }
    };

    template <typename T, typename ... Args> 
    Entity& Entity::AddComponent(Args && ... args)                       { GetManager().AddComponent<T>(*this, std::forward<Args>(args)...); return *this; }
    template<typename T> Entity& Entity::RemoveComponent()               { GetManager().RemoveComponent<T>(*this); return *this; }
    template<typename T> bool Entity::HasComponent()                const{ return GetManager().HasComponent<T>(*this); }
    template<typename T> T* Entity::GetComponent()                       { return GetManager().GetComponent<T>(*this); }

    template <typename T, typename ... Args> 
    void EntityManager::AddComponent(Entity e, Args && ... args)         { AddComponent(e, new T(std::forward<Args>(args)...)); }          
    template<typename T> void EntityManager::RemoveComponent(Entity e)   { RemoveComponent(e, typeid(T)); }
    template<typename T> bool EntityManager::HasComponent(Entity e) const{ return HasComponent(e, typeid(T)); }
    template<typename T> T* EntityManager::GetComponent(Entity e)        { return static_cast<T*>(GetComponent(e, typeid(T))); }
};