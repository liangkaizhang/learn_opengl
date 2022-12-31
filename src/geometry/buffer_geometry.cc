#include "geometry/buffer_geometry.h"

#include <string>
#include <vector>
#include <memory>

#include <absl/container/flat_hash_map.h>
#include <glog/logging.h>

#include "utils/utils.h"
#include "gl/buffer.h"
#include "gl/vertex_array.h"

namespace ogl {

class BufferGeometryImpl : public BufferGeometry {
  public:
    BufferGeometryImpl() :
        attributes_(), vao_(nullptr),
        index_(nullptr),
        num_of_vertices_(0) {};
    ~BufferGeometryImpl() = default;

    absl::Status SetAttribute(
            const GLuint location,
            const std::vector<float>& buffer,
            size_t element_size) override;

    absl::Status SetIndex(
            const std::vector<uint32_t>& index) override;
    bool HasIndex() const override;

    size_t NumVertices() const override {
        return num_of_vertices_;
    }

    size_t NumIndice() const override {
        return index_->NumIndice();
    }

    void Enable() const override {
        vao_->Bind();
        if (this->HasIndex()) {
            index_->Bind();
        }
    }

    void Disable() const override {
        if (this->HasIndex()) {
            index_->UnBind();
        }
        vao_->UnBind();
    }

    absl::Status Setup();

  private:
    HashMap attributes_;
    VertexArray::Ptr vao_;
    ElementBuffer::Ptr index_;
    size_t num_of_vertices_;
};

absl::Status BufferGeometryImpl::SetAttribute(
    const GLuint location,
    const std::vector<float>& buffer,
    size_t element_size) {
    if (attributes_.find(location) == attributes_.end()) {
        this->Enable();
        ASSIGN_OR_RETURN(
            attributes_[location],
            AttributeBuffer::Create(
                GL_FLOAT, GL_STATIC_DRAW, element_size,
                buffer.size(), &(buffer[0])));
        attributes_[location]->Enable(location);
        this->Disable();

        if (num_of_vertices_) {
            CHECK_EQ(num_of_vertices_, attributes_[location]->NumVertices());
        } else {
            num_of_vertices_ = attributes_[location]->NumVertices();
        }
        CHECK(num_of_vertices_);
    }
    return absl::OkStatus();
}

absl::Status BufferGeometryImpl::SetIndex(
    const std::vector<uint32_t>& index) {
    vao_->Bind();
    ASSIGN_OR_RETURN(
        index_,
        ElementBuffer::Create(GL_STATIC_DRAW, index.size(), &(index[0])));
    vao_->UnBind();
    return absl::OkStatus();
}

bool BufferGeometryImpl::HasIndex() const {
    return index_ != nullptr;
}

absl::Status BufferGeometryImpl::Setup() {
    ASSIGN_OR_RETURN(vao_, VertexArray::Create());
    return absl::OkStatus();
}

absl::StatusOr<BufferGeometry::Ptr> CreateBufferGeometry() {
    auto buffer_geometry = absl::make_unique<BufferGeometryImpl>();
    RETURN_IF_ERROR(buffer_geometry->Setup());
    return buffer_geometry;
}

}  // namespace ogl