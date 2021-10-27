#include "gl/shader.h"

namespace ogl {

Shader::Shader(const Type type) {
    id_ = glCreateShader(type);
}

Shader::~Shader() {
    glDeleteShader(id_);
}

absl::Status Shader::Compile(const std::string& shader_source) {
    const GLchar* source = (const GLchar*)shader_source.c_str();
    glShaderSource(id_, 1, &source, NULL);
    glCompileShader(id_);
    // check for shader compile errors.
    GLint success = GL_FALSE;
    glGetShaderiv(id_, GL_COMPILE_STATUS, &success);
    if (success != GL_TRUE) {
        std::string info_log;
        info_log.resize(512);
        glGetShaderInfoLog(id_, 512, NULL, &info_log[0]);
        return absl::InvalidArgumentError("Failed to compile shader, error: " + info_log);
    }
    return absl::OkStatus();
}

GLuint Shader::Id() const { return id_; }

ShaderProgram::ShaderProgram() {
    program_ = glCreateProgram();
}

ShaderProgram::~ShaderProgram() {
    glDeleteProgram(program_);
}

void ShaderProgram::Use() const {
    glUseProgram(program_);
}

absl::Status ShaderProgram::AttachShaders(
    const std::string& vertex_shader_source,
    const std::string& fragment_shader_source) {
    // Compile shaders.
    auto vertex_shader = Shader(Shader::Vertex);
    CHECK(vertex_shader.Compile(vertex_shader_source).ok());
    auto fragment_shader = Shader(Shader::Fragment);
    CHECK(fragment_shader.Compile(fragment_shader_source).ok());
    // Attach shaders.
    glAttachShader(program_, vertex_shader.Id());
    glAttachShader(program_, fragment_shader.Id());
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

GLuint ShaderProgram::GetAttributeLocation(const std::string& attribute_name) const {
    return glGetAttribLocation(program_, attribute_name.c_str());
}

}  // namespace ogl