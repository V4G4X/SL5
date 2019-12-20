#include<iostream>
#include<cstdlib>
using namespace std;

int *x;
int n;
long count=0;

bool place(int k,int i);
void write();

void nQueens(int k, int n){
	//Using Back-tracking this
	for(int i=0; i<n ; i++) {
		if(place(k,i)){
			x[k]=i;
			if(k==n-1)
				write();
			else
				nQueens(k+1,n);
		}
	}
}

bool place(int k,int i){
	for(int j=0;j<k;j++){
		if((x[j]==i) || (abs(x[j]-i)==abs(j-k)))
			return false;
	}
	return true;
}

void write(){
	cout<<"========================================\n";
	for(int i=0 ; i<n ; i++){				//print row
		for(int j=0 ; j<n ; j++){			//print column values
			if(j==x[i]){
				cout<<"1";			
			}
			else
				cout<<0;
		}
		cout<<"\n";
	}
	count++;
}

int main(){
	cout<<"Enter No of Queens: ";
	cin>>n;
	x=new int[n];
	nQueens(0,n);
	cout<<"No. of Solutions are "<<count<<endl;
	return 0;
}
