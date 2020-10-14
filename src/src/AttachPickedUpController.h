#pragma once

class AttachPickedUpController : public BaseActionsController
{
public:
	AttachPickedUpController();

private:
	Ped currentTarget;

	Ped findCarriedPed();
	Prompt* createActionPrompt();
	bool isAbleToExecute();
	void preparePrompt(Prompt* prompt);
	void execute();
};