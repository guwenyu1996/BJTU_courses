// ===============================================================================
// Project Name        :    LSB
// Project Description :    LSB隐藏信息
// ===============================================================================
// Class Name          :    Encode
// Class Description   :    
// Author              :    guwenyu
// Create Time         :    2017/5/22 17:21:28
// ===============================================================================
// Copyright © gwy 2017 . All rights reserved.
// ===============================================================================

#include <iostream>
#include <fstream>
#include <cmath>
#include <bitset>
#include <windows.h>
#include <atlstr.h>  
#include "MyBMP.h"
#include "Encode.h"
using namespace std;

const int PRENUM = 32;
extern const int MULTIPLE = 8;
extern void byte_to_bit(const UCHAR *puchByte, const int& iByteLen, UCHAR *puchBit, int *pBitLen);
extern void bit_to_byte(const UCHAR *puchBit, const int& iBitLen, UCHAR *puchByte, int* pByteLen);

Encode::Encode()
{
}

Encode::Encode(const char *filename)
{
	//bmp = new MyBMP("BMPtest\\gray256.bmp");
    bmp = new MyBMP(filename);
	//bmp->outputFileheader();


}


Encode::~Encode(void)
{
}

int Encode::getEncodeLen()
{
	// 最大可存储bit长度 = 像素数* - 存储信息长度(32位)
	int num = bmp->getImageDataNum();
	//double stored = (log(num+0.0))/ log(2.0);
	//cout << "stored bit = " << stored << endl;

	return num - 32;
}

//
//void Encode::encode(BYTE* message)
//{
//	// 获取位图数据
//	BYTE *oldimagedata = bmp->getImagedata();
//	int imgDataLen = bmp->getImageDataNum();
//	BYTE *newimagedata = new BYTE[imgDataLen];
//
//	// char* -> CString
//	//CString s = message;
//	//char* pchar = s.GetBuffer();
//
//	// 把隐藏信息转化为比特流
//	int iByteLen = sizeof(message)/sizeof(UCHAR);  //原始字节流长度  
//	int iBitLen = MULTIPLE*iByteLen;                   //比特流长度  
//	UCHAR *puchBit = new UCHAR[iBitLen];  
//	memset(puchBit, 0, iBitLen); 
//
//	int iBitLenX = 0;  // 字节流长度
//	byte_to_bit(message, iByteLen, puchBit, &iBitLenX);  //字节转化为比特流
//
///*	cout << "字节流转化过的位流为: " << endl;  
//	for (int i = 0; i < iBitLen; i++)  
//		printf("%0x",puchBit[i]);  
//	printf("\n");
//
//	
//	UCHAR* puchByte = new UCHAR[1 + iByteLen];  
//	memset(puchByte, 0, 1 + iByteLen);  
//	int iByteLenX = 0; 
//	bit_to_byte(puchBit, iBitLen, puchByte, &iByteLenX); 
//
//	cout << "测试位流转化过的字节流为: " << endl;  
//  
//	for (int i = 0; i < iByteLen; i++)  
//	{  
//		printf("%0x\t",puchByte[i]);  
//	}  
//	printf("\n");  
//
//	cout << "位流转为成的字节流为: " << puchByte << endl; */ 
//	
//
//	// 把隐藏信息转化为bit流
//
//	
//
//	/*UCHAR* puchByte = new UCHAR[1 + iMByteLen];  
//	memset(puchByte, 0, 1 + iMByteLen);  
//	int iByteLenX = 0; 
//	bit_to_byte(mBit, iMBitLen, puchByte, &iByteLenX); 
//
//	cout << "测试位流转化过的字节流为: " << endl;  
//  
//	for (int i = 0; i < iByteLen; i++)  
//	{  
//		printf("%0x\t",puchByte[i]);  
//	}  
//	printf("\n");  
//
//	cout << "位流转为成的字节流为: " << puchByte << endl;*/  
//
//	// 写入隐藏信息长度
//
//
//
//	// 写入隐藏信息
//	int countBit = 0;
//	for(int i = 0; i < imgDataLen; i ++)
//	{
//		BYTE temp = oldimagedata[i];
//
//		unsigned char bits[8];
//		byte_to_bit(temp, bits);  
//		//BYTE changed = bit_to_BYTE(bits);
//
//		printf("BYTE: %c\n", temp);
//		for (int i = 0; i < 8; i++) 
//			printf("%d",bits[i]);
//		printf("\n");
//		//printf("CHANGE BYTE: %c\n", changed);
//
//		// 替换最后一位
//		if(countBit < iBitLen)
//		{
//			bits[7] = puchBit[countBit];
//			countBit ++;
//		}
//		BYTE changed = bit_to_BYTE(bits);
//		newimagedata[i] = changed;
//
//	}
//
//	/*
//	UCHAR* puchByte = new UCHAR[1 + iByteLen];  
//	memset(puchByte, 0, 1 + iByteLen);  
//	int iByteLenX = 0; 
//	bit_to_byte(puchBit, iBitLen, puchByte, &iByteLenX); 
//
//	cout << "测试位流转化过的字节流为: " << endl;  
//  
//	for (int i = 0; i < iByteLen; i++)  
//	{  
//		printf("%0x\t",puchByte[i]);  
//	}  
//	printf("\n");  
//
//	cout << "位流转为成的字节流为: " << puchByte << endl;  
//	*/
//}

void Encode::encode(UCHAR* message)
{
	// encode思路
	// 1. 隐藏信息转化为bit
	// 2. 隐藏信息bit位数转为bit(32位)
	// 3. 读取位图，得到imagedata，先写入bit位数，再写入隐藏信息



	// 隐藏信息转化为比特流(uchar -> bits)
	int iByteLen = strlen((char*)message);  // 原始字节流长度  
	int iBitLen = MULTIPLE*iByteLen;                   // 比特流长度  
	UCHAR *puchBit = new UCHAR[iBitLen];  
	memset(puchBit, 0, iBitLen); 

	int iBitLenX = 0;  // 比特流长度
	byte_to_bit(message, iByteLen, puchBit, &iBitLenX);  // 字节转化为比特流

	// 隐藏信息长度转化为比特流(int -> bits)
	bitset<32> bs(iBitLen);
	string bits = bs.to_string();
	cout << "长度 " + bits << endl;

	// 获取位图数据
	BYTE *oldimagedata = bmp->getImagedata();
	int imgDataLen = bmp->getImageDataNum();
	BYTE *newimagedata = new BYTE[imgDataLen];

	// 替换位图数据
	// 1. 写入隐藏信息长度(32位)
	// 2. 写入隐藏信息
	int countBit = 0;

	string str = "";     // 输出测试用！
	char bit[2] = "";

	for(int i = 0; i < imgDataLen; i ++)
	{
		BYTE temp = oldimagedata[i];

		if(countBit == iBitLenX)
		{
			newimagedata[i] = oldimagedata[i];
			continue;
		}

		// 取每一个byte 转化为bits 替换最后一位
		int tempByteLen = sizeof(temp)/sizeof(BYTE);         // 原始字节流长度 
		BYTE *tempBit = new BYTE[MULTIPLE * tempByteLen + 1];    // bit数组！！！ 
		memset(tempBit, 0, MULTIPLE * tempByteLen + 1); 
		int tempBitLenX = 0;  // 比特流长度
		byte_to_bit(&temp, tempByteLen, tempBit, &tempBitLenX);  //字节转化为比特流

		if(i < PRENUM)   // 写入长度
		{
			byte num = bits[i];
			//cout << num;
			tempBit[7] = num;
		}
		else if(countBit < iBitLenX)  // 写入隐藏信息
		{
			byte num = puchBit[countBit];
			tempBit[7] = num;
			countBit ++;

			sprintf(bit, "%d", num);
			str = str + bit[0];
		}

		// 将替换好的bits 转成byte
		BYTE* tempByte = new UCHAR[1 + iByteLen];  
		memset(tempByte, 0, 1 + iByteLen);  
		int iByteLenX = 0; 
		bit_to_byte(tempBit, tempBitLenX, tempByte, &iByteLenX); // 比特转字节

		newimagedata[i] = tempByte[0];
		printf("i = %d %d\n", i, temp == tempByte[0]);
	}

	cout << "隐藏信息 " + str << endl;  

	// 生成图片
	if(bmp->isGreyPic()) // 灰度图
		createGreyPic(bmp->getWidth(), bmp->getHeight(), newimagedata);
	else  // 真彩
		createRGBPic(bmp->getWidth(), bmp->getHeight(), newimagedata);
}


void Encode::createGreyPic(int width, int length, BYTE *imagedata)
{
	int i;

    BITMAPFILEHEADER newfileheader;
    BITMAPINFOHEADER newinfoheader;

    newfileheader.bfType = 19778;
    newfileheader.bfSize = 14 + 40 + 256 * 4 + width * length * 1;
    newfileheader.bfReserved1 = 0;
    newfileheader.bfReserved2 = 0;
    newfileheader.bfOffBits = 14 + 40 + 256 * 4;

    newinfoheader.biSize = 40;    // 信息头长度
    newinfoheader.biWidth = width;
    newinfoheader.biHeight = length;
    newinfoheader.biPlanes = 1;
    newinfoheader.biBitCount = 8;
    newinfoheader.biCompression = 0;
    newinfoheader.biSizeImage = 0;
    newinfoheader.biXPelsPerMeter = 0;
    newinfoheader.biYPelsPerMeter = 0;
    newinfoheader.biClrUsed = 0;
    newinfoheader.biClrImportant = 0;

    RGBQUAD *newquad = new RGBQUAD[256];
    for (i = 0; i < 256; i++)
    {
        newquad[i].rgbBlue = i;
        newquad[i].rgbGreen = i;
        newquad[i].rgbRed = i;
        newquad[i].rgbReserved = 0;
    }

 	ofstream outputfile("BMPtest\\GreyExample.bmp", ios::binary);	
    if (outputfile)
    {
        outputfile.write((char*)(&newfileheader), sizeof(BITMAPFILEHEADER));
        outputfile.write((char*)(&newinfoheader), sizeof(BITMAPINFOHEADER));
        outputfile.write((char*)(newquad), sizeof(RGBQUAD) * 256);
        outputfile.write((char*)(imagedata), sizeof(BYTE) * width * length);
        outputfile.close();
        cout << "生成256色度的灰度图片" << endl;
    }

    delete []newquad;
}


void Encode::createRGBPic(int width, int length, BYTE *imagedata)
{

    BITMAPFILEHEADER newfileheader;
    BITMAPINFOHEADER newinfoheader;

    newfileheader.bfType = 19778;
    newfileheader.bfSize = 14 + 40 + width * length * 3;
    newfileheader.bfReserved1 = 0;
    newfileheader.bfReserved2 = 0;
    newfileheader.bfOffBits = 14 + 40 ;

    newinfoheader.biSize = 40;    // 信息头长度
    newinfoheader.biWidth = width;
    newinfoheader.biHeight = length;
    newinfoheader.biPlanes = 1;
    newinfoheader.biBitCount = 24;
    newinfoheader.biCompression = 0;
    newinfoheader.biSizeImage = 0;
    newinfoheader.biXPelsPerMeter = 0;
    newinfoheader.biYPelsPerMeter = 0;
    newinfoheader.biClrUsed = 0;
    newinfoheader.biClrImportant = 0;

 	ofstream outputfile("BMPtest\\RGBExample.bmp", ios::binary);	
    if (outputfile)
    {
        outputfile.write((char*)(&newfileheader), sizeof(BITMAPFILEHEADER));
        outputfile.write((char*)(&newinfoheader), sizeof(BITMAPINFOHEADER));
        outputfile.write((char*)(imagedata), sizeof(BYTE) * width * length * 3);
        outputfile.close();
        cout << "生成24位真彩图" << endl;
    }
}