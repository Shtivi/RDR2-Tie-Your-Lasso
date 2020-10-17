#include "Main.h"

BaseActionsController::BaseActionsController(ActivationType activationType)
{
	isInitialized = false;
	prompt = NULL;
	this->activationType = activationType;
	isExecuting = false;
}

void BaseActionsController::update()
{
	if (!isInitialized)
	{
		setPrompt(createActionPrompt());
		isInitialized = true;
	}

	if (isAbleToExecute())
	{
		preparePrompt(prompt);
		prompt->show();

		if (prompt->isActivatedByPlayer())
		{
			isExecuting = true;
			execute();
		}
	}
	else
	{
		prompt->setTargetEntity(NULL);
		prompt->hide();
	}

	if (activationType == ActivationType::HOLD && !prompt->isControlPressed() && isExecuting)
	{
		stop();
		isExecuting = false;
	}
}

void BaseActionsController::preparePrompt(Prompt* prompt)
{
}

void BaseActionsController::setPrompt(Prompt* prompt)
{
	this->prompt = prompt;
}

void BaseActionsController::stop() 
{
}