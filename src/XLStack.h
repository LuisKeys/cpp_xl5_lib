#pragma once

#define XL_STACK_OK 0
#define XL_STACK_ERR_STACK_OVERFLOW 1

// stack object and related operations which can handle any type of object
template<class T>
class XLStack {
	public:
		// returns the size of the stack
		int size() {
			return _size;
		}

		// create a stack object with the provided size
		void create(int size) {
			_stack_elements = new T[size];
			_size = size;
		}

		// push the provided object to the stack
		int push(T data_object) {
			_stack_elements[_top] = data_object;
			++_top;
			if(_top == _size) return XL_STACK_ERR_STACK_OVERFLOW;

			return XL_STACK_OK;
		}

		// pop the top most object from the stack
		T pop() {
			--_top;
			if(_top < 0) return NULL;
			return _stack_elements[_top];
		}

		// clear the stack
		void clear() {
			_top = 0;
		}

		// drop the stack from memory
		void drop() {
			delete _stack_elements;
		}

	private:
		T* _stack_elements;
		int _top = 0;
		int _size = 0;
};
