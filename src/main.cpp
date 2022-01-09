#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "VertexBuffer.h";
#include "IndexBuffer.h";
#include "Camera.h";
#include "Shader.h";

int width = 800, height = 800;
GLFWwindow* window;

Camera camera(width, height);

bool wasdDown[6];
bool ctrlDown;

void mouseCallback(GLFWwindow* window, double x, double y)
{
    camera.updateMouse((float)x, (float)y);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS)
    {
        if (key == GLFW_KEY_W)
            wasdDown[0] = true;
        else if (key == GLFW_KEY_S)
            wasdDown[1] = true;
        else if (key == GLFW_KEY_A)
            wasdDown[2] = true;
        else if (key == GLFW_KEY_D)
            wasdDown[3] = true;
        else if (key == GLFW_KEY_SPACE)
            wasdDown[4] = true;
        else if (key == GLFW_KEY_LEFT_SHIFT)
            wasdDown[5] = true;
        else if (key == GLFW_KEY_LEFT_CONTROL)
            ctrlDown = true;
    }
    if (action == GLFW_RELEASE)
    {
        if (key == GLFW_KEY_W)
            wasdDown[0] = false;
        else if (key == GLFW_KEY_S)
            wasdDown[1] = false;
        else if (key == GLFW_KEY_A)
            wasdDown[2] = false;
        else if (key == GLFW_KEY_D)
            wasdDown[3] = false;
        else if (key == GLFW_KEY_SPACE)
            wasdDown[4] = false;
        else if (key == GLFW_KEY_LEFT_SHIFT)
            wasdDown[5] = false;
        else if (key == GLFW_KEY_LEFT_CONTROL)
            ctrlDown = false;
    }
}

void bufferResize(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

bool init()
{
    glfwInit();
    // Configure glfw
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create the window
    window = glfwCreateWindow(width, height, "First opengl program", NULL, NULL);

    // Chech if the window was created succesfully
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }
    // Make an opengl context
    glfwMakeContextCurrent(window);

    // Load the opengl function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return false;
    }

    glViewport(0, 0, width, height);

    // Setup a callback function for window resizing
    glfwSetFramebufferSizeCallback(window, bufferResize);
    // Setup a callback for keys getting pressed
    glfwSetKeyCallback(window, keyCallback);

    glfwSetCursorPosCallback(window, mouseCallback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glEnable(GL_DEPTH_TEST);

    return true;
}

int main()
{
    if (!init())
    {
        return -1;
    }

    Shader basic_shader("VertexShader.vert", "FragmentShader.frag");
    Shader lightsource_shader("LightSource.vert", "LightSource.frag");

    /*GLfloat vertices[] =
    {
        // Positions
        // ------------------|------------------
        // Front face
        -0.5f, -0.5f, 0.5f,
         0.5f, -0.5f, 0.5f,
        -0.5f,  0.5f, 0.5f,
         0.5f,  0.5f, 0.5f,

        // Back face
        -0.5f, -0.5f, -0.5,
         0.5f, -0.5f, -0.5,
        -0.5f,  0.5f, -0.5,
         0.5f,  0.5f, -0.5
    };

    GLuint indices[] =
    {
        0, 1, 2, 2, 1, 3,
        4, 5, 6, 6, 5, 7,
        0, 4, 2, 2, 4, 6,
        1, 5, 3, 3, 5, 7,
        0, 1, 4, 4, 1, 5,
        2, 3, 6, 6, 3, 7
    };*/

    GLfloat cubeVertices[] =
    {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };

    GLuint CubeVAO;
    glGenVertexArrays(1, &CubeVAO);
    glBindVertexArray(CubeVAO);
    
    VertexBuffer CubeBuffer(&cubeVertices, sizeof(cubeVertices), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)3);
    glEnableVertexAttribArray(0);

    glm::vec3 lightPos(2.f, 2.f, 0.f);
    glm::vec3 lightColor(1.f, 1.f, 1.f);
    glm::vec3 cubeColor(1.f, 0.f, 0.f);

    while (!glfwWindowShouldClose(window))
    {
        camera.speed = 0.002f;

        if (ctrlDown)
            camera.speed = 0.008;

        if (wasdDown[0])
            camera.move(dir::forward);
        if (wasdDown[1])
            camera.move(dir::backward);
        if (wasdDown[2])
            camera.move(dir::left);
        if (wasdDown[3])
            camera.move(dir::right);
        if (wasdDown[4])
            camera.move(dir::up);
        if (wasdDown[5])
            camera.move(dir::down);

        // Clear the window
        glClearColor(0.1f, 0.1f, 0.1f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Create transformation matrixes
        glm::mat4 model(1.f);
        glm::mat4 view = camera.getViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(45.f), (float)(width / height), 0.1f, 100.f);

        // -------------------------- Draw cube ---------------------------- //
        glBindVertexArray(CubeVAO);

        basic_shader.use();

        basic_shader.set("model", glm::value_ptr(model));
        basic_shader.set("view", glm::value_ptr(view));
        basic_shader.set("projection", glm::value_ptr(projection));
        basic_shader.set("lightPos", lightPos[0], lightPos[1], lightPos[2]);
        basic_shader.set("lightColor", lightColor[0], lightColor[1], lightColor[2]);
        basic_shader.set("objectColor", cubeColor[0], cubeColor[1], cubeColor[2]);

        glDrawArrays(GL_TRIANGLES, 0, 36);

        // -------------------------- Draw light source ---------------------------- //
        glBindVertexArray(CubeVAO);

        lightsource_shader.use();

        model = glm::translate(model, lightPos);
        glm::mat4 trans = projection * view * model;
        lightsource_shader.set("trans", glm::value_ptr(trans));
        lightsource_shader.set("lightColor", lightColor[0], lightColor[1], lightColor[2]);

        glDrawArrays(GL_TRIANGLES, 0, 36);
        
        // Swap the buffers i.e. update contents on screen
        glfwSwapBuffers(window);
        // Handle events that might have been triggered since last frame
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &CubeVAO);

    CubeBuffer.CleanUp();

    glfwTerminate();

    _CrtDumpMemoryLeaks();
    return 0;
}