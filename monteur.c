#include<stdio.h> 			/* PRE DEFINED HEADER FILES */
#include<conio.h>
#include<string.h>
#include<stdlib.h>

	/*MINI PROJECT :

	SUBMITED BY :
	Name: Sunil Joshi and Shubham Gupta
	Roll No: 2007563 and 2007562
	Section:CSE

	MY MACHINE NAME IS : "MONTEUR"

	"MONTEUR" is a german word for "ASSEMBLER";

	Note: Input file has to be in the same format ;
*/



int main()     // Main function(not returning any value)
{
  char a[10],ad[10],label[10],opcode[10],operand[10],symbol[10],ch,fnm[15],ab[15]; // Initializing character value.

  int st,diff,diff1,i,address,address1,add,len,alen,finaddr,prevaddr,j=0;

  char mnemonic[15][15]={"LDA","STA","LDCH","STCH","ADD","SUB","MUL","DIV","J","JSUB"};  //Initializing mnemonics.

  int locctr=0x0,start,l,c=0x0,k=0,bol=0;    // Initalizing Location counter to zero for further use.

  char code[15][15]={"00","0C","50","54","28","29","3A","3B","3E","3F"};    // Defining object code for differnt mnemonics.

  FILE *fp1,*fp2,*fp3,*fp4;   // Making File pointer to operate different files.
  printf("ENTER THE PROGRAM FILE NAME  : \n");
  scanf("%s",&fnm);

  fp1 = fopen("MEDIATOR.txt","w");   // Opening MEDIATOR.txt in write mode.
  fp3 = fopen(fnm,"r");              // Opening fnm in read mode.

  printf("\n\n\t\t\tINPUT FILE:\n\n");
  ch=fgetc(fp3);

  while(ch!=EOF)
  {
   	printf("%c",ch);   // Printing Character.
   	ch=fgetc(fp3);
  }
 rewind(fp3);
 printf("\n\nSTART OF PASS 1 ");

 fp2=fopen("SYMTAB.txt","w");     //Opening SYMTAB.txt in write mode.
 fscanf(fp3,"%s%s%s%X",label,opcode,operand,&address);

 if(strcmp(operand,"START")==0)
 {
        start=address;
        locctr=start;
        prevaddr=locctr;
        c=address;
        fprintf(fp1,"%s\t%s\t%X\n",opcode,operand,address);    // printing opcode and ites operand with address.
 }
 else
        locctr=0x0;

 fscanf(fp3,"%s%s%s",label,opcode,operand);
 while(strcmp(opcode,"END")!=0)
 {
      if(strcmp(label,"**")!=0)

        fprintf(fp2,"%s\t%X\n",label,locctr);

        if(strcmp(opcode,"BYTE")==0)
            {
                fprintf(fp1,"%X\t%s\t%s\t%s\t\n",address,label,opcode,operand);
                len=strlen(operand);
                address+=len-3;
                locctr+=len-3;
            }
            else if(strcmp(opcode,"RESB")==0)
           {
                fprintf(fp1,"%X\t%s\t%s\t%s\n",address,label,opcode,operand);
                address+=(atoi(operand));
                locctr+=(atoi(operand));
           }
    else if (strcmp(opcode,"RESW")==0)
    {
        fprintf(fp1,"%X\t%s\t%s\t%s\n",address,label,opcode,operand);
        address+=(3*(atoi(operand)));
         locctr+=(3*(atoi(operand)));
    }
   else
   {
      fprintf(fp1,"%X\t%s\t%s\t%s\n",address,label,opcode,operand);
       address+=3;
       locctr+=3;
   }
   fscanf(fp3,"%s%s%s",label,opcode,operand);
  }

  fprintf(fp1,"%X\t%s\t%s\t%s\n",address,label,opcode,operand);
  l=address;

  fclose(fp1);   // Closing file fp1.
  fclose(fp2);  // Closing file fp2.
  fclose(fp3);  // Closing file fp3.

	printf("\n\nINTERMEDIATE FILE  : AFTER ADRESSING \n\n\t");

  fp1=fopen("MEDIATOR.txt","r");     // Reading from MEDIATOR.TXT.
  ch=fgetc(fp1);

  while(ch!=EOF)
  {
   printf("%c",ch);
   ch=fgetc(fp1);
  }
  fclose(fp1);

  printf("\n\nTHE LENGTH OF THE PROGRAM IS : %X",l-c);
															//ADDRESSING DONE IN MEDIATOR FILE;
															//AFTER ADDRESING :
	printf("\n\nSYMBOL TABLE CREATED");

  printf("\n\n\t\t\tSYMBOL TABLE :\n\n");
  fp2=fopen("SYMTAB.txt","r");

  ch=fgetc(fp2);
  while(ch!=EOF)
  {
   printf("%c",ch);
   ch=fgetc(fp2);
  }
fclose(fp2);

printf("\n\nEND OF PASS 1");
printf("\n\nSTART OF PASS 2 ");

 fp1 = fopen("OUTPUT.txt","w");   // Writing to output.txt
  fp2 = fopen("SYMTAB.txt","r");  // Reading from SYMTAB.txt
  fp3 = fopen("abc.txt","r");     // Reading from abc.txt.
  fp4 = fopen("OBJCODE.txt","w");  //Writing to OBJCODE.txt/

  fscanf(fp3,"%s%s%s",label,opcode,operand);

  while(strcmp(opcode,"END")!=0)
  {
   prevaddr=address;
   fscanf(fp3,"%X%s%s%s",&address,label,opcode,operand);
  }

  finaddr=address;
  fclose(fp3);

 fp3=fopen("MEDIATOR.txt","r");

  fscanf(fp3,"%s%s%s",label,opcode,operand);
  if(strcmp(opcode,"START")==0)
  {
   fprintf(fp1,"\t%s\t%s\t%s\n",label,opcode,operand);
   fprintf(fp4,"H^%s^00%s^00%X\n",label,operand,finaddr);
   fscanf(fp3,"%X%s%s%s",&address,label,opcode,operand);

   st=address;
   diff=prevaddr-st;
    fprintf(fp4,"T^00%X^%X",address,diff);
  }

  while(strcmp(opcode,"END")!=0)
  {
   if(strcmp(opcode,"BYTE")==0)
   {
    fprintf(fp1,"%X\t%s\t%s\t%s\t",address,label,opcode,operand);
    len=strlen(operand);
    alen=len-3;
    fprintf(fp4,"^");

    for(i=2;i<(alen+2);i++)
    {
     itoa(operand[i],ad,16);
     fprintf(fp1,"%s",ad);
     fprintf(fp4,"%s",ad);
    }
    fprintf(fp1,"\n");
   }
   else if(strcmp(opcode,"WORD")==0)
   {
    len=strlen(operand);
    itoa(atoi(operand),a,10);
    fprintf(fp1,"%X\t%s\t%s\t%s\t00000%s\n",address,label,opcode,operand,a);
    fprintf(fp4,"^00000%s",a);
   }
   else if((strcmp(opcode,"RESB")==0)||(strcmp(opcode,"RESW")==0))

    fprintf(fp1,"%X\t%s\t%s\t%s\n",address,label,opcode,operand);

   else
   {

    while(strcmp(opcode,mnemonic[j])!=0)
     j++;

    if(strcmp(operand,"COPY")==0)
     fprintf(fp1,"%X\t%s\t%s\t%s\t%s0000\n",address,label,opcode,operand,code[j]);
    else
    {
     rewind(fp2);
     fscanf(fp2,"%s%X",symbol,&add);
      while(strcmp(operand,symbol)!=0)
       fscanf(fp2,"%s%X",symbol,&add);
     fprintf(fp1,"%X\t%s\t%s\t%s\t%s%X\n",address,label,opcode,operand,code[j],add);
     fprintf(fp4,"^%s%X",code[j],add);
    }
   }
   fscanf(fp3,"%X%s%s%s",&address,label,opcode,operand);
  }

  fprintf(fp1,"%X\t%s\t%s\t%s\n",address,label,opcode,operand);
  fprintf(fp4,"\nE^00%X",st);

  printf("\n\n\tINTERMEDIATE FILE IS COVERTED INTO OBJECT CODE");
printf("\n\nEND OF PASS 2");

  fclose(fp1);
  fclose(fp2);
  fclose(fp3);
  fclose(fp4);

  printf("\n\n\t\t\tOUTPUT FILE :\n\n");
  fp1=fopen("OUTPUT.txt","r");
  ch=fgetc(fp1);

  while(ch!=EOF)
  {
   printf("%c",ch);
   ch=fgetc(fp1);
  }
  printf("\n\nCONTENTS OF OBJECT CODE FILE :\n\n");
  fp4=fopen("OBJCODE.txt","r");
  ch=fgetc(fp4);

  while(ch!=EOF)
  {
   printf("%c",ch);
   ch=fgetc(fp4);
  }
  fclose(fp1);
  fclose(fp3);
  fclose(fp4);

  getch();     // For holding screen.
  return(0);
}
