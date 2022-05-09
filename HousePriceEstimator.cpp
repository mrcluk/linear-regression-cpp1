/**
Copyright (C) Lukasz Marzec. All rights reserved.
Licensed under the MIT license. See LICENSE.txt file in the project root for full license information.

*/
#include "InputReader.h"
#include "StdInInputReader.h"
#include "HousePriceEstimator.h"
#include "ConsoleArrayPrinter.h"
#include "DecompositionInverter.h"
#include "AdjointMatrixInverter.h"

namespace regression {
	void HousePriceEstimator::estimate(MatrixInvertStrategy invertStrategy)
	{
		// get X and Y
		this->get_input();

		if (this->features && this->toEstimateFeatures && this->prices) {	
			// X'
			Matrix<float> featuresMatrixTransposed(this->features->get_transposed());

			// X' * X
			auto xt_x = featuresMatrixTransposed * (*this->features);

			std::shared_ptr<MatrixInverter<float>> inverter;
			if (invertStrategy == this->Cholesky) {
				inverter = std::make_shared<DecompositionInverter<float>>();
			}
			else {
				inverter = std::make_shared<AdjointMatrixInverter<float>>();
			}

			// (X' * X)^-1
			auto xt_x_inv = xt_x.get_inverted(*inverter);

			// X' * Y
			auto xt_y = featuresMatrixTransposed * (*this->prices);

			// B = (X' * X)^-1 * (X' * Y)
			auto b = xt_x_inv * xt_y;
			std::cout << b << std::endl;
		}
	}

	void HousePriceEstimator::get_input() {
		std::unique_ptr<InputReader> reader(std::make_unique<StdInInputReader>());
		reader->read_in();

		// set features
		this->features = std::make_unique<features_matrix_t>(reader->getFeatures());

		// set features to be estimated
		this->toEstimateFeatures = std::make_unique<features_matrix_t>(reader->getEstimateFeatures());

		// set prices
		this->prices = std::make_unique<features_matrix_t>(reader->getPrices());
	}

}