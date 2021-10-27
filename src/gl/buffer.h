#ifndef GL_BUFFER_H_
#define GL_BUFFER_H_

#include <GL/glew.h> 
#include <glog/logging.h>

#include "gl/abstract_object.h"

namespace ogl {

class ArrayBuffer : public AbstractObject {
  public:
    ArrayBuffer() = default;
    ~ArrayBuffer() override;

    void BufferData(GLenum data_type, GLenum usage,
                    size_t elements_per_vertex,
                    size_t data_length, const void* data);  

    void Bind() const override;
    void Unbind() const override;

    void Enable(GLuint attrib_location) const;
  private:
    GLenum data_type_;
    GLenum usage_;
    size_t elements_per_vertex_;
    size_t num_of_vertex_;
};

class IndexBuffer : public AbstractObject {
  public:
    IndexBuffer() = default;
    ~IndexBuffer() override;

    void BufferData(GLenum data_type, GLenum usage,
                    size_t data_length, const void* data);  

    void Bind() const override;
    void Unbind() const override;

    void Draw() const;
  private:
    GLenum data_type_;
    GLenum usage_;
    size_t num_of_index_;
};

}  // namespace ogl

#endif  // GL_BUFFER_H_