#ifndef RENDERER_ABSTRACT_RENDER_H_
#define RENDERER_ABSTRACT_RENDER_H_

#include <map>

#include <glog/logging.h>
#include <GL/glew.h> 
#include <absl/status/status.h>

#include "Eigen/Dense"
#include "gl/buffer.h"
#include "gl/framebuffer.h"
#include "gl/shader.h"
#include "gl/texture.h"
#include "gl/vertex_array.h"

namespace ogl {

class AbstractRenderer {
  public:
    virtual ~AbstractRenderer() = default;

    virtual void Render() const;
    virtual void Render(const Texture& texture) const;
    virtual void Render(const FrameBuffer& framebuffer) const;
    virtual void SetProjection(const Eigen::Matrix4f& projection) = 0;
    virtual void SetModelView(const Eigen::Matrix4f model_view) = 0;
    absl::Status UpdateTexture(const cv::Mat& image);
  protected:
    AbstractRenderer() = default;
  
    VertexArray vao_;
    std::map<std::string, ArrayBuffer> array_buffers_;
    IndexBuffer index_buffer_;
    std::unique_ptr<ShaderProgram> program_;
    std::unique_ptr<Texture> texture_;
};

}  // namespace ogl

#endif  // RENDERER_ABSTRACT_RENDER_H_
