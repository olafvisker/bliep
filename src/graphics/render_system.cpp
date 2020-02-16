#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "render_system.h"

#include "../core/timer.h"
#include "../components/transform.h"
#include "../components/mesh_renderer.h"
#include "../components/camera.h"

#include "../core/engine.h"
#include "../math/math.h"

namespace bliep {
    
    void RenderSystem::Init() {
        Require<Transform>(Sets::CAMERAS);
        Require<Camera>(Sets::CAMERAS);

        Require<Transform>(Sets::OBJECTS);
        Require<MeshRenderer>(Sets::OBJECTS);
    }
    
    void RenderSystem::Draw() {
        for (auto c : GetEntities(Sets::CAMERAS)) {        
            Transform* cam_trans = c.GetComponent<Transform>();
            Camera* cam = c.GetComponent<Camera>();

            GetEngine().GetWindow().SetViewport(cam->viewport.x, cam->viewport.y, cam->viewport.width, cam->viewport.height);
            
            for (auto e : GetEntities(Sets::OBJECTS)) {
                Transform* trans = e.GetComponent<Transform>();
                MeshRenderer* mesh_r = e.GetComponent<MeshRenderer>();

                // trans->rotation.x += 0.01; //DEBUG
                // trans->rotation.y += 0.02; //DEBUG
                // trans->rotation.z += 0.03; //DEBUG

                mesh_r->mesh->GetMaterial().Bind();
                mesh_r->mesh->GetMaterial().SetWorldModel(Math::Matrix(trans->position, trans->rotation, trans->scale));
                mesh_r->mesh->GetMaterial().SetView(Math::LookAt(cam_trans->position, cam_trans->position + Math::Forward(cam_trans->rotation), Math::Up(cam_trans->rotation)));
	            mesh_r->mesh->GetMaterial().SetProjection(Math::Projection(cam->field_of_view, (float)cam->viewport.width / (float)cam->viewport.height, cam->near_plane, cam->far_plane));
	            mesh_r->mesh->GetMaterial().SetNormal(Math::Normal(trans->position, trans->rotation, trans->scale));
	            mesh_r->mesh->GetMaterial().SetViewPosition(cam_trans->position);
                
                glBindVertexArray(mesh_r->mesh->GetVAO());
                if (mesh_r->mesh->GetIndices().size() > 0)  { glDrawElements(GL_TRIANGLES, mesh_r->mesh->GetIndices().size(), GL_UNSIGNED_INT, 0); }
                else                                        { glDrawArrays(GL_TRIANGLES, 0, mesh_r->mesh->GetVertices().size()); }
                glBindVertexArray(0);
            }
        }
    }
}