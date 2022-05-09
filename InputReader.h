/**
Copyright (C) Lukasz Marzec. All rights reserved.
Licensed under the MIT license. See LICENSE.txt file in the project root for full license information.

*/
#pragma once
#pragma once

#include <string>
#include <functional>
#include <regex>
#include "Types.h"
namespace regression {
	/// <summary>
	/// Abstract input class, responsible for getting input data. 
	/// </summary>
	class InputReader
	{
	public:
		virtual ~InputReader() = default;

		/// <summary>
		/// Reads in input data.
		/// </summary>
		virtual void read_in() = 0;

		/// <summary>
		/// Provides features data, read by the read_in function.
		/// </summary>
		virtual const matrix_t<float>& getFeatures() {
			return this->features;
		};

		/// <summary>
		/// Provides known home prices, read by the read_in function.
		/// </summary>
		virtual const matrix_t<float>& getPrices() {
			return this->prices;
		};

		/// <summary>
		/// Provides features used to estimate prices, read by the read_in function.
		/// </summary>
		virtual const matrix_t<float>& getEstimateFeatures() {
			return this->toEstimateFeatures;
		};
	protected:
		InputReader() = default;
		matrix_t<float> features;
		matrix_t<float> prices;
		matrix_t<float> toEstimateFeatures;
	};
}
