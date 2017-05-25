#include <iostream>
#include <windows.h>
#include <bitset>
#include "MyBMP.h"
#include "Encode.h"
#include "Decode.h"

using namespace std;

extern void bit_to_byte(const UCHAR *puchBit, const int& iBitLen, UCHAR *puchByte, int* pByteLen);
extern void byte_to_bit(const UCHAR *puchByte, const int& iByteLen, UCHAR *puchBit, int *pBitLen);

void bitConverterExample()
{
	bitset<32> bs(1024);
	string bits = bs.to_string();
	printf("%s\n", bits);

	bitset<32> n(bits);
	cout << n.to_ulong() << endl;

}

void testByte()
{
	BYTE temp = 4;
	int iByteLen = sizeof(temp)/sizeof(BYTE);  //原始字节流长度  

	BYTE *tempBit = new BYTE[8*iByteLen];  
	memset(tempBit, 0, 8*iByteLen); 
	int tempBitLenX = 0;  // 字节流长度
	byte_to_bit(&temp, iByteLen, tempBit, &tempBitLenX);  //字节转化为比特流

	cout << "字节流转化过的位流为: " << endl;  
	for (int i = 0; i < tempBitLenX; i++)  
		printf("%0x",tempBit[i]);  
	printf("\n");

	BYTE* tempByte = new UCHAR[iByteLen+1];  
	memset(tempByte, 0, iByteLen+1);  
	int iByteLenX = 0; 
	bit_to_byte(tempBit, tempBitLenX, tempByte, &iByteLenX); 

	cout << "测试位流转化过的字节流为: " << endl;  
  
	for (int i = 0; i < iByteLen; i++)  
	{  
		printf("%0x\t",tempByte[i]);  
	}  
	printf("\n");  

	cout << "位流转为成的字节流为: " << tempByte << endl;  

}

void testBitset()
{
	// int -> bits
	bitset<32> bs(32);
	string bits = bs.to_string();
	printf("%s\n", bits);

	// bits(string)  -> int
	bitset<32> bsa(bits);
	ULONG num = bsa.to_ulong();
	int inum = (int)num;
	printf("%d\n", inum);


}

void testUchar()
{
	//UCHAR uchar[] = "1111111111";
	//cout << sizeof(*uchar)/sizeof(UCHAR) << endl;
	//cout << strlen((char*)uchar) << endl;

	BYTE tempBit[] = "0011000100110001001100010011000100110001";
	int tempBitLen = strlen((char*)tempBit);

	int iByteLen = tempBitLen/8;
	BYTE* tempByte = new UCHAR[iByteLen+1];  
	memset(tempByte, 0, iByteLen+1);  
	int iByteLenX = 0; 
	bit_to_byte(tempBit, tempBitLen, tempByte, &iByteLenX); 

	cout << "测试位流转化过的字节流为: " << endl;  
  
	for (int i = 0; i < iByteLen; i++)  
	{  
		printf("%0x\t",tempByte[i]);  
	}  
	printf("\n");  

	cout << "位流转为成的字节流为: " << tempByte << endl;  
}


int main()
{
	Encode *test = new Encode("BMPtest\\test5.bmp");
	UCHAR uchar[] = "meqwrsdjfhkjasf";
	test->encode(uchar);
	//printf("%d\n", test->getEncodeLen());
	
	//testByte();
	//testBitset();
	// testUchar();

	Decode *decode = new Decode("BMPtest\\RGBExample.bmp");
	decode->decode();

	char c = getchar();
	return 0;
}



