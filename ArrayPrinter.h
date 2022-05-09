/**
Copyright (C) Lukasz Marzec. All rights reserved.
Licensed under the MIT license. See LICENSE.txt file in the project root for full license information.

*/
#pragma once
#include "Types.h"
namespace regression {
	template<typename Ty>
	class ArrayPrinter
	{
	public:
		ArrayPrinter(ArrayPrinter const &) = delete;
		ArrayPrinter& operator=(const ArrayPrinter&) = delete;

		virtual void print_matrix(matrix_t<Ty>) const = 0;

		virtual ~ArrayPrinter() = default;
	protected:
		ArrayPrinter() = default;
	};
}