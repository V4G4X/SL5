#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;

int LC = 0;  //Location Counter
int PTP = 0; //Pooltab Pointer
int LTP = 0; //Literal Table Pointer
int STP = 0; //Symbol Table Pointer
int POOLTAB[1000];

typedef struct Symbol
{
	string name;
	int address;
	string size; //Also called length
} Symbol;

Symbol SYMTAB[100];
int checkSYMTAB(string name){
	for (int i = 0; i < STP; i++)
	{
		if (name.compare(SYMTAB[i].name) == 0)
			return i;
	}
	return -1;
}

typedef struct Literal
{
	string name;
	int address;
} Literal;

bool isLiteral(string name){
	char str[name.length()];
	strcpy(str,name.c_str());
	if(str[0]=='=')
		return true;
	return false;
}

Literal LITTAB[100];

int checkLITTAB(string name)
{
	for (int i = POOLTAB[PTP]; i < LTP; i++)
	{
		if (name.compare(LITTAB[i].name) == 0)
			return i;
	}
	return -1;
}

char REG[4][2][5] = {
	//REG[x][] is used for iteration,
	//REG[][0] ==> Register
	//REG[][1] ==> Code
	{"AREG","R01"},
	{"BREG","R02"},
	{"CREG","R03"},
	{"DREG","R04"}
};

char *getReg(string str)
{
	for (int i = 0; i < 4; i++)
		if (strcasecmp(REG[i][0], str.c_str()) == 0) //Register Code Match
			return REG[i][1];
	return NULL;
}

char MOT[13][6][6]={
//				0	  1    2    3    	  4 	  5
/*0*/		{"MULT"	,"03","IS","2"		,"2",	"-1"},
/*1*/		{"READ"	,"09","IS","2"		,"1",	"-1"},
/*2*/		{"MOVEM","05","IS","2"		,"2",	"3"},
/*3*/		{"SUB"	,"02","IS","2"		,"2",	"-1"},
/*4*/		{"BC"	,"07","IS","2"		,"1",	"5"},
/*5*/		{"STOP"	,"00","IS","2"		,"0",	"-1"},
/*6*/		{"DC"	,"01","DL","1"		,"1",	"-1"},
/*7*/		{"COMP"	,"06","IS","2"		,"2",	"10"},
/*8*/		{"ADD"	,"01","IS","2"		,"2",	"12"},
/*9*/		{"DS"	,"02","DL","SIZE"	,"1",	"-1"},
/*10*/		{"MOVER","04","IS","2"		,"2",	"-1"},
/*11*/		{"PRINT","10","IS","2"		,"1",	"-1"},
/*12*/		{"DIV"	,"08","IS","2"		,"2",	"-1"}
};
//MOT[][x] where x=0 for mnem.code , 1 for machine, 2 for class, 3 for length of IS, 4 for no. of operands

int getHash(string stri)
{
	char str[stri.length() + 1];
	strcpy(str, stri.c_str());
	int val = 0;
	for (int i = 0; i < stri.length(); i++)
		val += (str[i] - 64);
	val %= 13;
	val--;
	while (strcasecmp(MOT[val][0], str) != 0)
	{
		sscanf(MOT[val][5], "%d", &val);
		if (val == -1)
			break;
	}
	return val;
}
bool isImperative(string inst){
		char instr[3];
	int index = getHash(inst);
	if(index==-1)
		return false;
	strcpy(instr,MOT[index][2]);
	if(instr[0]=='I' && instr[1]=='S')
		return true;
	return false;
}


char POT[5][2][7] = {
	//POT[][0] = Pseudo mnem code
	//POT[][1] = intermediate machine code
	{"START"	,"01"},
	{"END"		,"02"},
	{"LTORG"	,"03"},
	{"ORIGIN"	,"04"},
	{"EQU"		,"05"}
};

int getAD(string stri){
	char str[stri.length()+1];
	strcpy(str,stri.c_str());
	for(int i=0 ; i<5 ;i++)
		if(strcasecmp(POT[i][0],str)==0)
			return i;
	return -1;
}

bool isDeclarative(string inst){
	char instr[3];
	int index = getHash(inst);
	if(index==-1)
		return false;
	strcpy(instr,MOT[index][2]);
	if(instr[0]=='D' && instr[1]=='L')
		return true;
	return false;
}

void compError(string str){
	cout<<"Compilation Error: "<<str<<endl;
}

int main(int argc,char** argv){
	if(argv[1]==NULL){
		compError("No Input File");						//If first word not START, exit
		return 0;
	}
	ifstream reader;
	ofstream fout;
	ofstream ad_fout;
	fout.open("Pass1_OutPut");
	ad_fout.open("AD_OutPut");
	reader.open(argv[1],ios::in);							//Open program for input
	string line;
	char c_line[line.length()+1];
	getline(reader,line);								//Read first line from program
	strcpy(c_line,line.c_str());
	char* start_tok = strtok(c_line," ,\t");
	if(strcasecmp(start_tok,"START")!=0){
		compError("InCorrect \"START\" in Program.");				//If first word not START, exit
		return 0;
	}
	int len=0;
	while(start_tok!=NULL){
		start_tok = strtok(NULL," ,\t");
		if(start_tok==NULL){
			LC=0;
			break;
		}
		if(++len==1){
			LC=atoi(start_tok);
			cout<<"LC Updated with "<<LC<<endl;
			break;
		}
		else{
			compError("InCorrect \"START\" in Program.");			//If START incorrect
			return 0;
		}
	}
	//New Tokenization Attempt
	while(!reader.eof()){								//Go till End of File
		string label,inst,op1,op2;
		getline(reader,line);							//Read line
		strcpy(c_line,line.c_str());
		if(reader.eof())							//If file ended leave loop
			break;
		//Create Tokens First	
		string line_tok[4];							//Define array of strings
		char *temp = strtok(c_line," ,\t");					//Tokenize the string
		line_tok[0] = temp;
		int len=1;								//Counter for no. of tokens
		while(temp!=NULL){
			temp=strtok(NULL," ,\t");
			if(temp==NULL)
				break;
			line_tok[len++] = temp;						//Add token to Array of tokens
		}
		if(len==4){
			label = line_tok[0];
			inst = line_tok[1];
			op1 = line_tok[2];
			op2 = line_tok[3];
		}
		else if(len==3){
			//If first token is a label/symbol
			if((checkSYMTAB(line_tok[0])>0) || (getHash(line_tok[0])<0 && getAD(line_tok[0])<0)){
				label = line_tok[0];
				inst = line_tok[1];
				op1 = line_tok[2];
			}
			else{
				inst = line_tok[0];
				op1 = line_tok[1];
				op2 = line_tok[2];
			}
		}
		else if(len==2){
			//If first token is a label/symbol
			if((checkSYMTAB(line_tok[0])>0) || (getHash(line_tok[0])<0 && getAD(line_tok[0])<0)){
				label = line_tok[0];
				inst = line_tok[1];
			}
			else{
				inst = line_tok[0];
				op1 = line_tok[1];
			}
		}
		else if(len==1){
			//If first token is a label/symbol
			if((checkSYMTAB(line_tok[0])>0) || (getHash(line_tok[0])<0 && getAD(line_tok[0])<0))
				label = line_tok[0];
			else
				inst = line_tok[0];
		}
		else{
			compError("Too many tokens on Line");
			return 0;
		}
		cout<<LC++<<"\t";
		//Tokenization Complete
		cout<<"Tokenization Complete\t"<<label<<"\t"<<inst<<"\t"<<op1<<"\t"<<op2<<endl;
		//label Handling Start
		if(label.compare("")!=0){						//if Label variable is not empty
			if(checkSYMTAB(label)>0){					//Symbol already encountered
				SYMTAB[checkSYMTAB(label)].address = LC;
			}
			else if(checkSYMTAB(label)==-1){			//Label doesn't exist in SYMTAB
				Symbol temp;
				temp.name = label;
				temp.address = LC;
				SYMTAB[STP++] = temp;
			}
		}
		//label Handling End
		// cout<<"Label above: "<<endl;
		//Instruction Handling Start
		if (inst.compare("LTORG")==0)
		{
		}
		else if (inst.compare("ORIGIN")==0)
		{
		}
		else if (inst.compare("EQU")==0)
		{
		}
		 if (isImperative(inst))
		{
			if(inst.compare("STOP")==0){
				cout<<"BreakPoint Here"<<endl;
			}
			// cout<<"Imperative Statement"<<endl;
			inst = MOT[getHash(inst)][1];
			inst = "(IS,"+inst+")";
			// cout<<"Inst updated as: "<<inst<<endl;
			//Check operands

			//Operand 1
			if(isLiteral(op1)){
				//Operand 1 is Literal
				// cout<<"Entered 'Is Literal' block"<<endl;
				if(checkLITTAB(op1)==-1){
					//Operand 1 does not exist in LITTAB
					Literal temp;
					temp.name = op1;
					LITTAB[LTP++] = temp;
					op1 = "(L" + to_string(LTP-1) + ")";
				}
				op1 = "(L" + to_string(checkLITTAB(op1)) + ")";
			}
			else if(getReg(op1)!=NULL){
				//If Operand 1 is a Register
				// cout<<"Entered 'Is Register' block"<<endl;
				op1 =  getReg(op1);
				// cout<<"Operand 1 is now: "<<op1<<endl;
			}
			//If not Literal or not Register then a Symbol
			else {
				if (checkSYMTAB(op1)==-1){
					//If Symbol doesn't exist in SYMTAB
					Symbol temp;
					temp.name = op1;
					SYMTAB[STP++] = temp;
				}
				else
					op2 = "(S" + to_string(checkSYMTAB(op2)) + ")";
			}
			//Operand 2
			if(isLiteral(op2)){
				//Operand 2 is Literal
				if(checkLITTAB(op2)==-1){
					//Operand 1 does not exist in LITTAB
					Literal temp;
					temp.name = op2;
					LITTAB[LTP++] = temp;
					op2 = "(L" + to_string(LTP-1) + ")";
				}
				else
					op2 = "(L" + to_string(checkLITTAB(op2)) + ")";
			}
			else if(getReg(op2)!=NULL){
				//If Operand 1 is a Register
				// cout<<"Entered 'Is Register' block"<<endl;
				op2 =  getReg(op2);
				// cout<<"Operand 1 is now: "<<op1<<endl;
			}
			//If not Literal or not Register then a Symbol
			else {
				if (checkSYMTAB(op2)==-1){
					//If Symbol doesn't exist in SYMTAB
					Symbol temp;
					temp.name = op2;
					SYMTAB[STP++] = temp;
				}
				op2 = "(S" + to_string(checkSYMTAB(op2)) + ")";
			}
			LC++;
		}
		else if (isDeclarative(inst))
		{
			LC--;
			Symbol temp = SYMTAB[checkSYMTAB(label)];
			temp.size = op1;
			string op_copy = op1.c_str();
			char csize[6];
			if(inst.compare("DC")==0){
				inst = "(DL,01)";
				op1.erase(0,1);
				op1.erase(op1.length()-1,op1.length());
				LC++;
			}
			else{
				inst = "(DL,02)";
				strcpy(csize,op1.c_str());
				LC+=atoi(csize);
			}
			int index = checkSYMTAB(label);
			if(index!=-1)
				SYMTAB[index] = temp;
			else
				compError("Sudden Label MisMatch");
			op1 = "(C,"+op_copy+")";
		}
		cout<<label<<"\t"<<inst<<"\t"<<op1<<"\t"<<op2<<endl;
		//label Handling End
		
	//Previous Tokenization Attempt
	/*
		string output;
		///////////////////////////////////////////////////////////////////////////////////////
		//Now Tokenizng statement
		char c_line[line.length()+1];
		strcpy(c_line,line.c_str());
		string line_tok[4];							//Define array of strings
		char *temp = strtok(c_line," ,\t");					//Tokenize the string
		line_tok[0] = temp;
		int len=1;								//Counter for no. of tokens
		while(temp!=NULL){
			temp=strtok(NULL," ,\t");
			if(temp==NULL)
				break;
			line_tok[len++] = temp;						//Add token to Array of tokens
		}
		// for(int i=0;i<len;i++)
			// cout<<line_tok[i]<<"\t";
		// cout<<"No. of Tokens in String is: "<<len<<". ";
		/////////////////////////////////////////////////////////////////////////////////////////
		//Now converting
		int pt=0;	//Keep track of which token of the line
		int index = getHash(line_tok[pt]);
		if(index==-1){						//Token not a part of MOT
			index = getAD(line_tok[pt]);
			if(index==-1){					//Token not a part of MOT either, i.e LABEL is present
				label = line_tok[pt];
				// cout<<"\t//"<<label<<" will be treated a as a label"<<endl;
				Symbol temp;
				int SYMindex = checkSYMTAB(label);
				if(SYMindex==-1){			//Does not Exist in SYMTAB
					//Code to add to SYMTAB
					cout<<label<<" is being added to SYMTAB"<<endl;
					temp = {label.c_str(),LC,""};
					SYMTAB[STP] = temp;
				}
				else{						//Exists in SYMTAB
					temp = SYMTAB[SYMindex];
					temp.address = LC;
				}

				if(++pt==len){
					compError("Only a symbol on a line?");
					return 0;
				}
				index = getHash(line_tok[pt]);
				if(index==-1){				//Token after symbol does not match MOT
					index = getAD(line_tok[pt]);
					if(index==-1){			//Token after symbol does not match ADT
						compError("Incorrect Instruction");
						return 0;
					}
					else{		//Second token is an AD Statement
						inst = line_tok[pt];
						int counter = atoi(MOT[index][4]);
						if (counter == len - pt -1)
						{
							if (counter == 2)
							{
								op1 = line_tok[pt + 1];
								op2 = line_tok[pt + 2];
							}
							else if (counter == 1)
							{
								op1 = line_tok[pt + 1];
							}
						}
						else
						{
							compError("Operator Lengths MisMatch");
							return 0;
						}
					}
				}
				else{			//Second token is a MOT Statement
					inst = line_tok[pt];
					int counter = atoi(MOT[index][4]);
					if (counter == len - pt - 1)
					{
						if (counter == 2)
						{
							op1 = line_tok[pt + 1];
							op2 = line_tok[pt + 2];
						}
						else if (counter == 1)
						{
							op1 = line_tok[pt + 1];
						}
					}
					else
					{
						compError("Operator Lengths MisMatch");
						return 0;
					}
				}
				SYMTAB[STP++] = temp;
				cout<<"SYMTAB is changed with "<<temp.name<<", "<<temp.address<<", "<<temp.size<<endl;
			}
			else{							//No Symbol and an AD Statement
				inst = line_tok[pt];
				if (len - pt - 1 == 1)
					op1 = line_tok[pt + 1];
				if (index == 1)
				{ //End Statement
					cout << "This is an END statement" << endl;
					// return 0;
				}
			}
		}
		else{								//No Symbol and a MOT Statement
			inst = line_tok[pt];
			int counter = atoi(MOT[index][4]);
			if (counter == len - 1)
			{
				if (counter == 2)
				{
					op1 = line_tok[pt + 1];
					op2 = line_tok[pt + 2];
				}
				else if (counter == 1)
				{
					op1 = line_tok[pt + 1];
				}
			}
			else
			{
				compError("Operator Lengths MisMatch");
				return 0;
			}
		}
		*/
		// Previous Tokenisation End
		//cout<<LC;
		//cout<<"\t"<<inst<<"\t"<<op1<<"\t"<<op2<<endl;
	}
	cout<<"Program wrapping UP\n";
	cout<<"Final Values: \n";
	cout<<"LC: "<<LC<<endl;
	cout<<"PTP: "<<PTP<<endl;
	cout<<"LTP: "<<LTP<<endl;
	cout<<"STP: "<<STP<<endl;
	// Write SYMBOL Table Start
	cout<<"Symbol Table Below"<<endl;
	for (int i = 0; i < STP; i++)
	{
		Symbol temp = SYMTAB[i];
		cout<<i<<"\t"<<temp.name<<"\t"<<temp.address<<"\t"<<temp.size<<endl;
	}
	cout<<"Literal Table Below"<<endl;
	for (int i = 0; i < LTP; i++)
	{
		Literal temp = LITTAB[i];
		cout<<i<<"\t"<<temp.name<<"\t"<<temp.address<<endl;
	}
	// Write SYMBOL Table End
	reader.close();
	fout.close();
	ad_fout.close();
	return 0;
}
