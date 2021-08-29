#ifndef RENDERER_COLORED_MESH_H_
#define RENDERER_COLORED_MESH_H_

#include <cstdint>
#include <string>
#include <vector>

#include <absl/status/status.h>

namespace ogl {

struct ColoredMesh {
    std::vector<float> positions;
    std::vector<float> colors;
    std::vector<uint32_t> indices;

    absl::Status LoadFromFile(const std::string& file_name);
};

}  // namespace ogl

#endif  // RENDERER_COLORED_MESH_H_