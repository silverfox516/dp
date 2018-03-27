#ifndef _MY_LIST_TRAVERSER_H_
#define _MY_LIST_TRAVERSER_H_

#include <iostream>
#include "my_list.h"
#include "my_iterator.h"

template <typename Item>
class MyListTraverser {
public:
	MyListTraverser(MyList<Item>* list);
	~MyListTraverser();
	virtual bool traverse();

protected:
	virtual bool processItem(const Item item) = 0;

private:
	MyIteratorPtr<Item> mIterPtr;
};

template <typename Item>
MyListTraverser<Item>::MyListTraverser(MyList<Item>* list)
	: mIterPtr(list->createIterator()) {
	std::cout << "MyListTraverser()" << std::endl;
}

template <typename Item>
MyListTraverser<Item>::~MyListTraverser() {
	std::cout << "~MyListTraverser()" << std::endl;
}

template <typename Item>
bool MyListTraverser<Item>::traverse() {
	bool result = false;

	for (mIterPtr->begin(); !mIterPtr->isDone(); mIterPtr->next()) {
		result = processItem(mIterPtr->currentItem());
		if (false == result)
			break;
	}
	return result;
}

#endif /* _MY_LIST_TRAVERSER_H_ */
