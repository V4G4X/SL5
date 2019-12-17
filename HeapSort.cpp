#include<iostream>
using namespace std;

int largest(int a,int b,int c){
	if(arr[a]>=arr[b] && arr[a]>=arr[c])
		return a;
	if(arr[b]>=arr[a] && arr[b]>=arr[c])
		return b;
	else return c;
}

int heapify(int arr[] , int len , int i){
	//arr is array
	//len is length
	//i is index
	int large = largest(i,i*2+1,i*2+2);

}

int main(){
	cout<<"Input Array Size: ";
	int len;
	cin>>len;
	int arr[len];
	cout<<"Input Array: ";
	for(int i=0 ; i< len ; i++)
		cin>>arr[i];
	
	return 0;
}
