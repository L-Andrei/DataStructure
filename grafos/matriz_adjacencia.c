#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100  // Número máximo de vértices

typedef struct {
    int numVertices;             // Número de vértices no grafo
    int adj[MAX_VERTICES][MAX_VERTICES]; // Matriz de adjacência
} Grafo;

// Inicializa o grafo com um número específico de vértices
void inicializarGrafo(Grafo* g, int numVertices) {
    g->numVertices = numVertices;
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            g->adj[i][j] = 0; // Inicializa todas as arestas como inexistentes
        }
    }
}

// Adiciona uma aresta ao grafo
void adicionarAresta(Grafo* g, int origem, int destino, int peso) {
    if (origem >= g->numVertices || destino >= g->numVertices) {
        printf("Erro: Vértice inválido.\n");
        return;
    }
    g->adj[origem][destino] = peso;
}

// Exibe a matriz de adjacência
void exibirGrafo(Grafo* g) {
    printf("Matriz de Adjacência:\n");
    for (int i = 0; i < g->numVertices; i++) {
        for (int j = 0; j < g->numVertices; j++) {
            printf("%3d ", g->adj[i][j]);
        }
        printf("\n");
    }
}

// Remove uma aresta do grafo
void removerAresta(Grafo* g, int origem, int destino) {
    if (origem >= g->numVertices || destino >= g->numVertices) {
        printf("Erro: Vértice inválido.\n");
        return;
    }
    g->adj[origem][destino] = 0;
}

int main() {
    Grafo grafo;
    int numVertices;

    printf("Digite o número de vértices do grafo: ");
    scanf("%d", &numVertices);

    inicializarGrafo(&grafo, numVertices);

    adicionarAresta(&grafo, 0, 1, 10);
    adicionarAresta(&grafo, 0, 2, 5);
    adicionarAresta(&grafo, 1, 2, 2);
    adicionarAresta(&grafo, 2, 3, 8);

    printf("\n");
    exibirGrafo(&grafo);

    printf("\nRemovendo a aresta (0 -> 2):\n");
    removerAresta(&grafo, 0, 2);

    printf("\n");
    exibirGrafo(&grafo);

    return 0;
}
