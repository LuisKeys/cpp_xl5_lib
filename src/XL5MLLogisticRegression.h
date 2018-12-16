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
		  _W->create_random(num_of_features, 1, -0.01, 0.01);

			XL5Random<T> random;
			random.init();
			_b = random.get_value(-1.0, 1.0);
		  // _W->log("LR Weights:", XL5Color::FG_BLUE, 2);
		}

		T predict(XL5Matrix<T>* X) {
			XL5Matrix<T>* Z = X->multiply(_W);
			Z->add(_b);

			_non_rounded_estimation = xl5ml_sigmoid(Z->add());
			_estimation = xl5ml_round_activation(_non_rounded_estimation);

			Z->drop();
			XL5Memory::delete_object();
			delete Z;

			return _estimation;
		}

		void train(XL5Matrix<T>* X, T y, T learning_rate) {
			_estimation = predict(X);

			T diff = _estimation - y;
			XL5Matrix<T>* Xc = X->clone();
			Xc->multiply(diff);
			Xc->multiply(learning_rate);
			Xc->traspose();
			_W->subtract(Xc);
			Xc->traspose();

			_b -= learning_rate * diff;

			Xc->drop();
			XL5Memory::delete_object();
			delete Xc;
		}

		T get_estimation() {
			return _estimation;
		}

		T get_non_rounded_estimation() {
			return _non_rounded_estimation;
		}

    void drop() {
			XL5Memory::delete_object();
		  _W->drop();
		  delete _W;
		}

	private:
    XL5Matrix<T>* _W;
		T _b = 0;
		T _estimation = 0.0;
		T _non_rounded_estimation = 0.0;
};
