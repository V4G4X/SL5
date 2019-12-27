#include<iostream>
#include<fstream>
#include<string>
#include<cstring>
using namespace std;

char OPTAB[13][5][6]= {	
{"STOP","00","IS","2","0"}, 
{"ADD","01","IS","2","2"},
{"SUB","02","IS","2","2"},
{"MULT","03","IS","2","2"},
{"MOVER","04","IS","2","2"},
{"MOVEM","05","IS","2","2"},
{"COMP","06","IS","2","2"},
{"BC","07","IS","2","1"},
{"DIV","08","IS","2","2"},
{"READ","09","IS","2","1"},
{"PRINT","10","IS","2","1"},
{"DC","01","DL","1","1"},
{"DS","02","DL","SIZE","1"}
};
//OPTAB[][x] where x=0 for mnem.code , 1 for machine, 2 for class, 3 for length of IS, 4 for no. of operands

char ADTAB[5][2][7] = {
	//ADTAB[][0] = mnem code
	//ADTAB[][1] = intermediate machine code
	{"START","01"},
	{"END","02"},
	{"LTORG","03"},	
	{"ORIGIN","04"},	
	{"EQU","05"},	
};

void Compilation_Error(string str){
	cout<<"Compilation Error: "<<str<<endl;
}

int main(int argc,char** argv){
	ifstream reader;
	reader.open(argv[1],ios::in);
	string line;
	char c_line[line.length()+1];
	getline(reader,line);
	strcpy(c_line,line.c_str());
	if(strcmp(c_line,"START")!=0){
		Compilation_Error("No \"START\" in Program.");
		return 1;
	}
	cout<<"=======================================1"<<endl;
	while(!reader.eof()){
		getline(reader,line);
		char c_line[line.length()+1];
		strcpy(c_line,line.c_str());
		string line_tok[4];
		char *temp = strtok(c_line," ,\t");
		line_tok[0] = temp;
		cout<<"=======================================2"<<endl;
		short i=0;
		while(temp!=NULL){
			cout<<line_tok[i]<<"\t";
			temp=strtok(NULL," ,\t");
			cout<<"======================================"<<(i+3)<<endl;
			line_tok[++i] = temp;
		}
		cout<<"======================================"<<endl;
		if(reader.eof())
			break;
		cout<<endl;
//		cout<<line2<<endl;
	}
	reader.close();
	return 0;
}
