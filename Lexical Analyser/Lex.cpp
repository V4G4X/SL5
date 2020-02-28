#include <iostream>
#include <string.h>
#include <string>
#include <fstream>
using namespace std;

int main(int argc, char const *argv[])
{
	ofstream identifier("Identifier");
	ofstream literal("Literal");
	ifstream reader(argv[1]);
	char* token = new char[1000];
	int tok_pos=0;
	char prev_token[1000];
	int prev_pos=0;
	char in;
	while(reader.get(in)){
		if(in==reader.eof())	break;
		cout<<in;
		token[tok_pos++] = in;
		ifstream terminal("Terminal");
		while(!terminal.eof()){
			char line[15];
			terminal.getline(line,15);
			string stLine = line;
			stLine = stLine.substr(4,strlen(line)-4);
			if(strcmp(token,stLine.c_str())==0){
				cout<<endl<<"Literal Found:"<<token<<endl;
				token = new char[1000];
				tok_pos=0;
				break;
			}
		}
		terminal.close();
	}
	cout<<endl;
	return 0;
}