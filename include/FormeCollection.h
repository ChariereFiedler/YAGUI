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
#include "FormeModele.h"
#include "FormeInstance.h"

class FormeInstance;
/*
* \brief FormeCollection contains the informations relatives to their objects to display
*/
class FormeCollection {
unsigned int  _nbObjects;
GLuint _ColorBufferId, _PositionBufferId, _AngleBufferId, _SizeBufferId;

GLuint _indShader;
FormeModele & _modele;


void pop_back_AllDatas();

public:
std::vector<glm::vec3> _allColors;
std::vector<glm::vec2> _allPositions;
std::vector<float> _allAngles;
std::vector<float> _allSizes;

std::list<FormeInstance*> _allObjects;

    /*
    * \brief FormeCollection constructor
    * \param orig the FormeCollection object to copy
    */
	FormeCollection(const FormeCollection& orig);

    /*
    * \brief FormeCollection constructor
    * \param indShader a constant reference to the shader index used for the display
    *  \param modele the modele of the objects contained by the collection
    */
	FormeCollection(const GLuint & indShader, FormeModele & modele);
	virtual ~FormeCollection();
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
    void push_back(FormeInstance * object);
	/*
	* \brief delete the last item of the collection
	*/
    void pop_back();

    /*
    * \brief add an object at the end of the collection
    */
	void addInstance(FormeInstance * instance);
	void removeInstance(FormeInstance * instance);
	
	
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

