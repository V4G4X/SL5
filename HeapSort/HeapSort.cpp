#include<iostream>
using namespace std;

void swap(int arr[],int i1, int i2){
	int temp = arr[i1];
	arr[i1]=arr[i2];
	arr[i2]=temp;
}

int large(int arr[], int len ,int a,int b,int c){
	if((arr[a]>=arr[b] && arr[a]>=arr[c]))
		return a;
	if(arr[b]>=arr[a] && arr[b]>=arr[c])
		return b;
	else return c;
}

int heapify(int arr[] , int len , int i){
	//arr is array
	//len is length
	//i is index
	if(i>=len)
		return -1;
	int largest = large(arr,len,i,i*2+1,i*2+2);//largest contains the INDEX with the largest value
	if(i*2+1 < len && i*2+1==largest)
		swap(arr,largest,i*2+1);
	else if(i*2+2 < len && i*2+2==largest)
		swap(arr,largest,i*2+2);
	heapify(arr,len,2*i+1);
	heapify(arr,len,2*i+2);
}

void heapSort(int arr[],int len){
//	for(int i = len / 2 - 1; i >= 0; i--) 
		heapify(arr, len, 0); 
	
	for(int i=len-1;i>=0;i--){
		swap(arr,0,i);
		heapify(arr,len,0);
	}
}

void printArray(int arr[], int n) 
{ 
    for (int i=0; i<n; ++i) 
        cout << arr[i] << " "; 
    cout << "\n"; 
} 

int main(){
	cout<<"Input Array Size: ";
	int len;
	cin>>len;
	int arr[len];
	cout<<"Input Array: ";
	for(int i=0 ; i< len ; i++)
		cin>>arr[i];
	
	heapSort(arr, len);
	cout << "Sorted array is \n"; 
	printArray(arr, len); 	
	return 0;
}
