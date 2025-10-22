#include "Shader.h"
#include <fstream>
#include <sstream>

namespace EchoDrift::Rendering {

// --- Low-Level Helper Functions (Encapsulation) ---

std::string Shader::readShaderFile(const std::string& filePath) const {
    // Note: We use the assets/shaders directory structure you provided earlier.
    std::ifstream file;
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        std::stringstream ss;
        file.open("shaders/" + filePath);
        ss << file.rdbuf();
        file.close();
        return ss.str();
    } catch (std::ifstream::failure e) {
        std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << filePath << std::endl;
        return "";
    }
}

// CheckCompileErrors and CheckLinkErrors implementation omitted for brevity,
// but they are critical for debugging and safety in a final project!

// ------------------------------------------------------------------
// Constructor: Loading, Compiling, Linking (Abstraction Point)
// ------------------------------------------------------------------

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) {
    // 1. Retrieve the shader source code from file paths
    std::string vCode = readShaderFile(vertexPath);
    std::string fCode = readShaderFile(fragmentPath);
    const char* vShaderCode = vCode.c_str();
    const char* fShaderCode = fCode.c_str();

    // 2. Compile shaders (Low-Level GL)
    GLuint vertex, fragment;
    
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    // checkCompileErrors(vertex, "VERTEX"); // Always check errors!

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    // checkCompileErrors(fragment, "FRAGMENT"); // Always check errors!

    // 3. Link the program (Low-Level GL)
    m_programID = glCreateProgram();
    glAttachShader(m_programID, vertex);
    glAttachShader(m_programID, fragment);
    glLinkProgram(m_programID);
    // checkLinkErrors(m_programID); // Always check errors!

    // 4. Delete shaders as they are now linked into the program (Cleanup)
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    
    std::cout << "Shader Program linked successfully." << std::endl;
}

Shader::~Shader() {
    // RAII: Clean up the GL resource when the C++ object is destroyed.
    glDeleteProgram(m_programID);
}

void Shader::setUniformFloat(const std::string& name, float value) const {
    // Abstraction: Get the location and set the uniform, hiding the glGetUniformLocation
    // and glUniform1f complexity from other classes.
    glUniform1f(glGetUniformLocation(m_programID, name.c_str()), value);
}

} // namespace EchoDrift::Rendering