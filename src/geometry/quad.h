#ifndef GEOMETRY_QUAD_H_
#define GEOMETRY_QUAD_H_

#include <cstdint>
#include <string>
#include <vector>

#include <absl/status/status.h>
#include <absl/status/statusOr.h>

#include "geometry/camera.h"
#include "geometry/mesh.h"
#include "gl/program.h"
#include "gl/texture.h"

namespace ogl {

class Quad : public Mesh {
  public:
    ~Quad() = default;

    static absl::StatusOr<Object3d::Ptr> Create(float size_x, float size_y,
                                                Program::Ptr program);
  private:
    Quad(BufferGeometry::Ptr geometry, Program::Ptr program) :
          Mesh(std::move(geometry), program) {};
};

}  // namespace ogl

#endif  // GEOMETRY_QUAD_H_