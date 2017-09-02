#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<time.h>

using namespace std;

void RC4()
{
	int* key;
	int keylength;
	cout<<"Enter bytes in the key(>=3): ";
	cin>>keylength;

	time_t time1;
	int seedval = (unsigned int) time(&time1);
	srand(seedval);
	int iv= rand();
	iv =iv & 0xFFFFFF;

	cout<<"\nInitialization vector is: "<<iv;

	key = new int[keylength];
	key[0] = 'W';
	key[1] = 'i';
	key[2] = 'k';
	key[3] = 'i';
	int i=0;
/*	key[keylength - 1] = iv & 0x0000FF;
	key[keylength - 2] = iv & 0x00FF00;
	key[keylength - 3] = iv & 0xFF0000;

	int pass;
	for(i;i<(keylength - 3);i++)
	{
		cout<<"Enter byte #" << (i+1)<< " of the passphrase: ";
		cin>>pass;
		key[i] = pass;
	}
*/
	cout<<"\nKey of the RC4 cipher is:";
	for(i=0; i<keylength;i++)
		cout<<" "<<key[i];

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
		cout<<hex<<(int)charInput<<' ';
		fin.get(charInput);
	}

	fin.close();
	fin.open("plaintext.txt");

	ofstream fout("ciphertext.txt");

	fin.get(charInput);

	cout<<"\nCiphertext is:";
	int k=1;
	i=0,j=0;
	unsigned int input,output,temp;
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
			cout<<"\nKeystream element "<<k<<" is: "<<hex<<temp;
			output = (input ^ temp);
			fout<<output<<' ';
			cout<<"\nCiphertext element "<<k<<" is: "<<hex<<output;
		}
		fin.get(charInput);
		k++;
	}

	fin.close();
	fout.close();
	
	fin.open("ciphertext.txt");
	fout.open("decrypt.txt");
	fin>>input;

	k=1;
	i=0;j=0;

	for (i = 0; i < 256; i++)
	{
		S[i] = i;
	}
	for (i = 0; i < 256; i++)
	{
		j = (j + S[i] + key[i % keylength] ) % 256;
			t1=S[i];
			S[i]=S[j];
			S[j]=t1;
	}
	i=0;j=0;
	cout<<endl;
	while(!fin.eof())
	{
		i = (i+1)%256;
		j = (j+ S[i])%256;
		{
			cout<<"\nCiphertext element "<<k<<" is: "<<hex<<input;
			unsigned int t= S[i];
			 S[i]= S[j];
			 S[j]=t;
			unsigned int temp =  S[( S[i] +  S[j]) % 256];
			cout<<"\nKeystream element "<<k<<" is: "<<hex<<temp;
			output = (input ^ temp);
			fout<<(char)output;
			cout<<"\nPlaintext element "<<k<<" is: "<<hex<<output;
		}
		fin>>input;
		k++;
	}

	fin.close();
	fout.close();
}