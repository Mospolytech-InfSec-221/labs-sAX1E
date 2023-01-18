#include "Matrix_op_reloadr.h"
// �����������
Matrix::Matrix() {
	this->size_row = 0;
	this->size_col = 0;
	this->elem = nullptr;
};
//������������ ������������
Matrix::Matrix(int i, int j) {
	this->size_row = i;
	this->size_col = j;
	this->elem = new double[this->size_row * this->size_col];
	for (int i = 0; i < this->size_col * this->size_row; i++) {
		elem[i] = 0;
	}
}
//������������ ������������

Matrix::Matrix(int i, int j, const double* arr) {
	this->size_row = i;
	this->size_col = j;
	this->elem = new double[this->size_row * this->size_col];
	for (int i = 0; i < this->size_row * this->size_col; i++) {
		elem[i] = arr[i];
	}
}
//������������ ������������ (���������� �����������)
Matrix::Matrix(const Matrix& temp)
{
	this->size_col = temp.size_col;
	this->size_row = temp.size_row;
	this->elem = new double[temp.size_col * temp.size_row];
	for(int i=0;i< temp.size_col * temp.size_row;i++)
		this->elem[i] = temp.elem[i];
}
// ������������
Matrix::~Matrix() {
	if (this->elem != nullptr)
	{
		delete[] this->elem;
	}
}
// ���� �������
void Matrix::input() {
	std::cout << "������� ���������� ����� �������: ";
	std::cin >> this->size_row;
	std::cout << "������� ���������� �������� �������: ";
	std::cin >> this->size_col;
	if (this->elem != nullptr)
	{
		delete[] this->elem;
	}
	this->elem = new double[this->size_row * this->size_col];
	for (int i = 0; i < this->size_row * this->size_col; i++) {
		std::cin >> this->elem[i];
	}
}
// ������������ ������� input
void Matrix::input(int i, int j) {
	std::cout << "������� �������� ������� ���������������: \n";
	this->size_row = i;
	this->size_col = j;
	if (this->elem != nullptr)
	{
		delete[] this->elem;
	}
	this->elem = new double[this->size_row * this->size_col];
	for (int i = 0; i < this->size_row * this->size_col; i++) {
		std::cin >> this->elem[i];
	}
}
// ������������ ������� input
void Matrix::input(int i, int j, double* arr) {
	this->size_row = i;
	this->size_col = j;
	if (this->elem != nullptr)
	{
		delete[] this->elem;
	}
	this->elem = new double[this->size_row * this->size_col];
	for (int i = 0; i < this->size_row * this->size_col; i++) {
		this->elem[i] = arr[i];
	}
}

void Matrix::print() {
	std::cout << "���� �������: \n";
	for (int i = 0; i < this->size_row; i++) {
		for (int j = 0; j < this->size_col; j++) {
			std::cout << this->elem[i * this->size_col + j] << " ";
		}
		std::cout << '\n';
	}
}
// ������� �������� �������
int Matrix::get_columns() {
	return this->size_col;
}
// ������� ��������� �����
int Matrix::get_rows() {
	return this->size_row;
}
double Matrix::get_elem(int i, int j) {
	return this->elem[i * this->size_col + j];
}

// ������������ ��������� ����
Matrix operator+(const Matrix& temp1, const Matrix& temp2)
{
	if ((temp1.size_col == temp2.size_col) and (temp1.size_row == temp2.size_row)) {
		Matrix new_mat(temp1);
		new_mat.sum(temp2.elem, temp2.size_row, temp2.size_col);
		return new_mat;
	}
	else {
		std::cout << "����������� ������ �� ���������";
	}
}


// ������������ ��������� ��������� �����
Matrix operator-(const Matrix& temp1, const Matrix& temp2)
{
	Matrix new_mat;
	new_mat.size_col = temp2.size_col;
	new_mat.size_row = temp1.size_row;
	if (new_mat.elem != nullptr)
	{
		delete[] new_mat.elem;
	}
	new_mat.elem = new double[new_mat.size_col * new_mat.size_row];

	if ((temp1.size_col == temp2.size_col) and (temp1.size_row == temp2.size_row)) {
		for (int j = 0; j < temp1.size_col; j++) {
			for (int i = 0; i < temp1.size_row; i++) {
				new_mat.elem[i * temp1.size_col + j] = temp1.elem[i * temp2.size_col + j] - temp2.elem[i * temp1.size_col + j];
			}
		}
	}
	return new_mat;
}
// ������������ �������� ��������� �����
void Matrix::operator-()
{
	for (int i = 0; i < this->size_col * size_row; i++) {
		this->elem[i] *= -1;
	}
}
// ������������ �������� ��������� ��������
void Matrix::operator*(int n)
{
	for (int i = 0; i < this->size_row * this->size_col; i++) {
		this->elem[i] *= n;
	}
}

void Matrix::mult_by_num(double num) {
	for (int i = 0; i < this->size_row; i++) {
		for (int j = 0; j < this->size_col; j++) {
			this->elem[i * this->size_col + j] = this->elem[i * this->size_col + j] * num;
		}
	}
}
bool Matrix::sum(const Matrix* mat2) {
	if ((this->size_col == mat2->size_col) and (this->size_row == mat2->size_row)) {
		for (int i = 0; i < this->size_row; i++) {
			for (int j = 0; j < this->size_col; j++) {
				this->elem[i * this->size_col + j] = this->elem[i * this->size_col + j] + mat2->elem[i * mat2->size_col + j];
			}
		}
		return 0;
	}
	else {
		return 1;
	}
}
// ������������ ������� sum
bool Matrix::sum(const double* arr, int row, int col) {
	if ((this->size_col == col) && (this->size_row == row)) {
		for (int i = 0; i < this->size_row; i++) {
			for (int j = 0; j < this->size_col; j++) {
				elem[i * this->size_col + j] += arr[i * this->size_col + j];
			}
		}
		return 0;
	}
	else {
		return 1;
	}
}
double Matrix::trace() {
	if (this->size_col == this->size_row) {
		double summ = 0;
		for (int i = 0; i < this->size_col; i++) {
			summ += this->elem[i * this->size_col + i];
		}
		return summ;
	}
	return 100000;
}
// ������������ ��������� ���������
void Matrix::operator * (const Matrix& temp) {
	if (this->size_col == temp.size_row) {
		double* res = new double[this->size_row * temp.size_col];
		for (int i = 0; i < this->size_row; i++) {
			for (int j = 0; j < temp.size_col; j++) {
				double summ = 0;
				for (int q = 0; q < this->size_col; q++) {
					summ += this->elem[i * this->size_col + q] * temp.elem[q * temp.size_col + j];
				}
				res[i * temp.size_col + j] = summ;
			}
		}
		delete[] this->elem;
		this->elem = res;
		this->size_col = temp.size_col;
	}
	else {
		std::cout << "�������� ������. ����������� �� ����������";
	}
}
// ������������ ��������� ����������
void Matrix::operator=(const Matrix& temp)
{
	this->size_col = temp.size_col;
	this->size_row = temp.size_row;
	this->elem = new double[this->size_row * this->size_col];
	for (int i = 0; i < this->size_col * this->size_row; i++) {
		this->elem[i] = temp.elem[i];
	}
}

bool Matrix::mult(const Matrix* mat2) {
	if (this->size_col == mat2->size_row) {
		double* res = new double[this->size_row * mat2->size_col];
		for (int i = 0; i < this->size_row; i++) {
			for (int j = 0; j < mat2->size_col; j++) {
				double summ = 0;
				for (int q = 0; q < this->size_col; q++) {
					summ += this->elem[i * this->size_col + q] * mat2->elem[q * mat2->size_col + j];
				}
				res[i * mat2->size_col + j] = summ;
			}
		}
		delete[] this->elem;
		this->elem = res;
		this->size_col = mat2->size_col;
		return 1;
	}
	else {
		return 0;
	}
}
// ������������ �������� ���������
bool Matrix::mult(const double* arr, int col, int row) {
	if (this->size_col == row) {
		double* res = new double[this->size_row * col];
		for (int i = 0; i < this->size_row; i++) {
			for (int j = 0; j < col; j++) {
				double summ = 0;
				for (int q = 0; q < this->size_col; q++) {
					summ += this->elem[i * this->size_col + q] * arr[q * col + j];
				}
				res[i * col + j] = summ;
			}
		}
		delete[] this->elem;
		this->elem = res;
		this->size_col = col;
		return 1;
	}
	else {
		return 0;
	}
}
// ������������ ��������� << (std::cout)
std::ostream& operator <<(std::ostream& out, const Matrix& temp) {
	for (int i = 0; i < temp.size_row; i++) {
		for (int j = 0; j < temp.size_col; j++) {
			out << temp.elem[i * temp.size_col + j] << " ";
		}
		out << std::endl;
	}
	return out;
}
// ������������ ��������� >> (std::cin)
std::istream& operator >>(std::istream& in, Matrix& temp) {
	std::cout << "������� ���-�� �����: ";
	in >> temp.size_row;
	std::cout << "\n������� ���-�� ��������: ";
	in >> temp.size_col;
	if (temp.elem != nullptr)
	{
		delete[] temp.elem;
	}
	temp.elem = new double[temp.size_row * temp.size_col];
	std::cout << "��������������� ������� ��������: \n";
	for (int i = 0; i < temp.size_col * temp.size_row; i++) {
		std::cin >> temp.elem[i];
	}
	return std::cin;
}
// ������������ ��������� +-
void Matrix::operator+=(const Matrix& temp)
{
	if ((this->size_col == temp.size_col) and (this->size_row == temp.size_row)) {
		for (int i = 0; i < this->size_col * this->size_row; i++) {
			this->elem[i] += temp.elem[i];
		}
	}
	else {
		std::cout << "����������� �� ���������";
	}
}
// ������������ �������� -=
void Matrix::operator-=(const Matrix& temp)
{
	if ((this->size_col == temp.size_col) and (this->size_row == temp.size_row)) {
		for (int i = 0; i < this->size_col * this->size_row; i++) {
			this->elem[i] -= temp.elem[i];
		}
	}
	else {
		std::cout << "����������� �� ���������";
	}
}