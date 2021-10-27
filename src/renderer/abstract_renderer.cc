#include "renderer/abstract_renderer.h"

namespace ogl {

void AbstractRenderer::Render() const {
    program_.Use();
    vao_.Bind();
    for (const auto& buffer_iter : array_buffers_) {
        const auto attr_loc = program_.GetAttribLocation(buffer_iter.first);
        buffer_iter.second.Enable(attr_loc);
    }
    index_buffer_.Draw();
    vao_.Unbind();
}

}  // namespace ogl