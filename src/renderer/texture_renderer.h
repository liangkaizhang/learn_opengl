#ifndef RENDERER_TEXTURE_RENDER_H_
#define RENDERER_TEXTURE_RENDER_H_

#include <absl/status/status.h>
#include <GL/glew.h> 

#include "renderer/abstract_renderer.h"
#include "geometry/textured_mesh.h"
#include "gl/shader.h"
#include "gl/texture.h"

namespace ogl {

class TextureRender : public AbstractRenderer {
  public:
    absl::Status Init(const Shader& shader, const TexturedMesh& mesh, const Texture& texture);
    void Render() const final;
  private:
    GLuint texture_;
};

}  // namespace ogl

#endif  // RENDERER_TEXTURE_RENDER_H_
