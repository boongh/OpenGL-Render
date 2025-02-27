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
void ScrollCallback(GLFWwindow* window, double xpos, double ypos);

float ambientStrength = 0.1f;

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
    glfwSetScrollCallback(window, ScrollCallback);


    //Shader shader =  Shader("./shader/NormalShader/vertex.vs", "./shader/NormalShader/fragment.fs");

	Shader shader = Shader("./shader/NormalShader/vertex.vs", "./shader/NormalShader/fragment.fs");
    shader.Use();

    Shader lightShader = Shader("./shader/LightingShader/lightvertex.vert", "./shader/LightingShader/lightfragment.frag");
	Shader lightSourceShader = Shader("./shader/LightSourceShader/lightsourcevertex.vert", "./shader/LightSourceShader/lightsourcefragment.frag");


    lightShader.Use();

    lightShader.SetVec("lightColor", 1, glm::vec3(1.0f, 1.0f, 1.0f));
    lightShader.SetVec("objectColor", 1, glm::vec3(1.0f, 1.0f, 0.0f));
	lightShader.SetFloat("ambientStrength", ambientStrength);


    lightSourceShader.Use();

    lightSourceShader.SetVec("lightColor", 1, glm::vec3(1.0f, 1.0f, 1.0f));

    camera = Camera(cameraPos, cameraPos + cameraFront, cameraUp, &lightShader, false, 45);

#pragma region Opaque objects

    float threeDVertices[] = {
    //Position(xyz) Texture coordinate(xyz)
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


    //Create a vertex array object
    unsigned int opaqueVAO, opaqueVBO;
    glGenVertexArrays(1, &opaqueVAO);
    glGenBuffers(1, &opaqueVBO);

    //assigned VBO as a buffer of GL_ARRAY_BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, opaqueVBO);
    //Copy data from VBO to the GPU as static
    glBufferData(GL_ARRAY_BUFFER, sizeof(threeDVertices), threeDVertices, GL_STATIC_DRAW);

    glBindVertexArray(opaqueVAO);

    //How the program should interpret the vertex data / buffer data
    //https://learnopengl.com/Getting-started/Hello-Triangle#:~:text=The%20function%20glVertexAttribPointer,detail%20later%20on
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //texture coord
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

#pragma endregion


#pragma region Light objects

    float lightCubeVertices[]{
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f
    };

    glm::vec3 lightCubePosition[] = {
        glm::vec3(2.0f,  2.0f,  0.0f),
    };


    // Light Objects VAO Setup
    unsigned int lightVAO, lightVBO;
    glGenVertexArrays(1, &lightVAO);
    glGenBuffers(1, &lightVBO);

    // Create a VBO for the light object data
    glBindVertexArray(lightVAO);
    glBindBuffer(GL_ARRAY_BUFFER, lightVBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(threeDVertices), threeDVertices, GL_STATIC_DRAW);


    //How the program should interpret the vertex data / buffer data
    //https://learnopengl.com/Getting-started/Hello-Triangle#:~:text=The%20function%20glVertexAttribPointer,detail%20later%20on
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //texture coord
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // At this point, both VAOs are set up independently with separate buffers.

#pragma endregion


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
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        time = (float)glfwGetTime();
        deltaTime = time - lastTime;
        lastTime = time;

        glm::vec3 origin = glm::vec3(0, 0, 0);
            
        glfwGetCursorPos(window, &mouseX, &mouseY);
        glfwGetFramebufferSize(window, &widthFrame, &heightFrame);

        lightShader.SetInt("ourTexture", 0);
        lightShader.SetInt("smileytexture", 1);
        //lightShader.SetFloat("u_time", time);
        lightShader.SetFloat("cursorPos", (float)mouseX, (float)mouseY);
        lightShader.SetFloat("u_resolution", (float)widthFrame, (float)heightFrame);

		glBindVertexArray(opaqueVAO);

		lightShader.Use();
        camera.UpdateMatrix();

        for (int i = 0; i < sizeof(cubePositions) / sizeof(cubePositions[i]); i++) {
            float cacheRotation = cubeRotation[i];
            cacheRotation += deltaTime * std::pow(glm::length(cubePositions[i] - camera.cameraPos), 2);

			if (cacheRotation > 360) {
				cacheRotation = 0;
			}
            else if (cacheRotation < 0) {
				cacheRotation = 360;
            }

			cubeRotation[i] = cacheRotation;
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            model = glm::rotate(model, glm::radians(cubeRotation[i]), glm::vec3(1.0, 1.0, 0.0));
            lightShader.SetMatrix("model", 1, GL_FALSE, model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        //std::cout << mouseX << " " << mouseY << " " << widthFrame << " " << heightFrame <<  std::endl;
        
		glBindVertexArray(lightVAO);

		lightSourceShader.Use();
        for (int i = 0; i < sizeof(lightCubePosition) / sizeof(lightCubePosition[i]); i++) {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, lightCubePosition[i]);
            lightSourceShader.SetMatrix("model", 1, GL_FALSE, model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        glfwSwapBuffers(window);
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    glDeleteBuffers(1, &opaqueVBO);
    glDeleteVertexArrays(1, &opaqueVAO);
	glDeleteVertexArrays(1, &lightVAO);

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

void ScrollCallback(GLFWwindow* window, double xpos, double ypos) {
    camera.ZoomCamera(ypos);
}

#pragma endregion
