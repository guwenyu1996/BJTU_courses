#pragma once

class Decode
{
public:
	Decode(void);      // ²»Òªµ÷Õâ¸ö£¡£¡£¡
	Decode(const char* filename);
	~Decode(void);

	void decode();

private:
	MyBMP *bmp;
};

