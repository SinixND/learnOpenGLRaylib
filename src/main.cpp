#include <glad/glad.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

//* Setup
//* =======
static void quit(
    GLFWwindow* window,
    int key,
    [[maybe_unused]] int scancode,
    int action,
    [[maybe_unused]] int mods
)
{
    if ( key == GLFW_KEY_ESCAPE && action == GLFW_PRESS )
    {
        glfwSetWindowShouldClose( window, GLFW_TRUE );
    }
}
//* =======

//* A triangle in normalized device coordinates
float vertices[] = {
    -.5f, // x
    0.5f, // y
    0.0f, // z, once vertex
    0.5f,
    -.5f,
    0.0f,
    0.0f,
    0.5f,
    0.0f
};

int main()
{
    //* Setup
    //* =======
    glfwInit();

    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
    glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
    GLFWwindow* window = glfwCreateWindow( 1280, 720, "GLFW OpenGL", NULL, NULL );
    glfwMakeContextCurrent( window );
    gladLoadGLLoader( (GLADloadproc)glfwGetProcAddress );

    glfwSetKeyCallback( window, quit );
    while ( !glfwWindowShouldClose( window ) )
    {
        glfwPollEvents();

        glClearColor( 0.3, 0.3, 0.3, 1.0 );
        glClear( GL_COLOR_BUFFER_BIT );
        glfwSwapBuffers( window );

        //* VBO (vertex buffer object): to manage used GPU memory (aka. buffer)
        //* - stores (generated) buffer object names
        //* - to send (large) batches of data

        unsigned int VBO; // VBO ID

        //* Create buffer(s) (aka. data storage) on the GPU
        //* and store a reference to it in the VBO
        glGenBuffers(
            1, // amount of buffers
            &VBO
        );

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
    }

    glfwDestroyWindow( window );
    glfwTerminate();

    return 0;
}
