#include "Buffer.h"
#include <iostream>

namespace EchoDrift::Rendering {

// ------------------------------------------------------------------
// Constructor/Destructor (RAII)
// ------------------------------------------------------------------

Buffer::Buffer() {
    // Generate the VAO and VBO (Low-Level GL calls are encapsulated here)
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    
    // std::cout << "Buffer created (VAO: " << m_VAO << ", VBO: " << m_VBO << ")" << std::endl;
}

Buffer::~Buffer() {
    // Clean up the OpenGL resources
    if (m_VAO) glDeleteVertexArrays(1, &m_VAO);
    if (m_VBO) glDeleteBuffers(1, &m_VBO);
    // std::cout << "Buffer destroyed." << std::endl;
}

// ------------------------------------------------------------------
// Data Upload
// ------------------------------------------------------------------

void Buffer::SetData(const std::vector<float>& vertices) {
    if (vertices.empty()) return;
    
    // 1. Calculate and store vertex count
    // Data layout: We assume simple position data (x, y) = 2 floats per vertex.
    m_vertexCount = static_cast<GLsizei>(vertices.size() / 2); 
    
    // 2. Bind the VAO and VBO
    Bind(); // Binds m_VAO
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    
    // 3. Upload the data from CPU to GPU
    // GL_STATIC_DRAW means the data won't change often (good for our Grid).
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
    
    // 4. Set the vertex attribute pointer (The critical step stored by the VAO)
    // layout (location = 0) in the Vertex Shader:
    glVertexAttribPointer(0,        // Location 0 in shader (aPos)
                          2,        // Size of the attribute (vec2 = 2 floats)
                          GL_FLOAT, // Data type
                          GL_FALSE, // Don't normalize
                          2 * sizeof(float), // Stride: Size of one vertex (2 floats)
                          (void*)0); // Offset in the buffer
    
    // 5. Enable the attribute
    glEnableVertexAttribArray(0);
    
    // 6. Unbind (optional, but good practice)
    glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind VBO first
    Unbind();                         // Unbind VAO last
}

} // namespace EchoDrift::Rendering