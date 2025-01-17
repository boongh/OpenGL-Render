#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h> // include glad to get all the required OpenGL headers
#include <GLFW/glfw3.h>
#include <glm.hpp>

class Camera {
private:
	glm::vec3 cameraPos;
	glm::vec3 cameraFacing;
	glm::vec3 cameraUp;
	glm::vec3 view;
	glm::mat4 projection;

public:
	Camera(glm::vec3 pos, glm::vec3 facing, glm::vec3 up,
		float fov, float aspectRatio,
		float nearClip, float farClip);
	void SetCameraPosition(glm::vec3 pos);
	void MoveCamera(glm::vec3 pos, float time);

};

#endif