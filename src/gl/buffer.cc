#include "gl/buffer.h"

namespace ogl {

namespace {

size_t GetDataSize(GLenum data_type) {
  switch (data_type) {
  case GL_FLOAT:
    return sizeof(float);
  case GL_UNSIGNED_BYTE:
    return sizeof(uint8_t);
  case GL_SHORT:
    return sizeof(uint16_t);
  case GL_UNSIGNED_INT:
    return sizeof(uint32_t);
  default:
    LOG(FATAL) << "Unknow data type: " << data_type;
    return 0;
  }
}

}  // namespace

ArrayBuffer::~ArrayBuffer() {
  glDeleteBuffers(1, &id_);
}

void ArrayBuffer::Bind() const {
  glBindBuffer(GL_ARRAY_BUFFER, id_);
}

void ArrayBuffer::Unbind() const {
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ArrayBuffer::BufferData(GLenum data_type, GLenum usage,
                             size_t elements_per_vertex,
                             size_t data_length, const void* data) {              
  if (data == nullptr) {
    CHECK_LT(data_length, 0);
  }
  if (!is_generated_) {
    glGenBuffers(1, &id_);
    is_generated_ = true;
  }
  this->Bind();
  data_type_ = data_type;
  usage_ = usage;
  elements_per_vertex_ = elements_per_vertex;
  num_of_vertex_ = data_length / elements_per_vertex_;
  const auto data_size = data_length * GetDataSize(data_type_);
  glBufferData(GL_ARRAY_BUFFER, data_size, data, usage_);
  this->Unbind();
}

void ArrayBuffer::Enable(GLuint attrib_location) const {
  this->Bind();
  glEnableVertexAttribArray(attrib_location);
  const GLuint data_size = elements_per_vertex_ * GetDataSize(data_type_);
  glVertexAttribPointer(attrib_location, elements_per_vertex_, data_type_, GL_FALSE, data_size, 0);
  this->Unbind();
}

IndexBuffer::~IndexBuffer() {
  glDeleteBuffers(1, &id_);
}

void IndexBuffer::Bind() const {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_);
}

void IndexBuffer::Unbind() const {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBuffer::BufferData(GLenum data_type, GLenum usage,
                             size_t data_length, const void* data) {              
  if (data == nullptr) {
    CHECK_LT(data_length, 0);
  }
  if (!is_generated_) {
    glGenBuffers(1, &id_);
    is_generated_ = true;
  }
  this->Bind();
  data_type_ = data_type;
  usage_ = usage;
  num_of_index_ = data_length;
  const auto data_size = num_of_index_ * GetDataSize(data_type_);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, data_size, data, usage_);
  this->Unbind();
}

void IndexBuffer::Draw() const {
  this->Bind();
  glDrawElements(GL_TRIANGLES, num_of_index_, data_type_, 0);
  this->Unbind();
}

}  // namespace ogl
