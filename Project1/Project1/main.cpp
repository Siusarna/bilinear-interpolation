#include "image.h"
int main() {
	image first("t2_24.bmp");
	image second(first, 1);
	BMPHEAD ng;
	cout << sizeof(ng) << endl;
	cout << sizeof(ng.biClrImportant) << endl;
	cout << sizeof(ng.biClrUsed) << endl;
	cout << sizeof(ng.biCompression) << endl;
	cout << sizeof(ng.biPlanes) << endl;
	cout << sizeof(ng.biSizeImage) << endl;
	cout << sizeof(ng.bits) << endl;
	cout << sizeof(ng.biXPelsPerMeter) << endl;
	cout << sizeof(ng.biYPelsPerMeter) << endl;
	cout << sizeof(ng.depth) << endl;
	cout << sizeof(ng.filesize) << endl;
	cout << sizeof(ng.headersize) << endl;
	cout << sizeof(ng.id) << endl;
	cout << sizeof(ng.infoSize) << endl;
	cout << sizeof(ng.reserved) << endl;
	cout << sizeof(ng.width) << endl;
	system("pause");
	return 0;
}