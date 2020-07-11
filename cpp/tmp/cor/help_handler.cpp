#include "help_handler.h"

HelpHandler::HelpHandler(HelpHandler *h, Topic t)
	: _successor(h), _topic(t)
{
}

bool HelpHandler::HasHelp()
{
	return _topic != NO_HELP_TOPIC;
}

void HelpHandler::SetHandler(HelpHandler* h, Topic t)
{
	_successor = h;
	_topic = t;
}

void HelpHandler::HandleHelp()
{
	if (_successor != 0) {
		_successor->HandleHelp();
	}
}
