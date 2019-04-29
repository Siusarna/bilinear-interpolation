#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
using namespace std;


#pragma pack(2)
typedef struct {
	int8_t id[2];			
	int32_t filesize;        
	int16_t reserved[2];    
	int32_t headersize;      
	int32_t infoSize;        
	int32_t width;           
	int32_t depth;           
	int16_t biPlanes;        
	int16_t bits;           
	int32_t biCompression;   
	int32_t biSizeImage;     
	int32_t biXPelsPerMeter; 
	int32_t biYPelsPerMeter; 
	int32_t biClrUsed;      
	int32_t biClrImportant; 
} BMPHEAD;


struct PIXELDATA
{
	int8_t rgbRed;
	int8_t rgbGreen;
	int8_t rgbBlue;
	int8_t rgbReserved;
	PIXELDATA() : rgbBlue(), rgbGreen(), rgbRed() {}
};

void resample(PIXELDATA **a, PIXELDATA **b, int oldw, int oldh, int neww, int newh);

class image {
	//BMPHEAD head; - Temporary
	string path;
	BMPHEAD info; //Temporary
	PIXELDATA **arr;
	int padding;

public:
	image() {}
	image(string path) {
		this->path = path;

		PIXELDATA rgb_l; //empty pixel

		//int row = (width * 3 + 3) & (~3);
		FILE * f1;
		f1 = fopen("t2_24.bmp", "rb");

		fread(&this->info, sizeof(info), 1, f1);

		size_t padding = 0;//зміщення байт
		if ((this->info.width * 3) % 4)
		{
			padding = 4 - (this->info.width * 3) % 4;
		};
		this->padding = padding;
		this->arr = new PIXELDATA*[this->info.depth];
		for(int i=0;i<this->info.depth;i++){
			this->arr[i] = new PIXELDATA[this->info.width];
		}
		for (int i = 0; i < this->info.depth; i++) {
			for (int j = 0; j < this->info.width; j++) {
				fread((char*)&this->arr[i][j].rgbBlue, 1, 1, f1);
				fread((char*)&this->arr[i][j].rgbGreen, 1, 1, f1);
				fread((char*)&this->arr[i][j].rgbRed, 1, 1, f1);
			}
			if (padding != 0) fread(&rgb_l, 1, padding, f1);
		}
		
	}
	image(image& first, image& second, double coefficient) //TODO: image incease algorithm (use this constructor, Siusarna)
	{
		PIXELDATA rgb;
		FILE *f2;
		f2 = fopen("result.bmp", "wb");

		second.info = first.info;
		second.info.width = ceil(first.info.width * coefficient);
		second.info.depth = ceil(first.info.depth * coefficient);
		if ((second.info.width * 3) % 4) padding = 4 - (second.info.width * 3) % 4;
		second.padding = padding;
		second.info.biSizeImage = (second.info.depth*second.info.width * 3) + (padding*second.info.width);
		second.info.filesize = second.info.biSizeImage + sizeof(BMPHEAD);
		second.arr = new PIXELDATA*[second.info.depth];
		for (int i = 0; i < second.info.depth; i++) {
			second.arr[i] = new PIXELDATA[second.info.width];
		}

		resample(first.arr, second.arr, first.info.width, first.info.depth, second.info.width, second.info.depth);
		/*temp.rgbBlue = 0x00;
		temp.rgbGreen = 0x00;
		temp.rgbRed = 0x00;
		for (int j = 0; j < second.info.depth; j++) {
			for (int i = 0; i < second.info.width; i++) {
				second.arr[j][i] = temp;
			}
		}*/

		int8_t d = 0xFF;
		// write in file
		fwrite(&second.info, sizeof(second.info), 1, f2);
		for (int i = 0; i < second.info.depth; i++)
		{
			for (int j = 0; j < second.info.width; j++) {

				fwrite((char*)&second.arr[i][j].rgbBlue, 1, 1, f2);
				fwrite((char*)&second.arr[i][j].rgbGreen, 1, 1, f2);
				fwrite((char*)&second.arr[i][j].rgbRed, 1, 1, f2);
			}
			if (second.padding != 0)
			{
				int p = 0;
				while (p < second.padding) {
					fwrite(&d, 1, 1, f2);
					p++;
				}
			}
		}
	}
};