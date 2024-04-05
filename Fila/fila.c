#include <stdlib.h>
#include <stdio.h>

typedef struct item {
    int valor; //Value.
    struct item* proximo; // Item that entered in queue before.
    struct item* anterior; // Item that will enter in queue after.
}item;

typedef struct queue{
    item* head; // First of queue.
    item* tail; // Last of queue.
    int size; // Size of queue.
}queue;

queue* initqueue(){ 
    // Initializing a queue.
    queue* newqueue=malloc(sizeof(queue)); // alloc memory for object.
    newqueue->head=0;
    newqueue->tail=0;
    return newqueue;
};

item* initItem(){
    // Initializing one item.
    item* newItem=malloc(sizeof(item)); // alloc memory for object.
    newItem->valor=0;
    newItem->proximo=0;
    newItem->anterior=0;
    return newItem;
};

void deleteFila(queue** fila){ 
    free(*fila);
};

void esvaziaFila(queue** fila){

    item* aux=(*fila)->head;
    while(aux!= 0){

        item* temp= aux->anterior;
        free(aux);
        aux=temp;
    }
    (*fila)->head = 0;
    (*fila)->tail = 0;       
    (*fila)->size = 0;
};

void entraNaFila(queue** fila, int valor )
{
    item* newItem = initItem();
    item* aux = initItem();
    newItem->valor = valor;
    if((*fila)->head==NULL){ // Add new item if queue is empty.
        (*fila)->head=newItem;
        (*fila)->tail=newItem;
        (*fila)->size++;
    }else if((*fila)->size == 1){ // Add new item if queue have one item.
        newItem->proximo=(*fila)->head;
        aux=(*fila)->head;
        aux->anterior=newItem;
        (*fila)->tail=newItem;
        (*fila)->size++;
    } else{ // Add new item if queue have more than two items.
        newItem->proximo=(*fila)->tail;
        aux = (*fila)->tail;
        aux->anterior = newItem;
        (*fila)->tail = newItem;
        (*fila)->size++;
    }
};

void retiraDaFila(queue** fila){
    item* aux = initItem();
    item* aux2 = initItem();
    aux = (*fila)->head;
    (*fila)->head=aux->anterior;
    free(aux);
    aux2 = (*fila)->head;
    aux2->proximo=0;
    (*fila)->size--;
};

void encontraNaFila(const queue** fila,int valor){
    item* aux=initItem();
    aux = (*fila)->head;
    for (int i = 1; i <= ((*fila)->size); i++)
    {
        if (aux->valor == valor)
        {
            printf("The value %d on in %dº position.\n",valor,(i));
            break;
        };
        aux = aux->anterior;
    }
    
};

void imprimeFila(const queue** fila){
    item* aux=initItem();
    aux = (*fila)->head;
    for (int i = 0; i < ((*fila)->size); i++)
    {
        printf("Value: %d | Position: %d \n",aux->valor,(i+1));
        aux = aux->anterior;
    }
};

void main(){

    queue* fila=initqueue();
    entraNaFila(&fila,1);
    entraNaFila(&fila,2);
    entraNaFila(&fila,3);
    imprimeFila(&fila);
    retiraDaFila(&fila);
    imprimeFila(&fila);
    encontraNaFila(&fila,3);
    esvaziaFila(&fila);
    deleteFila(&fila);
    printf("queuea esvaziada");
};