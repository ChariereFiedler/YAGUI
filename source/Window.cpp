/* 
 * File:   SceneSDL.cpp
 * Author: Ycarh
 * 
 * Created on 29 septembre 2014, 22:34
 */

#include "Window.h"
#include <iostream>
#include <stdexcept>
#include <GL_Error.h>
#include <assert.h>

Window::Window(
        std::string title,
        int x,
        int y,
        int w,
        int h,
        Uint32 flags
):
        x(x),
        y(y),
        w(w),
        h(h),
        m_flags(flags)

{
}

//Window::Window(const Window& orig) {}

Window::~Window() {
    destroy();
}
void Window::destroy(){
    if(m_displayable){
        SDL_DestroyWindow(m_window);
        m_displayable = false;
    }
}

void Window::display(){
    //TODO : remove this flag, it is called every frame

    //rand();

    //glClearColor(float(rand())/RAND_MAX,rand()/RAND_MAX,rand()/RAND_MAX,1.);


    SDL_GL_SwapWindow(this->m_window);
    GL_CHECK_ERROR;
}





void Window::load(){

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        throw std::runtime_error(SDL_GetError());

    // Initialize OpenGL
    //Todo : Externalize this initialization step
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3); // Opengl V 3.*
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3); // Opengl V *.3
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    //SDL_GL_SetSwapInterval(0);

    m_window = SDL_CreateWindow(
            this->m_title.c_str(),                  // window m_title
            this->x,           // initial x _position
            this->y,           // initial y _position
            this->w,                               // width, in pixels
            this->h,                               // height, in pixels
            this->m_flags                  // m_flags - see below
    );

    if(!m_window)
        throw std::runtime_error(SDL_GetError());

    m_OpenGLContext = SDL_GL_CreateContext(this->m_window);
    GL_CHECK_ERROR;
    if(!m_OpenGLContext)
        throw std::runtime_error(SDL_GetError());
    GL_CHECK_ERROR;


    glewExperimental = GL_TRUE;
    GL_CHECK_ERROR;
    if(glewInit() != GLEW_OK)
        throw std::runtime_error("Unable do load Glew");
    glGetError();
    GL_CHECK_ERROR;
    glEnable(GL_DEPTH_TEST);
    GL_CHECK_ERROR;


    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.1,0.1,0.1,1.);
    this->m_displayable = true;
}