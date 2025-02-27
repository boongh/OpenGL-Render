#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h> // include glad to get all the required OpenGL headers
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <shader.h>
#include <math.h>	
#include <GLFW/glfw3.h>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>


class Camera {
private:

public:
	
	bool viewLock;

	glm::vec3 cameraPos;
	glm::vec3 cameraFacing;

	glm::vec3 cameraFront;
	glm::vec3 cameraUp;
	glm::vec3 cameraRight;

	float fov;
	float nearClip;
	float farClip;
	float aspectRatio;
	glm::mat4 view;
	glm::mat4 projection;

	Camera();
	Camera(glm::vec3 pos, glm::vec3 lookAt, glm::vec3 up, Shader* shaderRefIn, bool viewLockIn,
		float fov = 1.5708,
		float nearClip = 0.001, float farClip = 100000.0, float aspectRatio = 1.7778f);
	void UpdateAll(glm::vec3 pos, glm::vec3 facing, glm::vec3 up,
		float fov, float nearClip, float farClip, float aspectRatio);
	void UpdateView();
	void UpdatePerspective(float fov, float nearClip, float farClip, float aspectRatio);
	void UpdateMatrix();
	void SetCameraPosition(glm::vec3 pos);
	void MoveCamera(glm::vec3 direction, float speed);
	void TurnCamera(glm::vec3 front);
	void ZoomCamera(float factor);
	void EaseZoomCamera(float target);
};

#endif