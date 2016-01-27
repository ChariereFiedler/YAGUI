//
// Created by Patataa on 16/11/2015.
//

#ifndef YAGUI_MAP_H
#define YAGUI_MAP_H

#include <map>
#include "Geometry.h"
#include "Instance.h"
#include "Camera.h"

class Scene {


public :
    std::map<std::string, Geometry> m_geometries;
    //Todo : use to define a scene tree
    Instance * m_rootInstance;
    std::vector<std::shared_ptr<Instance>> m_allInstances;
    Camera * m_camera;
    glm::mat4 m_view;
    Shader m_shader;
    Scene():
            m_geometries(),
            m_rootInstance(nullptr)
    {}

    void setRoot(Instance * root) {
        m_rootInstance = root;
    }

    void display() {
        std::vector<std::pair<Instance *, glm::mat4>> displayStack;
        //glm::mat4
    }

    void displayTree() {
        //Todo : implement a tree functional iterator with different strategy
    }
    Shader & makeShader(const std::string & vertextShaderName, const std::string & fragShaderName) {

                GL_CHECK_ERROR;
        m_shader  = Shader("Shaders/couleur3D.vert", "Shaders/couleur3D.frag");


        GL_CHECK_ERROR;
        if(!m_shader.load())
            std::cout<<"Erreur de chargement du shader";

        return m_shader;
    }

    void displayRaw(){
        //Todo : replace projection and modelview with a true camera
        glm::mat4 projection = glm::perspective(90.0f, 4.0f/3.0f, 0.3f, 1500.0f);

        glm::mat4 modelView = glm::lookAt(
                glm::vec3(10,3,5), //Eye Position
                glm::vec3(0,0,0), //Center position
                glm::vec3(0,1.,0.)	// Vertical appearing vector
        );

        for(auto & instance : m_allInstances) {
            instance->display(projection, modelView);
        }
    }
};

#endif //YAGUI_MAP_H
