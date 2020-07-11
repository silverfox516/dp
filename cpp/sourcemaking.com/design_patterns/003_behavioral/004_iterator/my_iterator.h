#ifndef _MY_ITERATOR_H_
#define _MY_ITERATOR_H_

template<typename Item>
class MyIterator {
public:
	virtual void begin() = 0;
	virtual void end() = 0;
	virtual void next() = 0;
	virtual bool isDone() const = 0;
	virtual Item currentItem() const = 0;

protected:
	MyIterator() {};
};

#endif /* _MY_ITERATOR_H_ */
