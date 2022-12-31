#include <fstream>

#include <glog/logging.h>

#include "geometry/mesh.h"

namespace ogl {

absl::Status Mesh::Draw(const Camera& camera) const {
    geometry_->Enable();
    program_->Use();
    program_->SetUniform("projectionMatrix", camera.ProjectionMatrix());
    program_->SetUniform("viewMatrix", camera.ViewMatrix());
    program_->SetUniform("modelMatrix", matrix_);
    if (geometry_->HasIndex()) {
        glDrawElements(GL_TRIANGLES, geometry_->NumIndice(), GL_UNSIGNED_INT, 0);
    } else {
        glDrawArrays(GL_TRIANGLES, 0, geometry_->NumVertices());
    }
    geometry_->Disable();
    return absl::OkStatus();
}

absl::Status Mesh::Draw() const {
    geometry_->Enable();
    program_->Use();
    program_->SetUniform("modelMatrix", matrix_);
    if (geometry_->HasIndex()) {
        glDrawElements(GL_TRIANGLES, geometry_->NumIndice(), GL_UNSIGNED_INT, 0);
    } else {
        glDrawArrays(GL_TRIANGLES, 0, geometry_->NumVertices());
    }
    geometry_->Disable();
    return absl::OkStatus();
}

absl::StatusOr<Object3d::Ptr> Mesh::Create(
        BufferGeometry::Ptr geometry, Program::Ptr program) {
    return std::unique_ptr<Mesh>(
        new Mesh(std::move(geometry), program));
}

}  // namespace ogl