/**
Copyright (C) Lukasz Marzec. All rights reserved.
Licensed under the MIT license. See LICENSE.txt file in the project root for full license information.

*/
#include <iostream>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <stdexcept>
#include "FileInputReader.h"

namespace regression {
	void FileInputReader::read_in() {
		std::string line;
		std::ifstream inputFile(this->path);
		if (inputFile.is_open()) {

			read_input_data(inputFile);

			read_output_data(inputFile);

			inputFile.close();
		}
		else {
			throw std::runtime_error(std::string("Unable to open file " + this->path));
		}
	}

	void FileInputReader::read_input_data(std::ifstream& file) {
		if (file.is_open()) {
			std::string line;
			// get the first line
			std::getline(file, line);

			auto line_tokenized = tokenizer(line);
			if (line_tokenized.size() != 2) {
				throw std::runtime_error(std::string("Invalid first line."));
			}

			auto features = std::stoi(line_tokenized[0]);
			auto observations = std::stoi(line_tokenized[1]);

			// get input values
			for (auto i = 0; i < observations; ++i) {
				std::getline(file, line);
				line_tokenized = tokenizer(line);
				if (line_tokenized.size() != features + 1 /* features + price */) {
					throw std::runtime_error(std::string("Invalid input data."));
				}

				row_t<float> features_row;
				row_t<float> prices_row;

				features_row.push_back(1);

				for (auto token_nr = 0; token_nr < line_tokenized.size(); ++token_nr) {
					auto as_number = std::atof(line_tokenized.at(token_nr).c_str());
					if ((token_nr % (features + 1)) < features) {
						features_row.push_back(as_number);
					}
					else {
						prices_row.push_back(as_number);
					}
				}
				this->features.push_back(features_row);
				this->prices.push_back(prices_row);
			}
		}
	}

	void FileInputReader::read_output_data(std::ifstream& file) {
		if (file.is_open()) {
			std::string line;

			// get number of observations to estimate
			std::getline(file, line);
			auto observations = std::stoi(line);

			str_vector_t line_tokenized;
			for (auto i = 0; i < observations; ++i) {
				std::getline(file, line);
				line_tokenized = tokenizer(line);

				row_t<float> features_row;
				for (auto token_nr = 0; token_nr < line_tokenized.size(); ++token_nr) {
					auto as_number = std::atof(line_tokenized.at(token_nr).c_str());
					features_row.push_back(as_number);
				}
				this->toEstimateFeatures.push_back(features_row);
			}
		}
	}
}