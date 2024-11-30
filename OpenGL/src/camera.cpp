#include <camera.h>
#include <math.h>
#include <GLFW/glfw3.h>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
Camera::Camera(glm::vec3 pos, glm::vec3 facing, glm::vec3 up,
	float fov, float nearClip, float farClip, float aspectRatio) {
	this->cameraPos = pos;
	this->cameraFacing = facing;
	this->cameraUp = up;
	this->projection = glm::perspective(fov, aspectRatio, nearClip, farClip);
	this->view = glm::lookAt(pos, facing, up);

}