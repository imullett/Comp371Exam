// Modified from Ben Cook's Udemy OpenGL course https://www.udemy.com/course/graphics-with-modern-opengl/
#include "Camera.h"


Camera::Camera(glm::vec3 position, glm::vec3 up, GLfloat yaw, GLfloat pitch, GLfloat movementSpeed, GLfloat turnSpeed){

	this->position = position;
	this->worldUp = up;
	this->yaw = yaw;
	this->pitch = pitch;
	this->movementSpeed = movementSpeed;
	this->turnSpeed = turnSpeed;
	front = glm::vec3(0.0f, 0.0f, -1.0f);

	update();

}

void Camera::update() {

	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	front = glm::normalize(front); // Get it back into 0 to 1

	right = glm::normalize(glm::cross(front, worldUp)); // Find the right vector by getting cross product between front and up
	up = glm::normalize(glm::cross(right, front)); // Find the up vector by getting cross product between right and front

}

void Camera::movementFromKeyboard(bool* keys) { // Configure IJKL key movement

	if (keys[GLFW_KEY_I] && keys[GLFW_KEY_LEFT_SHIFT]) {
		position += front * movementSpeed; // Go forward
	}

	if (keys[GLFW_KEY_J] && keys[GLFW_KEY_LEFT_SHIFT]) {
		position -= right * movementSpeed; // Go left
	}

	if (keys[GLFW_KEY_K] && keys[GLFW_KEY_LEFT_SHIFT]) {
		position -= front * movementSpeed; // Go backwards
	}

	if (keys[GLFW_KEY_L] && keys[GLFW_KEY_LEFT_SHIFT]) {
		position += right * movementSpeed; // Go right
	}

}

void Camera::movementFromKeyboard(bool* keys, GLfloat deltatime) { // Configure IJKL key movement

	GLfloat velocity = movementSpeed * deltatime;

	if (keys[GLFW_KEY_I] && keys[GLFW_KEY_LEFT_SHIFT]) {
		position += front * velocity; // Go forward
	}

	if (keys[GLFW_KEY_J] && keys[GLFW_KEY_LEFT_SHIFT]) {
		position -= right * velocity; // Go left
	}

	if (keys[GLFW_KEY_K] && keys[GLFW_KEY_LEFT_SHIFT]) {
		position -= front * velocity; // Go backwards
	}

	if (keys[GLFW_KEY_L] && keys[GLFW_KEY_LEFT_SHIFT]) {
		position += right * velocity; // Go right
	}

}


void Camera::pan(bool* keys, GLfloat x) { // When the right button is pressed, move right and left with the mouse

	if (keys[GLFW_MOUSE_BUTTON_RIGHT]) {
		x *= turnSpeed; // Calculate x value
		yaw += x; // Add x value to yaw

		// Keep mouse movement within a certain range
		if (yaw > 360.0f) yaw = 0.0f;
		if (yaw < 0.0f) yaw = 360.0f;

		update();
	}

}

void Camera::tilt(bool* keys, GLfloat y) { // When the down button is pressed, move up and down with the mouse

	if (keys[GLFW_MOUSE_BUTTON_MIDDLE]) {
		y *= turnSpeed; // Calculate y value
		pitch += y; // Add y value to pitch

		// Keep mouse movement within a certain range
		if (pitch > 50.0f) pitch = 50.0f; 
		if (pitch < -50.0f) pitch = -50.0f;

		update();
	}

}

void Camera::magnify(bool* keys, GLfloat z) { // When the down button is pressed, move up and down with the mouse

	if (keys[GLFW_MOUSE_BUTTON_LEFT]) {
		z *= turnSpeed * 0.01;
		position += front * z; // Go forward

		update();
	}

}

glm::mat4 Camera::calculateViewMatrix() {
	return glm::lookAt(position, position + front, up);
}

glm::mat4 Camera::calculateViewMatrix(glm::vec3 eye, glm::vec3 target, glm::vec3 up) {
	return glm::lookAt(eye, target, up);
}

Camera::~Camera(){

}