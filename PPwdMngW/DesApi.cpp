#include <stdio.h>
#include <malloc.h>
#include <fcntl.h>
#include <string.h>

#include "pch.h"

extern void WriteLog(int iFlag, char* pcaHBuf, int iHBufLen, const char* pFormat, ...);
// global variables
// 8��S�У�����48bit->32bit 
unsigned char g_caSbox1[] =
{
   14, 4,13, 1, 2,15,11, 8, 3,10, 6,12, 5, 9, 0, 7,
    0,15, 7, 4,14, 2,13, 1,10, 6,12,11, 9, 5, 3, 8,
    4, 1,14, 8,13, 6, 2,11,15,12, 9, 7, 3,10, 5, 0,
   15,12, 8, 2, 4, 9, 1, 7, 5,11, 3,14,10, 0, 6,13
};


unsigned char g_caSbox2[] =
{
   15, 1, 8,14, 6,11, 3, 4, 9, 7, 2,13,12, 0, 5,10,
    3,13, 4, 7,15, 2, 8,14,12, 0, 1,10, 6, 9,11, 5,
    0,14, 7,11,10, 4,13, 1, 5, 8,12, 6, 9, 3, 2,15,
   13, 8,10, 1, 3,15, 4, 2,11, 6, 7,12, 0, 5,14, 9
};

unsigned char g_caSbox3[] =
{
   10, 0, 9,14, 6, 3,15, 5, 1,13,12, 7,11, 4, 2, 8,
   13, 7, 0, 9, 3, 4, 6,10, 2, 8, 5,14,12,11,15, 1,
   13, 6, 4, 9, 8,15, 3, 0,11, 1, 2,12, 5,10,14, 7,
    1,10,13, 0, 6, 9, 8, 7, 4,15,14, 3,11, 5, 2,12
};

unsigned char g_caSbox4[] =
{
    7,13,14, 3, 0, 6, 9,10, 1, 2, 8, 5,11,12, 4,15,
   13, 8,11, 5, 6,15, 0, 3, 4, 7, 2,12, 1,10,14, 9,
   10, 6, 9, 0,12,11, 7,13,15, 1, 3,14, 5, 2, 8, 4,
    3,15, 0, 6,10, 1,13, 8, 9, 4, 5,11,12, 7, 2,14
};

unsigned char g_caSbox5[] =
{
    2,12, 4, 1, 7,10,11, 6, 8, 5, 3,15,13, 0,14, 9,
   14,11, 2,12, 4, 7,13, 1, 5, 0,15,10, 3, 9, 8, 6,
    4, 2, 1,11,10,13, 7, 8,15, 9,12, 5, 6, 3, 0,14,
   11, 8,12, 7, 1,14, 2,13, 6,15, 0, 9,10, 4, 5, 3
};

unsigned char g_caSbox6[] =
{
   12, 1,10,15, 9, 2, 6, 8, 0,13, 3, 4,14, 7, 5,11,
   10,15, 4, 2, 7,12, 9, 5, 6, 1,13,14, 0,11, 3, 8,
    9,14,15, 5, 2, 8,12, 3, 7, 0, 4,10, 1,13,11, 6,
    4, 3, 2,12, 9, 5,15,10,11,14, 1, 7, 6, 0, 8,13
};

unsigned char g_caSbox7[] =
{
    4,11, 2,14,15, 0, 8,13, 3,12, 9, 7, 5,10, 6, 1,
   13, 0,11, 7, 4, 9, 1,10,14, 3, 5,12, 2,15, 8, 6,
    1, 4,11,13,12, 3, 7,14,10,15, 6, 8, 0, 5, 9, 2,
    6,11,13, 8, 1, 4,10, 7, 9, 5, 0,15,14, 2, 3,12
};

unsigned char g_caSbox8[] =
{
   13, 2, 8, 4, 6,15,11, 1,10, 9, 3,14, 5, 0,12, 7,
    1,15,13, 8,10, 3, 7, 4,12, 5, 6,11, 0,14, 9, 2,
    7,11, 4, 1, 9,12,14, 2, 0, 6,10,13,15, 3, 5, 8,
    2, 1,14, 7, 4,10, 8,13,15,12, 9, 0, 3, 5, 6,11
};

unsigned char* g_pcaSbox[] =
{
   g_caSbox1,
   g_caSbox2,
   g_caSbox3,
   g_caSbox4,
   g_caSbox5,
   g_caSbox6,
   g_caSbox7,
   g_caSbox8
};


//�����û��� initial permutation
unsigned char g_caIP[] =
{
   58,50,42,34,26,18,10, 2,60,52,44,36,28,20,12, 4,
   62,54,46,38,30,22,14, 6,64,56,48,40,32,24,16, 8,
   57,49,41,33,25,17, 9, 1,59,51,43,35,27,19,11, 3,
   61,53,45,37,29,21,13, 5,63,55,47,39,31,23,15, 7
};

//���ʼ�û��� inverse permutation
unsigned char g_caInvIP[] =
{
   40, 8,48,16,56,24,64,32,39, 7,47,15,55,23,63,31,
   38, 6,46,14,54,22,62,30,37, 5,45,13,53,21,61,29,
   36, 4,44,12,52,20,60,28,35, 3,43,11,51,19,59,27,
   34, 2,42,10,50,18,58,26,33, 1,41, 9,49,17,57,25
};

// ��Կ�û�ѡ���1��ȥУ��λ���ҽ���λת���� permutated choice 1
unsigned char g_caKeyPC1[] =
{
   57,49,41,33,25,17, 9, 1,58,50,42,34,26,18,
   10, 2,59,51,43,35,27,19,11, 3,60,52,44,36,
   63,55,47,39,31,23,15, 7,62,54,46,38,30,22,
   14, 6,61,53,45,37,29,21,13, 5,28,20,12, 4
};


// ��Կ�û�ѡ���2��56bit->48bit��permutated choice 2
unsigned char g_caKeyPC2[] =
{
   14,17,11,24, 1, 5, 3,28,15, 6,21,10,23,19,12, 4,
   26, 8,16, 7,27,20,13, 2,41,52,31,37,47,55,30,40,
   51,45,33,48,44,49,39,56,34,53,46,42,50,36,29,32
};

// E��չ�û���32bit->48bit��
unsigned char g_caExpand[] =
{
   32, 1, 2, 3, 4, 5, 4, 5, 6, 7, 8, 9, 8, 9,10,11,
   12,13,12,13,14,15,16,17,16,17,18,19,20,21,20,21,
   22,23,24,25,24,25,26,27,28,29,28,29,30,31,32, 1
};

// P���û����ֺ�����ʹ�ã�
unsigned char g_caFP[] =
{
   16, 7,20,21,29,12,28,17, 1,15,23,26, 5,18,31,10,
    2, 8,24,14,32,27, 3, 9,19,13,30, 6,22,11, 4,25
};

// ����1λ��
unsigned char g_caM1BtoL[] =
{
    2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,
   18,19,20,21,22,23,24,25,26,27,28, 1,30,31,32,33,
   34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,
   50,51,52,53,54,55,56,29
};

// ����2λ��
unsigned char g_caM2BtoL[] =
{
    3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,
   19,20,21,22,23,24,25,26,27,28, 1, 2,31,32,33,34,
   35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,
   51,52,53,54,55,56,29,30
};

// ����1λ��
unsigned char g_caM1BtoR[] =
{
   28, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,
   16,17,18,19,20,21,22,23,24,25,26,27,56,29,30,31,
   32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,
   48,49,50,51,52,53,54,55
};

// ����2λ��
unsigned char g_caM2BtoR[] =
{
   27,28, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,
   15,16,17,18,19,20,21,22,23,24,25,26,55,56,29,30,
   31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,
   47,48,49,50,51,52,53,54
};

/* 
���ݿ��λ�û����� 
������
unsigned char * -- I,�������ݿ� 
unsigned char * -- O,������ݿ�
int             -- I,Ŀ�����ݿ���λ��
unsigned char * -- I,λ�û��� 
*/ 
void BitTransfer(unsigned char* pcaIn, unsigned char* pcaOut, int iBitLen, unsigned char* pcaTable )
{
    int iL;
    unsigned char caOut[8];

    memset(caOut, 0x00, sizeof(caOut));

    for (iL = 0; iL < iBitLen; iL++)
    {
        caOut[iL >> 3] |= ((pcaIn[(pcaTable[iL] - 1) >> 3]
            & (0x80 >> ((pcaTable[iL] - 1) & 0x7)))
            << ((pcaTable[iL] - 1) & 0x7)) >> (iL & 0x7);
    }

    for (iL = 0; iL < iBitLen >> 3; iL++)
    {
        pcaOut[iL] = caOut[iL];
    }
}



/* 
���ݿ��S���û����� 
������
unsigned char * -- I,�������ݿ� 
int             -- I,Ŀ�����ݿ��ֽ��� 
unsigned char * -- O,������ݿ�
int             -- I,Ŀ�����ݿ��ֽ��� 
*/ 
int B6to4(unsigned char* pcaIn, int iInLen, unsigned char* pcaOut, int iOutLen)
{
    int iX = 0;
    int iY = 0;
    unsigned char cTemp = 0;
    unsigned char cTail0 = 0, cTail1 = 0, cTail2 = 0;
    unsigned char cOut = 0;
    int i = 0, j = 0, k = 0;

    for (i = 0; i < iInLen; i++)
    {
        cTemp = pcaIn[i];
        switch (i % 3)
        {
        case 0:
            cTail0 = (cTemp & 0x03) << 4; //00000011 -> 00110000
            cTemp = (cTemp & 0xFC) >> 2; //11111100 -> 00111111
            iX = (cTemp >> 4) & 0x2 | (cTemp & 0x1); //0010 | 0001
            iY = (cTemp >> 1) & 0xF;//1111
            cOut = g_pcaSbox[j][iX * 16 + iY] << 4;
            j++;
            break;
        case 1:
            cTail1 = (cTemp & 0x0F) << 2; //00001111 << 2 = 00111100
            cTemp = ((cTemp & 0xF0) >> 4) | cTail0; //11110000 -> 00001111 | 00110000
            iX = (cTemp >> 4) & 0x2 | (cTemp & 0x1); //0010 | 0001
            iY = (cTemp >> 1) & 0xF;//1111
            cOut = g_pcaSbox[j][iX * 16 + iY] | cOut;
            j++;
            pcaOut[k] = cOut;
            k++;
            break;
        case 2:
            cTail2 = cTemp & 0x3F; //00111111
            cTemp = (cTemp & 0xC0) >> 6 | cTail1; //11000000 -> 00000011 | 00111100
            iX = (cTemp >> 4) & 0x2 | (cTemp & 0x1); //0010 | 0001
            iY = (cTemp >> 1) & 0xF; //1111			
            cOut = g_pcaSbox[j][iX * 16 + iY] << 4;
            j++;
            iX = (cTail2 >> 4) & 0x2 | (cTail2 & 0x1); //0010 | 0001
            iY = (cTail2 >> 1) & 0xF; //1111		
            cOut = g_pcaSbox[j][iX * 16 + iY] | cOut;
            j++;
            pcaOut[k] = cOut;
            k++;
            break;
        default:
            return -1;
        }
    }
    if (k != iOutLen)
        return -1;
    return 0;
}


/* 
�ּ��ܺ��� 
������
int             -- I,�����n�ּ��� 
unsigned char * -- IO,����������ݿ� 
unsigned char * -- I,����Կ
*/ 
void CipherFunc(int iTurn, unsigned char* pcaIO64, unsigned char* pcaKey56)
{
    unsigned char caT32[4]; // temp variable
	unsigned char caK48[6], caR48[6], caS32[4];
    int iaShift[] = {1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};
    
    switch( iaShift[iTurn] )
    {
    	case 1:
    		BitTransfer( pcaKey56, pcaKey56, 56, g_caM1BtoL );	//��Կ�԰룬ѭ������1λ���ϲ�
			break;
		case 2:
			BitTransfer( pcaKey56, pcaKey56, 56, g_caM2BtoL );	//��Կ�԰룬ѭ������2λ���ϲ�
			break;
		default:
			return;
	}
    		
    memcpy(caT32, pcaIO64 + 4, 4); 

	// key 56bit->48bit ��Կ����PC-2�еĲ������ٴ�ȥ��8λ��Ϊ��ӭ��R������Key���
    BitTransfer( pcaKey56, caK48, 48, g_caKeyPC2 ); 		 

	//E����չ, R block 32bit->48bit
    BitTransfer( pcaIO64+4, caR48, 48, g_caExpand); 		

    for (int i = 0; i < 6; i++)
    {
        caR48[i] ^= caK48[i];		//R������Key��� 
    }

    B6to4(caR48, 6, caS32, 4);		//S��ѹ�� 
    BitTransfer(caS32, pcaIO64+4, 32, g_caFP);		//P���û� 
    
    //L������R����������� -> R 
    pcaIO64[4] ^= pcaIO64[0];
    pcaIO64[5] ^= pcaIO64[1]; 	
    pcaIO64[6] ^= pcaIO64[2];
    pcaIO64[7] ^= pcaIO64[3];
    
    // L+R -> output 
    if( iTurn == 15 )
    {
    	memcpy( pcaIO64, pcaIO64+4, 4 ); //���һ��LR���ݿ鲻����λ�� 
    	memcpy( pcaIO64+4, caT32, 4 );
	}
    else
		memcpy( pcaIO64, caT32, 4);

	return;
}


/* 
�ֽ��ܺ��� 
������
int             -- I,�����n�ּ��� 
unsigned char * -- IO,����������ݿ� 
unsigned char * -- I,����Կ
*/ 
void DecipherFunc(int iTurn, unsigned char* pcaIO64, unsigned char* pcaKey56)
{
    unsigned char caT32[4], caP32[4],caX32[4]; // temp variable and prime variable
	unsigned char caK48[6], caR48[6], caS32[4];
    int iaShift[] = {1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};
	
	if( iTurn == 15 )
	{
	 	memcpy(caT32, pcaIO64+4, 4); // ��������,T32����������
	 	memcpy(caP32, pcaIO64+4, 4); // ����ԭʼ״̬ 
	 	memcpy(caX32, pcaIO64, 4); //ֻ�������������� 
    	//E����չ, R block 32bit->48bit
    	BitTransfer( caT32, caR48, 48, g_caExpand); 
	}
    else
    {
    	memcpy(caT32, pcaIO64, 4);  // �������㣬T32����������
    	memcpy(caP32, pcaIO64, 4); // ����ԭʼ״̬ 
    	memcpy(caX32, pcaIO64+4, 4); //ֻ�������������� 
    	BitTransfer( caT32, caR48, 48, g_caExpand); 
	}
    	

	// key 56bit->48bit ��Կ����PC-2�еĲ������ٴ�ȥ��8λ��Ϊ��ӭ��R������Key���
    BitTransfer( pcaKey56, caK48, 48, g_caKeyPC2 ); 		 

		

    for (int i = 0; i < 6; i++)
    {
        caR48[i] ^= caK48[i];		//R������Key��� 
    }

    B6to4(caR48, 6, caS32, 4);		//S��ѹ�� 
    BitTransfer(caS32, caT32, 32, g_caFP);		//P���û� 
    
    caT32[0] ^= caX32[0];
    caT32[1] ^= caX32[1]; 	
    caT32[2] ^= caX32[2];
    caT32[3] ^= caX32[3];
    
   	memcpy( pcaIO64, caT32, 4 ); 
    memcpy( pcaIO64+4, caP32, 4 );

    switch( iaShift[iTurn] )
    {
    	case 1:
    		BitTransfer( pcaKey56, pcaKey56, 56, g_caM1BtoR );	//��Կ�԰룬ѭ������1λ���ϲ�
			break;
		case 2:
			BitTransfer( pcaKey56, pcaKey56, 56, g_caM2BtoR );	//��Կ�԰룬ѭ������2λ���ϲ�
			break;
		default:
			return;
	}	

	return;
}

/*
64λDES���ܺ���
����
unsigned char * -- I,�������ݿ飬64bits������
unsigned char * -- I,��Կ��64bits
unsigned char * -- O,������ݿ飬64bits������ 
*/
void Encrypt(unsigned char* pcaIn, unsigned char* pcaKey, unsigned char* pcaOut)
{
    unsigned char caI64[8], caK56[7];

    BitTransfer(pcaIn, caI64, 64, g_caIP); 		//IP�û� 
    WriteLog(0, (char *)caI64, 8, "[Encrypt] Initial permutation:");
  
    BitTransfer(pcaKey, caK56, 56, g_caKeyPC1);   //��Կȥ��8λ��żУ��λ������λ�û� 
    WriteLog(0, (char*)caK56, 7, "[Encrypt] key PC1:");
    
    // 16�ּ��ܲ��� 
    for( int i = 0; i < 16; i ++ )
    {
    	CipherFunc( i, caI64, caK56 );   
    	WriteLog(0, (char*)caK56, 7, "[Encrypt] key%d:", i+1);
    	WriteLog(0, (char*)caI64, 8, "[Encrypt] in %d turn:", i+1);
	}

    BitTransfer(caI64, pcaOut, 64, g_caInvIP);		//IP���û�
    
    return;
}



/*
64λDES���ܺ���
����
unsigned char * -- I,�������ݿ飬64bits������
unsigned char * -- I,��Կ��64bits
unsigned char * -- O,������ݿ飬64bits������ 
*/
void Decrypt(unsigned char* pcaIn, unsigned char* pcaKey, unsigned char* pcaOut)
{
    unsigned char caI64[8], caK56[7];

    BitTransfer(pcaIn, caI64, 64, g_caIP);		//�����IP�û��õı���ͬ 
    WriteLog(0, (char*)caI64, 8, "[Decrypt] Initial permutation:");
    
    BitTransfer(pcaKey, caK56, 56, g_caKeyPC1);
        
    // 16�ֽ��ܲ��� 
    for( int i = 15; i >= 0; i -- )
    {
    	WriteLog(0, (char*)caK56, 7, "[Decrypt] key%d:", i+1);
    	DecipherFunc( i, caI64, caK56 );   
    	WriteLog(0, (char*)caI64, 8, "[Decrypt] in %d turn, output:", i+1 );
	}

 
    BitTransfer(caI64, pcaOut, 64, g_caInvIP);
    WriteLog(0, (char*)caI64, 8, "inversed permutation:" );
    
    return;

}


int BlockEncrypt(unsigned char* pcaKey, unsigned char* pcaIn,
    unsigned char* pcaOut, int iLen)
{
    int iL = 0;
    int iSize = 0;
    unsigned char cTempIn[8] = { 0 };
    unsigned char cTempOut[8] = { 0 };

    iSize = iLen / 8;
    for (iL = 0; iL < iSize; iL++)
    {
        memcpy(cTempIn, pcaIn + (iL * 8), 8);
        Encrypt(cTempIn, pcaKey, cTempOut);
        memcpy(pcaOut + (iL * 8), cTempOut, 8);
    }
    return 0;
}

int BlockDecrypt(unsigned char* pcaKey, unsigned char* pcaIn,
    unsigned char* pcaOut, int iLen)
{
    int iL = 0;
    int iSize = 0;
    unsigned char cTempIn[8] = { 0 };
    unsigned char cTempOut[8] = { 0 };

    iSize = iLen / 8;

    for (iL = 0; iL < iSize; iL++)
    {
        memcpy(cTempIn, pcaIn + (iL * 8), 8);
        Decrypt(cTempIn, pcaKey, cTempOut);
        memcpy(pcaOut + (iL * 8), cTempOut, 8);
    }
    return 0;
}


