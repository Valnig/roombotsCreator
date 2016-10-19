#pragma once

#include "HalfModule.hh"
/**
   The Roombot class is a simple class that encapsulates two halfModules.
   It is mainly an interface class between the HalfModules and other parts
   of the software
*/

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

//returns a rotation matrix to go from vector 'from' to vector 'to'. 
//'axis' is used in case 'from' and 'to' are parallel but in opposite direction since
//there are an infinite number of ways to rotate from a vector to its opposite
glm::mat4 rotationToFit(glm::vec3 from, glm::vec3 to, glm::vec3 axis);

class RoomBot
{
private:
	typedef enum{AXIS1=1,AXIS2,AXIS3} AXIS_ENUM;
	typedef enum{HM1=1,HM2} HALF_MODULE_ENUM;
	typedef enum{ ACM1 = 1, LEFT1, BACK1, RIGHT1, FRONT1, LEFT2, BACK2, RIGHT2, FRONT2, ACM2 } FACES_ENUM;
	#define FIRST_FACE ACM1
	#define LAST_FACE ACM2
	
	glm::vec3 firstACMposition;
	glm::vec3 firstACMnormal;
	glm::vec3 left1Normal;//orientation of the left face of the first module around the first face's normal
	glm::mat4 firstACMrotation;

	bool firstACMlocked = false;
	bool secondACMlocked = false;
	bool connected = false;

	float axisAngle1 = M_PI/4;///<the first motor's current angle (inside the first half-module)
	float axisAngle2 = M_PI / 3;///<the second motor's current angle (between the two half-modules)
	float axisAngle3 = M_PI/4;///<the third motor's current angle (inside the second half-module)

	OBJModel*      d_p_hemisphere1;///<A pointer to a up-oriented hemisphere Model
	OBJModel*      d_p_hemisphere2;///<A pointer to a down-oriented hemisphere Model
	OBJModel*      d_p_circle;     ///<A pointer to a circle model

	//data methods
	glm::vec3 baseFacePosition(FACES_ENUM face) const;
	glm::vec3 facePosition(FACES_ENUM face) const;
	glm::vec3 baseFaceNormal(FACES_ENUM face) const;
	glm::vec3 faceNormal(FACES_ENUM face) const;
	glm::vec3 halfmodulePosition(HALF_MODULE_ENUM hm) const;
	glm::vec3 ACMposition(HALF_MODULE_ENUM hm) const;
	glm::vec3 ACMnormal(HALF_MODULE_ENUM hm) const;
	glm::vec3 middlePosition() const;
	glm::vec3 secondACMposition() const;
	glm::vec3 secondACMnormal() const;
	glm::vec3 Axis(AXIS_ENUM axis) const;
	glm::mat4 AxisTransform(AXIS_ENUM axis) const;
	glm::mat4 AxisTransform(FACES_ENUM face) const;
	glm::vec3 centerTranslation() const;
	glm::vec3 baseFirstACMnormal() const;
	glm::vec3 baseLeft1Normal() const;
	glm::mat4 firstACMtransformation() const;
	

public:
	
	/**Creates a new RoomBot laying verticaly and with the first back face pointing at (0.0,-1.0,0.0)
	\arg \c A The Position of the first HalfModule
	\arg \c B The Position of the second HalfModule
	\arg p_h1,p_h2_p_circle Pointers to OBJModel used to construct the two HalfModule
	*/
	RoomBot(glm::vec3 position, 
			OBJModel* p_h1, 
			OBJModel* p_h2, 
			OBJModel* p_circle);
	

	//manipulation methods
	void LockFirstACM(glm::vec3 position, glm::vec3 normal);
	void Drag(glm::vec3 target);
	bool CloseEnough(glm::vec3 position, float distance);
	bool CloseEnough(glm::vec3 position);
	void Drop();

	/**Draws the RoomBot*/
	void Draw(const glm::mat4& VP);// const;

};