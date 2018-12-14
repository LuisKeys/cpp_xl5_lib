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
			_weights = new XL5Matrix<T>();
		  _weights->create_random(num_of_features, 1, 0.0, 1.0);

			XL5Random<T> random;
			random.init();
			_bias = random.get_value(0.0, 1.0);
		  // _weights->log("LR Weights:", XL5Color::FG_BLUE, 2);
		}

		T predict(XL5Matrix<T>* x_features) {
			XL5Matrix<T>* Z = x_features.multiply(_weights);
			Z.add(_bias);
			Z->drop();

			XL5Memory::delete_object();
			delete Z;

			return xl5ml_sigmoid(Z.sum());
		}

		void train(XL5Matrix<T>* x_features_samples, T target, T learning_rate) {
			int rows = x_features_samples->rows_count();

			for(int i = 0; i < rows; ++i) {
				 XL5Matrix<T>* X = x_features_samples->get_row();
				T estimation = predict(X);

				T diff = estimation - target;
				X->multiply(diff);
				X->multiply(learning_rate);
				_weights.subtract(X);

				_bias -= learning_rate * diff;

				X->drop();
				XL5Memory::delete_object();
				delete X;
			}
		}

    void drop() {
			XL5Memory::delete_object();
		  _weights->drop();
		  delete _weights;
		}

	private:
    XL5Matrix<T>* _weights;
		T _bias = 0;
};
