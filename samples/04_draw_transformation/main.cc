#include <glog/logging.h>
#include <string>

#include "window/glfw_window.h"
#include "renderer/mesh_renderer.h"


namespace ogl {
namespace {
using Eigen::AngleAxisf;
using Eigen::Vector3f;
using Eigen::Matrix4f;
using Eigen::Matrix3f;
}


const std::string kVertexShaderSource ="#version 330 core\n"
    "layout (location = 0) in vec3 a_position;\n"
    "layout (location = 1) in vec3 a_color;\n"
    "out vec3 vertex_color;\n"
    "uniform mat4 model_view;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = model_view * vec4(a_position, 1.0);\n"
    "   vertex_color = a_color;\n"
    "}\0";

const std::string kFragmentShaderSource = "#version 330 core\n"
    "out vec4 frag_color;\n"
    "in vec3 vertex_color;\n"
    "void main()\n"
    "{\n"
    "   frag_color = vec4(vertex_color, 1.0f);\n"
    "}\n\0";

const std::vector<float> kPositions = {
    -0.5f, -0.5f, 0.0f,  // bottom left
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f,  0.5f, 0.0f,  // top  left 
     0.5f,  0.5f, 0.0f,  // top  right
};

const std::vector<float> kColors = {
    1.0f, 0.0f, 0.0f,  // red 
    0.0f, 1.0f, 0.0f,  // green 
    0.0f, 0.0f, 1.0f,  // blue 
    0.0f, 1.0f, 1.0f,  // yellow 
};

const std::vector<uint32_t> kIndices = {
    0, 2, 1,
    1, 2, 3,
};

class RenderHelper {
  public:
    void Init(const std::string& vertex_shader_source,
              const std::string& fragment_shader_source,
              const ColoredMesh& mesh, float speed) {
        renderer_=
            MeshRender::Create(vertex_shader_source, fragment_shader_source, mesh);
        time_ = 0;
        speed_ = speed;
        transform_ = Matrix4f::Identity();
    }

    void Render() {
        const float angle = time_ * speed_;
        transform_.topLeftCorner(3, 3) = AngleAxisf(angle, Vector3f::UnitY()).toRotationMatrix();
        renderer_->SetModelView(transform_);
        renderer_->Render();
        time_ += 1;
    }
  private:
    std::unique_ptr<MeshRender> renderer_;
    size_t time_;
    float speed_;
    Matrix4f transform_;
};

void Run() {
    GlfwWindow window;
    Window::WindowOptions opts;
    opts.height = 512;
    opts.width = 512;
    opts.title = "Hello Geometry!";
    CHECK(window.Create(opts).ok());

    ColoredMesh mesh;
    mesh.positions = kPositions;
    mesh.colors = kColors;
    mesh.indices = kIndices;
    auto renderer_helper = RenderHelper();
    renderer_helper.Init(kVertexShaderSource, kFragmentShaderSource, mesh, 0.01);
    window.SetOnRenderCallback([&]() { return renderer_helper.Render(); });
    window.Run();
}

}  // namespace ogl

int main() {
    ogl::Run();
    return 0;
}
