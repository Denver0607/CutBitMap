// #include"splitBMP.h"

// void copyHeader(BMP sourceFile, BMP &destinationFile, uint32_t height, uint32_t width)
// {
//     destinationFile.header=sourceFile.header;
//     char paddingCount=(4-(width*(sourceFile.dib.colorDepth/8)%4))%4;
//     destinationFile.header.fileSize=(width*sourceFile.dib.colorDepth/8+paddingCount)*height+sourceFile.header.pixelOffset;
// }

// void copyDIB(BMP sourceFile, BMP &destinationFile,uint32_t height, uint32_t width)
// {
//     destinationFile.dib=sourceFile.dib;
//     destinationFile.dib.imageHeight=height;
//     destinationFile.dib.imageWidth=width;
//     char paddingCount=(4-(width*(sourceFile.dib.colorDepth/8)%4))%4;
//     destinationFile.dib.pixelArrSize=(width*sourceFile.dib.colorDepth/8+paddingCount)*height;
// }

// BMP cutBmpFile(BMP bmp, uint32_t row, uint32_t column, uint32_t sizeRow, uint32_t sizeColumn)
// {
//     BMP bResult;
//     copyHeader(bResult, bmp, sizeRow,sizeColumn);
//     copyDIB(bResult, bmp, sizeRow, sizeColumn);


//     pixelArray data=bmp.pA, dataResult;
//     dataResult.rowColor=sizeRow;
//     dataResult.columnColor=sizeColumn;

//     dataResult.pixels=new Color *[sizeRow*sizeof(Color*)];
//     for (int i=0;i<sizeRow;i++)
//     {
//         dataResult.pixels[i]=new Color [sizeColumn*sizeof(Color)];
//         for (int j=0;j<sizeColumn;j++)
//         {
//             dataResult.pixels[i][j]=data.pixels[i+row][j+column];
//         }
//     }
//     bResult.pA=dataResult;
//     return bResult;
// }
