#pragma once

class PullGallowLeverController : public BaseActionsController
{
public:
	PullGallowLeverController();

private:
	Prompt* createActionPrompt();
	bool isAbleToExecute();
	void execute();
};