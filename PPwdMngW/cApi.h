extern int GetAccHeadMInd(char* pstrAccTypeName, struct AccHeadM* pAccHeadM);   
extern int AccFileWrite(char* pcaFileName, struct UsrFHead* pUsrFHead, struct AccHeadM* pAccHeadM);
extern int AddAccRec(char* pstrAccTypeName, struct AccHeadM* pAccHeadM, struct AccInfRec* pAccInfRec);
extern int AccFileRead(char* pcaFileName, struct UsrFHead* pUsrFHead, struct AccHeadM* pAccHeadM);
extern int DelAccRec(char* pstrAccTypeName, struct AccHeadM* pAccHeadM, struct AccInfRec* pAccInfRec);
extern int InqAccRec(char* pstrAccTypeName, struct AccHeadM* pAccHeadM, struct AccInfRec* pAccInfRec);
extern int UpdAccRec(char* pstrAccTypeName, struct AccHeadM* pAccHeadM, struct AccInfRec* pAccInfRec);
extern int GetAccType(char* pcaFileName, struct AccHeadM* pAccHeadM);
extern int GenKey(char* FileName, unsigned char* cKey);
extern int GetKey(char* FileName, unsigned char* cKey);
extern int FreeMem(struct AccHeadM* pAccHeadM);
extern int BlockEncrypt(unsigned char* pcaKey, unsigned char* pcaIn,
    unsigned char* pcaOut, int iLen);

extern int BlockDecrypt(unsigned char* pcaKey, unsigned char* pcaIn,
    unsigned char* pcaOut, int iLen);
