#ifndef _MY_LIST_H_
#define _MY_LIST_H_

#include <iostream>
#include "my_iterator.h"
#include "my_list_iterator.h"

template<typename Item>
class MyListIterator;

template <typename Item>
class AbstractMyList {
public:
	virtual MyIterator<Item>* createIterator() = 0;
private:
};

template<typename Item>
class MyList : public AbstractMyList<Item> {
public:
	MyList(long size = 100);
	~MyList();

public:
	long count() const;
	void pushBack(Item item);
	void popBack();
	Item get(long pos);
	virtual MyIterator<Item>* createIterator();

	void debugList() const;

private:
	long mSize;
	long mCount;
	int *mList;
};

template<typename Item>
MyList<Item>::MyList(long size)
	: mSize(size), mCount(0), mList(new Item(size)) {
	std::cout << "MyList() : mSize(" << size << ")" << std::endl;
}

template<typename Item>
MyList<Item>::~MyList() {
	delete mList;
}

template<typename Item>
long MyList<Item>::count() const {
	return mCount;
}

template<typename Item>
void MyList<Item>::pushBack(Item item) {
	if (mCount >= mSize) {
		std::cout << "count is over size" << std::endl;
		return;
	}

	mList[mCount++] = item;
	std::cout << "pushed " << item << " at " << mCount - 1 << std::endl;
}

template<typename Item>
void MyList<Item>::popBack() {
	if (mCount <= 0) {
		std::cout << "no item in list" << std::endl;
		return;
	}

	--mCount;
	std::cout << "poped " << mList[mCount] << " at " << mCount << std::endl;
}

template<typename Item>
Item MyList<Item>::get(long pos) {
	if (pos >= mCount) {
		std::cout << "wrong access, handle" << std::endl;
	}

	return mList[pos];
}

template <typename Item>
MyIterator<Item>* MyList<Item>::createIterator() {
	return new MyListIterator<Item>(this);
}

template<typename Item>
void MyList<Item>::debugList() const {
	std::cout << "\ndebug list..." << std::endl;
	for (int i = 0; i < mCount; i++) {
		std::cout << " " << mList[i];
	}
	std::cout << "\n\n" ;
}

#endif /* _MY_LIST_H_ */
