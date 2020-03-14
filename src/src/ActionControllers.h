#pragma once

class BaseActionsController
{
private:
	Prompt* prompt;
	bool isInitialized;

public:
	BaseActionsController();

	void update();

protected:
	virtual Prompt* createActionPrompt() = 0;
	virtual bool isAbleToExecute() = 0;
	virtual void preparePrompt(Prompt* prompt);
	virtual void execute() = 0;

private:
	void setPrompt(Prompt* prompt);
};

class AttachLassoController : public BaseActionsController
{
public:
	AttachLassoController();

private:
	Prompt* createActionPrompt();
	bool isAbleToExecute();
	void execute();
};

class AttachHogtiedController : public BaseActionsController
{
public:
	AttachHogtiedController();

private:
	Ped currentTarget;

	Prompt* createActionPrompt();
	bool isAbleToExecute();
	void preparePrompt(Prompt* prompt);
	void execute();
};

class KickPedController : public BaseActionsController
{
public:
	KickPedController();

private:
	Ped currentTarget;

	Prompt* createActionPrompt();
	bool isAbleToExecute();
	void preparePrompt(Prompt* prompt);
	void execute();
};