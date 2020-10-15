#include "Main.h"

std::vector<BaseActionsController*> actionControllers;

void initActions()
{
	actionControllers.push_back(new AttachLassoController());
	actionControllers.push_back(new AttachHogtiedController());
	//actionControllers.push_back(new KickPedController());
	actionControllers.push_back(new AttachPickedUpController());
	actionControllers.push_back(new WindRopeController());
	actionControllers.push_back(new HangPedController());
}

void handleActions()
{
	std::vector<BaseActionsController*>::iterator it;

	for (it = actionControllers.begin(); it != actionControllers.end(); ++it)
	{
		(*it)->update();
	}
}