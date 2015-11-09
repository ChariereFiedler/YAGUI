//
// Created by Patataa on 12/10/2015.
//

#include <GL_Error.h>
#include "Instance.h"

void Instance::display(const glm::mat4 & projection, const glm::mat4 &modelView) const {

    //std::cout << m_geometry << std::endl;
    glBindVertexArray(m_geometry.getVao());
    GL_CHECK_ERROR;
    glUseProgram(m_shader.getProgramID());
    GL_CHECK_ERROR;
    //Matrice de proj
    glUniformMatrix4fv(
            glGetUniformLocation(m_shader.getProgramID(), "P"),
            1,
            GL_FALSE,
            glm::value_ptr(projection)
    );
    GL_CHECK_ERROR;
    glUniformMatrix4fv(
            glGetUniformLocation(m_shader.getProgramID(), "MV"),
            1,
            GL_FALSE,
            glm::value_ptr(modelView)
    );
    GL_CHECK_ERROR;

    //std::cout<<m_geometry.getIndices().size()<<std::endl;
    glDrawElements(GL_TRIANGLES, m_geometry.getIndices().size(), GL_UNSIGNED_INT,(GLvoid*) 0);
    GL_CHECK_ERROR;

    glUseProgram(0);
    GL_CHECK_ERROR;
    //std::cout<< " 5 - "<<gluErrorString(glGetError()) << std::endl;
    glBindVertexArray(0);
    GL_CHECK_ERROR;
}