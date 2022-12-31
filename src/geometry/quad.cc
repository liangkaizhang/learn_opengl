#include "geometry/quad.h"

#include "geometry/buffer_geometry.h"
#include "geometry/camera.h"
#include "gl/program.h"
#include "gl/texture.h"
#include "utils/utils.h"

namespace ogl {
namespace {
const std::vector<float> kPositions = {
     0.5f,  0.5f, 0.0f,  // top right
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left 
};

const std::vector<float> kUvCoords = {
     1.0f,  0.0f,  // top right
     1.0f,  1.0f,  // bottom right
     0.0f,  1.0f,  // bottom left
     0.0f,  0.0f   // top left 
};

const std::vector<uint32_t> kIndices = {
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
};

std::vector<float> CreateQuad(float size_x, float size_y) {
    std::vector<float> positions;
    positions.reserve(4 * 3);
    for (int i = 0; i < kPositions.size(); i += 3) {
        positions.push_back(kPositions[i] * size_x);
        positions.push_back(kPositions[i + 1] * size_y);
        positions.push_back(kPositions[i + 2]);
    }
    return positions;
}

} // namespace

absl::StatusOr<Object3d::Ptr> Quad::Create(float size_x, float size_y,
                                           Program::Ptr program) {
    const auto positions = CreateQuad(size_x, size_y);
    ASSIGN_OR_RETURN(auto geometry, CreateBufferGeometry());
    CHECK_OK(geometry->SetAttribute(
        program->GetAttribLocation("position"), positions, 3));
    CHECK_OK(geometry->SetAttribute(
        program->GetAttribLocation("texcoord"), kUvCoords, 2));
    CHECK_OK(geometry->SetIndex(kIndices));
    return std::unique_ptr<Quad>(
            new Quad(std::move(geometry), program));
}

}  // namespace ogl