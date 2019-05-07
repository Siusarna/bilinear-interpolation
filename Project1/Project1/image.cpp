#include "image.h"

void resample(PIXELDATA **a, PIXELDATA **b, int oldw, int oldh, int neww, int newh)
{
	int i;
	int j;
	int l;
	int c;
	float t;
	float u;
	float tmp;
	float d1, d2, d3, d4;
	//unsigned int p1, p2, p3, p4; /* Окрестные пикселы */
	//uint8_t red, green, blue;
	PIXELDATA p1, p2, p3, p4,temp;

	for (i = 0; i < newh; i++) {
		for (j = 0; j < neww; j++) {

			tmp = (float)(i) / (float)(newh - 1) * (oldh - 1);
			l = (int)floor(tmp);
			if (l < 0) {
				l = 0;
			}
			else {
				if (l >= oldh - 1) {
					l = oldh - 2;
				}
			}
			u = tmp - l;

			tmp = (float)(j) / (float)(neww - 1) * (oldw - 1);
			c = (int)floor(tmp);
			if (c < 0) {
				c = 0;
			}
			else {
				if (c >= oldw - 1) {
					c = oldw - 2;
				}
			}
			t = tmp - c;

			/* Коэффициенты */
			d1 = (1 - t) * (1 - u);
			d2 = t * (1 - u);
			d3 = t * u;
			d4 = (1 - t) * u;

			/* Окрестные пиксели: a[i][j] 
			p1 = *((uint8_t*)a + (l * oldw) + c);
			p2 = *((uint8_t*)a + (l * oldw) + c + 1);
			p3 = *((uint8_t*)a + ((l + 1)* oldw) + c + 1);
			p4 = *((uint8_t*)a + ((l + 1)* oldw) + c);

			 Компоненты 
			blue = (uint8_t)p1 * d1 + (uint8_t)p2 * d2 + (uint8_t)p3 * d3 + (uint8_t)p4 * d4;
			green = (uint8_t)(p1 >> 8) * d1 + (uint8_t)(p2 >> 8) * d2 + (uint8_t)(p3 >> 8) * d3 + (uint8_t)(p4 >> 8) * d4;
			red = (uint8_t)(p1 >> 16) * d1 + (uint8_t)(p2 >> 16) * d2 + (uint8_t)(p3 >> 16) * d3 + (uint8_t)(p4 >> 16) * d4;

			 Новый пиксел из R G B  
			*((uint8_t*)b + (i * neww) + j) = (red << 16) | (green << 8) | (blue);*/
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

	//int row = (width * 3 + 3) & (~3);
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

	void imageResizer::resize(image& first, image& second, double coefficient) //TODO:Algorithm
	{

		second.info.depth = first.info.depth*coefficient;
		second.info.width = first.info.width*coefficient;
		int newh = second.info.depth;
		int neww = second.info.width;
		int oldw = first.info.width;
		int oldh = first.info.width;
		PIXELDATA **a = first.arr;
		PIXELDATA **b = second.arr;


		int i;
		int j;
		int l;
		int c;
		float t;
		float u;
		float tmp;
		float d1, d2, d3, d4;
		//unsigned int p1, p2, p3, p4; /* Окрестные пикселы */
		//uint8_t red, green, blue;
		PIXELDATA p1, p2, p3, p4, temp;

		for (i = 0; i < newh; i++) {
			for (j = 0; j < neww; j++) {

				tmp = (float)(i) / (float)(newh - 1) * (oldh - 1);
				l = (int)floor(tmp);
				if (l < 0) {
					l = 0;
				}
				else {
					if (l >= oldh - 1) {
						l = oldh - 2;
					}
				}
				u = tmp - l;

				tmp = (float)(j) / (float)(neww - 1) * (oldw - 1);
				c = (int)floor(tmp);
				if (c < 0) {
					c = 0;
				}
				else {
					if (c >= oldw - 1) {
						c = oldw - 2;
					}
				}
				t = tmp - c;

				/* Коэффициенты */
				d1 = (1 - t) * (1 - u);
				d2 = t * (1 - u);
				d3 = t * u;
				d4 = (1 - t) * u;

				/* Окрестные пиксели: a[i][j]
				p1 = *((uint8_t*)a + (l * oldw) + c);
				p2 = *((uint8_t*)a + (l * oldw) + c + 1);
				p3 = *((uint8_t*)a + ((l + 1)* oldw) + c + 1);
				p4 = *((uint8_t*)a + ((l + 1)* oldw) + c);

				 Компоненты
				blue = (uint8_t)p1 * d1 + (uint8_t)p2 * d2 + (uint8_t)p3 * d3 + (uint8_t)p4 * d4;
				green = (uint8_t)(p1 >> 8) * d1 + (uint8_t)(p2 >> 8) * d2 + (uint8_t)(p3 >> 8) * d3 + (uint8_t)(p4 >> 8) * d4;
				red = (uint8_t)(p1 >> 16) * d1 + (uint8_t)(p2 >> 16) * d2 + (uint8_t)(p3 >> 16) * d3 + (uint8_t)(p4 >> 16) * d4;

				 Новый пиксел из R G B
				*((uint8_t*)b + (i * neww) + j) = (red << 16) | (green << 8) | (blue);*/
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