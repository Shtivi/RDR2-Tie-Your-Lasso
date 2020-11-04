#pragma once

class StowBodyController : public BaseActionsController 
{
public:
	StowBodyController();

private:
	Vehicle wagon;

	Prompt* createActionPrompt();
	void preparePrompt(Prompt* prompt);
	bool isAbleToExecute();
	void execute();
};