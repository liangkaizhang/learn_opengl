#ifndef GL_TEXTURE_H_
#define GL_TEXTURE_H_

#include <string>

#include <GL/glew.h> 
#include <absl/status/status.h>
#include <absl/status/statusor.h>
#include <glog/logging.h>

#include "gl/abstract_object.h"

namespace ogl {

class Texture : public AbstractObject {
  public:
    using Ptr = std::unique_ptr<Texture>;

    struct Options {
      GLenum format = GL_RGB;
      GLenum type = GL_UNSIGNED_BYTE;
      GLint wrap_s = GL_REPEAT;
      GLint wrap_t = GL_REPEAT;
      GLint min_filter = GL_LINEAR;
      GLint mag_filter = GL_LINEAR;
    };

    ~Texture() override;

    absl::Status BufferData(size_t width, size_t height,
                            void* data = nullptr);
    void Bind() const;
    void UnBind() const;

    size_t Width() const { return width_; };
    size_t Height() const { return height_; };

    static absl::StatusOr<Ptr> Create(const Options& options);

  private:
    explicit Texture(const Options& options) :
        options_(options), width_(0), height_(0) {};
    absl::Status Setup();

    Options options_;
    size_t width_;
    size_t height_;
};

}  // namespace ogl

#endif  // GL_TEXTURE_H_