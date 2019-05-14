#include "image.h"

int main(int argc, char* argv[]) {
	string pathRead;
	string pathSave;
	double coefficient;
	getArguments(argc, argv, pathRead, pathSave, coefficient);
	imageReader reader;
	imageResizer resizer;
	imageSaver saver;
	image first = reader.read(pathRead);
	image second = resizer.resize(first, coefficient);
	saver.save(second, pathSave);
	system("pause");
	return 0;
}