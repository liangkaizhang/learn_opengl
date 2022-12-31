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

class DistortionMesh : public Mesh {
  public:
    struct DistortParams {
        float tmp = 0.0;
    };

    ~DistortionMesh() = default;

    static absl::StatusOr<Object3d::Ptr> Create(const DistortParams& params, Program::Ptr program);

  private:
    DistortionMesh(BufferGeometry::Ptr geometry, Program::Ptr program) :
            Mesh(std::move(geometry), program) {};
};

}  // namespace ogl

#endif  // GEOMETRY_MESH_H_