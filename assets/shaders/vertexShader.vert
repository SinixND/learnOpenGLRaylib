//* Required GLSL version
#version 330 core

//* Input vertex attributes
//* 'in' 'type' 'variableName'
layout(location = 0) in vec2 vertexPosition;
layout(location = 1) in vec3 vertexColor;

//* Input uniform (const?) values
// uniform mat4 var;

//* Output vertex attributes (TO FRAGMENT SHADER)
out vec4 fragmentColor;
out vec2 fragmentPosition;

void main()
{
    gl_PointSize = 10.0f;

    //* Output vertex attributes to fragment shader
    fragmentColor = vec4(vertexColor, 1.0);
    fragmentPosition = vertexPosition;

    //* Reqired: Output final vertex position
    gl_Position = vec4(vertexPosition, 0.0, 1.0);
}
