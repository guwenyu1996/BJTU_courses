#pragma once

class Encode
{
public:
	Encode(const char *filename);    // 带图片地址的构造函数
	Encode();                        // 默认构造函数(不要调这个！！！)
	~Encode(void);

	int getEncodeLen();              // 计算可嵌入信息字节数

	void encode(UCHAR* message);      // 嵌入信息

	void createRGBPic(int width, int length, BYTE *imagedata);     // 256灰度图

	void createGreyPic(int width, int length, BYTE *imagedata);    // 24位真彩图

private:
	MyBMP *bmp;
};

