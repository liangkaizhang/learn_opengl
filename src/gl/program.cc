#include "gl/program.h"

#include <memory>
#include <string>

#include <glog/logging.h>
#include <GL/glew.h> 
#include <absl/status/status.h>
#include <absl/status/statusor.h>
#include "Eigen/Dense"

#include "utils/utils.h"
#include "gl/shader.h"
#include "gl/texture.h"

namespace ogl {

Program::~Program() {
    glDeleteProgram(program_);
}

void Program::Use() const {
    glUseProgram(program_);
}

GLuint Program::GetAttribLocation(const std::string& attribute) const {
    this->Use();
    return glGetAttribLocation(program_, attribute.c_str());
}

void Program::SetUniform(const std::string& name, const Eigen::Matrix4f value) const {
    this->Use();
    const GLuint id = glGetUniformLocation(program_, name.c_str());
    glUniformMatrix4fv(id, 1, GL_FALSE, value.data());
}

void Program::SetUniform(const std::string& name, const float value) const {
    this->Use();
    const GLuint id = glGetUniformLocation(program_, name.c_str());
    glUniform1f(id, value);
}

void Program::SetTexture(GLuint unit, const Texture& texture) const {
    this->Use();
    glActiveTexture(GL_TEXTURE0 + unit);
    texture.Bind();
}

absl::Status Program::Setup(const std::string& vertex_shader_source,
                            const std::string& fragment_shader_source) {
    program_ = glCreateProgram();
    // Compile shaders.
    
   ASSIGN_OR_RETURN(const auto vertex_shader,
                    Shader::Create(vertex_shader_source,
                                   Shader::VertexShader));
   ASSIGN_OR_RETURN(const auto fragment_shader,
                    Shader::Create(fragment_shader_source,
                                   Shader::FragmentShader));
    // Attach shaders.
    glAttachShader(program_, vertex_shader->Id());
    glAttachShader(program_, fragment_shader->Id());
    glLinkProgram(program_);

    // check for linking errors
    GLint success;
    glGetProgramiv(program_, GL_LINK_STATUS, &success);
    if (!success) {
        std::string info_log;
        info_log.resize(512);
        glGetProgramInfoLog(program_, 512, NULL, &info_log[0]);
        return absl::InvalidArgumentError("ERROR::SHADER::PROGRAM::LINKING_FAILED: " + info_log);
    }
    return absl::OkStatus();
}

absl::StatusOr<Program::Ptr> Program::Create(
    const std::string& vertex_shader_source,
    const std::string& fragment_shader_source) {
    auto program = Ptr(new Program);
    RETURN_IF_ERROR(program->Setup(vertex_shader_source, fragment_shader_source));
    return program;
}

}  // namespace ogl