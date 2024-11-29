#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Node {
    int destino;
    int peso;
    struct Node* p;
} Node;

typedef struct Lista {
    Node* head;
} Lista;

typedef struct Grafo {
    int numVertices;
    Lista* adj;
} Grafo;

Node* CriarNo(int destino, int peso) {
    Node* newNo = (Node*)malloc(sizeof(Node));
    newNo->destino = destino;
    newNo->peso = peso;
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

void adicionaAresta(Grafo* g, int o, int d, int peso) {
    // Adiciona a aresta de o para d
    Node* n = CriarNo(d, peso);
    n->p = g->adj[o].head;
    g->adj[o].head = n;

    // Para grafos não direcionados, adiciona também a aresta reversa
    Node* n2 = CriarNo(o, peso);
    n2->p = g->adj[d].head;
    g->adj[d].head = n2;
}

void floydWarshall(Grafo* g, int** dist) {
    int V = g->numVertices;

    // Inicializa a matriz de distâncias
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (i == j) {
                dist[i][j] = 0; // Distância de um vértice para ele mesmo é 0
            } else {
                dist[i][j] = INT_MAX; // Inicializa com infinito
            }
        }
    }

    // Preenche a matriz com as distâncias das arestas
    for (int i = 0; i < V; i++) {
        Node* aux = g->adj[i].head;
        while (aux) {
            // Apenas armazena o menor peso para arestas duplicadas
            if (dist[i][aux->destino] > aux->peso) {
                dist[i][aux->destino] = aux->peso;
            }
            aux = aux->p;
        }
    }

    // Floyd-Warshall: Atualiza as distâncias mínimas
    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX &&
                    dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
}

int encontrarDistanciaMaximaPontoCentral(Grafo* g) {
    int V = g->numVertices;
    int** dist = (int**)malloc(V * sizeof(int*));
    for (int i = 0; i < V; i++) {
        dist[i] = (int*)malloc(V * sizeof(int));
    }

    floydWarshall(g, dist);

    int pontoCentral = -1;
    int menorDistanciaMaxima = INT_MAX;

    for (int i = 0; i < V; i++) {
        int distanciaMaxima = 0;
        for (int j = 0; j < V; j++) {
            if (dist[i][j] != INT_MAX) {
                if (dist[i][j] > distanciaMaxima) {
                    distanciaMaxima = dist[i][j];
                }
            }
        }

        if (distanciaMaxima < menorDistanciaMaxima) {
            menorDistanciaMaxima = distanciaMaxima;
            pontoCentral = i;
        }
    }

    for (int i = 0; i < V; i++) {
        free(dist[i]);
    }
    free(dist);

    return menorDistanciaMaxima;
}

int main() {
    int o, d, p;
    int c, e;

    scanf("%d %d", &c, &e);

    Grafo* grafo = criarGrafo(c);

    for (int i = 0; i < e; i++) {
        scanf("%d %d %d", &o, &d, &p);
        adicionaAresta(grafo, o, d, p);
    }

    printf("%d\n", encontrarDistanciaMaximaPontoCentral(grafo));

    return 0;
}