/* 
 * File:   Forme.cpp
 * Author: Ycarh
 * 
 * Created on 15 novembre 2014, 16:52
 */
#include <cstdlib>
#include "FormeInstance.h"
#include <iostream>

using namespace std;

FormeInstance::FormeInstance(FormeCollection &collection,  const glm::vec2 &pos,const glm::vec3 &color, float size, float angle):
	_collection(collection),
	_angle(angle)
{
	_indCollection = _collection.getNbObjects();
	_collection.incNbObjects();
	_collection._allPositions.push_back(pos);
	_collection._allColors.push_back(color);
	_collection._allAngles.push_back(angle);
    _collection._allSizes.push_back(size);
	_vitesse = rand() / (float)RAND_MAX * 5;
}

FormeInstance::FormeInstance(const FormeInstance& orig):
	_collection(orig._collection),
	_vitesse(orig._vitesse)
{
	_indCollection = _collection.getNbObjects();
	_collection.incNbObjects();
	_collection._allPositions.push_back(orig.getPosition());
	_collection._allColors.push_back(orig.getColor());
	_collection._allAngles.push_back(orig.getAngle());
    _collection._allSizes.push_back(orig.getSize());
}

FormeInstance::~FormeInstance() {
	//cout << "Delete FormeInstance" << endl;
	_collection.removeInstance(this);
	
}

void FormeInstance::init(){
	
}
const glm::vec3 & FormeInstance::getColor()const{
  return _collection._allColors[_indCollection];
}
const glm::vec2 & FormeInstance::getPosition()const{
  return _collection._allPositions[_indCollection];
}

float FormeInstance::getAngle()const{
  return _collection._allAngles[_indCollection];
}

float FormeInstance::getSize()const{
    return _collection._allSizes[_indCollection];
}

const glm::vec2 & FormeInstance::getTransform() const{
  return _transform;
}

int FormeInstance::getIndCollection() const{
	return _indCollection;
}

void FormeInstance::setColor(const glm::vec3 & color){
  _collection._allColors[_indCollection] = color;
}

void FormeInstance::setColor(float r, float v, float b){
    setColor(glm::vec3(r, v, b));
}

void FormeInstance::setPosition(const glm::vec2 & position){
 _collection._allPositions[_indCollection] = position;
}
void FormeInstance::setTransform(const glm::vec2 & transform){
  _transform = transform;
}
void FormeInstance::setAngle(float angle){

	if(angle < 0)
		angle = 360 + angle;

	_angle = angle;
	_collection._allAngles[_indCollection] = angle;
}

void FormeInstance::setSize(float size){
    _collection._allSizes[_indCollection] = size;
}

void FormeInstance::setIndCollection(unsigned int indice){
	_collection._allColors[indice] = _collection._allColors[_indCollection];
	_collection._allPositions[indice] = _collection._allPositions[_indCollection];
	_indCollection = indice;

}


void FormeInstance::rotate(float angle){
	setAngle(_angle + angle);
}

void FormeInstance::translate(float x, float y){
	_collection._allPositions[_indCollection] += glm::vec2(x,y);
}

void FormeInstance::effet(){
	_collection._allPositions[_indCollection].x += _vitesse;
	if(_collection._allPositions[_indCollection].x > 800)
		_collection._allPositions[_indCollection].x = 0;
}

FormeInstance& FormeInstance::operator=(const FormeInstance &orig){
	_transform = orig._transform;

	setColor(orig.getColor());
	setPosition(orig.getPosition());
	setAngle(orig.getAngle());

	_indCollection = orig._indCollection;
	return *this;
}

void FormeInstance::addColor(float r, float v, float b) {
    setColor(getColor() + glm::vec3(r, v, b));
}

void FormeInstance::addColor(const glm::vec3 &color) {
    setColor(getColor() + color);
}
