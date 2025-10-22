#pragma once

#include "Entities/Entity.h" // For the Vec2 struct
#include "Rendering/GLCommon.h"
#include "Rendering/Buffer.h" // Include the new Buffer header

namespace EchoDrift::Game {

using EchoDrift::Entities::Vec2;

/**
 * @class Grid
 * @brief Defines the game world boundaries and manages coordinate transformations.
 */
class Grid {
private:
    // --- Encapsulated Dimensions ---
    const int m_width;
    const int m_height;
    const float m_cellSize; // Size of one grid cell in normalized screen coordinates (NDC).

    // The Grid now owns a Buffer object.
    std::unique_ptr<EchoDrift::Rendering::Buffer> m_buffer;

    // --- Rendering Data (Modern OpenGL) ---
    // These hold the raw data for the grid lines.
    GLuint m_VAO = 0; // Vertex Array Object
    GLuint m_VBO = 0; // Vertex Buffer Object

    /**
     * @brief Generates the vertex data for the grid lines and fills the VBO/VAO.
     */
    void setupBuffers(); 

public:
    Grid(int width, int height, float cellSize);
    ~Grid(); // Crucial for cleaning up OpenGL buffers (RAII concept)

    /**
     * @brief Translates an integer grid position into a normalized screen coordinate (-1.0 to 1.0).
     * @param gridPos The integer (x, y) position.
     * @return A Vec2 where x and y are float coordinates for OpenGL.
     */
    Vec2 gridToScreen(const Vec2& gridPos) const;

    /**
     * @brief Draws the grid lines using the OpenGL buffers.
     */
    void Render(); 

    // Accessors for boundaries (Encapsulation provides read-only access)
    int getWidth() const { return m_width; }
    int getHeight() const { return m_height; }
};

} // namespace EchoDrift::Game