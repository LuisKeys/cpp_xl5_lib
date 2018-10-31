#pragma once

#include "XLLog.h"

#define XL_QUEUE_OK 0
#define XL_QUEUE_ERR_QUEUE_OVERFLOW 1

template<class T>
class XLQueue {
	public:
		int size() {
			return _size;
		}

		void create(int size) {
			_queue_elements = new T[size];
			_size = size;
			_head = 0;
			_tail = 0;
		}

		int enqueue(T data_object) {
			if(_tail < _head)
				if(_tail == _head - 1)
					return XL_QUEUE_ERR_QUEUE_OVERFLOW;

			if(_tail == _size)
				return XL_QUEUE_ERR_QUEUE_OVERFLOW;

			_queue_elements[_tail] = data_object;
			if(_tail == _size) {
				_tail = 1;
			}
			else {
				_tail++;
			}

			return XL_QUEUE_OK;
		}

		T dequeue() {				
			if(_head == _tail) return (T)NULL;

			T element = _queue_elements[_head];
			
			if(_head == _size) {
				_head = 1;
			}
			else {
				_head++;
			}

			return element;
		}

		void clear() {
			_head = 0;
			_tail = 0;
		}

		void drop() {
			delete _queue_elements;
		}

	private:		
		T* _queue_elements;
		int _head = 0;
		int _tail = 0;
		int _size = 0;
};