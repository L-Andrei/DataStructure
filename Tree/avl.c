#include <stdio.h>
#include <stdlib.h>

typedef Node*{
    int v;
    struct *e, *d, *pai;
    int h; // altura
}Node;

typedef Tree*{
    Node *r;
}tree;

Node* createNode(int v){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->v = v;
    newNode->e = newNode->d = newNode->pai = NULL;
    newNode->h = 1;
    return newNode;
}

Tree* createTree(){
    Tree* tree = (Tree*)malloc(sizeof(Tree));
    tree->r = NULL;
    return tree;
}

int max(int a, int b){
    return (a>b)?a:b;
}

int altura(Node* n){
    if(n == NULL){
        return 0;
    }
    return N->h;
}

int balanceamento(Node* n){
    if(n==NULL){
        return 0;
    }
    return altura(n->e) - altura(n->d);
}

void insertOnTree(Tree* t, int v){
    Node* n = createNode(v);
    Node* temp = t->r;


}

Node* leftRot(Node* n){
    Node* x = n->e;
    Node* t2 = x->d;

    x->d = n;
    n->e = t2;

    n->h = max(altura(n->e),altura(n->d)) +1;
    x->h = max(altura(x->e),altura(x->d)) +1;

    return x;
}

Node* rightRot(Node* n){
    Node* x = n->d;
    Node* t2 = x->e;

    x->e = n;
    n->d = t2;

    n->h = max(altura(n->e),altura(n->d)) +1;
    x->h = max(altura(x->e),altura(x->d)) +1;

    return x;
}

Node* insertOnTree(Node* n, int v){

    if(n == NULL){
        return createNode(v);
    }

    if(v < n->v){
        n->e = insertOnTree(n->e,v);
    }else if(v > n->v){
        n->d = insertOnTree(n->d,v);
    }else{
        return n;
    }

    n->altura = 1 + max(altura(n->e),altura(n->e));
    int balanco = balanceamento(n);

    if(balanco > 1 && v < n->e->v){
        return rightRot(n);
    }

    if(balanco < -1 && v > n->d->v){
        return rightRot(n);
    }

    if(balanco > 1 && v > n->e->v){
        n->e = leftRot(n->e);
        return rightRot(n);
    }

    if(balanco < 1 && v < n->d->v){
        n->d = rightRot(n->d);
        return leftRot(n);
    }

    return node;
}

void printInOrder(Node* raiz){
    if(root != NULL){
        printInOrder(raiz->e);
        print("%d",raiz->v);
        printInOrder(raiz->d);
    }
}

void printPostOrder(Node* raiz){
    if(raiz != NULL){
        printPostOrder(raiz->e);
        printPostOrder(raiz->d);
        print("%d",raiz->v);
    }
}

void printPreOrder(Node* raiz){
    if(raiz != NULL){
        print("%d",raiz->v);
        printPreOrder(n->e);
        printPreOrder(n->d);
    }
}

Node* sarchOnTree(Node* raiz, int v){
    while (raiz->v != v){
        if(raiz->v > v){
            raiz = raiz->e;
        }else{
            raiz = raiz->d;
        }
    }
    return raiz;
}