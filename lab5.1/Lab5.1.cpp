// Policarpov
#include "Matrix.h"
#include <iostream>
int main() {
	setlocale(LC_ALL, "RUS");
	Matrix mat1, mat2;
	int choice;
	//����
	while (true) {
		std::cout << "\n��� �� ������ ���������? \n"
			<< "1. ���� ������� �1\n"
			<< "2. ���� ������� �2\n"
			<< "3. ����� ������� �1\n"
			<< "4. ����� ������� �2\n"
			<< "5. ������� ���-�� ����� � �������� ������ �������\n"
			<< "6. ������� ���-�� ����� � �������� ������ �������\n"
			<< "7. ����� �������� ������� ����� 1 �� �������\n"
			<< "8. ����� �������� ������� ����� 2 �� �������\n"
			<< "9. �������� ������� �1 �� ����� n\n"
			<< "10.�������� ������� �2 �� ����� n\n"
			<< "11.��������� � ������� �1 ������� �2\n"
			<< "12.����� ���� ������ �������\n"
			<< "13.����� ���� ������ �������\n"
			<< "14.�������� ������ ������� �� ������\n"
			<< "15.�������� ������ ������� �� ������\n"
			<< "16.�����\n";
		std::cin >> choice;
		switch (choice) {
		case 1: {
			std::cout << "���� ������� �1\n";
			mat1.input();
			std::cout << "���� ������� �1 ��������\n";
			break;
		}
		case 2: {
			std::cout << "���� ������� �2\n";
			mat2.input();
			std::cout << "���� ������� �2��������\n";
			break;
		}
		case 3: {
			std::cout << "����� ������� �1\n";
			mat1.print();
			break;
		}
		case 4: {
			std::cout << "����� ������� �2\n";
			mat2.print();
			break;
		}
		case 5: {
			std::cout << "���-�� ����� ������ ������� " << mat1.get_rows() << '\n';
			std::cout << "���-�� �������� ������ ������� " << mat1.get_columns();
			break;
		}
		case 6: {
			std::cout << "���-�� ����� ������ ������� " << mat2.get_rows() << '\n';
			std::cout << "���-�� �������� ������ ������� " << mat2.get_columns();
			break;
		}
		case 7: {
			int i, j;
			std::cout << "\n������� i-������ � j- ������ ��� ������ �������� � ������ �������\n";
			std::cout << "i-������: "; std::cin >> i;
			std::cout << "j-������: "; std::cin >> j;
			std::cout << mat1.get_elem(i, j);
			break;
		}
		case 8: {
			int i, j;
			std::cout << "\n������� i-������ � j- ������ ��� ������ �������� �� ������ �������\n";
			std::cout << "i-������: "; std::cin >> i;
			std::cout << "j-������: "; std::cin >> j;
			std::cout << mat2.get_elem(i, j);
			break;
		}
		case 9: {
			std::cout << "\n������� ����� n: "; double n; std::cin >> n;
			mat1.mult_by_num(n);
			break;
		}
		case 10: {
			std::cout << "\n������� ����� n: "; double n; std::cin >> n;
			mat2.mult_by_num(n);
			break;
		}
		case 11: {
			if (mat2.get_columns() != 0) {
				if (mat1.sum(&mat2) == 0) {
					std::cout << "�������� ������ ������� �� ������ ������ �������\n";
				}
				else {
					std::cout << "����������� ������ ������� �� ��������� � ������������ ������";
				}
			}
			break;
		}
		case 12: {
			if (mat1.get_columns() == 0) {
				std::cout << "������� �1 �����";
				break;
			}
			if (mat1.trace() != 100000 ) {
				std::cout << mat1.trace();
			}
			else {
				std::cout << "������� �1 �� ����������\n";
			}
			break;
		}
		case 13: {
			if (mat2.get_columns() == 0) {
				std::cout << "������� �2 �����";
				break;
			}
			if (mat2.trace() != 100000) {
				std::cout << mat2.trace();
			}
			else {
				std::cout << "������� �2 �� ����������\n";
			}
			break;
		}
		case 14: {
			if (mat1.mult(&mat2) == 0 or mat1.get_columns() == 0 or mat2.get_columns() == 0) {
				std::cout << "���� �� ������ �����������";
			}
			else {
				mat1.mult(&mat2);
				std::cout << "��������� ������ �������";
			}
			break;
		}
		case 15: {
			if (mat2.mult(&mat1) == 0 or mat1.get_columns() == 0 or mat2.get_columns() == 0) {
				std::cout << "���� �� ������ �����������";
			}
			else {
				mat2.mult(&mat1);
				std::cout << "��������� ������ �������";
			}
			break;
		}
		case 16: {
			return 0;
		}
		}
	}
}