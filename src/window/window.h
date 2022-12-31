#ifndef WINDOW_WINDOW_H_
#define WINDOW_WINDOW_H_

#include <memory>
#include <string>
#include <functional>

#include <absl/status/status.h>

namespace ogl {

// Define abstract interface class for window.
class Window {
  public:
    struct WindowOptions {
        int width;
        int height;
        std::string title;
    };

    Window() = default;
    virtual ~Window() = default;

    virtual absl::Status Setup(const WindowOptions& options) = 0;

    virtual bool ShouldClose() const = 0;

    virtual void OnBeforeRender() const = 0;
    virtual void OnAfterRender() const = 0;

    virtual int Width() const { return  width_; }
    virtual int Height() const { return height_; }

  protected:
    int width_;
    int height_;
};

}  // namespace ogl

#endif  // WINDOW_WINDOW_H_
