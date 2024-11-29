#include <stdio.h>

// Função para verificar se é possível dividir o terreno conforme as áreas fornecidas
int pode_dividir(int a1, int a2, int a3, int a4) {
    int w, h;

    // Testa diferentes combinações de largura e altura possíveis
    for (w = 1; w * w <= a1 + a2 + a3 + a4; w++) {
        if ((a1 + a2 + a3 + a4) % w != 0) continue;
        h = (a1 + a2 + a3 + a4) / w;

        // Verifica todas as combinações para dividir o retângulo
        if ((a1 + a2 == w * h || a1 + a3 == w * h || a1 + a4 == w * h) &&
            (a1 == w * (h / 2) && a2 == w * (h / 2) ||
             a3 == w * (h / 2) && a4 == w * (h / 2))) {
            return 1;
        }
    }
    return 0;
}

int main() {
    int a1, a2, a3, a4;

    // Leitura das áreas
    scanf("%d %d %d %d", &a1, &a2, &a3, &a4);

    // Determina se é possível dividir o terreno
    if (pode_dividir(a1, a2, a3, a4)) {
        printf("S\n");
    } else {
        printf("N\n");
    }

    return 0;
}
