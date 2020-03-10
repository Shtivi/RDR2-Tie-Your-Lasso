#pragma once

class Prompt
{
	private: 
		bool isEnabled;
		int handle;
		const char* text;
		Hash control;
		Entity targetEntity;

	public: Prompt(const char* text, Hash control);

	public: 
		Entity getTargetEntity();
		bool getIsEnabled();

		void setText(const char* text);
		void setControl(Hash control);
		void setTargetEntity(Entity entity);
		void setPriority(int priority);

		bool isActivatedByPlayer();
		void show();
		void hide();

	private:
		void update();
};