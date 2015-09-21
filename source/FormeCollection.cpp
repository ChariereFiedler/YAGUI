/* 
 * File:   FormeCollection.cpp
 * Author: Ycarh
 * 
 * Created on 15 novembre 2014, 17:05
 */

#include "FormeCollection.h"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

using namespace std;
FormeCollection::FormeCollection(const GLuint & indShader, FormeModele & modele):
	_nbObjects(0),
	_indShader(indShader),
	_modele(modele)	
{
	init();
}

FormeCollection::FormeCollection(const FormeCollection& orig):
	_nbObjects(0),
	_indShader(orig._indShader),
	_modele(orig._modele)
	
{
	init();
}

FormeCollection::~FormeCollection() {
}

const unsigned int FormeCollection::getNbObjects()const{
	return _nbObjects;
}

void FormeCollection::incNbObjects(){
	++_nbObjects;
}

void FormeCollection::init(){
  	_modele.init();
  	glGenBuffers(1, &_PositionBufferId);
  	glBindBuffer(GL_ARRAY_BUFFER, _PositionBufferId);
  
  	glGenBuffers(1, &_ColorBufferId);
 	glBindBuffer(GL_ARRAY_BUFFER, _ColorBufferId);

	glGenBuffers(1, &_AngleBufferId);
  	glBindBuffer(GL_ARRAY_BUFFER,_AngleBufferId);

	glGenBuffers(1, &_SizeBufferId);
	glBindBuffer(GL_ARRAY_BUFFER,_SizeBufferId);

  
}

void FormeCollection::display(const glm::mat4 & projection){
	updateBuffers();


	glUseProgram( _indShader);
	glUniformMatrix4fv(glGetUniformLocation(_indShader, "P"), 1, GL_FALSE, glm::value_ptr(projection));
	glDrawElementsInstanced(GL_TRIANGLES, _modele.GetNbIndices(), GL_UNSIGNED_INT, (GLvoid*) 0, _nbObjects);


	// On désactive le tableau Vertex Attrib puisque l'on n'en a plus besoin
}

void FormeCollection::close() {
	glDisableVertexAttribArray(4);
    glDisableVertexAttribArray(3);
  	glDisableVertexAttribArray(2);
  	glDisableVertexAttribArray(1);
  	glDisableVertexAttribArray(0);
  
  	glBindBuffer(GL_ARRAY_BUFFER, 0);
  	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  	glBindVertexArray(0);
}


void FormeCollection::updateBuffers(){
	_modele.bindBuffers();

	glBindBuffer(GL_ARRAY_BUFFER, _PositionBufferId);
	glBufferData(GL_ARRAY_BUFFER,_allPositions.size() * 2 * sizeof(GLfloat), &_allPositions.front(), GL_STREAM_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);
	
	glBindBuffer(GL_ARRAY_BUFFER, _ColorBufferId);
	glBufferData(GL_ARRAY_BUFFER,_allColors.size()* 3 * sizeof(GLfloat), &_allColors.front(), GL_STREAM_DRAW); 
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, _AngleBufferId);
	glBufferData(GL_ARRAY_BUFFER,_allAngles.size() * sizeof(float), &_allAngles.front(), GL_STREAM_DRAW);
	glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(3);

    glBindBuffer(GL_ARRAY_BUFFER, _SizeBufferId);
    glBufferData(GL_ARRAY_BUFFER,_allSizes.size() * sizeof(float), &_allSizes.front(), GL_STREAM_DRAW);
    glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(4);
	
	glVertexAttribDivisor(0, 0);
	glVertexAttribDivisor(1, 1);
	glVertexAttribDivisor(2, 1);
	glVertexAttribDivisor(3, 1);
    glVertexAttribDivisor(4, 1);
	
}

void FormeCollection::push_back(FormeInstance * object){
	_allObjects.push_back(object);
	_nbObjects++;
}

void FormeCollection::pop_back(){
	_nbObjects--;

	pop_back_AllDatas();
}

void FormeCollection::addInstance(FormeInstance * instance){
	_allObjects.push_back(instance);
}

void FormeCollection::removeInstance(FormeInstance * instance){
	
	list<FormeInstance*>::iterator it, itEnd;

	it = _allObjects.begin();
	itEnd = _allObjects.end();
	itEnd--;
	while((it != itEnd) && ( (*it)->getIndCollection() != instance->getIndCollection())){
		it++;
		//cout << "Iter : " << (*it)->getIndCollection() << endl;
	}
	
	if( (*it)->getIndCollection() != instance->getIndCollection())
		cout << "Instance inexistante a supprimer" << endl;
	else{
		(**itEnd).setIndCollection((**it).getIndCollection());
		(*it) = (*itEnd);
		--_nbObjects;
		pop_back_AllDatas();
	}
	
}


 void FormeCollection::pop_back_AllDatas(){
 	_allObjects.pop_back();
	_allColors.pop_back();
	_allPositions.pop_back();
	_allAngles.pop_back();
     _allSizes.pop_back();
 }