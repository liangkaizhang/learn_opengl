#ifndef GL_ABSTRACT_OBJECT_H_
#define GL_ABSTRACT_OBJECT_H_

#include <limits>

#include <GL/glew.h> 

namespace ogl {

constexpr GLuint kInvalidId = std::numeric_limits<GLuint>::max();

class AbstractObject {
  public:
    AbstractObject() : id_(kInvalidId) {};
    virtual ~AbstractObject() = default;

    AbstractObject(const AbstractObject&) = delete;
    AbstractObject & operator=(const AbstractObject&) = delete;

    GLuint Id() const { return id_; };

  protected:
    GLuint id_;
};

}  // namespace ogl

#endif  // GL_ABSTRACT_OBJECT_H_