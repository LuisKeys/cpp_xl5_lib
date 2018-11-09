#pragma once

#define XL_STACK_OK 0
#define XL_STACK_ERR_STACK_OVERFLOW 1

// stack object and related operations which can handle any type of object
template<class T>
class XLStack {
	public:
		// returns the size of the stack
		int size() {
			return _top;
		}

		// create a stack object
		void create(int max_size) {
			_stack_elements = (T*)malloc(sizeof(T));
			++_top;
			_max_size = max_size;
		}

		// push the provided object to the stack
		int push(T data_object) {
			T* test = (T*)realloc(_stack_elements, (_top + 1) * sizeof(T));

			// if(!test){
			// 	throw std::bad_alloc();
			// }

			// _stack_elements[_top] = data_object;
			++_top;
			if(_top == _max_size) return XL_STACK_ERR_STACK_OVERFLOW;

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
			 free(_stack_elements);
			_stack_elements = (T*)malloc(sizeof(T));
			_top = 1;
		}

		// drop the stack from memory
		void drop() {
			free(_stack_elements);
		}

	private:
		T* _stack_elements;
		int _top = 0;
		int _max_size = 0;
};
