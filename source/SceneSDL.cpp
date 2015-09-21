/* 
 * File:   SceneSDL.cpp
 * Author: Ycarh
 * 
 * Created on 29 septembre 2014, 22:34
 */

#include "SceneSDL.h"
#include <iostream>
SceneSDL::SceneSDL(std::string title, 
                int x, 
                int y, 
                int w,
                int h,
                Uint32 flags):
        x(x),
        y(y),
        w(w),
        h(h),
        flags(flags)
               
{
}

//SceneSDL::SceneSDL(const SceneSDL& orig) {}

SceneSDL::~SceneSDL() {
    SDL_DestroyWindow(_window);
}
void SceneSDL::destroy(){
    SDL_DestroyWindow(_window);
}

void SceneSDL::display(){
  if(_affichable)
  {
	SDL_GL_SwapWindow(this->_window);
  }
}


void SceneSDL::init(){
	
  GLenum initialisationGLEW;
  if (SDL_Init(SDL_INIT_VIDEO) >= 0) {
	// Version d'OpenGL
		// Utilisation de la version 3.3 : gestion des shaders++
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3); // Opengl V 3.*
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3); // Opengl V *.3
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
		SDL_GL_SetSwapInterval(0);

	  _window = SDL_CreateWindow(
		  this->title.c_str(),                  // window title
		  this->x,           // initial x _position
		  this->y,           // initial y _position
		  this->w,                               // width, in pixels
		  this->h,                               // height, in pixels
		  this->flags                  // flags - see below
	  );
	  
	  this->_contexteOpenGL = SDL_GL_CreateContext(this->_window);
	  if (this->_contexteOpenGL != 0) {
            if (this->_window) {
                
				glewExperimental = GL_TRUE;
				// On initialise GLEW
                initialisationGLEW = glewInit();
                if (initialisationGLEW == GLEW_OK) {
                    //-----------------------------------------
					glEnable(GL_BLEND);
					glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
					this->_affichable = true;

					//-----------------------------------------
                }else std::cout << "Erreur Glew : %s \n" << glewGetErrorString(initialisationGLEW) << std::endl;
               
            }
            else  std::cout<<"Impossible de generer la fenetre: %s\n" << SDL_GetError() << std::endl;
        }
	  else std::cout << "Erreur de contexte: %s\n" << SDL_GetError() << std::endl;
	  
	  // Check that the window was successfully made
	  if (_window == NULL) {
		  // In the event that the window could not be made...
		  std::cout <<"Could not create window: %s\n"<< SDL_GetError() << std::endl;
	  }
  }
}
