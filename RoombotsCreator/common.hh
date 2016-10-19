
///This file simply regroups includes of external libraries used in most other files to leave said files clean 
#pragma once

#include "Libraries\glew\glew.h" //for OpenGL graphics operations
#include "Libraries\glew\wglew.h" //for OpenGL graphics operations
#include "Libraries\freeglut\freeglut.h" //for window and OpenGL context creation
#include "Libraries\glm\glm.hpp" //for mathematical operations used in OpenGL
#include "Libraries\glm\gtc\matrix_transform.hpp"//for transformations (matrices)
#include "Libraries\glm\gtx\transform.hpp" 
#include "Libraries\glm\gtx\euler_angles.hpp"
#include "Libraries\soil\SOIL.h"//for texture loading

#include "Libraries\wgl\wglext.h"
#include "Libraries\wgl\glext.h"

#include "Libraries\OVR\OVR_CAPI_GL.h"//Oculus' library
#include "Libraries\OVR\Extras\OVR_Math.h"

#include <Windows.h>
#include "Libraries\wgl\wglext.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>
#include <math.h>
#include <ctime>
#include <stdexcept>


#include "Libraries\Leap\Leap.h"


///All the following macros are in meters
#define M_PI       3.14159265358979323846f

#define MODULE_SIZE 0.12f ///<The size of a a half of a Roombots module
#define EYES_POSITION (29 * MODULE_SIZE / 2)///< The vertical position of the camera. It must be an odd multiple of MODULE_SIZE / 2
#define ROOM_SIZE 5.0f ///<The size of the room
#define BUTTON_SIZE 0.5f ///<The size of a button
#define BUTTON_SEPARATION 1.0f ///<The horizontal distance between two buttons
#define BUTTON_UP_START -0.3f ///<The vertical point where the buttons are positioned 
#define BUTTON_DEPTH_OFFSET -1.0f ///<The depth point where the buttons are positioned
#define BUTTON_RIGHT_START 1.3f ///<The horizontal point from where the buttons are drawn
#define LEAP_POINTER_SIZE 0.5f ///<The size of the LeapmotionPointer
#define TABLE_HEIGHT -0.1f ///<The height of the table on which the Roombots are dropped
#define COORDINATE_SYSTEM_SCALE_CONVERSION 0.005f ///<A conversion factor to scale the data 
                                                  ///<coming from the Leapmotion device
                                                  ///<to fit the Room-View mode characteristics
#define BOX_COORDINATE_SYSTEM_SCALE_CONVERSION 0.016f ///<A conversion factor to scale the data 
													  ///<coming from the Leapmotion device
													  ///<to fit the Box-View mode characteristics
#define PINCHING_LIMIT 0.8f ///<The minimal pinching value to consider that the hand is pinching
#define DRAG_RADIUS 0.3f ///<The minimal distance to grab a Structure
#define TRASH_CAN_SIZE 2.0f///<The size of the TrashCan





