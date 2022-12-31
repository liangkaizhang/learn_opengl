#include <string>
#include <stdlib.h>     /* srand, rand */

#include <absl/status/statusor.h>
#include "absl/random/random.h"
#include <glog/logging.h>
#include "Eigen/Dense"

#include "window/window.h"
#include "window/glfw_window.h"
#include "gl/program.h"
#include "utils/utils.h"
#include "geometry/buffer_geometry.h"
#include "geometry/camera.h"
#include "geometry/mesh.h"
#include "geometry/grid.h"

namespace ogl {
namespace {
constexpr size_t kWidth = 1080;
constexpr size_t kHeight = 720;

const std::string kVertexShaderSource =
    "#version 330 core\n"
    "layout (location = 0) in vec3 position;\n"
    "layout (location = 1) in vec4 color;\n"
    "uniform mat4 modelMatrix;\n"
    "uniform mat4 viewMatrix;\n"
	"uniform mat4 projectionMatrix;\n"
    "out vec3 vPosition;\n"
    "out vec4 vColor;\n"
    "void main()\n"
    "{\n"
    "   vPosition = position;\n"
    "   vColor = color;\n"
    "   gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1.0);\n"
    "}\0";

const std::string kFragmentShaderSource =
    "#version 330 core\n"
    "out vec4 frag_color;\n"
    "in vec3 vPosition;\n"
    "in vec4 vColor;\n"
    "uniform float time;\n"
    "void main()\n"
    "{\n"
    "   vec4 color = vec4(vColor);\n"
    "   color.r += sin(vPosition.x * 10.0 + time) * 0.5;\n"
    "   frag_color = color;\n"
    "}\n\0";

}  // namespace

absl::Status Render() {
    ogl::Window::WindowOptions opts;
    opts.height = kHeight;
    opts.width = kWidth;
    opts.title = "Hello Geometry!";

    Camera camera;
    camera.SetFocal(1000, 1000);
    camera.SetSize(kWidth, kHeight);
    camera.SetCenter(kWidth / 2, kHeight / 2);
    camera.SetTranslation({0.0, 0.0, -4});
    camera.SetRotation(Eigen::Matrix3f::Identity());
    camera.Rotate(-0.4 * M_PI, Eigen::Vector3f::UnitX());

    ASSIGN_OR_RETURN(const auto window,
                     ogl::createGlfwWindow(opts));
    CHECK(window != nullptr);

    absl::BitGen bitgen;
    const int num_vertices = 600;
    std::vector<float> positions;
    std::vector<float> colors;
    for (int i = 0; i < num_vertices; ++i) {
        positions.push_back(absl::Uniform(bitgen, 0.0, 1.0) - 0.5);
        positions.push_back(absl::Uniform(bitgen, 0.0, 1.0) - 0.5);
        positions.push_back(absl::Uniform(bitgen, 0.0, 1.0) - 0.5);
        colors.push_back(absl::Uniform(bitgen, 0.0, 1.0));
        colors.push_back(absl::Uniform(bitgen, 0.0, 1.0));
        colors.push_back(absl::Uniform(bitgen, 0.0, 1.0));
        colors.push_back(absl::Uniform(bitgen, 0.0, 1.0));
    }
    // Setup OpenGL.
    ASSIGN_OR_RETURN(const auto program,
                     ogl::Program::Create(
                        kVertexShaderSource, kFragmentShaderSource));
    program->SetUniform("time", 0.0);

    ASSIGN_OR_RETURN(auto buffer_geometry, CreateBufferGeometry());
    CHECK_OK(buffer_geometry->SetAttribute(
        program->GetAttribLocation("position"), positions, 3));
    CHECK_OK(buffer_geometry->SetAttribute(
        program->GetAttribLocation("color"), colors, 4));

    ASSIGN_OR_RETURN(auto mesh, Mesh::Create(std::move(buffer_geometry), program));

    const float grid_x = 2.0;
    const float grid_y = 2.0;
    ASSIGN_OR_RETURN(auto grid, Grid::Create(grid_x, grid_y, 10, 10));
    grid->SetTranslation({-0.5 * grid_x, -0.5 * grid_y, -0.5});

    long long time = 1;
    while (!window->ShouldClose()) {
        window->OnBeforeRender();

        program->SetUniform("time", time * 0.1);

        const auto position = -(grid->Rotation().transpose()) * grid->Translation();
        grid->SetRotation(0.01 * time, Eigen::Vector3f::UnitZ());
        grid->SetTranslation(-grid->Rotation() * position);

        CHECK_OK(grid->Draw(camera));

        mesh->SetRotation(grid->Rotation());
        CHECK_OK(mesh->Draw(camera));

        window->OnAfterRender();
        time++;
    }
    return absl::OkStatus();
}

}  // namespace ogl

int main() {
    CHECK_OK(ogl::Render());
    return 0;
}

