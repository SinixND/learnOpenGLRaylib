// Required GLSL version
#version 330

// Input vertex attributes (FROM VERTEX SHADER)
in vec4 fragmentColor;

// Output fragment color
out vec4 finalColor;

// NOTE: Add here your custom variables

void main()
{
    //* Required: output final vertex color
    finalColor = fragmentColor;
}
