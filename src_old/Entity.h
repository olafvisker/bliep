#pragma once
#include <map>
#include <vector>
#include <typeindex>

#include "Component.h"
#include "Logger.h"

class System;
class Engine;

class Entity
{
	friend class EntityManager;
public:
	virtual ~Entity();

	void SetName(const std::string& name) { m_name = name; }
	std::string GetName() { return m_name; }

	unsigned int GetID() { return m_id; }
	unsigned int GetBitFlag() { return m_bitflag; }

	Entity& AddComponent(Component* component);

	template<typename T>
	Entity& RemoveComponent()
	{
		if (m_components[typeid(T)] != nullptr)
		{
			m_bitflag &= ~m_components[typeid(T)]->GetBitFlag();
			delete m_components[typeid(T)];
			m_components.erase(typeid(T));
		}
		else
			Logger::Log(LogLevel::WARNING, "Cannot remove component '%s' from entity '%i' because it does not have one.",
			typeid(T).name(), m_id);

		return *this;
	}

	template<typename T>
	Component* GetComponent()
	{
		if (m_components[typeid(T)] != nullptr)
			return m_components[typeid(T)];

		Logger::Log(LogLevel::LOG_ERROR, "Entity '%s, %i' does not contain component '%s'.", m_name.c_str(), m_id, typeid(T).name());
		return nullptr;
	}

	Entity& Refresh();

	Engine& GetEngine() { return *m_engine; }
	void AddParentSystem(System *system);

private:
	std::string m_name = "UNDEFINED";

	unsigned int m_id;
	unsigned int m_bitflag;

	Engine* m_engine;

	std::map<std::type_index, Component*> m_components;
	std::vector<System*> m_parentSystems;

	Entity(unsigned int id, Engine* engine);
};

