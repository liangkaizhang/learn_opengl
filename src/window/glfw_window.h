#ifndef WINDOW_GLFW_WINDOW_H_
#define WINDOW_GLFW_WINDOW_H_

#include "window/window.h"

#include <string>

#include <GL/glew.h> 
#include <GLFW/glfw3.h>
#include <absl/status/status.h>
#include <glog/logging.h>

namespace ogl {

class GlfwWindow : public Window {
  public:
    ~GlfwWindow() override;

    absl::Status Create(const WindowOptions& opts) override;

    void Run() override;

    bool RunOnce() override;

    void Close() override;

  private:
    GLFWwindow* window_ = nullptr;
};

}  // namespace ogl

#endif  // WINDOW_GLFW_WINDOW_H_
