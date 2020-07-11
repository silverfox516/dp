#ifndef _WIDGET_H_
#define _WIDGET_H_

#include "help_handler.h"

class Widget : public HelpHandler {
protected:
	Widget(Widget* parent, Topic t = NO_HELP_TOPIC);
};

#endif	/* _WIDGET_H_ */
