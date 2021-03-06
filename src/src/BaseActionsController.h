#pragma once

enum ActivationType {
	TAP,
	HOLD
};

class BaseActionsController
{
private:
	Prompt* prompt;
	bool isInitialized;
	ActivationType activationType;
	bool isExecuting;
	float timeGap;
	Stopwatch stopwatch;
	bool allowExecute;

public:
	BaseActionsController(ActivationType activationType = ActivationType::TAP, float timeGap = 0);

	void update();

protected:
	virtual Prompt* createActionPrompt() = 0;
	virtual bool isAbleToExecute() = 0;
	virtual void preparePrompt(Prompt* prompt);
	virtual void execute() = 0;
	virtual void stop();

private:
	void setPrompt(Prompt* prompt);
};

#include "AttachLassoController.h";
#include "AttachHogtiedController.h";
#include "KickPedController.h";
#include "AttachPickedUpController.h";
#include "WindRopeController.h";
#include "HangPedController.h";
#include "StowBodyController.h";
#include "UnwindRopeController.h";
#include "PullGallowLeverController.h";
#include "TieGallowsNooseController.h";