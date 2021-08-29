#include "renderer/texture_renderer.h"

namespace ogl {

absl::Status TextureRender::Init(const Shader& shader, const TexturedMesh& mesh, const Texture& texture) {
    // Init buffers.
    glGenVertexArrays(1, &vao_);
    glGenBuffers(1, &vbo_);
    glGenBuffers(1, &ebo_);
    glBindVertexArray(vao_);

    // Buffer positions and texcoords data.
    const GLuint positions_size = mesh.positions.size() * sizeof(float);
    const GLuint texcoords_size = mesh.texcoords.size() * sizeof(float);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(GL_ARRAY_BUFFER, positions_size + texcoords_size, NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, positions_size, &(mesh.positions[0]));
    glBufferSubData(GL_ARRAY_BUFFER, positions_size, texcoords_size, &(mesh.texcoords[0]));
    // Position attribute.
    const GLuint position_loc = shader.GetAttributeLocation("a_position");
    glEnableVertexAttribArray(position_loc);
    glVertexAttribPointer(position_loc, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0));
    // Texure coord attribute.
    const GLuint texcoord_loc = shader.GetAttributeLocation("a_texcoord");
    glEnableVertexAttribArray(texcoord_loc);
    glVertexAttribPointer(texcoord_loc, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float),
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
    // Set texture.
    texture_ = texture.Id();
    return absl::OkStatus();
}

void TextureRender::Render() const {
    glBindTexture(GL_TEXTURE_2D, texture_);
    glUseProgram(program_);
    glBindVertexArray(vao_);
    glDrawElements(GL_TRIANGLE_STRIP, num_indices_, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

}  // namespace ogl