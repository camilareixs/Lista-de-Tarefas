#include <stdio.h>
#include "biblioteca.h"

int main() {
    struct Tarefa tarefas[100];
    int contador = 0;
    int opcao;

    FILE *arquivo = fopen("tarefas.txt", "a+");
    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo 'tarefas.txt'\n");
        return 1; 
    }
    fclose(arquivo);

    carregarTarefas(tarefas, &contador);

    while (1) {
        printf("\nOlá, o que você gostaria de fazer?\n");
        printf("1 - Adicionar nova tarefa\n");
        printf("2 - Listar todas as tarefas\n");
        printf("3 - Remover tarefa por título\n");
        printf("4 - Alterar uma tarefa\n");
        printf("5 - Fitrar por prioridade\n");
        printf("6 - Fitrar por estado\n");
        printf("7 - Fitrar por categoria\n");
        printf("8 - Sair\n");
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
                alterarTarefa(tarefas, &contador);
                salvarTarefas(tarefas, contador);
                break;
            case 5:
                filtrarPorPrioridade(tarefas, contador);
                break;
            case 6:
                filtrarPorEstado(tarefas, contador);
                break;
            case 7:
                {
                    char categoriaFiltrar[100];
                    printf("Digite a categoria para filtrar: ");
                    scanf(" %99[^\n]", categoriaFiltrar);
                    filtrarPorCategoriaPrioridade(tarefas, contador, categoriaFiltrar);
                }
                break;   
            case 8:
                salvarTarefas(tarefas, contador);
                return 0;
            default:
                printf("Opção inválida. Por favor, escolha novamente.\n");
        }
    }

    return 0;
}
