#ifndef WINDOW_WINDOW_H_
#define WINDOW_WINDOW_H_

#include <string>
#include <functional>

#include <absl/status/status.h>

namespace ogl {

using RenderCallback = std::function<void()>;

class Window {
  public:
    Window() = default;
    virtual ~Window() = default;

    struct WindowOptions {
        int width;
        int height;
        std::string title;
    };

    virtual absl::Status Create(const WindowOptions& opts) = 0;

    virtual void Run() = 0;

    virtual bool RunOnce() = 0;

    int Width() const { return  width_; }
    int Height() const { return height_; }

    void SetSize(int width, int height);

    void SetOnRenderCallback(const RenderCallback& on_render);

    virtual void Close() {}

  protected:
    int width_ = 0;
    int height_ = 0;
    RenderCallback on_render_;
};

std::unique_ptr<Window> GetWindow();

}  // namespace ogl

#endif  // WINDOW_WINDOW_H_
