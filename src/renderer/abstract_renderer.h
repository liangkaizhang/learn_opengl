#ifndef RENDERER_ABSTRACT_RENDER_H_
#define RENDERER_ABSTRACT_RENDER_H_

#include <map>

#include <glog/logging.h>
#include <GL/glew.h> 
#include <absl/status/status.h>

#include "gl/buffer.h"
#include "gl/shader.h"
#include "gl/vertex_array.h"

namespace ogl {

class AbstractRenderer {
  public:
    virtual void Render() const;
  protected:
    AbstractRenderer() = default;
    ~AbstractRenderer() = default;
  
    VertexArray vao_;
    ShaderProgram program_;
    ArrayBuffer pos_buffer_;
    ArrayBuffer color_buffer_;
    std::map<std::string, ArrayBuffer> array_buffers_;
    IndexBuffer index_buffer_;
};

}  // namespace ogl

#endif  // RENDERER_ABSTRACT_RENDER_H_
