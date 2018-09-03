#ifndef _MY_LIST_ITERATOR_H_
#define _MY_LIST_ITERATOR_H_

#include "my_list.h"
#include "my_iterator.h"

template<typename Item>
class MyListIterator : public MyIterator<Item> {
public:
	MyListIterator(MyList<Item>* myList);

public:
	virtual void begin();
	virtual void end();
	virtual void next();
	virtual bool isDone() const;
	virtual Item currentItem() const;

private:
	MyList<Item>* mMyList;
	long mCurrent;
};

template<typename Item>
MyListIterator<Item>::MyListIterator(MyList<Item>* myList)
	: mCurrent(0), mMyList(myList) {
}

template<typename Item>
void MyListIterator<Item>::begin() {
	mCurrent = 0;
}

template<typename Item>
void MyListIterator<Item>::end() {
	mCurrent = mMyList->count();
}

template<typename Item>
void MyListIterator<Item>::next() {
	if (isDone())
		return;

	mCurrent++;
}

template<typename Item>
bool MyListIterator<Item>::isDone() const {
	if (mCurrent >= mMyList->count())
		return true;
	return false;
}

template<typename Item>
Item MyListIterator<Item>::currentItem() const {
	return mMyList->get(mCurrent);
}

#endif /* _MY_LIST_ITERATOR_H_ */
