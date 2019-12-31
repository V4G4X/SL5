#include<iostream>
#include<fstream>
#include<string>
#include<cstring>
using namespace std;

char OPTAB[13][6][6]= {	
/*0*/		{"MULT"	,"03","IS","2"	,"2",	"-1"},
/*1*/		{"READ"	,"09","IS","2"	,"1",	"-1"},
/*2*/		{"MOVEM"	,"05","IS","2"	,"2",	"3"},
/*3*/		{"SUB"	,"02","IS","2"	,"2",	"-1"},
/*4*/		{"BC"		,"07","IS","2"	,"1",	"5"},
/*5*/		{"STOP"	,"00","IS","2"	,"0",	"-1"}, 
/*6*/		{"DC"		,"01","DL","1"	,"1",	"-1"},
/*7*/		{"COMP"	,"06","IS","2"	,"2",	"10"},
/*8*/		{"ADD"	,"01","IS","2"	,"2",	"12"},
/*9*/		{"DS"		,"02","DL","SIZE"	,"1",	"-1"},
/*10*/	{"MOVER"	,"04","IS","2"	,"2",	"-1"},
/*11*/	{"PRINT"	,"10","IS","2"	,"1",	"-1"},
/*12*/	{"DIV"	,"08","IS","2"	,"2",	"-1"}
};
//OPTAB[][x] where x=0 for mnem.code , 1 for machine, 2 for class, 3 for length of IS, 4 for no. of operands

int getHash(string stri){
	char str[stri.length()+1];
	strcpy(str,stri.c_str());
	int val = 0;
	for(int i=0 ; i<stri.length() ; i++)
		val+=(str[i]-64);
	val%=13;
	val--;	
	while(strcasecmp(OPTAB[val][0],str)!=0){
		sscanf(OPTAB[val][5],"%d",&val);
		if(val==-1)
			break;
	}
	return val;
}


char ADTAB[5][2][7] = {
	//ADTAB[][0] = mnem code
	//ADTAB[][1] = intermediate machine code
	{"START"	,"01"},
	{"END"	,"02"},
	{"LTORG"	,"03"},	
	{"ORIGIN"	,"04"},	
	{"EQU"	,"05"}	
};

void compError(string str){
	cout<<"Compilation Error: "<<str<<endl;
}

int main(int argc,char** argv){
	cout<<"Hash of ADD is :"<<getHash("ADD")<<endl;
	cout<<"Hash of COMP is :"<<getHash("COMP")<<endl;
	cout<<"Hash of PRINT is :"<<getHash("PRINT")<<endl;
	cout<<"Hash of STOP is :"<<getHash("STOP")<<endl;
	cout<<"Hash of MOVER is :"<<getHash("MOVER")<<endl;
	cout<<"Hash of HAHA is :"<<getHash("HAHA")<<endl;
	ifstream reader;
	reader.open(argv[1],ios::in);
	string line;
	char c_line[line.length()+1];
	getline(reader,line);
	strcpy(c_line,line.c_str());
	if(strcmp(c_line,"START")!=0){
		compError("No \"START\" in Program.");
		return 1;
	}
	while(!reader.eof()){
		getline(reader,line);
		if(reader.eof())
			break;
		char c_line[line.length()+1];
		strcpy(c_line,line.c_str());
		string line_tok[4];
		char *temp = strtok(c_line," ,\t");
		line_tok[0] = temp;
		short i=0;
		while(temp!=NULL){
			cout<<line_tok[i]<<"\t";
			temp=strtok(NULL," ,\t");
			if(temp==NULL)
				break;
			line_tok[++i] = temp;
		}
		cout<<endl;
	}
	reader.close();
	return 0;
}
