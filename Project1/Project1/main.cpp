#include "image.h"
int main(int argc, char* argv[]) {
	string pathRead, pathSave;
	int coefficient;
	//getArguments(argc, argv, pathRead, pathSave, coefficient);
	//cout << pathRead << " " << pathSave << " " << coefficient << endl;
	image first("test2.bmp");  // цей шлях не працює, воно відкриває файл, шлях якого в image.h 67 рядок і записує в файл який в 95 рядку
	image second;
	image third(first,second, 5);
	system("pause");
	return 0;
}