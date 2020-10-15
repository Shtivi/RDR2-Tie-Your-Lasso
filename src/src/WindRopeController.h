#pragma once

class WindRopeController : public BaseActionsController
{
public:
	WindRopeController();

private:
	AttachedRope* rope;

	Prompt* createActionPrompt();
	bool isAbleToExecute();
	void execute();
	void stop();
};