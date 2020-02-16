#include "Mesh.h"
#include "Logger.h"

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &m_VAO);
}

void Mesh::Build()
{
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	glGenBuffers(NUM_BUFFERS, m_VBO);

	if (m_vertices.size() > 0)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO[POSITION_VB]);
		glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(m_vertices[0]), &m_vertices[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	}
	else
		Logger::Log(LogLevel::LOG_WARNING, "Mesh '%s' does not contain any defined vertices.", m_name.c_str());

	if (m_normals.size() > 0)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO[NORMAL_VB]);
		glBufferData(GL_ARRAY_BUFFER, m_normals.size() * sizeof(m_normals[0]), &m_normals[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	}
	else
		Logger::Log(LogLevel::LOG_WARNING, "Mesh '%s' does not contain any defined normals.", m_name.c_str());

	if (m_uvs.size() > 0)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO[UV_VB]);
		glBufferData(GL_ARRAY_BUFFER, m_uvs.size() * sizeof(m_uvs[0]), &m_uvs[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
	}
	else
		Logger::Log(LogLevel::LOG_WARNING, "Mesh '%s' does not contain any defined UVs.", m_name.c_str());

	if (m_indices.size() > 0)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_VBO[INDEX_VB]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(m_indices[0]), &m_indices[0], GL_STATIC_DRAW);
	}
	else
		Logger::Log(LogLevel::LOG_WARNING, "Mesh '%s' does not contain any defined indices.", m_name.c_str());

	glBindVertexArray(0);

	Logger::Log(LogLevel::LOG_INFO, "Mesh '%s' was build.", m_name.c_str());
}