#include "gl/vertex_array.h"

#include <glog/logging.h>
#include <absl/status/status.h>
#include <absl/status/statusor.h>

#include "utils/utils.h"

namespace ogl {

VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &id_);
}

void VertexArray::Bind() const {
    glBindVertexArray(id_);
}

void VertexArray::UnBind() const {
    glBindVertexArray(0);
}

absl::Status VertexArray::Setup() {
    glGenVertexArrays(1, &id_);
    return absl::OkStatus();
}

absl::StatusOr<VertexArray::Ptr> VertexArray::Create() {
  auto vao = Ptr(new VertexArray);
  RETURN_IF_ERROR(vao->Setup());
  return vao;
}

}  // namespace ogl