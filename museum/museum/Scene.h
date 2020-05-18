#ifndef SCENE_H
#define SCENE_H

#include <GL/glew.h>
#include <glfw3.h>
#include "Camera.h"
#include <vector>

class Scene
{
public:
    GLuint Width, Height;
    // Constructor/Destructor
    Scene(GLuint width, GLuint height);
    ~Scene();
    // Initialize game state (load all shaders/textures/levels)
    void Init();
    void SetCamera(Camera* camera);
    // GameLoop
    void Render();
    void RenderModels();
    bool TeleportingCollWall();
    bool CheckColFloor();
    bool CheckCollObj();

private:
    int resize = 20;
    Camera* pCamera;
    bool modelsLoaded = false;
};
#endif 

