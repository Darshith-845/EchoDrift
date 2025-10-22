#include "Rendering/Renderer.h"
#include <iostream>
#include "Rendering/Shader.h"

namespace EchoDrift::Rendering {

void Renderer::Init() {
    // This is where we would enable depth test, blending, etc.
    m_defaultShader = std::make_unique<Shader>("simple.vert", "simple.frag");

    // Enable Blending for transparency and glow effects
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE); // Additive blending for neon glow

    // Set line width for trails (can be changed later)
    glLineWidth(2.0f); // Make lines a bit thicker

    std::cout << "Renderer Initialized. Shader Program Ready. Blending Enabled." << std::endl;
}

void Renderer::ClearScreen() {
    // This is the LOW-LEVEL command we are ABSTRACTION away.
    // The GameManager doesn't need to know 'glClearColor' or 'glClear'.
    glClearColor(0.0f, 0.0f, 0.1f, 1.0f); // Dark blue for the neon look
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::Draw(const Buffer& buffer, const Shader& shader, float r, float g, float b) const {
    // 1. Activate the Shader Program
    shader.Use(); 
    
    // 2. Pass the Color Uniform
    // (We assume the shader has a uniform called "uColor" that accepts a float vector)
    // NOTE: If you implemented a setUniformVec3 function in Shader.h/cpp, use it here!
    // Since we only made setUniformFloat, we'll assume a vec3 uniform for colors.
    
    // --- TEMPORARY UNIFORM FIX ---
    // Since we only implemented setUniformFloat, we'll call a hypothetical setUniformVec3 here.
    // If your Shader class uses GLM or similar for Vec3, you MUST implement this function:
    // shader.setUniformVec3("uColor", glm::vec3(r, g, b)); 
    // For this example, we assume setUniformVec3 exists.
    
    // You MUST implement this function in Shader.cpp!
    GLint colorLocation = glGetUniformLocation(shader.getProgramID(), "uColor"); 
    glUniform3f(colorLocation, r, g, b);
    // -----------------------------
    
    // 3. Bind the Geometry Data
    buffer.Bind();

    // 4. Draw the Geometry
    // We are drawing GL_LINES because the Grid setup created pairs of vertices for lines.
    glDrawArrays(primitiveType, 0, buffer.getVertexCount()); // Use the passed primitiveType    
    // 5. Cleanup (optional, but good practice)
    buffer.Unbind();
}

void Renderer::DrawObject(float r, float g, float b) {
// 1. Activate the Shader Program
    // m_defaultShader->Use(); 
    
    // // 2. Pass the desired color to the Fragment Shader
    // m_defaultShader->setUniformFloat("uColor", r);
    // m_defaultShader->setUniformFloat("uColor + 1", g); // ERROR! uColor is a vec3, not a float.
    // Let's assume we implement a setUniformVec3 helper function:
    // m_defaultShader->setUniformVec3("uColor", glm::vec3(r, g, b)); 
    
    // Since we don't have the VBO/VAO system yet, we cannot draw anything properly
    // with this shader. We will finish the DrawObject in the next step.
    
    // For now, we leave the immediate mode drawing for debug purposes, 
    // but recognize it MUST be removed in the next step:
    // glColor3f(r, g, b); // Will be ignored by modern GL pipeline
    // glBegin(GL_QUADS); // WILL BE REMOVED!
    // ...
    // glEnd();}

} // namespace EchoDrift::Rendering