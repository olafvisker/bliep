#include "EntityManager.h"
#include "Entity.h"

EntityManager::~EntityManager()
{
	for (auto& i : m_entities)
		delete i.second;
}

Entity& EntityManager::CreateEntity()
{
	unsigned int id = m_uid.GetNextID();
	m_entities[id] = new Entity(id, m_engine);
	return *m_entities[id];
}

void EntityManager::DestroyEntity(unsigned int id)
{
	if (m_entities[id] != nullptr)
	{
		m_uid.FreeID(id);
		delete m_entities[id];
		m_entities.erase(id);
	}
	else
		Logger::Log(LogLevel::LOG_WARNING, "Entity '%i' is already destroyed", id);
}

Entity* EntityManager::GetEntity(unsigned int id)
{
	if (m_entities.count(id) > 0)
		return m_entities[id];

	Logger::Log(LogLevel::LOG_ERROR, "Entity '%i' does not exist", id);
	return nullptr;
}
