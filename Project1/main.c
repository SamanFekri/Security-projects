 /* 
	Author: SKings (samanf74@gmail.com)
	Date: 10/26/2016
	HOW TO USE 
 	 gcc main.c -o main -lssl -lcrypto
 	 ./main
 	 */

 /* C headers*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

 /* OpenSSL headers */
#include <openssl/des.h>

 /* Function for encrypt des in openssl */
char * Encrypt( char *Key, char *Msg, int size) {
 
        static char* Res;
        int n=0;
        DES_cblock Key2;
        DES_key_schedule schedule;
 
        Res = ( char * ) malloc( size );
 
        /* Prepare the key for use with DES_cfb64_encrypt */
        memcpy( Key2, Key,8);
        DES_set_odd_parity( &Key2 );
        DES_set_key_checked( &Key2, &schedule );
 
        /* Encryption occurs here */
        DES_cfb64_encrypt( ( unsigned char * ) Msg, ( unsigned char * ) Res,
                           size, &schedule, &Key2, &n, DES_ENCRYPT );
 
         return (Res);
}

 /* Function for decrypt des in openssl */
char * Decrypt( char *Key, char *Msg, int size) {
 
        static char* Res;
        int n=0;
 
        DES_cblock Key2;
        DES_key_schedule schedule;
 
        Res = ( char * ) malloc( size );
 
        /* Prepare the key for use with DES_cfb64_encrypt */
        memcpy( Key2, Key,8);
        DES_set_odd_parity( &Key2 );
        DES_set_key_checked( &Key2, &schedule );
 
        /* Decryption occurs here */
        DES_cfb64_encrypt( ( unsigned char * ) Msg, ( unsigned char * ) Res,
                           size, &schedule, &Key2, &n, DES_DECRYPT );
 
        return (Res);
 
}

 /* Function read a file */
char* readFromFile(char *path)	{
	char* buffer = 0;
	long length;
	FILE * f = fopen (path, "rb");
  	if (f){
	    fseek (f, 0, SEEK_END);
	    length = ftell (f);
	    fseek (f, 0, SEEK_SET);
	    buffer = malloc (length);
	    if (buffer){
	      fread (buffer, 1, length, f);
	    }
  	  	fclose (f);
  	}

  	return buffer;
}

/* Function write in file */
int writeInFile(char* path, char* text){
	FILE * f = fopen(path,"wb+");
	if(f){
		fputs(text,f);
		fclose(f);
		return 0;
	}
	return 1;
}

/* main function */
int main() {
	// initial
	// Key of encryption
	char key[]="salamsalam";
    
    char* encrypted;
    char* decrypted;

    // Reading orginal message file from orginal.txt
    char* c = readFromFile("orginal.txt");
    char** orginal = malloc(sizeof(char*) * 1);
    orginal[0] = c;

	printf("OrginalText {\n%s\n}\n", orginal[0]);

    // set size of encrypted an decrypted
    encrypted = malloc( strlen(orginal[0]));
    decrypted = malloc( strlen(orginal[0]));

    // Encrypt here
	memcpy(encrypted,Encrypt(key,orginal[0],strlen(orginal[0])),strlen(orginal[0]));
	printf("EncryptedTexxt {\n%s\n}\n",encrypted);
	// Write in enc.txt
	writeInFile("enc.txt",encrypted);

	// Decrypt here
	memcpy(decrypted,Decrypt(key,encrypted,strlen(orginal[0])), strlen(orginal[0]));
	printf("DecryptedTexxt {\n%s\n}\n",decrypted);
	// Write in dec.txt
	writeInFile("dec.txt",decrypted);

    return 0;
}