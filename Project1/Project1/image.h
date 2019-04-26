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
	char rgbRed;
	char rgbGreen;
	char rgbBlue;
	char rgbReserved;
};


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
			arr[i] = new PIXELDATA[this->info.width];
		}
		for (int i = 0; i < this->info.depth; i++) {
			fread(arr[i], sizeof(PIXELDATA), this->info.width, f1);
			if (padding != 0) fread(&rgb_l, padding, 1, f1);
		}
		
	}
	image(image& first, image& second, double coefficient) //TODO: image incease algorithm (use this constructor, Siusarna)
	{
		
		FILE *f2;
		f2 = fopen("result.bmp", "wb");

		PIXELDATA rgb_l;
		second.info = first.info;
		second.info.width = first.info.width * coefficient;
		second.info.depth = first.info.depth * coefficient;
		if ((second.info.width * 3) % 4) padding = 4 - (second.info.width * 3) % 4;
		second.padding = padding;
		second.info.biSizeImage = (second.info.depth*second.info.width * 3) + (padding*second.info.width);
		second.info.filesize = second.info.biSizeImage + sizeof(BMPHEAD);
		second.arr = new PIXELDATA*[second.info.depth];
		for (int i = 0; i < second.info.depth; i++) {
			second.arr[i] = new PIXELDATA[second.info.width];
		}

		PIXELDATA temp;
		for (int i = 0; i < first.info.depth; i++) {
			for (int j = 0; j < first.info.width; j++) {
				temp = first.arr[i][j];
				second.arr[i * 2][j * 2] = temp;
				second.arr[i * 2 + 1][j * 2] = temp;
				second.arr[i * 2][j * 2 + 1] = temp;
				second.arr[i * 2 + 1][j * 2 + 1] = temp;
			}
			if (padding != 0) {
				int p = 0;
				PIXELDATA rgb;
				while (p != padding) {
					second.arr[i * 2][second.info.width - p] = rgb;
					second.arr[i * 2 + 1][second.info.width - p] = rgb;
				}
			}
		}




		// write in file
		fwrite(&second.info, sizeof(second.info), 1, f2);
		for (int i = 0; i < second.info.depth; i++)
		{
			fwrite(second.arr[i], sizeof(second.arr), second.info.width, f2);
			if (padding != 0)
			{
				fwrite(&rgb_l, padding, 1, f2);
			}
		}
	}
};