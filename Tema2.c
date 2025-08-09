#include <stdio.h>
#include <string.h>
#include <locale.h>

typedef struct {
    char estado[3];
    char codigo[5];
    char nome[50];
    int populacao;
    float pib;          // está em bilhoes
    float area;         // km²
    int pontosTuristicos;
    float densidade;    // populacao/area
    float pibPerCapita; // PIB/populacao
} Carta;

// exibir uma carta resumida (nome e estado)
void exibirCartaResumo(Carta c) {
    printf("%s (%s)", c.nome, c.estado);
}

//  mostra o menu dinamico do segundo atributo, excluindo o escolhido no primeiro
int menuSegundoAtributo(int excluido) {
    printf("Escolha o segundo atributo:\n");
    int op = 1;
    for (int i = 1; i <= 6; i++) {
        if (i == excluido) continue; // pula o atributo ja escolhido

        switch(i) {
            case 1: printf("%d - Populacao\n", op++); break;
            case 2: printf("%d - PIB\n", op++); break;
            case 3: printf("%d - Area\n", op++); break;
            case 4: printf("%d - Pontos Turisticos\n", op++); break;
            case 5: printf("%d - Densidade Demografica\n", op++); break;
            case 6: printf("%d - PIB per Capita\n", op++); break;
        }
    }
    printf("Opcao: ");

    int escolha_usuario;
    scanf("%d", &escolha_usuario);
    return escolha_usuario;
}

// Funcao para mapear o numero do menu (1 a 5) para o atributo real (1 a 6) ignorando o excluido
int mapearSegundoAtributo(int excluido, int escolha) {
    int count = 0;
    for (int i = 1; i <= 6; i++) {
        if (i == excluido) continue;
        count++;
        if (count == escolha) return i;
    }
    return -1; // invalido
}

// Funcao para obter o nome do atributo
const char* nomeAtributo(int attr) {
    switch(attr) {
        case 1: return "Populacao";
        case 2: return "PIB (bilhoes)";
        case 3: return "Area (km2)";
        case 4: return "Pontos Turisticos";
        case 5: return "Densidade Demografica";
        case 6: return "PIB per Capita";
        default: return "Atributo invalido";
    }
}

// Funcao para pegar o valor do atributo da carta
double valorAtributo(Carta c, int attr) {
    switch(attr) {
        case 1: return (double)c.populacao;
        case 2: return (double)c.pib;
        case 3: return (double)c.area;
        case 4: return (double)c.pontosTuristicos;
        case 5: return (double)c.densidade;
        case 6: return (double)c.pibPerCapita;
        default: return -1;
    }
}

// Funcao que compara dois valores com a regra da densidade invertida
// Retorna 1 se valor1 vence, 2 se valor2 vence, 0 empate
int comparaAtributos(int attr, double v1, double v2) {
    if (attr == 5) { // Densidade Demografica, menor vence
        if (v1 < v2) return 1;
        else if (v1 > v2) return 2;
        else return 0;
    } else {
        if (v1 > v2) return 1;
        else if (v1 < v2) return 2;
        else return 0;
    }
}

int main() {
    setlocale(LC_ALL, ""); // ajuda na exibicao no terminal

    // Cartas com Itajai e Maceio
    Carta c1 = {"SC", "A01", "Itajai", 280000, 12.0f, 301.3f, 15, 0, 0};
    Carta c2 = {"AL", "B02", "Maceio", 1000000, 18.5f, 511.1f, 25, 0, 0};

    // Calcular atributos derivados
    c1.densidade = c1.populacao / c1.area;
    c1.pibPerCapita = (c1.pib * 1e9f) / c1.populacao;

    c2.densidade = c2.populacao / c2.area;
    c2.pibPerCapita = (c2.pib * 1e9f) / c2.populacao;

    int atr1, atr2;

    printf("=== Super Trunfo - Comparacao com 2 Atributos ===\n");
    printf("Carta 1: ");
    exibirCartaResumo(c1);
    printf("\nCarta 2: ");
    exibirCartaResumo(c2);
    printf("\n\nEscolha o primeiro atributo:\n");
    printf("1 - Populacao\n2 - PIB\n3 - Area\n4 - Pontos Turisticos\n5 - Densidade Demografica\n6 - PIB per Capita\n");
    printf("Opcao: ");
    scanf("%d", &atr1);

    if (atr1 < 1 || atr1 > 6) {
        printf("Atributo invalido. Encerrando.\n");
        return 1;
    }

    // Menu dinamico para o segundo atributo
    int escolha2 = menuSegundoAtributo(atr1);

    if (escolha2 < 1 || escolha2 > 5) {
        printf("Opcao invalida no segundo atributo. Encerrando.\n");
        return 1;
    }

    atr2 = mapearSegundoAtributo(atr1, escolha2);
    if (atr2 == -1) {
        printf("Erro ao mapear o segundo atributo. Encerrando.\n");
        return 1;
    }

    // Obter valores dos atributos para as duas cartas
    double val1_attr1 = valorAtributo(c1, atr1);
    double val2_attr1 = valorAtributo(c2, atr1);

    double val1_attr2 = valorAtributo(c1, atr2);
    double val2_attr2 = valorAtributo(c2, atr2);

    // Soma dos valores para decidir vencedor
    double soma1 = val1_attr1 + val1_attr2;
    double soma2 = val2_attr1 + val2_attr2;

    // Mostrar resultados formatados
    printf("\n\nResultado da comparacao:\n");
    printf("%-25s | %-20s | %-20s\n", "Atributo", "Carta 1", "Carta 2");
    printf("-------------------------------------------------------------------\n");
    printf("%-25s | %-20.2f | %-20.2f\n", nomeAtributo(atr1), val1_attr1, val2_attr1);
    printf("%-25s | %-20.2f | %-20.2f\n", nomeAtributo(atr2), val1_attr2, val2_attr2);
    printf("-------------------------------------------------------------------\n");
    printf("%-25s | %-20.2f | %-20.2f\n", "Soma dos atributos", soma1, soma2);

    printf("\nCarta 1: ");
    exibirCartaResumo(c1);
    printf("\nCarta 2: ");
    exibirCartaResumo(c2);
    printf("\n\n");

    if (soma1 > soma2)
        printf(">>> Carta 1 venceu a rodada! <<<\n");
    else if (soma2 > soma1)
        printf(">>> Carta 2 venceu a rodada! <<<\n");
    else
        printf(">>> Empate! <<<\n");

    return 0;
}
