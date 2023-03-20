#include "readBmpFormat.h"

bool isBMP(FILE* f)
{
	if (f == NULL)
		return false;

	bmpSignature s;
	fseek(f, 0, SEEK_SET);
	fread(&s, sizeof(bmpSignature), 1, f);

	if (s.s[0] == 'B' && s.s[1] == 'M')
		return true;
	return false;
}

void readHeaderFormat(FILE* f, headerFormat& header)
{
	if (f == NULL)
		return;

	fseek(f, 0, SEEK_SET);
	fread(&header, sizeof(headerFormat), 1, f);
}

void readDIB(FILE* f, dibFormat& dib)
{
	if (f == NULL)
		return;

	fseek(f, sizeof(headerFormat), SEEK_SET);
	fread(&dib, sizeof(dibFormat), 1, f);
}

void readPixelLine(FILE* f, Color*& line, uint32_t length)
{
	if (f == NULL)
		return;

	line = new Color[length];
	fread(line, sizeof(Color), length, f);
}

void skipPadding(FILE* f, char count)
{
	if (f == NULL)
		return;

	if (count == 0)
		return;

	char padding[3];
	fread(padding, count, 1, f);
}

void readPixelArray(FILE* f, headerFormat header, dibFormat dib, pixelArray& data)
{
	if (f == NULL)
		return;

	data.rowColor = dib.imageHeight;
	data.columnColor = dib.imageWidth;
	data.pixels = new Color * [data.rowColor];
	char paddingCount = (4 - (dib.imageWidth * (dib.colorDepth / 8) % 4)) % 4;

	fseek(f, header.pixelOffset, SEEK_SET);

	for (int i = 0; i < data.rowColor; i++)
	{
		readPixelLine(f, data.pixels[data.rowColor - i - 1], dib.imageWidth);
		skipPadding(f, paddingCount);
	}
}

bool readBMPfile(char* filename, BMP& b)
{
	FILE* f = fopen(filename, "rb");
	if (f == NULL)
	{
		cout << "Can't open file\n";
		return false;
	}

	if (!isBMP(f))
	{
		cout << f << " isn't BMP file\n";
		return false;
	}
	readHeaderFormat(f, b.header);
	readDIB(f, b.dib);
	readPixelArray(f, b.header, b.dib, b.pA);
	fclose(f);
	
	return true;
}

