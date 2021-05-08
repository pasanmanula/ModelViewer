#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/rotate_vector.hpp"
#include "glm/gtx/vector_angle.hpp"
#include "Shader.h"

class Camera
{
private:
	glm::vec3 Orientation = glm::vec3(0.0f,0.0f,-1.0f);
	glm::vec3 Up = glm::vec3(0.0f,1.0f,0.0f);
	glm::vec3 Position;
	int Width, Height;
	float speed = 0.1f;
	float sensitivity = 100.0f;
	bool firstClick = true;

public:
	Camera(glm::vec3 position, const int& width, const int& height)
		: Position(position), Width(width), Height(height)
	{}

	void Matrix(const float& FOVdeg, const float& nearPlane, const float& farPlane, const Shader& shader, const char* uniform);
	void Inputs(GLFWwindow* window);
};