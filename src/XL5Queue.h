#pragma once

#include "XL5Log.h"

#define XL5_QUEUE_OK 0
#define XL5_QUEUE_ERR_QUEUE_OVERFLOW 1

// Queue object and related operations, any type can be enqueue and dequeue
template<class T>
class XL5Queue {
	public:
		// Returns queue size
		int size() {
			return _size;
		}

		// Creates a queue with the provided size
		void create(int size) {
			XL5Memory::new_object();
			_queue_elements = new T[size];
			_size = size;
			_head = 0;
			_tail = 0;
		}

		// Enqueue an object ot type T in the queue
		int enqueue(T data_object) {
			if(_tail < _head)
				if(_tail == _head - 1)
					return XL5_QUEUE_ERR_QUEUE_OVERFLOW;

			if(_tail == _size)
				return XL5_QUEUE_ERR_QUEUE_OVERFLOW;

			_queue_elements[_tail] = data_object;
			if(_tail == _size) {
				_tail = 1;
			}
			else {
				_tail++;
			}

			return XL5_QUEUE_OK;
		}

		// Dequeue an object ot type T from the queue
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

		// Clear the queue
		void clear() {
			_head = 0;
			_tail = 0;
		}

		// Drop the queue from memory
		void drop() {
			XL5Memory::delete_object();
			delete _queue_elements;
		}

	private:
		T* _queue_elements;
		int _head = 0;
		int _tail = 0;
		int _size = 0;
};
