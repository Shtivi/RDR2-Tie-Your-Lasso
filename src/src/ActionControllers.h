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

public:
	BaseActionsController(ActivationType activationType = ActivationType::TAP);

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

class AttachPickedUpController : public BaseActionsController
{
public:
	AttachPickedUpController();

private:
	Ped currentTarget;

	Ped findCarriedPed();
	Prompt* createActionPrompt();
	bool isAbleToExecute();
	void preparePrompt(Prompt* prompt);
	void execute();
};

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