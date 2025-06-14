#include <raylib.h>
#include <rlgl.h>

int const WINDOW_WIDTH{ 800 };
int const WINDOW_HEIGHT{ 940 };

char const* const vertexShaderPath{ "assets/shaders/vertexShader.vert" };
char const* const fragmentShaderPath{ "assets/shaders/fragmentShader.frag" };

int main()
{
    float vertices[] = {
        // clang-format off
        //* x, y, r, g, b
        -.5f, -.5f,  1.0f, 0.0f, 0.0f, 
        0.5f, -.5f,  0.0f, 1.0f, 0.0f, 
        0.0f, 0.5f,  0.0f, 0.0f, 1.0f
        // clang-format on
    };

    InitWindow(
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        "test"
    );

    //* Shader
    Shader rlShader = LoadShader(
        vertexShaderPath,
        fragmentShaderPath
    );

    //* VAO
    unsigned int vao = rlLoadVertexArray();
    rlEnableVertexArray( vao );

    //* VBO
    unsigned int vbo = rlLoadVertexBuffer(
        vertices,
        sizeof( vertices ),
        false
    );

    rlSetVertexAttribute(
        0,
        2,
        RL_FLOAT,
        false,
        5 * sizeof( float ),
        0
    );
    rlSetVertexAttribute(
        1,
        3,
        RL_FLOAT,
        false,
        5 * sizeof( float ),
        0
    );

    rlEnableVertexAttribute( 0 );
    rlEnableVertexAttribute( 1 );

    while ( !WindowShouldClose() )
    {
        BeginDrawing();
        ClearBackground( BLACK );

        rlEnableShader( rlShader.id );

        rlEnableVertexArray( vao );

        rlDrawVertexArray(
            0,
            3
        );

        rlDisableVertexArray();

        EndShaderMode();
        EndDrawing();
    }

    //* Close: free all resources
    rlUnloadVertexArray( vao );
    rlUnloadVertexBuffer( vbo );

    CloseWindow();
}
