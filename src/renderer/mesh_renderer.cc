#include "renderer/mesh_renderer.h"

namespace ogl {
namespace {

const std::string kVertexShaderSource =
    "#version 330 core\n"
    "layout (location = 0) in vec3 a_position;\n"
    "layout (location = 1) in vec3 a_texcoord;\n"
    "out vec2 texcoord;\n"
    "uniform mat4 model_view;\n"
    "uniform mat4 projection;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = projection * model_view * vec4(a_position, 1.0);\n"
    "   texcoord = vec2(a_texcoord.x, 1 - a_texcoord.y);\n"
    "}\0";

const std::string kFragmentShaderSource =
    "#version 330 core\n"
    "out vec4 frag_color;\n"
    "in vec2 texcoord;\n"
    "uniform sampler2D u_texture;\n"
    "void main()\n"
    "{\n"
    "   frag_color = texture(u_texture, texcoord);\n"
    "}\n\0";

}  // namespace

std::unique_ptr<AbstractRenderer> MeshRender::Create(
        const Mesh& mesh) {
    auto render_ptr = absl::make_unique<MeshRender>();
    const auto status = render_ptr->Init(kVertexShaderSource,
                                         kFragmentShaderSource, mesh);
    if (!status.ok()) render_ptr.reset(nullptr);
    return render_ptr;
}

void MeshRender::SetProjection(const Eigen::Matrix4f& projection) {
    program_->SetUniform("projection", projection);
}

void MeshRender::SetModelView(const Eigen::Matrix4f model_view) {
    program_->SetUniform("model_view", model_view);
}

absl::Status MeshRender::Init(
        const std::string& vertex_shader_source,
        const std::string& fragment_shader_source,
        const Mesh& mesh) {
    // Set shader program.
    if (!program_) {
        program_ = absl::make_unique<ShaderProgram>();
    }
    CHECK(program_->AttachShaders(vertex_shader_source, fragment_shader_source).ok());
    SetProjection(Eigen::Matrix4f::Identity());
    SetModelView(Eigen::Matrix4f::Identity());

    vao_.Bind();
    // Buffer position data.
    if (!mesh.positions.empty()) {
        auto& position_buffer = array_buffers_["a_position"];
        position_buffer.BufferData(GL_FLOAT, GL_STATIC_DRAW, 3,
                                mesh.positions.size(),
                                &(mesh.positions[0]));
    }
    // Buffer color data.
    if (!mesh.colors.empty()) {
        auto& color_buffer = array_buffers_["a_color"];
        color_buffer.BufferData(GL_FLOAT, GL_STATIC_DRAW, 3,
                                mesh.colors.size(),
                                &(mesh.colors[0]));
    }
    // Buffer texture coord and texture data.
    if (!mesh.uv_coords.empty()) {
        auto& uv_coord_buffer = array_buffers_["a_texcoord"];
        uv_coord_buffer.BufferData(GL_FLOAT, GL_STATIC_DRAW, 2,
                                   mesh.uv_coords.size(),
                                   &(mesh.uv_coords[0]));
        if (!texture_) {
            texture_ = absl::make_unique<Texture>();
        }
        const auto image = cv::imread(mesh.texture_filename);
        CHECK(texture_->BufferData(image).ok());
    }
    // Buffer index data.
    CHECK(!mesh.indices.empty());
    index_buffer_.BufferData(GL_UNSIGNED_INT, GL_STATIC_DRAW,
                             mesh.indices.size(),
                             &(mesh.indices[0]));
    vao_.Unbind();
    return absl::OkStatus();
}

}  // namespace ogl