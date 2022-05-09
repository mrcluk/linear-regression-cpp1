/**
Copyright (C) Lukasz Marzec. All rights reserved.
Licensed under the MIT license. See LICENSE.txt file in the project root for full license information.

*/
#pragma once
#include <vector>
#include <iostream>
#include <iomanip>
#include "Types.h"
#include "ArrayPrinter.h"
#include "MatrixInverter.h"
#include "MatrixTransposer.h"

namespace regression {
	/// <summary>
	/// A matrix representation with basic functions and operators.
	/// <summary>
	template<class Ty>
	class Matrix {
	public:
		Matrix() = default;
		Matrix(const matrix_t<Ty>& matrix) : matrix(matrix) {}
		Matrix(const row_t<Ty>& row) { 
			row_t<Ty> r(row);
			matrix.push_back(r); 
		}

		void print(const ArrayPrinter<Ty>&) const;
		bool is_empty() const;
		void set(std::size_t i, std::size_t j, Ty value);
		std::pair<size_t, size_t> size() const;

		Matrix<Ty> get_inverted(MatrixInverter<Ty>& inverted) const;
		Matrix<Ty> get_transposed() const;

		auto cbegin() const {
			return this->matrix.cbegin();
		}

		auto cend() const {
			return this->matrix.cend();
		}

		Ty& operator()(std::size_t i, std::size_t j) {
			resize_matrix(i, j);
			return matrix[i][j];
		}
		Ty operator()(std::size_t i, std::size_t j) const { return matrix[i][j]; }
		friend Matrix<Ty> operator * (const Matrix<Ty>& lhs, const Matrix<Ty>& rhs) {
			return Matrix<Ty>(lhs.matrix * rhs.matrix);
		}

		friend std::ostream& operator<<(std::ostream& os, const Matrix<Ty>& m) {
			for (const auto& row : m.matrix) {
				for (const auto& item : row) {
					os << std::fixed << std::setprecision(2) << item << ' ';
				}
				os << std::endl;
			}
			return os;
		}
	protected:
	private:

		matrix_t<Ty> matrix;

		void resize_matrix(std::size_t i, std::size_t j);
	};

	template<class Ty>
	bool Matrix<Ty>::is_empty() const {
		return matrix.size() == 0;
	}

	template<class Ty>
	std::pair<size_t, size_t> Matrix<Ty>::size() const {
		std::pair<size_t, size_t> matrix_size;
		if (!this->matrix.empty()) {
			matrix_size.first = this->matrix.size();
			matrix_size.second = this->matrix[0].size();
		}
		return matrix_size;
	}


	template<class Ty> void Matrix<Ty>::print(const ArrayPrinter<Ty>& printer) const {
		printer.print_matrix(this->matrix);
	}

	template<class Ty> void Matrix<Ty>::set(std::size_t i, std::size_t j, Ty value) {
		resize_matrix(i, j);
		matrix[i][j] = value;
	}

	template<class Ty>
	Matrix<Ty> Matrix<Ty>::get_inverted(MatrixInverter<Ty>& inverter) const {
		auto invertedMatrix = inverter.invert_matrix(this->matrix);
		Matrix<Ty> result(invertedMatrix);
		return result;
	}

	template<class Ty>
	Matrix<Ty> Matrix<Ty>::get_transposed() const {
		MatrixTransposer<Ty> transposer(this->matrix);
		return Matrix<Ty>(transposer.get_transposed());
	}


	template<class Ty>
	void Matrix<Ty>::resize_matrix(std::size_t i, std::size_t j) {
		if (this->matrix.size() < i + 1) {
			this->matrix.resize(i + 1);
		}
		for (auto &v : this->matrix) {
			if (v.size() < j + 1) {
				v.resize(j + 1);
			}
		}
	}
}