#pragma once
#include <iostream>
#include "XL5MLActivation.h"
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
			_W = new XL5Matrix<T>();
		  _W->create_random(num_of_features, 1, 0.0, 1.0);

			XL5Random<T> random;
			random.init();
			_b = random.get_value(0.0, 1.0);
		  // _W->log("LR Weights:", XL5Color::FG_BLUE, 2);
		}

		T predict(XL5Matrix<T>* x_features) {
			XL5Matrix<T>* Z = x_features.multiply(_W);
			Z.add(_b);
			Z->drop();

			XL5Memory::delete_object();
			delete Z;

			return xl5ml_sigmoid(Z.sum());
		}

		void train(XL5Matrix<T>* X, T y, T learning_rate) {
			T estimation = predict(X);

			T diff = estimation - y;
			X->multiply(diff);
			X->multiply(learning_rate);
			_W.subtract(X);

			_b -= learning_rate * diff;

			X->drop();
			XL5Memory::delete_object();
			delete X;
		}

    void drop() {
			XL5Memory::delete_object();
		  _W->drop();
		  delete _W;
		}

	private:
    XL5Matrix<T>* _W;
		T _b = 0;
};
