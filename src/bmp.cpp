#include "main.h"
#include "bmp.h"

int write_bmp(string filename, char **rgb)
{
    int i, j, ipos;
    int bytesPerLine;
    unsigned char *line;

    FILE *file;
    struct BMPHeader bmph;

    /* The length of each line must be a multiple of 4 bytes */

    bytesPerLine = (3 * (WINDOW_X + 1) / 4) * 4;
    strcpy(bmph.bfType, "BM");
    bmph.bfOffBits = 54;
    bmph.bfSize = bmph.bfOffBits + bytesPerLine * WINDOW_Y;
    bmph.bfReserved = 0;
    bmph.biSize = 40;
    bmph.biWidth = WINDOW_X;
    bmph.biHeight = WINDOW_Y;
    bmph.biPlanes = 1;
    bmph.biBitCount = 24;
    bmph.biCompression = 0;
    bmph.biSizeImage = bytesPerLine * WINDOW_Y;
    bmph.biXPelsPerMeter = 0;
    bmph.biYPelsPerMeter = 0;
    bmph.biClrUsed = 0;       
    bmph.biClrImportant = 0; 

    file = fopen(filename.c_str(), "wb");
    if (!file) 
        return(0);
  
    fwrite(&bmph.bfType, 2, 1, file);
    fwrite(&bmph.bfSize, 4, 1, file);
    fwrite(&bmph.bfReserved, 4, 1, file);
    fwrite(&bmph.bfOffBits, 4, 1, file);
    fwrite(&bmph.biSize, 4, 1, file);
    fwrite(&bmph.biWidth, 4, 1, file);
    fwrite(&bmph.biHeight, 4, 1, file);
    fwrite(&bmph.biPlanes, 2, 1, file);
    fwrite(&bmph.biBitCount, 2, 1, file);
    fwrite(&bmph.biCompression, 4, 1, file);
    fwrite(&bmph.biSizeImage, 4, 1, file);
    fwrite(&bmph.biXPelsPerMeter, 4, 1, file);
    fwrite(&bmph.biYPelsPerMeter, 4, 1, file);
    fwrite(&bmph.biClrUsed, 4, 1, file);
    fwrite(&bmph.biClrImportant, 4, 1, file);
  
    line = (unsigned char*)malloc(bytesPerLine);
    if (!line)
    {
        fprintf(stderr, "Can't allocate memory for BMP file.\n");
        return 0;
    }

    for (i = WINDOW_Y - 1; i >= 0; i--)
    {
        for (j = 0; j < WINDOW_X; j++)
        {
            ipos = (WINDOW_Y * j+ i);
            line[3*j] = rgb[ipos][2];
            line[3*j+1] = rgb[ipos][1];
            line[3*j+2] = rgb[ipos][0];
        }

        fwrite(line, bytesPerLine, 1, file);
    }

    free(line);
    fclose(file);

    return 1;
}

