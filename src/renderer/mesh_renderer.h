#ifndef RENDERER_MESH_RENDER_H_
#define RENDERER_MESH_RENDER_H_

#include <absl/status/status.h>
#include <GL/glew.h> 

#include "Eigen/Dense"
#include "renderer/abstract_renderer.h"
#include "geometry/mesh.h"

namespace ogl {

class MeshRender : public AbstractRenderer {
  public:
    ~MeshRender() = default;
    static std::unique_ptr<AbstractRenderer> Create(const Mesh& mesh);

    void SetProjection(const Eigen::Matrix4f& projection) override;
    void SetModelView(const Eigen::Matrix4f model_view) override;
  private:
    absl::Status Init(
        const std::string& vertex_shader_source,
        const std::string& fragment_shader_source,
        const Mesh& mesh);
};

}  // namespace ogl

#endif  // RENDERER_MESH_RENDER_H_
