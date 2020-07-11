#include <iostream>
#include "my_list_iterator.h"
#include "my_list.h"
#include "my_iterator_ptr.h"
#include "my_list_traverser.h"

class PrintMyListInt : public MyListTraverser<int> {
public:
	PrintMyListInt(MyList<int>* list, long total)
		: MyListTraverser(list), mTotal(total), mCount(0) {}

protected:
	bool processItem(const int item) {
		mCount++;
		std::cout << "traversing ... " << item << std::endl;
		return mCount < mTotal;
	}

private:
	long mTotal;
	long mCount;
};

int main(void)
{
	MyList<int> l;
	l.pushBack(1);
	l.pushBack(1);
	l.pushBack(3);
	l.pushBack(5);
	l.debugList();
	l.popBack();
	l.popBack();
	l.debugList();
	l.popBack();
	l.popBack();
	l.popBack();
	l.popBack();
	l.debugList();
	l.pushBack(7);
	l.pushBack(9);
	l.pushBack(3);
	l.pushBack(100);
	l.pushBack(99);
	l.pushBack(77);
	l.pushBack(44);
	l.debugList();

	std::cout << "debug by iterator..." << std::endl;
	MyListIterator<int> iter(&l);
	for (iter.begin(); !iter.isDone(); iter.next()) {
		std::cout << iter.currentItem() << std::endl;
	}

	std::cout << "debug by iterator ptr..." << std::endl;
	MyIteratorPtr<int> iterPtr(l.createIterator());
	for (iterPtr->begin(); !iterPtr->isDone(); iterPtr->next()) {
		std::cout << (*iterPtr).currentItem() << std::endl;
	}

	std::cout << "traverser test..." << std::endl;
	PrintMyListInt t(&l, 5);
	t.traverse();

	return 0;
}
