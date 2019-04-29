#include "image.h"
int main() {
	image first("Screenshot_3.bmp");
	image second;
	image third(first,second, 2);
	system("pause");
	return 0;
}