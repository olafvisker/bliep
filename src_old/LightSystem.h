#pragma once
#include "System.h"

class LightSystem : public System
{
public:
	LightSystem();
	~LightSystem();

	void InitializeSystem() { }
	void Initialize(Entity& entity) { }
	void Process(float deltaTime, Entity& entity) { }
};

