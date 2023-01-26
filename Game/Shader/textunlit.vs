#version 330 core
layout (location = 0) in vec4 vertex; // <vec2 position, vec2 texCoords>

out vec2 TexCoords;

uniform mat4 uProjectionMatrix;
uniform mat4 uModelMatrix;

void main()
{
    TexCoords = vertex.zw;
    vec4 finalPos = uProjectionMatrix * vec4(vertex.xy, 0.0, 1.0);

    gl_Position = finalPos;
}