#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <Windows.h>
#include <iostream>
using namespace std;

#define  UCHAR  unsigned char
const int MULTIPLE = 8;       // �ֽ���������λ����8��
const int FIX_VAL = 0X01;     // ��&ר���ض�ֵ
const int g_BinArr[MULTIPLE] = {128,64,32,16,8,4,2,1}; //2�Ĵ���
const unsigned char mask = 1; // Bit mask

/*
**@brief �ֽ���תΪλ��
**@param [in]puchByte,�ֽ���;[in]iByteLen���ֽ�������; 
   [in&out]puchBit,λ��; [in&out]iBitLen,λ������
**@return ��
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
**@brief λ��תΪ�ֽ���
**@param [in]puchBit,λ��;[in]iBitLen��λ������; 
   [in&out]puchByte,�ֽ��� [in&out]pByteLen,�ֽ�������
**@return ��
*/
void bit_to_byte(const UCHAR *puchBit, const int& iBitLen, UCHAR *puchByte, int* pByteLen)
{
	assert(puchBit && iBitLen > 0 && puchByte && pByteLen);
	int iByteNo = 0;  
	int iBitInByte = 0;
	for(int i = 0; i < iBitLen; i++)
	{
		iByteNo = i/MULTIPLE;    //�ֽ����
		iBitInByte = i%MULTIPLE; //�ֽ���ı������(0-7)
 
		puchByte[iByteNo] += puchBit[i]*g_BinArr[iBitInByte];  //�ۼ����
  
		//cout << "iByteNo =:" << iByteNo << "\t iBitInByte = " << iBitInByte \
		//<< "\t puchByte[iByteNo] = " << puchByte[iByteNo] << endl;
	}//end for i
	*pByteLen = iBitLen/MULTIPLE;
}

/*
UCHAR* byte_to_bit()
{
	const UCHAR uchByte[] = "0123456789abcdef";        //ԭʼ�ֽ���  
	int iByteLen = sizeof(uchByte)/sizeof(UCHAR) - 1;  //ԭʼ�ֽ�������  
	int iBitLen = MULTIPLE*iByteLen;                   //����������  
	UCHAR *puchBit = new UCHAR[iBitLen];  
	memset(puchBit, 0, iBitLen); 

	int iBitLenX = 0;  
	byte_to_bit(uchByte, iByteLen, puchBit, &iBitLenX);  //�ֽ�ת��Ϊ������  

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
