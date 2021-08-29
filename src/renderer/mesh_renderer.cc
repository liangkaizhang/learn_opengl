#include "renderer/mesh_renderer.h"

namespace ogl {

absl::Status MeshRender::Init(const Shader& shader, const ColoredMesh& mesh) {
    // Init buffers.
    glGenVertexArrays(1, &vao_);
    glGenBuffers(1, &vbo_);
    glGenBuffers(1, &ebo_);
    glBindVertexArray(vao_);

    // Buffer position and color data.
    const GLuint positions_size = mesh.positions.size() * sizeof(float);
    const GLuint colors_size = mesh.colors.size() * sizeof(float);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(GL_ARRAY_BUFFER, positions_size + colors_size, NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, positions_size, &(mesh.positions[0]));
    glBufferSubData(GL_ARRAY_BUFFER, positions_size, colors_size, &(mesh.colors[0]));
    // Position attribute.
    const GLuint position_loc = shader.GetAttributeLocation("a_position");
    glEnableVertexAttribArray(position_loc);
    glVertexAttribPointer(position_loc, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0));
    // Color attribute.
    const GLuint color_loc = shader.GetAttributeLocation("a_color");
    glEnableVertexAttribArray(color_loc);
    glVertexAttribPointer(color_loc, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                          reinterpret_cast<void*>(positions_size));
    // Bind EBO.
    num_indices_ = mesh.indices.size();
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, num_indices_ * sizeof(uint32_t), &(mesh.indices[0]), GL_STATIC_DRAW);

    // Unbind buffers.
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0); 

    // Set shader program.
    program_ = shader.Program();
    return absl::OkStatus();
}

}  // namespace ogl