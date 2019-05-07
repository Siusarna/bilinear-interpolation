#include "image.h"
int main(int argc, char* argv[]) {
	string pathRead, pathSave;
	int coefficient;
	getArguments(argc, argv, pathRead, pathSave, coefficient);
	cout << pathRead << " " << pathSave << " " << coefficient << endl;
	image first("t2_24.bmp");
	image second;
	image third(first,second, 2);
	system("pause");
	return 0;
}