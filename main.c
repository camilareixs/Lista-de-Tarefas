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
        printf("8 - Fitrar por prioridade e categoria\n");
        printf("9 - Exportar tarefas por prioridade\n");
        printf("10 - Exportar tarefas por categoria\n");
        printf("11 - Exportar tarefas por prioridade e categoria\n");
        printf("12 - Sair\n");
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
          {
            char categoriaFiltrar[100];
            int prioridadeFiltrar;
            printf("Digite a categoria para filtrar: ");
            scanf(" %99[^\n]", categoriaFiltrar);
            printf("Digite a prioridade para filtrar (de 0 a 10): ");
            scanf("%d", &prioridadeFiltrar);
            filtrarPorPrioridadeECategoria(tarefas, contador, categoriaFiltrar, prioridadeFiltrar);
          }
          break;
            case 9:
          {
            int prioridadeExportar;
            printf("Digite a prioridade para exportar: ");
            scanf("%d", &prioridadeExportar);
            exportarPorPrioridade(tarefas, contador, prioridadeExportar);
          }
          break;
          case 10:
          {
              char categoriaExportar[100];
              printf("Digite a categoria para exportar: ");
              scanf(" %99[^\n]", categoriaExportar);
              exportarPorCategoria(tarefas, contador, categoriaExportar);
          }
          break;
          case 11:
          {
              int prioridadeExportar;
              char categoriaExportar[100];
              printf("Digite a prioridade para exportar: ");
              scanf("%d", &prioridadeExportar);
              printf("Digite a categoria para exportar: ");
              scanf(" %99[^\n]", categoriaExportar);
              exportarPorPrioridadeECategoria(tarefas, contador, prioridadeExportar, categoriaExportar);
          }
          break;
          
            case 12:
                salvarTarefas(tarefas, contador);
                return 0;
            default:
                printf("Opção inválida. Por favor, escolha novamente.\n");
        }
    }

    return 0;
}
