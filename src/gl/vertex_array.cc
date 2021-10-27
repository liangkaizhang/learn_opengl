#include "gl/vertex_array.h"

namespace ogl {

VertexArray::VertexArray() {
    glGenVertexArrays(1, &id_);
}

VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &id_);
}

void VertexArray::Bind() const {
    glBindVertexArray(id_);
}

void VertexArray::Unbind() const {
    glBindVertexArray(0);
}

}  // namespace ogl