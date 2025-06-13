#include <fstream>
#include <glad/glad.h>
#include <iostream>
#include <sstream>
#include <string>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

char const* const vertexShaderPath{ "assets/shaders/vertexShader.vert" };
char const* const fragmentShaderPath{ "assets/shaders/fragmentShader.frag" };

//* Sync viewport to window
void updateViewport(
    GLFWwindow* window,
    int width,
    int height
);

void processInput( GLFWwindow* window );

std::string readFile( std::string path );

int main()
{
    //* GLFW: Init and configure
    glfwInit();
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
    glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );

    //* GLFW: Create window
    GLFWwindow* window = glfwCreateWindow( 1280, 720, "GLFW OpenGL", NULL, NULL );

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

    //* Shader
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

    //* Data
    //* A triangle in normalized device coordinates
    // clang-format off
    GLfloat vertices[] = {
        //* x, y, r, g, b
        -.5f, -.5f,  1.0f, 0.0f, 0.0f, 
        0.5f, -.5f,  0.0f, 1.0f, 0.0f, 
        0.0f, 0.5f,  0.0f, 0.0f, 1.0f
    };
    // clang-format on

    //* VAO (vertex array object):
    //* - how to access VBO
    //* or
    //* - what is the structure of the VBO

    //* VBO (vertex buffer object): to manage used GPU memory (aka. buffer)
    //* - stores (generated) buffer object names
    //* - to send (large) batches of data
    GLuint VAO, VBO; // (unsigned int) reference ID

    //* Create buffer(s) (aka. data storage) on the GPU
    //* and store a reference to it (eg. in the VBO)
    glGenVertexArrays(
        1,
        &VAO
    );
    glGenBuffers(
        1, // amount of buffers
        &VBO
    );

    //* Bind VAO
    glBindVertexArray( VAO );

    //* Bind the VBO to the GL_ARRAY_BUFFER target (like a pointer)
    //* In other words: the GL_ARRAY_BUFFER now targets/points to the VBO
    glBindBuffer(
        GL_ARRAY_BUFFER,
        VBO
    );

    //* Copies user-defined data ('vertices' in this case)
    //* into currently bound buffer.
    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof( vertices ),
        vertices,
        GL_STATIC_DRAW
    );

    //* Link vertex attributes (vertices/input to vertex shader), so the must match the inputs in the vertex shader: "layout (location = X)"
    //* "When you read the input for the vertex shaders vertex attribute(s),
    //* interpret (periodically) every [stride] bits,
    //* starting from [index]
    //* as [type],
    //* which appears first at [pointer] within the data"
    glVertexAttribPointer(
        0, // "layout (location = 0)" in vertex shader
        2,
        GL_FLOAT,
        GL_FALSE,
        5 * sizeof( GLfloat ),
        (void*)0
    );
    glVertexAttribPointer(
        1,
        3,
        GL_FLOAT,
        GL_FALSE,
        5 * sizeof( GLfloat ),
        (void*)0
    );

    //* Enable the vertex attribute (aka. input data)
    glEnableVertexAttribArray( 0 );
    glEnableVertexAttribArray( 1 );

    //* Render loop
    while ( !glfwWindowShouldClose( window ) )
    {
        processInput( window );

        //* Set clearing color and clear/reset window
        glClearColor(
            0.0f,
            0.0f,
            0.0f,
            1.0f
        );
        glClear( GL_COLOR_BUFFER_BIT );

        //* Activate shader
        glUseProgram( shaderProgram );

        //* Bind VAO to use
        glBindVertexArray( VAO );

        //* Draw
        glDrawArrays(
            GL_TRIANGLES,
            0,
            3
        );

        //* GLFW: Swap main buffers and poll events
        glfwSwapBuffers( window );
        glfwPollEvents();
    }

    //* Close: free all resources
    glDeleteVertexArrays(
        1,
        &VAO
    );
    glDeleteBuffers(
        1,
        &VBO
    );
    glDeleteProgram( shaderProgram );
    glfwDestroyWindow( window );
    glfwTerminate();

    return 0;
}

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

