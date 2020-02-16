#include "mesh.h"
#include "../core/logger.h"

namespace bliep {
    Mesh::~Mesh() {
        glDeleteVertexArrays(1, &m_vao);
    }

    void Mesh::Build() {
        glGenVertexArrays(1, &m_vao);
        glBindVertexArray(m_vao);

        glGenBuffers(NUM_BUFFERS, m_vbo);

        if (m_vertices.size() > 0) {
            glBindBuffer(GL_ARRAY_BUFFER, m_vbo[POSITION_VB]);
            glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(m_vertices[0]), &m_vertices[0], GL_STATIC_DRAW);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        }
        else { LOGW << "Mesh does not contain any defined vertices."; }

        if (m_normals.size() > 0) {
            glBindBuffer(GL_ARRAY_BUFFER, m_vbo[NORMAL_VB]);
            glBufferData(GL_ARRAY_BUFFER, m_normals.size() * sizeof(m_normals[0]), &m_normals[0], GL_STATIC_DRAW);
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
        }
        else { LOGW << "Mesh does not contain any defined normals."; }

        if (m_uvs.size() > 0) {
            glBindBuffer(GL_ARRAY_BUFFER, m_vbo[UV_VB]);
            glBufferData(GL_ARRAY_BUFFER, m_uvs.size() * sizeof(m_uvs[0]), &m_uvs[0], GL_STATIC_DRAW);
            glEnableVertexAttribArray(2);
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
        }
        else { LOGW << "Mesh does not contain any defined uvs."; }

        if (m_indices.size() > 0) {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vbo[INDEX_VB]);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(m_indices[0]), &m_indices[0], GL_STATIC_DRAW);
        }
        else { LOGW << "Mesh does not contain any defined indices."; }

        glBindVertexArray(0);
    }
}