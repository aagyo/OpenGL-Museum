#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include <GL/glew.h>

class Texture2D
{
public:
    // Holds the ID of the texture object, used for all texture operations to reference to this particlar texture
    GLuint ID;
    // Texture image dimensions
    GLint Width, Height; // Width and height of loaded image in pixels
    // Texture Format
    //int Internal_Format; // Format of texture object
    GLint Image_Format; // Format of loaded image
    // Texture configuration
    GLint Wrap_S; // Wrapping mode on S axis
    GLint Wrap_T; // Wrapping mode on T axis
    GLint Filter_Min; // Filtering mode if texture pixels < screen pixels
    GLint Filter_Max; // Filtering mode if texture pixels > screen pixels
    // Constructor (sets default texture modes)
    Texture2D();
    // Generates texture from image data
    void Generate(int width, int height, unsigned char* data);
    // Binds the texture as the current active GL_TEXTURE_2D texture object
    void Bind() const;
  
};
#endif


