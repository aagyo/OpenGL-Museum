#ifndef RENDERER_H
#define RENDERER_H

#include <GL/glew.h>
#define GLM_FORCE_CTOR_INIT 
#include <GLM.hpp>
#include <gtc/type_ptr.hpp>

#include "Texture2D.h"
#include "Shader.h"
#include "Camera.h"


class Renderer
{
public:
    // Constructor (inits shaders/shapes)
    Renderer(Shader& shader);
    Renderer(Shader& shader, bool flag);
    ~Renderer();
    // Renders a defined quad textured with given sprite
    void Draw(Texture2D& texture, Camera* pCamera, glm::vec3 position, glm::vec3 size, GLfloat rotate, glm::vec3 axis, char oAxis);
private:
    int resize = 20;
    Shader shader;
    GLuint quadVAO;
    // Initializes and configures the quad's buffer and vertex attributes
    void initRenderData();
    void initRenderData(bool flag);
    void rotateOn(glm::mat4& model,GLfloat& roatate,char oAxis);
    void howToDraw();
    bool flag = false;
 
};

#endif

