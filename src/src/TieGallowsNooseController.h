#pragma once

class TieGallowsNooseController : public BaseActionsController
{
public:
	TieGallowsNooseController();

private:
	Gallows* gallows;
	Ped victim;

	Prompt* createActionPrompt();
	void preparePrompt(Prompt* prompt);
	bool isAbleToExecute();
	void execute();
};