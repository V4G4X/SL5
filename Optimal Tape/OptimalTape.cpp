#include<iostream>
using namespace std;

void MergeSort(int arr[],int n){
    //Base Case
    if(n==1)
        return;
    if(n==2){
        if(arr[0]<=arr[1])
            return;
        else
        {
            int temp = arr[1];
            arr[1] = arr[0];
            arr[0] = temp;
        }
    }
    int arr1[n/2];
    for(int i=0 ; i<n/2; i++)
        arr1[i] = arr[i];
    int arr2[n-n/2];
    for(int i=n/2 ; i<n; i++)
        arr2[i-n/2] = arr[i];
    //First SubProblem
    MergeSort(arr1,n/2);
    //Second SubProblem
    MergeSort(arr2,n-n/2);
    //Combine arr1 and arar2 into arr
    int i=0,j=0,k=0;
    while(k<n){
        if((i<n/2) && j<(n-n/2)){
            if(arr1[i]<=arr2[j])
                arr[k++] = arr1[i++];
            else
            arr[k++] = arr2[j++];
        }
        else{
            while(i<n/2){
                arr[k++] = arr1[i++];
            }
            while(j<n-n/2){
                arr[k++] = arr2[j++];
            }
        }
    }
    return;
}

int main(int argc, char const *argv[])
{
    //Initialize Input
    //I.e No. of Tapes
    int T = 3;
    int Tape[T][1000];
    int TapePos[T];
    //No. of Programs
    int P = 5;
    //Length of Programs
    int prog[] = {67,23,87,12,89};
    //Sort the programs according to length
    MergeSort(prog,5);
    //Lay programs like laying cards
    int currCard = 0;
    for(int i=0 ; i < P ; i++){
        Tape[currCard][TapePos[currCard]] = prog[i];
        TapePos[currCard]++;
        currCard=(currCard+1)%T;
    }
    //Print Every Tape
    float aver=0.0;
    for(int i=0 ; i<T ; i++){
        float avg=0.0;
        for (int j = 0; j < TapePos[i]; j++){
            cout<<Tape[i][j]<<"\t";
            avg+=Tape[i][j];
        }
        cout<<endl;
        aver+=(avg/TapePos[i]);
    }
    aver/=T;
    cout<<"Retrieval Time is: "<<aver<<endl;
    return 0;
}
