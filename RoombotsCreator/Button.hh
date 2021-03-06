#pragma once

#include "Cube.hh"
#include "Quad.hh"

/** A Button is a holder for MovableStructure to pop.*/

class Button
{
	Cube*                 d_model;       ///<the cube model used to represent the button
	Quad*                 d_shadow;      ///<a shadow of the cube projected on the floor
	const glm::vec3       d_position;    ///<its position within the scene

public:
	
	/**Creates a new button containing the structure passed as argument
	\arg \c position the position of the new Button
	\arg \c ID the unique ID of the new Button
	\arg \c a pointer to the Structure that will be used to pop new MovableStructures*/
	Button(glm::vec3 position);

	/**Draws the button and its shadow*/
	void Draw(const glm::mat4& VP) const;

	/**Cleans up all the models (cube, shadow and the structure's)
	and deletes the pointer to the Structure, meaning it absolutely 
	shouldn't be accessed once this method has been called*/
	void CleanUp() const;

	/**Returns the button's position */
	glm::vec3 Position() const { return d_position; }


};
