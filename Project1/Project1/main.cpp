#include "image.h"
int main(int argc, char* argv[]) {
	string pathRead, pathSave;
	int coefficient;
	//getArguments(argc, argv, pathRead, pathSave, coefficient);
	//cout << pathRead << " " << pathSave << " " << coefficient << endl;
	image first("test2.bmp");  // ��� ���� �� ������, ���� ������� ����, ���� ����� � image.h 67 ����� � ������ � ���� ���� � 95 �����
	image second;
	image third(first,second, 5);
	system("pause");
	return 0;
}