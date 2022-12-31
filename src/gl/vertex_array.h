#ifndef GL_VERTEX_ARRAY_H_
#define GL_VERTEX_ARRAY_H_

#include <memory>

#include <GL/glew.h> 
#include <absl/status/status.h>
#include <absl/status/statusor.h>

#include "gl/abstract_object.h"

namespace ogl {

class VertexArray : public AbstractObject {
  public:
    using Ptr = std::unique_ptr<VertexArray>;

    ~VertexArray() override;

    void Bind() const;
    void UnBind() const;

    static absl::StatusOr<Ptr> Create();

  private:
    VertexArray() = default;
    absl::Status Setup();
};

}  // namespace ogl

#endif  // GL_VERTEX_ARRAY_H_