#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF INT_MAX

typedef struct {
    int origem, destino, peso;
} Aresta;

typedef struct {
    int V, E;       // Número de vértices e arestas
    int** matriz;   // Matriz de adjacência
} Grafo;

// Cria um grafo com matriz de adjacência
Grafo* criarGrafo(int V) {
    Grafo* grafo = (Grafo*)malloc(sizeof(Grafo));
    grafo->V = V;
    grafo->E = 0;

    grafo->matriz = (int**)malloc(V * sizeof(int*));
    for (int i = 0; i < V; i++) {
        grafo->matriz[i] = (int*)malloc(V * sizeof(int));
        for (int j = 0; j < V; j++) {
            grafo->matriz[i][j] = INF; // Inicializa com valores infinitos
        }
    }

    return grafo;
}

// Adiciona uma aresta ao grafo
void adicionaAresta(Grafo* grafo, int origem, int destino, int peso) {
    grafo->matriz[origem][destino] = peso;
    grafo->matriz[destino][origem] = peso; // Grafo não direcionado
    grafo->E++;
}

// Imprime o grafo como matriz de adjacência
void imprimirGrafo(Grafo* grafo) {
    printf("Matriz de adjacencia:\n");
    for (int i = 0; i < grafo->V; i++) {
        for (int j = 0; j < grafo->V; j++) {
            if (grafo->matriz[i][j] == INF)
                printf("INF ");
            else
                printf("%3d ", grafo->matriz[i][j]);
        }
        printf("\n");
    }
}

// Algoritmo de Prim
void algoritmoPrim(Grafo* grafo) {
    int V = grafo->V;
    int* chave = (int*)malloc(V * sizeof(int)); // Valores mínimos para cada vértice
    int* pai = (int*)malloc(V * sizeof(int));  // Array para armazenar a árvore geradora mínima
    int* visitados = (int*)calloc(V, sizeof(int)); // Vértices já incluídos na MST

    for (int i = 0; i < V; i++) {
        chave[i] = INF;
        pai[i] = -1;
    }
    chave[0] = 0; // Começa pelo primeiro vértice

    for (int count = 0; count < V - 1; count++) {
        // Seleciona o vértice com a menor chave que ainda não foi incluído na MST
        int u = -1;
        for (int i = 0; i < V; i++) {
            if (!visitados[i] && (u == -1 || chave[i] < chave[u])) {
                u = i;
            }
        }

        visitados[u] = 1;

        // Atualiza os valores das chaves dos vértices adjacentes a `u`
        for (int v = 0; v < V; v++) {
            if (grafo->matriz[u][v] != INF && !visitados[v] && grafo->matriz[u][v] < chave[v]) {
                chave[v] = grafo->matriz[u][v];
                pai[v] = u;
            }
        }
    }

    printf("\nÁrvore Geradora Mínima (Prim):\n");
    for (int i = 1; i < V; i++) {
        printf("%d - %d, Peso: %d\n", pai[i], i, grafo->matriz[i][pai[i]]);
    }

    free(chave);
    free(pai);
    free(visitados);
}

// Comparador para ordenar arestas por peso
int comparador(const void* a, const void* b) {
    return ((Aresta*)a)->peso - ((Aresta*)b)->peso;
}

// Busca o conjunto ao qual um elemento pertence (para Kruskal)
int encontrar(int* parent, int i) {
    if (parent[i] == i)
        return i;
    return encontrar(parent, parent[i]);
}

// Une dois subconjuntos (para Kruskal)
void unir(int* parent, int* rank, int x, int y) {
    int raizX = encontrar(parent, x);
    int raizY = encontrar(parent, y);

    if (rank[raizX] < rank[raizY])
        parent[raizX] = raizY;
    else if (rank[raizX] > rank[raizY])
        parent[raizY] = raizX;
    else {
        parent[raizY] = raizX;
        rank[raizX]++;
    }
}

// Algoritmo de Kruskal
void algoritmoKruskal(Grafo* grafo) {
    int V = grafo->V;
    int E = 0;
    Aresta* arestas = (Aresta*)malloc(grafo->E * sizeof(Aresta));

    // Constrói a lista de arestas a partir da matriz de adjacência
    for (int i = 0; i < V; i++) {
        for (int j = i + 1; j < V; j++) {
            if (grafo->matriz[i][j] != INF) {
                arestas[E++] = (Aresta){i, j, grafo->matriz[i][j]};
            }
        }
    }

    // Ordena as arestas pelo peso
    qsort(arestas, E, sizeof(Aresta), comparador);

    // Inicializa as estruturas para união e busca
    int* parent = (int*)malloc(V * sizeof(int));
    int* rank = (int*)calloc(V, sizeof(int));

    for (int i = 0; i < V; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    printf("\nÁrvore Geradora Mínima (Kruskal):\n");
    int totalPeso = 0;
    for (int i = 0, arestasIncluidas = 0; arestasIncluidas < V - 1 && i < E; i++) {
        int u = arestas[i].origem;
        int v = arestas[i].destino;

        // Verifica se adicionar a aresta forma um ciclo
        if (encontrar(parent, u) != encontrar(parent, v)) {
            printf("%d - %d, Peso: %d\n", u, v, arestas[i].peso);
            totalPeso += arestas[i].peso;
            unir(parent, rank, u, v);
            arestasIncluidas++;
        }
    }

    printf("Peso Total: %d\n", totalPeso);

    free(arestas);
    free(parent);
    free(rank);
}

// Exemplo de uso
int main() {
    Grafo* grafo = criarGrafo(5);

    adicionaAresta(grafo, 0, 1, 2);
    adicionaAresta(grafo, 0, 3, 6);
    adicionaAresta(grafo, 1, 2, 3);
    adicionaAresta(grafo, 1, 3, 8);
    adicionaAresta(grafo, 1, 4, 5);
    adicionaAresta(grafo, 2, 4, 7);
    adicionaAresta(grafo, 3, 4, 9);

    imprimirGrafo(grafo);

    algoritmoPrim(grafo);
    algoritmoKruskal(grafo);

    // Libera memória do grafo
    for (int i = 0; i < grafo->V; i++) {
        free(grafo->matriz[i]);
    }
    free(grafo->matriz);
    free(grafo);

    return 0;
}
