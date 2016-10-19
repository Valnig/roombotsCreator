/*
@author Valentin NIGOLIAN
valentin.nigolian@epfl.ch
Fall 2015
*/
#include "RoomBot.hh"

void printVec3(glm::vec3 vec){
	std::cout << "(" << vec.x << "," << vec.y << "," << vec.z << ")" << std::endl;
}

float norm(glm::vec3 vec){
	return sqrt(vec.x * vec.x + vec.y *vec.y + vec.z*vec.z);
}

void RTFtest(){
	for (int i(0); i < 10; i++){
		for (int j(0); j < 10; j++){
			for (int k(0); k < 10; k++){
				glm::vec3 from = (1.f / 10.f)*glm::vec3(i - 10.f, j - 10.f, k - 10.f);
				glm::vec3 to = (1.f / 10.f)*glm::vec3(k - 10.f, i - 10.f, j - 10.f);
				glm::vec3 x = glm::cross(from, to);
				float theta = glm::dot(from, to);
				glm::vec3 to2 = glm::vec3(rotationToFit(from, to, glm::vec3(from.y, -from.x, 0))*glm::vec4(from, 1.0));
				glm::vec3 diff = glm::vec3(glm::rotate(std::acos(glm::dot(from, to)), glm::cross(from, to))*glm::vec4(from, 1.0)) - to;
				printVec3(from);
				printVec3(to);
				printVec3(x);
				printVec3(to2);
				std::cout << "theta = " << theta << std::endl;
				std::cout << "diff = "; printVec3(diff);
				std::cout << "norm : " << norm(diff) << std::endl << std::endl;;
			}
		}
	}
}

RoomBot::RoomBot(glm::vec3 position, OBJModel* p_h1, OBJModel* p_h2, OBJModel* p_circle) :
//firstACMposition(position), firstACMnormal(normalize(glm::vec3(1.0, -1.0, 0.0))), left1Normal(normalize(glm::vec3(0.0, 0.0, -1.0))), d_p_hemisphere1(p_h1), d_p_hemisphere2(p_h2), d_p_circle(p_circle) 
firstACMposition(position), firstACMnormal(glm::vec3(0.0, -1.0, 0.0)), left1Normal(glm::vec3(-1.0, 0.0, 0.0)), d_p_hemisphere1(p_h1), d_p_hemisphere2(p_h2), d_p_circle(p_circle)

{

	std::cout << "created roombot. first ACM is at " << firstACMposition.x << "," << firstACMposition.y << "," << firstACMposition.z << std::endl;
	std::cout << "halmodules are at "; printVec3(halfmodulePosition(HM1)); 
	std::cout << "and at : "; printVec3(halfmodulePosition(HM2));

	for (unsigned int i(AXIS1); i <= AXIS3; i++){
		std::cout << "axis " << i << " : "; printVec3(Axis((AXIS_ENUM)i));
	}
	for (unsigned int face(FIRST_FACE); face <= LAST_FACE; face++){
		std::cout << "face  "<<face<<" : "; printVec3(facePosition((FACES_ENUM)face));
		std::cout << "with normal  ";  printVec3(faceNormal((FACES_ENUM)face));
		std::cout << "normal after rotation : "; printVec3(glm::vec3(rotationToFit(glm::vec3(0.0, 0.0, -1.0), faceNormal((FACES_ENUM)face), glm::vec3(0.0, 1.0, 0.0))*glm::vec4(0.0, 0.0, -1.0,1.0)));

	}
	//RTFtest();

	firstACMrotation = glm::rotate(M_PI / 2, glm::vec3(0, 1, 0))*glm::rotate(M_PI / 2, glm::vec3(0, 0, -1));

	firstACMnormal = glm::vec3(firstACMrotation*glm::vec4(baseFirstACMnormal(), 1.0));
	left1Normal = glm::vec3(firstACMrotation*glm::vec4(baseLeft1Normal(), 1.0));
}

int drawcount = 0;

void RoomBot::Draw(const glm::mat4& VP) //const
{
	drawcount++;
	firstACMrotation = glm::rotate(drawcount*(M_PI / 100) , glm::vec3(0, 1, 0))*glm::rotate(drawcount*(M_PI / 200), glm::vec3(0, 0, -1));

	/*drawcount = (drawcount + 1) % 71;

	switch(drawcount) {
	case 20: axisAngle1 += (M_PI / 10); break;
	case 40: axisAngle2 -= (M_PI / 10); break;
	case 60: axisAngle3 += (M_PI / 10); break;
	
	}*/


	glm::mat4 VPWithACMtransformation = VP*firstACMtransformation();

	d_p_hemisphere1->Draw(VPWithACMtransformation * glm::translate(centerTranslation()));
	d_p_hemisphere2->Draw(VPWithACMtransformation * AxisTransform(AXIS1));
	d_p_hemisphere1->Draw(VPWithACMtransformation * AxisTransform(AXIS1) * glm::translate(centerTranslation()) * AxisTransform(AXIS2));
	d_p_hemisphere2->Draw(VPWithACMtransformation * AxisTransform(AXIS1) * AxisTransform(AXIS2) * AxisTransform(AXIS3));


	glm::mat4 scale_matrix = glm::scale(glm::mat4(1.0f), glm::vec3(MODULE_SIZE*0.63f));

	//TODO : DRAW PROPERLY
	for (unsigned int face(FIRST_FACE); face <= LAST_FACE; face++){
		glm::mat4 rotation_matrix = rotationToFit(glm::vec3(0.0, 0.0, -1.0), faceNormal((FACES_ENUM)face), glm::vec3(0.0, 1.0, 0.0));
		//std::cout << norm(glm::vec3(rotationToFit(glm::vec3(0.0, 0.0, -1.0), faceNormal((FACES_ENUM)face), glm::vec3(0.0, 1.0, 0.0))*glm::vec4(glm::vec3(0.0, 0.0, -1.0), 1.0)) - faceNormal((FACES_ENUM)face)) <<  std::endl;;
		d_p_circle->Draw(VP 
			* glm::translate(facePosition((FACES_ENUM(face))))
			* rotation_matrix
			* scale_matrix);
	}
}


void RoomBot::Drag(glm::vec3 target){
	firstACMposition = target;
}



bool RoomBot::CloseEnough(glm::vec3 position, float distance){
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



//OK
glm::vec3 RoomBot::centerTranslation() const{
	return glm::vec3(0.0, MODULE_SIZE / 2, 0.0);
}

//OK
//the position of the center of the halfmodules
glm::vec3 RoomBot::halfmodulePosition(HALF_MODULE_ENUM hm) const{
	switch (hm){
	case HM1: return glm::vec3(firstACMtransformation() * glm::vec4(centerTranslation(),1.0)); break;
	case HM2: return glm::vec3(firstACMtransformation() * AxisTransform(AXIS1) * glm::vec4(2.0f*centerTranslation(), 1.0)); break;
		//case HM2: return halfmodulePosition(HM1) + axis(AXIS2)*(MODULE_SIZE); break;
	default: throw std::invalid_argument("There is no halfmodule " + hm); break;
	}
}

glm::vec3 RoomBot::baseFaceNormal(FACES_ENUM face) const{
	switch (face){
	case ACM1: return baseFirstACMnormal(); break;
	case LEFT1: return baseLeft1Normal(); break;
	case BACK1: return glm::cross(baseFirstACMnormal(), baseLeft1Normal()); break;

	case RIGHT1: return -baseLeft1Normal(); break;
	case FRONT1: return -baseFaceNormal(BACK1); break;

	case LEFT2: return baseLeft1Normal(); break;
	case BACK2: return baseFaceNormal(BACK1); break;

	case RIGHT2: return -baseLeft1Normal(); break;
	case FRONT2: return -baseFaceNormal(BACK1); break;
	case ACM2: return -baseFirstACMnormal(); break;

	default: throw std::invalid_argument("there is no face " + face);
	}
}

//this should work for all angle but must be verified
//all normals except the member ones or computed based on the difference between the face position and the corresponding halfmodule's center
glm::vec3 RoomBot::faceNormal(FACES_ENUM face) const{

	if (face >= 1 && face <= 10){
		if (face == ACM1)return firstACMnormal;
		else if (face == LEFT1) return left1Normal;
		else if (face == BACK1) return glm::normalize(glm::cross(firstACMnormal, left1Normal));
		else {
			if (face <= 5) return normalize(facePosition(face) - halfmodulePosition(HM1));
			else return normalize(facePosition(face) - halfmodulePosition(HM2));;
		}
	}
	else{
		throw std::invalid_argument("there is no face " + face);
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
glm::vec3 RoomBot::Axis(AXIS_ENUM axis) const{
	switch (axis){
	case AXIS1: return glm::vec3(MODULE_SIZE / 2); break;
	case AXIS2: return firstACMnormal; break;
	case AXIS3: return Axis(AXIS1); break;
	default: throw std::invalid_argument("There is no axis " + axis); break;
	}
}




//this should work for all angle but must be verified
glm::vec3 RoomBot::secondACMnormal() const{
	return faceNormal(ACM2);
}

glm::vec3 RoomBot::baseFirstACMnormal() const{
	return glm::vec3(0, -1, 0);
}

glm::vec3 RoomBot::baseLeft1Normal() const{
	return glm::vec3(-1, 0, 0);
}


glm::vec3 RoomBot::baseFacePosition(FACES_ENUM face) const{
	switch (face){
	case ACM1: return glm::vec3(0.0f); break;
	case LEFT1: return (baseLeft1Normal()-baseFirstACMnormal())*(MODULE_SIZE / 2); break;
	case BACK1: return (glm::cross(baseFirstACMnormal(), baseLeft1Normal())-baseFirstACMnormal())*(MODULE_SIZE / 2); break;

	case RIGHT1: return -baseLeft1Normal()*(MODULE_SIZE/2); break;
	case FRONT1: return -glm::cross(baseFirstACMnormal(), baseLeft1Normal())*(MODULE_SIZE / 2); break;

	case LEFT2: return baseFacePosition(LEFT1); break;
	case BACK2: return baseFacePosition(BACK1); break;

	case RIGHT2: return baseFacePosition(RIGHT1); break; 
	case FRONT2: return baseFacePosition(FRONT1); break;    
	case ACM2: return centerTranslation(); break;

	default: throw std::invalid_argument("there is no face " + face);
	}
}


//TODO -> compute
//only works with all angles at 0 for now
glm::vec3 RoomBot::secondACMposition() const{
	//for now it's based on ACM1's normal
	return facePosition(ACM2);
}

glm::vec3 RoomBot::middlePosition() const{
	return 0.5f * (halfmodulePosition(HM1) - halfmodulePosition(HM2)) ;
}


glm::vec3 RoomBot::facePosition(FACES_ENUM face) const{
	return glm::vec3(firstACMtransformation() * AxisTransform(face) * glm::vec4(baseFacePosition(face), 1.0));
}


glm::mat4 RoomBot::AxisTransform(AXIS_ENUM axis) const{
	switch (axis){
	case AXIS1: return glm::translate(centerTranslation())*glm::rotate(axisAngle1, Axis(AXIS1));
	case AXIS2: return glm::translate(centerTranslation())*glm::rotate(axisAngle2, Axis(AXIS2));
	case AXIS3: return glm::translate(centerTranslation())*glm::rotate(axisAngle3, Axis(AXIS3));
	}
}

glm::mat4 RoomBot::AxisTransform(FACES_ENUM face) const{
	switch (face){
	case ACM1: return glm::mat4(1.0f); break;
	case LEFT1: return glm::mat4(1.0f); break;
	case BACK1: return glm::mat4(1.0f); break;

	case RIGHT1: return AxisTransform(AXIS1); break;
	case FRONT1: return AxisTransform(AXIS1); break;

	case LEFT2: return AxisTransform(AXIS1)*AxisTransform(AXIS2); break;
	case BACK2: return AxisTransform(AXIS1)*AxisTransform(AXIS2); break;

	case RIGHT2: return AxisTransform(AXIS1)*AxisTransform(AXIS2)*AxisTransform(AXIS3); break;
	case FRONT2: return AxisTransform(AXIS1)*AxisTransform(AXIS2)*AxisTransform(AXIS3); break;
	case ACM2: return  AxisTransform(AXIS1)*AxisTransform(AXIS2)*AxisTransform(AXIS3); break;
	}
}


glm::mat4 RoomBot::firstACMtransformation() const{
	//le problème vient d'ici
	//return glm::translate(firstACMposition)*rotationToFit(firstACMnormal, baseFirstACMnormal(), baseLeft1Normal())*rotationToFit(left1Normal, baseLeft1Normal(), baseFirstACMnormal());
	return glm::translate(firstACMposition)*firstACMrotation;
}

//(0,0,-1), (0,-1,0), (-1,0,0) 
glm::mat4 rotationToFit(glm::vec3 from, glm::vec3 to, glm::vec3 axis){
	normalize(from);
	normalize(to);
	normalize(axis);
	if (norm(glm::cross(from, to)) == 0){
		if (glm::dot(from, to) / ((norm(from)*norm(to))) == 1) return glm::mat4(1.0f);
		else return glm::rotate(M_PI, axis);
	}
	else{
		glm::vec3 v = glm::cross(from, to);
		glm::mat4 V(0.0f);
		V[0][1] = -v.z;
		V[0][2] = v.y;
		V[1][0] = v.z;
		V[1][2] = -v.x;
		V[2][0] = -v.y;
		V[2][1] = v.x;

		//return glm::mat4(1.0f) + V + V*V*((1 - glm::dot(from, to)) / (norm(v)*norm(v)));
		return glm::rotate(std::acos(glm::dot(from, to)), glm::normalize(glm::cross(from, to)));
	}
}

