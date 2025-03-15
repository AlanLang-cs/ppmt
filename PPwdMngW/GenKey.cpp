# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <iostream>

#include "pch.h"

# define FILE_ERR -1
# define N 8

using namespace std;
extern void WriteLog(int iFlag, char* pcaHBuf, int iHBufLen, const char* pFormat, ...);

int GenKey(char *pcaFileName,unsigned char *cKey)
{
	int iL=0;
	int iSeat=0;
	unsigned char cStr[8]={0};
	FILE *fp;

	errno_t errFile = fopen_s(&fp, pcaFileName, "wb");
	if (errFile != 0)
	{
		WriteLog(1, NULL, 0, "Failed to open file[%s],error no is %d", pcaFileName, FILE_ERR);
		return FILE_ERR;
	}
	
	srand(time(0));
	for(iL=0;iL<N;iL++)
	{
		iSeat=rand();
		iSeat=iSeat%256;
		//cout<<"debug"<<':'<<iSeat<<endl;
		cStr[iL]=iSeat;
		cKey[iL]=iSeat;
	}
	if(fwrite(cStr,sizeof(cStr),1,fp)!=1)
	{
		WriteLog(1, NULL, 0, "File write error");
		return FILE_ERR;
	}
	fclose(fp);
	return 0;
}
int GetKey(char *pcaFileName,unsigned char *cKey)
{
	FILE *fp;

	errno_t errFile = fopen_s(&fp, pcaFileName, "rb");
	
	if(errFile != 0)
	{
		WriteLog(1, NULL, 0, "Failed to open file[%s],error no is %d", pcaFileName, FILE_ERR);
		return FILE_ERR;
	}
	
	if(fread(cKey,sizeof(cKey),1,fp)!=1)
	{
		WriteLog(1, NULL, 0, "File read error");
		return FILE_ERR;
	}
	fclose(fp);
	return 0;
}
/*
int Print(char* FileName, unsigned char* cKey)
{
	int iL=0;
	
	for(iL=0;iL<N;iL++)
	{
		printf("%#x",cKey[iL]);
	}
	printf("\n");
	return 0;
}
*/
/*
int main()
{
	unsigned char cKey[N]={0};
	char cStr[1000]={0};
		
	cin>>cStr;
	GenKey(cStr,cKey);
	Print(cStr,cKey);
	GetKey(cStr,cKey);
	Print(cStr,cKey);
	return 0;
}
*/