#ifndef GL_VERTEX_ARRAY_H_
#define GL_VERTEX_ARRAY_H_

#include <GL/glew.h> 
#include <glog/logging.h>

#include "gl/abstract_object.h"

namespace ogl {

class VertexArray : public AbstractObject {
  public:
    VertexArray();
    ~VertexArray() override;

    void Bind() const override;
    void Unbind() const override;
};

}  // namespace ogl

#endif  // GL_VERTEX_ARRAY_H_