#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Shader.h"
#include "Mesh.h"
#include "Camera.h"
#include "Window.h"
#include "IndependentMesh.h"
#include "ComplexObject.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
float toRadians(float deg);
/// <summary>
/// Creates a square grid by creating vertices for the given amount of squares (basically a 2d array).
/// Links all the vertices with 2-pair indices that can be used with GL_LINES to draw the triangle. 
/// </summary>
/// <param name="squareCount">Integer describing amount of squares user wishes to be created. </param>
void createGrid(int squareCount);

// Character creation methods

/// <summary>
/// Creates characters representing the first and last letter of each team member's name, and the first and last digit of their student ID.
/// This then adds those created objects to the object list.
/// </summary>
/// <param name="shader">The shader that will be used to render the objects</param>


// Letter Creation Methods
ComplexObject* CreateLetterM(GLuint uniformModel);
ComplexObject* CreateLetterU(GLuint uniformModel);
ComplexObject* CreateLetterL(GLuint uniformModel);
ComplexObject* CreateLetterE(GLuint uniformModel);
ComplexObject* CreateLetterT(GLuint uniformModel);
void CreateLetters(Shader* shader);

// Create Axes
void CreateAxes(Shader* shader);

// Utility methods for object creation
IndependentMesh* CreateCylinder(double radius);
IndependentMesh* CreateCube();
IndependentMesh* CreateSphere();
IndependentMesh* CreateVertical(GLuint uniformModel);
IndependentMesh* CreateHorizontal(GLuint uniformModel);

// Select model to transfrom with keyboard
void SelectModel();

// Global Variables
const int WIDTH = 1024, HEIGHT = 768;
std::vector<Mesh*> meshList;
std::vector<ComplexObject*> objectList;
Camera camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 90.0f, 0.0f, 0.05f, 0.5f); // Initialize camera
Window window;
const float BASE_WORLD_XANGLE = -5.0f;
const float BASE_WORLD_YANGLE = 0.0f;
const float BASE_WORLD_Y_POS = -0.5f;
float currentWorldXAngle = BASE_WORLD_XANGLE;
float currentWorldYAngle = BASE_WORLD_YANGLE;
float currentYPos = BASE_WORLD_Y_POS - 1.0f;
float worldRotationIncrement = 0.5f;
float worldPosIncrement = 0.01f;

unsigned int selectedModel = 0; // Selected model to transform using keyboard

// Window initialization and handling modified from Ben Cook's Udemy course
// https://www.udemy.com/course/graphics-with-modern-opengl/
int main(int argc, char* argv[])
{
	// Initializing Global Variables
	meshList = std::vector<Mesh*>();
	objectList = std::vector<ComplexObject*>();

	window = Window(WIDTH, HEIGHT);
	window.initialise();

	glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_PRIMITIVE_RESTART);
    glPrimitiveRestartIndex(GL_PRIMITIVE_RESTART_FIXED_INDEX);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	// Creating grid
	createGrid(128);
	Shader gridShader = Shader("src/shader.vs", "src/shader.fs");

	glm::mat4 projection(1.0f);
	projection = glm::perspective(45.0f, (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);

	// Creating the letters
	CreateLetters(&gridShader);

	// Create the axes
    CreateAxes(&gridShader);

	while (!window.getShouldClose())
	{

		// rendering commands
        // Set background Teal 
		glClearColor(0.0f, 0.502f, 0.502f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Camera movement
		camera.pan(window.getKeys(), window.getDeltaX());
		camera.tilt(window.getKeys(), window.getDeltaY());
		camera.magnify(window.getKeys(), window.getDeltaY());
		camera.movementFromKeyboard(window.getKeys());

		gridShader.use();

		// Handling rotations
		// Rotating the entire world dependent on key presses.
			// We rotate around the X-Axis
		if (window.getKeys()[GLFW_KEY_LEFT])
		{
			// Anticlockwise rotation
			currentWorldXAngle += worldRotationIncrement;
		}
		if (window.getKeys()[GLFW_KEY_RIGHT])
		{
			// Clockwise rotation
			currentWorldXAngle -= worldRotationIncrement;
		}
		if (window.getKeys()[GLFW_KEY_UP])
		{
			// Anticlockwise rotation
			currentWorldYAngle += worldRotationIncrement;
		}
		if (window.getKeys()[GLFW_KEY_DOWN])
		{
			// Clockwise rotation
			currentWorldYAngle -= worldRotationIncrement;
		}
		if (window.getKeys()[GLFW_KEY_HOME])
		{
			// Reset to default rotation.
			currentWorldXAngle = BASE_WORLD_XANGLE;
			currentWorldYAngle = BASE_WORLD_YANGLE;
		}

		// Handling vertical camera movement
		if (window.getKeys()[GLFW_KEY_EQUAL])
		{
			currentYPos -= worldPosIncrement;
		}
		if (window.getKeys()[GLFW_KEY_MINUS])
		{
			currentYPos += worldPosIncrement;
		}
		
		if (window.getKeys()[GLFW_KEY_T])
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
		if (window.getKeys()[GLFW_KEY_L] && !window.getKeys()[GLFW_KEY_LEFT_SHIFT])
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		if (window.getKeys()[GLFW_KEY_P])
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		}

		// Seclect model to transform with keyboard
        SelectModel();

		// Model matrix for the world grid
		glm::mat4 model(1.0f);
		model = glm::translate(model, glm::vec3(-10.0f, 0.0f, -10.0f));
		model = glm::rotate(model, toRadians(0), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(20.0f, 1.0f, 20.0f));

		// View matrix
		glm::mat4 view(1.0f);
		view = glm::translate(view, glm::vec3(0.0f, currentYPos, 9.0f));
		view = glm::rotate(view, toRadians(currentWorldXAngle), glm::vec3(1.0f, 0.0f, 0.0f)); // Rotating around X Axis
		view = glm::rotate(view, toRadians(currentWorldYAngle), glm::vec3(0.0f, 1.0f, 0.0f)); // Rotating around Y Axis
		view = camera.calculateViewMatrix() * view;

		// Connect matrices with shaders
		gridShader.setMatrix4Float("model", &model);
		gridShader.setMatrix4Float("projection", &projection);
		gridShader.setMatrix4Float("view", &view);

		// Drawing the grid
		// Setting the color (yellow)
		gridShader.setFloat("r", 0.8f);
		gridShader.setFloat("rg", 0.85f);
		gridShader.setFloat("rgb", 0.0f);
		meshList[0]->RenderMesh(GL_LINES);

		// Drawing the letters

        // If 1 is pressed, transform T with keyboard
        if(selectedModel == 0){
            objectList[0]->objectList[0]->Transform(window.getKeys());
        }
        // Setting color
        gridShader.setFloat("r", 48.0f/255.0f);
        gridShader.setFloat("rg", 26.0f/255.0f);
        gridShader.setFloat("rgb", 75.0f/255.0f);
        // Render T
        objectList[0]->objectList[0]->RenderObject(objectList[0]->GetModelMatrix(), 0);

        // If 2 is pressed, transform E with keyboard
        if(selectedModel == 1){
            objectList[0]->objectList[1]->Transform(window.getKeys());
        }
        // Setting color
        gridShader.setFloat("r", 109.0f/255.0f);
        gridShader.setFloat("rg", 177.0f/255.0f);
        gridShader.setFloat("rgb", 191.0f/255.0f);
        // Render E
        objectList[0]->objectList[1]->RenderObject(objectList[0]->GetModelMatrix(), 0);

        // If 3 is pressed, transform L1 with keyboard
        if(selectedModel == 2){
            objectList[0]->objectList[2]->Transform(window.getKeys());
        }
        // Setting color
        gridShader.setFloat("r", 255.0f/255.0f);
        gridShader.setFloat("rg", 224.0f/255.0f);
        gridShader.setFloat("rgb", 236.0f/255.0f);
        // Render L1
        objectList[0]->objectList[2]->RenderObject(objectList[0]->GetModelMatrix(), 0);

        // If 4 is pressed, transform L2 with keyboard
        if(selectedModel == 3){
            objectList[0]->objectList[3]->Transform(window.getKeys());
        }
        // Setting color
        gridShader.setFloat("r", 243.0f/255.0f);
        gridShader.setFloat("rg", 154.0f/255.0f);
        gridShader.setFloat("rgb", 157.0f/255.0f);
        // Render L2
        objectList[0]->objectList[3]->RenderObject(objectList[0]->GetModelMatrix(), 0);

        // If 5 is pressed, transform U with keyboard
        if(selectedModel == 4){
            objectList[0]->objectList[4]->Transform(window.getKeys());
        }
        // Setting color
        gridShader.setFloat("r", 63.0f/255.0f);
        gridShader.setFloat("rg", 108.0f/255.0f);
        gridShader.setFloat("rgb", 81.0f/255.0f);
        // Render U
        objectList[0]->objectList[4]->RenderObject(objectList[0]->GetModelMatrix(), 0);

        // If 6 is pressed, transform M with keyboard
        if(selectedModel == 5){
            objectList[0]->objectList[5]->Transform(window.getKeys());
        }
        // Setting color
        gridShader.setFloat("r", 223.0f/255.0f);
        gridShader.setFloat("rg", 87.0f/255.0f);
        gridShader.setFloat("rgb", 188.0f/255.0f);
        // Render M
        objectList[0]->objectList[5]->RenderObject(objectList[0]->GetModelMatrix(), 0);

        // Render object containing all letters
		//objectList[0]->RenderObject();


        // Resetting the matrix
		model = glm::mat4(1.0f);
		gridShader.setMatrix4Float("model", &model);

		// Render the set of axis
		// Setting the colors gridShader.setFloat("r", 1.0);
		gridShader.setFloat("rg", 0.0f);
		gridShader.setFloat("rgb", 0.0f);
		objectList[1]->meshList[0]->RenderMesh(GL_TRIANGLE_STRIP);

		gridShader.setFloat("r", 0.0f);
		gridShader.setFloat("rg", 1.0f);
		gridShader.setFloat("rgb", 0.0f);
		objectList[1]->meshList[1]->RenderMesh(GL_TRIANGLE_STRIP);

		gridShader.setFloat("r", 0.0f);
		gridShader.setFloat("rg", 0.0f);
		gridShader.setFloat("rgb", 1.0f);
		objectList[1]->meshList[2]->RenderMesh(GL_TRIANGLE_STRIP);

		gridShader.free();

		//check and call events and swap buffers
		window.swapBuffers();
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

float toRadians(float deg)
{
	return deg * (3.14159265f / 180.0f);
}

// Create grid to draw
void createGrid(int squareCount)
{
	std::vector<float> vertices;
	std::vector<unsigned int> indices;

	// Loops through each row, then for each column it creates a point clamped between 0 to 1
	for (int i = 0; i <= squareCount; i++) {
		for (int j = 0; j <= squareCount; j++) {
			float x = (float)j / (float)squareCount;
			float y = 0;
			float z = (float)i / (float)squareCount;

			vertices.push_back(x);
			vertices.push_back(y);
			vertices.push_back(z);
		}
	}

	// A double loop to connect all the vertices with the appropriate indices.
	// First it top left to top right vertex, then top right with bottom right, then bottom right with bottom left and finally bottom left with top right. 
	for (int i = 0; i < squareCount; i++) {
		for (int j = 0; j < squareCount; j++) {
			int top = i * (1 + squareCount);
			int bottom = (i + 1) * (1 + squareCount);

			// Top line
			indices.push_back(top + j);
			indices.push_back(top + j + 1);
			// Right line
			indices.push_back(top + j + 1);
			indices.push_back(bottom + j + 1);
			// Bottom line
			indices.push_back(bottom + j + 1);
			indices.push_back(bottom + j);
			// Left line
			indices.push_back(bottom + j);
			indices.push_back(top + j);
		}
	}

	Mesh* gridObj = new Mesh();
	gridObj->CreateMesh(&vertices[0], &indices[0], vertices.size(), indices.size());
	meshList.push_back(gridObj);
}

// Create letters individually and then add them to a single complex object to draw
void CreateLetters(Shader* shader) {
	GLuint modelLocation = shader->getLocation("model");

    //////////////////////////////////////////
	// Creating Ian's name and ID object    //
	//////////////////////////////////////////

	// Create letter T
	ComplexObject* letterT = CreateLetterT(modelLocation);
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
    letterT->SetModelMatrix(model, modelLocation);

    // Create letter E
    ComplexObject* letterE = CreateLetterE(modelLocation);
    model = glm::translate(model, glm::vec3(0.0f, 4.7f, 0.0f));
    letterE->SetModelMatrix(model, modelLocation);

    // Create letter L
    ComplexObject* letterL1 = CreateLetterL(modelLocation);
    model = glm::translate(model, glm::vec3(0.0f, 4.7f, 0.0f));
    letterL1->SetModelMatrix(model, modelLocation);

    // Create another letter L
    ComplexObject* letterL2 = CreateLetterL(modelLocation);
    model = glm::translate(model, glm::vec3(0.0f, 4.7f, 0.0f));
    letterL2->SetModelMatrix(model, modelLocation);

    // Create letter U
    ComplexObject* letterU = CreateLetterU(modelLocation);
    model = glm::translate(model, glm::vec3(0.0f, 4.7f, 0.0f));
    letterU->SetModelMatrix(model, modelLocation);

    // Create letter M
    ComplexObject* letterM = CreateLetterM(modelLocation);
    model = glm::translate(model, glm::vec3(0.0f, 4.3f, 0.0f));
    letterM->SetModelMatrix(model, modelLocation);

    // Complex object for all letters
	ComplexObject* IanNameAndID = new ComplexObject();

    IanNameAndID->objectList.push_back(letterT);
    IanNameAndID->objectList.push_back(letterE);
    IanNameAndID->objectList.push_back(letterL1);
    IanNameAndID->objectList.push_back(letterL2);
    IanNameAndID->objectList.push_back(letterU);
    IanNameAndID->objectList.push_back(letterM);

    // Scale letters to a reasonable size and push to back of grid in z
    model = glm::mat4(1.0f);
    model = glm::scale(model, glm::vec3(0.25f,0.25f,0.25f));
    model = glm::translate(model, glm::vec3(0.0f, 1.0f, 40.0f));
    IanNameAndID->SetModelMatrix(model, modelLocation);

    // Add letters to list of objects to render
	objectList.push_back(IanNameAndID);
}

// Create axes to draw
void CreateAxes(Shader* shader)
{
	GLuint modelLocation = shader->getLocation("model");

	// 4 points for our axes
	GLfloat vertices[] = {
		0.0, 0.0, 0.0,
		7.0, 0.0, 0.0,
		0.0, 7.0, 0.0,
		0.0, 0.0, 7.0
	};

	// We draw 3 lines.
	unsigned int indicesX[] = {
		0, 1
	};

	unsigned int indicesY[] = {
		0, 2
	};

	unsigned int indicesZ[] = {
		0, 3
	};

	ComplexObject* axes = new ComplexObject();

	// Moving the set of axis
	glm::mat4 model = glm::mat4(1.0f);

	IndependentMesh* objX = CreateCylinder(0.125);
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    objX->SetModelMatrix(model, modelLocation);
	axes->meshList.push_back(objX);

	IndependentMesh* objY = CreateCylinder(0.125);
    model = glm::mat4(1.0f);
	axes->meshList.push_back(objY);

	IndependentMesh* objZ = CreateCylinder(0.125);
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    objZ->SetModelMatrix(model, modelLocation);
	axes->meshList.push_back(objZ);

	objectList.push_back(axes);
}

// Select model to transform with keyboard
void SelectModel()
{
    bool *keys = window.getKeys();
    // Set global variable to index of model in ComplexObject vector
    if(keys[GLFW_KEY_1]) selectedModel = 0;
    if(keys[GLFW_KEY_2]) selectedModel = 1;
    if(keys[GLFW_KEY_3]) selectedModel = 2;
    if(keys[GLFW_KEY_4]) selectedModel = 3;
    if(keys[GLFW_KEY_5]) selectedModel = 4;
    if(keys[GLFW_KEY_6]) selectedModel = 5;

}

// Creates a unit sphere - taken from https://gist.github.com/zwzmzd/0195733fa1210346b00d
IndependentMesh* CreateSphere(){
    int lats = 40;
    int longs = 40;

    int i, j;
    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;
    int indicator = 0;
    for(i = 0; i <= lats; i++) {
        double lat0 = glm::pi<double>() * (-0.5 + (double) (i - 1) / lats);
        // Set radius to 0.25
       double z0  = sin(lat0);
       double zr0 =  cos(lat0);

       double lat1 = glm::pi<double>() * (-0.5 + (double) i / lats);
       double z1  = sin(lat1);
       double zr1 =  cos(lat1);

       for(j = 0; j <= longs; j++) {
           double lng = 2 * glm::pi<double>() * (double) (j - 1) / longs;
           double x = cos(lng);
           double y = sin(lng);

           vertices.push_back(x * zr0);
           vertices.push_back(y * zr0);
           vertices.push_back(z0);
           indices.push_back(indicator);
           indicator++;

           vertices.push_back(x * zr1);
           vertices.push_back(y * zr1);
           vertices.push_back(z1);
           indices.push_back(indicator);
           indicator++;
       }
       indices.push_back(GL_PRIMITIVE_RESTART_FIXED_INDEX);
   }
    IndependentMesh* sphere = new IndependentMesh();
    sphere->CreateMesh(&vertices[0], &indices[0], vertices.size(), indices.size());
    return sphere;
}

// Creates a unit cube
IndependentMesh* CreateCube(){
    std::vector<GLuint> indices = {
            // front
            0, 1, 2,
            2, 3, 0,
            // right
            1, 5, 6,
            6, 2, 1,
            // back
            7, 6, 5,
            5, 4, 7,
            // left
            4, 0, 3,
            3, 7, 4,
            // bottom
            4, 5, 1,
            1, 0, 4,
            // top
            3, 2, 6,
            6, 7, 3
    };

    std::vector<GLfloat> vertices = {
            // front
            -0.5, -0.5,  0.5,
            0.5, -0.5,  0.5,
            0.5,  0.5,  0.5,
            -0.5,  0.5,  0.5,
            // back
            -0.5, -0.5, -0.5,
            0.5, -0.5, -0.5,
            0.5,  0.5, -0.5,
            -0.5,  0.5, -0.5
    };

    IndependentMesh* cube = new IndependentMesh();
    cube->CreateMesh(&vertices[0], &indices[0], vertices.size(), indices.size());
    return cube;

}

// Creates a 0.25 x 2.5 cylinder. Modified from https://gist.github.com/zwzmzd/0195733fa1210346b00d
IndependentMesh* CreateCylinder(double radius){
    int lats = 40;

    int i;
    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;
    int indicator = 0;
    for(i = 0; i <= lats; i++) {
        //First build circle
        double ang0 = 2 * glm::pi<double>() * ((double) (i - 1) / lats);
        double z0  = radius * sin(ang0);
        double x0 =  radius * cos(ang0);

        double ang1 = 2 * glm::pi<double>() * ((double) i / lats);
        double z1 = radius * sin(ang1);
        double x1 = radius * cos(ang1);

        // Sides
        // Bottom vertices
        vertices.push_back(x0);
        vertices.push_back(0.0);
        vertices.push_back(z0);
        indices.push_back(indicator);
        indicator++;

        vertices.push_back(x1);
        vertices.push_back(0.0);
        vertices.push_back(z1);
        indices.push_back(indicator);
        indicator++;


        // Sides
        // Top vertices
        vertices.push_back(x0);
        vertices.push_back(2.5);
        vertices.push_back(z0);
        indices.push_back(indicator);
        indicator++;

        vertices.push_back(x1);
        vertices.push_back(2.5);
        vertices.push_back(z1);
        indices.push_back(indicator);
        indicator++;

        // End faces
        // Top face
        vertices.push_back(x0);
        vertices.push_back(2.5);
        vertices.push_back(z0);
        indices.push_back(indicator);
        indicator++;

        vertices.push_back(x1);
        vertices.push_back(2.5);
        vertices.push_back(z1);
        indices.push_back(indicator);
        indicator++;

        vertices.push_back(0);
        vertices.push_back(2.5);
        vertices.push_back(0);
        indices.push_back(indicator);
        indicator++;

        // Bottom face
        vertices.push_back(x0);
        vertices.push_back(0);
        vertices.push_back(z0);
        indices.push_back(indicator);
        indicator++;

        vertices.push_back(x1);
        vertices.push_back(0);
        vertices.push_back(z1);
        indices.push_back(indicator);
        indicator++;

        vertices.push_back(0);
        vertices.push_back(0);
        vertices.push_back(0);
        indices.push_back(indicator);
        indicator++;
   }
    IndependentMesh* cylinder = new IndependentMesh();
    cylinder->CreateMesh(&vertices[0], &indices[0], vertices.size(), indices.size());
    return cylinder;
}

// Transforms base unit sphere into a 0.25 x 1.00 ellipsoid to be used as vertical portion of letters
IndependentMesh* CreateVertical(GLuint uniformModel){
   IndependentMesh* vert = CreateSphere();
   glm::mat4 partModel(1.0f);
   partModel = glm::scale(partModel, glm::vec3(0.25f, 1.0f, 0.25f));
   vert->SetModelMatrix(partModel, uniformModel);
   return vert;
}

// Transforms base unit cube into a 1.0 x 0.5 x 0.25 rectangle to be used as horizontal portion of letters
IndependentMesh* CreateHorizontal(GLuint uniformModel){
    IndependentMesh* horizontal = CreateCube();
    glm::mat4 partModel(1.0f);
    partModel = glm::scale(partModel, glm::vec3(1.0f, 0.5f, 0.25f));
    horizontal->SetModelMatrix(partModel, uniformModel);
    return horizontal;
}

// Creates a complex object for the letter M
ComplexObject* CreateLetterM(GLuint uniformModel){
    ComplexObject* letterM = new ComplexObject();

    // Bottom left vertical
    IndependentMesh* m1 = CreateVertical(uniformModel);
    glm::mat4 partModel = m1->GetModelMatrix();
    partModel = glm::translate(partModel, glm::vec3(-4.0f, 0.0f, 0.0f));
    m1->SetModelMatrix(partModel, uniformModel);
    letterM->meshList.push_back(m1);

    // Top left vertical
    IndependentMesh* m2 = CreateVertical(uniformModel);
    partModel = m2->GetModelMatrix();
    partModel = glm::translate(partModel, glm::vec3(-4.0f, 2.0f, 0.0f));
    m2->SetModelMatrix(partModel, uniformModel);
    letterM->meshList.push_back(m2);

    // Middle vertical
    IndependentMesh* m3 = CreateVertical(uniformModel);
    partModel = m3->GetModelMatrix();
    partModel = glm::translate(partModel, glm::vec3(0.0f, 2.0f, 0.0f));
    m3->SetModelMatrix(partModel, uniformModel);
    letterM->meshList.push_back(m3);

    // Bottom right vertical
    IndependentMesh* m4 = CreateVertical(uniformModel);
    partModel = m4->GetModelMatrix();
    partModel = glm::translate(partModel, glm::vec3(4.0f, 0.0f, 0.0f));
    m4->SetModelMatrix(partModel, uniformModel);
    letterM->meshList.push_back(m4);

    // Top left vertical
    IndependentMesh* m5 = CreateVertical(uniformModel);
    partModel = m5->GetModelMatrix();
    partModel = glm::translate(partModel, glm::vec3(4.0f, 2.0f, 0.0f));
    m5->SetModelMatrix(partModel, uniformModel);
    letterM->meshList.push_back(m5);

    // Bottom left horizontal
    IndependentMesh* m6 = CreateHorizontal(uniformModel);
    partModel = m6->GetModelMatrix();
    partModel = glm::translate(partModel, glm::vec3(-0.5, 6.0, 0.0));
    m6->SetModelMatrix(partModel, uniformModel);
    letterM->meshList.push_back(m6);

    // Bottom right horizontal
    IndependentMesh* m7 = CreateHorizontal(uniformModel);
    partModel = m7->GetModelMatrix();
    partModel = glm::translate(partModel, glm::vec3(0.5, 6.0, 0.0));
    m7->SetModelMatrix(partModel, uniformModel);
    letterM->meshList.push_back(m7);

    return letterM;
}

// Creates a complex object for the letter U
ComplexObject* CreateLetterU(GLuint uniformModel){
    ComplexObject* letterU = new ComplexObject();

    // Bottom left vertical
    IndependentMesh* u1 = CreateVertical(uniformModel);
    glm::mat4 partModel = u1->GetModelMatrix();
    partModel = glm::translate(partModel, glm::vec3(-4.0f, 0.0f, 0.0f));
    u1->SetModelMatrix(partModel, uniformModel);
    letterU->meshList.push_back(u1);

    // Top left vertical
    IndependentMesh* u2 = CreateVertical(uniformModel);
    partModel = u2->GetModelMatrix();
    partModel = glm::translate(partModel, glm::vec3(-4.0f, 2.0f, 0.0f));
    u2->SetModelMatrix(partModel, uniformModel);
    letterU->meshList.push_back(u2);

    // Top right vertical
    IndependentMesh* u3 = CreateVertical(uniformModel);
    partModel = u3->GetModelMatrix();
    partModel = glm::translate(partModel, glm::vec3(4.0f, 2.0f, 0.0f));
    u3->SetModelMatrix(partModel, uniformModel);
    letterU->meshList.push_back(u3);

    // Bottom right vertical
    IndependentMesh* u4 = CreateVertical(uniformModel);
    partModel = u4->GetModelMatrix();
    partModel = glm::translate(partModel, glm::vec3(4.0f, 0.0f, 0.0f));
    u4->SetModelMatrix(partModel, uniformModel);
    letterU->meshList.push_back(u4);

    // Bottom left horizontal
    IndependentMesh* u5 = CreateHorizontal(uniformModel);
    partModel = u5->GetModelMatrix();
    partModel = glm::translate(partModel, glm::vec3(-0.5, -2.0, 0.0));
    u5->SetModelMatrix(partModel, uniformModel);
    letterU->meshList.push_back(u5);

    // Bottom right horizontal
    IndependentMesh* u6 = CreateHorizontal(uniformModel);
    partModel = u6->GetModelMatrix();
    partModel = glm::translate(partModel, glm::vec3(0.5, -2.0, 0.0));
    u6->SetModelMatrix(partModel, uniformModel);
    letterU->meshList.push_back(u6);

    return letterU;
}

// Creates a complex object for the letter L
ComplexObject* CreateLetterL(GLuint uniformModel){
    ComplexObject* letterL = new ComplexObject();

    // Bottom left vertical
    IndependentMesh* l1 = CreateVertical(uniformModel);
    glm::mat4 partModel = l1->GetModelMatrix();
    partModel = glm::translate(partModel, glm::vec3(4.0f, 0.0f, 0.0f));
    l1->SetModelMatrix(partModel, uniformModel);
    letterL->meshList.push_back(l1);

    // Top left vertical
    IndependentMesh* l2 = CreateVertical(uniformModel);
    partModel = l2->GetModelMatrix();
    partModel = glm::translate(partModel, glm::vec3(4.0f, 2.0f, 0.0f));
    l2->SetModelMatrix(partModel, uniformModel);
    letterL->meshList.push_back(l2);

    // Bottom left horizontal
    IndependentMesh* l3 = CreateHorizontal(uniformModel);
    partModel = l3->GetModelMatrix();
    partModel = glm::translate(partModel, glm::vec3(-0.5, -2.0, 0.0));
    l3->SetModelMatrix(partModel, uniformModel);
    letterL->meshList.push_back(l3);

    // Bottom right horizontal
    IndependentMesh* l4 = CreateHorizontal(uniformModel);
    partModel = l4->GetModelMatrix();
    partModel = glm::translate(partModel, glm::vec3(0.5, -2.0, 0.0));
    l4->SetModelMatrix(partModel, uniformModel);
    letterL->meshList.push_back(l4);

    return letterL;
}

// Creates a complex object for the letter E
ComplexObject* CreateLetterE(GLuint uniformModel){
    ComplexObject* letterE = new ComplexObject();

    // Bottom left vertical
    IndependentMesh* e1 = CreateVertical(uniformModel);
    glm::mat4 partModel = e1->GetModelMatrix();
    partModel = glm::translate(partModel, glm::vec3(4.0f, 0.0f, 0.0f));
    e1->SetModelMatrix(partModel, uniformModel);
    letterE->meshList.push_back(e1);

    // Top left vertical
    IndependentMesh* e2 = CreateVertical(uniformModel);
    partModel = e2->GetModelMatrix();
    partModel = glm::translate(partModel, glm::vec3(4.0f, 2.0f, 0.0f));
    e2->SetModelMatrix(partModel, uniformModel);
    letterE->meshList.push_back(e2);

    // Bottom left horizontal
    IndependentMesh* e3 = CreateHorizontal(uniformModel);
    partModel = e3->GetModelMatrix();
    partModel = glm::translate(partModel, glm::vec3(-0.5, -2.0, 0.0));
    e3->SetModelMatrix(partModel, uniformModel);
    letterE->meshList.push_back(e3);

    // Bottom right horizontal
    IndependentMesh* e4 = CreateHorizontal(uniformModel);
    partModel = e4->GetModelMatrix();
    partModel = glm::translate(partModel, glm::vec3(0.5, -2.0, 0.0));
    e4->SetModelMatrix(partModel, uniformModel);
    letterE->meshList.push_back(e4);

    // Middle left horizontal
    IndependentMesh* e5 = CreateHorizontal(uniformModel);
    partModel = e5->GetModelMatrix();
    partModel = glm::translate(partModel, glm::vec3(-0.5, 2.0, 0.0));
    e5->SetModelMatrix(partModel, uniformModel);
    letterE->meshList.push_back(e5);

    // Middle right horizontal
    IndependentMesh* e6 = CreateHorizontal(uniformModel);
    partModel = e6->GetModelMatrix();
    partModel = glm::translate(partModel, glm::vec3(0.5, 2.0, 0.0));
    e6->SetModelMatrix(partModel, uniformModel);
    letterE->meshList.push_back(e6);

    // Top left horizontal
    IndependentMesh* e7 = CreateHorizontal(uniformModel);
    partModel = e7->GetModelMatrix();
    partModel = glm::translate(partModel, glm::vec3(-0.5, 6.0, 0.0));
    e7->SetModelMatrix(partModel, uniformModel);
    letterE->meshList.push_back(e7);

    // Top left horizontal
    IndependentMesh* e8 = CreateHorizontal(uniformModel);
    partModel = e8->GetModelMatrix();
    partModel = glm::translate(partModel, glm::vec3(0.5, 6.0, 0.0));
    e8->SetModelMatrix(partModel, uniformModel);
    letterE->meshList.push_back(e8);

    return letterE;
}

// Create a complex object for the letter T
ComplexObject* CreateLetterT(GLuint uniformModel) {
    ComplexObject *letterT = new ComplexObject();

    IndependentMesh *t1 = CreateVertical(uniformModel);
    glm::mat4 partModel = t1->GetModelMatrix();
    partModel = glm::translate(partModel, glm::vec3(0.0f, 0.0f, 0.0f));
    t1->SetModelMatrix(partModel, uniformModel);
    letterT->meshList.push_back(t1);

    IndependentMesh *t2 = CreateVertical(uniformModel);
    partModel = t2->GetModelMatrix();
    partModel = glm::translate(partModel, glm::vec3(0.0f, 2.0f, 0.0f));
    t2->SetModelMatrix(partModel, uniformModel);
    letterT->meshList.push_back(t2);

    IndependentMesh *t3 = CreateHorizontal(uniformModel);
    partModel = t3->GetModelMatrix();
    partModel = glm::translate(partModel, glm::vec3(-0.5, 6.0, 0.0));
    t3->SetModelMatrix(partModel, uniformModel);
    letterT->meshList.push_back(t3);

    IndependentMesh *t4 = CreateHorizontal(uniformModel);
    partModel = t4->GetModelMatrix();
    partModel = glm::translate(partModel, glm::vec3(0.5, 6.0, 0.0));
    t4->SetModelMatrix(partModel, uniformModel);
    letterT->meshList.push_back(t4);

    return letterT;
}

