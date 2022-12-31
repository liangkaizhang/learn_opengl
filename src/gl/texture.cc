#ifndef RENDERER_TEXTURE_H_
#define RENDERER_TEXTURE_H_

#include "gl/texture.h"
#include "utils/utils.h"

namespace ogl {

Texture::~Texture() {
    glDeleteTextures(1, &id_);
}

absl::Status Texture::BufferData(size_t width,
                                 size_t height,
                                 void* data) {
    width_ = width;
    height_ = height;
    this->Bind();
    glTexImage2D(GL_TEXTURE_2D, 0,
                 GL_RGB,
                 width_, height_, 0,
                 options_.format, options_.type,
                 data);
    this->UnBind(); 
    return absl::OkStatus();
}

// absl::Status Texture::GenerateMipmap() const {
//     this->Bind();
//     glGenerateMipmap(GL_TEXTURE_2D);
//     this->UnBind(); 
//     return absl::OkStatus();
// }

void Texture::Bind() const {
    glBindTexture(GL_TEXTURE_2D, id_);
}

void Texture::UnBind() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}

absl::Status Texture::Setup() {
    glGenTextures(1, &id_);
    this->Bind();
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, options_.wrap_s);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, options_.wrap_t);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, options_.min_filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, options_.mag_filter);
    this->UnBind();
    return absl::OkStatus();
}

absl::StatusOr<Texture::Ptr> Texture::Create(const Options& options) {
    auto texture = Ptr(new Texture {options});
    RETURN_IF_ERROR(texture->Setup());
    return texture;
}

}  // namespace ogl

#endif  // RENDERER_TEXTURE_H_