#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <Windows.h>
#include <iostream>
using namespace std;

#define  UCHAR  unsigned char
const int MULTIPLE = 8;       // 字节流长度是位流的8倍
const int FIX_VAL = 0X01;     // 求&专用特定值
const int g_BinArr[MULTIPLE] = {128,64,32,16,8,4,2,1}; //2的次幂
const unsigned char mask = 1; // Bit mask

/*
**@brief 字节流转为位流
**@param [in]puchByte,字节流;[in]iByteLen，字节流长度; 
   [in&out]puchBit,位流; [in&out]iBitLen,位流长度
**@return 空
*/
void byte_to_bit(const UCHAR *puchByte, const int& iByteLen, UCHAR *puchBit, int *pBitLen)
{
	assert(puchByte != NULL && iByteLen >0 && puchBit != NULL && pBitLen !=NULL);
 
	int iBitLen = 0;
	for (int i = 0; i < iByteLen; i++)
    {
		for(int j = 0; j < MULTIPLE; j++)
		{
			//printf("%0x >> %d = %0x\n", puchByte[i], j, puchByte[i]>>j);
			puchBit[i*MULTIPLE + MULTIPLE - 1 - j] = ((puchByte[i])>>j)&FIX_VAL;
			iBitLen++;
		}//end for j
	}//end for 
 
	*pBitLen = iBitLen;
}


/*
**@brief 位流转为字节流
**@param [in]puchBit,位流;[in]iBitLen，位流长度; 
   [in&out]puchByte,字节流 [in&out]pByteLen,字节流长度
**@return 空
*/
void bit_to_byte(const UCHAR *puchBit, const int& iBitLen, UCHAR *puchByte, int* pByteLen)
{
	assert(puchBit && iBitLen > 0 && puchByte && pByteLen);
	int iByteNo = 0;  
	int iBitInByte = 0;
	for(int i = 0; i < iBitLen; i++)
	{
		iByteNo = i/MULTIPLE;    //字节序号
		iBitInByte = i%MULTIPLE; //字节里的比特序号(0-7)
 
		puchByte[iByteNo] += puchBit[i]*g_BinArr[iBitInByte];  //累计求和
  
		//cout << "iByteNo =:" << iByteNo << "\t iBitInByte = " << iBitInByte \
		//<< "\t puchByte[iByteNo] = " << puchByte[iByteNo] << endl;
	}//end for i
	*pByteLen = iBitLen/MULTIPLE;
}

/*
UCHAR* byte_to_bit()
{
	const UCHAR uchByte[] = "0123456789abcdef";        //原始字节流  
	int iByteLen = sizeof(uchByte)/sizeof(UCHAR) - 1;  //原始字节流长度  
	int iBitLen = MULTIPLE*iByteLen;                   //比特流长度  
	UCHAR *puchBit = new UCHAR[iBitLen];  
	memset(puchBit, 0, iBitLen); 

	int iBitLenX = 0;  
	byte_to_bit(uchByte, iByteLen, puchBit, &iBitLenX);  //字节转化为比特流  

	return puchBit;
}*/

//void byte_to_bit(BYTE byte, unsigned char* bits)
//{
//	for (int i = 0; i < 8; i++) 
//	{
//		// Mask each bit in the byte and store it
//		bits[i] = (byte & (mask << i)) != 0;;
//	}
//}

//BYTE bit_to_BYTE(unsigned char* bits)
//{
//	BYTE byte = 0;
//	for (int i = 0; i < 8; i++)
//	{
//		//byte += bits[i] - '0';
//		byte |= bits[i] & 1;
//		byte<<=1;
//	}
//	
//	return byte;
//}
