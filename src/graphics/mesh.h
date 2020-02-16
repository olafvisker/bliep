#pragma once
#include <GLM/glm.hpp>
#include <GL/glew.h>
#include <vector>

namespace bliep {

    class Material;

    class Mesh {
        public:
            Mesh() { }
            ~Mesh();

            GLuint GetVAO()                               const{ return m_vao; }
            const std::vector<glm::vec3>& GetVertices()   const{ return m_vertices; }
            const std::vector<unsigned int>& GetIndices() const{ return m_indices; }
            const std::vector<glm::vec3>& GetNormals()    const{ return m_normals; }
            const std::vector<glm::vec3>& GetTangets()    const{ return m_tangents; }
            const std::vector<glm::vec3>& GetBitangents() const{ return m_bitangents; }
            const std::vector<glm::vec2>& GetUVs()        const{ return m_uvs; }
            Material& GetMaterial()                            { return *m_material; }

            void SetVertices(const std::vector<glm::vec3>& vertices)        { m_vertices = vertices; }
            void SetIndices(const std::vector<unsigned int>& indices)       { m_indices = indices; }
            void SetNormals(const std::vector<glm::vec3>& normals)          { m_normals = normals; }
            void SetTangets(const std::vector<glm::vec3>& tangents)         { m_tangents = tangents; }
            void SetBitangents(const std::vector<glm::vec3>& bitangents)    { m_bitangents = bitangents; }
            void SetUVs(const std::vector<glm::vec2>& uvs)                  { m_uvs = uvs; }
            void SetMaterial(Material* material)                            { m_material = material; }

            void Build();

        protected:
            enum {
                POSITION_VB,
                NORMAL_VB,
                UV_VB,
                INDEX_VB,
                NUM_BUFFERS
            };

            GLuint m_vao;
            GLuint m_vbo[NUM_BUFFERS];

            std::vector<glm::vec3> m_vertices;
            std::vector<unsigned> m_indices;
            std::vector<glm::vec3> m_normals;
            std::vector<glm::vec3> m_tangents;
            std::vector<glm::vec3> m_bitangents;
            std::vector<glm::vec2> m_uvs;            
            Material* m_material;
    };
}

