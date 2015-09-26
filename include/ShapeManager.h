/* 
 * File:   FormeManager.h
 * Author: Ycarh
 *
 * Created on 15 novembre 2014, 17:32
 */

#ifndef FORMEMANAGER_H
#define	FORMEMANAGER_H

#include <map>
#include <string>

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ShapeCollection.h"
#include "FormeInstance.h"
#include "ShapeModel.h"
class ShapeManager {
	std::map<std::string, ShapeCollection> _listCollections;
	glm::mat4 _projection;
	std::map<unsigned int, ShapeModel *> _libRegularModels;


public:
	ShapeManager( float width = 800, float height = 600);
	~ShapeManager();


    ShapeModel * generateRegularPolygone(unsigned int nbNode);
	bool newCollection(std::string key, const GLuint & indShader, ShapeModel & modele);
	bool newCollection(std::string key, const GLuint & indShader, unsigned int nbNodes);
	FormeInstance * newObject(std::string key, const glm::vec2 &position,const glm::vec3 &color,float size = 1, float angle = 0 );
	void display();
	//void close();
};	

#endif	/* FORMEMANAGER_H */

