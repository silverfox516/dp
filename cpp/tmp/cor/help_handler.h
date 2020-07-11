#ifndef _HELP_HANDLER_H_
#define _HELP_HANDLER_H_

typedef int Topic;
const Topic NO_HELP_TOPIC = -1;

class HelpHandler {
public:
	HelpHandler(HelpHandler* = 0, Topic = NO_HELP_TOPIC);
	virtual bool HasHelp();
	virtual void SetHandler(HelpHandler*, Topic);
	virtual void HandleHelp();
private:
	HelpHandler* _successor;
	Topic _topic;
};

#endif	/* _HELP_HANDLER_H_ */
