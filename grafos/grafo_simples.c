#include <stdio.h>
#include <stdlib.h>

// Estrutura para representar um nó de uma lista de adjacência
typedef struct Node {
    int destino;          // Identifica o vértice adjacente
    struct Node* p;       // Ponteiro para o próximo nó na lista
} Node;

// Lista de adjacência de um vértice
typedef struct Lista {
    Node* head;           // Ponteiro para o primeiro nó da lista
} Lista;

// Estrutura para representar o grafo
typedef struct Grafo {
    int numVertices;      // Número de vértices no grafo
    Lista* adj;           // Array de listas de adjacência (uma por vértice)
} Grafo;

// Estrutura para representar uma fila circular
typedef struct Fila {
    int* itens;           // Array que armazena os elementos da fila
    int frente;           // Índice do primeiro elemento na fila
    int tras;             // Índice do último elemento na fila
    int tamanho;          // Número atual de elementos na fila
    int capacidade;       // Capacidade máxima da fila
} Fila;

// Cria um novo nó de lista de adjacência
Node* CriarNo(int destino) {
    Node* newNo = (Node*)malloc(sizeof(Node));
    newNo->destino = destino;
    newNo->p = NULL; // O ponteiro inicializa como NULL (final da lista)
    return newNo;
}

// Cria um grafo com um número especificado de vértices
Grafo* criarGrafo(int vertices) {
    Grafo* newGrafo = (Grafo*)malloc(sizeof(Grafo));
    newGrafo->numVertices = vertices;

    // Aloca memória para o array de listas de adjacência
    newGrafo->adj = (Lista*)malloc(vertices * sizeof(Lista));

    // Inicializa cada lista de adjacência como vazia (head = NULL)
    for (int i = 0; i < vertices; i++) {
        newGrafo->adj[i].head = NULL;
    }

    return newGrafo;
}

// Cria uma fila com uma capacidade especificada
Fila* criarFila(int capacidade) {
    Fila* fila = (Fila*)malloc(sizeof(Fila));
    fila->capacidade = capacidade;
    fila->frente = fila->tamanho = 0;
    fila->tras = capacidade - 1; // Ajusta o índice inicial de `tras` para uma fila circular
    fila->itens = (int*)malloc(capacidade * sizeof(int));
    return fila;
}

// Adiciona uma aresta ao grafo não direcionado
void adicionaAresta(Grafo* g, int o, int d) {
    // Adiciona um nó à lista de adjacência do vértice de origem `o`
    Node* n = CriarNo(d);
    n->p = g->adj[o].head;  // O novo nó aponta para o head atual
    g->adj[o].head = n;     // Atualiza o head da lista de `o`

    // Adiciona o vértice de origem `o` à lista de adjacência de destino `d`
    Node* n2 = CriarNo(o);
    n2->p = g->adj[d].head;
    g->adj[d].head = n2;
}

// Imprime as listas de adjacência do grafo
void imprimirGrafo(Grafo* g) {
    for (int i = 0; i < g->numVertices; i++) {
        Node* aux = g->adj[i].head; // Ponteiro para percorrer a lista
        printf("Vertice %d: ", i);
        while (aux) {
            printf("%d -> ", aux->destino); // Imprime o vértice adjacente
            aux = aux->p; // Avança para o próximo nó
        }
        printf("NULL\n");
    }
}

// Remove uma aresta entre dois vértices
void removerAresta(Grafo* g, int o, int d) {
    Node* atual = g->adj[o].head;
    Node* temp = NULL;

    // Procura o nó com destino `d` na lista de adjacência de `o`
    while (atual != NULL && atual->destino != d) {
        temp = atual;         // Guarda o nó anterior
        atual = atual->p;     // Avança para o próximo nó
    }
    if (atual != NULL) {
        if (temp == NULL) {
            g->adj[o].head = atual->p; // Remove o head
        } else {
            temp->p = atual->p; // Remove o nó intermediário
        }
        free(atual);           // Libera a memória do nó removido
    }

    // Repete o processo para o vértice `d` e sua lista
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

// Função recursiva auxiliar para DFS
void DFSUtil(Grafo* grafo, int v, int* visitados) {
    visitados[v] = 1; // Marca o vértice como visitado
    printf("%d ", v);

    // Percorre todos os vértices adjacentes
    Node* adjacente = grafo->adj[v].head;
    while (adjacente != NULL) {
        if (!visitados[adjacente->destino]) { // Realiza DFS nos não visitados
            DFSUtil(grafo, adjacente->destino, visitados);
        }
        adjacente = adjacente->p; // Avança para o próximo adjacente
    }
}

// Inicia a DFS a partir de um vértice inicial
void DFS(Grafo* grafo, int inicio) {
    int* visitados = (int*)calloc(grafo->numVertices, sizeof(int)); // Array de visitados
    DFSUtil(grafo, inicio, visitados); // Chama a função recursiva
    free(visitados); // Libera a memória alocada
}

// Verifica se a fila está vazia
int estaVazia(Fila* fila) {
    return (fila->tamanho == 0); // Fila está vazia se `tamanho` for 0
}

// Enfileira um elemento na fila circular
void enfileirar(Fila* fila, int item) {
    fila->tras = (fila->tras + 1) % fila->capacidade; // Atualiza o índice `tras` de forma circular
    fila->itens[fila->tras] = item; // Adiciona o elemento
    fila->tamanho++; // Incrementa o tamanho da fila
}

// Remove e retorna o elemento da frente da fila circular
int desenfileirar(Fila* fila) {
    int item = fila->itens[fila->frente]; // Recupera o elemento da frente
    fila->frente = (fila->frente + 1) % fila->capacidade; // Atualiza o índice `frente` de forma circular
    fila->tamanho--; // Decrementa o tamanho da fila
    return item;
}

// Realiza a BFS a partir de um vértice inicial
void BFS(Grafo* grafo, int inicio) {
    int* visitados = (int*)calloc(grafo->numVertices, sizeof(int)); // Array de visitados
    Fila* fila = criarFila(grafo->numVertices); // Cria a fila

    visitados[inicio] = 1; // Marca o vértice inicial como visitado
    enfileirar(fila, inicio); // Enfileira o vértice inicial

    while (!estaVazia(fila)) { // Enquanto houver vértices na fila
        int v = desenfileirar(fila);
        printf("%d ", v);

        Node* adjacente = grafo->adj[v].head;
        while (adjacente != NULL) {
            if (!visitados[adjacente->destino]) {
                visitados[adjacente->destino] = 1; // Marca como visitado
                enfileirar(fila, adjacente->destino); // Enfileira o adjacente
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


    adicionaAresta(grafo, 0, 1);
    adicionaAresta(grafo, 1, 2);
    adicionaAresta(grafo, 2, 3);
    adicionaAresta(grafo, 3, 4);


    imprimirGrafo(grafo);

    return 0;
}
