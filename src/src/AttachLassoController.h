#pragma once

class AttachLassoController : public BaseActionsController
{
private:
	Entity lassoTarget;

public:
	AttachLassoController();

private:
	Prompt* createActionPrompt();
	bool isAbleToExecute();
	void execute();
};