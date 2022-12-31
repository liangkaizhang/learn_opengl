#ifndef RENDERER_IMAGE_RENDER_H_
#define RENDERER_IMAGE_RENDER_H_

#include <absl/status/status.h>
#include <GL/glew.h> 

#include "Eigen/Dense"
#include "renderer/abstract_renderer.h"
#include "opencv2/opencv.hpp"

namespace ogl {

class ImageRender : public AbstractRenderer {
  public:
    ~ImageRender() = default;
    static std::unique_ptr<AbstractRenderer> Create(const cv::Mat& image);
    void SetProjection(const Eigen::Matrix4f& projection) override;
    void SetModelView(const Eigen::Matrix4f model_view) override;
  private:
    absl::Status Init(
        const std::string& vertex_shader_source,
        const std::string& fragment_shader_source,
        const cv::Mat& image);
    size_t image_width_;
    size_t image_height_;
};

}  // namespace ogl

#endif  // RENDERER_IMAGE_RENDER_H_