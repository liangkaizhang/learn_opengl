#include "gl/shader.h"

namespace ogl {

Shader::~Shader() {
    glDeleteProgram(program_);
}

absl::Status Shader::Compile(
    const std::string& vertex_shader_source,
    const std::string& fragment_shader_source) {
    // Vertex shader.
    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    if (!CompileShader(vertex_shader, vertex_shader_source).ok()) {
        return absl::InvalidArgumentError("Fail to compile vertext shader.");
    }
    // Fragment shader.
    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    if (!CompileShader(fragment_shader, fragment_shader_source).ok()) {
        return absl::InvalidArgumentError("Fail to compile fragment shader.");
    }
    return LinkShaders(vertex_shader, fragment_shader);
}

GLuint Shader::GetAttributeLocation(const std::string& attribute_name) const {
    return glGetAttribLocation(program_, attribute_name.c_str());
}

absl::Status Shader::CompileShader(const GLuint shader_id,
                                   const std::string& shader_source) const {
    const GLchar* source = (const GLchar*)shader_source.c_str();
    glShaderSource(shader_id, 1, &source, NULL);
    glCompileShader(shader_id);
    // check for shader compile errors.
    GLint success = GL_FALSE;
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
    if (success != GL_TRUE) {
        std::string info_log;
        info_log.resize(512);
        glGetShaderInfoLog(shader_id, 512, NULL, &info_log[0]);
        return absl::InvalidArgumentError("Failed to compile shader, error: " + info_log);
    }
    return absl::OkStatus();
}

absl::Status Shader::LinkShaders(const GLuint vertex_shader,
                                 const GLuint fragment_shader) {
    // link shaders
    program_ = glCreateProgram();
    glAttachShader(program_, vertex_shader);
    glAttachShader(program_, fragment_shader);
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
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    return absl::OkStatus();
}

}  // namespace ogl