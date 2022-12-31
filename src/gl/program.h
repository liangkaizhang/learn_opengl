#ifndef GL_PROGRAM_H_
#define GL_PROGRAM_H_

#include <memory>
#include <string>

#include <absl/status/status.h>
#include <absl/status/statusor.h>
#include <absl/strings/string_view.h>
#include "Eigen/Dense"
#include <GL/glew.h> 

#include "gl/texture.h"

namespace ogl {

class Program {
  public:
    using Ptr = std::shared_ptr<Program>;

    ~Program();

    Program(const Program&) = delete;
    Program & operator=(const Program&) = delete;

    void Use() const;
    GLuint GetAttribLocation(const std::string& attribute) const;

    void SetUniform(const std::string& name,
                    const Eigen::Matrix4f value) const;
    void SetUniform(const std::string& name,
                    const float value) const;
    void SetTexture(GLuint unit, const Texture& texture) const;

    static absl::StatusOr<Ptr> Create(
      const std::string& vertex_shader_source,
      const std::string& fragment_shader_source);
  
  private:
    Program() noexcept = default;
    absl::Status Setup(const std::string& vertex_shader_source,
                      const std::string& fragment_shader_source);

    GLuint program_;
};

}  // namespace ogl

#endif  // GL_PROGRAM_H_