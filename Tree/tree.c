#include <stdlib.h>
#include <stdio.h>

typedef struct item {
    int v; //Valor
    struct item* d; // Próximo a direita.
    struct item* e; // Próximo a esquerda.
}item;

typedef struct tree{
    item* raiz;
    int size;
    int h;
}tree;

tree* initTree(){
    tree* newTree=malloc(sizeof(tree));
    newTree->raiz=NULL;
    return newTree;
}

item* initItem(){
    item* newItem=malloc(sizeof(item));
    newItem->v = 0;
    newItem->d = NULL;
    newItem->e = NULL;
    return newItem;
}

item* insereNaArvore(item *t, int v){
    if (!t){
        t = initItem();
        t->v = v;
    } else if(t->v > v){
        t->e = insereNaArvore(t->e,v);
    } else if(t->v < v){
        t->d = insereNaArvore(t->d,v);
    }
    return t;
}

int calculaAltura(item *r){
    if (!r){
        return 0;
    } else {

    int alturaEsquerda = calculaAltura(r->e);
    int alturaDireita = calculaAltura(r->d);

    if (alturaEsquerda > alturaDireita) {
        return alturaEsquerda + 1;
    } else {
        return alturaDireita + 1;
    }
}
}

item* buscarNaArvore(item* r, int v) {
    if (!r || r->v == v) {
        return r;
    }

    if (v < r->v) {
        return buscarNaArvore(r->e, v);
    }

    return buscarNaArvore(r->d, v);
}

void printTreeInOrder(item* raiz) {
    if (raiz == NULL) {
        return;
    }
    printTreeInOrder(raiz->e); // Percorre a subárvore esquerda
    printf("%d ", raiz->v);    // Imprime o valor do nó atual
    printTreeInOrder(raiz->d); // Percorre a subárvore direita
}

int main(){
    tree* a = initTree();
    a->raiz = insereNaArvore(a->raiz,10);
    a->raiz = insereNaArvore(a->raiz,1);
    a->raiz = insereNaArvore(a->raiz,18);
    printTreeInOrder(a->raiz);
    a->h = calculaAltura(a->raiz);
    printf("%d",a->h);
return 0;
}
