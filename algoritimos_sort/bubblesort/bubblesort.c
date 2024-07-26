#include <stdio.h>

void bubblesort(int arr[],int n){
    for(int i = 0 ; i < n - 1; i++){
        for(int j = 0; j < n - i -1; j++){
            if(arr[j]>arr[j+1]){
                int aux = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = aux;
            }
        }
    }
}
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main(){
    int arr[] = {-5,-6,5,9,7,10,-1};
    int n = sizeof(arr)/sizeof(arr[0]);
    bubblesort(arr,n);
    printArray(arr,n);
    return 0;
}
