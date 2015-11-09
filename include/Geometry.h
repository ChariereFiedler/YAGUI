//
// Created by Patataa on 05/10/2015.
//

#ifndef OPENGL_TP1_OBJECT_H
#define OPENGL_TP1_OBJECT_H


#include <GL/glew.h>
#include <iostream>
#include "Buffer.h"

class Geometry {

    Buffer<GLfloat> m_vertices,
            m_normals,
            m_uv;

    Buffer<GLuint> m_indices;

    GLuint m_vaoId = 0;


public:

    void load(){

        std::cout<<"LoadGeometry"<<std::endl;
        glGenVertexArrays(1, &m_vaoId);
        GL_CHECK_ERROR;

        glBindVertexArray(m_vaoId);
        GL_CHECK_ERROR;

        std::cout << "Vertices Buffer loaded" << std::endl;
        m_vertices.load();

        std::cout << "Normals Buffer loaded" << std::endl;
        m_normals.load();

        std::cout << "UV Buffer loaded" << std::endl;
        m_uv.load();

        std::cout << "Indices Buffer loaded" << std::endl;
        m_indices.load();

        glBindVertexArray(0);
        GL_CHECK_ERROR;
        glBindBuffer(GL_ARRAY_BUFFER,0);
        GL_CHECK_ERROR;
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
        GL_CHECK_ERROR;
    }



    Geometry(
        const Buffer<GLfloat> & vertices,
        const Buffer<GLfloat> & normals,
        const Buffer<GLfloat> & uv,
        const Buffer<GLuint> & indices
    )
        :m_vertices(vertices),
         m_normals(normals),
         m_uv(uv),
         m_indices(indices)
    {
        load();
    }

    Geometry(
            std::vector<GLfloat> && dataVertices,
            std::vector<GLfloat> && dataNormals,
            std::vector<GLfloat> && dataUv,
            std::vector<GLuint > && dataIndices
    ):
            m_vertices( 0, GL_ARRAY_BUFFER,GL_STATIC_DRAW,3, 1,"Vertices",std::move(dataVertices)),
            m_normals(  1, GL_ARRAY_BUFFER,GL_STATIC_DRAW,3, 1,"Vertices",std::move(dataNormals) ),
            m_uv(       2, GL_ARRAY_BUFFER,GL_STATIC_DRAW,3, 1,"Vertices",std::move(dataUv) ),
            m_indices(  3, GL_ELEMENT_ARRAY_BUFFER,GL_STATIC_DRAW,3, 0,"Vertices",std::move(dataIndices) )
    {
        load();
    }

    Geometry(
            const std::vector<GLfloat> & dataVertices,
            const std::vector<GLfloat> & dataNormals,
            const std::vector<GLfloat> & dataUv,
            const std::vector<GLuint > & dataIndices
    ):
            m_vertices( 0, GL_ARRAY_BUFFER, GL_STATIC_DRAW, 3, 0,"Vertices", dataVertices),
            m_normals(  1, GL_ARRAY_BUFFER, GL_STATIC_DRAW, 3, 1,"Normals", dataNormals),
            m_uv(       2, GL_ARRAY_BUFFER, GL_STATIC_DRAW, 3, 1,"Uv", dataUv ),
            m_indices(  3, GL_ELEMENT_ARRAY_BUFFER,GL_STATIC_DRAW,3, 1,"Indices",dataIndices )
    {
        std::cout << "Geometry () - copy" << std::endl;
        load();
    }

    const GLuint & getVao()const {
        return m_vaoId;
    }

    const Buffer<GLfloat> &getVertices() const {
        return m_vertices;
    }

    const Buffer<GLfloat> &getNormals() const {
        return m_normals;
    }

    const Buffer<GLfloat> &getUv() const {
        return m_uv;
    }

    const Buffer<GLuint> &getIndices() const {
        return m_indices;
    }
};

inline std::ostream & operator<<(std::ostream & in, const Geometry & geometry) {
    in
        << "Vertices : " << geometry.getVertices() << std::endl
        << "Indices : " << geometry.getIndices() << std::endl
        << "Normals : " << geometry.getNormals() << std::endl
        << "Uv : " << geometry.getUv() <<std::endl;

    return in;
}

#endif //OPENGL_TP1_OBJECT_H
