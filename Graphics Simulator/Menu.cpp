#include "Menu.h"


// Callback function associated to the 'Change lights' button of the lights tweak bar.
void TW_CALL ReinitCB(void *clientData)
{
	Menu *menu = static_cast<Menu *>(clientData); // scene pointer is stored in clientData
	menu->Init(true);                               // re-initialize the scene
}