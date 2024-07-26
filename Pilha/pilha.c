#include <stdlib.h>
#include <stdio.h>

typedef struct item {
    int valor; //Valor
    struct item* proximo; // Próximo
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
}

item* initItem(){
    item* newItem=malloc(sizeof(item));
    newItem->valor=0;
    newItem->proximo=0;
    return newItem;
}

void deleteList(list** lista){ 
    free(*lista);
}

void esvaziaLista(list** lista){

    item* itemAtual=(*lista)->head;
    while(itemAtual!= 0){
        //declara uma variavel temporaria que recebe itemAtual.proximo
        item* temp= itemAtual->proximo;
        free(itemAtual);
        itemAtual=temp;
    }
    (*lista)->head = 0;
    (*lista)->tail = 0;        //declara uma variavel temporaria que recebe itemAtual.proximo
    (*lista)->size = 0;
}


void pushItem(list** lista, int valor ){
    //iniciou
    item* newItem=initItem();
    newItem->valor=valor;
    //se a lista for vazia 
    if((*lista)->head ==  NULL){
        //automaticamente ele aponta para alguma coisa, minha cabeça, e o final da lista recebe o primeiro item
        (*lista)->head=newItem;
        (*lista)->tail=newItem;
        (*lista)->size++;
    }else{
        newItem->proximo=(*lista)->tail;
        (*lista)->tail=newItem;
        (*lista)->size++;
    }    
}


void printList(const list* list){
    //if(){
    item* item=list->tail;
    while (item != NULL)
    {
        printf("%d\n",item->valor);
        item=item->proximo;
    }
    printf("Final da lista \n") ;
}

int main(){
    list* lista=initList();
    pushItem(&lista,1);
    pushItem(&lista,2);
    pushItem(&lista,3);
    printList(lista);
    esvaziaLista(&lista);
    printList(lista);
    deleteList(&lista);
    return 0;
}

