#include "LightSystem.h"
#include "Component.h"
#include "Entity.h"
#include "Light.h"

LightSystem::LightSystem()
{
	RegisterRequired(ComponentType::COM_TRANSFORM);
	RegisterRequired(ComponentType::COM_LIGHT);
}

LightSystem::~LightSystem()
{ }