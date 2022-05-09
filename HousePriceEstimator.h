/**
Copyright (C) Lukasz Marzec. All rights reserved.
Licensed under the MIT license. See LICENSE.txt file in the project root for full license information.

*/
#pragma once
#include <memory>
#include "Matrix.h"

namespace regression {
	/// <summary>
	/// Estimates house prices using either adjoint method or Cholesky decomposition.
	/// </summary>
	class HousePriceEstimator final
	{
		public:
			/// <summary>
			/// Defines available matrix invertion methods.
			/// BruteForce - adjoin method
			/// Cholesky - Cholesky decomposition method
			/// </summary>
			enum MatrixInvertStrategy {
				BruteForce, Cholesky
			};

			HousePriceEstimator() = default;
			~HousePriceEstimator() = default;

			/// <summary>
			/// Performs price estimation.
			/// </summary>
			/// <param name="invertStrategy">Determines method used to invert matrix.</param>
			void estimate(MatrixInvertStrategy);
		private:
			using features_matrix_t = Matrix<float>;
			using price_matrix_t = Matrix<float>;
			using features_matrix_ptr_t = std::unique_ptr<features_matrix_t>;
			using price_matrix_ptr_t = std::unique_ptr<price_matrix_t>;

			features_matrix_ptr_t features;
			features_matrix_ptr_t toEstimateFeatures;
			price_matrix_ptr_t prices;

			void get_input();
	};
}
