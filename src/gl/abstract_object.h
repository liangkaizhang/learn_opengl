#ifndef GL_ABSTRACT_OBJECT_H_
#define GL_ABSTRACT_OBJECT_H_

#include <GL/glew.h> 

namespace ogl {

class AbstractObject {
  public:
    AbstractObject() = default;
    virtual ~AbstractObject() = default;

    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

    GLuint Id() const { return id_; };
  protected:
    GLuint id_;
    bool is_generated_ = false;
};


}  // namespace ogl

#endif  // GL_ABSTRACT_OBJECT_H_