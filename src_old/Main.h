#pragma once
#include "Engine.h"

class Main : public Engine
{
public:
	Main() { }
	~Main() { }

	void Initialize();
	void Update(float deltaTime);
};