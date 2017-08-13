#include <iostream>
#include "button.h"

Button::Button(Widget* h, Topic t) : Widget(h, t)
{
}

void Button::HandleHelp()
{
	if (HasHelp()) {
		// offer help on the button
		std::cout << "Button Help" << std::endl;
	} else {
		HelpHandler::HandleHelp();
	}
}
