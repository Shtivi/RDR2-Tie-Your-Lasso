#pragma once

class UnwindRopeController : public BaseActionsController
{
public:
	UnwindRopeController();

private:
	Rope* rope;

	Prompt* createActionPrompt();
	bool isAbleToExecute();
	void execute();
	void stop();
};