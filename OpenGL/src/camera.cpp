#include <camera.h>
#include <shader.h>
#include <math.h>
#include <GLFW/glfw3.h>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

Camera::Camera(glm::vec3 pos, glm::vec3 lookAt, glm::vec3 up, Shader* shaderRefIn, bool viewLockIn,
	float fovIn, float nearClipIn, float farClipIn, float aspectRatioIn) {
	fov = fovIn;
	nearClip = nearClipIn;
	farClip = farClipIn;
	aspectRatio = aspectRatioIn;
	viewLock = viewLockIn;
	cameraPos = pos;
	cameraFacing = lookAt;
	cameraFront = glm::normalize(lookAt - pos);
	cameraUp = up;
	cameraRight = glm::normalize(glm::cross(cameraFacing, cameraUp));
	projection = glm::perspective(fov, aspectRatio, nearClip, farClip);
	view = glm::lookAt(pos, lookAt, up);
	shaderRef = shaderRefIn;
	shaderRef->SetMatrix("view", 1, GL_FALSE, view);
	shaderRef->SetMatrix("projection", 1, GL_FALSE, projection);
}

Camera::Camera() {

}

void Camera::UpdateAll(glm::vec3 pos, glm::vec3 facing, glm::vec3 up,
	float fov, float nearClip, float farClip, float aspectRatio) {
	projection = glm::perspective(fov, aspectRatio, nearClip, farClip);
	cameraPos = pos;
	cameraFacing = facing;
	cameraFront = glm::normalize(facing - pos);
	cameraUp = up;
	view = glm::lookAt(pos, facing, up);
	cameraRight = glm::normalize(glm::cross(cameraFront, cameraUp));
	cameraFront = glm::normalize(facing - pos);

	shaderRef->SetMatrix("view", 1, GL_FALSE, view);
	shaderRef->SetMatrix("projection", 1, GL_FALSE, projection);
}

void Camera::UpdateView(glm::vec3 pos, glm::vec3 facing, glm::vec3 up) {
	cameraPos = pos;
	cameraFacing = facing;
	cameraFront = glm::normalize(facing - pos);
	cameraUp = up;
	cameraRight = glm::normalize(glm::cross(cameraFront, cameraUp));
	view = glm::lookAt(pos, facing, up);
	shaderRef->SetMatrix("view", 1, GL_FALSE, view);
}


void Camera::UpdatePerspective(float fov, float nearClip, float farClip, float aspectRatio) {
	projection = glm::perspective(fov, aspectRatio, nearClip, farClip);
	shaderRef->SetMatrix("projection", 1, GL_FALSE, projection);

}

void Camera::SetCameraPosition(glm::vec3 pos) {
	cameraPos = pos;
	
	UpdateView(pos, cameraFacing, cameraUp);
}

void Camera::ZoomCamera(float factor) {
	fov -= factor * 0.1f;
	projection = glm::perspective(fov, aspectRatio, nearClip, farClip);
	shaderRef->SetMatrix("projection", 1, GL_FALSE, projection);
}

void Camera::EaseZoomCamera(float target) {
	float dif = target - fov;
	fov -= dif;
	projection = glm::perspective(fov, aspectRatio, nearClip, farClip);
	shaderRef->SetMatrix("projection", 1, GL_FALSE, projection);
}

void Camera::MoveCamera(glm::vec3 direction, float speed) {
	if (viewLock == false) {
		cameraPos = cameraPos + direction * speed;
		cameraFacing = cameraFacing + direction * speed;
	}
	else if (viewLock == true) {
		cameraPos = cameraPos + direction * speed;
	}

	view = glm::lookAt(cameraPos, cameraFacing, cameraUp);
	cameraFront = glm::normalize(cameraFacing - cameraPos);
	cameraRight = glm::normalize(glm::cross(cameraFront, cameraUp));

	shaderRef->SetMatrix("view", 1, GL_FALSE, view);
}

void Camera::TurnCamera(glm::vec3 front) {

	cameraFacing = cameraPos + front;
	cameraFront = glm::normalize(front);
	cameraRight = glm::normalize(glm::cross(cameraFront, cameraUp));
	
	view = glm::lookAt(cameraPos, cameraFacing, cameraUp);
	shaderRef->SetMatrix("view", 1, GL_FALSE, view);

}
