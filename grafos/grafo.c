#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int destino;
    struct Node* p;
} Node;

typedef struct Lista {
    Node* head;
} Lista;

typedef struct Grafo {
    int numVertices;
    Lista* adj;
} Grafo;

Node* CriarNo(int destino) {
    Node* newNo = (Node*)malloc(sizeof(Node));
    newNo->destino = destino;
    newNo->p = NULL;
    return newNo;
}

Grafo* criarGrafo(int vertices) {
    Grafo* newGrafo = (Grafo*)malloc(sizeof(Grafo));
    newGrafo->numVertices = vertices;
    newGrafo->adj = (Lista*)malloc(vertices * sizeof(Lista));

    for (int i = 0; i < vertices; i++) {
        newGrafo->adj[i].head = NULL;
    }

    return newGrafo;
}

void adicionaAresta(Grafo* g, int o, int d) {
    Node* n = CriarNo(d);
    n->p = g->adj[o].head;
    g->adj[o].head = n;

    Node* n2 = CriarNo(o);
    n2->p = g->adj[d].head;
    g->adj[d].head = n2;
}

void imprimirGrafo(Grafo* g) {
    for (int i = 0; i < g->numVertices; i++) {
        Node* aux = g->adj[i].head;
        printf("Vertice %d: ", i);
        while (aux) {
            printf("%d -> ", aux->destino);
            aux = aux->p;
        }
        printf("NULL\n");
    }
}

void removerAresta(Grafo* g, int o, int d) {
    Node* atual = g->adj[o].head;
    Node* temp = NULL;

    while (atual != NULL && atual->destino != d) {
        temp = atual;
        atual = atual->p;
    }
    if (atual != NULL) {
        if (temp == NULL) {
            g->adj[o].head = atual->p;
        } else {
            temp->p = atual->p;
        }
        free(atual);
    }

    atual = g->adj[d].head;
    temp = NULL;

    while (atual != NULL && atual->destino != o) {
        temp = atual;
        atual = atual->p;
    }
    if (atual != NULL) {
        if (temp == NULL) {
            g->adj[d].head = atual->p;
        } else {
            temp->p = atual->p;
        }
        free(atual);
    }
}

int main() {
    Grafo* grafo = criarGrafo(5);

    adicionaAresta(grafo, 0,1);
    adicionaAresta(grafo, 1, 2);
    adicionaAresta(grafo, 2, 3);
    adicionaAresta(grafo, 3, 4);

    imprimirGrafo(grafo);

    return 0;
}
