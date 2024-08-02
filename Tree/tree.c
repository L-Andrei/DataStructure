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

item* findMin(item* node) {
    while (node->e != NULL) {
        node = node->e;
    }
    return node;
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
    printf("%d \n", raiz->v);    // Imprime o valor do nó atual
    printTreeInOrder(raiz->d); // Percorre a subárvore direita
}

item* deleteNode(item* root, int v) {
    if (root == NULL) {
        return root; // Árvore vazia
    }
    
    // Se o valor a ser excluído for menor que o valor da raiz, procurar na subárvore esquerda
    if (v < root->v) {
        root->e = deleteNode(root->e, v);
    }
    // Se o valor a ser excluído for maior que o valor da raiz, procurar na subárvore direita
    else if (v > root->v) {
        root->d = deleteNode(root->d, v);
    } else {
        // Caso 1: Nó sem filhos (folha)
        if (root->e == NULL && root->d == NULL) {
            free(root);
            root = NULL;
        }
        // Caso 2: Nó com um único filho
        else if (root->e == NULL) {
            item* temp = root;
            root = root->d;
            free(temp);
        }
        else if (root->d == NULL) {
            item* temp = root;
            root = root->e;
            free(temp);
        }
        // Caso 3: Nó com dois filhos
        else {
            item* temp = findMin(root->d); // Encontrar o menor valor na subárvore direita
            root->v = temp->v; // Copiar o valor do nó
            root->d = deleteNode(root->d, temp->v); // Excluir o nó duplicado
        }
    }
    return root;
}

item* rotateRight(item* y) {
    item* x = y->e;
    item* T2 = x->d;
    
    x->d = y;
    y->e = T2;
    
    return x; // Nova raiz
}

item* rotateLeft(item* x) {
    item* y = x->d;
    item* T2 = y->e;
    
    y->e = x;
    x->d = T2;
    
    return y; // Nova raiz
}

// Função para encontrar um nó com o valor especificado
item* findNode(item* root, int v) {
    if (root == NULL || root->v == v) {
        return root;
    }
    
    if (v < root->v) {
        return findNode(root->e, v);
    } else {
        return findNode(root->d, v);
    }
}

// Função principal para rotacionar a árvore em relação ao nó com o valor especificado
item* rotateNode(item* root, int v, char direction) {
    item* node = findNode(root, v);
    
    if (node == NULL) {
        printf("Nó com valor %d não encontrado.\n", v);
        return root;
    }
    
    if (direction == 'L' || direction == 'l') {
        // Rotação à esquerda
        return rotateLeft(node);
    } else if (direction == 'R' || direction == 'r') {
        // Rotação à direita
        return rotateRight(node);
    } else {
        printf("Direção inválida. Use 'L' para esquerda ou 'R' para direita.\n");
        return root;
    }
}

// Função para atualizar a árvore após a rotação
item* rotateTree(item* root, int v, char direction) {
    if (root == NULL) {
        return root;
    }
    
    if (v < root->v) {
        root->e = rotateTree(root->e, v, direction);
    } else if (v > root->v) {
        root->d = rotateTree(root->d, v, direction);
    } else {
        if (direction == 'L' || direction == 'l') {
            return rotateLeft(root);
        } else if (direction == 'R' || direction == 'r') {
            return rotateRight(root);
        }
    }
    return root;
}


int main(){
    tree* a = initTree();
    a->raiz = insereNaArvore(a->raiz,10);
    a->raiz = insereNaArvore(a->raiz,5);
    a->raiz = insereNaArvore(a->raiz,15);
    a->raiz = insereNaArvore(a->raiz,4);
    a->raiz = insereNaArvore(a->raiz,6);
    a->raiz = insereNaArvore(a->raiz,14);
    a->raiz = insereNaArvore(a->raiz,16);
    a->h = calculaAltura(a->raiz);
    a->raiz = rotateTree(a->raiz,15,'r');
    printTreeInOrder(a->raiz);
return 0;
}
