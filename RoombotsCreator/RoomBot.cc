/*
@author Valentin NIGOLIAN
valentin.nigolian@epfl.ch
Fall 2015
*/
#include "RoomBot.hh"

RoomBot::RoomBot(glm::vec3 position, OBJModel* p_h1, OBJModel* p_h2, OBJModel* p_circle) :
firstACMposition(position), firstACMnormal(glm::vec3(0.0, -1.0, 0.0)), left1Normal(glm::vec3(-1.0, 0.0, 0.0)), d_p_hemisphere1(p_h1), d_p_hemisphere2(p_h2), d_p_circle(p_circle) 
{
	std::cout << "created roombot. first ACM is at " << firstACMposition.x << "," << firstACMposition.x << "," << firstACMposition.x << std::endl;
	for (unsigned int face(FIRST_FACE); face < LAST_FACE; face++){
		std::cout << "face  " << (FACES_ENUM)face << " at " << facePosition((FACES_ENUM)face).x << "," << facePosition((FACES_ENUM)face).y << "," << facePosition((FACES_ENUM)face).z << std::endl;
		std::cout << "with normal  " << faceNormal((FACES_ENUM)face).x << "," << faceNormal((FACES_ENUM)face).y << "," << faceNormal((FACES_ENUM)face).z << std::endl;

	}

}


void RoomBot::Draw(const glm::mat4& VP) const
{
	//glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), d_firstPosition + glm::vec3(MODULE_SIZE / 2));
	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), firstACMposition);

	glm::mat4 VPWithTranslate = VP * translationMatrix;


	d_p_hemisphere1->Draw(VPWithTranslate);
	d_p_hemisphere2->Draw(VPWithTranslate);


	glm::mat4 scale_matrix = glm::scale(glm::mat4(1.0f), glm::vec3(MODULE_SIZE*0.65f));

	//TODO : DRAW PROPERLY
	for (unsigned int face(FIRST_FACE); face < 2; face++){
		d_p_circle->Draw(VP*glm::translate(glm::mat4(1.0f), facePosition((FACES_ENUM)face))
		*glm::rotate(M_PI, glm::normalize(faceNormal((FACES_ENUM)face) + glm::vec3(0.0, 1.0, 0.0)))
		*scale_matrix);
	}

	//Here, the same circle is drawn 6 times in different positions and orientations in order to draw all 6 faces
	/*d_p_circle->Draw(VP*glm::translate(glm::mat4(1.0f), glm::vec3(d_firstPosition.x, d_firstPosition.y - MODULE_SIZE / 2, d_firstPosition.z - 0.005f))
		*glm::rotate(1.57f, glm::vec3(1.0f, 0.0f, 0.0f))
		*scale_matrix);

	d_p_circle->Draw(VP*glm::translate(glm::mat4(1.0f), glm::vec3(d_firstPosition.x, d_firstPosition.y + MODULE_SIZE / 2, d_firstPosition.z - 0.005f))
		*glm::rotate(1.57f, glm::vec3(1.0f, 0.0f, 0.0f))
		*scale_matrix);

	d_p_circle->Draw(VP*glm::translate(glm::mat4(1.0f), glm::vec3(d_firstPosition.x, d_firstPosition.y + 0.001f, d_firstPosition.z + MODULE_SIZE / 2))
		*scale_matrix);

	d_p_circle->Draw(VP*glm::translate(glm::mat4(1.0f), glm::vec3(d_firstPosition.x, d_firstPosition.y + 0.001f, d_firstPosition.z - MODULE_SIZE / 2))
		*scale_matrix);

	d_p_circle->Draw(VP*glm::translate(glm::mat4(1.0f), glm::vec3(d_firstPosition.x - MODULE_SIZE / 2, d_firstPosition.y, d_firstPosition.z + 0.001f))
		*glm::rotate(1.57f, glm::vec3(0.0f, 1.0f, 0.0f))
		*scale_matrix);

	d_p_circle->Draw(VP*glm::translate(glm::mat4(1.0f), glm::vec3(d_firstPosition.x + MODULE_SIZE / 2, d_firstPosition.y, d_firstPosition.z + 0.001f))
		*glm::rotate(1.57f, glm::vec3(0.0f, 1.0f, 0.0f))
		*scale_matrix);
		*/
}


void RoomBot::Drag(glm::vec3 target){
	firstACMposition = target;

}



bool RoomBot::CloseEnough(glm::vec3 position, float distance){
	//std::cout << "(" << position.x << "," << position.y << "," << position.z << ")  (" << d_firstPosition.x << "," << d_firstPosition.y << "," << d_firstPosition.z << ")  = " << glm::distance(position, d_firstPosition) << std::endl;
	return glm::distance(position, halfmodulePosition(HM1)) < distance;
}

bool RoomBot::CloseEnough(glm::vec3 position){
	return CloseEnough(position, DRAG_RADIUS); 
}

void RoomBot::Drop(){
	firstACMposition = glm::vec3(firstACMposition.x, TABLE_HEIGHT, firstACMposition.z);
}


void RoomBot::LockFirstACM(glm::vec3 position, glm::vec3 normal){
	firstACMlocked = true;
}


/* faces :
1 : ACM1
2 : left1
3 : back1

4 : right1
5 : front1

6 : ACM2
7 : left2
8 : back2

9 : right2
10 : front2
*/

//this should work for all angle but must be verified
//all normals except the member ones or computed based on the difference between the face position and the corresponding halfmodule's center
glm::vec3 RoomBot::faceNormal(FACES_ENUM face) const{

	if (face >= 1 && face <= 10){
		if (face == ACM1)return firstACMnormal;
		else if (face == LEFT1) return left1Normal;
		else {
			if (face <= 5) return normalize(facePosition(face) - halfmodulePosition(HM1));
			else return normalize(facePosition(face) - halfmodulePosition(HM2));;
		}
	}else{
		throw std::invalid_argument("there is no face " + face);
	}
}

//the position of the center of the halfmodules
glm::vec3 RoomBot::halfmodulePosition(HALF_MODULE_ENUM hm) const{
	switch (hm){
	case HM1: return firstACMposition - firstACMnormal*(MODULE_SIZE/2); break;
	case HM2: return glm::vec3(glm::rotate(axisAngle1, axis(AXIS1))*glm::vec4(0.0, MODULE_SIZE*1.5f, 0.0, 1.0)); break;
	//case HM2: return halfmodulePosition(HM1) + axis(AXIS2)*(MODULE_SIZE); break;
	default: throw std::invalid_argument("There is no halfmodule " + hm); break;
	}
}

glm::vec3 RoomBot::ACMposition(HALF_MODULE_ENUM hm) const{
	switch (hm){
	case HM1: return firstACMposition; break;
	case HM2: return secondACMposition(); break;
	default: throw std::invalid_argument("There is no halfmodule " + hm); break;
	}
}

glm::vec3 RoomBot::ACMnormal(HALF_MODULE_ENUM hm) const{
	switch (hm){
	case HM1: return firstACMnormal; break;
	case HM2: return secondACMnormal(); break;
	default: throw std::invalid_argument("There is no halfmodule " + hm); break;
	}
}


//this should work for all angle but must be verified
glm::vec3 RoomBot::axis(AXIS_ENUM axis) const{
	switch (axis){
	case 1: return - glm::normalize((faceNormal(ACM1) + faceNormal(BACK1) + faceNormal(LEFT1))*(MODULE_SIZE / 2)); break;
	case 2: return glm::normalize(halfmodulePosition(HM2) - halfmodulePosition(HM1)); break;
	case 3: return - glm::normalize((faceNormal(ACM2) + faceNormal(BACK2) + faceNormal(LEFT2))*(MODULE_SIZE / 2)); break;
	default: throw std::invalid_argument("There is no axis " + axis); break;
	}
}


//this should work for all angle but must be verified
glm::vec3 RoomBot::secondACMnormal() const{
	return normalize(secondACMposition()-halfmodulePosition(HM2));
}

//TODO -> compute
//only works with all angles at 0 for now
glm::vec3 RoomBot::secondACMposition() const{
	//for now it's based on ACM1's normal
	return halfmodulePosition(HM2) - firstACMnormal*(MODULE_SIZE / 2);

}

//TODO : compute all faces positions
//only works with all angles at 0 for now
glm::vec3 RoomBot::facePosition(FACES_ENUM face) const{
	switch (face){
	case ACM1: return firstACMposition; break;
	case LEFT1: return halfmodulePosition(HM1) + left1Normal*(MODULE_SIZE / 2); break;
	case BACK1: return halfmodulePosition(HM1) + glm::cross(firstACMnormal,left1Normal)*(MODULE_SIZE / 2); break;

	case RIGHT1: return halfmodulePosition(HM1) - left1Normal*(MODULE_SIZE / 2); break;                                //TODO
	case FRONT1: return halfmodulePosition(HM1) - glm::cross(firstACMnormal, left1Normal)*(MODULE_SIZE / 2); break;    //TODO

	case ACM2: return secondACMposition(); break;
	case LEFT2: return halfmodulePosition(HM2) + left1Normal*(MODULE_SIZE / 2); break;
	case BACK2: return halfmodulePosition(HM1) + glm::cross(firstACMnormal, left1Normal)*(MODULE_SIZE / 2); break;

	case RIGHT2: return halfmodulePosition(HM2) - left1Normal*(MODULE_SIZE / 2); break;                                //TODO
	case FRONT2: return halfmodulePosition(HM1) - glm::cross(firstACMnormal, left1Normal)*(MODULE_SIZE / 2); break;    //TODO

	default: throw std::invalid_argument("there is no face " + face);
	}
}