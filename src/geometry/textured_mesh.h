#ifndef RENDERER_TEXTURED_MESH_H_
#define RENDERER_TEXTURED_MESH_H_

#include <cstdint>
#include <string>
#include <vector>

#include <absl/status/status.h>

namespace ogl {

struct TexturedMesh {
    std::vector<float> positions;
    std::vector<float> texcoords;
    std::vector<uint32_t> indices;

    absl::Status LoadFromFile(const std::string& file_name);
};

}  // namespace ogl

#endif  // RENDERER_TEXTURED_MESH_H_