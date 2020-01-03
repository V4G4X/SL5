#include<iostream>
#include<fstream>
#include<string>
#include<cstring>
using namespace std;

int LC=0;	//Location Counter
int PTP=0;	//Pooltab Pointer
int LTP=0;	//Location Table Pointer
int STP=0;	//Symbol Table Pointer
int POOLTAB=0;

char REG[4][2][5] = {
	//REG[x][] is used for iteration,
	//REG[][0] ==> Register
	//REG[][1] ==> Code
	{"AREG","R01"},
	{"BREG","R02"},
	{"CREG","R03"},
	{"DREG","R04"}
};
char* getReg(string str){
	for(int i=0 ; i<4 ; i++)
		if(strcasecmp(REG[i][0],str.c_str())==0)//Register Code Match
			return REG[i][1];
	return NULL;
}

char MOT[13][6][6]= {	
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

int getHash(string stri){
	char str[stri.length()+1];
	strcpy(str,stri.c_str());
	int val = 0;
	for(int i=0 ; i<stri.length() ; i++)
		val+=(str[i]-64);
	val%=13;
	val--;	
	while(strcasecmp(MOT[val][0],str)!=0){
		sscanf(MOT[val][5],"%d",&val);
		if(val==-1)
			break;
	}
	return val;
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

void compError(string str){
	cout<<"Compilation Error: "<<str<<endl;
}

int main(int argc,char** argv){
	ifstream reader;
	reader.open(argv[1],ios::in);							//Open program for input
	string line;
	char c_line[line.length()+1];
	getline(reader,line);								//Read first line from program
	strcpy(c_line,line.c_str());
	char* start_tok = strtok(c_line," ,\t");
	if(strcasecmp(start_tok,"START")!=0){		
		compError("InCorrect \"START\" in Program.");				//If first word not START, exit
		return 1;
	}
	int len=0;
	while(start_tok!=NULL){
		start_tok = strtok(NULL," ,\t")	;
		if(start_tok==NULL && len!=0){
			break;
		}
		if(++len==1){
			sscanf(start_tok,"%d",&LC);
			cout<<"LC Updated with "<<LC<<endl;
		}
		else{
			compError("InCorrect \"START\" in Program.");			//If START incorrect
			return 1;
		}
	}
	while(!reader.eof()){								//Go till End of File
		getline(reader,line);							//Read line
		if(reader.eof())							//If file ended leave loop
			break;
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
		for(int i=0;i<len;i++)
			cout<<line_tok[i]<<"\t";
		cout<<"No. of Tokens in String is: "<<len<<endl;
		/////////////////////////////////////////////////////////////////////////////////////////
	}
	reader.close();
	return 0;
}
