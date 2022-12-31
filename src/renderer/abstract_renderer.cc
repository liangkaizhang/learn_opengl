#include "renderer/abstract_renderer.h"

namespace ogl {

absl::Status AbstractRenderer::UpdateTexture(const cv::Mat& image) {
    return texture_->BufferData(image);
}

void AbstractRenderer::Render() const {
    glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LEQUAL); 
    // glEnable(GL_CULL_FACE);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    program_->Use();
    if (texture_) texture_->Bind();
    vao_.Bind();
    for (const auto& buffer_iter : array_buffers_) {
        const auto attr_loc = program_->GetAttribLocation(buffer_iter.first);
        buffer_iter.second.Enable(attr_loc);
    }
    index_buffer_.Draw();
    vao_.Unbind();
}

void AbstractRenderer::Render(const Texture& texture) const {
    glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LEQUAL); 
    // glEnable(GL_CULL_FACE);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    program_->Use();
    texture.Bind();
    vao_.Bind();
    for (const auto& buffer_iter : array_buffers_) {
        const auto attr_loc = program_->GetAttribLocation(buffer_iter.first);
        buffer_iter.second.Enable(attr_loc);
    }
    index_buffer_.Draw();
    vao_.Unbind();
}

void AbstractRenderer::Render(const FrameBuffer& framebuffer) const {
    framebuffer.Bind();
    Render();
    framebuffer.Unbind();
}

}  // namespace ogl