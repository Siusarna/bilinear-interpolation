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
	char *pixel;
	string path;
	BMPHEAD info; //Temporary
	int bytesPerLine;
	PIXELDATA **arr;

public:
	image(string path) {
		this->path = path;
		ifstream fin(path, ios::binary);
		fin.read((char*)&info, sizeof(info));
		cout << info.depth << endl;

		PIXELDATA rgb_l;
		//int row = (width * 3 + 3) & (~3);
		FILE * f1, *f2;

		f1 = fopen("t2_24.bmp", "rb");
		f2 = fopen("result.bmp", "wb");

		size_t padding = 0;//смещение байт
		if ((this->info.width * 3) % 4)
		{
			padding = 4 - (this->info.width * 3) % 4;
		};
		this->arr = new PIXELDATA*[this->info.depth];
		for(int i=0;i<this->info.depth;i++){
			arr[i] = new PIXELDATA[this->info.width];
			/*for (int j = 0; j < width * 3; j += 3) {
				temp = pixel[j];
				pixel[j] = pixel[j + 2];
				pixel[j + 2] = temp;
			}*/
		}
		for (int i = 0; i < this->info.depth; i++) {
			fread(arr[i], sizeof(PIXELDATA), this->info.width, f1);
			if (padding != 0) fread(&rgb_l, padding, 1, f1);
		}
		fin.close();
		for (int i = 0; i < this->info.depth; i++)
		{
			fwrite(this->arr[i], sizeof(arr), this->info.width, f2);
			if (padding != 0)
			{
				fwrite(&rgb_l, padding, 1, f2);
			}
		}
	}
	/*image(image& first, double coefficient) //TODO: image incease algorithm (use this constructor, Siusarna)
	{
		ofstream out;
		out.open("result.bmp", ios::binary);
		out.write((char*)&first.info, sizeof(first.info));
		for (int i = 0; i < arr.size(); i++) {
			out.write((char*)&first.arr, sizeof(first.arr));
		}
		out.close();
	}*/
};