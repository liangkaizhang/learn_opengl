#include <glog/logging.h>
#include <string>

#include "window/glfw_window.h"
#include "renderer/texture_renderer.h"


namespace ogl {

const std::string kVertexShaderSource ="#version 330 core\n"
    "layout (location = 0) in vec3 a_position;\n"
    "layout (location = 1) in vec3 a_texcoord;\n"
    "out vec2 texcoord;\n"
    "uniform mat4 mvp;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = mvp * vec4(a_position, 1.0);\n"
    "   texcoord = vec2(a_texcoord.x, 1 - a_texcoord.y);\n"
    "}\0";

const std::string kFragmentShaderSource = "#version 330 core\n"
    "out vec4 frag_color;\n"
    "in vec2 texcoord;\n"
    "uniform sampler2D u_texture;\n"
    "void main()\n"
    "{\n"
    "   frag_color = texture(u_texture, texcoord);\n"
    "}\n\0";

const std::vector<float> kPositions = {
    -1.0f, -1.0f, 0.0f,  // bottom left
     1.0f, -1.0f, 0.0f,  // bottom right
    -1.0f,  1.0f, 0.0f,  // top  left 
     1.0f,  1.0f, 0.0f,  // top  right
};

const std::vector<float> kTexCoords = {
    0.0f, 0.0f,  // bottom left
    1.0f, 0.0f,  // bottom right
    0.0f, 1.0f,  // top  left 
    1.0f, 1.0f,  // top  right
};

const std::vector<uint32_t> kIndices = {
    0, 2, 1,
    1, 2, 3,
};


void Run() {
    GlfwWindow window;
    Window::WindowOptions opts;
    opts.height = 1024;
    opts.width = 1024;
    opts.title = "Hello Transformation!";
    CHECK(window.Create(opts).ok());

    ShaderProgram shader;
    CHECK(shader.AttachShaders(kVertexShaderSource, kFragmentShaderSource).ok());

    TexturedMesh mesh;
    mesh.positions = kPositions;
    mesh.texcoords = kTexCoords;
    mesh.indices = kIndices;

    const std::string texture_file = "/Users/zhangliangkai/devel/study/learn_opengl/data/pattern.png";
    Texture texture(texture_file);
    TextureRender renderer;
    CHECK(renderer.Init(shader, mesh, texture).ok());

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
