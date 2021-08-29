#ifndef GL_TEXTURE_H_
#define GL_TEXTURE_H_

#include <string>

#include <GL/glew.h> 
#include <absl/status/status.h>
#include <glog/logging.h>

namespace ogl {

class Texture {
  public:
    Texture() = delete;
    explicit Texture(const std::string& filename);

    GLuint Id() const { return texture_; }
  private:
    GLuint texture_;
};

}  // namespace ogl

#endif  // GL_TEXTURE_H_