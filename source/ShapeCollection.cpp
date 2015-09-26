/* 
 * File:   FormeCollection.cpp
 * Author: Ycarh
 * 
 * Created on 15 novembre 2014, 17:05
 */

#include "ShapeCollection.h"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

using namespace std;
ShapeCollection::ShapeCollection(const GLuint & indShader, ShapeModel &model):
	m_size(0),
	m_shaderIndex(indShader),
	_model(model)
{
	init();
}

ShapeCollection::ShapeCollection(const ShapeCollection & orig):
	m_size(0),
	m_shaderIndex(orig.m_shaderIndex),
	_model(orig._model)
	
{
	init();
}

ShapeCollection::~ShapeCollection() {
}

const unsigned int ShapeCollection::getNbObjects()const{
	return m_size;
}

void ShapeCollection::incNbObjects(){
	++m_size;
}

void ShapeCollection::init(){
  	_model.init();
  	glGenBuffers(1, &m_positionBufferId);
  	glBindBuffer(GL_ARRAY_BUFFER, m_positionBufferId);
  
  	glGenBuffers(1, &m_colorBufferId);
 	glBindBuffer(GL_ARRAY_BUFFER, m_colorBufferId);

	glGenBuffers(1, &m_angleBufferId);
  	glBindBuffer(GL_ARRAY_BUFFER, m_angleBufferId);

	glGenBuffers(1, &m_sizeBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, m_sizeBufferId);

  
}

void ShapeCollection::display(const glm::mat4 & projection){
	updateBuffers();


	glUseProgram(m_shaderIndex);
	glUniformMatrix4fv(glGetUniformLocation(m_shaderIndex, "P"), 1, GL_FALSE, glm::value_ptr(projection));
	glDrawElementsInstanced(GL_TRIANGLES, _model.GetNbIndices(), GL_UNSIGNED_INT, (GLvoid*) 0, m_size);


	// On désactive le tableau Vertex Attrib puisque l'on n'en a plus besoin
}

void ShapeCollection::close() {
	glDisableVertexAttribArray(4);
    glDisableVertexAttribArray(3);
  	glDisableVertexAttribArray(2);
  	glDisableVertexAttribArray(1);
  	glDisableVertexAttribArray(0);
  
  	glBindBuffer(GL_ARRAY_BUFFER, 0);
  	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  	glBindVertexArray(0);
}


void ShapeCollection::updateBuffers(){
	_model.bindBuffers();

	glBindBuffer(GL_ARRAY_BUFFER, m_positionBufferId);
	glBufferData(GL_ARRAY_BUFFER,_allPositions.size() * 2 * sizeof(GLfloat), &_allPositions.front(), GL_STREAM_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);
	
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBufferId);
	glBufferData(GL_ARRAY_BUFFER,_allColors.size()* 3 * sizeof(GLfloat), &_allColors.front(), GL_STREAM_DRAW); 
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, m_angleBufferId);
	glBufferData(GL_ARRAY_BUFFER,_allAngles.size() * sizeof(float), &_allAngles.front(), GL_STREAM_DRAW);
	glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(3);

    glBindBuffer(GL_ARRAY_BUFFER, m_sizeBufferId);
    glBufferData(GL_ARRAY_BUFFER,_allSizes.size() * sizeof(float), &_allSizes.front(), GL_STREAM_DRAW);
    glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(4);
	
	glVertexAttribDivisor(0, 0);
	glVertexAttribDivisor(1, 1);
	glVertexAttribDivisor(2, 1);
	glVertexAttribDivisor(3, 1);
    glVertexAttribDivisor(4, 1);
	
}

void ShapeCollection::push_back(FormeInstance * object){
	_allObjects.push_back(object);
	m_size++;
}

void ShapeCollection::pop_back(){
	m_size--;

	pop_back_AllData();
}

void ShapeCollection::addInstance(FormeInstance * instance){
	_allObjects.push_back(instance);
}

void ShapeCollection::removeInstance(FormeInstance * instance){
	
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
		--m_size;
		pop_back_AllData();
	}
	
}


 void ShapeCollection::pop_back_AllData(){
 	_allObjects.pop_back();
	_allColors.pop_back();
	_allPositions.pop_back();
	_allAngles.pop_back();
     _allSizes.pop_back();
 }