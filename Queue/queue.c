#include <stdlib.h>
#include <stdio.h>

typedef struct item {
    int value; //Value.
    struct item* next; // Item that entered in queue before.
    struct item* previous; // Item that will enter in queue after.
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
    newItem->value=0;
    newItem->next=0;
    newItem->previous=0;
    return newItem;
};

void deletQueue(queue** queue){ 
    free(*queue);
};

void cleanQueue(queue** queue){

    item* aux=(*queue)->head;
    while(aux!= 0){

        item* temp= aux->previous;
        free(aux);
        aux=temp;
    }
    (*queue)->head = 0;
    (*queue)->tail = 0;       
    (*queue)->size = 0;
};

void insertInQueue(queue** queue, int value )
{
    item* newItem = initItem();
    item* aux = initItem();
    newItem->value = value;
    if((*queue)->head==NULL){ // Add new item if queue is empty.
        (*queue)->head=newItem;
        (*queue)->tail=newItem;
        (*queue)->size++;
    }else if((*queue)->size == 1){ // Add new item if queue have one item.
        newItem->next=(*queue)->head;
        aux=(*queue)->head;
        aux->previous=newItem;
        (*queue)->tail=newItem;
        (*queue)->size++;
    } else{ // Add new item if queue have more than two items.
        newItem->next=(*queue)->tail;
        aux = (*queue)->tail;
        aux->previous = newItem;
        (*queue)->tail = newItem;
        (*queue)->size++;
    }
};

void removeFromQueue(queue** queue){
    item* aux = initItem();
    item* aux2 = initItem();
    aux = (*queue)->head;
    (*queue)->head=aux->previous;
    free(aux);
    aux2 = (*queue)->head;
    aux2->next=0;
    (*queue)->size--;
};

void SearchAtQueue(const queue** queue,int value){
    item* aux=initItem();
    aux = (*queue)->head;
    for (int i = 1; i <= ((*queue)->size); i++)
    {
        if (aux->value == value)
        {
            printf("The value %d on in %dº position.\n",value,(i));
            break;
        };
        aux = aux->previous;
    }
    
};

void printQueue(const queue** queue){
    item* aux=initItem();
    aux = (*queue)->head;
    for (int i = 0; i < ((*queue)->size); i++)
    {
        printf("Value: %d | Position: %d \n",aux->value,(i+1));
        aux = aux->previous;
    }
};

void main(){

    queue* queue=initqueue();
    insertInQueue(&queue,1);
    insertInQueue(&queue,2);
    insertInQueue(&queue,3);
    printQueue(&queue);
    removeFromQueue(&queue);
    printQueue(&queue);
    SearchOnQueue(&queue,3);
    cleanQueue(&queue);
    deletQueue(&queue);
    printf("Queue cleaned");
};