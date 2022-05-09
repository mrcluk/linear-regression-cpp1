/**
Copyright (C) Lukasz Marzec. All rights reserved.
Licensed under the MIT license. See LICENSE.txt file in the project root for full license information.

*/
#pragma once
#include <iostream>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <stdexcept>
#include "FileInputReader.h"

namespace regression {
	/// <summary>
	/// Implements InputReader class. Reads in data from the standard input.
	/// </summary>
	class StdInInputReader final : public InputReader
	{
	public:
		StdInInputReader() = default;
		virtual ~StdInInputReader() = default;
		virtual void read_in();
	};
}