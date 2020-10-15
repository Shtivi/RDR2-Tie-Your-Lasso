#pragma once

class AttachHogtiedController : public BaseActionsController
{
public:
	AttachHogtiedController();

private:
	Ped currentTarget;

	Prompt* createActionPrompt();
	bool isAbleToExecute();
	void preparePrompt(Prompt* prompt);
	void execute();
};