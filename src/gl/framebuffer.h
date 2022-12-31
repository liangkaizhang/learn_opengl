#ifndef GL_FRAMEBUFFER_H_
#define GL_FRAMEBUFFER_H_

#include <GL/glew.h> 
#include <glog/logging.h>
#include <absl/status/status.h>
#include <absl/status/statusor.h>
#include "opencv2/opencv.hpp"

#include "gl/abstract_object.h"
#include "gl/texture.h"

namespace ogl {

class RenderBuffer : public AbstractObject {
public:
  using Ptr = std::unique_ptr<RenderBuffer>;

  ~RenderBuffer() = default;

  void Bind() const;
  void UnBind() const;

  size_t Width() const { return width_; };
  size_t Height() const { return height_; };

  static absl::StatusOr<Ptr> Create(size_t width, size_t height);

private:
  RenderBuffer() = default;
  absl::Status Setup(size_t width, size_t height);

  size_t width_;
  size_t height_;
};

class FrameBuffer : public AbstractObject {
public:
  using Ptr = std::unique_ptr<FrameBuffer>;

  ~FrameBuffer() override;

  void Bind() const;
  void UnBind() const;

  const Texture& Texture() const { return *texture_; };
  absl::Status ReadPixels(cv::Mat& image) const;

  size_t Width() const { return width_; };
  size_t Height() const { return height_; };

  static absl::StatusOr<Ptr> Create(size_t width, size_t height);

private:
  FrameBuffer() = default;
  absl::Status Setup(size_t width, size_t height);

  Texture::Ptr texture_;
  RenderBuffer::Ptr render_buffer_;

  size_t width_;
  size_t height_;
};

}  // namespace ogl

#endif  // GL_FRAMEBUFFER_H_