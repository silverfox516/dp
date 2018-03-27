#ifndef _COLLEAGUE_H_
#define _COLLEAGUE_H_

#include <string>
#include <iostream>
#include "mediator.h"

class Mediator;

class Colleague
{
public:
	virtual void sendMessage(std::string msg) = 0;
	virtual void receiveMessage(std::string msg) = 0;
protected:
	Colleague();
};

class ConcreteColleague : public Colleague
{
public:
	virtual void sendMessage(std::string msg);
	virtual void receiveMessage(std::string msg);
	ConcreteColleague(Mediator* m, int id);

private:
	Mediator* mMediator;
	int mId;
};

ConcreteColleague::ConcreteColleague(Mediator* m, int id) : mMediator(m), mId(id)
{
}

void ConcreteColleague::sendMessage(std::string msg)
{
	mMediator->receiveMessage(msg, this);
	std::cout << mId << " Sent message " << msg << std::endl;
}

void ConcreteColleague::receiveMessage(std::string msg)
{
	std::cout << mId << " Got message " << msg << std::endl;
}

#endif /* _COLLEAGUE_H_ */
