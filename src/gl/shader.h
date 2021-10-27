#ifndef GL_SHADER_H_
#define GL_SHADER_H_

#include <string>

#include <GL/glew.h> 
#include <absl/status/status.h>
#include <glog/logging.h>

namespace ogl {

class Shader {
  public:
    enum Type {
      Vertex = GL_VERTEX_SHADER,
      Fragment = GL_FRAGMENT_SHADER,
    };

    explicit Shader(const Type type);
    ~Shader();

    absl::Status  Compile(const std::string& shader_source);
    GLuint Id() const;
  private:
    GLuint id_;
};

class ShaderProgram {
  public:
    ShaderProgram();
    ~ShaderProgram();

    absl::Status AttachShaders(
      const std::string& vertex_shader_source,
      const std::string& fragment_shader_source);
    void Use() const;
    GLuint GetAttribLocation(const std::string& attribute_name) const;
  private:
    GLuint program_ ;
};

}  // namespace ogl

#endif  // GL_SHADER_H_