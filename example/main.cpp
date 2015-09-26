/* 
 * File:   main.cpp
 * Author: Ycarh
 *
 * Created on 29 septembre 2014, 21:54
 */
#define GLM_FORCE_RADIANS

#include <cstdlib>

#include <cstdlib>
#include <SDL2/SDL.h>
#include <iostream>
#include <stdio.h>

#include <iostream> 
#include <stdexcept> 
  

#include "SceneSDL.h"

#include "FormeInstance.h"
#include "FormeManager.h"
#include "FormeModele.h"
#include "Shader.h"
using namespace std;

/*
 * 
 */


int main(int argc, char** argv) {

		srand(0);
	
		SceneSDL scene;
        
		scene.init();
		
		FormeManager fm;
		Shader shader("Shaders/forme2D.vert", "Shaders/forme2D.frag");
		if(!shader.charger())return 1;
		
		std::vector<float> sommets = {-40 , -20 , 0 ,50, 40 , -20};
		std::vector<unsigned int> indices = { 0, 1, 2};
		std::vector<FormeInstance *> biblio;
		
		glm::vec2 pos(0,0);
		glm::vec3 color(1,0,0);
		
		FormeModele modele(sommets, indices);
		
		FormeModele * penta =  fm.generateRegularPolygone(3);
		
		fm.newCollection(string("Triangle"), shader.getProgramID(), *penta);


		//delete biblio.front();
		//biblio.erase(biblio.begin()--);


		for(int j = 0; j < 10000; ++j)
			biblio.push_back(fm.newObject(string("Triangle"), glm::vec2(rand()%800,rand()%600), glm::vec3( 0, (float)rand() / (float)RAND_MAX , (float)rand() / (float)RAND_MAX  ), rand() % 360  ) );

		cout << "Fin pop_back" << endl;
		cout << biblio.size() << endl;
		std::vector<FormeInstance *>::iterator it;
		for(int i = 0; i < 5000; ++i){


			for(it = biblio.begin(); it != biblio.end(); ++it){
				(*it)->translate((float)rand() / (float)RAND_MAX * 10 - 5,(float)rand() / (float)RAND_MAX * 10 - 5);
				//(*it)->rotate(10);
			}

			glClear(GL_COLOR_BUFFER_BIT);
			fm.display();
			scene.display();

		}
		
		scene.display();
		

        scene.destroy();
        // Close and destroy the window
        return 1;
}

