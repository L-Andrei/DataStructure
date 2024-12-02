#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100 // Número máximo de vértices

// Estrutura do grafo utilizando matriz de adjacência
typedef struct {
    int matriz[MAX][MAX]; // Matriz de adjacência
    int numVertices;      // Número de vértices no grafo
} Grafo;

// Inicializa o grafo, definindo todos os valores da matriz como 0
void inicializarGrafo(Grafo *g, int numVertices) {
    g->numVertices = numVertices;
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            g->matriz[i][j] = 0;
        }
    }
}

// Adiciona uma aresta entre dois vértices (grafo não direcionado)
void adicionarAresta(Grafo *g, int v1, int v2) {
    g->matriz[v1][v2] = 1; // Conecta v1 a v2
    g->matriz[v2][v1] = 1; // Conecta v2 a v1
}

// Realiza uma busca em profundidade (DFS) para verificar conexidade
void dfs(Grafo *g, int v, bool *visitado) {
    visitado[v] = true; // Marca o vértice como visitado
    for (int i = 0; i < g->numVertices; i++) {
        if (g->matriz[v][i] && !visitado[i]) { // Se há uma conexão e não foi visitado
            dfs(g, i, visitado); // Continua a busca recursivamente
        }
    }
}

// Verifica se o grafo é conexo
bool ehConexo(Grafo *g) {
    bool visitado[MAX] = {false}; // Inicializa todos os vértices como não visitados
    dfs(g, 0, visitado); // Começa a busca a partir do vértice 0
    for (int i = 0; i < g->numVertices; i++) {
        if (!visitado[i]) { // Se algum vértice não foi visitado, o grafo não é conexo
            return false;
        }
    }
    return true; // Todos os vértices foram visitados, o grafo é conexo
}

// Verifica se o grafo é Euleriano
bool ehEuleriano(Grafo *g) {
    if (!ehConexo(g)) { // Um grafo Euleriano deve ser conexo
        return false;
    }
    for (int i = 0; i < g->numVertices; i++) {
        int grau = 0;
        for (int j = 0; j < g->numVertices; j++) {
            if (g->matriz[i][j]) { // Conta o grau do vértice
                grau++;
            }
        }
        if (grau % 2 != 0) { // Um grafo Euleriano deve ter todos os vértices com grau par
            return false;
        }
    }
    return true;
}

// Função auxiliar para verificar a existência de um ciclo Hamiltoniano (backtracking)
bool cicloHamiltonianoUtil(Grafo *g, int pos, int *caminho, bool *visitado) {
    if (pos == g->numVertices) { // Se visitamos todos os vértices
        return g->matriz[caminho[pos - 1]][caminho[0]] == 1; // Verifica se há uma aresta para o início
    }
    for (int v = 0; v < g->numVertices; v++) {
        if (g->matriz[caminho[pos - 1]][v] && !visitado[v]) { // Se há conexão e não foi visitado
            visitado[v] = true; // Marca como visitado
            caminho[pos] = v; // Adiciona ao caminho
            if (cicloHamiltonianoUtil(g, pos + 1, caminho, visitado)) {
                return true;
            }
            visitado[v] = false; // Backtracking
        }
    }
    return false;
}

// Verifica se o grafo é Hamiltoniano
bool ehHamiltoniano(Grafo *g) {
    int caminho[MAX]; // Caminho que será percorrido
    bool visitado[MAX] = {false}; // Inicializa todos os vértices como não visitados
    for (int i = 0; i < g->numVertices; i++) {
        caminho[i] = -1; // Inicializa o caminho
    }
    caminho[0] = 0; // Começa pelo vértice 0
    visitado[0] = true; // Marca o vértice 0 como visitado
    return cicloHamiltonianoUtil(g, 1, caminho, visitado);
}

int main() {
    Grafo g;
    int numVertices = 5;

    inicializarGrafo(&g, numVertices);


    adicionarAresta(&g, 0, 1);
    adicionarAresta(&g, 1, 2);
    adicionarAresta(&g, 2, 3);
    adicionarAresta(&g, 3, 4);
    adicionarAresta(&g, 4, 0);


    printf("Grafo é conexo? %s\n", ehConexo(&g) ? "Sim" : "Não");
    printf("Grafo é Euleriano? %s\n", ehEuleriano(&g) ? "Sim" : "Não");
    printf("Grafo é Hamiltoniano? %s\n", ehHamiltoniano(&g) ? "Sim" : "Não");

    return 0;
}
