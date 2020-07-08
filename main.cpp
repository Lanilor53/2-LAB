#include <iostream>
#include <cstring>
#include "matr.h"

using namespace std;
template <typename matrType>
void realMAIN(matrType i);

int main(int argc, char** argv) {
  // x 3 plotnost' pixeley
	char buff[256];
	int flagInt = 0;
	double flagDouble = 0;
	float flagFloat = 0;

	while (!(flagInt || flagDouble || flagFloat)) {
		cout << "Input type of matrices:" << endl << ">";
		cin >> buff;
		strcmp(buff, "float") == 0 ? realMAIN(flagFloat++) : (strcmp(buff, "int") == 0 ? realMAIN(flagInt++) : (strcmp(buff, "double") == 0 ? realMAIN(flagDouble++) : (void)flagInt));
		cout << "Incorrect type" << endl;
	}
	
	return 1;
}

/**
 * A templated main(), all driving is here
 * @tparam matrType Type of the matrix to be used
 * @param i Matrix type sample
 */
template <typename matrType>
void realMAIN(matrType i) {
	int height, width;
	bool isProgramShouldClose = false;
	int functionFlag;
	cout << "Input 1 matrix height:";
	cin >> height;
	cout << "Input 1 matrix width:";
	cin >> width;
	matr<matrType> A(height, width);

	cout << "Input 2 matrix height:";
	cin >> height;
	cout << "Input 2 matrix width:";
	cin >> width;
	matr<matrType> B(height, width);
	//matr<matrType> A(3), B(3);
	matrType arfmTMP;

	while (!isProgramShouldClose) {
		system("cls");
		cout << "1 - sum of matrices" << endl
			<< "2 - multiply of matrices" << endl
			<< "3 - sum with scalar" << endl
			<< "4 - multiply with scalar" << endl
			<< "5 - transpose matrix" << endl
			<< "6 - matrix decrement" << endl
			<< "7 - normalize matrix" << endl
			<< ">";
		cin >> functionFlag;
		switch (functionFlag) {
		case 0:
			isProgramShouldClose = true;
			break;
		case 1: // sum of matrices
			system("cls");
			if (A.GetH() != B.GetH() || A.GetW() != B.GetW()) {
				cout << "Incorrect matrix size." << endl;
				break;
			}
			else
				(A + B).show();
			system("pause");
			break;
		case 2: // power of matrices
			system("cls");
			cout << "0 - A * B" << endl << "1 - B * A" << endl << ">";
			cin >> functionFlag;
			while (functionFlag != 0 && functionFlag != 1) {
				cout << "Incorrect command." << endl;
				cin >> functionFlag;
			}
			if (functionFlag == 0) {
				if (A.GetW() != B.GetH()) {
					cout << "Incorrect matrix size." << endl;
					break;
				}
				system("cls");
				(A * B).show();
				system("pause");
				break;
			}
			else {
				if (B.GetW() != A.GetH()) {
					cout << "Incorrect matrix size." << endl;
					break;
				}
				system("cls");
				(B * A).show();
				system("pause");
				break;
			}
		case 3: // sum with scalar
			system("cls");
			cout << "Input number:";
			cin >> arfmTMP;
			(A + arfmTMP).show();
			system("pause");
			break;
		case 4: // multiply by scalar
			system("cls");
			cout << "Input number:";
			cin >> arfmTMP;
			(A * arfmTMP).show();
			system("pause");
			break;
		case 5: // transpose
			system("cls");
			cout << "0 - transpose matrix A" << endl << "1 - transpose matrix B" << endl << ">";
			cin >> functionFlag;
			while (functionFlag != 0 && functionFlag != 1) {
				system("cls");
				cout << "Incorrect command." << endl;
				cout << "0 - transpose matrix A" << endl << "1 - transpose matrix B" << endl << ">";
				cin >> functionFlag;
			}
			system("cls");
			if (!functionFlag) {
				A.transpose();
				A.show();
				system("pause");
				break;
			}
			else {
				B.transpose();
				B.show();
				system("pause");
				break;
			}
		case 6: // decrement
			system("cls");
			cout << "0 - decrement matrix A" << endl << "1 - decrement matrix B" << endl << ">";
			cin >> functionFlag;
			while (functionFlag != 0 && functionFlag != 1) {
				system("cls");
				cout << "Incorrect command" << endl;
				cout << "0 - decrement matrix A" << endl << "1 - decrement matrix B" << endl << ">";
				cin >> functionFlag;
			}
			system("cls");
			if (!functionFlag) {
				cout << A.decrement() << endl;
				system("pause");
				break;
			}
			else {
				cout << B.decrement() << endl;
				system("pause");
				break;
			}
		case 7: // matrix normalize
			system("cls");
			cout << "0 - normalize matrix A" << endl << "1 - normalize matrix B" << endl << ">";
			cin >> functionFlag;
			while (functionFlag != 0 && functionFlag != 1) {
				system("cls");
				cout << "Incorrect command." << endl;
				cout << "0 - normalize matrix A" << endl << "1 - normalize matrix B" << endl << ">";
				cin >> functionFlag;
			}
			system("cls");
			if (!functionFlag) {
				cout << "0 - normalize of height" << endl << "1 - normalize of width" << endl << ">";
				cin >> functionFlag;
				while (functionFlag != 0 && functionFlag != 1) {
					system("cls");
					cout << "Incorrect command." << endl;
					cout << "0 - normalize of height" << endl << "1 - normalize of width" << endl << ">";
					cin >> functionFlag;
				}
				system("cls");
				if (!functionFlag) {
					cout << "Input number of height in [1;" << A.GetH() << "]" << endl << ">";
					cin >> functionFlag;
					while (functionFlag >= 1 || functionFlag <= A.GetH()) {
						system("cls");
						cout << "Incorrect size." << endl;
						cout << "Input number of height in [1;" << A.GetH() << "]" << endl << ">";
						cin >> functionFlag;
					}
					A.normalizeH(functionFlag - 1);
					A.show();
					system("pause");
					break;
				}
				else {
					cout << "Input number of width in [1;" << A.GetW() << "]" << endl << ">";
					cin >> functionFlag;
					while (functionFlag >= 1 || functionFlag <= A.GetW()) {
						system("cls");
						cout << "Incorrect size." << endl;
						cout << "Input number of height in [1;" << A.GetW() << "]" << endl << ">";
						cin >> functionFlag;
					}
					A.normalizeW(functionFlag - 1);
					A.show();
					system("pause");
					break;
				}
			}
			else {
				cout << "0 - normalize of height" << endl << "1 - normalize of width" << endl << ">";
				cin >> functionFlag;
				while (functionFlag != 0 && functionFlag != 1) {
					system("cls");
					cout << "Incorrect command." << endl;
					cout << "0 - normalize of height" << endl << "1 - normalize of width" << endl << ">";
					cin >> functionFlag;
				}
				system("cls");
				if (!functionFlag) {
					cout << "Input number of height in [1;" << B.GetH() << "]" << endl << ">";
					cin >> functionFlag;
					while (functionFlag >= 1 || functionFlag <= B.GetH()) {
						system("cls");
						cout << "Incorrect size." << endl;
						cout << "Input number of height in [1;" << B.GetH() << "]" << endl << ">";
						cin >> functionFlag;
					}
					B.normalizeH(functionFlag - 1);
					B.show();
					system("pause");
					break;
				}
				else {
					cout << "Input number of width in [1;" << B.GetW() << "]" << endl << ">";
					cin >> functionFlag;
					while (functionFlag >= 1 || functionFlag <= B.GetW()) {
						system("cls");
						cout << "Incorrect size." << endl;
						cout << "Input number of height in [1;" << B.GetW() << "]" << endl << ">";
						cin >> functionFlag;
					}
					B.normalizeW(functionFlag - 1);
					B.show();
					system("pause");
					break;
				}
			}
		default:
			cout << "Incorrect command." << endl;
		}
	}
}