//
// Created by Patataa on 12/10/2015.
//

#ifndef OPENGL_TP1_INSTANCE_H
#define OPENGL_TP1_INSTANCE_H

#include <glm/gtx/transform.hpp>
#include "Geometry.h"
#include "Shader.h"

using tm_type = GLfloat;

class Instance {
    const Geometry & m_geometry;
    const Shader & m_shader;
    glm::tmat4x4<tm_type> m_transformationMatrix;

public:

    //TODO : Replace shader by a material object
    Instance(const Geometry & geometry, const Shader & shader)
        :
            m_geometry(geometry),
            m_shader(shader),
            m_transformationMatrix(1.0)
            {
    }



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
