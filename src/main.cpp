#include <glad/glad.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

//* Sync viewport to window
void updateViewport(
    GLFWwindow* window,
    int width,
    int height
);

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
        return -1;
    }

    glfwMakeContextCurrent( window );

    //* GLAD: Load OpenGL function pointers
    if ( !gladLoadGLLoader( (GLADloadproc)glfwGetProcAddress ) )
    {
        std::cerr << "[ERROR] GLAD initialization failed!\n";
        return -1;
    }

    //* Callbacks
    glfwSetFramebufferSizeCallback(
        window,
        updateViewport
    );

    //* Render loop
    while ( !glfwWindowShouldClose( window ) )
    {
        //* Set clearing color and clear/reset window
        glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
        glClear( GL_COLOR_BUFFER_BIT );

        //* GLFW: Swap main buffers and poll events
        glfwSwapBuffers( window );
        glfwPollEvents();
    }

    //* Close: free all resources
    glfwDestroyWindow( window );
    glfwTerminate();

    return 0;
}

void updateViewport(
    GLFWwindow* window,
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

// //* A triangle in normalized device coordinates
// float vertices[] = {
//     -.5f, // x
//     0.5f, // y
//     0.0f, // z, once vertex
//     0.5f,
//     -.5f,
//     0.0f,
//     0.0f,
//     0.5f,
//     0.0f
// };
//
// //* VBO (vertex buffer object): to manage used GPU memory (aka. buffer)
// //* - stores (generated) buffer object names
// //* - to send (large) batches of data
//
// unsigned int VBO; // VBO ID
//
// //* Create buffer(s) (aka. data storage) on the GPU
// //* and store a reference to it in the VBO
// glGenBuffers(
//     1, // amount of buffers
//     &VBO
// );
//
// //* Bind the VBO to the GL_ARRAY_BUFFER target (like a pointer)
// //* In other words: the GL_ARRAY_BUFFER now targets/points to the VBO
// glBindBuffer(
//     GL_ARRAY_BUFFER,
//     VBO
// );
//
// //* Copies user-defined data ('vertices' in this case)
// //* into currently bound buffer.
// glBufferData(
//     GL_ARRAY_BUFFER,
//     sizeof( vertices ),
//     vertices,
//     GL_STATIC_DRAW
// );
