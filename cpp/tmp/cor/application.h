#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include "help_handler.h"

class Application : public HelpHandler {
public:
	Application(Topic t) : HelpHandler(0, t) {}
	virtual void HandleHelp();
};

#endif	/* _APPLICATION_H_ */

