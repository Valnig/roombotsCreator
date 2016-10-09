#pragma once

#include "HalfModule.hh"

/**
   The Roombot class is a simple class that encapsulates two halfModules.
   It is mainly an interface class between the HalfModules and other parts
   of the software
*/

class RoomBot
{
private:
	glm::vec3 d_centerPosition;
	OBJModel*      d_p_hemisphere1;///<A pointer to a up-oriented hemisphere Model
	OBJModel*      d_p_hemisphere2;///<A pointer to a down-oriented hemisphere Model
	OBJModel*      d_p_circle;     ///<A pointer to a circle model

public:
	
	/**Creates a new RoomBot
	\arg \c A The Position of the first HalfModule
	\arg \c B The Position of the second HalfModule
	\arg p_h1,p_h2_p_circle Pointers to OBJModel used to construct the two HalfModule
	*/
	RoomBot(glm::vec3 position, 
			OBJModel* p_h1, 
			OBJModel* p_h2, 
			OBJModel* p_circle);


	/*
	bool MovableStructure::CloseEnough(glm::vec3 position) const
{
	return CloseEnough(position,DRAG_RADIUS);
}

bool MovableStructure::CloseEnough(glm::vec3 position, float distance) const
{
	return glm::distance(d_position + d_p_structure->CenterOffset() - glm::vec3(MODULE_SIZE / 2, MODULE_SIZE / 2, -MODULE_SIZE / 2), position) < distance;
}*/

	void Drag(glm::vec3 target){}
	bool CloseEnough(glm::vec3 position, float distance){ return CloseEnough(position, DRAG_RADIUS); }
	bool CloseEnough(glm::vec3 position){ return false; }
	void Drop(){}

	/**Draws the RoomBot*/
	void Draw(const glm::mat4& VP) const;

};