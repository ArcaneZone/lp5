#include<bits/stdc++.h>
#include<omp.h>
using namespace std;

void bubbleSortSerial(int a[],int n){
    int i ,j;
    for(int i=0;i<n;i++){
        for(int j=0;j<n-i-1;j++){
            if(a[j]<a[j+1]){
                swap(a[j],a[j+1]);
            }
        }
    }
}

void bubbleSortParallel(int a[],int n){
    int i,j;
    #pragma omp parallel for private(i,j)
    for(int i=0;i<n;i++){
        for(int j=0;j<n-i-1;j++){
            if(a[j]<a[j+1]){
                swap(a[j],a[j+1]);
            }
        }
    }
}

int main(){
    int n;
    cout<<"Enter the no of elements : ";
    cin>>n;
    int arr[n];
    for(int i=0;i<n;i++){
        arr[i]=rand()%n;
    }
    cout<<"The elements are : ";
    for (int i=0;i<n;i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;

    double start= omp_get_wtime();
    bubbleSortSerial(arr,n);
    double end= omp_get_wtime();
    double serial_time =end-start;
    cout<<"the sorted array : "<< endl;
    for(int i=0;i<n;i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;
    cout<<"the execution time for serial bubble sort : "<<serial_time;
    cout<<endl;
    cout<<endl;

    start= omp_get_wtime();
    bubbleSortParallel(arr,n);
    end= omp_get_wtime();
    double parallel_time =end-start;
    cout<<"the sorted array : "<< endl;
    for(int i=0;i<n;i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;
    cout<<"the execution time for Parallel bubble sort : "<<parallel_time;
    cout<<endl;
    cout<<endl;

}