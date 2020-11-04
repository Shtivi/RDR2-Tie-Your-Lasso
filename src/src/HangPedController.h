#pragma once

class HangPedController : public BaseActionsController
{
public:
	HangPedController();

private:
	Ped victim;
	Vector3 hangFrom;
	bool shouldDrop;

	Prompt* createActionPrompt();
	bool isAbleToExecute();
	void preparePrompt(Prompt* prompt);
	void execute();
	void reset();
};