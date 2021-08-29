#include "window/glfw_window.h"

namespace ogl {

GlfwWindow::~GlfwWindow() {
    Close();
}

absl::Status GlfwWindow::Create(const WindowOptions& opts) {
    width_ = opts.width;
    height_ = opts.height;
    CHECK(glfwInit()) << "Failed to initialize GLFW";

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
	// Open a window and create its OpenGL context
	window_ = glfwCreateWindow(width_, height_, opts.title.c_str(), nullptr, nullptr);
    CHECK(window_) << "Failed to open GLFW window";
    // Init glfw.
    glfwMakeContextCurrent(window_);
    // glfwSetFramebufferSizeCallback(window_, framebuffer_size_callback);
    CHECK_EQ(glewInit(), GLEW_OK) << "Failed to initialize GLEW.";
    return absl::OkStatus();
}

void GlfwWindow::Run() {
    while (RunOnce()) {
        absl::SleepFor(absl::Microseconds(100));
    }
}

bool GlfwWindow::RunOnce() {
    glfwPollEvents();
    if (glfwGetKey(window_, GLFW_KEY_ESCAPE) == GLFW_PRESS ||
        glfwWindowShouldClose(window_)) {
            return false;
    }
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Run render callback.
    if (on_render_) on_render_();

    glFlush();
    glfwSwapBuffers(window_);
    return true;
}

void GlfwWindow::Close() {
    if (window_ != nullptr) {
        glfwDestroyWindow(window_);
        window_ = nullptr;
    }
}

}  // namespace ogl
