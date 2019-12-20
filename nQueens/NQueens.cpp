#include<iostream>
#include<cstdlib>
using namespace std;

int *x;			//Array where array is row no. and value is column no.
int n;			
long count=0;

bool place(int k,int i);
void write();

void nQueens(int k, int n){
	//Using Back-tracking this
	for(int i=0; i<n ; i++) {			//'i' stands for iteration of soln. and can also be thought of as 
							//calculating the position by moving a Queen across a row
		if(place(k,i)){				//if can be placed 
			x[k]=i;				//place a Queen at that column
			if(k==n-1)			//Iif last queen is placed
				write();		//print board
			else	
				nQueens(k+1,n);		//move to next Queen
		}
	}
}

bool place(int k,int i){				//See if Queen at k,i doesn't conflict with any Queens put before
	for(int j=0;j<k;j++){
		if((x[j]==i) || (abs(x[j]-i)==abs(j-k)))//If conflicts at Column or Diagonal, return false
			return false;
	}
	return true;
}

void write(){
	cout<<"========================================\n";
	for(int i=0 ; i<n ; i++){				//traverses row
		for(int j=0 ; j<n ; j++){			//traverses column values
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
