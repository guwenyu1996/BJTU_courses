#pragma once

class Decode
{
public:
	Decode(void);      // ��Ҫ�����������
	Decode(const char* filename);
	~Decode(void);

	void decode();

private:
	MyBMP *bmp;
};

