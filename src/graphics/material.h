#pragma once
#include <vector>
#include <string>
#include <glm/glm.hpp>


namespace bliep {
    class Shader;
    class Texture;
    struct color;
    
    class Material {
        public:
            Material() { }
            ~Material() { }

            void Bind();
            void Unbind();

            Shader& GetShader() const;
            void SetShader(Shader* shader);

            void SetWorldModel(const glm::mat4 model);
            void SetView(const glm::mat4 view);
            void SetProjection(const glm::mat4 projection);
            void SetNormal(const glm::mat3& normal);
            void SetViewPosition(const glm::vec3& position);

            void SetDiffuse(Texture* diffuse);
            void SetSpecular(Texture* specular);
            void SetShininess(const float shininess);

        private:
            Shader* m_shader        = nullptr;

            Texture* m_diffuse      = nullptr;
            Texture* m_specular     = nullptr;
            
            void BindShader();
            void BindTextures();
    };

    namespace MaterialDefinitions {
        const std::string WORLDMODEL                = "model";
        const std::string VIEW                      = "view";
        const std::string PROJECTION                = "projection";
        const std::string NORMAL                    = "normal";
        const std::string VIEWPOSITION              = "view_pos";

        const std::string MAT_DEFINITION            = "material.";
        const std::string MAT_DIFFUSE               = MAT_DEFINITION + "diffuse";
        const std::string MAT_SPECULAR              = MAT_DEFINITION + "specular";
        const std::string MAT_SHININESS             = MAT_DEFINITION + "shininess";

        // const std::string LIGHT_DIR_DEFINITION      = "dirlight.";
        // const std::string LIGHT_POINT_DEFINITION    = "pointlight.";
        // const std::string LIGHT_SPOT_DEFINITION     = "spotlight.";

        // const std::string LIGHT_DIRECTION           = "direction";
        // const std::string LIGHT_AMBIENT             = "ambient";
        // const std::string LIGHT_DIFFUSE             = "diffuse";
        // const std::string LIGHT_SPECULAR            = "specular";
    };
}