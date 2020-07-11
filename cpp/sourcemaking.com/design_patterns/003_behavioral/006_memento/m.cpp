#include <stack>
#include <string>
#include <iostream> 
class Memento
{
public:
	Memento(std::string state) : mState(state) {}

public:
	std::string getState() const { return mState; }

private:
	std::string mState;
};

class Originator
{
public:
	void setState(std::string state) {
		mState = state;
		std::cout << "Originator::setState() " << state << std::endl;
	}

	void setMemento(Memento *m) {
		if (m) {
			mState = m->getState();
			delete m;
			std::cout << "Originator::setMemento() " << mState << std::endl;
		}
	}

	Memento* createMemento() {
		std::cout << "Originator::createMemento() " << mState << std::endl;
		return new Memento(mState);
	}

private:
	std::string mState;
};

class Caretaker
{
public:
	void pushMemento(Memento* m) { mStack.push(m); }
	Memento* popMemento() { Memento* m = mStack.top(); mStack.pop(); return m; }

private:
	std::stack<Memento*> mStack;
};

int main(void)
{
	Caretaker caretaker;
	Originator *originator = new Originator();

	originator->setState("state1");
	caretaker.pushMemento(originator->createMemento());

	originator->setState("state2");
	caretaker.pushMemento(originator->createMemento());

	originator->setMemento(caretaker.popMemento());
	originator->setMemento(caretaker.popMemento());

	delete originator;

	return 0;
}
