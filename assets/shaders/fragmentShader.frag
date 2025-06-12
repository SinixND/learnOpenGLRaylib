// Required GLSL version
#version 330

// Input vertex attributes (FROM VERTEX SHADER)
in vec4 fragmentColor;
in vec2 fragmentPosition;

// Input uniform (const?) values
// uniform sampler2D texture0;
// uniform vec4 colDiffuse;

// Output fragment color
out vec4 finalColor;

// NOTE: Add here your custom variables

void main()
{
    //* Required: output final vertex color
    finalColor = vec4(
        fragmentColor.r * sqrt(
            (fragmentPosition.x 
                * fragmentPosition.x) 
            + (fragmentPosition.y 
                * fragmentPosition.y)),
        fragmentColor.g * sqrt(
            (fragmentPosition.x 
                * fragmentPosition.x) 
            + (fragmentPosition.y 
                * fragmentPosition.y)),
        fragmentColor.b * sqrt(
            (fragmentPosition.x 
                * fragmentPosition.x) 
            + (fragmentPosition.y 
                * fragmentPosition.y)),
        1.0);

}
