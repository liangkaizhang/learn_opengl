#ifndef GEOMETRY_QUAD_H_
#define GEOMETRY_QUAD_H_

#include <cstdint>
#include <string>
#include <vector>

#include <absl/status/status.h>
#include <absl/status/statusOr.h>

#include "geometry/camera.h"
#include "geometry/object3d.h"
#include "gl/program.h"
#include "gl/texture.h"

namespace ogl {

class Quad : public Object3d {
  public:
    ~Quad() = default;

    absl::Status Draw(const Camera& camera) const override;
    absl::Status Draw() const override;

    static absl::StatusOr<Object3d::Ptr> Create(float size_x, float size_y,
                                                Program::Ptr program);

  private:
    Quad(BufferGeometry::Ptr geometry, Program::Ptr program) :
        geometry_(std::move(geometry)), program_(program), Object3d() {};

    BufferGeometry::Ptr geometry_;
    Program::Ptr program_;
};

}  // namespace ogl

#endif  // GEOMETRY_QUAD_H_