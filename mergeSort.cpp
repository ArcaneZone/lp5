#include <bits/stdc++.h>
#include <omp.h>
using namespace std;
void merge(int a[], int left, int middle, int right){
    int i,j,k,n1,n2;
    n1 = middle - left +1;
    n2 = right - middle;

    int L[n1],R[n2];

    for(i=0;i<n1;i++){
        L[i] = a[left+i];
    }
    for(j=0;j<n2;j++){
        R[j] = a[middle+1+j];
    }

    i=0;
    j=0;
    k=left;

    while(i<n1 && j<n2){
        if(L[i]<=R[j]){
            a[k] = L[i];
            i++;
        }
        else{
            a[k] = R[j];
            j++;
        }
        k++;
    }

    while(i<n1){
        a[k] = L[i];
        i++;
        k++;
    }
    while(j<n2){
        a[k] = R[j];
        j++;
        k++;
    }
}

void MergeSortSerial(int a[],int left, int right){
    if(left<right){
        int middle = (left+right)/2;
        MergeSortSerial(a,left,middle);
        MergeSortSerial(a,middle+1,right);
        merge(a,left,middle,right);
    }
}

void MergeSortParallel(int a[],int left, int right){
    if(left<right){
        int middle = (left+right)/2;
        #pragma omp parallel sections num_threads(2)
        {
            #pragma omp section
            {
                MergeSortParallel(a,left,middle);
            }
             #pragma omp section
            {
                MergeSortParallel(a,middle+1,right);
            }        
            
        }
        merge(a,left,middle,right);
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
    MergeSortSerial(arr,0,n-1);
    double end= omp_get_wtime();
    double serial_time =end-start;
    cout<<"the sorted array : "<< endl;
    for(int i=0;i<n;i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;
    cout<<"the execution time for serial Merge Sort : "<<serial_time;
    cout<<endl;
    cout<<endl;

    start= omp_get_wtime();
    MergeSortParallel(arr,0,n-1);
    end= omp_get_wtime();
    double parallel_time =end-start;
    cout<<"the sorted array : "<< endl;
    for(int i=0;i<n;i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;
    cout<<"the execution time for Parallel Merge Sort : "<<parallel_time;
    cout<<endl;
    cout<<endl;

}