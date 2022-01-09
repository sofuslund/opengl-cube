#pragma once
#include <glm/glm.hpp>

enum class dir
{
	forward, 
	backward, 
	left, 
	right, 
	up, 
	down
};

class Camera
{
private:
	// Vectors needed
	glm::vec3 position;
	glm::vec3 viewDir;

	static const glm::vec3 UP;
	static const glm::vec3 defaultViewDir;

	int scrWidth, scrHeight;
public:
	float speed;

	Camera(int scrWidth, int scrHeight, float speed=0.005f);
	void move(dir direction);
	void updateMouse(float x, float y);
	glm::mat4 getViewMatrix();
};