#include "gl/framebuffer.h"

#include "gl/texture.h"
#include "utils/utils.h"

namespace ogl {
namespace {
}

void RenderBuffer::Bind() const {
    glBindRenderbuffer(GL_RENDERBUFFER, id_);  
}

void RenderBuffer::UnBind() const {
    glBindRenderbuffer(GL_RENDERBUFFER, 0);  
}

absl::Status RenderBuffer::Setup(size_t width, size_t height) {
    width_ = width;
    height_ = height;
    glGenRenderbuffers(1, &id_);
    this->Bind();
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width_, height_);
    this->UnBind();
    return absl::OkStatus();
}

absl::StatusOr<RenderBuffer::Ptr> RenderBuffer::Create(size_t width, size_t height) {
    auto render_buffer = Ptr(new RenderBuffer);
    RETURN_IF_ERROR(render_buffer->Setup(width, height));
    return render_buffer;
}

FrameBuffer::~FrameBuffer() {
    glDeleteFramebuffers(1, &id_);  
}

void FrameBuffer::Bind() const {
    glBindFramebuffer(GL_FRAMEBUFFER, id_);
    glViewport(0, 0, width_, height_);
}

void FrameBuffer::UnBind() const {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);  
}

absl::Status FrameBuffer::ReadPixels(cv::Mat& image) const {
    this->Bind();
    image.create(height_, width_, CV_8UC3);
    glReadPixels(0, 0, width_, height_, GL_BGR, GL_UNSIGNED_BYTE, image.data);
    this->UnBind();
    cv::flip(image, image, 0);
    return absl::OkStatus();
}

absl::Status FrameBuffer::Setup(size_t width, size_t height) {
    width_ = width;
    height_ = height;

    glGenFramebuffers(1, &id_);
    this->Bind();
    // Create Texture.
    ASSIGN_OR_RETURN(texture_, Texture::Create(Texture::Options()));
    RETURN_IF_ERROR(texture_->BufferData(width_, height_));
    texture_->Bind();
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture_->Id(), 0);
    // Create render buffer.
    ASSIGN_OR_RETURN(render_buffer_, RenderBuffer::Create(width_, height_));
    render_buffer_->Bind();
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, render_buffer_->Id());
    CHECK_EQ(glCheckFramebufferStatus(GL_FRAMEBUFFER), GL_FRAMEBUFFER_COMPLETE);
    this->UnBind();
    return absl::OkStatus();
}

absl::StatusOr<FrameBuffer::Ptr> FrameBuffer::Create(size_t width, size_t height) {
    auto frame_buffer = Ptr(new FrameBuffer);
    RETURN_IF_ERROR(frame_buffer->Setup(width, height));
    return frame_buffer;
}

}  // namespace ogl