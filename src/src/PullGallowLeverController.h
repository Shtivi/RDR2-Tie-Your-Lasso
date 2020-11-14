#pragma once

class PullGallowLeverController : public BaseActionsController
{
public:
	PullGallowLeverController();

private:
	Gallow* gallows;

	Prompt* createActionPrompt();
	void preparePrompt(Prompt* prompt);
	bool isAbleToExecute();
	void execute();
};