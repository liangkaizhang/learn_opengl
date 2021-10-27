#include "renderer/mesh_renderer.h"

namespace ogl {

std::unique_ptr<MeshRender> MeshRender::Create(
        const std::string& vertex_shader_source,
        const std::string& fragment_shader_source,
        const ColoredMesh& mesh) {
    auto render_ptr = absl::make_unique<MeshRender>();
    const auto status = render_ptr->Init(vertex_shader_source,
                                         fragment_shader_source, mesh);
    if (!status.ok()) render_ptr.reset(nullptr);
    return render_ptr;
}

void MeshRender::SetProjection(const Eigen::Matrix4f& projection) {
    program_.SetUniform("projection", projection);
}

void MeshRender::SetModelView(const Eigen::Matrix4f model_view) {
    program_.SetUniform("model_view", model_view);
}

absl::Status MeshRender::Init(
        const std::string& vertex_shader_source,
        const std::string& fragment_shader_source,
        const ColoredMesh& mesh) {
    // Set shader program.
    program_.AttachShaders(vertex_shader_source, fragment_shader_source);

    vao_.Bind();
    // // Buffer position data.
    auto& position_buffer = array_buffers_["a_position"];
    position_buffer.BufferData(GL_FLOAT, GL_STATIC_DRAW, 3,
                               mesh.positions.size(),
                               &(mesh.positions[0]));
    // // Buffer color data.
    auto& color_buffer = array_buffers_["a_color"];
    color_buffer.BufferData(GL_FLOAT, GL_STATIC_DRAW, 3,
                            mesh.colors.size(),
                            &(mesh.colors[0]));
    // Buffer index data.
    index_buffer_.BufferData(GL_UNSIGNED_INT, GL_STATIC_DRAW,
                             mesh.indices.size(), &(mesh.indices[0]));
    vao_.Unbind();
    return absl::OkStatus();
}

}  // namespace ogl