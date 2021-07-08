#include "window/window.h"

namespace ogl {

void Window::SetSize(int width, int height) {
    width_ = width;
    height_ = height;
}

void Window::SetOnRenderCallback(const RenderCallback& on_render) {
    on_render_ = on_render;
}

}  // namespace ogl
