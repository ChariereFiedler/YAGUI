/* 
 * File:   Forme.h
 * Author: Ycarh
 *
 * Created on 15 novembre 2014, 16:52
 */

#ifndef FORME_H
#define	FORME_H
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ShapeCollection.h"

class ShapeCollection;

class Shape {
	glm::vec2 _transform;
	ShapeCollection &_collection;
	unsigned int _indCollection;
	float _angle;
public:
	Shape(ShapeCollection &collection, const glm::vec2 &pos,const glm::vec3 &color, float size = 1 , float angle = 0);
	Shape(const Shape & orig);
	virtual ~Shape();


	const glm::vec3 & getColor()const;
	const glm::vec2 & getPosition()const;
	const glm::vec2 & getTransform() const;
	float getAngle()const;
    float getSize()const;
	int getIndCollection()const;
	
	void setColor(const glm::vec3 & color);
    void setColor(float r, float v, float b);
	void setPosition(const glm::vec2 & position);
	void setTransform(const glm::vec2 & transform);
	void setAngle(float angle);
    void setSize(float size);

	void setIndCollection(unsigned int indice);

    void addColor(const glm::vec3 &color);
    void addColor(float r, float v, float b);
	void rotate(float angle);
	void translate(float x, float y);
	void effect();


	Shape & operator=(const Shape &orig);
private:
	void init();
	
	float _vitesse;
};

#endif	/* FORME_H */

