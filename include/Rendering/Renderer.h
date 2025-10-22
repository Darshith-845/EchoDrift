#pragma once

// We include necessary GL headers here, NOT in GameManager.h.
#include "Rendering/GLCommon.h"
#include "Shader.h" // Need the Shader class definition

namespace EchoDrift::Rendering {

/**
 * @class Renderer
 * @brief Handles all low-level OpenGL commands. 
 * Abstracts graphics details away from the core game logic.
 */
class Renderer {
private:
    // Composition: The Renderer owns the shader program it needs.
    std::unique_ptr<Shader> m_defaultShader;

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

    void Draw(const Buffer& buffer, const Shader& shader, float r, float g, float b, GLenum primitiveType) const;};

} // namespace EchoDrift::Rendering