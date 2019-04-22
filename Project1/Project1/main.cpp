#include "image.h"
int main() {
	image first("t2_24.bmp");
	image second(first, 1);
	cout << sizeof(BMPHEAD) << endl;
	system("pause");
	return 0;
}