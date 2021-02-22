#include "IndependentMesh.h"

IndependentMesh::IndependentMesh() : Mesh()
{
	modelMatrix = new glm::mat4(1.0f);
    uniformModelLocation = 0;
}

IndependentMesh::~IndependentMesh()
{
    // Removing the model matrix from gpu
    glUniform1f((*this).uniformModelLocation, 0.0f);

	delete modelMatrix;
}

void IndependentMesh::RenderMesh()
{
    // We want to work with our created VAO.
    glBindVertexArray(VAO);
    // We indent to show we are working with this VAO from here on.  

    // Binding IBO.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

    // Reassigning the uniform variable. So now we want to assign a matrix, 4x4, with float values.
    glUniformMatrix4fv(uniformModelLocation, // Value to change
        1, // How many matrices to pass
        GL_FALSE, // Transpose?
        glm::value_ptr(*modelMatrix)); // Our value. Can't pass our value directly. We need to use a pointer.

    // Drawing our triangles.
    glDrawElements(GL_TRIANGLES, // What to draw
        indexCount, // Count of indices
        GL_UNSIGNED_INT, // Format of indices
        0 // Point to the indices, but we dont need it because we have IBO already.
    );

    // Removing the model matrix from gpu
    glUniform1f(uniformModelLocation, 0.0f);

    // We unbind the VAO.
    glBindVertexArray(0);
    // Unbinding the IBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndependentMesh::RenderMesh(GLenum drawType)
{
    // We want to work with our created VAO.
    glBindVertexArray(VAO);
    // We indent to show we are working with this VAO from here on.  

    // Binding IBO.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

    // Reassigning the uniform variable. So now we want to assign a matrix, 4x4, with float values.
    glUniformMatrix4fv(uniformModelLocation, // Value to change
        1, // How many matrices to pass
        GL_FALSE, // Transpose?
        glm::value_ptr(*modelMatrix)); // Our value. Can't pass our value directly. We need to use a pointer.

    // Drawing our triangles.
    glDrawElements(drawType, // What to draw
        indexCount, // Count of indices
        GL_UNSIGNED_INT, // Format of indices
        0 // Point to the indices, but we dont need it because we have IBO already.
    );

    // Removing the model matrix from gpu
    glUniform1f(uniformModelLocation, 0.0f);

    // We unbind the VAO.
    glBindVertexArray(0);
    // Unbinding the IBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndependentMesh::RenderMesh(glm::mat4& matrix, GLuint uniformModelLocation)
{
    // We want to work with our created VAO.
    glBindVertexArray(VAO);
    // We indent to show we are working with this VAO from here on.  

    // Binding IBO.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

    // We apply the parent transformation first, then our own.
    glm::mat4 model = matrix * *modelMatrix;

    // Reassigning the uniform variable. So now we want to assign a matrix, 4x4, with float values.
    glUniformMatrix4fv(uniformModelLocation, // Value to change
        1, // How many matrices to pass
        GL_FALSE, // Transpose?
        glm::value_ptr(model)); // Our value. Can't pass our value directly. We need to use a pointer.

    // Drawing our triangles.
    glDrawElements(GL_TRIANGLE_STRIP, // What to draw
        indexCount, // Count of indices
        GL_UNSIGNED_INT, // Format of indices
        0 // Point to the indices, but we dont need it because we have IBO already.
    );

    // Removing the model matrix from gpu
    glUniform1f(uniformModelLocation, 0.0f);

    // We unbind the VAO.
    glBindVertexArray(0);
    // Unbinding the IBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndependentMesh::SetModelMatrix(glm::mat4& matrix, GLuint uniformModelLocation)
{
    // Removing the model matrix from gpu
    glUniform1f((*this).uniformModelLocation, 0.0f);

	*modelMatrix = matrix;
    this->uniformModelLocation = uniformModelLocation;
}

glm::mat4& IndependentMesh::GetModelMatrix()
{
	return *modelMatrix;
}
