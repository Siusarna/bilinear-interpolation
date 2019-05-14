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

class image {
protected:
	PIXELDATA **arr;
	int padding;
	BMPHEAD info;
public:
	friend class imageReader;
	friend class imageResizer;
	friend class imageSaver;
};

class imageReader {
public:
	image read(string path);
};

class imageResizer {
public:
	image resize(image &first,int coefficient);
};

class imageSaver {
public:
	void save(image &im, string path);
};
void getArguments(int argc, char* argv[], string &pathRead, string &pathSave, double &coefficient);
