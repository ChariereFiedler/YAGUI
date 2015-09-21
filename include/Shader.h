
#ifndef DEF_SHADER
#define DEF_SHADER
#define GLM_FORCE_RADIANS

// Include Windows



#include <GL/glew.h>



// Includes communs

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <string>
#include <fstream>


// Classe Shader

class Shader
{
    public:

    Shader();
    Shader(Shader const &shaderACopier);
    Shader(std::string vertexSource, std::string fragmentSource);
    ~Shader();

    Shader& operator=(Shader const &shaderACopier);

    bool charger();
    bool compilerShader(GLuint &shader, GLenum type, std::string const &fichierSource);
    const GLuint & getProgramID() const;


    private:

    GLuint m_vertexID;
    GLuint m_fragmentID;
    GLuint m_programID;

    std::string m_vertexSource;
    std::string m_fragmentSource;
};

#endif