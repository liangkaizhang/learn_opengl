#include "renderer/image_renderer.h"
#include "geometry/mesh.h"

namespace ogl {
namespace {

const std::string kVertexShaderSource =
    "#version 330 core\n"
    "layout (location = 0) in vec3 a_position;\n"
    "layout (location = 1) in vec3 a_texcoord;\n"
    "uniform mat4 model_view;\n"
    "uniform mat4 projection;\n"
    "out vec2 texcoord;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = projection * model_view * vec4(a_position.x, a_position.y, 0.0, 1.0);\n"
    "   texcoord = vec2(a_texcoord.x, a_texcoord.y);\n"
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

const std::vector<float> kPositions = {
    -1.0f, -1.0f,  // bottom left
     1.0f, -1.0f,  // bottom right
    -1.0f,  1.0f,  // top  left 
     1.0f,  1.0f,  // top  right
};

const std::vector<float> kUvCoords = {
    0.0f, 0.0f,  // bottom left
    1.0f, 0.0f,  // bottom right
    0.0f, 1.0f,  // top  left 
    1.0f, 1.0f,  // top  right
};

const std::vector<uint32_t> kIndices = {
    0, 1, 2,
    1, 3, 2,
};

}  // namespace

std::unique_ptr<AbstractRenderer> ImageRender::Create(
        const cv::Mat& image) {
    auto render_ptr = absl::make_unique<ImageRender>();
    const auto status = render_ptr->Init(kVertexShaderSource,
                                         kFragmentShaderSource, image);
    if (!status.ok()) render_ptr.reset(nullptr);
    return render_ptr;
}

void ImageRender::SetProjection(const Eigen::Matrix4f& projection) {
    program_->SetUniform("projection", projection);
}

void ImageRender::SetModelView(const Eigen::Matrix4f model_view) {
    program_->SetUniform("model_view", model_view);
}

absl::Status ImageRender::Init(
        const std::string& vertex_shader_source,
        const std::string& fragment_shader_source,
        const cv::Mat& image) {
    // Set shader program.
    if (!program_) {
        program_ = absl::make_unique<ShaderProgram>();
    }
    CHECK(program_->AttachShaders(vertex_shader_source, fragment_shader_source).ok());
    SetProjection(Eigen::Matrix4f::Identity());
    SetModelView(Eigen::Matrix4f::Identity());

    vao_.Bind();
    // Buffer position data.
    auto& position_buffer = array_buffers_["a_position"];
    position_buffer.BufferData(GL_FLOAT, GL_STATIC_DRAW, 2,
                               kPositions.size(),
                               &(kPositions[0]));
    // Buffer texture coord and texture data.
    auto& uv_coord_buffer = array_buffers_["a_texcoord"];
    uv_coord_buffer.BufferData(GL_FLOAT, GL_STATIC_DRAW, 2,
                               kUvCoords.size(),
                               &(kUvCoords[0]));
    texture_ = absl::make_unique<Texture>();
    CHECK(texture_->BufferData(image).ok());
    // Buffer index data.
    index_buffer_.BufferData(GL_UNSIGNED_INT, GL_STATIC_DRAW,
                             kIndices.size(),
                             &(kIndices[0]));
    vao_.Unbind();
    return absl::OkStatus();
}

}  // namespace ogl
