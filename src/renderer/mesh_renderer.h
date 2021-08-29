#ifndef RENDERER_MESH_RENDER_H_
#define RENDERER_MESH_RENDER_H_

#include <absl/status/status.h>
#include <GL/glew.h> 

#include "renderer/abstract_renderer.h"
#include "geometry/colored_mesh.h"
#include "gl/shader.h"

namespace ogl {

class MeshRender : public AbstractRenderer {
  public:
    absl::Status Init(const Shader& shader, const ColoredMesh& mesh);
};

}  // namespace ogl

#endif  // RENDERER_MESH_RENDER_H_
