#include <assert.h>

#include "entity.h"
#include "component.h"
#include "system.h"
#include "../core/logger.h"

namespace bliep {
    EntityManager& Entity::GetManager() const{ return *m_manager; }

    uint32_t Entity::GetId()        const{ return m_uid & IndexMask; }
    uint8_t Entity::GetVersion()    const{ return (m_uid >> IndexBits) & VersionMask; }
    unsigned Entity::GetFlag()      const{ return GetManager().GetFlag(*this); }
    unsigned Entity::GetOldFlag()   const{ return GetManager().GetOldFlag(*this); }

    bool Entity::IsValid()  const{ return GetManager().IsValid(*this); }
    void Entity::Destroy()       { return GetManager().Destroy(*this); }
    void Entity::Bind()          { GetManager().Bind(*this); }

    EntityManager::~EntityManager() {
        for (unsigned i = 0; i < m_components.size(); i++) {
            for (unsigned j = 0; j < m_components[i].size(); j++) {
                delete m_components[i][j];
            }
        }
    }

    Entity EntityManager::Create() { 
        uint32_t index;

        if (m_free_ids.size() > MIN_FREE_IDS) {
            index = m_free_ids.front();
            m_free_ids.pop_front();
        } else {
            m_versions.push_back(0);
            index = static_cast<unsigned int>(m_versions.size()) - 1;
            if (index >= m_bitflags.size()) { 
                m_bitflags.resize(index + EXTRA_ID_RESERVE); 
                m_old_bitflags.resize(index + EXTRA_ID_RESERVE); 
            }
        }

        Entity e(this, index, m_versions[index]);
        return e;
    }

    void EntityManager::Remove(Entity e){
        const auto id = e.GetId();
        const auto mask = m_bitflags[id];
        for (unsigned i = 0; i < m_components.size(); i++) {
            if (mask & (1 << i)) { delete m_components[i][id]; }
        }
        ++m_versions[id];
        m_free_ids.push_back(id);
        m_bitflags[id] = 0;
        m_old_bitflags[id] = 0;
    }

    Entity EntityManager::Get(uint32_t id)          { return Entity(this, id, m_versions[id]); }
    unsigned EntityManager::GetFlag(Entity e)       { return m_bitflags[e.GetId()]; }
    unsigned EntityManager::GetOldFlag(Entity e)    { return m_old_bitflags[e.GetId()]; }
    void EntityManager::UpdateFlags(Entity e)       { m_old_bitflags[e.GetId()] = m_bitflags[e.GetId()]; }
    void EntityManager::Destroy(Entity e)           { m_removable_entities.push_back(e); }

    void EntityManager::Bind(Entity e) { 
        m_bindable_entities.push_back(e); 
    }

    void EntityManager::Clear() {
        m_bindable_entities.clear();
        m_removable_entities.clear();
    }

    bool EntityManager::IsValid(Entity e) const{
        const uint32_t id = e.GetId();
        return m_versions[id] == e.GetVersion();
    }

    void EntityManager::AddComponent(Entity e, Component* c) {
        const auto c_id = Components::GetId(typeid(*c));
        const auto e_id = e.GetId();
        unsigned int bit = 1 << c_id;

        if (c_id >= m_components.size())        { m_components.push_back(std::vector<Component*>()); }
        if (e_id >= m_components[c_id].size())  { m_components[c_id].resize(e_id + 1, nullptr); }         
        if (HasComponent(e, typeid(*c)))        { LOGW << "Entity '" << e_id << "' already contains component '" << typeid(*c).name() << "'."; return; }

        m_components[c_id][e_id] = c;   
        m_bitflags[e_id] |= bit; 
    }

    void EntityManager::RemoveComponent(Entity e, std::type_index t) {
        int c_id = Components::GetId(t);
        int e_id = e.GetId();
        unsigned int bit = 1 << c_id;        
        if (!HasComponent(e, t)) { LOGW << "Can't remove component '" << t.name() << "' from entity '" << e_id << "' as it does not contain that component"; return; }

        delete m_components[c_id][e_id];
        m_bitflags[e_id] &= ~bit;
    }

    bool EntityManager::HasComponent(Entity e, std::type_index t) const{
        int c_id = Components::GetId(t);
        int e_id = e.GetId();
        unsigned int bit = 1 << c_id;
        return m_bitflags[e_id] & bit;
    }

    Component* EntityManager::GetComponent(Entity e, std::type_index t) {
        int c_id = Components::GetId(t);
        int e_id = e.GetId();
        if (!HasComponent(e, t)) { LOGW << "Entity '" << e_id << "' does not contain component '" << t.name() << "'."; return nullptr; }
        return m_components[c_id][e_id];
    }
};