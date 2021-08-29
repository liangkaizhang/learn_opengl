#include <glog/logging.h>
#include <string>

#include "window/glfw_window.h"
#include "renderer/mesh_renderer.h"


namespace ogl {

const std::string kVertexShaderSource ="#version 330 core\n"
    "layout (location = 0) in vec3 a_position;\n"
    "layout (location = 1) in vec3 a_color;\n"
    "out vec3 vertex_color;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(a_position, 1.0);\n"
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
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
     0.5f,  0.5f, 0.0f,  // top  right
    -0.5f,  0.5f, 0.0f,  // top  left 
};

// const std::vector<float> kPositions = {
//      1.0f, -1.0f, 0.0f,  // bottom right
//     -1.0f, -1.0f, 0.0f,  // bottom left
//      1.0f,  1.0f, 0.0f,  // top  right
//     -1.0f,  1.0f, 0.0f,  // top  left 
// };

const std::vector<float> kColors = {
    1.0f, 0.0f, 0.0f,  // red 
    0.0f, 1.0f, 0.0f,  // green 
    0.0f, 0.0f, 1.0f,  // blue 
    0.0f, 1.0f, 1.0f,  // yellow 
};

const std::vector<uint32_t> kIndices = {
    3, 1, 2, 0,
};


void Run() {
    GlfwWindow window;
    Window::WindowOptions opts;
    opts.height = 512;
    opts.width = 512;
    opts.title = "Hello Geometry!";
    CHECK(window.Create(opts).ok());

    Shader shader;
    CHECK(shader.Compile(kVertexShaderSource, kFragmentShaderSource).ok());

    ColoredMesh mesh;
    mesh.positions = kPositions;
    mesh.colors = kColors;
    mesh.indices = kIndices;
    MeshRender renderer;
    CHECK(renderer.Init(shader, mesh).ok());

    //
    window.SetOnRenderCallback([&]() { return renderer.Render(); });
    window.Run();
}

}  // namespace ogl

int main() {
    ogl::Run();
    // LOG(INFO) << glGetString(GL_VERSION);
    return 0;
}
