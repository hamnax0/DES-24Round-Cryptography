#include<iostream>
#include<string>
#include<bitset>
using namespace std;

//inital permutation table
int IP[64] = {
    58,50,42,34,26,18,10,2,
    60,52,44,36,28,20,12,4,
    62,54,46,38,30,22,14,6,
    64,56,48,40,32,24,16,8,
    57,49,41,33,25,17, 9,1,
    59,51,43,35,27,19,11,3,
    61,53,45,37,29,21,13,5,
    63,55,47,39,31,23,15,7
};

//final permutation table IP-1
int FP[64] = {
    40,8,48,16,56,24,64,32,
    39,7,47,15,55,23,63,31,
    38,6,46,14,54,22,62,30,
    37,5,45,13,53,21,61,29,
    36,4,44,12,52,20,60,28,
    35,3,43,11,51,19,59,27,
    34,2,42,10,50,18,58,26,
    33,1,41, 9,49,17,57,25
};

//expansion table
int E[48] = {
    32, 1, 2, 3, 4, 5,
     4, 5, 6, 7, 8, 9,
     8, 9,10,11,12,13,
    12,13,14,15,16,17,
    16,17,18,19,20,21,
    20,21,22,23,24,25,
    24,25,26,27,28,29,
    28,29,30,31,32, 1
};

//permutation table
int P[32] = {
    16, 7,20,21,
    29,12,28,17,
     1,15,23,26,
     5,18,31,10,
     2, 8,24,14,
    32,27, 3, 9,
    19,13,30, 6,
    22,11, 4,25
};

//Permuted Choice 1
int PC1[56] = {
    57,49,41,33,25,17, 9,
     1,58,50,42,34,26,18,
    10, 2,59,51,43,35,27,
    19,11, 3,60,52,44,36,
    63,55,47,39,31,23,15,
     7,62,54,46,38,30,22,
    14, 6,61,53,45,37,29,
    21,13, 5,28,20,12, 4
};

//permuted choice 2
int PC2[48] = {
    14,17,11,24, 1, 5,
     3,28,15, 6,21,10,
    23,19,12, 4,26, 8,
    16, 7,27,20,13, 2,
    41,52,31,37,47,55,
    30,40,51,45,33,48,
    44,49,39,56,34,53,
    46,42,50,36,29,32
};

//key shifts table
int shiftTable[24]=
{
    1,1,2,2,2,2,2,2,
    1,2,2,2,2,2,2,1,
    2,2,2,2,2,2,2,2
};

//S-Boxes
int SBOX[8][4][16] = {
    // S1
    {
        {14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
        {0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
        {4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
        {15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}
    },
    // S2
    {
        {15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},
        {3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},
        {0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},
        {13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}
    },
    // S3
    {
        {10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},
        {13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},
        {13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},
        {1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}
    },
    // S4
    {
        {7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},
        {13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},
        {10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},
        {3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}
    },
    // S5
    {
        {2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},
        {14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},
        {4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},
        {11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}
    },
    // S6
    {
        {12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},
        {10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},
        {9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},
        {4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}
    },
    // S7
    {
        {4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},
        {13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},
        {1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},
        {6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}
    },
    // S8
    {
        {13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},
        {1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},
        {7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},
        {2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}
    }
};

//permutation
void permutation(int input[], int output[], int table[], int outsize)
{
	for(int i=0;i<outsize;i++)
	{
		output[i]=input[table[i]-1];
	}
}

//left shifts
void shift(int arr[], int shifts, int size)
{
	for(int i=0;i<shifts;i++)
	{
		int first=arr[0];
		for(int j=0;j<size-1;j++)
		{
			arr[j]=arr[j+1];
		}
		arr[size-1]=first;
	}
}

//key expansion
void keyExp(int key[64], int roundkeys[24][48])
{
	int key56[56];
	permutation(key,key56,PC1,56);
	
	int c[28],d[28];
	for(int i=0;i<28;i++)
	{
		c[i]=key56[i];
		d[i]=key56[i+28];
	}
	for(int k=0;k<24;k++)  //24 rounds
	{
		shift(c,shiftTable[k],28);
		shift(d,shiftTable[k],28);
	
	int combined[56];
	for(int i=0;i<28;i++)
	{
		combined[i]=c[i];
		combined[i+28]=d[i];
	}
	
	permutation(combined,roundkeys[k],PC2,48);
	}
}

//fFucntion
void fFunction(int R[32], int key[48], int output[32])
{
	int ExpandOutput[48];
	permutation(R,ExpandOutput,E,48);
	
	int xored[48];
	for(int i=0;i<48;i++)
	{
		xored[i]=ExpandOutput[i]^key[i];
	}
	
	int index=0;
	int sboxOutput[32];
	for(int i=0;i<8;i++)
	{
		int block[6];
		for(int j=0;j<6;j++)
		{
			block[j]=xored[i*6+j];
		}
		
		int row=block[0]*2+block[5];
		int col=block[1]*8+block[2]*4+block[3]*2+block[4];
		
		int value=SBOX[i][row][col];
		for(int k=3;k>=0;k--)
		{
			sboxOutput[index+k]=value%2;
			value/=2;
		}
		index+=4;
	}
	
	permutation(sboxOutput,output,P,32);
}

//main DES Encryption
void DES(int plaintext[64],int key[64],int ciphertext[64])
{
	int permutedText[64];
	permutation(plaintext,permutedText,IP,64);
	
	int R[32],L[32];
	for(int i=0;i<32;i++)
	{
		L[i]=permutedText[i];
		R[i]=permutedText[i+32];
	}
	
	int roundkeys[24][48];
	keyExp(key,roundkeys);
	
	for(int i=0;i<24;i++)
	{
		int temp[32];
		for(int j=0;j<32;j++)
		{
			temp[j]=R[j];
		}
		
		int fOut[32];
		fFunction(R,roundkeys[i],fOut);
		
		for(int j=0;j<32;j++)
		{
			R[j]=fOut[j]^L[j];
		}
		
		for(int j=0;j<32;j++)
		{
			L[j]=temp[j];
		}
	}
	
	int combined[64];
	for(int i=0;i<32;i++)
	{
		combined[i]=R[i];
		combined[i+32]=L[i];
	}
	
	permutation(combined,ciphertext,FP,64);
}

void DES_Decrypt(int ciphertext[64], int key[64], int plaintext[64])
{
    int permutedText[64];
    permutation(ciphertext,permutedText,IP,64);

    int L[32],R[32];
    for(int i=0;i<32;i++)
    {
        L[i]=permutedText[i];
        R[i]=permutedText[i+32];
    }

    int roundkeys[24][48];
    keyExp(key,roundkeys);

    for(int i=0;i<24;i++)
    {
        int temp[32];
        for(int j=0;j<32;j++)
        {
            temp[j]=R[j];
        }

        int fOut[32];
        fFunction(R,roundkeys[23-i],fOut);  // reverse order

        for(int j=0;j<32;j++)
        {
            R[j]=fOut[j]^L[j];
        }

        for(int j=0;j<32;j++)
        {
            L[j]=temp[j];
        }
    }

    int combined[64];
    for(int i=0;i<32;i++)
    {
        combined[i]=R[i];
        combined[i+32]=L[i];
    }

    permutation(combined,plaintext,FP,64);
}

//main function
int main()
{
    string text,keyStr;
    cout<<"Enter plaintext (8 chars): ";
    cin>>text;

    cout<<"Enter key (8 chars): ";
    cin>>keyStr;

    int plaintext[64],key[64],ciphertext[64];

    //plaintext string to binary
    for(int i=0;i<8;i++)
    {
        bitset<8> b(text[i]);
        for(int j=0;j<8;j++)
        {
            plaintext[i*8+j]=b[7-j];
        }
    }

    //key string to binary
    for(int i=0;i<8;i++)
    {
        bitset<8> b(keyStr[i]);
        for(int j=0;j<8;j++)
        {
            key[i*8+j]=b[7-j];
        }
    }

    // DES encryption
    DES(plaintext, key, ciphertext);

    // Convert ciphertext to string
    cout<<"\n\nCiphertext: ";
    for(int i=0;i<8;i++)
    {
        int val=0;

        for(int j=0;j<8;j++)
        {
            val=val*2+ciphertext[i*8+j];
        }

        cout<<char(val);
    }

	//decryption
	int decrypted[64];
	DES_Decrypt(ciphertext, key, decrypted);

	cout<<"\nDecrypted text: ";
	for(int i=0;i<8;i++)
	{
    	int val=0;
    	for(int j=0;j<8;j++)
    	{
        	val=val*2+decrypted[i*8+j];
    	}
    	cout<<char(val);
	}
    return 0;
}