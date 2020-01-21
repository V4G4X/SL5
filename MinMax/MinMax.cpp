#include<iostream>
using namespace std;

void divCon(int arr[],int len,int* min, int* max){
	//Base Case 1
	if(len==2){
		if(arr[0]<=arr[1]){
			*min = arr[0];
			*max=arr[1];
			return;
		}
		else{
			*max = arr[0];
			*min=arr[1];
			return;
		}
	}
	//Base Case 2
	else if(len==1){
		*min = arr[0];
		*max= arr[0];
		return;
	}
	//General Case
	//Divide the array to first half
	int *arr1 = new int[len/2];
	for(int i=0 ; i<len/2 ; i++)
		arr1[i] = arr[i];
	//Divide the array to second half
	int *arr2 = new int[len-len/2];
	for(int i=len/2 ; i<len ; i++)
		arr2[i-len/2] = arr[i];
	int *min1 = new int;
	int *max1 = new int;
	divCon(arr1,len/2,min1,max1);
	int *min2 = new int;
	int *max2 = new int;
	divCon(arr2,len-len/2,min2,max2);
	//Combine Results of Both Calls
	if(*min1<=*min2)
		*min=*min1;
	else
		*min=*min2;
	if(*max1>*max2)
		*max=*max1;
	else
		*max=*max2;
}

int main(){
	int arr[] = {67,54,4,55,3,5,6,7,8,23,243,54,-567,43,-34};
	int len = 15;
	int *min= new int;
	int *max= new int;
	divCon(arr,len,min,max);
	cout<<"Min is : "<<*min<<endl;
	cout<<"Max is : "<<*max<<endl;
	return 0;
}



	
