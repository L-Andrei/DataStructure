#include <stdio.h>

void selectionsort(int arr[],int n){
    for(int i = 0; i < n-1; i++){
        int min = i;
        for(int j = i+1;j<n;j++){
            if(arr[j]<arr[min]){
                min = j;
            }
        }
        int aux = arr[min];
        arr[min] = arr[i];
        arr[i] = aux;
    }
}
void printArray(int arr[], int size) {
    int i;
    for (i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main(){
    int arr[] = { 5,2,9,7,3,4,6};
    int n = sizeof(arr)/sizeof(arr[0]);
    selectionsort(arr,n);
    printArray(arr,n);
    return 0;
}
