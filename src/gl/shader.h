#ifndef GL_SHADER_H_
#define GL_SHADER_H_

#include <memory>
#include <string>

#include <absl/status/status.h>
#include <absl/status/statusor.h>
#include <GL/glew.h> 

#include "gl/abstract_object.h"

namespace ogl {

class Shader : public AbstractObject {
  public:
    using Ptr = std::unique_ptr<Shader>;

    enum ShaderType {
      VertexShader = GL_VERTEX_SHADER,
      FragmentShader = GL_FRAGMENT_SHADER,
    };

    ~Shader() override;

    static absl::StatusOr<Ptr> Create(
        const std::string& shader_source,
        const Shader::ShaderType type);

  private:
    Shader() noexcept = default;
    absl::Status Setup(const std::string& shader_source,
                       const ShaderType type);
};

}  // namespace ogl

#endif  // GL_SHADER_H_