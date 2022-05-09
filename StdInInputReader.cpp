/**
Copyright (C) Lukasz Marzec. All rights reserved.
Licensed under the MIT license. See LICENSE.txt file in the project root for full license information.

*/
#include <iostream>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <stdexcept>
#include "StdInInputReader.h"

namespace regression {
	void StdInInputReader::read_in() {
		// get F and T
		unsigned F, T;
		std::cin >> F >> T;
		
		for (auto i = 0; i < T; ++i) {
			// Features
			row_t<float> features_row;
			row_t<float> price_row;

			features_row.push_back(1);

			for (auto j = 0; j < F; ++j) {
				float f;
				std::cin >> f;
				features_row.push_back(f);
			}
			this->features.push_back(features_row);

			// Price
			float price;
			std::cin >> price;
			price_row.push_back(price);
			this->prices.push_back(price_row);
		}

		// Features with unknown price
		std::cin >> T;
		for (auto i = 0; i < T; i++) {
			row_t<float> features_row;
			for (auto j = 0; j < F; ++j) {
				float f;
				std::cin >> f;
				features_row.push_back(f);
			}
			this->toEstimateFeatures.push_back(features_row);
		}
	}
}