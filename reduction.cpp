#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

int min(int arr[],int n){
    int min_val=arr[0];
    #pragma omp parallel for reduction(min:min_val)
    for(int i=0;i<n;i++){
        if(arr[i]<min_val){
            min_val=arr[i];
        }
    }
    return min_val;
}

int max(int arr[],int n){
    int max_val=arr[0];
    #pragma omp parallel for reduction(max:max_val)
    for(int i=0;i<n;i++){
        if(arr[i]>max_val)
        max_val=arr[i];
    }
    return max_val;
}
int sum(int arr[],int n){
    int sum_val=arr[0];
    #pragma omp parallel for reduction(sum:sum_val)
    for(int i=0;i<n;i++){
        sum_val+=arr[i];
    }
    return sum_val;
}
int avg(int arr[],int n){
    int sum_val=arr[0];
    #pragma omp parallel for reduction(avg:sum_val)
    for(int i=0;i<n;i++){
        sum_val+=arr[i];
    }
    return sum_val/n;
}

int main(){
    int n;
    cout<<"enter the no. of elements";
    cin>>n;
    int arr[n];
    for(int i=0;i<n;i++){
        arr[i]=rand()%n;
    }
    for (int i = 0; i < n; i++)
    {
        cout<<arr[i]<<" ";
    }
    cout<<endl;

    cout<<max(arr,n)<<endl;
    cout<<min(arr,n)<<endl;
    cout<<sum(arr,n)<<endl;
    cout<<avg(arr,n)<<endl;

}