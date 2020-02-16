#pragma once

class ResourceManager;

class Factory
{
public:
	Factory(ResourceManager* resourceManager) : m_resourceManager(resourceManager) { }
	virtual ~Factory() { }

protected:
	ResourceManager* m_resourceManager;
};