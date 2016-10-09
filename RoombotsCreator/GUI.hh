#pragma once

#include "Button.hh"
#include "LeapmotionPointer.hh"
#include "Position.hh"
#include "TrashCan.hh"

/**The Graphic User Interface (GUI) regroups everything related to the manipulation of the environment.
It notably handles the LeapmotionPointer, the Buttons, the TrashCan and all MovableRoomBots.
It is also the link between all those elements*/
class GUI
{
	Button*          d_p_button;        ///<The Buttons contained in the scene
	std::vector<RoomBot*>      d_roombots;     ///<The RoomBots contained in the scene
	size_t                              d_nRoomBots = 0;///<The number of RoomBots in the scene
	LeapmotionPointer                   d_pointer;        ///<The pointer using the Leapmotion device
	OBJModel*                           d_p_hemi1;        ///<The pointer to the first hemisphere Model
	OBJModel*                           d_p_hemi2;        ///<The pointer to the second hemisphere Model
	OBJModel*                           d_p_circle;       ///<The pointer to the circle Model
	TrashCan*                           d_trashCan;

public:
	
	/**Initializes the Graphic User Interface by initializing the LeapmotionPointer and adding Buttons*/
	void Init();

	/**Updates the positions of the RoomBots and the LeapmotionPointer
	\arg \c mode The current Simulator mode.*/
	void Update(bool mode);

	/**Updates the scene's world matrix. 
	  Used to change the behaviour of the LeapmotionPointer depending on the current mode*/
	void UpdateWorldMatrix(const glm::mat4& worldMatrix);

	/**Renders (draws) the Buttons, the RoomBots and the LeapmotionPointer*/
	void const Render(const glm::mat4& VP);


	/**Notifies the GUI a RoomBot has been dropped and pops a new one 
	  on the corresponding button if the ID is valid
	  \arg \c buttonID The ID of the Button from which the dropped MovableRoomBot comes*/
	void DroppedRoomBot();


	/**Cleans up everything*/
	void CleanUp();

private:

	/**Adds a button to the interface (max 3 for now)
	\arg \c  p_RoomBot A pointer to the RoomBot that will be used to pop new 
	 MovableRoomBots from the added Button*/
	void AddButton();

	/**Checks for every RoomBot if it is being pinched by the LeapmotionPointer*/
	void CheckForPinchedRoomBot();

	/**Updates the LeapmotionPointer's position depending on the Leapmotion Controller's data
	\arg \c mode the current Simulator mode*/
	void UpdatePointer(bool mode);

	void PopRoomBot();
};