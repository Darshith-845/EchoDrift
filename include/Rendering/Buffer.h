#pragma once

#include "Rendering/GLCommon.h"
#include <vector>

namespace EchoDrift::Rendering {

/**
 * @class Buffer
 * @brief Encapsulates the management of OpenGL Vertex Array Objects (VAO) 
 * and Vertex Buffer Objects (VBO) for storing geometry data.
 */
class Buffer {
private:
    // OpenGL IDs are hidden and managed internally.
    GLuint m_VAO = 0;
    GLuint m_VBO = 0;
    
    GLsizei m_vertexCount = 0; // Number of vertices stored

public:
    Buffer();
    
    // RAII: Cleans up OpenGL resources.
    ~Buffer(); 

    /**
     * @brief Binds the VAO, making it the active context for drawing.
     */
    void Bind() const {
        glBindVertexArray(m_VAO);
    }

    /**
     * @brief Unbinds the VAO.
     */
    void Unbind() const {
        glBindVertexArray(0);
    }
    
    /**
     * @brief Uploads data to the VBO and sets the vertex attribute pointers 
     * using the VAO (our data format is simple vec2 position).
     * @param vertices The raw data to upload (e.g., a vector of floats).
     */
    void SetData(const std::vector<float>& vertices);
    
    GLsizei getVertexCount() const { return m_vertexCount; }
};

} // namespace EchoDrift::Rendering