#ifndef _MEDIATOR_H_
#define _MEDIATOR_H_

#include <string>
#include <list>
#include "colleague.h"

class Mediator 
{
public:
	virtual void receiveMessage(std::string msg, Colleague *colleague) = 0;
	virtual void add(Colleague* colleague) = 0;
protected:
	Mediator();
};

class ConcreteMediator : public Mediator
{
public:
	virtual void receiveMessage(std::string msg, Colleague *colleague);
	virtual void add(Colleague* colleague);

private:
	std::list<Colleague*> colleagues;
};

void ConcreteMediator::receiveMessage(std::string msg, Colleague* colleague)
{
	std::list<Colleague*>::iterator iter;
	for (iter = colleagues.begin(); iter != colleagues.end(); ++iter) {
		(*iter)->receiveMessage(msg);
	}
}

void ConcreteMediator::add(Colleague* colleague)
{
	colleagues.push_back(colleague);
}

#endif /* _MEDIATOR_H_ */
