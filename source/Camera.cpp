/* 
 * File:   Camera.cpp
 * Author: Ycarh
 * 
 * Created on 11 mai 2014, 18:47
 */

#include <iostream>
#include <math.h>
#include "Camera.h"

#define PI (3.141592653589793)

Camera::Camera() :
        m_position(),
        m_orientation(),
        m_phi(0.0),
        m_theta(0.0),
        m_speed(0.3f),
        m_axeVertical(0, 1, 0),
        m_lateralMove(),

        m_targetPoint() {
}

Camera::Camera(glm::vec3 position, glm::vec3 targetPoint, glm::vec3 axeVertical, float speed) :
        m_position(position),
        m_orientation(),
        m_phi(-35.26),
        m_theta(-135),
        m_speed(speed),
        m_axeVertical(axeVertical),
        m_lateralMove(),
        m_targetPoint(targetPoint)
{
}

void Camera::redefine(glm::vec3 position, glm::vec3 targetPoint, glm::vec3 axeVertical, float speed) {
    std::cout<<"Redefine camera"<<std::endl;
    this->m_phi = 35.26f;
    this->m_theta = 135;
    this->m_position = position;
    this->m_targetPoint = targetPoint;
    this->m_axeVertical = axeVertical;
    this->m_speed = speed;
}
/*
Camera::Camera(glm::vec3& position,glm::vec3& pointCible,glm::vec3& axeVertical, float vitesse) : m_phi(-35.26), m_theta(-135), m_orientation(), m_lateralMove(),m_speed(vitesse)
{
	 this->m_position = position;
	 this->m_targetPoint = pointCible;
	 this->m_axeVertical = axeVertical;
	 
}
*/
Camera::~Camera() {
}

void Camera::orienter(int xRel, int yRel)
{
    // Récupération des angles

    m_phi += -yRel * 0.3;
    m_theta += -xRel * 0.3;


    // Limitation de l'angle phi

    if(m_phi > 89.0)
        m_phi = 89.0;

    else if(m_phi < -89.0)
        m_phi = -89.0;

    // Conversion des angles en radian
    float phiRadian = m_phi * PI / 180;
    float thetaRadian = m_theta * PI / 180;

    // Si l'axe vertical est l'axe X
    if(m_axeVertical.x == 1.0)
    {
        // Calcul des coordonnées sphériques
        m_orientation.x = sin(phiRadian);
        m_orientation.y = cos(phiRadian) * cos(thetaRadian);
        m_orientation.z = cos(phiRadian) * sin(thetaRadian);
    }
        // Si c'est l'axe Y
    else if(m_axeVertical.y == 1.0)
    {
        // Calcul des coordonnées sphériques
        m_orientation.x = cos(phiRadian) * sin(thetaRadian);
        m_orientation.y = sin(phiRadian);
        m_orientation.z = cos(phiRadian) * cos(thetaRadian);
    }
        // Sinon c'est l'axe Z
    else
    {
        // Calcul des coordonnées sphériques
        m_orientation.x = cos(phiRadian) * cos(thetaRadian);
        m_orientation.y = cos(phiRadian) * sin(thetaRadian);
        m_orientation.z = sin(phiRadian);
    }
    // Calcul de la normale
    m_lateralMove = glm::cross(m_axeVertical, m_orientation);
    m_lateralMove = glm::normalize(m_lateralMove);
    // Calcul du point ciblé pour OpenGL
    m_targetPoint = m_position + m_orientation;
}

void Camera::deplacementV(float dir){
    m_position = m_position + m_orientation * dir * this->m_speed;
    m_targetPoint = m_position + m_orientation;
}
void Camera::deplacementH(float dir){
    m_position = m_position + m_lateralMove * dir * this->m_speed;
    m_targetPoint = m_position + m_orientation;
}
void Camera::lookAt(glm::mat4 &modelview)
{
    // Actualisation de la vue dans la matrice
    modelview = glm::lookAt(m_position, m_targetPoint, m_axeVertical);
}