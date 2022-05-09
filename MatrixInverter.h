/**
Copyright (C) Lukasz Marzec. All rights reserved.
Licensed under the MIT license. See LICENSE.txt file in the project root for full license information.

*/
#pragma once
#include "Types.h"

namespace regression {
	template<typename Ty>
	class MatrixInverter {
	public:
		MatrixInverter(MatrixInverter<Ty> const &) = delete;
		MatrixInverter<Ty>& operator=(const MatrixInverter<Ty>&) = delete;

		matrix_t<Ty> virtual invert_matrix(matrix_t<Ty>) = 0;
		virtual ~MatrixInverter() = default;
	protected:
		MatrixInverter() = default;
	};
}