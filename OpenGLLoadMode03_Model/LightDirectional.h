#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
class LightDirectional
{
public:
	glm::vec3 postion;
	glm::vec3 angles;
	glm::vec3 direction ;
	glm::vec3 color;

	LightDirectional(glm::vec3 _position, glm::vec3 _angles, glm::vec3 _color=glm::vec3(1.0f,1.0f,1.0f));
	void UpdateDirection();
};

