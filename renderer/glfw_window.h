#ifndef RENDERER_GLFW_WINDOW_H_
#define RENDERER_GLFW_WINDOW_H_

#include "renderer/window.h"

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

#endif  // RENDERER_GLFW_WINDOW_H_
