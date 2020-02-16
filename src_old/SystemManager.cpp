#include "SystemManager.h"
#include "System.h"
#include "Entity.h"
#include "Logger.h"

SystemManager::~SystemManager()
{
	for (auto& i : m_systems)
		delete i.second;
}

SystemManager& SystemManager::AddSystem(System* system)
{
	if (m_systems[typeid(*system)] == nullptr)
	{
		system->m_engine = m_engine;
		m_systems[typeid(*system)] = system;
	}
	else
		Logger::Log(LogLevel::LOG_WARNING, "System '%s' is already registered.", typeid(*system).name());

	return *this;
}

void SystemManager::BindToInterested(Entity& entity)
{
	for (auto& i : m_systems)
	{
		if (i.second->Matches(entity.GetBitFlag()))
			i.second->AddEntity(entity);
	}
}

void SystemManager::Initialize()
{
	for (auto& i : m_systems)
		i.second->InitializeSystems();
}

void SystemManager::Update(float deltaTime)
{
	for (auto& i : m_systems)
		i.second->UpdateSystems(deltaTime);
}
