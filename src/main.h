#pragma once
#include "core/engine.h"

class Main : public bliep::Engine {
public:
	Main() { }
	~Main() { }

	void Init();
	void Update();
	void Draw();
};