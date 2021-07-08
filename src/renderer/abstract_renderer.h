#ifndef RENDERER_ABSTRACT_RENDER_H_
#define RENDERER_ABSTRACT_RENDER_H_

#include <absl/status/status.h>
#include <GL/glew.h> 

#include "renderer/shader.h"
#include "renderer/geometry.h"

namespace ogl {

class AbstractRenderer {
  public:
    AbstractRenderer() = default;
    virtual ~AbstractRenderer() = default;

    virtual absl::Status Init(const Shader& shader, const Geometry& geometry);
    void Render() const;
  protected:
    GLuint vao_;
    GLuint vbo_;
    GLuint ebo_;
    GLuint program_;
};

}  // namespace ogl

#endif  // RENDERER_ABSTRACT_RENDER_H_
