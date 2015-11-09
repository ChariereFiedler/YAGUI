/*
 * File:   FormeCollection.h
 * Author: Ycarh
 *
 * Created on 15 novembre 2014, 17:05
 */

#ifndef FORMECOLLECTION_H
#define	FORMECOLLECTION_H
#define GLM_FORCE_RADIANS




#include <vector>
#include <list>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "ShapeModel.h"
#include "Shape.h"
#include "Buffer.h"

class Shape;
/*
* \brief ShapeCollection data container of contained shapes
* Each collection is defined by a list of elements sharing their geometry
 * They have all the same model and they are instanced with an instancing algorithm
*/
class ShapeCollection {
	unsigned int m_size; /* The objects number contained by the collection */
	GLuint 	m_colorBufferId,
			m_positionBufferId,
			m_angleBufferId,
			m_sizeBufferId;

	GLuint m_shaderIndex;

	ShapeModel &_model;




	void pop_back_AllData();

public:
	std::vector<glm::vec3> _allColors;
	std::vector<glm::vec2> _allPositions;
	std::vector<float> _allAngles;
	std::vector<float> _allSizes;

	Buffer<GLfloat> positionBuffer;

	std::list<Shape *> _allObjects;

	/*
    * \brief ShapeCollection constructor
    * \param orig the ShapeCollection object to copy
    */
	ShapeCollection(const ShapeCollection & orig);

	/*
    * \brief ShapeCollection constructor
    * \param indShader a constant reference to the shader index used for the display
    * \param model the shape model of the collection
    */
	ShapeCollection(const GLuint & indShader, ShapeModel &model);
	virtual ~ShapeCollection();
	/*
    * \brief Getter for the objects number
    * \return the objects number contained by the collection
    */
	const unsigned int getNbObjects()const;
	/*
    * `\brief increase the number of objects by one
    */
	void incNbObjects();

	/*
    * \brief display the objects contained
    * \param projection the projection Matrix used for the display
    */
	void display(const glm::mat4 & projection);

	/*
    * \brief add an object at the end of the collection
    * \param object the object to add
    */
	void push_back(Shape * object);
	/*
	* \brief delete the last item of the collection
	*/
	void pop_back();

	/*
    * \brief add an object at the end of the collection
    */
	void addInstance(Shape * instance);
	void removeInstance(Shape * instance);


private:


	/*
	* \brief Operation requiered to initialize the buffer objects which contains the informations of the objects
	*/
	void init();

	void close();
	/*
    * \brief Operation requiered to close the buffers relatives of the objects informations
    */
	void updateBuffers();

};

#endif	/* FORMECOLLECTION_H */

