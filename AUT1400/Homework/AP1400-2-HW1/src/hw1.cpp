#include "hw1.h"
#include <random>
Matrix algebra::zeros(size_t n, size_t m){
    return Matrix(n, std::vector<double>(m, 0.0));
};

Matrix algebra::ones(size_t n, size_t m){
    return Matrix(n, std::vector<double>(m, 1.0));
};

Matrix algebra::random(size_t n, size_t m, double min, double max){
    if(min > max) {
        throw std::logic_error(" min number should less than max number");
    }
    std::default_random_engine generator ;
    std::uniform_real_distribution<double> distribution(min,max);
    Matrix matrix(n, std::vector<double>(m));
    for (auto &row: matrix){
        for (auto &elem: row){
            elem = distribution(generator);
        }
    }
    return matrix;
};

void algebra::show(const Matrix& matrix){
    for (auto &row:matrix){
        for(auto &elem:row){
            std::cout<< elem << " ";
        }
        std:: cout << "\n";
    }
}

Matrix algebra::multiply(const Matrix& matrix, double c){
    Matrix res = matrix;
    for (auto &row:res){
        for (auto &elem:row){
            elem *= c;
        }
    }
    return res;
};

Matrix algebra::multiply(const Matrix& matrix1, const Matrix& matrix2){
    if(matrix1.empty() || matrix2.empty()) {
        if(matrix1.empty() && matrix2.empty()) {
            Matrix matrix;
            return matrix;
        }
        throw std::logic_error("cannot multiply a non-empty matrix with an empty matrix");
    }
    if(matrix1[0].size() != matrix2.size()) {
        throw std::logic_error("cannot multipy two different dimension matrixs");
    }
    std::size_t row1 = matrix1.size();
    std::size_t col1 = matrix1[0].size();
    std::size_t row2 = matrix2.size();
    std::size_t col2 = matrix2[0].size();
    Matrix result(row1, std::vector<double>(col2));
    for (std::size_t i = 0; i < row1; ++i){
        for(std::size_t j = 0; j < col2; ++j){
            for(std::size_t k = 0; k < col1; ++k){
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
    return result;
};

Matrix algebra::sum(const Matrix& matrix, double c){
    Matrix result = matrix;
    for (auto &row:result){
        for (auto &elem:row){
            elem += c; 
        }
    }
    return result;
};

Matrix algebra::sum(const Matrix& matrix1, const Matrix& matrix2){
    if(matrix1.empty() || matrix2.empty()) {
        if(matrix1.empty() && matrix2.empty()) {
            Matrix matrix;
            return matrix;
        }
        throw std::logic_error("cannot multiply a non-empty matrix with an empty matrix");
    }
    auto row1 = matrix1.size();
    auto col1 = matrix1[0].size();
    auto row2 = matrix2.size();
    auto col2 = matrix2[0].size();
    if(row1 != row2 || col1 != col2) {
        throw std::logic_error("cannot multipy two different dimension matrixs");
    }
    Matrix result = Matrix(row1, std::vector<double>(col1));
    for (std::size_t i = 0; i < row1; ++i){
        for (std::size_t j = 0; j < col1; ++j){
            result[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }
    return result;
};

Matrix algebra::transpose(const Matrix& matrix){
    if(matrix.empty()){
        Matrix emptymatrix;
        return emptymatrix;
    }
    int row = matrix.size();
    int col = matrix[0].size();
    Matrix result(col, std::vector<double>(row));

    for (int i = 0 ; i < col; ++i){
        for(int j = 0; j < row; ++j){
            result[i][j] = matrix[j][i];
        }
    }
    return result;
};

Matrix algebra::minor(const Matrix& matrix, size_t n, size_t m){
    int row = matrix.size();
    int col = matrix[0].size(); 
    Matrix result(row-1, std::vector<double>(col-1));
    for(int i = 0; i < row-1; ++i){
        for(int j = 0;j < col-1; ++j){
            int r = i;
            int c = j;
            if(i >= n){
                r = i+1;
            };
            if(j >= m){
                c = j+1;
            };
            result[i][j] = matrix[r][c];
        }
    }
    return result;
};

double algebra::determinant(const Matrix& matrix){
    double result = 0;
    if(matrix.empty()){
        result = 1;
        return result;
    }
    int row = matrix.size();
    int col = matrix[0].size();
    if (row != col ){
        throw std::logic_error("only square matrix has determiant");
    }
    if (row == 1){
        result = matrix[0][0];
        return result;
    }
    if (row == 2){
        result = (matrix[0][0] * matrix[1][1]) - (matrix[1][0] * matrix[0][1]);
    }
    if (row > 2){
        for (int i = 0; i < col; ++i){
            int sign = i%2 == 0? 1:-1;
            result += (sign * matrix[0][i] * algebra::determinant(algebra::minor(matrix, 0, i)));
        }
    }
    return result;
};

Matrix algebra::inverse(const Matrix& matrix){
    if (matrix.empty()){
        return matrix;
    }
    int row = matrix.size();
    int col = matrix[0].size();
    Matrix result(row, std::vector<double>(col));
    if (row != col ){
        throw std::logic_error("only square matrices has inverse matrix");
    }
    double det = algebra::determinant(matrix);
    if (det == 0){
        throw std::logic_error("singularity matrix has no inverse");
    }
    for (int i = 0; i < row; ++i){
        for(int j = 0; j < col; ++j){
            int sign = (i + j) % 2 == 0 ? 1 : -1;
            result[i][j] = sign * determinant(minor(matrix, i, j)) / det;
        }
    }
    return transpose(result);
};

Matrix algebra::concatenate(const Matrix& matrix1, const Matrix& matrix2, int axis){
    if ((axis == 0 && matrix1[0].size() != matrix2[0].size()) || (axis == 1 && matrix1.size() != matrix2.size())){
        throw std::logic_error("cannot concatenate");
    }
    Matrix result = matrix1;
    if (axis == 0){
        result.insert(result.end(), matrix2.begin(), matrix2.end());
;    }
    if (axis == 1){
        for (int i = 0; i < matrix1.size(); ++i){
            result[i].insert(result[i].end(), matrix2[i].begin(), matrix2[i].end());
        }
    }
    return result;
};

Matrix algebra::ero_swap(const Matrix& matrix, size_t r1, size_t r2){
    if (matrix.empty()){
        return matrix;
    }
    int row = matrix.size();
    int col = matrix[0].size();
    if (r1 > row-1 || r2 > row-1){
        throw std::logic_error{"Caution: r1 or r2 inputs are out of range"};
    }
    Matrix result = matrix;
    for (int i = 0; i < col;++i){
        std::swap(result[r1][i], result[r2][i]);
    }
    return result;
}   

Matrix algebra::ero_multiply(const Matrix& matrix, size_t r, double c){
    int row = matrix.size();
    int col = matrix[0].size();
    Matrix result = matrix;
    for (int i = 0; i < col;++i){
        result[r][i] = matrix[r][i] * c;
    }
    return result;
}

Matrix algebra::ero_sum(const Matrix& matrix, size_t r1, double c, size_t r2){
    int row = matrix.size();
    int col = matrix[0].size();
    Matrix result = matrix;
    for (int i = 0; i < col;++i){
        result[r2][i] += matrix[r1][i] * c;
    }
    return result;
}

Matrix algebra::upper_triangular(const Matrix& matrix) {
    if (matrix.empty()) {
        return matrix;
    }
    int row = matrix.size();
    int col = matrix[0].size();
    if (row != col) {
        throw std::logic_error("Caution: non-square matrices have no upper triangular form");
    }
    Matrix result = matrix;
    for (int r1 = 0; r1 < row - 1; ++r1) {
        // Implement partial pivoting: Swap with a row below if pivot element is zero
        if (result[r1][r1] == 0) {
            bool swapped = false;
            for (int r = r1 + 1; r < row; ++r) {
                if (result[r][r1] != 0) {
                    result = ero_swap(result, r1, r);
                    swapped = true;
                    break;
                }
            }
            if (!swapped) {
                throw std::logic_error("Division by zero detected, matrix may be singular");
            }
        }
        for (int r2 = r1 + 1; r2 < row; ++r2) {
            double c = result[r2][r1] / result[r1][r1] * -1;
            result = ero_sum(result, r1, c, r2);
        }
    }
    return result;
}
