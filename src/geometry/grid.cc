#include "geometry/grid.h"

#include "geometry/buffer_geometry.h"
#include "geometry/camera.h"
#include "gl/program.h"
#include "utils/utils.h"

namespace ogl {
namespace {
const std::string kVertexShaderSource =
    "#version 330 core\n"
    "layout (location = 0) in vec3 position;\n"
    "uniform mat4 modelMatrix;\n"
    "uniform mat4 viewMatrix;\n"
	"uniform mat4 projectionMatrix;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1.0);\n"
    "}\0";

const std::string kFragmentShaderSource =
    "#version 330 core\n"
    "out vec4 frag_color;\n"
    "void main()\n"
    "{\n"
    "   frag_color = vec4(1.0);\n"
    "}\n\0";

std::vector<float> CreateGrid(float size_x,
                              float size_y,
                              size_t divisions_x,
                              size_t divisions_y) {
    std::vector<float> positions;
    positions.reserve((divisions_x + divisions_y) * 2 * 3);
    const float step_x = size_x / divisions_x;
    const float step_y = size_y / divisions_y;

    // Add lines in Y-axis.
    for (int i = 0; i < divisions_x + 1; ++i) {
        const float x = step_x * i;
        // Point A.
        positions.push_back(x);
        positions.push_back(0.0);
        positions.push_back(0.0);
        // Point B.
        positions.push_back(x);
        positions.push_back(size_y);
        positions.push_back(0.0);
    }
    // Add lines in X-axis.
    for (int i = 0; i < divisions_y + 1; ++i) {
        const float y = step_y * i;
        // Point A.
        positions.push_back(0.0);
        positions.push_back(y);
        positions.push_back(0.0);
        // Point B.
        positions.push_back(size_y);
        positions.push_back(y);
        positions.push_back(0.0);
    }
    return positions;
}

} // namespace

absl::Status Grid::Draw(const Camera& camera) const {
    geometry_->Enable();
    program_->Use();
    program_->SetUniform("projectionMatrix", camera.ProjectionMatrix());
    program_->SetUniform("viewMatrix", camera.ViewMatrix());
    program_->SetUniform("modelMatrix", matrix_);
    glDrawArrays(GL_LINES, 0, geometry_->NumVertices());
    geometry_->Disable();
    return absl::OkStatus();
}

absl::Status Grid::Draw() const {
    geometry_->Enable();
    program_->Use();
    program_->SetUniform("modelMatrix", matrix_);
    glDrawArrays(GL_LINES, 0, geometry_->NumVertices());
    geometry_->Disable();
    return absl::OkStatus();
}

absl::StatusOr<Object3d::Ptr> Grid::Create(
        float size_x, float size_y, size_t divisions_x, size_t divisions_y) {
    ASSIGN_OR_RETURN(auto program,
                     Program::Create(
                        kVertexShaderSource, kFragmentShaderSource));
    const auto positions = CreateGrid(
                size_x, size_y, divisions_x, divisions_y);
    ASSIGN_OR_RETURN(auto geometry, CreateBufferGeometry());
    CHECK_OK(geometry->SetAttribute(
        program->GetAttribLocation("position"), positions, 3));

    return std::unique_ptr<Grid>(
            new Grid(std::move(geometry), std::move(program)));
}

}  // namespace ogl