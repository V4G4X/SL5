#include<iostream>
#include<fstream>
#include<string>
using namespace std;

string trim(string str){
	while(true){				//Trimming from Front
		unsigned int i=0;
		char ch = str.at(i);
		if(ch=='\t' || ch==' '){
			str.erase(i,i+1);
			continue;
		}
		break;
	}
	while(true){				//Trimming from Behind
		unsigned int i=str.length()-1;
		char ch = str.at(i);
		if(ch=='\t' || ch==' '){
			str.erase(i);
			continue;
		}
		break;
	}
	return str;
}

int main(int argc, char** argv){
	ifstream reader;
	reader.open("input.ASM",ios::in);
	string line;
	while(!reader.eof()){
		getline(reader,line);
		if(reader.eof()) break;
		if(line.length()!=1){
			line=trim(line);
			cout<<line<<endl;
		}
	}
}
