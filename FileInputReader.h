/**
Copyright (C) Lukasz Marzec. All rights reserved.
Licensed under the MIT license. See LICENSE.txt file in the project root for full license information.

*/
#pragma once

#include <string>
#include <functional>
#include <regex>
#include "InputReader.h"
#include "Types.h"
namespace regression {
	/// <summary>
	/// Implements InputReader class. Reads in data from a file.
	/// </summary>
	class FileInputReader final : public InputReader
	{
	public:
		FileInputReader(const char* path) :path(path) {};
		virtual ~FileInputReader() = default;
		virtual void read_in();

	private:
		using str_t = std::string;
		using str_vector_t = std::vector<str_t>;
		str_t path;

		void read_input_data(std::ifstream&);
		void read_output_data(std::ifstream&);

		std::function<str_vector_t(str_t)> tokenizer = [](std::string line) {
			std::regex ws_re("\\s+"); // whitespace

			std::sregex_token_iterator
				first{ std::begin(line), std::end(line), ws_re, -1 },
				last;

			std::vector<std::string> result{ first, last };
			return result;
		};
	};
}