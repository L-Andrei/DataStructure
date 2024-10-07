#include <stdio.h>
#include <stdlib.h>

typedef enum {RED,BLACK} Color;

typedef struct Node{
    int v; 
    Color cor;
    struct Node *e; //Filho a esquerda
    struct Node *d; // Filho a direita
    struct Node *pai; // Pai do nó
    
}Node;

typedef struct treeRB{  
    Node *raiz;
    Node *nil; // Nó sentinela semlhante a um nó nulo
    int altura;
} treeRB;

Node* createNode(int v, Color cor, Node* nil){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->v = v; //inicializa o valor.
    newNode->cor = cor; //inicializa a cor
    newNode->e = newNode->d = newNode->pai = nil; // Faz todos os filhos e o pai apontarem para o nó nulo
    return newNode;
}

treeRB* crateTreeRB(){
    treeRB* newTree = (treeRB*)malloc(sizeof(treeRB));
    newTree->nil = (Node*)malloc(sizeof(Node)); // Nó nulo
    newTree->nil->cor = BLACK;  //Nos nulos tem são pretos, segundo a definição
    newTree->raiz = newTree->nil; //Faz a raiz ser nula
    newTree->altura = 0;
    return newTree;    
}

void leftRot(treeRB* t,Node* x){
    // Armazena o filho a direita de x em y
    Node* y = x->d;

    //A subárvore a esquerda de y se torna a filho a direita de x
    x->d = y->e; 

    // Se a nova subárvore esquerda de x não for o nó sentinela,
    // atualizamos o ponteiro do pai dessa subárvore para apontar para x
    if(x->e != t->nil){ 
        y->e->pai = x;
    }
    y->pai = x->pai; // Faz o pai de x virar pai de y

    if(x->pai == t->nil){ // Se x era raiz, atualizamos y para raiz
        t->raiz = y;
    }else if(x == x->pai->e){ // Se x era filho a esquerda, transofmamos y no filho a esquerda atual
        x->pai->e = y;
    }else{ // Se x era filho direito, agora y será filho direito
        x->pai->d = y;
    }

    y->e = x; // Faz o filho a esquerda de y virár x
    x->pai = y; // Faz o pai de x virar y
}

void rightRot(treeRB* t, Node* x){
    // Armazenamos o filho à esquerda de x em y
    Node* y = x->e;

    // A subárvore direita de y torna-se a subárvore esquerda de x
    x->e = y->d;

    // Se a nova subárvore direita de x não for o nó sentinela,
    // atualizamos o ponteiro do pai dessa subárvore para apontar para x
    if(x->d != t->nil){  
        y->d->pai = x; 
    }
    y->pai = x->pai; // Faz o pai de x virar pai de y

    if(x->pai == t->nil){// Se x era a raiz da árvore, atualizamos a raiz para y
        t->raiz = y;
    }else if( x == x->pai->d){ // Se x era o filho direito do seu pai, agora o filho direito de seu pai é y
        x->pai->d = y;
    }else{ // Se x era o filho esquerdo, agora o filho esquerdo será y
        x->pai->e = y;
    }

    y->d = x; // Agora fazemos o x virar o filho a direita de y
    x->pai = y; // Finalmente, atualizamos o pai de x para ser y
}

void fixTree(treeRB* t, Node* n) {
    // Se o nó é a raiz ou o pai de n é preto, não há nada a corrigir
    if (n == t->raiz || n->pai->cor == BLACK) {
        t->raiz->cor = BLACK; // Certifica-se de que a raiz é preta
        return;
    }

    // Se o pai de n for vermelho, precisamos corrigir
    if (n->pai == n->pai->pai->d) {
        
        Node* tio = n->pai->pai->e; // Se o pai de n for filho a direita, pega o filho a esquerda do avô de n.

        // Caso 1: O tio é vermelho, precisa recolorir
        if (tio->cor == RED) {
            n->pai->cor = BLACK; // Transforma o pai em preto
            tio->cor = BLACK; //Transforma o tio em preto
            n->pai->pai->cor = RED;

            fixTree(t, n->pai->pai); // Recursivamente vai arrumando os nós superiores
        } else {
            // Caso 2: Tio preto, faz rotações
            if (n == n->pai->e) {
                n = n->pai;
                rightRot(t, n); // Rotaciona à direita
            }
            n->pai->cor = BLACK;
            n->pai->pai->cor = RED;
            leftRot(t, n->pai->pai); // Rotaciona à esquerda o avô de n
        }
    } else {

        Node* tio = n->pai->pai->d; // Se o pai de n for filho a esquerda, pega o filho a direita do avô de n

        // Caso 1: O tio é vermelho, precisa recolorir
        if (tio->cor == RED) {
            n->pai->cor = BLACK; // Transforma o pai em preto
            tio->cor = BLACK; // tio também virá preto
            n->pai->pai->cor = RED; //Transforma o avô em vermelho
            
            fixTree(t, n->pai->pai); // Recursivamente vai arrumando os nós superiores
        } else {
            // Caso 2: Tio preto, faz rotações
            if (n == n->pai->d) {
                n = n->pai; // Obtem o pai de n
                leftRot(t, n); // Rotaciona à esquerda o pai de n
            }
            n->pai->cor = BLACK; // Tranforma o pai de n em preto
            n->pai->pai->cor = RED; //Transforma o avô em vermelho
            rightRot(t, n->pai->pai); // Rotaciona à direita
        }
    }   
}

void insertOnTree(treeRB* t, int v){
    Node* n = createNode(v,RED,t->nil); // Cria o nó que será inserido na árvore
    Node* r = t->raiz; // Obtem a raiz da árvore
    Node* nil = t->nil; // Obtem o nó sentinela

    while (r != t->nil){ //Percorre a árvore enquanto r não for nulo
        nil = r; // Armazena o nó atual.
        if(n->v < r->v){ // Se o valor do novo nó é menor que o atual
            r = r->e; // Entra na arvore a esquerda da atual
        } else{  // Se o valor do novo nó for maior que o atual
            r = r->d; // Entra na subarvore a direita
        }
    }

    n->pai = nil; // Transforma o nó anterior do novo nó em seu pai dele

    if(nil == t->nil){ // Se a sentinela for nula, mesmo depois do while anterior
        t->raiz = n; // O novo nó é raiz da árvore
        t->raiz->cor = BLACK; // A raiz sempre deve ser preta
    }else if(n->v < nil->v){ // Verifica se o valor do novo nó é menor do que seu pai
        nil->e = n; // Transforma o novo nó em filho a esquerda
    }else{
        nil->d = n; // Transforma novo nó em filho a direita de seu pai
    }
    
    fixTree(t,n); // arruma a árvore
}

void printEnOrder(Node* r, treeRB* t){
    if(r != t->nil){ //Enquanto o nó atual não for nulo percorre a árovre
    printEnOrder(r->e,t); // Percorre recursivamente a subárvore à esquerda
    printf(" %d",r->v); // Imprime o valor do nó atual
    printEnOrder(r->d,t); // Percorre recursivamente a subárvore à direita
    }
}

int countRed(Node* r, treeRB* t){
    if(r != t->nil){ // Verifica se o nó é nulo
        if(r->cor == RED){ // Se for vermelho soma +1 e faz a recursão para os filhos 
            return countRed(r->e,t) + countRed(r->d,t) + 1;
        }else{ // Se for preto apenas faz a recursão
            return countRed(r->e,t) + countRed(r->d,t);
        }
    }
    return 0;
}

int countBlack(Node* r, treeRB* t){
    if(r != t->nil){ // Verifica se o nó atual é nulo
        if(r->cor == BLACK){ // Se for preto soma +1 e faz a recursão para os filhos
            return countBlack(r->e,t) + countBlack(r->d,t) + 1;
        }else{ // Se for vermelho somente faz a recursão para os filhos
            return countBlack(r->e,t) + countBlack(r->d,t);
        }
    }

    return 0;
}

int calcAltura(Node* r, treeRB* t){
    if(r != t->nil){ // Se r não for nulo

        int alturaEsq = calcAltura(r->e,t); // Calcula recursivamente a altura da subárvore esquerda
        int alturaDir = calcAltura(r->d,t); // Calcula recursivamente a altura da subárvore direita

        if(alturaEsq > alturaDir){ // Verifica se a altura a esquerda é maior que a da direita
            return alturaEsq + 1; // Se for maior retorna altura esquerda +1
        }else{
            return alturaDir + 1 ; // Se a altura da direita for maior retorna ela +1
        }
    }
    return -1;
}

int main() {
    // Inicializa a árvore
    treeRB* t = crateTreeRB();
    int valores[13]; // Array para armazenar os valores
    
    // Coletar 13 números do usuário
    for (int i = 0; i < 13; i++) {
        scanf("%d", &valores[i]); // Ler o número e armazenar no array
    }

    // Inserir cada valor na árvore
    for (int i = 0; i < 13; i++) {
        insertOnTree(t, valores[i]); // Inserir na árvore
    }

    printf("Percurso em ordem:");
    printEnOrder(t->raiz, t);
    printf("\n");


    printf("Raiz: %d\n", t->raiz->v);


    int altura = calcAltura(t->raiz, t);
    printf("Altura: %d\n", altura);


    int nosVermelhos = countRed(t->raiz, t);
    printf("Quantidade de nós vermelhos: %d\n", nosVermelhos);


    int nosPretos = countBlack(t->raiz, t);
    printf("Quantidade de nós pretos: %d\n", nosPretos);

    free(t->nil);
    free(t);

    return 0;
}
