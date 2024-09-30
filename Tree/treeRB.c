#include <stdio.h>
#include <stdlib.h>

typedef enum {RED,BLACK} color;

typedef struct Node{
    int v;
    Color cor;
    struct *e,*d,*pai;
    
}Node;

typedef struct treeRB{
    struct *raiz;
    struct *nil;
    int altura;
} treeRB;

Node* createNode(int v, Color cor, Node* nil){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->v = v;
    newNode->cor = cor;
    newNode->e = newNode->d = newNode->pai = nil; 
    return newNode;
}

treeRB* crateTreeRB(){
    treeRb* newTree = (treeRB*)malloc(sizeof(tree));
    newTree->nil = (Node*)malloc(sizeof(Node));
    newTree->nil->cor = BLACK;
    newTree->raiz = newTree->nil;
    return newTree;    
}

void leftRot(treeRB* t,Node* x){
    Node* y = x->d;
    x->d = y->e;

    if(x->e != t->nil){ // Verifica se x possui filho a esquerda para rotacionar.
        y->e->pai = x;
    }
    y->pai = x->pai;

    if(x->pai == t->nil){ //Verifica se o x é a raiz.
        t->raiz = y;
    }else if(x == x->pai->e){ //Verifica se o x é o filho a esquerda do pai.
        x->pai->e = y;
    }else{
        x->pai->d = y;
    }

    y->e = x;
    x->pai = y;
}

void rightRot(treeRB* t, Node* x){
    Node* y = x->e;
    x->e = y->d;

    if(x->d != t->nill){
       y->d->pai = x; 
    }
    y->pai = x->pai;

    if(x->pai == t->nil){
        t->raiz = y;
    }else if( x == x->pai->d){
        x->pai->d = y;
    }else{
        x->pai->e = y;
    }
    
    y->d = x;
    x->pai = y;
}

void insertOnTree(treeRB* t, int v){
    Node* n = createNode(v,RED,t->nil);
    Node* r = t->raiz;
    Node* nil = t->nil;

    while (r != tree->nil){
        nil = r;
        if(n->v < r->v){
            r = r->e;
        } else{
            r = r->d;
        }
    }

    n->pai = nil;

    if(nil == t->nil){
        t->r = n;
    }else if(n->v < nil->v){
        nil->e = n;
    }else{
        nil->d = n;
    }

    n->e = n->d = tree->nill;
    fixTree(t,n);
}

void fixTree(treeRB* t, Node* n){
    while(n->pai->cor == RED){
        if(n->pai == n->pai->pai->d){
            Node* temp = z->pai->pai->d;
            if(temp->cor == RED){
                n->pai->cor = BLACK;
                temp->cor = BLACK;
                n->pai->pai->cor=RED;
                n = n->pai->pai;
            }else{
                if(n == n->pai->d){
                    n = n->pai;
                    leftRot(t,n);
                }
                n->pai->cor = BLACK;
                n->pai->pai->cor = BLACK;
                rightRot(t,n); 
            }
        }else{
            Node* temp = n->pai->pai->e;
            if(temp->cor == RED){
                n->pai->cor = BLACK;
                temp->cor = BLACK;
                n->pai->pai->cor=RED;
                n = n->pai->pai;
            }else{
                if(n == n->pai->e){
                    n = n->pai;
                    leftRot(t,n);
                }
                n->pai->cor = BLACK;
                n->pai->pai->cor = BLACK;
                rightRot(t,n); 
            }
        }
    }
    t->raiz->cor = BLACK;
}

void printEnOrder(Node* r, treeRB* t){
    if(r != t->nil){
    printEnOrder(n->e,t);
    printf("%d",n->v);
    printEnOrder(e->d,t);
    }
}

int countRed(Node* r, treeRB* t){
    if(r != t->nil){
        if(r->cor == RED){
            return countRed(n->e,t) + countRed(n->d,t) + 1;
        }else{
            return countRed(n->e,t) + countRed(n->d,t) + 1;
        }
    }
    return 0
}

int countBlack(Node r*, treeRB* t){
    if(r != t->nil){
        if(r->cor == BLACK){
            return countBlack(n->e,t) + countBlack(n->d,t) + 1;
        }else{
            return countBlack(n->e,t) + countBlack(n->d,t);
        }
    }

    return 0;
}

int calcAltura(Node* r, treeRB* t){
    if(r != t->nil){

        int alturaEsq = calcAltura(r->e,t);
        int alturaDir = calcAltura(r->d,t);

        if(alturaEsq > alturaDir){
            return alturaEsq + 1;
        }else{
            return alturaDir + 1 ;
        }
    }
    return 0;
}


int main(){

    return 0;
}
