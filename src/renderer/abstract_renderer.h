#ifndef RENDERER_ABSTRACT_RENDER_H_
#define RENDERER_ABSTRACT_RENDER_H_

#include <glog/logging.h>
#include <absl/status/status.h>
#include <GL/glew.h> 

namespace ogl {

class AbstractRenderer {
  public:
    AbstractRenderer() = default;
    ~AbstractRenderer() = default;

    virtual void Render() const;
  protected:
    GLuint num_indices_;
    GLuint vao_;
    GLuint vbo_;
    GLuint ebo_;
    GLuint program_;
};

}  // namespace ogl

#endif  // RENDERER_ABSTRACT_RENDER_H_
