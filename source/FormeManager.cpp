/* 
 * File:   FormeManager.cpp
 * Author: Ycarh
 * 
 * Created on 15 novembre 2014, 17:32
 */

#include "FormeManager.h"
#include <iostream>
#define M_PI 3.1415926535897932384

FormeManager::FormeManager(float width, float height) {
	_projection = glm::ortho( 0.0f, width, height, 0.0f,-5.0f, 5.0f);
}

FormeManager::~FormeManager() {
}

bool FormeManager::newCollection(std::string key, const GLuint & indShader, unsigned int nbNodes){
  std::map<unsigned int, FormeModele*>::key_compare comp;
  std::map<unsigned int, FormeModele*>::iterator it;

  comp = _libRegularModels.key_comp();
  it = _libRegularModels.find(nbNodes);

  if( comp( (*it).first, nbNodes ))
  {
    it = _libRegularModels.emplace(nbNodes, generateRegularPolygone(nbNodes)).first;
  }

  return newCollection(key, indShader, *(it->second) );
}

bool FormeManager::newCollection(std::string key, const GLuint & indShader, FormeModele & modele){
	 return _listCollections.emplace(key, FormeCollection(indShader, modele )).second;
}

FormeInstance * FormeManager::newObject(std::string key, const glm::vec2 &position, const glm::vec3 &color,float size, float angle){
  std::map<std::string, FormeCollection>::key_compare comp;
  std::map<std::string, FormeCollection>::iterator it;
  FormeInstance *instance;
  
  comp = _listCollections.key_comp();
  it = _listCollections.find(key);
  if( comp( (*it).first, key ))
	  throw("Aucune collection correspondant à ce nom n'existe \n");
  instance = new FormeInstance( it->second, position, color, size, angle);
  it->second.addInstance(instance);
  return instance;
}

void FormeManager::display(){
  glClear(GL_COLOR_BUFFER_BIT);
	std::map<std::string, FormeCollection>::iterator it;
	for(it = _listCollections.begin() ; it != _listCollections.end(); it++ ){
		it->second.display(_projection);
	}
}

FormeModele * FormeManager::generateRegularPolygone(unsigned int nbNode){
  std::vector<float> nodes;
  std::vector<unsigned int> indices;
  if(nbNode > 2){
    
    float angle =  M_PI * 2 / nbNode;

    for(unsigned int i = 0; i < nbNode; ++i){
      float a = angle * i;
      nodes.push_back(cos(a));
      nodes.push_back(sin(a));
    }
    for(unsigned int i = 2; i < nbNode; ++i){
      indices.push_back(0);
      indices.push_back(i-1);
      indices.push_back(i);
    }
/*
      for(unsigned int i = 0; i < nodes.size(); ++i)
      {
          std::cout << nodes[i] << std::endl;
      }
      for(unsigned int i = 0; i < indices.size(); ++i)
      {
          std::cout << indices[i] << std::endl;
      }*/
  }

  return new FormeModele(nodes, indices);
}