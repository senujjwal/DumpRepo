#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<time.h>

using namespace std;

unsigned int crc32Table[256];
void init_CRC32 ()
{

	int i, j;
	unsigned int dwPolynomial;
	unsigned int dwCrc;

	dwPolynomial = 0xEDB88320;

	// Lookup table
	for (i = 0; i<256; i++){
		dwCrc = i;
		for (j = 8; j>0; j--){
			if (dwCrc & 1){
				dwCrc >>= 1;
				dwCrc ^= dwPolynomial;
			}
			else {
				dwCrc >>= 1;
			}
		}
		crc32Table[i] = dwCrc;
	}
}

void WEP()
{
	init_CRC32();
	int* key;
	int keylength;
	cout<<"Enter bytes in the key(>=3): ";
	cin>>keylength;

	time_t t;
	int seedval = (unsigned int) time(&t);
	srand(seedval);
	int iv= rand();
	iv =iv & 0xFFFFFF;

	key = new int[keylength];
	int i=0;
	key[keylength - 1] = iv & 0x0000FF;
	key[keylength - 2] = iv & 0x00FF00;
	key[keylength - 3] = iv & 0xFF0000;

	int pass;
	for(i;i<(keylength - 3);i++)
	{
		cout<<"Enter byte #" << (i+1)<< " of the passphrase: ";
		cin>>pass;
		key[i] = pass;
	}

	cout<<"\nInitialization vector is: "<<iv<<endl;
	cout<<"\nKey of the RC4 cipher is:";
	for(i=0; i<keylength;i++)
		cout<<' '<<key[i];

	unsigned int S[256];

	for (i = 0; i < 256; i++)
	{
		S[i] = i;
	}
	int j = 0;
	int t1;
	for (i = 0; i < 256; i++)
	{
		j = (j + S[i] + key[i % keylength] ) % 256;
		t1=S[i];
		S[i]=S[j];
		S[j]=t1;
	}

	char charInput;
	ifstream fin("plaintext.txt");

	fin.get(charInput);
	cout<<"\nPlaintext message is: ";
	while(!fin.eof())
	{
		cout<<charInput;
		fin.get(charInput);
	}

	fin.close();
	fin.open("plaintext.txt");

	fin.get(charInput);

	/*Generate CRC 32*/
	unsigned int crc32Result = 0xFFFFFFFF;
	while(!fin.eof())
	{

	unsigned char iLookup;
		iLookup = (crc32Result & 0xFF) ^ charInput;
		crc32Result >>= 8;
		crc32Result ^= crc32Table[iLookup];
		fin.get(charInput);
	}
	crc32Result=~(crc32Result);
	cout<<"\n\nChecksum = "<<hex<<crc32Result;
	/*Generaton completed*/	
	fin.close();
	ofstream fout("ciphertext.txt");

	cout<<"\nAttaching the IV to ciphertext...";
	fout<<iv<<' ';

	unsigned int input,output,temp;

	cout<<"\nAttaching the CRC to ciphertext...";
	fout<<crc32Result<<' ';
	fin.open("plaintext.txt");

	fin.get(charInput);

	i=0,j=0;
	while(!fin.eof())
	{
		i = (i+1)%256;
		j = (j+S[i])%256;
		{
			input = (unsigned int)charInput;
			t1= S[i];
			S[i]= S[j];
			S[j]=t1;
			temp =  S[( S[i] +  S[j]) % 256];
			output = (input ^ temp);
			fout<<output<<' ';
		}
		fin.get(charInput);
	}

	fin.close();
	fout.close();

	fin.open("ciphertext.txt");
	cout<<"\nCiphertext is (With IV attached): ";
	fin>>input;
	while(!fin.eof())
	{
		cout<<dec<<input<<' ';
		fin>>input;
	}
	fin.close();

	fin.open("ciphertext.txt");
	fout.open("decrypt.txt");

	cout<<"\nDecrypt ciphertext?(Y/N): ";
	char ans;
	cin>>ans;
	if(ans == 'N' || ans == 'n')
		exit(0);

	int receivedKeylength;
	cout<<"\nEnter keylength for decryption: ";
	cin>>receivedKeylength;

	int receivedIV;
	fin>>receivedIV;
	cout<<"\nReceived IV is: "<<receivedIV<<endl;

	int* receivedKey = new int[receivedKeylength];

	for(i=0;i<(receivedKeylength - 3);i++)
	{
		cout<<"Enter byte #" << (i+1)<< " of the passphrase: ";
		cin>>receivedKey[i];
	}
	receivedKey[receivedKeylength - 1] = receivedIV & 0x0000FF;
	receivedKey[receivedKeylength - 2] = receivedIV & 0x00FF00;
	receivedKey[receivedKeylength - 3] = receivedIV & 0xFF0000;

	cout<<"\nReceived key of the RC4 cipher is:";
	for(i=0; i<receivedKeylength;i++)
		cout<<' '<<receivedKey[i];

	i=0;j=0;
	/*Initialize State*/
	for (i = 0; i < 256; i++)
	{
		S[i] = i;
	}
	for (i = 0; i < 256; i++)
	{
		j = (j + S[i] + receivedKey[i % receivedKeylength] ) % 256;
		t1=S[i];
		S[i]=S[j];
		S[j]=t1;
	}
	i=0;j=0;
	cout<<endl;
	/*Initialize State over*/
	fin>>input;
	int received_CRC;
	cout<<"Received CRC:"<<hex<<input<<dec;
	received_CRC = input;
	fin>>input;
	while(!fin.eof())
	{
		i = (i+1)%256;
		j = (j+ S[i])%256;
		{
			unsigned int t= S[i];
			S[i]= S[j];
			S[j]=t;
			unsigned int temp =  S[( S[i] +  S[j]) % 256];
			output = (input ^ temp);
			fout<<(char)output;
		}
		fin>>input;
	}

	fin.close();
	fout.close();

	cout<<"\nDecrypted plaintext is:";
	fin.open("decrypt.txt");
	fin.get(charInput);
	/*Generate CRC 32*/
	crc32Result = 0xFFFFFFFF;
	while(!fin.eof())
	{

	unsigned char iLookup;
		iLookup = (crc32Result & 0xFF) ^ (int)charInput;
		crc32Result >>= 8;
		cout<<charInput;
		crc32Result ^= crc32Table[iLookup];
		fin.get(charInput);
	}
	crc32Result=~(crc32Result);
	cout<<"\n\nChecksum = "<<hex<<crc32Result;
	/*Generaton completed*/	
	fin.close();

	if(crc32Result !=received_CRC)
		cout<<"Checksum unsuccesful???!!!";
	else
		cout<<"Checksum successful";
}