#include "Main.h"

Prompt::Prompt(const char* text, Hash control)
{
	this->handle = UI::_0x04F97DE45A519419(); // _UIPROMPT_REGISTER_BEGIN
	this->setControl(control);
	this->setText(text);
	this->setTargetEntity(NULL);
	UI::_0xF7AA2696A22AD8B9(this->handle); // _UIPROMPT_REGISTER_END

	this->isEnabled = false;
}

void Prompt::setText(const char* text)
{
	this->text = text;
	const char* textLabel = UI::_CREATE_VAR_STRING(10, "LITERAL_STRING", text);
	UI::_0x5DD02A8318420DD7(this->handle, (Any*)textLabel); // _UIPROMPT_SET_TEXT
}

void Prompt::setControl(Hash control)
{
	this->control = control;
	UI::_0xB5352B7494A08258(this->handle, control); // _UIPROMPT_SET_CONTROL_ACTION
}

Entity Prompt::getTargetEntity()
{
	return this->targetEntity;
}

void Prompt::setTargetEntity(Entity target)
{
	this->targetEntity = target;

	if (!target)
	{
		// needs testing
		UI::_0x2F11D3A254169EA4(this->handle, 0, 0);
		return;
	}

	int targetEntityGroupId = UI::_0xB796970BD125FCE8(target); // _UIPROMPT_GET_GROUP_ID_FOR_TARGET_ENTITY 
	if (targetEntityGroupId)
	{
		UI::_0x2F11D3A254169EA4(this->handle, targetEntityGroupId, 0); // _UIPROMPT_SET_GROUP
	}
}

bool Prompt::isActivatedByPlayer()
{
	if (!this->isEnabled)
	{
		return false;
	}

	// Validate that this is the correct native
	if (CONTROLS::IS_CONTROL_JUST_RELEASED(0, this->control))
	{
		return true;
	}

	return false;
}

void Prompt::update()
{
	UI::_0x8A0FB4D03A630D21(this->handle, isEnabled); // _UIPROMPT_SET_ENABLED
	UI::_0x71215ACCFDE075EE(this->handle, isEnabled); // _UIPROMPT_SET_VISIBLE
}