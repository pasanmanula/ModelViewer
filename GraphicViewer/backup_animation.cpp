#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Shader.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Texture.h"
#include "stb_image/stb_image.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

const int width = 800;
const int height = 800;

int main()
{
	// Initialize GLFW
	glfwInit();
	// Tell GLFW what version of OpenGL we are using. Here we use 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using CORE profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// Create a GLFWWindow object of 800x800 pixels
	GLFWwindow* window = glfwCreateWindow(width, height, "Graphic Viewer", NULL, NULL);
	if (window == NULL)
	{
		glfwTerminate();
		return -1;
	}
	// Introduce the window to the current context
	glfwMakeContextCurrent(window);
	// Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewpoint of OpenGL in the Window. 
	glViewport(0, 0, width, height);
	// Specify the color of the background
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	// Clean the back buffer and assign the new color to it
	glClear(GL_COLOR_BUFFER_BIT);
	// Swap the back buffer with the front buffer
	glfwSwapBuffers(window);

	// Vertices coordinates
	float vertices[] =
	{ //     COORDINATES     /        COLORS      /   TexCoord  //
		-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
		-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
		 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
		 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
		 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	2.5f, 5.0f
	};

	// Indices for vertices order
	unsigned int indices[] =
	{
		0, 1, 2,
		0, 2, 3,
		0, 1, 4,
		1, 2, 4,
		2, 3, 4,
		3, 0, 4
	};

	// Pipeline Starts Here (Shaders)
	Shader shader("resources/shaders/Basic.shader");
	shader.Bind();
	// Vertex Buffer
	VertexBuffer vb(vertices, sizeof(vertices));
	// Vertex Array Object
	VertexArray vao;
	//Index Buffer 
	IndexBuffer ib(indices, sizeof(indices));

	// Unbinding everything
	glBindVertexArray(0);
	shader.Unbind();
	vb.Unbind();
	ib.Unbind();
	vao.Unbind();

	// Adding textures
	Texture texture("resources/textures/brick.png");

	Rotation timer
	float rotation = 0.0f;
	double prevTime = glfwGetTime();
	double crntTime = prevTime;

	glfwSwapInterval(1); //Sync with monitors refresh rate
	glEnable(GL_DEPTH_TEST);


	glm::mat4 model;
	glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -0.5f, -2.0f));
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)(width / height), 0.1f, 100.0f);

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			crntTime = glfwGetTime();
			if (crntTime - prevTime >= 1 / 60)
			{
				rotation += 0.5f;
				prevTime = crntTime;
			}

			model = glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));


		shader.Bind();

		camera.Matrix(45.0f, 0.1f, 100.0f, shader, "camMatrix");

		shader.setUniform4m("model",model);
		shader.setUniform4m("view",view);
		shader.setUniform4m("projection",projection);

		// Setting up uniforms
		shader.setUniform1f("scale", 0.5f);
		shader.setUniform1i("tex0", 0);
		texture.Bind();
		vao.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0); // DrawCall

		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();

	}


	// Delete the window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
}


// https://www.youtube.com/watch?v=45MIykWJ-C4&list=WL&index=35 1:04:07