/* 
 * File:   FormeModele.cpp
 * Author: Ycarh
 * 
 * Created on 17 novembre 2014, 19:02
 */
#include <iostream>
#include "FormeModele.h"
using namespace std;
FormeModele::FormeModele(vector<float> vertex, vector<unsigned int> indices):
	_vertex(vertex),
	_indices(indices),
	_nbIndices(indices.size()),
	_nbCoords(vertex.size()),
	_VaoId(0),
	_VboId(0),
	_IndicesBufferId(0)
{
	init();
	std::cout << "Nb Indicees" <<_nbIndices << std::endl;
	std::cout << "Nb Vertex" << _nbCoords << std::endl;
	std::cout << "Vao : "	<< _VaoId << std::endl;
}

FormeModele::FormeModele(const FormeModele& orig):
	_vertex(orig._vertex),
	_indices(orig._indices),
	_nbIndices(_indices.size()),
	_nbCoords(_vertex.size()),
	_VaoId(0),
	_VboId(0),
	_IndicesBufferId(0)
{
	init();
	std::cout << "Nb Indices : " <<_nbIndices << std::endl;
	std::cout << "Nb Vertex : " << _nbCoords << std::endl;
	std::cout << "Vao : "	<< _VaoId << std::endl;
}

FormeModele::~FormeModele() {
}

void FormeModele::init(){
  glGenVertexArrays(1, &_VaoId);
  glBindVertexArray(_VaoId);

  glGenBuffers(1, &_VboId);
  glBindBuffer(GL_ARRAY_BUFFER, _VboId);
  glBufferData(GL_ARRAY_BUFFER,(GLsizeiptr)_nbCoords * sizeof(float), (GLvoid*) &_vertex.front(), GL_STATIC_DRAW);

  glGenBuffers(1, &_IndicesBufferId);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _IndicesBufferId);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,(GLsizeiptr)_nbIndices * sizeof(unsigned int),  (GLvoid*) &_indices.front(), GL_STATIC_DRAW);

}

void FormeModele::bindBuffers() const{
  glBindVertexArray(_VaoId);
  
  glBindBuffer(GL_ARRAY_BUFFER, _VboId);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0,0);
  glEnableVertexAttribArray(0);
}
void FormeModele::bindVBO(){
	glBindBuffer(GL_ARRAY_BUFFER, _VboId);
}