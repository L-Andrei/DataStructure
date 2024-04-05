#include <stdlib.h>
#include <stdio.h>

typedef struct item {
    int valor; 
    struct item* proximo; 
    struct item* anterior;
}item;

typedef struct list{
    item* head;
    item* tail;
    int size;
}list;

list* initList(){
    list* newList=malloc(sizeof(list));
    newList->head=0;
    newList->tail=0;
    return newList;
};

item* initItem(){
    item* newItem=malloc(sizeof(item));
    newItem->valor=0;
    newItem->proximo=0;
    newItem->anterior=0;
    return newItem;
};

void deleteFila(list** fila){ 
    free(*fila);
};

void esvaziaFila(list** fila){

    item* itemAtual=(*fila)->head;
    while(itemAtual!= 0){

        item* temp= itemAtual->anterior;
        free(itemAtual);
        itemAtual=temp;
    }
    (*fila)->head = 0;
    (*fila)->tail = 0;       
    (*fila)->size = 0;
};

void entraNaFila(list** fila, int valor )
{
    item* newItem = initItem();
    item* aux = initItem();
    newItem->valor = valor;
    if((*fila)->head==NULL){
        (*fila)->head=newItem;
        (*fila)->tail=newItem;
        (*fila)->size++;
    }else if((*fila)->size == 1){
        newItem->proximo=(*fila)->head;
        aux=(*fila)->head;
        aux->anterior=newItem;
        (*fila)->tail=newItem;
        (*fila)->size++;
    } else{
        newItem->proximo=(*fila)->tail;
        aux = (*fila)->tail;
        aux->anterior = newItem;
        (*fila)->tail = newItem;
        (*fila)->size++;
    }
};

void retiraDaFila(list** fila){
    item* aux = initItem();
    item* aux2 = initItem();
    aux = (*fila)->head;
    (*fila)->head=aux->anterior;
    free(aux);
    aux2 = (*fila)->head;
    aux2->proximo=0;
    (*fila)->size--;
};

void encontraNaFila(const list** fila,int valor){
    item* aux=initItem();
    aux = (*fila)->head;
    for (int i = 1; i <= ((*fila)->size); i++)
    {
        if (aux->valor == valor)
        {
            printf("O valor %d esta na %dº posição.\n",valor,(i));
            break;
        };
        aux = aux->anterior;
    }
    
};

void imprimeFila(const list** fila){
    item* aux=initItem();
    aux = (*fila)->head;
    for (int i = 0; i < ((*fila)->size); i++)
    {
        printf("Valor: %d | Posição: %d \n",aux->valor,(i+1));
        aux = aux->anterior;
    }
};

void main(){

    list* fila=initList();
    entraNaFila(&fila,1);
    entraNaFila(&fila,2);
    entraNaFila(&fila,3);
    imprimeFila(&fila);
    retiraDaFila(&fila);
    imprimeFila(&fila);
    encontraNaFila(&fila,3);
    esvaziaFila(&fila);
    deleteFila(&fila);
    printf("lista esvaziada");
};