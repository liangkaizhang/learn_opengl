#include <glog/logging.h>

#include "window/glfw_window.h"
#include "utils/utils.h"

namespace ogl {
void DrawZimaBlue() {
    glClearColor(0.118f, 0.706f, 0.914f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}
}  // namespace ogl

int main() {
    ogl::Window::WindowOptions opts;
    opts.height = 512;
    opts.width = 512;
    opts.title = "Hello Window!";

    const auto window_or = ogl::createGlfwWindow(opts);
    CHECK(window_or.ok());
    const auto& window = *window_or;
    CHECK(window != nullptr);

    while (!window->ShouldClose()) {
        window->OnBeforeRender();
        ogl::DrawZimaBlue();
        window->OnAfterRender();
    }
    return 0;
}
