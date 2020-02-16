#pragma once
#include <map>

#include "UID.h"

class Entity;

class EntityManager
{
	friend class Engine;
public:
	~EntityManager();

	Entity& CreateEntity();
	void DestroyEntity(unsigned int id);
	Entity* GetEntity(unsigned int id);

private:
	Engine* m_engine;

	std::map<unsigned int, Entity*> m_entities;

	UID m_uid;

	EntityManager(Engine* engine) : m_engine(engine) { }
};

