//* Required GLSL version
#version 330 core

//* Input vertex attributes
//* 'in' 'type' 'variableName'
layout(location = 0) in vec2 position;
layout(location = 1) in vec3 color;

//* Output vertex attributes (TO FRAGMENT SHADER)
out vec4 fragmentColor;

void main()
{
    gl_PointSize = 10.0f;

    //* Output vertex attributes to fragment shader
    fragmentColor = vec4(color, 1.0);

    //* Reqired: Output final vertex position
    gl_Position = vec4(position, 0.0, 1.0);
}
