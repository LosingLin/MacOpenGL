//
//  MYImage.c
//  MacOpenGL
//
//  Created by qiusnay on 13-9-26.
//  Copyright (c) 2013年 qiusnay. All rights reserved.
//

#include "MYImage.h"
#include <string.h>

void initMYImage(const char *fileName)
{
    //init FileHeader
    m_bmpFileHeader = malloc(sizeof(BMPFileHeader));
    
    //init InfoHeader
    m_bmpInfoHeader = malloc(sizeof(BMPInfoHeader));
    
    //init FILE
    size_t rootPathLength = strlen(PROJECTPATH);
    size_t fileNameLength = strlen(fileName);
    char *filePath = malloc(sizeof(char) * (rootPathLength + fileNameLength));
    filePath = strcat(filePath, PROJECTPATH);
    filePath = strcat(filePath, fileName);
    m_fpbmp = fopen(filePath, "rb+");
    if (!m_fpbmp)
    {
        printf("open %s fail", fileName);
        MY_SAFE_FREE(filePath);
        destoryMYImage();
        exit(0);
    }
    MY_SAFE_FREE(filePath);
}

void destoryMYImage()
{
    MY_SAFE_FREE(m_bmpFileHeader);
    MY_SAFE_FREE(m_bmpInfoHeader);
    fclose(m_fpbmp);
}

void bmpFileTest()
{
    fseek(m_fpbmp, 0L, SEEK_SET);
    fread(&(m_bmpFileHeader->bfType), sizeof(char), 2, m_fpbmp);

    printf("bmp type = %d", m_bmpFileHeader->bfType);
}

void readBmpFileHeader()
{
    fseek(m_fpbmp, 0L, SEEK_SET);
    
    fread(&(m_bmpFileHeader->bfType), sizeof(char), 2, m_fpbmp);
    fread(&(m_bmpFileHeader->bfSize), sizeof(char), 4, m_fpbmp);
    fread(&(m_bmpFileHeader->bfReserved1), sizeof(char), 2, m_fpbmp);
    fread(&(m_bmpFileHeader->bfReserved2), sizeof(char), 2, m_fpbmp);
    fread(&(m_bmpFileHeader->bfOffBits), sizeof(char), 4, m_fpbmp);
    
    printf("************************************************\n");
    printf("*************tagBITMAPFILEHEADER info***********\n");
    printf("************************************************\n");
    printf("bfType              is %d.\n", m_bmpFileHeader->bfType);
    printf("bfSize              is %lu.\n", m_bmpFileHeader->bfSize);
    printf("bfReserved1         is %d.\n", m_bmpFileHeader->bfReserved1);
    printf("bfReserved2         is %d.\n", m_bmpFileHeader->bfReserved2);
    printf("bfOffBits           is %lu.\n", m_bmpFileHeader->bfOffBits);
}

void readBmpInfoHeader()
{
    fseek(m_fpbmp, 14L, SEEK_SET);
    
    fread(&(m_bmpInfoHeader->biSize),          sizeof(char), 4, m_fpbmp); //18
    fread(&(m_bmpInfoHeader->biWidth),         sizeof(char), 4, m_fpbmp);  
    fread(&(m_bmpInfoHeader->biHeight),        sizeof(char), 4, m_fpbmp);
    fread(&(m_bmpInfoHeader->biPlanes),        sizeof(char), 4, m_fpbmp);
    fread(&(m_bmpInfoHeader->biBitCount),      sizeof(char), 4, m_fpbmp);
    fread(&(m_bmpInfoHeader->biCompression),   sizeof(char), 4, m_fpbmp);
    fread(&(m_bmpInfoHeader->biSizeImage),     sizeof(char), 4, m_fpbmp);
    fread(&(m_bmpInfoHeader->biXPelsPerMerer), sizeof(char), 4, m_fpbmp);
    fread(&(m_bmpInfoHeader->biYPelsPerMerer), sizeof(char), 4, m_fpbmp);
    fread(&(m_bmpInfoHeader->biClrUsed),       sizeof(char), 4, m_fpbmp);
    fread(&(m_bmpInfoHeader->biClrImportant),  sizeof(char), 4, m_fpbmp);
    
    printf("************************************************\n");
    printf("*************tagBITMAPINFOHEADER info***********\n");
    printf("************************************************\n");
    printf("biSize              is %lu. \n", m_bmpInfoHeader->biSize);
    printf("biWidth             is %lu.\n", m_bmpInfoHeader->biWidth);
    printf("biHeight            is %lu.\n", m_bmpInfoHeader->biHeight);
    printf("biPlanes            is %d. \n", m_bmpInfoHeader->biPlanes);
    printf("biBitCount          is %d. \n", m_bmpInfoHeader->biBitCount);
    printf("biCompression       is %lu. \n", m_bmpInfoHeader->biCompression);
    printf("biSizeImage         is %lu. \n", m_bmpInfoHeader->biSizeImage);
    printf("biXPelsPerMerer     is %lu.\n", m_bmpInfoHeader->biXPelsPerMerer);
    printf("biYPelsPerMerer     is %lu.\n", m_bmpInfoHeader->biYPelsPerMerer);
    printf("biClrUsed           is %lu. \n", m_bmpInfoHeader->biClrUsed);
    printf("biClrImportant      is %lu. \n", m_bmpInfoHeader->biClrImportant);
}

unsigned char* readBmpData(unsigned int* width, unsigned int* height)
{
    unsigned int offset = 0;
    fseek(m_fpbmp, 10L, SEEK_SET);
    fread(&offset, sizeof(char), 4, m_fpbmp);
    printf("------>offset = %d\n", offset);

    fseek(m_fpbmp, 18L, SEEK_SET);
    fread(width, sizeof(char), 4, m_fpbmp);
    fread(height, sizeof(char), 4, m_fpbmp);
    printf("------>width = %d, height = %d\n", *width, *height);
    unsigned long size = 0;
    fseek(m_fpbmp, 34L, SEEK_SET);
    fread(&size, sizeof(char), 4, m_fpbmp);
    printf("------>size = %lu\n", size);
    
    //read data
    fseek(m_fpbmp, offset, SEEK_SET);
    unsigned char* data = malloc(sizeof(char)*size);
    fread(data, sizeof(char)*size, 1, m_fpbmp);
    
    return data;
}

unsigned int getBmpHeaderPartLength()
{
    unsigned int offset = 0;
    fseek(m_fpbmp, 10L, SEEK_SET);
    fread(&offset, sizeof(char), 4, m_fpbmp);
    return offset;
}
