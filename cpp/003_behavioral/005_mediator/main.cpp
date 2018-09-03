//#include "mediator.h"
//#include "colleague.h"

#include <iostream>
#include <list>

class Mediator;

class Colleague
{
public:
	virtual void sendMessage(std::string msg) = 0;
	virtual void receiveMessage(std::string msg) = 0;
protected:
	Colleague() {}
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

class Mediator 
{
public:
	virtual void receiveMessage(std::string msg, Colleague *colleague) = 0;
	virtual void add(Colleague* colleague) = 0;
protected:
	Mediator() {}
};

class ConcreteMediator : public Mediator
{
public:
	virtual void receiveMessage(std::string msg, Colleague *colleague);
	virtual void add(Colleague* colleague);

private:
	std::list<Colleague*> colleagues;
};


ConcreteColleague::ConcreteColleague(Mediator* m, int id) : mMediator(m), mId(id)
{
	mMediator->add(this);
}

void ConcreteColleague::sendMessage(std::string msg)
{
	std::cout << mId << " Sent message " << msg << std::endl;
	mMediator->receiveMessage(msg, this);
}

void ConcreteColleague::receiveMessage(std::string msg)
{
	std::cout << mId << " Got message " << msg << std::endl;
}

void ConcreteMediator::receiveMessage(std::string msg, Colleague* colleague)
{
	std::list<Colleague*>::iterator iter;
	for (iter = colleagues.begin(); iter != colleagues.end(); ++iter) {
		if (colleague != *iter)
			(*iter)->receiveMessage(msg);
	}
}

void ConcreteMediator::add(Colleague* colleague)
{
	colleagues.push_back(colleague);
}

int main(void)
{
	Mediator *m = new ConcreteMediator;
	Colleague *c1 = new ConcreteColleague(m, 1);
	Colleague *c2 = new ConcreteColleague(m, 2);
	Colleague *c3 = new ConcreteColleague(m, 3);

	c1->sendMessage("hello");
	c2->sendMessage("yeah");
	return 0;
}
