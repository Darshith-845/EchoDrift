#version 330 core
out vec4 FragColor; // The final color output

uniform vec3 uColor; // The color passed from the C++ side

void main()
{
    FragColor = vec4(uColor, 1.0); // Use the color passed from C++
}