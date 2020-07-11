#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "widget.h"

class Button : public Widget {
public:
	Button(Widget* d, Topic t = NO_HELP_TOPIC);
	virtual void HandleHelp();
};

#endif	/* _BUTTON_H_ */
