#ifndef GEOMETRY_BUFFER_GEOMETRY_H_
#define GEOMETRY_BUFFER_GEOMETRY_H_

#include <memory>

#include <absl/status/status.h>
#include <absl/status/statusor.h>
#include <absl/container/flat_hash_map.h>

#include "gl/vertex_array.h"
#include "gl/buffer.h"

namespace ogl {

class BufferGeometry {
  public:
    using Ptr = std::unique_ptr<BufferGeometry>;
    using HashMap = absl::flat_hash_map<GLuint, AttributeBuffer::Ptr>;

    BufferGeometry() = default;
    virtual ~BufferGeometry() = default;

    virtual absl::Status SetAttribute(
            const GLuint location,
            const std::vector<float>& buffer,
            size_t element_size) = 0;

    virtual void Enable() const = 0;
    virtual void Disable() const = 0;

    virtual absl::Status SetIndex(
            const std::vector<uint32_t>& index) = 0;
    virtual bool HasIndex() const = 0;

    virtual size_t NumVertices() const = 0;
    virtual size_t NumIndice() const = 0;
};

absl::StatusOr<BufferGeometry::Ptr> CreateBufferGeometry();

}  // namespace ogl

#endif  // GEOMETRY_BUFFER_GEOMETRY_H_