#include "image.h"

void resample(PIXELDATA **a, PIXELDATA **b, int oldw, int oldh, int neww, int newh)
{
	int i;
	int j;
	int l;
	int c;
	float t;
	int x, y, x_diff, y_diff;
	float x_ratio = ((float)(oldh - 1) / newh);
	float y_ratio = ((float)(oldw - 1) / neww);
	float u;
	float tmp;
	float d1, d2, d3, d4;
	PIXELDATA p1, p2, p3, p4,temp;

	for (i = 0; i < newh; i++) {
		for (j = 0; j < neww; j++) {

			x = (int)(x_ratio*i);
			y = (int)(y_ratio*j);
			x_diff = (x_ratio*i) - x;
			y_diff = (y_ratio*j) - y;
			l = (int)floor(x);
			c = (int)floor(y);
			
			/* Коэффициенты */
			d1 = (1 - x_diff) * (1 - y_diff);
			d2 = x_diff * (1 - y_diff);
			d3 = x_diff * y_diff;
			d4 = (1 - x_diff) * y_diff;

		
			p1 = a[l][c];
			p2 = a[l][c + 1];
			p3 = a[l + 1][c + 1];
			p4 = a[l + 1][c];

			temp.rgbBlue = p1.rgbBlue*d1 + p2.rgbBlue*d2 + p3.rgbBlue*d3 + p4.rgbBlue*d4;
			temp.rgbGreen = p1.rgbGreen*d1 + p2.rgbGreen*d2 + p3.rgbGreen*d3 + p4.rgbGreen*d4;
			temp.rgbRed = p1.rgbRed*d1 + p2.rgbRed*d2 + p3.rgbRed*d3 + p4.rgbRed*d4;

			b[i][j] = temp;
		}
	}
}

void getArguments(int argc, char* argv[], string &pathRead, string &pathSave, double &coefficient) {
	pathRead = argv[1];
	pathSave = argv[2];
	string coef = argv[3];
	coefficient = stoi(coef);

}

image imageReader::read(string path) {
	image im;
	const int n = path.length();
	char *char_path = new char[n + 1];
	strcpy(char_path, path.c_str());
	PIXELDATA rgb_l; //empty pixel

	FILE * f1;
	f1 = fopen(char_path, "rb");
	fread(&im.info, sizeof(im.info), 1, f1);

	size_t padding = 0;//зміщення байт
	if ((im.info.width * 3) % 4) {
		padding = 4 - (im.info.width * 3) % 4;
	}
	im.padding = padding;
	im.arr = new PIXELDATA*[im.info.depth];
	for (int i = 0; i < im.info.depth; i++) {
		im.arr[i] = new PIXELDATA[im.info.width];
	}
	for (int i = 0; i < im.info.depth; i++) {
		for (int j = 0; j < im.info.width; j++) {
			fread((char*)&im.arr[i][j].rgbBlue, 1, 1, f1);
			fread((char*)&im.arr[i][j].rgbGreen, 1, 1, f1);
			fread((char*)&im.arr[i][j].rgbRed, 1, 1, f1);
		}
		if (padding != 0) fread(&rgb_l, 1, padding, f1);
	}
	return im;
}

image imageResizer::resize(image &first,double coefficient) {
	image second;
	int padding; 
	double coef = fabs(coefficient);
	second.info = first.info;
	second.info.width = ceil(first.info.width * coef);
	second.info.depth = ceil(first.info.depth * coef);
	if ((second.info.width * 3) % 4) padding = 4 - (second.info.width * 3) % 4;
	second.padding = padding;
	second.info.biSizeImage = (second.info.depth*second.info.width * 3) + (padding*second.info.width);
	second.info.filesize = second.info.biSizeImage + sizeof(BMPHEAD);
	second.arr = new PIXELDATA*[second.info.depth];
	for (int i = 0; i < second.info.depth; i++) {
		second.arr[i] = new PIXELDATA[second.info.width];
	}
	resample(first.arr, second.arr, first.info.width, first.info.depth, second.info.width, second.info.depth);
	if (coefficient < 0) {
		for (int i = 0; i < (second.info.depth)/2; i++) {
			for (int j =0; j < second.info.width-1; j++) {
				swap(second.arr[i][j], second.arr[second.info.depth - i - 1][second.info.width-j-1]);
			}
		}
	}
	return second;
}

void imageSaver::save(image & im, string path) {
	FILE* f2;
	f2 = fopen("result.bmp", "wb");
	int8_t d = 0xFF;
	fwrite(&im.info, sizeof(im.info), 1, f2);
	for (int i = 0; i < im.info.depth; i++) {
		for (int j = 0; j < im.info.width; j++) {
			fwrite((char*)& im.arr[i][j].rgbBlue, 1, 1, f2);
			fwrite((char*)& im.arr[i][j].rgbGreen, 1, 1, f2);
			fwrite((char*)& im.arr[i][j].rgbRed, 1, 1, f2);
		}
		if (im.padding != 0) {
			int p = 0;
			while (p < im.padding) {
				fwrite(&d, 1, 1, f2);
				p++;
			}
		}
	}
}
