#include <stdio.h>


void insetionSort(int a[],int n){
    
    int key,j;
    for (int i=1;i<n;i++){
        key = a[i];
        j=i-1;

        while (j>=0 && a[j]<key){
            a[j+1]=a[j];
            j=j-1;
            
        }
        a[j+1]=key;
    };
};

void printArray(int a[],int n){

    for(int t=0;t<n;t++){
        printf("%d ",a[t]);
    } 
    printf("\n");
};

int main(){

    int a[]={10,65,6,89,50,16,74,2};
    int n= sizeof(a)/sizeof(a[0]);
    int i;

    insetionSort(a,n);

    printArray(a,n);

    return 0;
};