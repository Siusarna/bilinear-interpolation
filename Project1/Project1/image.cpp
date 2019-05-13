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

void imageReader::readImage(string path)
{
	//image img;

	PIXELDATA rgb_l; //empty pixel

	FILE* f1;
	f1 = fopen((char*)& path, "rb");

	fread(&this->info, sizeof(info), 1, f1);

	size_t padding = 0;//зміщення байт
	if ((this->info.width * 3) % 4)
	{
		padding = 4 - (this->info.width * 3) % 4;
	};
	this->padding = padding;
	this->arr = new PIXELDATA * [this->info.depth];
	for (int i = 0; i < this->info.depth; i++) {
		this->arr[i] = new PIXELDATA[this->info.width];
	}
	for (int i = 0; i < this->info.depth; i++) {
		for (int j = 0; j < this->info.width; j++) {
			fread((char*)& this->arr[i][j].rgbBlue, 1, 1, f1);
			fread((char*)& this->arr[i][j].rgbGreen, 1, 1, f1);
			fread((char*)& this->arr[i][j].rgbRed, 1, 1, f1);
		}
		if (padding != 0) fread(&rgb_l, 1, padding, f1);
	}
}
/*
	void imageResizer::resize(image& first, image& second, double coefficient) //TODO:Algorithm
	{
		return;
	}
	*/

	void imageWriter::writeImage(string path, image &img)
	{
		FILE* f2;
		f2 = fopen("result.bmp", "wb");
		int8_t d = 0xFF;
		fwrite(&img.getHeader(), sizeof(img.getHeader()), 1, f2);
		for (int i = 0; i < img.getHeader().depth; i++)
		{
			for (int j = 0; j < img.getHeader().width; j++) {

				fwrite((char*)& img.getPixelData()[i][j].rgbBlue, 1, 1, f2);
				fwrite((char*)& img.getPixelData()[i][j].rgbGreen, 1, 1, f2);
				fwrite((char*)& img.getPixelData()[i][j].rgbRed, 1, 1, f2);
			}
			if (img.getPadding() != 0)
			{
				int p = 0;
				while (p < img.getPadding()) {
					fwrite(&d, 1, 1, f2);
					p++;
				}
			}
		}
	}

	void getArguments(int argc, char* argv[], string &pathRead, string &pathSave, int &coefficient) {

		pathRead = argv[1];
		pathSave = argv[2];
		string coef = argv[3];
		coefficient = stoi(coef);

	}