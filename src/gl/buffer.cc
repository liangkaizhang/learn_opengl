
#include <glog/logging.h>

#include "gl/buffer.h"

namespace ogl {

namespace {
size_t GetDataSize(GLenum data_type) {
  switch (data_type) {
  case GL_FLOAT:
    return sizeof(float);
  case GL_UNSIGNED_BYTE:
    return sizeof(uint8_t);
  case GL_UNSIGNED_SHORT:
    return sizeof(uint16_t);
  case GL_UNSIGNED_INT:
    return sizeof(uint32_t);
  default:
    LOG(FATAL) << "Unknow data type: " << data_type;
    return 0;
  }
}

}  // namespace

AttributeBuffer::~AttributeBuffer() {
  glDeleteBuffers(1, &id_);
}

void AttributeBuffer::Bind() const {
  glBindBuffer(GL_ARRAY_BUFFER, id_);
}

void AttributeBuffer::UnBind() const {
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void AttributeBuffer::BufferData(GLenum data_type, GLenum usage,
                                 size_t element_size,
                                 size_t data_length, const void* data) {              
  if (data == nullptr) {
    CHECK_LT(data_length, 0);
  }
  if (id_ == kInvalidId) {
    glGenBuffers(1, &id_);
  }
  this->Bind();
  data_type_ = data_type;
  usage_ = usage;
  element_size_ = element_size;
  num_of_vertice_ = data_length / element_size_;
  const auto data_size = data_length * GetDataSize(data_type_);
  glBufferData(GL_ARRAY_BUFFER, data_size, data, usage_);
  this->UnBind();
}

void AttributeBuffer::Enable(const GLuint attrib_location) const {
  this->Bind();
  glEnableVertexAttribArray(attrib_location);
  const GLuint data_size = element_size_ * GetDataSize(data_type_);
  glVertexAttribPointer(attrib_location, element_size_, data_type_, GL_FALSE, data_size, 0);
  this->UnBind();
}

absl::StatusOr<AttributeBuffer::Ptr> AttributeBuffer::Create(
      GLenum data_type, GLenum usage, size_t elements_per_vertex,
      size_t data_length, const void* data) {
  auto attr_buffer = Ptr(new AttributeBuffer);
  attr_buffer->BufferData(data_type, usage, elements_per_vertex, data_length, data);
  return attr_buffer;
}

ElementBuffer::~ElementBuffer() {
  glDeleteBuffers(1, &id_);
}

void ElementBuffer::Bind() const {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_);
}

void ElementBuffer::UnBind() const {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void ElementBuffer::BufferData(GLenum data_type, GLenum usage,
                               size_t data_length, const void* data) {              
  if (data == nullptr) {
    CHECK_LT(data_length, 0);
  }
  if (id_ == kInvalidId) {
    glGenBuffers(1, &id_);
  }
  this->Bind();
  data_type_ = data_type;
  usage_ = usage;
  num_of_index_ = data_length;
  const auto data_size = num_of_index_ * GetDataSize(data_type_);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, data_size, data, usage_);
  this->UnBind();
}

absl::StatusOr<ElementBuffer::Ptr> ElementBuffer::Create(
      GLenum usage,  size_t data_length, const void* data) {
  auto element_buffer = Ptr(new ElementBuffer);
  element_buffer->BufferData(GL_UNSIGNED_INT, usage, data_length, data);
  return element_buffer;
}

}  // namespace ogl
