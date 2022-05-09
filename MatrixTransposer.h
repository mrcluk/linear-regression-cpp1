/**
Copyright (C) Lukasz Marzec. All rights reserved.
Licensed under the MIT license. See LICENSE.txt file in the project root for full license information.

*/
#pragma once
#include "Types.h"
namespace regression {
	/// <summary>
	/// Transposes a matrix.
	/// </summary>
	template <typename Ty>
	class MatrixTransposer {
	public:
		MatrixTransposer(matrix_t<Ty> data) : data(data) {};
		virtual ~MatrixTransposer() = default;

		/// <summary>
		/// Transposes a matrix provided in the class constructor.
		/// </summary>
		matrix_t<Ty> get_transposed() const;
	private:
		matrix_t<Ty> data;
	};

	template <typename Ty>
	matrix_t<Ty> MatrixTransposer<Ty>::get_transposed() const {
		const auto matrix_size = this->data.size();
		const auto columns = this->data[0].size();
		matrix_t<Ty> result;

		// pre-initilize matrix
		result.reserve(columns);
		for (auto row_index = 0; row_index < columns; ++row_index) {
			row_t<Ty> row;
			row.resize(matrix_size);
			result.push_back(row);
		}

		// transpose
		for (auto row_index = 0; row_index < matrix_size; ++row_index) {
			for (auto col_index = 0; col_index < columns; ++col_index) {
				result[col_index][row_index] = this->data[row_index][col_index];
			}
		}

		return result;
	}
}