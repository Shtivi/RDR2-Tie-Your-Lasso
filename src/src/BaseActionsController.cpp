#include "Main.h"

BaseActionsController::BaseActionsController()
{
	isInitialized = false;
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
			execute();
		}
	}
	else
	{
		prompt->hide();
	}
}

void BaseActionsController::preparePrompt(Prompt* prompt)
{
}

void BaseActionsController::setPrompt(Prompt* prompt)
{
	this->prompt = prompt;
}