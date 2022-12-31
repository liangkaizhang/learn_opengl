#ifndef GEOMETRY_GRID_H_
#define GEOMETRY_GRID_H_

#include <cstdint>
#include <string>
#include <vector>

#include <absl/status/status.h>
#include <absl/status/statusOr.h>

#include "geometry/camera.h"
#include "geometry/object3d.h"
#include "gl/program.h"

namespace ogl {

class Grid : public Object3d {
  public:
    ~Grid() = default;

    absl::Status Draw(const Camera& camera) const override;
    absl::Status Draw() const override;

    static absl::StatusOr<Object3d::Ptr> Create(
        float size_x, float size_y, size_t divisions_x, size_t divisions_y);

  private:
    Grid(BufferGeometry::Ptr geometry, Program::Ptr program) :
        geometry_(std::move(geometry)), program_(program), Object3d() {};

    BufferGeometry::Ptr geometry_;
    Program::Ptr program_;
};

}  // namespace ogl

#endif  // GEOMETRY_GRID_H_