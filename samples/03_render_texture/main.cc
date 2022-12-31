#include <glog/logging.h>
#include <string>

#include <absl/status/statusor.h>

#include "opencv2/opencv.hpp"
#include "window/window.h"
#include "window/glfw_window.h"
#include "gl/program.h"
#include "gl/texture.h"
#include "utils/utils.h"
#include "geometry/quad.h"

namespace ogl {
namespace {

const std::string kVertexShaderSource =
    "#version 330 core\n"
    "layout (location = 0) in vec3 position;\n"
    "layout (location = 1) in vec3 texcoord;\n"
    "out vec2 uv;\n"
    "void main()\n"
    "{\n"
    "   uv = vec2(texcoord.x, texcoord.y);\n"
    "   gl_Position = vec4(position, 1.0);\n"
    "}\0";

const std::string kFragmentShaderSource =
    "#version 330 core\n"
    "out vec4 frag_color;\n"
    "in vec2 uv;\n"
    "uniform sampler2D texture0;\n"
    "void main()\n"
    "{\n"
    "   vec2 uv_stretch = vec2(uv * 1.5 - 0.5);\n"
    "   vec4 color = texture(texture0, uv_stretch);\n"
    "   frag_color = vec4(color.rgb, 1.0);\n"
    "}\0";

}  // namespace

absl::Status Render() {
    const std::string filename = "/Users/zhangliangkai/devel/study/learn_opengl/assets/forest.jpeg";
    auto image = cv::imread(filename);

    ogl::Window::WindowOptions opts;
    opts.height = image.size().height;
    opts.width = image.size().width;
    opts.title = "Hello Texture!";

    ASSIGN_OR_RETURN(const auto window,
                     ogl::createGlfwWindow(opts));
    CHECK(window != nullptr);

    // Setup Texture.
    Texture::Options texture_opts;
    texture_opts.format = GL_BGR;
    texture_opts.wrap_s = GL_MIRRORED_REPEAT;
    texture_opts.wrap_t = GL_MIRRORED_REPEAT;
    ASSIGN_OR_RETURN(auto texture, Texture::Create(texture_opts));
    CHECK_OK(texture->BufferData(image.size().width, image.size().height, image.ptr()));

    ASSIGN_OR_RETURN(const auto program,
                     ogl::Program::Create(
                        kVertexShaderSource, kFragmentShaderSource));
    ASSIGN_OR_RETURN(auto quad, Quad::Create(2.0, 2.0, program));
    program->SetTexture(0, *texture);

    while (!window->ShouldClose()) {
        window->OnBeforeRender();
        CHECK_OK(quad->Draw());
        window->OnAfterRender();
    }
    return absl::OkStatus();
}

}  // namespace ogl

int main() {
    CHECK_OK(ogl::Render());
    return 0;
}

