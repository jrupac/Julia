#ifndef __MAIN_H__
#define __MAIN_H__

#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <complex>
#include <stdio.h>
#include <string.h>
#include <string>

#define WINDOW_X_DEFAULT 600
#define WINDOW_Y_DEFAULT 600
#define INIT_X_DEFAULT -2.0f
#define INIT_Y_DEFAULT -2.0f
#define FINAL_X_DEFAULT 2.0f
#define FINAL_Y_DEFAULT 2.0f
#define PRECISION_DEFAULT 0.001f
#define ITR_DEFAULT 1200

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

//#define _BUDDHABROT
//#define _ABUDDHABROT
#define _USE_RANDOM

using namespace std;

struct BMPHeader
{
    char bfType[2];       /* "BM" */
    int bfSize;           /* Size of file in bytes */
    int bfReserved;       /* set to 0 */
    int bfOffBits;        /* Byte offset to actual bitmap data (= 54) */
    int biSize;           /* Size of BITMAPINFOHEADER, in bytes (= 40) */
    int biWidth;          /* Width of image, in pixels */
    int biHeight;         /* Height of images, in pixels */
    short biPlanes;       /* Number of planes in target device (set to 1) */
    short biBitCount;     /* Bits per pixel (24 in this case) */
    int biCompression;    /* Type of compression (0 if no compression) */
    int biSizeImage;      /* Image size, in bytes (0 if no compression) */
    int biXPelsPerMeter;  /* Resolution in pixels/meter of display device */
    int biYPelsPerMeter;  /* Resolution in pixels/meter of display device */
    int biClrUsed;        /* Number of colors in the color table (if 0, use 
                             maximum allowed by biBitCount) */
    int biClrImportant;   /* Number of important colors.  If 0, all colors 
                             are important */
};

extern float INIT_X, INIT_Y, FINAL_X, FINAL_Y, PRECISION;
extern int WINDOW_X, WINDOW_Y, ITR;
extern bool _contrast_map;

int inline CLAMP(int x, int low, int high)
{
    if (x > high)
        return high;
    if (x < low)
        return low;
    return x;
}

void initRendering();

void color(int itr, int x, int y);

void render(int x, int y);

#endif
