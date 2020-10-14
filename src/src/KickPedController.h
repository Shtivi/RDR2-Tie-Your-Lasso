#pragma once

class KickPedController : public BaseActionsController
{
public:
	KickPedController();

private:
	Ped currentTarget;

	Prompt* createActionPrompt();
	bool isAbleToExecute();
	void preparePrompt(Prompt* prompt);
	void execute();
};