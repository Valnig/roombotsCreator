/*
@author Valentin NIGOLIAN
valentin.nigolian@epfl.ch
Fall 2015
*/
#include "GUI.hh"



void GUI::Init()
{
	//first, the LeapmotionPointer is initialized
	d_pointer.Init(this);

	//then we set up the hemisphere models used by the Roombot modules
	OBJModel* hemisphere1 = new OBJModel("Models/hemisphere_10.obj", "Shaders/simple_vshader.glsl", "Shaders/colorvec_fshader.glsl", "", glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));
	OBJModel* hemisphere2 = new OBJModel("Models/hemisphere_10.obj", "Shaders/simple_vshader.glsl", "Shaders/colorvec_fshader.glsl", "", glm::vec4(0.8f, 0.8f, 0.8f, 1.0f));
	
	hemisphere1->SetModelMatrix(glm::scale(glm::mat4(1.0f), glm::vec3(MODULE_SIZE)));
	hemisphere2->SetModelMatrix(glm::rotate(1.57f, glm::vec3(1.0f, 0.0f, 0.0f))
	*glm::rotate(3.14f, glm::vec3(.0f, 0.0f, 1.0f))
	*glm::scale(glm::mat4(1.0f), glm::vec3(MODULE_SIZE)));
	
	glm::vec4 pale_green(0.66f, 0.66f, 0.18f, 1.0f);
	OBJModel* p_circle = new OBJModel("Models/circle_50.obj", "Shaders/simple_vshader.glsl", "Shaders/colorvec_fshader.glsl", "", pale_green);

	d_p_hemi1 = hemisphere1;
	d_p_hemi2 = hemisphere2;
	d_p_circle = p_circle;

	AddButton();

	d_trashCan = new TrashCan(glm::vec3(ROOM_SIZE / 2 + TRASH_CAN_SIZE / 2 + 0.01f, 0.0f, - ROOM_SIZE / 2));

	std::cout << "GUI initialized" << std::endl;
}

void GUI::AddButton()
{

		//we make the position of the buttons vary to get a line of buttons
		glm::vec3 position = Position(glm::vec3(BUTTON_RIGHT_START - (BUTTON_SIZE + BUTTON_SEPARATION), BUTTON_UP_START, BUTTON_DEPTH_OFFSET)).ToGLM()*MODULE_SIZE;

		//we create the new Button with the position
		d_p_button = new Button(position);

		//and add a RoomBot linked to this button at the same position
		PopRoomBot();
}

void GUI::PopRoomBot()
{
	std::cout << "popping new RoomBot in button" << std::endl;
	RoomBot* newRoomBot = new RoomBot(d_p_button->Position(), d_p_hemi1, d_p_hemi2, d_p_circle);

	d_roombots.push_back(newRoomBot);
	d_nRoomBots++;

}


void GUI::DroppedRoomBot()
{
	PopRoomBot();
	size_t i(0);
	while( i<d_nRoomBots)
	{
		if (d_roombots[i]->CloseEnough(d_trashCan->Position(), TRASH_CAN_SIZE))
		{
			delete d_roombots[i];
			d_roombots.erase(d_roombots.begin() + i);
			d_nRoomBots--;
		}
		i++;
	}
}

void const GUI::Render(const glm::mat4& VP)
{

	//we draw all the RoomBots
	for (size_t i(0); i < this->d_nRoomBots; i++)
	{
		d_roombots[i]->Draw(VP);
	}
	

		d_p_button->Draw(VP);

	//the TrashCan
	d_trashCan->Draw(VP);
	
	//and finally the LeapmotionPointer
	d_pointer.Draw(VP);
}


void GUI::CleanUp()
{
	d_p_button->CleanUp();

	//the three Models used for the RoomBots
	d_p_hemi1->CleanUp();
	delete d_p_hemi1;
	d_p_hemi2->CleanUp();
	delete d_p_hemi2;
	d_p_circle->CleanUp();
	delete d_p_circle;

	//delete all RoomBots
	for (size_t i(0); i < d_nRoomBots; i++)
	{
		delete d_roombots[i];
	}

	//the trashCan
	d_trashCan->CleanUp();
	delete d_trashCan;

	//and the pointer
	d_pointer.CleanUp();
}

void GUI::CheckForPinchedRoomBot()
{
	

	//we look for the first MovableRoomBot in pinching range from the LeapmotionPointer while it is pinching
	for (size_t i(0); i < this->d_nRoomBots; i++)
	{
		if (d_roombots[i]->CloseEnough(d_pointer.Position()) && d_pointer.Pinching())
		{
			std::cout << "pinched roombot " <<d_roombots[i]<< std::endl;
			d_pointer.AssignRoomBot((d_roombots[i]));
		}
	}
}

void GUI::UpdatePointer(bool mode)
{
	d_pointer.update(mode);
}

void GUI::Update(bool mode)
{
	UpdatePointer(mode);
	CheckForPinchedRoomBot();

}

void GUI::UpdateWorldMatrix(const glm::mat4& worldMatrix)
{
	d_pointer.UpdateWorldMatrix(worldMatrix);
}

