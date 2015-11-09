/* 
 * File:   Camera.h
 * Author: Ycarh
 *
 * Created on 11 mai 2014, 18:47
 */

#ifndef CAMERA_H
#define	CAMERA_H

//Include GLM
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Camera {
public:
    Camera();
    Camera(glm::vec3 position, glm::vec3 targetPoint, glm::vec3 axeVertical, float speed);

    void redefine(glm::vec3 position, glm::vec3 targetPoint, glm::vec3 axeVertical, float speed);

    //Camera(glm::vec3& position,glm::vec3& pointCible,glm::vec3& axeVertical, float vitesse);

    virtual ~Camera();

    void orienter(int xRel, int yRel);
    void deplacer(int x, int y);

    void lookAt(glm::mat4 &modelview);

    void deplacementV(float dir);
    void deplacementH(float dir);

    glm::vec3 m_position;
    glm::vec3 m_orientation;
private:


    // Attributs d'orientation
    float m_phi;
    float m_theta;
    float m_speed;

    // Attributs de déplacement
    glm::vec3 m_axeVertical;
    glm::vec3 m_lateralMove;


    glm::vec3 m_targetPoint;
};

#endif	/* CAMERA_H */

