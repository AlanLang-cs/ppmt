# include <stdio.h>
# include <string.h>
# include <malloc.h>
# include <iostream>

#include "pch.h"
# include "cCommon.h"
//using namespace std;


extern void WriteLog(int iFlag, char* pcaHBuf, int iHBufLen, const char* pFormat, ...);
/*
功能：在AccHeadM数组中查找账户类别，并返回相应数组下标
参数：
char *              -- I，文件名
struct AccHeadM *   -- IO，账户信息内存数据结构
*/
int GetAccHeadMInd(char *pstrAccTypeName,struct AccHeadM *pAccHeadM)
{
	int iL=0;
	
	for(iL=0;iL<ACC_MAX;iL++)
	{
		if(strcmp(pstrAccTypeName,pAccHeadM[iL].strAccTypeName)==0)
		{
			return iL;
		}
	}
	
	return FAIL_ACCTYPEERR;
}

/*
功能：将内存数据结构的账户信息数据写入文件
参数：
char *              -- I，文件名
struct AccHeadM *   -- IO，账户信息内存数据结构
*/

int AccFileWrite(char *pcaFileName,struct UsrFHead *pUsrFHead,struct AccHeadM *pAccHeadM)
{
	FILE *fp;
	int iCount=0;
	int i=0;
	int j=0;
	struct AccInfRecM *pTemp=NULL;
	int iTotal=0;
	struct AccInfRec stAccInfRec={0};
	struct AccHead stAccHead={0};
	
	WriteLog(1, NULL, 0, "Enter function[AccFileWrite], file name is %s\n", pcaFileName );
	errno_t errFile = fopen_s(&fp, pcaFileName, "wb");
	if (errFile != 0)
	{
		WriteLog(1, NULL, 0, "Failed to open file, error number is %d\n", errFile);
		return FILE_ERR;
	}
	/*if ((fp = fopen(pcaFileName, "wb")) == NULL)
	{
		WriteLog(1,NULL,30,"Failed to open file\n");
	}
	*/
	if (pAccHeadM == NULL)
	{
		fwrite(pUsrFHead, sizeof(struct UsrFHead), 1, fp);
		fclose(fp);
		return 0;
	}

	for(i=0;i<ACC_MAX;i++)
	{
		iTotal=iTotal+pAccHeadM[i].iNum;
	}
	pUsrFHead->iTotal=iTotal;
	fwrite(pUsrFHead,sizeof(struct UsrFHead),1,fp);
	i=0;
	while(iCount<(pUsrFHead->iTotal))
	{
		memcpy(stAccHead.strAccoutType,pAccHeadM[i].strAccoutType,ACCTYPE_LEN+1);
		memcpy(stAccHead.strAccTypeName,pAccHeadM[i].strAccTypeName,ACCTYPENAME_LEN);
		stAccHead.iNum=pAccHeadM[i].iNum;
		fwrite(&stAccHead,sizeof(struct AccHead),1,fp);
		pTemp=pAccHeadM[i].pstAccInfRecM;
		for(j=0;j<(pAccHeadM[i].iNum);j++)
		{
			stAccInfRec.iAccNo=pTemp->stAccInfRec.iAccNo;
			fwrite(&pTemp->stAccInfRec,sizeof(struct AccInfRec),1,fp);
			pTemp=pTemp->pstNext;
			iCount=iCount+1;
		}
		i=i+1;
	}
	fclose(fp);
	WriteLog(1, NULL, 0, "End of function[AccFileWrite], file name is %s\n", pcaFileName );

	return 0;
}

/*
功能：从文件中将账户信息数据读入内存数据结构
参数：
char *              -- I，文件名
struct AccHeadM *   -- IO，账户信息内存数据结构
*/
int AccFileRead(char *pcaFileName,struct UsrFHead *pUsrFHead,struct AccHeadM *pAccHeadM)
{
	FILE *fp;
	int iCount=0;
	int i=0;
	int j=0;
	struct AccInfRecM *pTemp=NULL;
	struct AccHead stAccHead={0};
	
	WriteLog(1, NULL, 0, "Enter function[AccFileRead], file name is %s\n", pcaFileName );
	
	errno_t errFile = fopen_s(&fp, pcaFileName, "rb");
	
	if (errFile != 0)
	{
		WriteLog(1,NULL,0,"Failed to open file,error no is %d\n", errFile);
		return FILE_ERR;
	}
	
	fread(pUsrFHead,sizeof(UsrFHead),1,fp);
	while(iCount<(pUsrFHead->iTotal))
	{
		fread(&stAccHead,sizeof(struct AccHead),1,fp);
		memcpy(pAccHeadM[i].strAccoutType,stAccHead.strAccoutType,ACCTYPE_LEN+1);
		memcpy(pAccHeadM[i].strAccTypeName,stAccHead.strAccTypeName,ACCTYPENAME_LEN);
		pAccHeadM[i].iNum=stAccHead.iNum;
		pAccHeadM[i].pstAccInfRecM=(struct AccInfRecM *)malloc(sizeof(struct AccInfRecM));
		pTemp=pAccHeadM[i].pstAccInfRecM;
		memset(pTemp, 0x00, sizeof(struct AccInfRecM));
		for(j=0;j<pAccHeadM[i].iNum;j++)
		{
			fread(&(pTemp->stAccInfRec),sizeof(struct AccInfRec),1,fp);
			if (j != pAccHeadM[i].iNum - 1)
			{
				pTemp->pstNext = (struct AccInfRecM*)malloc(sizeof(struct AccInfRecM));
				memset(pTemp->pstNext, 0x00, sizeof(struct AccInfRecM));
				pTemp = pTemp->pstNext;
			}
			iCount=iCount+1;
		}
		i=i+1;
	}
	fclose(fp);
	WriteLog(1, NULL, 0, "End of function[AccFileRead], file name is %s\n", pcaFileName );

	return 0;
}

/*
功能：释放内存数据结构的链表内存
struct AccHeadM *   -- I，账户信息内存数据结构
*/
int FreeMem(struct AccHeadM* pAccHeadM)
{
	struct AccInfRecM* pstTemp = NULL;
	struct AccInfRecM* pstNext = NULL;
	int i = 0;

	for (i = 0; i < ACC_MAX; i++)
	{
		pstTemp = pAccHeadM[i].pstAccInfRecM;
		if (pstTemp == NULL)
		{
			continue;
		}
		while (pstTemp->pstNext != NULL)
		{
			pstNext = pstTemp->pstNext;
			free(pstTemp);
			pstTemp = pstNext;
		}
		free(pstTemp);
	}
	return 0;
}

/*
功能：在内存数据结构中对于个人账户信息进行增加操作
参数：char *              -- I，账户类别名称
struct AccHeadM *   -- IO，账户信息内存数据结构
struct AccInfoRec *   --I，需要增加的账户信息记录
*/
int AddAccRec(char *pstrAccTypeName,struct AccHeadM *pAccHeadM,struct AccInfRec *pAccInfRec)
{
	int iL=0;
	int iSeat=0;
	int iNum=0;
	int iTemp=0;
	int iCount=0;
	struct AccInfRecM *pTemp=NULL;
	
//	WriteLog(1, (char *)pAccInfRec, sizeof(struct AccInfRec), "Enter function[AddAccRec], pstrAccTypeName=%s\n", pstrAccTypeName  );
	
	iSeat=GetAccHeadMInd(pstrAccTypeName,pAccHeadM);
	if (iSeat < 0)
	{
		WriteLog(1, NULL, 0, "Failed to match AccType");
		return FAIL_ACCTYPEERR;
	}

	if(pAccHeadM[iSeat].iNum==0)
	{
		pAccHeadM[iSeat].pstAccInfRecM=(struct AccInfRecM *)malloc(sizeof(struct AccInfRecM));
		memset(pAccHeadM[iSeat].pstAccInfRecM, 0x00, sizeof(struct AccInfRecM));
		memcpy((pAccHeadM[iSeat].pstAccInfRecM)->stAccInfRec.strAccName,pAccInfRec->strAccName,ACCNAME_LEN);
		memcpy((pAccHeadM[iSeat].pstAccInfRecM)->stAccInfRec.strAccNumber,pAccInfRec->strAccNumber,ACCNUM_LEN);
		memcpy((pAccHeadM[iSeat].pstAccInfRecM)->stAccInfRec.caAccPwd,pAccInfRec->caAccPwd,ACCPWD_LEN);
		memcpy((pAccHeadM[iSeat].pstAccInfRecM)->stAccInfRec.strAccMemo,pAccInfRec->strAccMemo,ACCMEMO_LEN);
		memcpy((pAccHeadM[iSeat].pstAccInfRecM)->stAccInfRec.strAccURL,pAccInfRec->strAccURL,ACCURL_LEN);
		pAccHeadM[iSeat].pstAccInfRecM->stAccInfRec.iAccNo=1;
		pAccHeadM[iSeat].iNum=pAccHeadM[iSeat].iNum+1;
	}
	else
	{
		pTemp=pAccHeadM[iSeat].pstAccInfRecM;
		for(iL=0;iL<pAccHeadM[iSeat].iNum-1;iL++)
		{
			pTemp=pTemp->pstNext;
		}
		(pTemp->pstNext)=(struct AccInfRecM *)malloc(sizeof(struct AccInfRecM));
		memset((pTemp->pstNext),0x00,sizeof(struct AccInfRecM));
		pTemp=pTemp->pstNext;
		pAccHeadM[iSeat].iNum=pAccHeadM[iSeat].iNum+1;
		pTemp->stAccInfRec.iAccNo=pAccHeadM[iSeat].iNum;
		memcpy(pTemp->stAccInfRec.strAccName,pAccInfRec->strAccName,ACCNAME_LEN);
		memcpy(pTemp->stAccInfRec.strAccNumber,pAccInfRec->strAccNumber,ACCNUM_LEN);
		memcpy(pTemp->stAccInfRec.caAccPwd,pAccInfRec->caAccPwd,ACCPWD_LEN);
		memcpy(pTemp->stAccInfRec.strAccMemo,pAccInfRec->strAccMemo,ACCMEMO_LEN);
		memcpy(pTemp->stAccInfRec.strAccURL,pAccInfRec->strAccURL,ACCURL_LEN);	
	}
//	WriteLog(1, (char *)pAccHeadM, sizeof(struct AccHeadM), "End of function[AddAccRec], pstrAccTypeName=%s\n", pstrAccTypeName  );

	return 0;
}

/*
功能：在内存数据结构中对于个人账户信息进行删除操作
参数：char *              -- I，账户类别名称
struct AccHeadM *   -- IO，账户信息内存数据结构
struct AccInfoRec *   --I，需要增删除的账户信息记录
*/
int DelAccRec(char *pstrAccTypeName,struct AccHeadM *pAccHeadM,struct AccInfRec *pAccInfRec)
{
	int iSeat=0;
	short iTemp=0;
	int iL=0;
	struct AccInfRecM *pTemp=NULL;
	struct AccInfRecM *pSeat=NULL;
	int iJudge=-1;

//	WriteLog(1, (char *)pAccInfRec, sizeof(struct AccInfRec), "Enter function[DelAccRec], pstrAccTypeName=%s\n", pstrAccTypeName  );	
	iSeat=GetAccHeadMInd(pstrAccTypeName,pAccHeadM);
	if (iSeat < 0)
	{
		WriteLog(1, NULL, 0, "Failed to match AccType");
		return FAIL_ACCTYPEERR;
	}
	pTemp=pAccHeadM[iSeat].pstAccInfRecM;
	pSeat=pAccHeadM[iSeat].pstAccInfRecM;
	for(iL=0;iL<pAccHeadM[iSeat].iNum;iL++)
	{
		if(pTemp->stAccInfRec.iAccNo==pAccInfRec->iAccNo)
		{
			if((pTemp->stAccInfRec.iAccNo)==pAccHeadM[iSeat].iNum)
			{
				free(pTemp);
				if ((pAccInfRec->iAccNo) == 1)
				{
					pAccHeadM[iSeat].pstAccInfRecM = NULL;
				}
				else
				{
					pSeat->pstNext = NULL;
				}
				iJudge=0;
			}
			else
			{
				if((pAccInfRec->iAccNo)==1)
				{	
					iTemp=1;
					pAccHeadM[iSeat].pstAccInfRecM=(pTemp->pstNext);
					pSeat=pAccHeadM[iSeat].pstAccInfRecM;
					free(pTemp);
					iJudge=0;
					break;
				}
				else
				{
					iTemp=pTemp->stAccInfRec.iAccNo;
					iJudge=0;
					pSeat->pstNext=pTemp->pstNext;
					free(pTemp);
					break;		
				}
			}
		}
		else
		{
			pSeat=pTemp;
			pTemp=pTemp->pstNext;
		}
	}
	if((pAccInfRec->iAccNo)!=pAccHeadM[iSeat].iNum)
	{
		if((pAccInfRec->iAccNo)==1)
		{
			for(iTemp=iTemp+1;iTemp<=pAccHeadM[iSeat].iNum;iTemp++)
			{
				pSeat->stAccInfRec.iAccNo=pSeat->stAccInfRec.iAccNo-1;
				pSeat=pSeat->pstNext;
			}	
		}
		else
		{
			pSeat=pSeat->pstNext;
			for(iTemp=iTemp+1;iTemp<=pAccHeadM[iSeat].iNum;iTemp++)
			{
				pSeat->stAccInfRec.iAccNo=pSeat->stAccInfRec.iAccNo-1;
				pSeat=pSeat->pstNext;
			}	
		}
	}
	pAccHeadM[iSeat].iNum=pAccHeadM[iSeat].iNum-1;
	
	if(iJudge==-1)
	{
		WriteLog(1,NULL,0,"Failed to delete\n");
		return FAIL_DELETEERR;
	}
	
//	WriteLog(1, (char *)pAccHeadM, sizeof(struct AccHeadM), "End of function[DelAccRec], pstrAccTypeName=%s\n", pstrAccTypeName  );
	return 0;
}

/*
功能：在内存数据结构中对于个人账户信息进行查询操作
参数：char *              -- I，账户类别名称
struct AccHeadM *   -- I，账户信息内存数据结构
struct AccInfoRec *   --O，需要查询的账户信息记录
*/
int InqAccRec(char *pstrAccTypeName,struct AccHeadM *pAccHeadM,struct AccInfRec *pAccInfRec)
{
	int iL=0;
	int iSeat=0;
	int iJudge=-1;
	struct AccInfRecM *pTemp=NULL;

//	WriteLog(1, (char *)pAccInfRec, sizeof(struct AccInfRec), "Enter function[InqAccRec], pstrAccTypeName=%s\n", pstrAccTypeName  );	
	iSeat=GetAccHeadMInd(pstrAccTypeName,pAccHeadM);
	if (iSeat < 0)
	{
		WriteLog(1, NULL, 0, "Failed to match AccType\n");
		return FAIL_ACCTYPEERR;
	}
	pTemp=pAccHeadM[iSeat].pstAccInfRecM;
	for(iL=0;iL<pAccHeadM[iSeat].iNum;iL++)
	{
		if(pTemp->stAccInfRec.iAccNo==pAccInfRec->iAccNo)
		{
			memcpy(pAccInfRec->strAccName,pTemp->stAccInfRec.strAccName, ACCNAME_LEN);
			memcpy(pAccInfRec->strAccNumber,pTemp->stAccInfRec.strAccNumber,ACCNUM_LEN);
			memcpy(pAccInfRec->caAccPwd,pTemp->stAccInfRec.caAccPwd,ACCPWD_LEN);
			memcpy(pAccInfRec->strAccMemo,pTemp->stAccInfRec.strAccMemo, ACCMEMO_LEN);
			memcpy(pAccInfRec->strAccURL,pTemp->stAccInfRec.strAccURL,ACCURL_LEN);
			iJudge=0;
			break;
		}
		else
		{
			pTemp=pTemp->pstNext;
		}
	}
	if(iJudge!=0)
	{
		WriteLog(1,NULL,30,"Failed to search\n");
		return FAIL_SEARCHERR;
	}
	
//	WriteLog(1, (char *)pAccHeadM, sizeof(struct AccHeadM), "End of function[InqAccRec], pstrAccTypeName=%s\n", pstrAccTypeName  );
	return 0;
}

/*
功能：在内存数据结构中对于个人账户信息进行修改操作
参数：char *              -- I，账户类别名称
struct AccHeadM *   -- IO，账户信息内存数据结构
struct AccInfoRec *   --I，需要修改的账户信息记录
*/
int UpdAccRec(char *pstrAccTypeName,struct AccHeadM *pAccHeadM,struct AccInfRec *pAccInfRec)
{
	int iSeat=0;
	int iL=0;
	struct AccInfRecM *pTemp=NULL;
	int iJudge=-1;

//	WriteLog(1, (char *)pAccInfRec, sizeof(struct AccInfRec), "Enter function[UpdAccRec], pstrAccTypeName=%s\n", pstrAccTypeName  );
	iSeat=GetAccHeadMInd(pstrAccTypeName,pAccHeadM);
	if (iSeat < 0)
	{
		WriteLog(1, NULL, 0, "Failed to match AccType");
		return FAIL_ACCTYPEERR;
	}
	pTemp=pAccHeadM[iSeat].pstAccInfRecM;
	for(iL=0;iL<pAccHeadM[iSeat].iNum;iL++)
	{
		if(pTemp->stAccInfRec.iAccNo==pAccInfRec->iAccNo)
		{
			memcpy(pTemp->stAccInfRec.strAccName,pAccInfRec->strAccName,ACCNAME_LEN);
			memcpy(pTemp->stAccInfRec.strAccNumber,pAccInfRec->strAccNumber,ACCNUM_LEN);
			memcpy(pTemp->stAccInfRec.caAccPwd,pAccInfRec->caAccPwd,ACCPWD_LEN);
			memcpy(pTemp->stAccInfRec.strAccMemo,pAccInfRec->strAccMemo,ACCMEMO_LEN);
			memcpy(pTemp->stAccInfRec.strAccURL,pAccInfRec->strAccURL,ACCURL_LEN);
			iJudge=0;
			break;
		}
		else
		{
			pTemp=pTemp->pstNext;
		}
	}
	if(iJudge!=0)
	{
		WriteLog(1,NULL,30,"Failed to uppdate\n");
		return FAIL_UPDERR;
	}
//	WriteLog(1, (char *)pAccHeadM, sizeof(struct AccHeadM), "End of function[UpdAccRec], pstrAccTypeName=%s\n", pstrAccTypeName  );
	return 0;
}

/*
功能：从配置文件读入账户类别数据
参数：
char* 配置文件文件名
struct AccHeadM* 输出项，内存数据结构数组部分，包括账户类别与账户类别编码
*/
int GetAccType(char *pcaFileName,struct AccHeadM *pAccHeadM)
{
	int iL=0;
	FILE *fp;
	
	errno_t errFile = fopen_s(&fp, pcaFileName, "rb");
	
	if( errFile != 0 )
	{
		WriteLog(1,NULL,0,"Failed to open file acctype,error no is %d\n",errFile);
		return FILE_ERR;
	}
	
	while(!feof(fp))
	{
		fscanf_s(fp,"%s %s",
			      pAccHeadM[iL].strAccoutType, (unsigned int)sizeof(pAccHeadM[iL].strAccoutType), 
			      pAccHeadM[iL].strAccTypeName, (unsigned int)sizeof(pAccHeadM[iL].strAccTypeName));
		WriteLog(0,NULL,30,pAccHeadM[iL].strAccoutType);
		WriteLog(0,NULL,30,pAccHeadM[iL].strAccTypeName);
		iL=iL+1;
	}
	fclose(fp);
	return 0;
}
