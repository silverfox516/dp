#ifndef _MY_ITERATOR_PTR_H_
#define _MY_ITERATOR_PTR_H_

#include <iostream>
#include "my_iterator.h"

template <typename Item>
class MyIteratorPtr {
public:
	MyIteratorPtr(MyIterator<Item>* iter) : mIter(iter) {}
	~MyIteratorPtr();
	MyIterator<Item>* operator->() { return mIter; }
	MyIterator<Item>& operator*() { return *mIter; }

private:
	MyIteratorPtr(const MyIteratorPtr&);
	MyIteratorPtr& operator=(const MyIteratorPtr&);

private:
	MyIterator<Item>* mIter;
};

template <typename Item>
MyIteratorPtr<Item>::~MyIteratorPtr() {
	delete mIter;
	std::cout << "~MyIteratorPtr(), deleted mIter" << std::endl;	
}

#endif /* _MY_ITERATOR_PTR_H_ */
