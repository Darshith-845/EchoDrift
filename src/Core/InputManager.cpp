#pragma once

// We include necessary GL headers here, NOT in GameManager.h.
#include <GL/glew.h> 

namespace EchoDrift::Rendering {

/**
 * @class Renderer
 * @brief Handles all low-level OpenGL commands. 
 * Abstracts graphics details away from the core game logic.
 */
class Renderer {
private:
    // Renderer state variables will go here later (Shaders, Buffers, etc.)
    // For now, just a placeholder.

public:
    Renderer() = default;
    ~Renderer() = default;

    /**
     * @brief Initializes any necessary OpenGL state.
     */
    void Init();

    /**
     * @brief Sets the clear color and clears the buffers (the sky of our game).
     */
    void ClearScreen();

    /**
     * @brief Placeholder for drawing general objects (Echo, Grid, etc.).
     * @param color The color to draw the next object.
     */
    void DrawObject(float r, float g, float b); 
};

} // namespace EchoDrift::Rendering