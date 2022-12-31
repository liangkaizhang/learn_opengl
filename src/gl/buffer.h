#ifndef GL_BUFFER_H_
#define GL_BUFFER_H_

#include <GL/glew.h> 
#include <absl/status/statusor.h>

#include "gl/abstract_object.h"

namespace ogl {

class AttributeBuffer : public AbstractObject {
  public:
    using Ptr = std::unique_ptr<AttributeBuffer>;

    ~AttributeBuffer() override;

    void Bind() const;
    void UnBind() const;

    void Enable(const GLuint attrib_location) const;

    size_t NumVertices() const {
      return num_of_vertice_;
    }

    static absl::StatusOr<Ptr> Create(
        GLenum data_type, GLenum usage,
        size_t element_size,
        size_t data_length,
        const void* data);

  private:
    AttributeBuffer() = default;
    void BufferData(GLenum data_type, GLenum usage,
                    size_t element_size,
                    size_t data_length, const void* data);  

    GLenum data_type_;
    GLenum usage_;
    size_t element_size_;
    size_t num_of_vertice_;
};

class ElementBuffer : public AbstractObject {
  public:
    using Ptr = std::unique_ptr<ElementBuffer>;

    ~ElementBuffer() override;

    void Bind() const;
    void UnBind() const;

    size_t NumIndice() const {
      return num_of_index_;
    }
  
    static absl::StatusOr<Ptr> Create(
        GLenum usage,
        size_t data_length,
        const void* data);

  private:
    ElementBuffer() = default;
    void BufferData(GLenum data_type, GLenum usage,
                    size_t data_length, const void* data);

    GLenum data_type_;
    GLenum usage_;
    size_t num_of_index_;
};

}  // namespace ogl

#endif  // GL_BUFFER_H_