#include "renderer/abstract_renderer.h"

namespace ogl {

void AbstractRenderer::Render() const {
    glUseProgram(program_);
    glBindVertexArray(vao_);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
}

}  // namespace ogl