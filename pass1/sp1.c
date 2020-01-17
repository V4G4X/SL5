#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define N 90

//Symbol table structure
typedef struct sym_table
{
	char sym_no[N];
	char sym[N];
	char sym_addr[N];
}sym_table;


//Literal table structure
typedef struct lit_table
{
	char lit_no[N];
	char lit[N];
	char lit_addr[N];
}lit_table;


//Funtion to check if symbol is present
int check_symtab(sym_table symbol_table[N],int n,char s[])
{
	int i=0;
	for(i=0;i<n;i++)
	{
		if(strcmp(symbol_table[i].sym,s)==0)
			return i;
	}
	return -1;
}


//Function to check if literal is present
int check_littab(lit_table literal_table[N],int start,int end,char s[])
{
	int i=0;
	for(i=start;i<end;i++)
	{
		if(strcmp(literal_table[i].lit,s)==0)
			return i;
	}
	return -1;
}


int main()
{
	sym_table symbol_table[N];                  //symbol_table array
	lit_table literal_table[N];                 //Literal table array
	FILE *f1,*f2,*f3;                           //File pointers
	int pooltab[N],start=0,flag=0;
	int sa,LC=0,m[N],i=0,k=0;
	int symtab_count=0;
	int littab_count=0;
	int pooltab_count=1;
	pooltab[0]=0;
	char label[N],mnemonic[N],operand1[N],operand2[N],name[N],opcode[N],type[N],n[N],symbol[N],value[N];
	
	printf("PASS 1 ASSEMBLER\n");
	f1=fopen("input1.txt","r");
	f2=fopen("mot.txt","r");
	f3=fopen("output1.txt","w+");
	
	fscanf(f1,"%s%s%s%s",label,mnemonic,operand1,operand2);
	if(strcmp(mnemonic,"START")==0)
 	{
 	    if(strcmp(operand1,"-")==0)
    	{
    	    strcpy(operand1,"100");
    	}
    	sa=atoi(operand1);
    	LC=sa;
    	fprintf(f3,"%d (AD,01)",LC);
 
 		fscanf(f1,"%s%s%s%s",label,mnemonic,operand1,operand2);
 		while(strcmp(mnemonic,"END")!=0)
 		{	
 			if(strcmp(label,"-")!=0)
 			{
 				char s[N];
 				k=check_symtab(symbol_table,symtab_count,label);
 				if(k!=-1)
 				{
 					sprintf(s,"%d",LC);
 					strcpy(symbol_table[k].sym_addr,s);
 				}
 				else
 				{
 					char s[N],s1[N];
 					strcpy(symbol_table[symtab_count].sym,label);
 					sprintf(s,"%d",LC);
 					strcpy(symbol_table[symtab_count].sym_addr,s);
 					sprintf(s1,"%d",symtab_count+1);
 					strcpy(symbol_table[symtab_count].sym_no,s1);
 					symtab_count++;
 				}
 			}
 			
 			if(strcmp(mnemonic,"ORIGIN")==0)
 			{
 				LC=atoi(operand1);
 				fprintf(f3,"%d (AD,04)",LC);
 			}
 			
 			else if(strcmp(mnemonic,"LTORG")==0)
 			{
 				char s[N];
				fprintf(f3,"%d (AD,05)",LC);
 				for(i=start;i<littab_count;i++)
 				{
 					sprintf(s,"%d",LC);
 					strcpy(literal_table[i].lit_addr,s);
 					LC=LC+1;				
 				}
 				start=littab_count;
 				pooltab[pooltab_count]=start;
 				pooltab_count++; 
 			}
 			
 			else
 			{
 				fseek(f2,SEEK_SET,0);
 				fscanf(f2,"%s%s%s",name,opcode,type);
 				while(!feof(f2))
 				{
 					if(strcmp(mnemonic,name)==0)
 					{
 						fprintf(f3,"%d (%s,%s) ",LC,type,opcode);
	 					LC=LC+1;
	 					break;
	 				}
 					else
 					{
 						fscanf(f2,"%s%s%s",name,opcode,type);
	 				}
	 			}
	 			if(strcmp(operand1,"-")!=0 || strcmp(operand2,"-")!=0)
	 			{
	 				if(strcmp(operand1,"AREG")==0)
	 					fprintf(f3,"(R,01) ");
	 				else if(strcmp(operand1,"BREG")==0)
	 					fprintf(f3,"(R,02) ");	
	 				else if(strcmp(operand1,"CREG")==0)
	 					fprintf(f3,"(R,03) ");	
	 				else if(strcmp(operand1,"LT")==0)
	 					fprintf(f3,"(CC,01) ");
	 				else if(strcmp(operand1,"GT")==0)
	 					fprintf(f3,"(CC,02) ");
	 				else if(strcmp(operand1,"LE")==0)
	 					fprintf(f3,"(CC,03) ");
	 				else if(strcmp(operand1,"GE")==0)
	 					fprintf(f3,"(CC,04) ");
	 				else if(strcmp(operand1,"NE")==0)
	 					fprintf(f3,"(CC,05) ");
		 			else if(strcmp(operand1,"EQ")==0)
	 					fprintf(f3,"(CC,06) ");
	 				else if(strcmp(operand1,"ANY")==0)
	 					fprintf(f3,"(CC,07) ");
	 			
	 				if(strcmp(operand2,"-")!=0)	
	 				{
	 					if(operand2[0]!= '=')
	 					{
	 						k=check_symtab(symbol_table,symtab_count,operand2);
	 						if(k==-1)
	 						{
	 							char s[N],s1[N];
	 							fprintf(f3,"(ST,%d) ",(symtab_count+1));
 								strcpy(symbol_table[symtab_count].sym,operand2);
 								strcpy(symbol_table[symtab_count].sym_addr,"-1");
 								sprintf(s1,"%d",symtab_count+1);
 								strcpy(symbol_table[symtab_count].sym_no,s1);
 								symtab_count++;
	 						}
	 						else
	 						{
	 							fprintf(f3,"(ST,%d) ",(k+1));
	 						}
	 					}
	 					else
	 					{
	 						k=check_littab(literal_table,start,littab_count,operand2);
	 						if(k==-1)
	 						{
	 							char s[N],s1[N];
	 							fprintf(f3,"(LT,%d)",(littab_count));
	 							strcpy(literal_table[littab_count].lit,operand2);
	 							strcpy(literal_table[littab_count].lit_addr,"-1");
	 							sprintf(s1,"%d",littab_count);
 								strcpy(literal_table[littab_count].lit_no,s1);
 								littab_count++;
	 						}
	 						else
	 						{
	 							fprintf(f3,"(LT,%d) ",(k));
	 						}
	 					}
	 				}
	 			}
	 		}	
	 		fprintf(f3,"\n");
 			fscanf(f1,"%s%s%s%s",label,mnemonic,operand1,operand2);
 		}
 		int flag=0;
 		if(strcmp(mnemonic,"END")==0)
 		{
 		    for(i=0;i<littab_count;i++)
 		    {
 		        if(strcmp(literal_table[i].lit_addr,"-1")==0)
 		        {
 		            char s[N];
 					sprintf(s,"%d",LC);
 					strcpy(literal_table[i].lit_addr,s);
 					LC=LC+1;
 					flag=1;				
 			}
 		    }
 		    if(flag==1)
 		    {
 		        start=littab_count;
 			    pooltab[pooltab_count]=start;
 			    pooltab_count++; 
 		}
            	fprintf(f3,"%d (AD,02)\n",LC);	
 		}
 	}
 	else
 		printf("\nError in the code\n");
 	
 	fclose(f1);
 	fclose(f2);
 	fclose(f3);
	
	if(symtab_count!=0)
	{
		printf("\nSymbol Table");
		printf("\nSym_no\tSymbol\tSym_addr\n");
		for(i=0;i<symtab_count;i++)
		{
			printf("%s\t%s\t%s\n",symbol_table[i].sym_no,symbol_table[i].sym,symbol_table[i].sym_addr);
		}
	}
	if(littab_count!=0)
	{
		printf("\nLiteral Table");
		printf("\nLit_no\tLiteral\tLit_addr\n");
		for(i=0;i<littab_count;i++)
		{
			printf("%s\t%s\t%s\n",literal_table[i].lit_no,literal_table[i].lit,literal_table[i].lit_addr);
		}	
	}
	if(pooltab_count!=0)
	{
		printf("\nPool Table\nPoolTab Index\n");
		for(i=0;i<pooltab_count;i++)
		{
			printf("%d\n",pooltab[i]);
		}	
	}
	return 0;
}
