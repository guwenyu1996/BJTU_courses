#pragma once

class Encode
{
public:
	Encode(const char *filename);    // ��ͼƬ��ַ�Ĺ��캯��
	Encode();                        // Ĭ�Ϲ��캯��(��Ҫ�����������)
	~Encode(void);

	int getEncodeLen();              // �����Ƕ����Ϣ�ֽ���

	void encode(UCHAR* message);      // Ƕ����Ϣ

	void createRGBPic(int width, int length, BYTE *imagedata);     // 256�Ҷ�ͼ

	void createGreyPic(int width, int length, BYTE *imagedata);    // 24λ���ͼ

private:
	MyBMP *bmp;
};

