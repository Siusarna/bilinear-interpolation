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
