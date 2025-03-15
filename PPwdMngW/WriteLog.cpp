#include <stdio.h>  
#include <stdarg.h>  
#include <time.h>
#include <string.h>

#include"pch.h"

#define _DEBUG_

void WriteLog( int iFlag, char *pcaHBuf, int iHBufLen, const char *pFormat, ...)
{
    va_list       vaArgs;  
    char          caBuf[80] = {0};
	time_t        rawtime;  
    struct tm    timeinfo;  
	FILE* fpFile;

	#ifndef _DEBUG_
	if( iFlag == 0 )
		return; 
	#endif

	errno_t errFile = fopen_s(&fpFile, "pwdmng.log", "ab");
	/*
    fpFile = fopen("pwdmng_log.txt", "ab");  
    if (fpFile == NULL) {  
        return;  
    }  
	*/
    // 获取当前时间  
    time(&rawtime);  
     // 将 time_t 转换为本地时间  
	localtime_s(&timeinfo, &rawtime);
    //timeinfo = localtime(&rawtime);  
     // 使用 strftime 格式化时间  
    strftime(caBuf, 80, "%Y-%m-%d %H:%M:%S|Message:\n", &timeinfo);  
   	fwrite(caBuf, strlen(caBuf), 1, fpFile);
  	
  	if( pFormat != NULL )
  	{
		va_start(vaArgs, pFormat);  //initialize args
    	vfprintf(fpFile, pFormat, vaArgs);  
    	va_end(vaArgs);  //close args  	
		fprintf(fpFile, "\n");	
	}
	if( pcaHBuf != NULL )
	{
		fprintf(fpFile, "0-1-2-3-4-5-6-7-8-9-A-B-C-D-E-F-\n");
		for( int i=0; i<iHBufLen; i++ )
		{
			fprintf(fpFile, "%02hhX", pcaHBuf[i]);
			if( (i+1)%16 == 0 )
			{
				fprintf(fpFile, "\n");
			}
		}
	}
	fprintf(fpFile, "\n");
	
	fclose(fpFile);
		
}

/*int main( void )
{
	char caBuf[50] = {0};
	char caUsrName[20] = {0};
	
	memset( caBuf, 0x44, 20 );
	strcpy(caUsrName, "Lang");
	WriteLog(1, NULL, 0, "%s", "hello world!");
	WriteLog(1, caBuf, 20, NULL );
	WriteLog(0, caBuf, 20, "user name:%s", caUsrName);
	
	return 0;
}*/
