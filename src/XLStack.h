#pragma once

#include "XLLog.h"

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
			_max_size = max_size;
		}

		// push the provided object to the stack
		int push(T data_object) {
			T* test = (T*)realloc(_stack_elements, (_top + 1) * sizeof(T));
			_stack_elements[_top] = data_object;

			if(!test){
				throw std::bad_alloc();
			}

			// _stack_elements[_top] = data_object;
			++_top;
			if(_top == _max_size) return XL_STACK_ERR_STACK_OVERFLOW;

			return XL_STACK_OK;
		}

		// pop the top most object from the stack
		T pop() {
			--_top;
			if(_top < 0) return (T)NULL;
			return _stack_elements[_top];
		}

		// pop an element from given position
		// similar to pop, but deom any position
		T pop(int position) {
			if(position < 0 || _top == 0) return (T)NULL;

			T element = _stack_elements[position];

			for(int i = position; i < _top - 1; ++i) {
				_stack_elements[i] = _stack_elements[i + 1];
			}

			--_top;
			if(_top < 0) return (T)NULL;
			return element;
		}

		// set element at the given position
		void set(int position, T value) {
			_stack_elements[position] = value;
		}
		// return element at the given position

		T get(int position) {
			return _stack_elements[position];
		}

		// clear the stack
		void clear() {
			 free(_stack_elements);
			_stack_elements = (T*)malloc(sizeof(T));
			_top = 0;
		}

		// drop the stack from memory
		void drop() {
			free(_stack_elements);
		}

		// Print stack content for debug purposes
		// Thie method only prints int or float values
		void print() {
			XLLog log;
			for(int i = 0; i < _top; ++i) {
				log.value_line("Position", i, XLColor::FG_YELLOW);
				log.text_line(" - ", XLColor::FG_GREEN);
				log.value("Value", _stack_elements[i], XLColor::FG_YELLOW);
		 	}
		}

	private:
		T* _stack_elements;
		int _top = 0;
		int _max_size = 0;
};
