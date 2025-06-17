//* DEFINE VERSION HERE
// #define VERSION_OPENGL
#define VERSION_RAYLIB

#if defined( VERSION_OPENGL )
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#endif

#if defined( VERSION_RAYLIB )
#include <raylib.h>
#include <rlgl.h>
#endif

int const WINDOW_WIDTH{ 800 };
int const WINDOW_HEIGHT{ 800 };

char const* const vertexShaderPath{ "assets/shaders/example.vert" };
char const* const fragmentShaderPath{ "assets/shaders/example.frag" };

//* Forward declares
#if defined( VERSION_OPENGL )
//* Sync viewport to window
void updateViewport( GLFWwindow* window, int width, int height );
void processInput( GLFWwindow* window );
std::string readFile( std::string path );
#endif

int main()
{
//* Initialize window and OpenGL context
#if defined( VERSION_OPENGL )
    //* GLFW: Init and configure
    glfwInit();
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
    glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );

    //* Draw triangle as points
    // glEnable( GL_PROGRAM_POINT_SIZE );

    //* GLFW: Create window
    GLFWwindow* window = glfwCreateWindow( WINDOW_WIDTH, WINDOW_HEIGHT, "GLFW OpenGL", NULL, NULL );

    if ( !window )
    {
        std::cerr << "[ERROR] Window creation failed!\n";
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent( window );

    //* Callbacks
    glfwSetFramebufferSizeCallback(
        window,
        updateViewport
    );

    //* GLAD: Load OpenGL function pointers
    if ( !gladLoadGLLoader( (GLADloadproc)glfwGetProcAddress ) )
    {
        std::cerr << "[ERROR] GLAD initialization failed!\n";
        return 1;
    }
#endif
#if defined( VERSION_RAYLIB )
    InitWindow(
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        "raylib window"
    );

    //* Draw triangle as points
    // rlEnablePointMode();
#endif

//* ShaderProgram (Load source, compile source, link program, compile program)
#if defined( VERSION_OPENGL )
    GLuint vertexShader = glCreateShader( GL_VERTEX_SHADER );
    GLuint fragmentShader = glCreateShader( GL_FRAGMENT_SHADER );

    //* Load shader source code
    std::string vertexShaderSource{ readFile( vertexShaderPath ) };
    std::string fragmentShaderSource{ readFile( fragmentShaderPath ) };

    char const* vertexShaderCode{ vertexShaderSource.c_str() };
    char const* fragmentShaderCode{ fragmentShaderSource.c_str() };

    glShaderSource(
        vertexShader,
        1,
        &vertexShaderCode,
        NULL
    );
    glShaderSource(
        fragmentShader,
        1,
        &fragmentShaderCode,
        NULL
    );

    //* Compile shader
    glCompileShader( vertexShader );
    glCompileShader( fragmentShader );

    //* Error handling for shader compilation
    int success;
    char infoLog[512];

    glGetShaderiv( vertexShader, GL_COMPILE_STATUS, &success );
    if ( !success )
    {
        glGetShaderInfoLog( vertexShader, 512, NULL, infoLog );
        std::cerr << "[ERROR] Vertex shader comilation failed\n"
                  << infoLog << std::endl;
    }

    glGetShaderiv( fragmentShader, GL_COMPILE_STATUS, &success );
    if ( !success )
    {
        glGetShaderInfoLog( fragmentShader, 512, NULL, infoLog );
        std::cerr << "[ERROR] Fragment shader comilation failed\n"
                  << infoLog << std::endl;
    }

    //* Shader program
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(
        shaderProgram,
        vertexShader
    );
    glAttachShader(
        shaderProgram,
        fragmentShader
    );

    glLinkProgram( shaderProgram );

    //* Error handling
    glGetProgramiv( shaderProgram, GL_LINK_STATUS, &success );
    if ( !success )
    {
        glGetProgramInfoLog( shaderProgram, 512, NULL, infoLog );
        std::cerr << "[ERROR] Shader program comilation failed\n"
                  << infoLog << std::endl;
    }

    //* Delete shaders after linking
    glDeleteShader( vertexShader );
    glDeleteShader( fragmentShader );
#endif
#if defined( VERSION_RAYLIB )
    Shader pixelShader = LoadShader(
        vertexShaderPath,
        fragmentShaderPath
    );
#endif

    //* Data
    //* A triangle in normalized device coordinates
    // clang-format off
#if defined( VERSION_OPENGL )
    GLfloat vertices[] 
#endif
#if defined( VERSION_RAYLIB )
    float vertices[] 
#endif
    = {
        // px, py, r, g, b
        -0.5f, -0.5f,  +1.0f, +0.0f, +0.0f,
        +0.5f, -0.5f,  +0.0f, +1.0f, +0.0f,
        +0.0f, +0.5f,  +0.0f, +0.0f, +1.0f
    };
    // clang-format on

    //* VAO (vertex array object):
    //* - how to access VBO
    //* or
    //* - what is the structure of the VBO
#if defined( VERSION_OPENGL )
    GLuint vao; // (unsigned int) reference ID

    //* Create buffer(s) (aka. data storage) on the GPU
    //* and store a reference to it
    glGenVertexArrays(
        1,
        &vao
    );
#endif
#if defined( VERSION_RAYLIB )
    unsigned int vao = rlLoadVertexArray();
#endif

    //* Bind VAO
    //* Any subsequent vertex attribute calls from that point on will be stored inside the VAO
    //* A vertex array object stores the following:
    //* - Calls to `glEnableVertexAttribArray` or `glDisableVertexAttribArray`.
    //* - Vertex attribute configurations via `glVertexAttribPointer`.
    //* - Vertex buffer objects associated with vertex attributes by calls to `glVertexAttribPointer`.
#if defined( VERSION_OPENGL )
    glBindVertexArray( vao );
#endif
#if defined( VERSION_RAYLIB )
    rlEnableVertexArray( vao );
#endif

    //* VBO (vertex buffer object): to manage used GPU memory (aka. buffer)
    //* - stores (generated) buffer object names
    //* - to send (large) batches of data
    //* Gen, Bind and Buffer
#if defined( VERSION_OPENGL )
    GLuint vbo; // (unsigned int) reference ID

    //* Create buffer(s) (aka. data storage) on the GPU
    //* and store a reference to it
    glGenBuffers(
        1, // amount of buffers
        &vbo
    );

    //* Bind the VBO to the GL_ARRAY_BUFFER target (like a pointer)
    //* In other words: the GL_ARRAY_BUFFER now targets/points to the VBO
    glBindBuffer(
        GL_ARRAY_BUFFER,
        vbo
    );

    //* Copies user-defined data ('vertices' in this case)
    //* into currently bound buffer.
    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof( vertices ),
        vertices,
        GL_DYNAMIC_DRAW
    );

#endif
#if defined( VERSION_RAYLIB )
    unsigned int vbo = rlLoadVertexBuffer(
        vertices,
        sizeof( vertices ),
        true
    );

#endif

    //* Bind VAO before here, needed for following functions!

    //* Link vertex attributes (vertices/input to vertex shader): they must match the inputs in the vertex shader ["layout (location = X)"]
    //* "When you read the input for the vertex shaders vertex attribute(s),
    //* interpret (periodically) every [stride] bits,
    //* starting from [index]
    //* as [type],
    //* which appears first at [pointer] within the data"
    //* This is stored in the currently bound VAO (if bound)
#if defined( VERSION_OPENGL )
    //* Position
    glVertexAttribPointer(
        0, // "layout (location = 0)" in vertex shader
        2,
        GL_FLOAT,
        GL_FALSE,
        5 * sizeof( GLfloat ),
        (void*)( 0 * sizeof( float ) )
    );

    //* Color
    glVertexAttribPointer(
        1,
        3,
        GL_FLOAT,
        GL_FALSE,
        5 * sizeof( GLfloat ),
        (void*)( 2 * sizeof( float ) )
    );

    //* Enable the vertex attribute (aka. input data)
    //* This is also stored in the currently bound VAO (if bound)
    glEnableVertexAttribArray( 0 );
    glEnableVertexAttribArray( 1 );
#endif
#if defined( VERSION_RAYLIB )
    //* Position
    rlSetVertexAttribute(
        0,
        2,
        RL_FLOAT,
        false,
        5 * sizeof( float ),
        0 * sizeof( float )
    );

    //* Color
    rlSetVertexAttribute(
        1,
        3,
        RL_FLOAT,
        false,
        5 * sizeof( float ),
        2 * sizeof( float )
    );

    rlEnableVertexAttribute( 0 );
    rlEnableVertexAttribute( 1 );
#endif

    //* Render loop
    while (
#if defined( VERSION_OPENGL )
        !glfwWindowShouldClose( window )
#endif
#if defined( VERSION_RAYLIB )
            !WindowShouldClose()
#endif
    )
    {
#if defined( VERSION_OPENGL )
        //* Set clearing color and clear/reset window
        glClearColor(
            0.0f,
            0.0f,
            0.0f,
            1.0f
        );
        glClear( GL_COLOR_BUFFER_BIT );
#endif
#if defined( VERSION_RAYLIB )
        BeginDrawing(); // Seems to only update time?
        ClearBackground( BLACK );
#endif

        //* - Activate shader
        //* - Bind VAO to use
        //* - Draw
#if defined( VERSION_OPENGL )
        glUseProgram( shaderProgram );

        glBindVertexArray( vao );

        glDrawArrays(
            // GL_TRIANGLES,
            GL_POINTS,
            0,
            3
        );
#endif
#if defined( VERSION_RAYLIB )
        rlEnableShader( pixelShader.id );

        rlEnableVertexArray( vao );

        rlDrawVertexArray(
            0,
            3
        );
#endif

//* GLFW: Swap main buffers and poll events
#if defined( VERSION_OPENGL )
        glBindVertexArray( 0 );

        glfwSwapBuffers( window );
        processInput( window );
        glfwPollEvents();
#endif
#if defined( VERSION_RAYLIB )
        rlDisableVertexArray();

        EndDrawing();
#endif
    }

    //* Close: free all resources
#if defined( VERSION_OPENGL )
    glDeleteVertexArrays(
        1,
        &vao
    );
    glDeleteBuffers(
        1,
        &vbo
    );
    glDeleteProgram( shaderProgram );
    glfwDestroyWindow( window );
    glfwTerminate();
#endif
#if defined( VERSION_RAYLIB )
    rlUnloadVertexArray( vao );
    rlUnloadVertexBuffer( vbo );
    UnloadShader( pixelShader );

    CloseWindow();
#endif

    return 0;
}

#if defined( VERSION_OPENGL )
void updateViewport(
    [[maybe_unused]] GLFWwindow* window,
    int width,
    int height
)
{
    glViewport(
        0,     // left
        0,     // bottom
        width, // right
        height // top
    );
}

void processInput( GLFWwindow* window )
{
    if ( glfwGetKey(
             window,
             GLFW_KEY_ESCAPE
         )
         == GLFW_PRESS )
    {
        glfwSetWindowShouldClose(
            window,
            true
        );
    }
}

std::string readFile( std::string path )
{
    std::string content{};
    std::ifstream inputFileStream( path );

    std::ostringstream outStringStream;

    if ( !inputFileStream.is_open() )
    {
        std::cerr << "[ERROR] Failed to open file " << path << "\n";

        return content;
    }

    outStringStream << inputFileStream.rdbuf();
    inputFileStream.close();

    content = outStringStream.str();

    return content;
}
#endif
