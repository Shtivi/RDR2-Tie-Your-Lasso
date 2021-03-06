#include "Main.h"

std::vector<BaseActionsController*> actionControllers;

void initActions()
{
	actionControllers.push_back(new AttachLassoController());
	actionControllers.push_back(new AttachHogtiedController());
	actionControllers.push_back(new AttachPickedUpController());
	actionControllers.push_back(new WindRopeController());
	actionControllers.push_back(new HangPedController());
	//actionControllers.push_back(new StowBodyController());
	actionControllers.push_back(new UnwindRopeController());
	actionControllers.push_back(new PullGallowLeverController());
	actionControllers.push_back(new TieGallowsNooseController());
}

void handleActions()
{
	std::vector<BaseActionsController*>::iterator it;

	for (it = actionControllers.begin(); it != actionControllers.end(); ++it)
	{
		(*it)->update();
	}
}