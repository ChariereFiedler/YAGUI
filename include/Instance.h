//
// Created by Patataa on 12/10/2015.
//

#ifndef OPENGL_TP1_INSTANCE_H
#define OPENGL_TP1_INSTANCE_H

#include <glm/gtx/transform.hpp>
#include <memory>
#include "Geometry.h"
#include "Shader.h"

using tm_type = GLfloat;

class Instance {

    Instance * m_parent = nullptr;
    std::vector<Instance *> m_children;

    const Geometry & m_geometry;
    const Shader & m_shader;
    glm::tmat4x4<tm_type> m_transformationMatrix;



public:

    //TODO : Replace shader by a material object
    Instance(
            const Geometry & geometry,
            const Shader & shader)
        :
            m_geometry(geometry),
            m_shader(shader),
            m_transformationMatrix(1.0)
            {
    }

    void setParent(Instance * parent) {
        m_parent = parent;
    }

    template<typename ... Args>
    void add_Children(Instance * head, Args ... children) {
        m_children.push_back(head);
        head->setParent(this);

        add_Children(children ...);
    }

    void add_children(){}




    template <typename  ... Args>
    glm::tmat4x4<tm_type> rotate(Args && ... pack) {
        return glm::rotate(m_geometry, std::forward<Args>(pack)...);
    }

    template <typename ... Args>
    glm::tmat4x4<tm_type> translate(Args && ... pack) {
        return glm::translate(m_transformationMatrix, std::forward<Args>(pack)...);
    }

    template <typename ... Args>
    glm::tmat4x4<tm_type> scale(Args && ... pack) {
        return glm::scale(m_transformationMatrix, std::forward<Args>(pack) ...);
    }

    void display(const glm::mat4 & projection, const glm::mat4 & modelView) const;
};


#endif //OPENGL_TP1_INSTANCE_H
