// Modified from Ben Cook's Udemy OpenGL course https://www.udemy.com/course/graphics-with-modern-opengl/
#include "Window.h"

Window::Window()
{
	width = 1024;
	height = 768;
	deltaX = 0.0f;
	deltaY = 0.0f;

	for (int i = 0; i < 1024; i++) {
		keys[i] = 0;
	}
}

Window::Window(GLint windowWidth, GLint windowHeight)
{
	width = windowWidth;
	height = windowHeight;
	deltaX = 0.0f;
	deltaY = 0.0f;

	for (int i = 0; i < 1024; i++) {
		keys[i] = 0;
	}
}

int Window::initialise()
{
	if (!glfwInit())
	{
		printf("Error Initialising GLFW");
		glfwTerminate();
		return 1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// Create the window
	mainWindow = glfwCreateWindow(width, height, "Assignment 1", NULL, NULL);
	if (!mainWindow)
	{
		printf("Error creating GLFW window!");
		glfwTerminate();
		return 1;
	}

	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	glfwMakeContextCurrent(mainWindow);
	createCallbacks();
	glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	glewExperimental = GL_TRUE;

	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		printf("Error: %s", glewGetErrorString(error));
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	glViewport(0, 0, bufferWidth, bufferHeight);

	glfwSetWindowUserPointer(mainWindow, this);

	return 0;
}

void Window::createCallbacks() {
	glfwSetKeyCallback(mainWindow, handleKeys); // When a key is pressed in window, handle input
	glfwSetCursorPosCallback(mainWindow, handleMouse);
	glfwSetMouseButtonCallback(mainWindow, handleMouseButtons);
}

void Window::handleKeys(GLFWwindow* window, int key, int code, int action, int mode) {

	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) { // Close window if escape key is pressed
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key < 1024) {
		if (action == GLFW_PRESS) {
			theWindow->keys[key] = true;
		}
		else if (action == GLFW_RELEASE) {
			theWindow->keys[key] = false;
		}
	}

}

void Window::handleMouse(GLFWwindow* window, double x, double y) {

	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (theWindow->initialMouseMove) {
		theWindow->lastX = x;
		theWindow->lastY = y;
		theWindow->initialMouseMove = false;
	}

	theWindow->deltaX = x - theWindow->lastX;
	theWindow->deltaY = theWindow->lastY - y;

	theWindow->lastX = x;
	theWindow->lastY = y;

}

void Window::handleMouseButtons(GLFWwindow* window, int button, int action, int mods)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
	if (button >= 0 && button < 1024) {
		if (action == GLFW_PRESS) {
			theWindow->keys[button] = true;
		}
		else if (action == GLFW_RELEASE) {
			theWindow->keys[button] = false;
		}
	}
}


Window::~Window()
{
	glfwDestroyWindow(mainWindow);
	glfwTerminate();
}
