#pragma once

class PullGallowLeverController : public BaseActionsController
{
public:
	PullGallowLeverController();

private:
	Gallows* gallows;

	Prompt* createActionPrompt();
	void preparePrompt(Prompt* prompt);
	bool isAbleToExecute();
	void execute();
};