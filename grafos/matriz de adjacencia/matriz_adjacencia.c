#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100  // Número máximo de vértices
#define INFINITO INT_MAX

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

// Algoritmo de Dijkstra
void dijkstra(Grafo* g, int origem) {
    int dist[MAX_VERTICES], visitado[MAX_VERTICES];
    int n = g->numVertices;

    // Inicialização
    for (int i = 0; i < n; i++) {
        dist[i] = INFINITO;
        visitado[i] = 0;
    }
    dist[origem] = 0;

    for (int i = 0; i < n - 1; i++) {
        int minDist = INFINITO, u = -1;

        // Encontra o vértice não visitado com menor distância
        for (int j = 0; j < n; j++) {
            if (!visitado[j] && dist[j] < minDist) {
                minDist = dist[j];
                u = j;
            }
        }

        if (u == -1) break; // Todos os vértices acessíveis foram visitados

        visitado[u] = 1;

        // Atualiza as distâncias dos vizinhos
        for (int v = 0; v < n; v++) {
            if (!visitado[v] && g->adj[u][v] != INFINITO && dist[u] != INFINITO && dist[u] + g->adj[u][v] < dist[v]) {
                dist[v] = dist[u] + g->adj[u][v];
            }
        }
    }

    printf("Distâncias a partir do vértice %d:\n", origem);
    for (int i = 0; i < n; i++) {
        if (dist[i] == INFINITO)
            printf("Para %d: INFINITO\n", i);
        else
            printf("Para %d: %d\n", i, dist[i]);
    }
}

// Algoritmo de Floyd-Warshall
void floydWarshall(Grafo* g) {
    int n = g->numVertices;
    int dist[MAX_VERTICES][MAX_VERTICES];

    // Inicialização
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dist[i][j] = g->adj[i][j];
        }
    }

    // Aplicação do algoritmo
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] != INFINITO && dist[k][j] != INFINITO &&
                    dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    // Exibição dos resultados
    printf("Matriz de distâncias mínimas:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (dist[i][j] == INFINITO)
                printf("INF ");
            else
                printf("%3d ", dist[i][j]);
        }
        printf("\n");
    }
}

int main() {
    Grafo grafo;
    int numVertices;

    printf("Digite o número de vértices do grafo: ");
    scanf("%d", &numVertices);

    inicializarGrafo(&grafo, numVertices);

    adicionarAresta(&grafo, 0, 1, 4);
    adicionarAresta(&grafo, 0, 2, 1);
    adicionarAresta(&grafo, 1, 3, 1);
    adicionarAresta(&grafo, 2, 1, 2);
    adicionarAresta(&grafo, 2, 3, 5);

    printf("\n--- Algoritmo de Dijkstra ---\n");
    dijkstra(&grafo, 0);

    printf("\n--- Algoritmo de Floyd-Warshall ---\n");
    floydWarshall(&grafo);

    return 0;
}
