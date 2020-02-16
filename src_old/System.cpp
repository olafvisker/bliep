#include "System.h"
#include "Entity.h"

void System::RegisterRequired(unsigned int bitflag)
{
	m_bitflag |= bitflag;
}

bool System::Matches(unsigned int bitflag)
{
	return ((m_bitflag & ~bitflag) == 0);
}

void System::AddEntity(Entity& entity)
{
	entity.AddParentSystem(this);
	m_entities[entity.GetID()] = &(entity);
}

void System::RemoveEntity(Entity& entity)
{
	m_entities.erase(entity.GetID());
}

void System::InitializeSystems()
{
	InitializeSystem();
	for (auto& i : m_entities)
		Initialize(*i.second);
}

void System::UpdateSystems(float deltaTime)
{
	for (auto& i : m_entities)
		Process(deltaTime, *i.second);
}
