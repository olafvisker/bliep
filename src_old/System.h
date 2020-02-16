#pragma once
#include <map>

#include "Engine.h"

class Entity;

class System
{
	friend class SystemManager;
public:
	virtual ~System() { }

	void RegisterRequired(unsigned int bitflag);
	bool Matches(unsigned int bitflag);

	void AddEntity(Entity& entity);
	void RemoveEntity(Entity& entity);

	void InitializeSystems();
	virtual void InitializeSystem() = 0;
	virtual void Initialize(Entity& entity) = 0;

	void UpdateSystems(float deltaTime);
	virtual void Process(float deltaTime, Entity& entity) = 0;

	Engine& GetEngine() { return *m_engine; }
	std::map<unsigned int, Entity*>& GetEntities() { return m_entities; }

protected:
	System() : m_bitflag(0) { }

private:
	Engine* m_engine;

	unsigned int m_bitflag;
	std::map<unsigned int, Entity*> m_entities;
};

