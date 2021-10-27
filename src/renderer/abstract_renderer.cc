#include "renderer/abstract_renderer.h"

namespace ogl {

void AbstractRenderer::Render() const {
    program_.Use();
    vao_.Bind();
    for (const auto& buffer_iter : array_buffers_) {
        const auto attrib_location =
                program_.GetAttributeLocation(buffer_iter.first);
        buffer_iter.second.Enable(attrib_location);
    }
    index_buffer_.Draw();
    vao_.Unbind();
}

}  // namespace ogl