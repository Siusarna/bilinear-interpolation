#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
using namespace std;
/*
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
*/
/*
typedef struct {
	int8_t redComponent;
	int8_t greenComponent;
	int8_t blueComponent;
} PIXELDATA;
*/

class image {
	//BMPHEAD head; - Temporary
	int width, height;
	char *pixel;
	string path;
	char info[54]; //Temporary
public:
	image(string path) {
		this->path = path;
		ifstream fin(path, ios::binary);
		fin.read(info, sizeof(info));
		this->width = *(int*)&info[18];
		this->height = *(int*)& info[22];

		int row = (width * 3 + 3) & (~3);
		pixel = new char[row];
		char temp;
		for (int i = 0; i < this->height; i++) {
			fin.read(pixel, row);
			for (int j = 0; j < width * 3; j += 3) {
				temp = pixel[j];
				pixel[j] = pixel[j + 2];
				pixel[j + 2] = temp;
			}
		}
		fin.close();
	}
	image(image& first, double coefficient) //TODO: image incease algorithm (use this constructor, Siusarna)
	{

	}
};