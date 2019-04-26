#include "image.h"
int main() {
	image first("t2_24.bmp");
	image second;
	image third(first,second, 2);
	cout << sizeof(BMPHEAD) << endl;
	system("pause");
	return 0;
}