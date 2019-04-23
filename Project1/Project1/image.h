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
	image(image& first, double coefficient) //TODO: image incease algorithm (use this constructor, Siusarna)
	{
		
		FILE *f2;
		f2 = fopen("result.bmp", "wb");

		PIXELDATA rgb_l;

		this->info.width = first.info.width * coefficient;
		this->info.depth = first.info.depth * coefficient;
		if ((this->info.width * 3) % 4) padding = 4 - (this->info.width * 3) % 4;
		this->padding = padding;
		this->arr = new PIXELDATA*[this->info.depth];
		for (int i = 0; i < this->info.depth; i++) {
			arr[i] = new PIXELDATA[this->info.width];
		}



		fwrite(&this->info, sizeof(this->info), 1, f2);
		for (int i = 0; i < this->info.depth; i++)
		{
			fwrite(this->arr[i], sizeof(this->arr), this->info.width, f2);
			if (padding != 0)
			{
				fwrite(&rgb_l, padding, 1, f2);
			}
		}
	}
};