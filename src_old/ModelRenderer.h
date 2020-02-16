#pragma once
#include "Model.h"
#include "Component.h"

class ModelRenderer : public Component
{
public:
	ModelRenderer() : Component(ComponentType::COM_MODELRENDERER) { }
	~ModelRenderer() { }

	void SetModel(Model* model)	{ m_model = model; }
	Model& GetModel()			{ return *m_model; }

private:
	Model* m_model;
};