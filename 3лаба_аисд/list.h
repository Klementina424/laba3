#ifndef List_H
#define List_H
#include <string>

template<class T>
class List {
private:
	class nodeList;
	nodeList* _head;
	int _size;
public:
	List();
	~List();
	T pop();
	T pop(int);
	void push(T value);
	int getSize();
	void sort();
	const T operator[](const int index) const;
	};

template <class T>
class List<T>::nodeList {
private:
	T _value;
	nodeList* _next;
public:
	nodeList() : _next(nullptr) {};
	nodeList(T value, nodeList* next) :
		_value(value), _next(next) {}
	T getValue() {
		return _value;
	}
	void setValue(T value) {
		_value = value;
	}
	nodeList* getNext() {
		return _next;
	}
	void setNext(nodeList* next) {
		_next = next;
	}
};

template <class T>
List<T>::List() : _head(nullptr), _size(0) {}

template<class T>
List<T>::~List()
{
	while (_size > 0)
		this->pop();
}

template <class T>
T List<T>::pop() {
	if (_size == 0)
		throw;
	if (_size == 1) {
		T tempNextVal = _head->getValue();
		delete _head;
		_head = nullptr;
		this->_size = 0;
		return tempNextVal;
	}
	nodeList* temp = _head;
	while (temp->getNext()->getNext() != nullptr) temp = temp->getNext();
	T tempNextVal = temp->getNext()->getValue();
	delete temp->getNext();
	_size--;
	temp->setNext(nullptr);
	return tempNextVal;
}

template <class T>
T List<T>::pop(int index) {
	if (_size == 1 || _size == 0 || index == _size - 1) {
		return this->pop();
	}
	if (index == 0) {
		nodeList* temp = _head->getNext();
		T tempvalue = _head->getValue();
		_head = temp;
		_size--;
		return tempvalue;
	}
	nodeList* temp = _head;
	for (int i = 0; i < index - 1; i++)
		temp = temp->getNext();
	T tempNextVal = temp->getNext()->getValue();
	nodeList* tempNext = temp->getNext()->getNext();
	_size--;
	temp->setNext(tempNext);
	return tempNextVal;
}

template <class T>
void List<T>::push(T value) {
	if (_size == 0) {
		_head = new nodeList(value, nullptr);
		_size++;
		return;
	}
	nodeList* temp = _head;
	while (temp->getNext() != nullptr) temp = temp->getNext();
	temp->setNext(new nodeList(value, nullptr));
	_size++;
	return;
}

template <class T>
int List<T>::getSize() {
	return _size;
}

template <class T>
void List<T>::sort() {
	if (_size == 1 || _size == 0)
		return;
	nodeList* temp = _head;
	bool f = false;
	for (int i = 0; i < _size - 1; i++) {
		temp = _head;
		f = false;
		for (int j = 0; j < _size - 1 - i; j++) {
			if ((temp->getValue()).cost > (temp->getNext()->getValue()).cost) {
				T tempVal = temp->getValue();
				temp->setValue(temp->getNext()->getValue());
				temp->getNext()->setValue(tempVal);
				f = true;
			}
			temp = temp->getNext();
		}
		if (!f)
			return;
	}
}

template <class T>
const T List<T>::operator[](const int index) const{
	nodeList* it = _head;
	if (index < 0 || index > _size)
		throw;
	for (int i = 0; i < index; i++) {
		it = it->getNext();
	}
	return it->getValue();
}

#endif