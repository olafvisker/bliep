#include "Entity.h"
#include "System.h"

Entity::Entity(unsigned int id, Engine* engine) :
m_id(id),
m_bitflag(0),
m_engine(engine)
{ }

Entity::~Entity()
{
	for (auto& i : m_components)
		delete i.second;

	for (auto& i : m_parentSystems)
		i->RemoveEntity(*this);
}

Entity& Entity::AddComponent(Component* component)
{
	if (m_components[typeid(*component)] == nullptr)
	{
		component->m_engine = m_engine;
		m_components[typeid(*component)] = component;
		m_bitflag |= component->GetBitFlag();
	}
	else
		Logger::Log(LogLevel::LOG_WARNING, "Entity '%i' already contains component '%s'.", m_id, typeid(*component).name());

	return *this;
}

void Entity::AddParentSystem(System* system)
{
	m_parentSystems.push_back(system);
}

Entity& Entity::Refresh()
{
	for (auto& i : m_parentSystems)
		i->RemoveEntity(*this);

	m_parentSystems.clear();

	m_engine->GetSystemManager().BindToInterested(*this);
	return *this;
}
