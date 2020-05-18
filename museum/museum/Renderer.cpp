#include "Renderer.h"

Renderer::Renderer(Shader& shader)
{
    this->shader = shader;
    this->initRenderData();
}

Renderer::Renderer(Shader& shader, bool flag)
{
    this->shader = shader;
	this->initRenderData(flag);
}

Renderer::~Renderer()
{
    glDeleteVertexArrays(1, &this->quadVAO);
}

void Renderer::Draw(Texture2D& texture, Camera* pCamera, glm::vec3 position, glm::vec3 size, GLfloat rotate,glm::vec3 axis, char oAxis)
{
    // Prepare transformations
    this->shader.Use();
    glm::mat4 proj = pCamera->GetProjectionMatrix();
    glm::mat4 view = pCamera->GetViewMatrix();
    this->shader.SetMat4("projection", proj);
    this->shader.SetMat4("view", view);
    glm::mat4 model = glm::mat4();
    if(position.x!=0.0f || position.y != 0.0f || position.z != 0.0f)
       model = glm::translate(model, position);
    if(rotate!=0.0f)
        model = glm::rotate(model, rotate, axis); // Then rotate
	if (oAxis != NULL)
		rotateOn(model, rotate, oAxis);
    if(size.x!=0.0f || size.y!=0.0f || size.z!=0.0f)
        model = glm::scale(model, size); // Last scale

    this->shader.SetMat4("model", model);

    glActiveTexture(GL_TEXTURE0);
    texture.Bind();

    glBindVertexArray(this->quadVAO);
	howToDraw();
    //glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void Renderer::initRenderData()
{
    // Configure VAO/VBO
    GLuint VBO;
    GLfloat vertices[] = {
        5.0f + resize, -0.5f,  5.0f + resize, 1.0f + resize, 0.0f + resize,
        -5.0f - resize, -0.5f ,  5.0f + resize, 0.0f + resize, 0.0f + resize,
        -5.0f - resize, -0.5f,  -5.0f - resize,  0.0f + resize, 1.0f + resize,

        5.0f + resize, -0.5f,  5.0f + resize,  1.0f + resize, 0.0f + resize,
        -5.0f - resize, -0.5f, -5.0f - resize,  0.0f + resize, 1.0f + resize,
        5.0f + resize, -0.5f, -5.0f - resize,  1.0f + resize, 1.0f + resize,
    };

    glGenVertexArrays(1, &this->quadVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(this->quadVAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Renderer::initRenderData(bool flag)
{
	this->flag = flag;
	GLfloat podium[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};
	// Podium VAO and VBO
	GLuint podiumVBO;
	glGenVertexArrays(1, &this->quadVAO);
	glGenBuffers(1, &podiumVBO);

	glBindBuffer(GL_ARRAY_BUFFER, podiumVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(podium), podium, GL_STATIC_DRAW);

	glBindVertexArray(this->quadVAO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glBindVertexArray(0);
}

void Renderer::rotateOn(glm::mat4& model,GLfloat& rotate, char oAxis)
{
	if(oAxis == 'x')
		model = glm::rotate(model, rotate, glm::vec3(1.f,0.f,0.f));
	if(oAxis == 'y')
		model = glm::rotate(model, rotate, glm::vec3(0.f, 0.f, 1.f));
	if(oAxis == 'z')
		model = glm::rotate(model, rotate, glm::vec3(0.f, 1.f, 0.f));
}

void Renderer::howToDraw()
{
	if(this->flag == false)
		glDrawArrays(GL_TRIANGLES, 0, 6);
	else
		glDrawArrays(GL_TRIANGLES, 0, 12 * 3);
}
