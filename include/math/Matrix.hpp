//
// Created by arthur on 22/08/2022.
//

#ifndef CONCERTO_MATRIX_HPP
#define CONCERTO_MATRIX_HPP

#include <array>

namespace Concerto::Math
{
	template<typename T, std::size_t Rows, std::size_t Columns>
	class Matrix
	{
	public:
		template<typename ...Args>
		constexpr explicit Matrix(Args&& ... args)
		{
			static_assert(sizeof...(args) == Rows * Columns,
					"Error : The number of arguments doesn't match the matrix size");
			_data = { args... };
		}

		constexpr Matrix() : _data{ 0 }
		{
		}

		constexpr Matrix(const Matrix&) = default;

		constexpr Matrix(Matrix&&) noexcept = default;

		constexpr Matrix& operator=(const Matrix&) = default;

		constexpr Matrix& operator=(Matrix&&) noexcept = default;

		~Matrix() = default;

		[[nodiscard]] constexpr std::size_t GetWidth() const noexcept
		{
			return Columns;
		}

		[[nodiscard]] constexpr std::size_t GetHeight() const noexcept
		{
			return Rows;
		}

		/**
		 * @brief Get the value of the matrix at the given position.
		 *
		 * @param row The row of the matrix.
		 * @param column The column of the matrix.
		 * @return Reference to the value of the matrix at the given position.
		 */
		constexpr T& GetElement(std::size_t row, std::size_t column) noexcept
		{
			assert(row < Rows);
			assert(column < Columns);
			return _data[row * Columns + column];
		}

		/**
		 * @brief Get the value of the matrix at the given position.
		 *
		 * @param row The row of the matrix.
		 * @param column The column of the matrix.
		 * @return Constant reference to the value of the matrix at the given position.
		 */
		constexpr const T& GetElement(std::size_t row, std::size_t column) const noexcept
		{
			assert(row < Rows);
			assert(column < Columns);
			return _data[row * Columns + column];
		}

		/**
		 * @brief Creates an identity matrix.
		 * @attention The matrix must be square.
		 * @return Identity matrix.
		 */
		static constexpr Matrix<T, Rows, Columns> Identity() noexcept
		{
			Matrix<T, Rows, Columns> result;
			for (std::size_t i = 0; i < Rows; ++i)
			{
				for (std::size_t j = 0; j < Columns; ++j)
				{
					result.GetElement(i, j) = i == j ? T(1) : T(0);
				}
			}
			return result;
		}

		/**
		 * @brief Inverse the matrix.
		 * @return A new matrix that is the inverse of the matrix.
		 */
		constexpr Matrix<T, Rows, Columns> Inverse() const noexcept
		{
			Matrix<T, Rows, Columns> result;
			for (std::size_t i = 0; i < Rows; ++i)
			{
				for (std::size_t j = 0; j < Columns; ++j)
				{
					result.GetElement(i, j) = GetElement(j, i);
				}
			}
			return result;
		}

		/**
		 * @brief Add the given matrix to the current matrix.
		 * @param other The matrix to add.
		 * @return A new matrix that is the sum of the two matrices.
		 */
		constexpr Matrix<T, Rows, Columns> operator+(const Matrix<T, Rows, Columns>& other) const noexcept
		{
			Matrix<T, Rows, Columns> result;
			for (std::size_t i = 0; i < Rows; ++i)
			{
				for (std::size_t j = 0; j < Columns; ++j)
				{
					result.GetElement(i, j) = GetElement(i, j) + other.GetElement(i, j);
				}
			}
			return result;
		}

		/**
		 * @brief Subtract the given matrix to the current matrix.
		 * @param other The matrix to subtract.
		 * @return A new matrix that is the subtraction of the two matrices.
		 */
		constexpr Matrix<T, Rows, Columns> operator-(const Matrix<T, Rows, Columns>& other) const noexcept
		{
			Matrix<T, Rows, Columns> result;
			for (std::size_t i = 0; i < Rows; ++i)
			{
				for (std::size_t j = 0; j < Columns; ++j)
				{
					result.GetElement(i, j) = GetElement(i, j) - other.GetElement(i, j);
				}
			}
			return result;
		}

		/**
		 * @brief Multiply the given matrix to the current matrix.
		 * @param other The matrix to multiply.
		 * @return A new matrix that is the multiplication of the two matrices.
		 */
		constexpr Matrix<T, Rows, Columns> operator*(const Matrix<T, Rows, Columns>& other) const noexcept
		{
			Matrix<T, Rows, Columns> result;
			for (std::size_t i = 0; i < Rows; ++i)
			{
				for (std::size_t j = 0; j < Columns; ++j)
				{
					for (std::size_t k = 0; k < Columns; ++k)
					{
						result.GetElement(i, j) += GetElement(i, k) * other.GetElement(k, j);
					}
				}
			}
			return result;
		}

		/**
		 * @brief Divide the given matrix to the current matrix.
		 * @param other The matrix to divide.
		 * @return A new matrix that is the division of the two matrices.
		 */
		constexpr Matrix operator/(const Matrix<T, Rows, Columns>& other) const noexcept
		{
			Matrix<T, Rows, Columns> result;
			for (std::size_t i = 0; i < Rows; ++i)
			{
				for (std::size_t j = 0; j < Columns; ++j)
				{
					result.GetElement(i, j) = GetElement(i, j) / other.GetElement(i, j);
				}
			}
			return result;
		}

		/**
		 * @brief Add the given value to the current matrix.
		 * @param value The value to add.
		 * @return A new matrix that is the sum of the matrix and the value.
		 */
		constexpr Matrix<T, Rows, Columns> operator+(T value) const noexcept
		{
			Matrix<T, Rows, Columns> result;
			for (std::size_t i = 0; i < Rows; ++i)
			{
				for (std::size_t j = 0; j < Columns; ++j)
				{
					result.GetElement(i, j) = GetElement(i, j) + value;
				}
			}
			return result;
		}

		/**
		 * @brief Subtract the given value to the current matrix.
		 * @param value The value to subtract.
		 * @return A new matrix that is the subtraction of the matrix and the value.
		 */
		constexpr Matrix<T, Rows, Columns> operator-(T value) const noexcept
		{
			Matrix<T, Rows, Columns> result;
			for (std::size_t i = 0; i < Rows; ++i)
			{
				for (std::size_t j = 0; j < Columns; ++j)
				{
					result.GetElement(i, j) = GetElement(i, j) - value;
				}
			}
			return result;
		}

		/**
		 * @brief Multiply the given value to the current matrix.
		 * @param value The value to multiply.
		 * @return A new matrix that is the multiplication of the matrix and the value.
		 */
		constexpr Matrix<T, Rows, Columns> operator*(T value) const noexcept
		{
			Matrix<T, Rows, Columns> result;
			for (std::size_t i = 0; i < Rows; ++i)
			{
				for (std::size_t j = 0; j < Columns; ++j)
				{
					result.GetElement(i, j) = GetElement(i, j) * value;
				}
			}
			return result;
		}

		/**
		 * @brief Divide the given value to the current matrix.
		 * @param value The value to divide.
		 * @return A new matrix that is the division of the matrix and the value.
		 */
		constexpr Matrix<T, Rows, Columns> operator/(T value) const noexcept
		{
			Matrix<T, Rows, Columns> result;
			for (std::size_t i = 0; i < Rows; ++i)
			{
				for (std::size_t j = 0; j < Columns; ++j)
				{
					result.GetElement(i, j) = GetElement(i, j) / value;
				}
			}
			return result;
		}

		/**
		 * @brief Add the given matrix to the current matrix.
		 * @param other The matrix to add.
		 * @return A reference to the current matrix.
		 */
		constexpr Matrix<T, Rows, Columns>& operator+=(const Matrix<T, Rows, Columns>& other) noexcept
		{
			for (std::size_t i = 0; i < Rows; ++i)
			{
				for (std::size_t j = 0; j < Columns; ++j)
				{
					GetElement(i, j) += other.GetElement(i, j);
				}
			}
			return *this;
		}

		/**
		 * @brief Subtract the given matrix to the current matrix.
		 * @param other The matrix to subtract.
		 * @return A reference to the current matrix.
		 */
		constexpr Matrix<T, Rows, Columns>& operator-=(const Matrix<T, Rows, Columns>& other) noexcept
		{
			for (std::size_t i = 0; i < Rows; ++i)
			{
				for (std::size_t j = 0; j < Columns; ++j)
				{
					GetElement(i, j) -= other.GetElement(i, j);
				}
			}
			return *this;
		}

		/**
		 * @brief Multiply the given matrix to the current matrix.
		 * @param other The matrix to multiply.
		 * @return A reference to the current matrix.
		 */
		constexpr Matrix<T, Rows, Columns>& operator*=(const Matrix<T, Rows, Columns>& other) noexcept
		{
			for (std::size_t i = 0; i < Rows; ++i)
			{
				for (std::size_t j = 0; j < Columns; ++j)
				{
					GetElement(i, j) *= other.GetElement(i, j);
				}
			}
			return *this;
		}

		/**
		 * @brief Divide the given matrix to the current matrix.
		 * @param other The matrix to divide.
		 * @return A reference to the current matrix.
		 */
		constexpr Matrix<T, Rows, Columns>& operator/=(const Matrix<T, Rows, Columns>& other) noexcept
		{
			for (std::size_t i = 0; i < Rows; ++i)
			{
				for (std::size_t j = 0; j < Columns; ++j)
				{
					GetElement(i, j) /= other.GetElement(i, j);
				}
			}
			return *this;
		}

		/**
		 * @brief Add the given value to the current matrix.
		 * @param value The value to add.
		 * @return A reference to the current matrix.
		 */
		constexpr Matrix<T, Rows, Columns>& operator+=(T value) noexcept
		{
			for (std::size_t i = 0; i < Rows; ++i)
			{
				for (std::size_t j = 0; j < Columns; ++j)
				{
					GetElement(i, j) += value;
				}
			}
			return *this;
		}

		/**
		 * @brief Subtract the given value to the current matrix.
		 * @param value The value to subtract.
		 * @return A reference to the current matrix.
		 */
		constexpr Matrix<T, Rows, Columns>& operator-=(T value) noexcept
		{
			for (std::size_t i = 0; i < Rows; ++i)
			{
				for (std::size_t j = 0; j < Columns; ++j)
				{
					GetElement(i, j) -= value;
				}
			}
			return *this;
		}

		/**
		 * @brief Multiply the given value to the current matrix.
		 * @param value The value to multiply.
		 * @return A reference to the current matrix.
		 */
		constexpr Matrix<T, Rows, Columns>& operator*=(T value) noexcept
		{
			for (std::size_t i = 0; i < Rows; ++i)
			{
				for (std::size_t j = 0; j < Columns; ++j)
				{
					GetElement(i, j) *= value;
				}
			}
			return *this;
		}

		/**
		 * @brief Divide the given value to the current matrix.
		 * @param value The value to divide.
		 * @return A reference to the current matrix.
		 */
		constexpr Matrix<T, Rows, Columns>& operator/=(T value) noexcept
		{
			for (std::size_t i = 0; i < Rows; ++i)
			{
				for (std::size_t j = 0; j < Columns; ++j)
				{
					GetElement(i, j) /= value;
				}
			}
			return *this;
		}

		/**
		 * @brief Compare the current matrix with the given matrix.
		 * @param other The matrix to compare.
		 * @return True if the current matrix is equal to the given matrix, false otherwise.
		 */
		constexpr bool operator==(const Matrix<T, Rows, Columns> &other) const
		{
			for (std::size_t i = 0; i < Rows; ++i)
			{
				for (std::size_t j = 0; j < Columns; ++j)
				{
					if (GetElement(i, j) != other.GetElement(i, j))
					{
						return false;
					}
				}
			}
			return true;
		}

		/**
		 * @brief Compare the current matrix with the given matrix.
		 * @param other The matrix to compare.
		 * @return False if the current matrix is equal to the given matrix, true otherwise.
		 */
		constexpr bool operator!=(const Matrix<T, Rows, Columns> &other) const
		{
			return !(*this == other);
		}
	private:
		std::array<T, Rows * Columns> _data;
	};

	// Aliases

	using Matrix4f = Matrix<float, 4, 4>;
	using Matrix3f = Matrix<float, 3, 3>;
	using Matrix2f = Matrix<float, 2, 2>;

	using Matrix4d = Matrix<double, 4, 4>;
	using Matrix3d = Matrix<double, 3, 3>;
	using Matrix2d = Matrix<double, 2, 2>;

	using Matrix4i = Matrix<int, 4, 4>;
	using Matrix3i = Matrix<int, 3, 3>;
	using Matrix2i = Matrix<int, 2, 2>;
}
#endif //CONCERTO_MATRIX_HPP
