/**
Copyright (C) Lukasz Marzec. All rights reserved.
Licensed under the MIT license. See LICENSE.txt file in the project root for full license information.

*/
#pragma once
namespace regression {
	/// <summary>
	/// A vector of type T
	/// </summary>
	template<typename T>
	using row_t = std::vector<T>;

	/// <summary>
	/// A vector of vectors of type T
	/// </summary>
	template<typename T>
	using matrix_t = std::vector<row_t<T>>;

	/// <summary>
	/// A Matrix by Matrix multiplication operator. X = A * B, where both 'A' and 'B' are matrices.
	/// </summary>
	template <typename Ty>
	matrix_t<Ty> operator*(const matrix_t<Ty>& lhs, const matrix_t<Ty>& rhs) {
		matrix_t<Ty> result;

		for (size_t r = 0, lhs_rows_size = lhs.size(); r < lhs_rows_size; ++r) {
			row_t<Ty> row;
			for (size_t r_cols = 0, rhs_cols_size = rhs[0].size(); r_cols < rhs_cols_size; ++r_cols) {
				Ty sum = 0;
				for (size_t l_col = 0, lhs_cols_size = lhs[r].size(); l_col < lhs_cols_size; ++l_col) {
					sum += (Ty)(lhs[r][l_col] * rhs[l_col][r_cols]);
				}
				row.push_back(sum);
			}
			result.push_back(row);
		}
		return result;
	}

	/// <summary>
	/// A scalar by matrix multiplication operator. X = a * B, whare 'a' is a scalar and 'B' is a matrix.
	template <typename Ty, class C>
	matrix_t<Ty> operator*(C x, const matrix_t<Ty>& rhs) {
		auto matrix_size = rhs.size();
		matrix_t<Ty> result;
		result.reserve(matrix_size);

		for (auto i = rhs.begin(); i != rhs.end(); ++i) {
			row_t<Ty> row;
			row.reserve(matrix_size);
			for (auto j = (*i).begin(); j != (*i).end(); ++j) {
				row.push_back(x * (*j));
			}
			result.push_back(row);
		}

		return result;
	}
}