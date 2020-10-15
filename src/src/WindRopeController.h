#pragma once

class WindRopeController : public BaseActionsController
{
public:
	WindRopeController();

private:
	Rope* rope;

	Prompt* createActionPrompt();
	bool isAbleToExecute();
	void preparePrompt(Prompt* prompt);
	void execute();
	void stop();
};