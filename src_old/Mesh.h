#pragma once
#include <GLM/glm.hpp>
#include <GL/glew.h>
#include <map>
#include <vector>

class Mesh
{
public:
	Mesh() { }
	~Mesh();

	GLuint GetVAO() { return m_VAO; }
	std::vector<glm::vec3>& Vertices()				{ return m_vertices; }
	std::vector<unsigned int>& Indices()			{ return m_indices; }
	std::vector<glm::vec3>& Normals()				{ return m_normals; }
	std::vector<glm::vec2>& UVs()					{ return m_uvs; }
	unsigned int& MaterialIndex()					{ return m_materialIndex; }

	std::string GetName() { return m_name; }
	void SetName(const std::string& name) { m_name = name; }

	void Build();

protected:
	enum
	{
		POSITION_VB,
		NORMAL_VB,
		UV_VB,
		INDEX_VB,

		NUM_BUFFERS
	};

	GLuint m_VAO;
	GLuint m_VBO[NUM_BUFFERS];

	std::string m_name = "UNDEFINED";

	std::vector<glm::vec3> m_vertices;
	std::vector<unsigned int> m_indices;
	std::vector<glm::vec3> m_normals;
	std::vector<glm::vec2> m_uvs;
	unsigned int m_materialIndex = 0;
};

