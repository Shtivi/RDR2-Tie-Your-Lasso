#pragma once

class Prompt
{
	public:
		bool isEnabled;

	private: 
		int handle;
		const char* text;
		Hash control;
		Entity targetEntity;

	public: Prompt(const char* text, Hash control);

	public: 
		Entity getTargetEntity();
		void setText(const char* text);
		void setControl(Hash control);
		void setTargetEntity(Entity entity);

		bool isActivatedByPlayer();
		void update();
};