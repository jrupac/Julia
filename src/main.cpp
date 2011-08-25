#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <string>
#include <complex>
#include <stdio.h>

#include "main.h"
#include "bmp.h"

float INIT_X = INIT_X_DEFAULT;
float INIT_Y = INIT_Y_DEFAULT; 
float FINAL_X = FINAL_X_DEFAULT; 
float FINAL_Y = FINAL_Y_DEFAULT; 
float PRECISION = PRECISION_DEFAULT; 
int WINDOW_X = WINDOW_X_DEFAULT;
int WINDOW_Y = WINDOW_Y_DEFAULT;
int ITR = ITR_DEFAULT;
bool _contrast_map = true;

static const string FILENAME = "out.bmp"; 
//static const complex<float> _z_start(-0.74543f, 0.11301f);
//static const complex<float> _z_start(-0.8f, 0.156f);
static const complex<float> _z_start(-0.75f, 0.11f);

#ifdef _USE_RANDOM
int **colors;
#endif
char **image;

static string inline input(string prompt)
{
    cout << prompt;
    string in;
    getline(cin, in);
    return in;
}

void initRendering() 
{
    string in;
    
    cout << "Mandelbrot Set Generator" << endl;
    
    in = input("Enter Initial x-value (Hit Enter for default value): ");
 
    if (in.length()) 
        INIT_X = atof(in.c_str());
    
    in = input("Enter Initial y-value (Hit Enter for default value): ");
    
    if (in.length()) 
        INIT_Y = atof(in.c_str());
    
    in = input("Enter Width to be Rendered (Hit Enter for default value): ");
    
    if (in.length()) 
    {
        FINAL_X = INIT_X + atof(in.c_str());
        FINAL_Y = INIT_Y + atof(in.c_str());
    }
    
    in = input("Enter Precision (Hit Enter for default value): ");
    
    if (in.length()) 
        PRECISION = atof(in.c_str());
    
    in = input("Enter Number of Iterations (Hit Enter for default value): ");
    
    if (in.length()) 
        ITR = atoi(in.c_str());
    
    in = input("Render with Contrast Map? (Y/N) (Hit Enter for default value): ");
    
    if (in.length() && !in.compare("Y")) 
        _contrast_map = true;
    
    WINDOW_X = (FINAL_X - INIT_X) / PRECISION;
    WINDOW_Y = (FINAL_Y - INIT_Y) / PRECISION;

#ifdef _USE_RANDOM
    colors = (int**)calloc(ITR+1, sizeof(int*));
    srand(time(NULL));
    for (int i = 0; i <= ITR; i++)
    {
        int *ci = (int*)calloc(3, sizeof(int));
        for (int j = 0; j < 3; j++)
            ci[j] = rand() % 255;
        colors[i] = ci;
    }
#endif

    image = (char**)calloc((WINDOW_X+1) * (WINDOW_Y+1), sizeof(char*));
    for (int i = 0; i < (WINDOW_X+1) * (WINDOW_Y+1); i++)
        image[i] = (char*)calloc(3, sizeof(char));
}

void color(int itr, int x, int y)
{
#if defined _BUDDHABROT || defined _ABUDDHABROT
    image[x * WINDOW_Y + y][0] = CLAMP(image[x * WINDOW_Y + y][0] + 8, 0, 255);
    image[x * WINDOW_Y + y][1] = CLAMP(image[x * WINDOW_Y + y][1] + 8, 0, 255);
    image[x * WINDOW_Y + y][2] = CLAMP(image[x * WINDOW_Y + y][2] + 8, 0, 255);
    return;
#endif

#ifdef _USE_RANDOM
    int r = colors[itr][0], g = colors[itr][1], b = colors[itr][2];
#else
    int r = 0, g = (int)((itr * 255.0)/ITR), b = g;
#endif
    image[x * WINDOW_Y + y][0] = (char)r;
    image[x * WINDOW_Y + y][1] = (char)g;
    image[x * WINDOW_Y + y][2] = (char)b;
}

void update(vector<complex<float> > path)
{
    for (int i = 0; i < path.size(); i++)
    {
        int ix = (real(path[i]) - INIT_X) / PRECISION;
        int iy = (imag(path[i]) - INIT_Y) / PRECISION;
        color(0, ix, iy);
    }
}

void render(int x, int y) 
{   
    complex<float> _z_current(INIT_X  + ((float)x / WINDOW_X) * (FINAL_X - INIT_X),
                            FINAL_Y - ((float)y / WINDOW_Y) * (FINAL_Y - INIT_Y));
#ifdef _BUDDHABROT
    vector<complex<float> > path;
#endif

    for (int i = 0; i < ITR; i++)
    {
        _z_current = _z_current * _z_current + _z_start;

        if (abs(_z_current) >= 2.0f)
        {
#ifdef _BUDDHABROT
            update(path);
#else
            (_contrast_map) ? color(i, x-1, y-1) : color(0, x-1, y-1);
#endif
            return;
        }
#ifdef _BUDDHABROT
        path.push_back(_z_current);
#endif
    }
#ifdef _ABUDDHABROT
    update(path);
#endif
    color(ITR, x-1, y-1);
}

int main(int argc, char** argv) 
{ 
    initRendering();
    for (int y = 1; y <= WINDOW_Y; y++)
    {
        for (int x = 1; x <= WINDOW_X; x++)
        {
            long index = (y-1) * WINDOW_X + (x-1);
            if (index % (WINDOW_X * WINDOW_Y / 10) == 0)
                cout << (index+0.) / (WINDOW_Y * WINDOW_X) * 100 << "\% done" << endl;
            render(x, y);
        }
    }
    write_bmp(FILENAME, image);
 
    return 0; 
}

