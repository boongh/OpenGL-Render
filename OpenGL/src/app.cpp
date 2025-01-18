#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <shader.h>
#include <camera.h>
#include <math.h>
#include <stb_image.h>
#include <textureload.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>


#pragma region Initialization values and function declaration

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window, Camera* camera, float deltaSPD);
void MouseMoveCallback(GLFWwindow* window, double xpos, double ypos);
void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
void foo(GLFWwindow* window, double xpos, double ypos);

float xposBuffer = 480;
float yposBuffer = 270;

float height = 960;
float width = 540;

bool firstMouse = true;
bool mouseEnabled = false;

float yawAngle;
float pitchAngle;

//vertices stuff magic
float vertices[] = {
    // positions          // colors           // texture coords
     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   2.0f, 2.0f,   // top right
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   2.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 2.0f    // top left 
};

float threeDVertices[] = {
-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

glm::vec3 cubePositions[] = {
    glm::vec3(0.0f,  0.0f,  0.0f),
    glm::vec3(2.0f,  5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3(2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f,  3.0f, -7.5f),
    glm::vec3(1.3f, -2.0f, -2.5f),
    glm::vec3(1.5f,  2.0f, -2.5f),
    glm::vec3(1.5f,  0.2f, -1.5f),
    glm::vec3(-1.3f,  1.0f, -1.5f)
};

float cubeRotation[10] = { 0.0f };

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

Camera camera;

#pragma endregion

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif // __APPLE__ Compatability


    GLFWwindow* window = glfwCreateWindow(height, width, "Test", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, MouseMoveCallback);
    glfwSetMouseButtonCallback(window, MouseButtonCallback);

    Shader shader =  Shader("./shader/vertex.vs", "./shader/fragment.fs");
    shader.use();

    camera = Camera(cameraPos, cameraPos + cameraFront, cameraUp, &shader, false);

    //Create a vertex array object
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    //assigned VBO as a buffer of GL_ARRAY_BUFFER
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //Copy data from VBO to the GPU as static
    glBufferData(GL_ARRAY_BUFFER, sizeof(threeDVertices), threeDVertices, GL_STATIC_DRAW);


    //How the program should interpret the vertex data
    //https://learnopengl.com/Getting-started/Hello-Triangle#:~:text=The%20function%20glVertexAttribPointer,detail%20later%20on
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //texture coord
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //Create element buffer object
    /*
    unsigned int edges[] = {
        0, 2, 1,
        0, 2, 3
    };
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(edges), edges, GL_STATIC_DRAW);
    */

    Texture texture("./Texture/container.jpg", GL_TEXTURE_2D, GL_LINEAR_MIPMAP_NEAREST, GL_NEAREST, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE, 0);

    Texture smileyface("./Texture/awesomeface.png", GL_TEXTURE_2D, GL_LINEAR_MIPMAP_NEAREST, GL_NEAREST, GL_REPEAT, GL_REPEAT, 1);
    

    float time = 0;
    int widthFrame, heightFrame = 0;
    double mouseX, mouseY = 0;

    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;

    
        //Rotation
    #pragma region Camera Rotation
        yawAngle = -90.0f;
        pitchAngle = 0;


    #pragma endregion

    float lastTime = 0.0;
    float deltaTime = 0.0;

    glEnable(GL_DEPTH_TEST);



    while (!glfwWindowShouldClose(window))
    {
        /*
        if (timeLocation == -1 || winSize == -1 || cursorPos == -1) {
            std::cerr << "Error: One or more uniforms not found!" << std::endl;
        }
        */

        //Process input
        processInput(window, &camera, deltaTime * 10);

        //Render Stage
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        time = (float)glfwGetTime();
        deltaTime = time - lastTime;
        lastTime = time;

        glm::vec3 origin = glm::vec3(0, 0, 0);
            
        glfwGetCursorPos(window, &mouseX, &mouseY);
        glfwGetFramebufferSize(window, &widthFrame, &heightFrame);
        camera.UpdatePerspective(glm::radians(45.0), 0.01, 100.0, (float)widthFrame/heightFrame);


        shader.SetInt("ourTexture", 0);
        shader.SetInt("smileytexture", 1);
        shader.SetFloat("u_time", time);
        shader.SetFloat("cursorPos", (float)mouseX, (float)mouseY);
        shader.SetFloat("u_resolution", (float)widthFrame, (float)heightFrame);
        for (int i = 0; i < sizeof(cubePositions) / sizeof(cubePositions[i]); i++) {
            cubeRotation[i] += deltaTime * std::pow(glm::length(cubePositions[i] - camera.cameraPos), 2);
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            model = glm::rotate(model, glm::radians(cubeRotation[i]), glm::vec3(1.0, 1.0, 0.0));
            shader.SetMatrix("model", 1, GL_FALSE, model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        //std::cout << mouseX << " " << mouseY << " " << widthFrame << " " << heightFrame <<  std::endl;

        //activate the shader program

        glfwSwapBuffers(window);
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

#pragma region Movement Related Functions

void processInput(GLFWwindow* window, Camera* camera, float deltaSPD) {
    float cameraSPD = deltaSPD;
    glm::vec3 offsetFront = camera->cameraFront * cameraSPD;
    glm::vec3 offsetRight = camera->cameraRight * cameraSPD;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera->MoveCamera(camera->cameraFront, cameraSPD);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera->MoveCamera(-camera->cameraFront, cameraSPD);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera->MoveCamera(camera->cameraRight, cameraSPD);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera->MoveCamera(-camera->cameraRight, cameraSPD);
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        camera->MoveCamera(camera->cameraUp, cameraSPD);
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
        camera->MoveCamera(-camera->cameraUp, cameraSPD);
    }


    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}


void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods){
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        mouseEnabled = true;
    }
    else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        mouseEnabled = false;
        firstMouse = true;
    }

}
void MouseMoveCallback(GLFWwindow* window, double xpos, double ypos) {

    if (mouseEnabled) {
        if (firstMouse) {
            xposBuffer = xpos;
            yposBuffer = ypos;
            firstMouse = false;
        }
        float sensitivity = 0.1f;
        float deltaX = xpos - xposBuffer;
        float deltaY = ypos - yposBuffer;

        xposBuffer = xpos;
        yposBuffer = ypos;

        deltaX *= sensitivity;
        deltaY *= sensitivity;


        if (pitchAngle > 89.0f)
            pitchAngle = 89.0f;
        if (pitchAngle < -89.0f)
            pitchAngle = -89.0f;

        if (yawAngle < -180) {
            yawAngle += 360;
        }
        else if (yawAngle > 180) {
            yawAngle -= 360;
        }

        yawAngle += deltaX;
        pitchAngle += deltaY;

        glm::vec3 direction;
        direction.x = cos(glm::radians(yawAngle)) * cos(glm::radians(pitchAngle)); // Note that we convert the angle to radians first
        direction.y = -sin(glm::radians(pitchAngle));
        direction.z = sin(glm::radians(yawAngle)) * cos(glm::radians(pitchAngle));

        direction = glm::normalize(direction);

        camera.TurnCamera(direction);
    
    }
}

#pragma endregion
