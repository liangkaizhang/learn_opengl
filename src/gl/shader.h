#ifndef GL_SHADER_H_
#define GL_SHADER_H_

#include <string>

#include <GL/glew.h> 
#include <absl/status/status.h>
#include <glog/logging.h>

namespace ogl {

class Shader {
  public:
    Shader() = default;
    ~Shader();

    absl::Status Compile(const std::string& vertex_shader_source,
                         const std::string& fragment_shader_source);
    GLuint Program() const { return program_;};
    GLuint GetAttributeLocation(const std::string& attribute_name) const;
  private:
    absl::Status CompileShader(const GLuint shader_id,
                               const std::string& shader_source) const;
    absl::Status LinkShaders(const GLuint vertex_shader,
                             const GLuint fragment_shader);
    GLuint program_ ;
};

}  // namespace ogl

#endif  // GL_SHADER_H_