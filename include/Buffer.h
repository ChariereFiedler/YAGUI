//
// Created by Patataa on 05/10/2015.
//
#pragma once
#ifndef OPENGL_TP1_BUFFER_H
#define OPENGL_TP1_BUFFER_H


#include <vector>
#include <GL/glew.h>
#include <string>
#include <assert.h>
#include "GL_Error.h"


template<typename E>   // primary template
    inline GLenum getGLenumType()
    {
        return -1;
    }

    template <>
    inline GLenum getGLenumType<GLfloat>(){
        return GL_FLOAT;
    }

    template <>
    inline GLenum getGLenumType<GLint>(){
        return GL_INT;
    }

    template <>
    inline GLenum getGLenumType<GLshort>() {
        return GL_SHORT;
    }

    template <>
    inline GLenum getGLenumType<GLdouble>() {
        return GL_DOUBLE;
    }



template<typename T >
class Buffer {
    std::vector<T> m_data;
    GLuint m_index, m_id, m_sizePack, m_rate;
    GLenum  m_type, m_usage;
    std::string m_name;

public:

    template <typename ... Args >
    Buffer( const GLuint & index,
            const GLenum & type,
            const GLenum & usage,
            const GLuint & sizePack,
            const GLuint & rate,
            const std::string & name,
            Args && ... data
    ):      m_data(std::forward<Args>(data)...),
            m_index(index),
            m_sizePack(sizePack),
            m_rate(rate),
            m_type(type),
            m_usage(usage),
            m_name(name)

    {}

    Buffer(const Buffer<T> & origin)
            : m_data(origin.getData()),
              m_index(origin.getIndex()),
              m_id(origin.getSizePack()),
              m_sizePack(origin.getSizePack()),
              m_rate(origin.getRate()),
              m_type(origin.getType()),
              m_usage(origin.getUsage()),
              m_name(origin.getName())
    {}
    unsigned int size()const{
        return m_data.size();
    }
    GLenum getUsage() const {
        return m_usage;
    }

    void setUsage(GLenum m_usage) {
        Buffer::m_usage = m_usage;
    }

    const std::vector<T> & getData() const {
        return m_data;
    }

    void setData(const std::vector<T> &m_data) {
        Buffer::m_data = m_data;
    }

    GLuint getIndex() const {
        return m_index;
    }

    void setIndex(GLuint m_index) {
        Buffer::m_index = m_index;
    }

    GLuint getId() const {
        return m_id;
    }

    void setId(GLuint m_id) {
        Buffer::m_id = m_id;
    }

    GLuint getSizePack() const {
        return m_sizePack;
    }

    void setSizePack(GLuint m_sizePack) {
        Buffer::m_sizePack = m_sizePack;
    }

    GLuint getRate() const {
        return m_rate;
    }

    void setRate(GLuint m_rate) {
        Buffer::m_rate = m_rate;
    }

    GLenum getType() const {
        return m_type;
    }

    void setType(GLenum m_type) {
        Buffer::m_type = m_type;
    }

    const std::string & getName()const{
        return m_name;
    }

    virtual ~ Buffer(){}

    void load(){
        std::cout<<"========================="<<std::endl;
        std::cout<<"Begin BufferLoad"<<std::endl;
        glGenBuffers(1, &m_id);
        GL_CHECK_ERROR;
        std::cout<<"Begin BufferLoad"<<std::endl;
        glBindBuffer(m_type, m_id);
        GL_CHECK_ERROR;
        std::cout<<"Begin BufferLoad"<<std::endl;
        glBufferData(m_type,(GLsizeiptr) m_data.size() * sizeof(T), (GLvoid *) m_data.data(), m_usage);
        GL_CHECK_ERROR;
        std::cout<<"Begin BufferLoad"<<std::endl;
        if(m_type != GL_ELEMENT_ARRAY_BUFFER) {

            glVertexAttribPointer(m_index, m_sizePack, getGLenumType<T>(), GL_FALSE, 0, 0);
            std::cout<<"Begin BufferLoad"<<std::endl;
            GL_CHECK_ERROR;
            glEnableVertexAttribArray(m_index);
            std::cout<<"Begin BufferLoad"<<std::endl;
            GL_CHECK_ERROR;
            std::cout<<m_index << ":" << m_rate<<std::endl;


            //glVertexAttribDivisor(m_index, m_rate);
            std::cout<<"Begin BufferLoad"<<std::endl;
            GL_CHECK_ERROR;
        }
        std::cout<<"End"<<std::endl;
        std::cout<<"========================="<<std::endl;

    }

    /*
    GLenum bind(){
        glBindBuffer(m_type, m_id);

        return glGetError();
    }*/

    template<typename ... Args>
    void redefineData( Args && ...pack) {
        m_data = std::vector<T>(std::forward(pack)...);
    }

    void push_back(const std::vector<T> & data) {
        m_data.push_back(data);
    }

    void push_back(const T & data) {
        m_data.push_back(data);
    }
    T pop_back(){
        return m_data.pop_back();
    }
};

template<typename T>
inline std::ostream & operator<<(std::ostream & in, const Buffer<T> & buffer) {
    for(auto & element : buffer.getData()) {
        in << element << " | ";
    }
    return in;
}

#endif //OPENGL_TP1_BUFFER_H
