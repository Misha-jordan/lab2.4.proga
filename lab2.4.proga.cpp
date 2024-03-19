
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>



template <typename T>
class Matrix {
private:
    std::vector<std::vector<T>> data;
    unsigned int m;
    unsigned int n;

public:
    Matrix(unsigned int rows, unsigned int cols) : m(rows), n(cols) {
        data.resize(m, std::vector<T>(n, 0));
    }

    ~Matrix() {}

    std::vector<T>& operator[](unsigned int index) {
        return data[index];
    }

    void fillRandom() {
        srand(static_cast<unsigned int>(time(0)));
        for (unsigned int i = 0; i < m; ++i) {
            for (unsigned int j = 0; j < n; ++j) {
                data[i][j] = static_cast<T>(rand() % 10);
            }
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const Matrix<T>& matrix) {
        for (unsigned int i = 0; i < matrix.m; ++i) {
            for (unsigned int j = 0; j < matrix.n; ++j) {
                os << matrix.data[i][j] << ' ';
            }
            os << '\n';
        }
        return os;
    }

    Matrix<T> operator+(const Matrix<T>& other) const {
        Matrix<T> result(m, n);
        for (unsigned int i = 0; i < m; ++i) {
            for (unsigned int j = 0; j < n; ++j) {
                result.data[i][j] = data[i][j] + other.data[i][j];
            }
        }
        return result;
    }

    Matrix<T> operator-(const Matrix<T>& other) const {
        Matrix<T> result(m, n);
        for (unsigned int i = 0; i < m; ++i) {
            for (unsigned int j = 0; j < n; ++j) {
                result.data[i][j] = data[i][j] - other.data[i][j];
            }
        }
        return result;
    }

    Matrix<T> operator*(const Matrix<T>& other) const {
        Matrix<T> result(m, other.n);
        for (unsigned int i = 0; i < m; ++i) {
            for (unsigned int j = 0; j < other.n; ++j) {
                for (unsigned int k = 0; k < n; ++k) {
                    result.data[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }
        return result;
    }

    bool operator==(const Matrix<T>& other) const {
        return data == other.data;
    }

    bool operator!=(const Matrix<T>& other) const {
        return !(*this == other);
    }
};

template<typename T>
class Vector : public Matrix<T> {
public:
    Vector(unsigned int size) : Matrix<T>(1, size) {}

    Matrix<T> vectorProduct(const Vector<T>& other) const {
        return *this * other;
    }

    T scalarProduct(const Vector<T>& other) const {
        T result = 0;
        for (unsigned int i = 0; i < this->n; ++i) {
            result += this->data[0][i] * other.data[0][i];
        }
        return result;
    }
};

int main() {
    Matrix<int> mat1(3, 3);
    Matrix<int> mat2(3, 3);

    mat1.fillRandom();
    mat2.fillRandom();

    std::cout << "Matrix 1:\n" << mat1 << "\n";
    std::cout << "Matrix 2:\n" << mat2 << "\n";

    Matrix<int> sum = mat1 + mat2;
    std::cout << "Sum of matrices:\n" << sum << "\n";

    Matrix<int> diff = mat1 - mat2;
    std::cout << "Difference of matrices:\n" << diff << "\n";

    Matrix<int> mult = mat1 * mat2;
    std::cout << "Product of matrices:\n" << mult << "\n";

    std::cout << "Matrix 1 == Matrix 2: " << (mat1 == mat2) << "\n";
    std::cout << "Matrix 1 != Matrix 2: " << (mat1 != mat2) << "\n";

    // Testing Vector 
    Vector<int> vec1(3);
    Vector<int> vec2(3);
    vec1.fillRandom();
    vec2.fillRandom();
    std::cout << "Vector 1:\n" << vec1 << "\n";
    std::cout << "Vector 2:\n" << vec2 << "\n";
    Matrix<int> vecProd = vec1.vectorProduct(vec2);
    std::cout << "Vector product of vectors:\n" << vecProd << "\n";
    int scalarProd = vec1.scalarProduct(vec2);
    std::cout << "Scalar product of vectors: " << scalarProd << "\n";

    return 0;
}
