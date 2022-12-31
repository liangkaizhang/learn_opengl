#include "window/glfw_window.h"

#include "utils/utils.h"

namespace ogl {
namespace {
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

}  // namespace

GlfwWindow::~GlfwWindow() {
    if (window_ != nullptr) {
        glfwDestroyWindow(window_);
    }
}

absl::Status GlfwWindow::Setup(const WindowOptions& options) {
    CHECK_GT(options.width, 0);
    CHECK_GT(options.height, 0);

    width_ = options.width;
    height_ = options.height;
    CHECK(glfwInit()) << "Failed to initialize GLFW";

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
	// Open a window and create its OpenGL context
	window_ = glfwCreateWindow(width_, height_, options.title.c_str(), nullptr, nullptr);
    CHECK(window_) << "Failed to open GLFW window";
    // Init glfw.
    glfwMakeContextCurrent(window_);
    glfwSetFramebufferSizeCallback(window_, framebuffer_size_callback);
    CHECK_EQ(glewInit(), GLEW_OK) << "Failed to initialize GLEW.";
    glfwGetFramebufferSize(window_, &width_, &height_);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable( GL_BLEND );
    return absl::OkStatus();
}

bool GlfwWindow::ShouldClose() const {
    glfwPollEvents();
    if (glfwGetKey(window_, GLFW_KEY_ESCAPE) == GLFW_PRESS ||
        glfwWindowShouldClose(window_)) {
            return true;
    }
    return false;
}

void GlfwWindow::OnBeforeRender() const {
    glViewport(0, 0, width_, height_);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GlfwWindow::OnAfterRender() const {
    glfwMakeContextCurrent(window_);
    glfwSwapBuffers(window_);
}

absl::StatusOr<std::unique_ptr<Window>>
createGlfwWindow(const Window::WindowOptions& options) {
    auto window = absl::make_unique<GlfwWindow>();
    RETURN_IF_ERROR(window->Setup(options));
    return window;
}

}  // namespace ogl
