#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

const glm::vec3 Camera::UP = glm::vec3(0.f, 1.f, 0.f);
const glm::vec3 Camera::defaultViewDir(0.f, 0.f, -1.f);

Camera::Camera(int scrWidth, int scrHeight, float speed) : 
	position(0.f, 0.f, 5.0f), viewDir(defaultViewDir), 
	scrWidth(scrWidth), scrHeight(scrHeight), 
	speed(speed)
{
	
}

void Camera::move(dir direction)
{
	glm::mat4 trans(1.0);
	trans = glm::rotate(trans, glm::radians(-90.f), glm::vec3(0.f, 1.f, 0.f));

	// The camera's right
	glm::vec3 cameraRight = trans * glm::vec4(viewDir, 1.f);

	switch (direction)
	{
	case dir::forward:
		position += viewDir * speed;
		break;
	case dir::backward:
		position -= viewDir * speed;
		break;
	case dir::left:
		position -= cameraRight * speed;
		break;
	case dir::right:
		position += cameraRight * speed;
		break;
	case dir::down:
		position -= UP * speed;
		break;
	case dir::up:
		position += UP * speed;
		break;
	}
}

void Camera::updateMouse(float x, float y)
{
	float mappedX = -(45.f/scrWidth * x - 45.f/2);
	float mappedY = -(45.f/2/scrHeight * y - 45.f/4);
	
	glm::mat4 trans(1.0);
	trans = glm::rotate(trans, glm::radians(mappedX), glm::vec3(0.f, 1.f, 0.f));
	trans = glm::rotate(trans, glm::radians(mappedY), glm::vec3(1.f, 0.f, 0.f));

	viewDir = trans * glm::vec4(defaultViewDir, 1.f);
}

glm::mat4 Camera::getViewMatrix()
{
	return glm::lookAt(position, position + viewDir, UP);
}