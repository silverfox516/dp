#ifndef _DIALOG_H_
#define _DIALOG_H_

#include "widget.h"

class Dialog : public Widget {
public:
	Dialog(HelpHandler* h, Topic t = NO_HELP_TOPIC);
	virtual void HandleHelp();
};

#endif	/* _DIALOG_H_ */

