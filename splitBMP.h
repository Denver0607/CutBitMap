#include"readBmpFormat.h"

void copyHeader(BMP sourceFile, BMP &destinationFile, uint32_t height, uint32_t width);
void copyDIB(BMP sourceFile, BMP &destinationFile,uint32_t height, uint32_t width);
BMP cutBmpFile(BMP bmp, uint32_t row, uint32_t column, uint32_t sizeRow, uint32_t sizeColumn);