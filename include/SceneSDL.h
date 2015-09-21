/* 
 * File:   SceneSDL.h
 * Author: Ycarh
 *
 * Created on 29 septembre 2014, 22:34
 */

#ifndef SCENESDL_H
#define	SCENESDL_H
#include <string>
#include <SDL2/SDL.h>

#define GLEW_STATIC
#include <GL/glew.h>

class SceneSDL {
public:
    SceneSDL(std::string title = "Window", 
                int x =  50, 
                int y =  50, 
                int w = 800,
                int h = 600,
                Uint32 flags = SDL_WINDOW_OPENGL);
    SceneSDL(const SceneSDL& orig);
    virtual ~SceneSDL();
    void init();
    void destroy();
    void display();

    int getW() const {
        return w;
    }

    int getH() const {
        return h;
    }


private:
    std::string title;
    int x, y, w, h;
    Uint32 flags;
    SDL_Window* _window;
    SDL_GLContext _contexteOpenGL;
    bool _affichable;
};

#endif	/* SCENESDL_H */

