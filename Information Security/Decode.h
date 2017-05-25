#pragma once

class Decode
{
public:
	Decode(void);      // 不要调这个！！！
	Decode(const char* filename);
	~Decode(void);

	void decode();

private:
	MyBMP *bmp;
};

