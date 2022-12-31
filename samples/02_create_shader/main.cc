#include <glog/logging.h>

#include <vector>
#include <string>

#include <absl/status/statusor.h>

#include "window/window.h"
#include "window/glfw_window.h"
#include "gl/program.h"
#include "geometry/quad.h"
#include "utils/utils.h"

namespace ogl {
namespace {
const std::string kFragmentShaderSource =
    "#version 330 core\n"
    "out vec4 frag_color;\n"
    "in vec2 texcoord;\n"
    "void main()\n"
    "{\n"
    "   frag_color = vec4(texcoord.x, texcoord.y, 0.0, 1.0);\n"
    "}\n\0";

}  // namespace

absl::Status Render() {
    ogl::Window::WindowOptions opts;
    opts.height = 512;
    opts.width = 512;
    opts.title = "Hello Shader!";

    ASSIGN_OR_RETURN(const auto window,
                     ogl::createGlfwWindow(opts));
    CHECK(window != nullptr);

    ASSIGN_OR_RETURN(auto quad, Quad::Create(2.0, 2.0, kFragmentShaderSource));

    while (!window->ShouldClose()) {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        program->Use();
        vao->Bind();
        glDrawElements(GL_TRIANGLES, index_buffer.NumIndice(), GL_UNSIGNED_INT, 0);
        vao->UnBind();

        window->OnAfterRender();
    }
    return absl::OkStatus();
}

}  // namespace ogl

int main() {
    ogl::Render();
    return 0;
}
