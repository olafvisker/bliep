#pragma once
#include <map>
#include <typeindex>

class Entity;
class System;

class SystemManager
{
	friend class Engine;
public:
	~SystemManager();

	SystemManager& AddSystem(System* system);
	template <typename T>
	T* GetSystem() { return (T*)m_systems[typeid(T)]; }

	void BindToInterested(Entity& entity);

	void Initialize();
	void Update(float deltaTime);

private:
	std::map<std::type_index, System*> m_systems;

	Engine* m_engine;

	SystemManager(Engine* engine) : m_engine(engine) { }
};

