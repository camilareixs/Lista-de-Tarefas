#include <stdio.h>
#include "biblioteca.h"

int main() {
    struct Tarefa tarefas[100];
    int contador = 0;
    int opcao;

    carregarTarefas(tarefas, &contador);

    while (1) {
        printf("\nOlá, o que você gostaria de fazer?\n");
        printf("1 - Adicionar nova tarefa\n");
        printf("2 - Listar todas as tarefas\n");
        printf("3 - Remover tarefa por título\n");
        printf("4 - Sair\n");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarTarefa(tarefas, &contador);
                salvarTarefas(tarefas, contador);
                break;
            case 2:
                listarTarefas(tarefas, contador);
                break;
            case 3:
                removerTarefa(tarefas, &contador);
                salvarTarefas(tarefas, contador);
                break;
            case 4:
                return 0;
            default:
                printf("Opção inválida. Por favor, escolha novamente.\n");
        }
    }

    return 0;
}
