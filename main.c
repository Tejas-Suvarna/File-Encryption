// Basic imports
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>

void decrypt();
void encrypt();

// File pointers
FILE *sfile,*tfile;

// Some global variables
char password[20],file_path[100],extension[10];
char afile_path[15]="temp.";

void main()
{
	clrscr(); //Remove this for LINUX
	char ch;
	int x,y,z;
	while(1)
	{
		printf("\n1.Encrypt a file\n2.Decrypt a file\n3.Exit\n");
		ch=getch();
		switch(ch)
		{
			case '1':encrypt();
					break;
			case '2':decrypt();
					break;
			case '3':exit(0);
			default: printf("Invalid input!");
		}
	}

}
// Function to encrypt the file
void encrypt()
{
	long int i,j=0,k;
	long int count=0;
	char ch;
	printf("Enter the filename with extension:");
	gets(file_path);  // Reads the path of file to encrypt
	printf("file = %s\n",file_path);
	
	// Reverses the path to check the extension of the file
	strrev(file_path);
	for(count=0;file_path[count]!='.';count++)
	{
		extension[count]=file_path[count];
		if(count>strlen(file_path))
		{
			printf("Invalid file!");
			getch();
			exit(0);
		}
	}
	extension[count]='\0';
	strrev(extension);
	strrev(file_path);
	count=0;
	
	// Reads the password
	printf("Enter the password of max 15 characters:");
	AGAINPASS:i=0; // A goto statement if the user wants to re-enter the password
	while(1)
	{
	   ch=getch();
	   if(ch==13)
	   {
			printf("\n");
			break;
	   }
	   if(ch==8)
	   {
			printf("\nPlease re-enter the password:");
			goto AGAINPASS;

	   }
	   printf("*");
	   password[i]=ch;
	   i++;
	}
	password[i]='\0';
	printf("Please Wait!\n");
	i=0;
	sfile=fopen(file_path,"rb");
	if(sfile==NULL)
	{
	 printf("File not found!");
	 getch();
	 exit(0);
	 return;
	}
	
	// Checking the length of the file
	while(!feof(sfile))
	{
	   //	printf(" (%c - %d) ",ch,count);
		fread(&ch,1,1,sfile);
		count++;
           //	printf("count = %d",count);
	   //	ch=fgetc(sfile);
	}
	fclose(sfile);
	
	// Performing the encryption
	sfile=fopen(file_path,"rb");
	char tempch;
	i=count/strlen(password);  // We divide the file into n number of parts where n is the length of the file, i is the size of each part
	printf("Size = %ld bytes",count);
	strcat(afile_path,extension);
	printf("\nEncrypting file - %s *PLEASE DON'T CLOSE THE PROGRAM*\n",afile_path);
	
	// We add ASCII value of each character of the password of it's corresponding part of the divided file
	tfile=fopen(afile_path,"wb");
	  for(j=0;j<strlen(password);j++)
	  {
	   for(k=1;k<=i;k++)
	   {
		 fread(&ch,1,1,sfile);
		 if(feof(sfile))
		 {
		   printf("\nFile Encrypted!\n");
		   break;
		 }
		 ch=ch+password[j];
		 fwrite(&ch,1,1,tfile);
		}
	 }
	
	// This part is to encrypt the last remaining part of the file that is unequal in size of the other parts
	 while(!feof(sfile))
	 {
		 fread(&ch,1,1,sfile);
		 if(feof(sfile))
		 {
		   printf("\nFile Encrypted!\n");
		   break;
		 }
		 ch=ch+(password[0]+password[1]);
		 fwrite(&ch,1,1,tfile);
	 }
	fclose(sfile);
	fclose(tfile);
}

// It is the opposite to encryption
void decrypt()
{
	long int count=0;
	char ch;
	printf("Enter the password of max 15 characters:");
	long int i=0,j=0,k;
	AGAINPASS:i=0;
	while(1)
	{
	   ch=getch();
	   if(ch==13)
	   {
			printf("\n");
			break;
	   }
	   if(ch==8)
	   {
			printf("\nPlease re-enter the password:");
			goto AGAINPASS;

	   }
	   printf("*");
	   password[i]=ch;
	   i++;
	}
	password[i]='\0';
	printf("Please Wait!\n");
	i=0;
	sfile=fopen(afile_path,"rb");
	if(sfile==NULL)
	{
	 printf("File not found!");
	 return;
	}
	char tempch;
	while(!feof(sfile))
	{
		fread(&ch,1,1,sfile);
		count++;
	}
	fclose(sfile);
	char tempfname[15]="j";
	sfile=fopen(afile_path,"rb");
	i=count/strlen(password);
	strcat(tempfname,afile_path);
	strcpy(afile_path,tempfname);
	printf("\nDecrypting file - %s *PLEASE DON'T CLOSE THE PROGRAM*\n",afile_path);
	tfile=fopen(afile_path,"wb");

	for(j=0;j<strlen(password);j++)
	  {
	   for(k=1;k<=i;k++)
	   {
		 fread(&ch,1,1,sfile);
		 if(feof(sfile))
		 {
		   printf("\nFile Decrypted!\n");
		   break;
		 }
		 ch=ch-password[j];
		 fwrite(&ch,1,1,tfile);
		}
	 }
	 while(!feof(sfile))
	 {
		 fread(&ch,1,1,sfile);
		 if(feof(sfile))
		 {
		   printf("\nFile Decrypted!\n");
		   break;
		 }
		 ch=ch-(password[0]+password[1]);
		 fwrite(&ch,1,1,tfile);
	 }
	fclose(sfile);
	fclose(tfile);
}
