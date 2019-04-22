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

/*
typedef struct {
	int8_t redComponent;
	int8_t greenComponent;
	int8_t blueComponent;
} PIXELDATA;
*/

class image {
	//BMPHEAD head; - Temporary
	char *pixel;
	string path;
	BMPHEAD info; //Temporary
	int bytesPerLine;

public:
	image(string path) {
		this->path = path;
		ifstream fin(path, ios::binary);
		fin.read((char*)&info, sizeof(info));
		cout << info.depth << endl;

		//int row = (width * 3 + 3) & (~3);

		bytesPerLine = this->info.width * 3;  /* (for 24 bit images) */
		/* round up to a dword boundary */
		if (bytesPerLine & 0x0003)
		{
			bytesPerLine |= 0x0003;
			++bytesPerLine;
		}
		//bh.filesize = bh.headersize + (long)bytesPerLine*bh.depth;
		this->info.filesize = this->info.headersize + (long)bytesPerLine*this->info.depth;
		//pixel = new char[bytesPerLine];
		pixel = (char *)calloc(1, bytesPerLine);
		for (int i = this->info.depth; i >=0; i--) {
			fin.read(pixel,bytesPerLine);
			/*for (int j = 0; j < width * 3; j += 3) {
				temp = pixel[j];
				pixel[j] = pixel[j + 2];
				pixel[j + 2] = temp;
			}*/
		}
		fin.close();
	}
	image(image& first, double coefficient) //TODO: image incease algorithm (use this constructor, Siusarna)
	{
		ofstream out;
		out.open("result.bmp", ios::binary);
		out.write((char*)&first.info, sizeof(first.info));
		for(int i = 0; i<=first.info.depth;i++){
			out.write((char*)&first.pixel[i], first.bytesPerLine);
		}
		out.close();
	}
};