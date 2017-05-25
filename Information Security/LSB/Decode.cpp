// ===============================================================================
// Project Name        :    LSB
// Project Description :    LSB隐藏信息
// ===============================================================================
// Class Name          :    Dncode
// Class Description   :    Extract message.
// Author              :    guwenyu
// Create Time         :    2017/5/23 18:56:28
// ===============================================================================
// Copyright © gwy 2017 . All rights reserved.
// ===============================================================================

#include <Windows.h>
#include <iostream>
#include <string>
#include <bitset>

#include "MyBMP.h"
#include "Decode.h"

using namespace std;

const int PRENUM = 32;
const int MULTIPLE = 8;

extern void byte_to_bit(const UCHAR *puchByte, const int& iByteLen, UCHAR *puchBit, int *pBitLen);
extern void bit_to_byte(const UCHAR *puchBit, const int& iBitLen, UCHAR *puchByte, int* pByteLen);



Decode::Decode(void)
{
}


Decode::~Decode(void)
{
}

Decode::Decode(const char* filename)
{
	//bmp = new MyBMP("BMPtest\\GreyExample.bmp");
	bmp = new MyBMP(filename);
}

void Decode::decode()
{
	// decode思路
	// 获取位图imagedata数据
	// 首先读取前32bit，转成int即为信息bit长度
	// 循环读取bit，转成uchar*

	BYTE *imagedata = bmp->getImagedata();
	int imgDataLen = bmp->getImageDataNum();

	// 读取前32bit
	UCHAR *readBit = new UCHAR[PRENUM];  
	memset(readBit, 0, PRENUM); 
	string str = "";
	char bit[2] = "";
	for(int i = 0; i < 32; i ++)
	{
		BYTE temp = imagedata[i];

		int tempByteLen = sizeof(temp)/sizeof(BYTE);         // 原始字节流长度 
		BYTE *tempBit = new BYTE[MULTIPLE * tempByteLen + 1];    // bit数组！！！ 
		memset(tempBit, 0, MULTIPLE * tempByteLen + 1); 
		int tempBitLenX = 0;  // 比特流长度
		byte_to_bit(&temp, tempByteLen, tempBit, &tempBitLenX);  //字节转化为比特流

		readBit[i] = tempBit[7];
		printf("i = %d  %d\n", i, readBit[i]);
		sprintf(bit, "%d", readBit[i]);
		str = str + bit[0];
		//printf("%s", str);
	}

	cout << str << endl;

	bitset<32> set(str);
	ULONG num = set.to_ulong();
	int bitLen = (int)num;

	// 循环读imagedata
	BYTE *messageBit = new BYTE[bitLen];
	memset(messageBit, 0, bitLen); 

	string strt = "";     // 输出测试用！
	char bitt[2] = "";

	for(int i = 0; i < bitLen; i ++)
	{
		// BYTE -> bits 取最后一位
		BYTE byte = imagedata[i + 32];
		int byteLen = sizeof(byte)/sizeof(BYTE);
		BYTE *bits = new BYTE[MULTIPLE * byteLen + 1];    // bit数组！！！ 
		memset(bits, 0, MULTIPLE * byteLen + 1); 
		int bitLenX = 0;  // 比特流长度
		byte_to_bit(&byte, byteLen, bits, &bitLenX);  //字节转化为比特流

		messageBit[i] = bits[7];
		printf("i = %d  %d\n", i + 32, bits[7]);

		sprintf(bitt, "%d", bits[7]);
		strt = strt +  bitt[0];
	}

	cout << str << endl;

	// bits -> byte
	BYTE *messageByte = new BYTE[bitLen/MULTIPLE + 1];
	memset(messageByte, 0, bitLen/MULTIPLE + 1); 
	int messageByteLen = 0;
	bit_to_byte(messageBit, bitLen, messageByte, &messageByteLen); // 比特转字节
	
	cout << "测试位流转化过的字节流为: " << endl;  
  
	for (int i = 0; i < messageByteLen; i++)  
	{  
		printf("%0x\t",messageByte[i]);  
	}  
	printf("\n");  

	cout << "位流转为成的字节流为: " << messageByte << endl;  

}
