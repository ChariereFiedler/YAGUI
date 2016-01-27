/* 
 * File:   main.cpp
 * Author: Ycarh
 *
 * Created on 29 septembre 2014, 21:54
 */


#include <cstdlib>

#include <SDL2/SDL.h>
#include <iostream>

#include <Geometry.h>
#include <Instance.h>
#include <AssimpBuilder.h>
#include <stdexcept> 
  

#include "Window.h"

#include <GL_Error.h>
#include "AssimpSceneLoader.h"

using namespace std;

void newMain(){

    glGetError();

    Window window;

    window.load();
    Loader::AssimpBuilder builder;
    Loader::AssimpSceneLoader loader;

    Scene * map =loader.import("map/map1.obj", builder);

    while(true) {
        glClear(GL_COLOR_BUFFER_BIT |GL_DEPTH_BUFFER_BIT);
        map->displayRaw();
        GL_CHECK_ERROR;
        window.display();
        GL_CHECK_ERROR;
        //std::cout<< gluErrorString(glGetError()) << std::endl;
    }


    window.destroy();

}
void oldMain(){

    glGetError();

    Window scene;

    scene.load();

    GL_CHECK_ERROR;
    glm::mat4 projection = glm::perspective(90.0f, 4.0f/3.0f, 0.1f, 1500.0f);

    glm::mat4 modelView = glm::lookAt(
            glm::vec3(0,0,100), //Eye Position
            glm::vec3(0,0,0), //Center position
            glm::vec3(0,1.,0.)	// Vertical appearing vector
    );

    projection = modelView = glm::mat4(1);


    GL_CHECK_ERROR;
    Shader shader("Shaders/couleur3D.vert", "Shaders/couleur3D.frag");


    GL_CHECK_ERROR;
    if(!shader.load())
        std::cout<<"Erreur de chargement du shader";
    GL_CHECK_ERROR;
    std::vector<GLfloat>vertices = {
            0, 1 , 0,
            1 , 0  , 0,
            1, 1 , 0
    };
    GL_CHECK_ERROR;
    std::vector<GLfloat> normals={0, 1 , 0,
                                  1 , 0  , 0,
                                  1, 1 , 0};

    std::vector<GLfloat> uv = {0, 1 , 0,
                               1 , 0  , 0,
                               1, 1 , 0};

    std::vector<GLuint> indices = {0,1,2};

    GL_CHECK_ERROR;
    Geometry cube(
            vertices,
            normals,
            uv,
            indices
    );

    GL_CHECK_ERROR;
    Instance object(cube, shader);
    GL_CHECK_ERROR;

    while(true) {

        object.display(projection, modelView);
        GL_CHECK_ERROR;
        scene.display();
        GL_CHECK_ERROR;
        std::cout<< gluErrorString(glGetError()) << std::endl;
    }


    scene.destroy();

}

int main(int argc, char **argv)  {
    std::cout<<"Plop"<<std::endl;

    newMain();

	return 1;
}

