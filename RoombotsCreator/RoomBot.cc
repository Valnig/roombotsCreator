/*
@author Valentin NIGOLIAN
valentin.nigolian@epfl.ch
Fall 2015
*/
#include "RoomBot.hh"
glm::vec3 d_centerPosition;
OBJModel*      d_p_hemisphere1;///<A pointer to a up-oriented hemisphere Model
OBJModel*      d_p_hemisphere2;///<A pointer to a down-oriented hemisphere Model
OBJModel*      d_p_circle;     ///<A pointer to a circle model

RoomBot::RoomBot(glm::vec3 position, OBJModel* p_h1, OBJModel* p_h2, OBJModel* p_circle) :
d_centerPosition(position), d_p_hemisphere1(p_h1), d_p_hemisphere2(p_h2), d_p_circle(p_circle) {}


void RoomBot::Draw(const glm::mat4& VP) const
{
	
	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), d_centerPosition + glm::vec3(MODULE_SIZE / 2));
	glm::mat4 VPWithTranslate = VP * translationMatrix;


	d_p_hemisphere1->Draw(VPWithTranslate);
	d_p_hemisphere2->Draw(VPWithTranslate);


	glm::mat4 scale_matrix = glm::scale(glm::mat4(1.0f), glm::vec3(MODULE_SIZE*0.65f));

	//Here, the same circle is drawn 6 times in different positions and orientations in order to draw all 6 faces
	d_p_circle->Draw(VP*glm::translate(glm::mat4(1.0f), glm::vec3(d_centerPosition.x, d_centerPosition.y - MODULE_SIZE / 2, d_centerPosition.z - 0.005f))
		*glm::rotate(1.57f, glm::vec3(1.0f, 0.0f, 0.0f))
		*scale_matrix);

	d_p_circle->Draw(VP*glm::translate(glm::mat4(1.0f), glm::vec3(d_centerPosition.x, d_centerPosition.y + MODULE_SIZE / 2, d_centerPosition.z - 0.005f))
		*glm::rotate(1.57f, glm::vec3(1.0f, 0.0f, 0.0f))
		*scale_matrix);

	d_p_circle->Draw(VP*glm::translate(glm::mat4(1.0f), glm::vec3(d_centerPosition.x, d_centerPosition.y + 0.001f, d_centerPosition.z + MODULE_SIZE / 2))
		*scale_matrix);

	d_p_circle->Draw(VP*glm::translate(glm::mat4(1.0f), glm::vec3(d_centerPosition.x, d_centerPosition.y + 0.001f, d_centerPosition.z - MODULE_SIZE / 2))
		*scale_matrix);

	d_p_circle->Draw(VP*glm::translate(glm::mat4(1.0f), glm::vec3(d_centerPosition.x - MODULE_SIZE / 2, d_centerPosition.y, d_centerPosition.z + 0.001f))
		*glm::rotate(1.57f, glm::vec3(0.0f, 1.0f, 0.0f))
		*scale_matrix);

	d_p_circle->Draw(VP*glm::translate(glm::mat4(1.0f), glm::vec3(d_centerPosition.x + MODULE_SIZE / 2, d_centerPosition.y, d_centerPosition.z + 0.001f))
		*glm::rotate(1.57f, glm::vec3(0.0f, 1.0f, 0.0f))
		*scale_matrix);
}


