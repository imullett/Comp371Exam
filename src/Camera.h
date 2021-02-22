// Modified from Ben Cook's Udemy OpenGL course https://www.udemy.com/course/graphics-with-modern-opengl/
#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>


class Camera
{
public:
	/// <summary>
	/// Create a camera with initial parameters
	/// </summary>
	/// <param name="position">The position of the camera</param>
	/// <param name="up">Where the up direction is situated</param>
	/// <param name="yaw">Initial x-axis position</param>
	/// <param name="pitch">Initial y-axis position</param>
	/// <param name="movementSpeed">Speed of movement</param>
	/// <param name="turnSpeed">Speed of turning</param>
	Camera(glm::vec3 position, glm::vec3 up, GLfloat yaw, GLfloat pitch, GLfloat movementSpeed, GLfloat turnSpeed);
	
	/// <summary>
	/// Allows for WASD movement from keyboard
	/// </summary>
	void movementFromKeyboard(bool* keys); // WASD movement
	/// <summary>
	/// Allows for WASD movement from keyboard using delta time
	/// </summary>
	void movementFromKeyboard(bool* keys, GLfloat deltatime); // WASD movement using delta time
	/// <summary>
	/// Pans the camera right and left while holding down the right mouse button
	/// </summary>
	void pan(bool* keys,  GLfloat x);
	/// <summary>
	/// Tilts the camera up and down while holding down the middle mouse button
	/// </summary>
	void tilt(bool* keys, GLfloat y);
	/// <summary>
	/// Zooms camera in and out
	/// </summary>
	void magnify(bool* keys, GLfloat z);
	/// <summary>
	/// Calculates the view matrix
	/// </summary>
	/// <returns>A 4x4 matrix</returns>
	glm::mat4 calculateViewMatrix();
	/// <summary>
	/// Produces a view matrix based on given parameters
	/// </summary>
	/// <param name="eye">The initial position of the camera</param>
	/// <param name="target">Where the camera is supposed to be looking</param>
	/// <param name="up">Where the up direction is situated</param>
	/// <returns>A 4x4 matrix</returns>
	glm::mat4 calculateViewMatrix(glm::vec3 eye, glm::vec3 target, glm::vec3 up);
	
	/// <summary>
	/// Deconstructor
	/// </summary>
	~Camera();

private:
	/// <summary>
	/// Defines a 3D position
	/// </summary>
	glm::vec3 position;
	/// <summary>
	/// Defines where the front direction is situated in 3D space
	/// </summary>
	glm::vec3 front;
	/// <summary>
	/// Defines where the up direction is situated in 3D space
	/// </summary>
	glm::vec3 up;
	/// <summary>
	/// Defines where the right direction is situated in 3D space
	/// </summary>
	glm::vec3 right;
	/// <summary>
	/// Defines where the up direction is situated in 3D world space
	/// </summary>
	glm::vec3 worldUp;

	/// <summary>
	/// Defines the side-to-side movement of the camera
	/// </summary>
	GLfloat yaw;
	/// <summary>
	/// Defines the up-and-down movement of the camera
	/// </summary>
	GLfloat pitch;

	/// <summary>
	/// Defines the movement speed
	/// </summary>
	GLfloat movementSpeed;
	/// <summary>
	/// Defines the turn speed
	/// </summary>
	GLfloat turnSpeed;

	/// <summary>
	/// Updates all variables after a change occurs
	/// </summary>
	void update();
};
