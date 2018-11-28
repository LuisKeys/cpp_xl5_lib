#pragma once

#include "XL5Log.h"

#define XL5_STACK_OK 0
#define XL5_STACK_ERR_STACK_OVERFLOW 1

// stack object and related operations which can handle any type of object
template<class T>
class XL5Stack {
	public:
		// returns the size of the stack
		int size() {
			return _top;
		}

		// create a stack object
		void create(int max_size, int grow_size) {
			_stack_elements = (T*)malloc(sizeof(T));
			_max_size = max_size;
			_grow_size = grow_size;
		}

		// push the provided object to the stack
		int push(T data_object) {
			if(_top >= _alloc_space) {
				_alloc_space = _top + _grow_size;
				_stack_elements = (T*)realloc(_stack_elements, (_alloc_space) * sizeof(T));
			}

			_stack_elements[_top] = data_object;

			if(!_stack_elements){
				throw std::bad_alloc();
			}

			++_top;
			if(_top == _max_size) return XL5_STACK_ERR_STACK_OVERFLOW;

			return XL5_STACK_OK;
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
			if(position < 0 || _top == 0) return;
			_stack_elements[position] = value;
		}

		// insert a value in a given position
		void insert(int position, T value) {
			if(position < 0 || _top == 0) return;

			T* test = (T*)realloc(_stack_elements, (_top + 1) * sizeof(T));

			if(!test){
				throw std::bad_alloc();
			}

			++_top;

			for(int i = _top - 1; i >= 0; --i) {
				_stack_elements[i + 1] = _stack_elements[i];
			}

			_stack_elements[position] = value;
		}

		// return element at the given position
		T get(int position) {
			if(position < 0 || _top == 0) return (T)NULL;
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
			XL5Log log;
			for(int i = 0; i < _top; ++i) {
				log.value_line("Position", i, XL5Color::FG_YELLOW);
				log.text_line(" - ", XL5Color::FG_GREEN);
				log.value("Value", _stack_elements[i], XL5Color::FG_YELLOW);
		 	}
		}

	private:
		T* _stack_elements;
		int _top = 0;
		int _grow_size = 0;
		int _alloc_space = 0;
		int _max_size = 0;
};
