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

typedef struct Fila {
    int* itens;
    int frente, tras, tamanho, capacidade;
} Fila;


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

Fila* criarFila(int capacidade) {
    Fila* fila = (Fila*)malloc(sizeof(Fila));
    fila->capacidade = capacidade;
    fila->frente = fila->tamanho = 0;
    fila->tras = capacidade - 1;
    fila->itens = (int*)malloc(capacidade * sizeof(int));
    return fila;
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

void DFSUtil(Grafo* grafo, int v, int* visitados) {
    // Marca o vértice como visitado e imprime
    visitados[v] = 1;
    printf("%d ", v);

    // Percorre os vizinhos do vértice `v`
    Node* adjacente = grafo->adj[v].head;
    while (adjacente != NULL) {
        if (!visitados[adjacente->destino]) {
            DFSUtil(grafo, adjacente->destino, visitados);
        }
        adjacente = adjacente->p;
    }
}

void DFS(Grafo* grafo, int inicio) {
    int* visitados = (int*)calloc(grafo->numVertices, sizeof(int));
    DFSUtil(grafo, inicio, visitados);
    free(visitados);
}

int estaVazia(Fila* fila) {
    return (fila->tamanho == 0);
}

void enfileirar(Fila* fila, int item) {
    fila->tras = (fila->tras + 1) % fila->capacidade;
    fila->itens[fila->tras] = item;
    fila->tamanho++;
}

int desenfileirar(Fila* fila) {
    int item = fila->itens[fila->frente];
    fila->frente = (fila->frente + 1) % fila->capacidade;
    fila->tamanho--;
    return item;
}

void BFS(Grafo* grafo, int inicio) {
    int* visitados = (int*)calloc(grafo->numVertices, sizeof(int));
    Fila* fila = criarFila(grafo->numVertices);

    // Marca o vértice inicial como visitado e enfileira
    visitados[inicio] = 1;
    enfileirar(fila, inicio);

    while (!estaVazia(fila)) {
        int v = desenfileirar(fila);
        printf("%d ", v);

        // Percorre os vizinhos do vértice `v`
        Node* adjacente = grafo->adj[v].head;
        while (adjacente != NULL) {
            if (!visitados[adjacente->destino]) {
                visitados[adjacente->destino] = 1;
                enfileirar(fila, adjacente->destino);
            }
            adjacente = adjacente->p;
        }
    }

    free(fila->itens);
    free(fila);
    free(visitados);
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
