#ifndef WINDOW_GLFW_WINDOW_H_
#define WINDOW_GLFW_WINDOW_H_

#include "window/window.h"

#include <string>

#include <GL/glew.h> 
#include <GLFW/glfw3.h>
#include <absl/status/status.h>
#include <absl/status/statusor.h>
#include <glog/logging.h>

namespace ogl {

// Window class implemention interms of GLFW.
class GlfwWindow : public Window {
  public:
    GlfwWindow() : window_(nullptr) {};
    ~GlfwWindow() override;

    absl::Status Setup(const WindowOptions& options) override;

    bool ShouldClose() const override;

    void OnBeforeRender() const override;
    void OnAfterRender() const override;

  private:
    GLFWwindow* window_;
};

absl::StatusOr<std::unique_ptr<Window>>
createGlfwWindow(const Window::WindowOptions& options);

}  // namespace ogl

#endif  // WINDOW_GLFW_WINDOW_H_
