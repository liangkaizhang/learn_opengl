#ifndef RENDERER_MESH_RENDER_H_
#define RENDERER_MESH_RENDER_H_

#include <absl/status/status.h>
#include <GL/glew.h> 

#include "renderer/abstract_renderer.h"
#include "geometry/colored_mesh.h"

namespace ogl {

class MeshRender : public AbstractRenderer {
  public:
    static std::unique_ptr<MeshRender> Create(
        const std::string& vertex_shader_source,
        const std::string& fragment_shader_source,
        const ColoredMesh& mesh);
  private:
    absl::Status Init(
        const std::string& vertex_shader_source,
        const std::string& fragment_shader_source,
        const ColoredMesh& mesh);
};

}  // namespace ogl

#endif  // RENDERER_MESH_RENDER_H_
