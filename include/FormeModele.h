/* 
 * File:   FormeModele.h
 * Author: Ycarh
 *
 * Created on 17 novembre 2014, 19:02
 */

#ifndef FORMEMODELE_H
#define	FORMEMODELE_H
#define GLM_FORCE_RADIANS

#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


class FormeModele {
public:
	FormeModele(std::vector<float> vertex, std::vector<unsigned int> indices);
	FormeModele(const FormeModele& orig);
	virtual ~FormeModele();
	
	void init();
	void bindBuffers() const;
	void bindVBO();

    void SetIndicesBufferId(GLuint _IndicesBufferId) {
    	this->_IndicesBufferId = _IndicesBufferId;
    }

    GLuint GetIndicesBufferId() const {
    	return _IndicesBufferId;
    }

    GLuint GetVboId() const {
    	return _VboId;
    }

    GLuint GetVaoId() const {
    	return _VaoId;
    }

    void SetNbCoords(unsigned int _nbCoords) {
    	this->_nbCoords = _nbCoords;
    }

    unsigned int GetNbCoords() const {
    	return _nbCoords;
    }

    void SetNbIndices(unsigned int _nbIndices) {
    	this->_nbIndices = _nbIndices;
    }

    unsigned int GetNbIndices() const {
    	return _nbIndices;
    }
	
	
private:
	std::vector<float> _vertex;
    std::vector<unsigned int> _indices;
	unsigned int _nbIndices, _nbCoords;
	GLuint _VaoId, _VboId, _IndicesBufferId;
	
	
	
};

#endif	/* FORMEMODELE_H */

