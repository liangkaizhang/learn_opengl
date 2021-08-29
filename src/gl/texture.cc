#ifndef RENDERER_TEXTURE_H_
#define RENDERER_TEXTURE_H_

#include "gl/texture.h"

#include "opencv2/opencv.hpp"

namespace ogl {

Texture::Texture(const std::string& filename) {
    // load and create a texture 
    glGenTextures(1, &texture_);
    glBindTexture(GL_TEXTURE_2D, texture_); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // Load image file.
    const auto image = cv::imread(filename);
    const size_t width = image.size().width;
    const size_t height = image.size().height; 
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, image.ptr());
    glGenerateMipmap(GL_TEXTURE_2D);
}

}  // namespace ogl

#endif  // RENDERER_TEXTURE_H_