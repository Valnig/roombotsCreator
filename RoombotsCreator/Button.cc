/*
@author Valentin NIGOLIAN
valentin.nigolian@epfl.ch
Fall 2015
*/
#include "Button.hh"
#include "RoomBot.hh"


Button::Button(glm::vec3 position) : d_position(position)
{
	d_model = new Cube("Shaders/simple_vshader.glsl", 
		               "Shaders/colorvec_fshader.glsl", 
					   "", 
					   glm::vec4(0.0f,0.0f,1.0f,0.3f));

	d_model->SetModelMatrix(glm::translate(glm::mat4(1.0f), d_position)
		                   *glm::scale(glm::mat4(1.0f), glm::vec3(BUTTON_SIZE)));

	d_shadow = new Quad("Shaders/simple_vshader.glsl", 
		                "Shaders/colorvec_fshader.glsl", 
						"", 
						glm::vec4(0.0f, 0.0f, 1.0f, 0.3f));

	d_shadow->SetModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(d_position.x, -EYES_POSITION + 0.01f, d_position.z))
							*glm::scale(glm::mat4(1.0f), glm::vec3(BUTTON_SIZE)));

}


void Button::Draw(const glm::mat4& VP) const
{
	d_model->Draw(VP);
	d_shadow->Draw(VP);
}


void Button::CleanUp() const
{
	d_model->CleanUp();
	d_shadow->CleanUp();
}
