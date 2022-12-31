#include "gl/shader.h"

#include <memory>
#include <string>

#include <absl/status/status.h>
#include <absl/status/statusor.h>
#include <GL/glew.h> 

#include "utils/utils.h"

namespace ogl {

Shader::~Shader() {
    glDeleteShader(id_);
}

absl::Status Shader::Setup(const std::string& shader_source,
                           const ShaderType type) {
    id_ = glCreateShader(type);
    const auto source = shader_source.c_str();
    glShaderSource(id_, 1, &source, NULL);
    glCompileShader(id_);
    // check for shader compile errors.
    GLint success = GL_FALSE;
    glGetShaderiv(id_, GL_COMPILE_STATUS, &success);
    if (success != GL_TRUE) {
        std::string info_log;
        info_log.resize(512);
        glGetShaderInfoLog(id_, 512, NULL, &info_log[0]);
        return absl::InvalidArgumentError(
            "Failed to compile shader, error: " + info_log);
    }
    return absl::OkStatus();
}

absl::StatusOr<Shader::Ptr> Shader::Create(
    const std::string& shader_source,
    const Shader::ShaderType type) {
    auto shader = Ptr(new Shader);
    RETURN_IF_ERROR(shader->Setup(shader_source, type));
    return shader;
}

}  // namespace ogl