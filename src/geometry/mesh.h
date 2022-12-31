#ifndef GEOMETRY_MESH_H_
#define GEOMETRY_MESH_H_

#include <cstdint>
#include <string>
#include <vector>

#include <absl/status/status.h>
#include <absl/status/statusOr.h>

#include "geometry/camera.h"
#include "geometry/object3d.h"
#include "gl/program.h"

namespace ogl {

class Mesh : public Object3d {
  public:
    ~Mesh() = default;

    absl::Status Draw(const Camera& camera) const override;
    absl::Status Draw() const override;

    static absl::StatusOr<Object3d::Ptr> Create(BufferGeometry::Ptr geometry,Program::Ptr program);

  private:
    Mesh(BufferGeometry::Ptr geometry, Program::Ptr program) :
        geometry_(std::move(geometry)), program_(program), Object3d() {};

    BufferGeometry::Ptr geometry_;
    Program::Ptr program_;
};

}  // namespace ogl

#endif  // GEOMETRY_MESH_H_