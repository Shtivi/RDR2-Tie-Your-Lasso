#pragma once

class WindRopeController : public BaseActionsController
{
public:
	WindRopeController();

private:
	Rope* rope;

	Prompt* createActionPrompt();
	bool isAbleToExecute();
	void execute();
	void stop();
};