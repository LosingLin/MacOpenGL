//
//  MYImage.c
//  MacOpenGL
//
//  Created by qiusnay on 13-9-26.
//  Copyright (c) 2013年 qiusnay. All rights reserved.
//

#ifndef __MYIMAGE_C__
#define __MYIMAGE_C__

#include <stdio.h>
#include <stdlib.h>
#include "MY.h"

//BMP文件的文件头
typedef struct tagBMPFileHeader
{
    unsigned int bfType;
    unsigned long bfSize;
    unsigned int bfReserved1;
    unsigned int bfReserved2;
    unsigned long bfOffBits;
}BMPFileHeader;

//BMP文件的图像信息头
typedef struct tagBMPInfoHeader
{
    unsigned long biSize;
    unsigned long biWidth;
    unsigned long biHeight;
    unsigned int biPlanes;
    unsigned int biBitCount;
    unsigned long biCompression;
    unsigned long biSizeImage;
    unsigned long biXPelsPerMerer;
    unsigned long biYPelsPerMerer;
    unsigned long biClrUsed;
    unsigned long biClrImportant;
}BMPInfoHeader;

//unsigned int OffSet = 0;
//long BmpWidth = 0;
//long BmpHeight = 0;

void initMYImage(const char *fileName);
void destoryMYImage();

void bmpFileTest();
void readBmpFileHeader();
void readBmpInfoHeader();
unsigned int getBmpHeaderPartLength();
unsigned char* readBmpData(unsigned int* width, unsigned int* height);

BMPFileHeader* m_bmpFileHeader;
BMPInfoHeader* m_bmpInfoHeader;
FILE* m_fpbmp;

#endif