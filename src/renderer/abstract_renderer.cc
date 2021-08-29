#include "renderer/abstract_renderer.h"

namespace ogl {

void AbstractRenderer::Render() const {
    glUseProgram(program_);
    glBindVertexArray(vao_);
    glDrawElements(GL_TRIANGLE_STRIP, num_indices_, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

}  // namespace ogl