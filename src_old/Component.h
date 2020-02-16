#pragma once
#include "Engine.h"

enum ComponentType
{
	COM_EMPTY				= 0,
	COM_TRANSFORM			= 1 << 0,
	COM_MODELRENDERER		= 1 << 1,
	COM_CAMERA				= 1 << 2,
	COM_CAMERACONTROLLER	= 1 << 3,
	COM_LIGHT				= 1 << 4,
};

class Component
{
	friend class Entity;
public:
	virtual ~Component() { }

	unsigned int GetBitFlag() { return m_bitflag; }

protected:
	Component(unsigned int bitflag) : m_bitflag(bitflag) { }
	Engine& GetEngine() { return *m_engine; }

private:
	unsigned int m_bitflag;
	Engine* m_engine;
};

