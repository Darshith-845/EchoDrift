#pragma once

#include "Rendering/GLCommon.h"
#include <string>
#include <iostream>

namespace EchoDrift::Rendering {

/**
 * @class Shader
 * @brief Encapsulates OpenGL shader program creation, compilation, and usage.
 */
class Shader {
private:
    // The OpenGL ID for the compiled and linked shader program.
    GLuint m_programID;

    // --- Helper Methods (Encapsulated Low-Level Logic) ---
    std::string readShaderFile(const std::string& filePath) const;
    GLuint compileShader(GLuint type, const std::string& source) const;
    void checkCompileErrors(GLuint shader, const std::string& type) const;
    void checkLinkErrors(GLuint program) const;

public:
    /**
     * @brief Loads, compiles, and links the vertex and fragment shaders.
     * @param vertexPath File path to the vertex shader (.vert).
     * @param fragmentPath File path to the fragment shader (.frag).
     */
    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    
    // RAII: Clean up the program when the object goes out of scope.
    ~Shader(); 

    // --- Abstraction Methods (The Interface) ---
    
    /**
     * @brief Activates the shader program for rendering.
     */
    void Use() const { glUseProgram(m_programID); }
    
    /**
     * @brief Sets a uniform (constant) float value in the shader.
     */
    void setUniformFloat(const std::string& name, float value) const;
    
    // TODO: Add setUniformVec2, setUniformMat4, etc., as needed.
};

} // namespace EchoDrift::Rendering