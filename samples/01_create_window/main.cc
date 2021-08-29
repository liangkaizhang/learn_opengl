#include "window/glfw_window.h"

#include <glog/logging.h>

void DrawZimaBlue() {
    glClearColor(0.118f, 0.706f, 0.914f, 0.0f);
}

int main() {
    ogl::GlfwWindow window;
    ogl::Window::WindowOptions opts;
    opts.height = 256;
    opts.width = 256;
    opts.title = "Hello Window!";
    CHECK(window.Create(opts).ok());
    window.SetOnRenderCallback([]() { return DrawZimaBlue(); });
    window.Run();
    // LOG(INFO) << glGetString(GL_VERSION);
    return 0;
}
