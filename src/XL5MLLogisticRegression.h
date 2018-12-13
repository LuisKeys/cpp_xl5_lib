#pragma once
#include <iostream>
#include "XL5Exceptions.h"
#include "XL5Log.h"
#include "XL5Matrix.h"
#include "XL5Memory.h"
#include "XL5MLLogisticRegression.h"
#include "XL5Random.h"

// ML Logistic Regression object and related operations
template<class T>
class XL5MLLogisticRegression {
	public:
		void create(int num_of_features) {
			XL5Memory::new_object();
			_weights = new XL5Matrix<T>();
		  _weights->create_random(num_of_features, 1, 0.0, 1.0);

			XL5Random<T> random;
			random.init();
			_bias = random.get_value(0.0, 1.0);
		  // _weights->log("LR Weights:", XL5Color::FG_BLUE, 2);
		}

		void predict(XL5Matrix<T>* x_features) {
		}

		void train(XL5Matrix<T>* x_features, T x_target) {
		}

    void drop() {
			XL5Memory::delete_object();
		  _weights->drop();
		  delete _weights;
		}

	private:
    XL5Matrix<T>* _weights;
		T _bias;
};
