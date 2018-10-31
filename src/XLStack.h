#pragma once

#define XL_STACK_OK 0
#define XL_STACK_ERR_STACK_OVERFLOW 1

template<class T>
class XLStack {
	public:
		int size() {
			return _size;
		}

		void create(int size) {
			_stack_elements = new T[size];
			_size = size;
		}

		int push(T data_object) {
			_stack_elements[_top] = data_object;
			++_top;
			if(_top == _size) return XL_STACK_ERR_STACK_OVERFLOW;

			return XL_STACK_OK;
		}

		T pop() {	
			--_top;
			if(_top < 0) return NULL;
			return _stack_elements[_top];
		}

		void clear() {
			_top = 0;
		}

		void drop() {
			delete _stack_elements;
		}

	private:		
		T* _stack_elements;
		int _top = 0;
		int _size = 0;
};